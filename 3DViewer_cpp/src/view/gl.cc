#include "gl.h"

#include <QImage>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QString>

namespace s21 {

GlWidget::GlWidget(Controller &controller, QWidget *parent)
    : QOpenGLWidget(parent),
      controller_(controller),
      vbo_(QOpenGLBuffer::VertexBuffer),
      ibo_(QOpenGLBuffer::IndexBuffer) {
  setMinimumSize(1000, 500);
  InitGif();
}

void GlWidget::initializeGL() {
  initializeOpenGLFunctions();
  vbo_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);

  vbo_.create();
  ibo_.create();

  vao_.create();
  vao_.bind();

  vbo_.bind();
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  ibo_.bind();

  vao_.release();

  InitShaders();
  controller_.SetPerspectiveProjection(fov_, near_, far_);

  QObject::connect(context(), &QOpenGLContext::aboutToBeDestroyed, this,
                   &GlWidget::Cleanup);
}

void GlWidget::InitShaders() {
  makeCurrent();

  AllocateShaders();
  CompileShaders();
  BuildShaders();
}

void GlWidget::AllocateShaders() {
  transform_ = new QOpenGLShader(QOpenGLShader::Vertex, this);
  line_fragment_ = new QOpenGLShader(QOpenGLShader::Fragment, this);
  line_geometry_ = new QOpenGLShader(QOpenGLShader::Geometry, this);
  point_fragment_ = new QOpenGLShader(QOpenGLShader::Fragment, this);
  point_square_geometry_ = new QOpenGLShader(QOpenGLShader::Geometry, this);
  point_circle_geometry_ = new QOpenGLShader(QOpenGLShader::Geometry, this);
}

void GlWidget::CompileShaders() {
  makeCurrent();
  transform_->compileSourceFile(":/vertex.vert");
  line_fragment_->compileSourceFile(":/lines.frag");
  point_fragment_->compileSourceFile(":/points.frag");
  point_circle_geometry_->compileSourceFile(":/circle_point.geom");
  point_square_geometry_->compileSourceFile(":/square_point.geom");
  line_geometry_->compileSourceFile(":/lines.geom");
}

void GlWidget::BuildShaders() {
  line_ = BuildLineShader();
  line_thick_ = BuildThickLineShader();
  point_circle_ = BuildCirclePointShader();
  point_square_ = BuildSquarePointShader();
}

QOpenGLShaderProgram *GlWidget::BuildLineShader() {
  QOpenGLShaderProgram *shader = new QOpenGLShaderProgram(this);

  makeCurrent();
  shader->create();
  shader->addShader(transform_);
  shader->addShader(line_fragment_);
  shader->link();

  return shader;
}

QOpenGLShaderProgram *GlWidget::BuildThickLineShader() {
  QOpenGLShaderProgram *shader = new QOpenGLShaderProgram(this);

  makeCurrent();
  shader->create();
  shader->addShader(transform_);
  shader->addShader(line_fragment_);
  shader->addShader(line_geometry_);
  shader->link();

  return shader;
}

QOpenGLShaderProgram *GlWidget::BuildCirclePointShader() {
  QOpenGLShaderProgram *shader = new QOpenGLShaderProgram(this);

  makeCurrent();
  shader->create();
  shader->addShader(transform_);
  shader->addShader(point_fragment_);
  shader->addShader(point_circle_geometry_);
  shader->link();

  return shader;
}

QOpenGLShaderProgram *GlWidget::BuildSquarePointShader() {
  QOpenGLShaderProgram *shader = new QOpenGLShaderProgram(this);

  makeCurrent();
  shader->create();
  shader->addShader(transform_);
  shader->addShader(point_fragment_);
  shader->addShader(point_square_geometry_);
  shader->link();

  return shader;
}

void GlWidget::paintGL() {
  glClearColor(background_color_.redF(), background_color_.greenF(),
               background_color_.blueF(), background_color_.alphaF());

  vao_.bind();
  vbo_.write(0, controller_.Vertices().data(),
             controller_.Vertices().size() * sizeof(float));
  vao_.release();

  DrawEdges();
  if (vertex_type_ != VertexType::kNone) {
    DrawPoints();
  }
}

void GlWidget::DrawEdges() {
  makeCurrent();
  QOpenGLShaderProgram *line = 0;

  if (line_size_ == 1.0) {
    line = line_;
  } else {
    line = line_thick_;
  }

  line->bind();
  line->setUniformValue("resolution", width(), height());
  line->setUniformValue("transform", controller_.ProjectionMatrix());
  line->setUniformValue("world", controller_.WorldMatrix());
  line->setUniformValue("edge_color", edge_color_.redF(), edge_color_.greenF(),
                        edge_color_.blueF(), edge_color_.alphaF());
  line->setUniformValue("line_size", line_size_);
  line->setUniformValue("dash_threshold", dash_threshold_);

  vao_.bind();
  glDrawElements(GL_LINES, controller_.Indexes().size(), GL_UNSIGNED_INT,
                 nullptr);
  vao_.release();
  line->release();
}

void GlWidget::DrawPoints() {
  makeCurrent();
  QOpenGLShaderProgram *point = 0;

  if (vertex_type_ == VertexType::kSquare) {
    point = point_square_;
  } else if (vertex_type_ == VertexType::kCircle) {
    point = point_circle_;
  } else {
    return;
  }

  point->bind();
  point->setUniformValue("resolution", width(), height());
  point->setUniformValue("transform", controller_.ProjectionMatrix());
  point->setUniformValue("world", controller_.WorldMatrix());
  point->setUniformValue("vertex_color", vertex_color_.redF(),
                         vertex_color_.greenF(), vertex_color_.blueF(),
                         vertex_color_.alphaF());
  point->setUniformValue("point_size", point_size_);

  vao_.bind();
  glDrawElements(GL_POINTS, controller_.Indexes().size(), GL_UNSIGNED_INT,
                 nullptr);
  vao_.release();
  point->release();
}

void GlWidget::LoadNewObject() {
  makeCurrent();
  vao_.bind();
  vbo_.allocate(controller_.Vertices().data(),
                controller_.Vertices().size() * sizeof(float));
  ibo_.allocate(controller_.Indexes().data(),
                controller_.Indexes().size() * sizeof(unsigned int));
  vao_.release();
  controller_.MoveZ(-1.0);
}

void GlWidget::mousePressEvent(QMouseEvent *event) {
  mouse_last_position_ = event->position().toPoint();
}

void GlWidget::mouseMoveEvent(QMouseEvent *event) {
  QPoint mouse_cur_position = event->position().toPoint();
  QPoint diff_position = mouse_last_position_ - mouse_cur_position;

  if (event->buttons() & Qt::LeftButton) {
    controller_.MoveX(-diff_position.x() / 1000.0);
    controller_.MoveY(diff_position.y() / 1000.0);
    emit ChangeTextMove(diff_position);
  } else if (event->buttons() & Qt::RightButton) {
    controller_.RotateX(-diff_position.y());
    controller_.RotateY(-diff_position.x());
    emit ChangeTextRotate(diff_position);
  }

  mouse_last_position_ = mouse_cur_position;
  update();
}

void GlWidget::SetBackgroundColor(const QColor color) {
  background_color_ = color;
  update();
}
void GlWidget::SetEdgeColor(const QColor color) {
  edge_color_ = color;
  update();
}
void GlWidget::SetVertexColor(const QColor color) {
  vertex_color_ = color;
  update();
}

void GlWidget::SetVertexSize(const float size) {
  point_size_ = size;
  update();
}
void GlWidget::SetEdgeSize(const float size) {
  line_size_ = size;
  update();
}

void GlWidget::SetVertexType(const VertexType type) {
  vertex_type_ = type;
  update();
}

void GlWidget::SetEdgeType(const EdgeType type) {
  if (type == EdgeType::kSolid) {
    dash_threshold_ = 1.0;
  } else {
    dash_threshold_ = 0.5;
  }
  update();
}

void GlWidget::SetProjectionType(const ProjectionType type) {
  if (type == ProjectionType::kCentral) {
    controller_.SetPerspectiveProjection(fov_, near_, far_);
  } else {
    controller_.SetOrthographicProjection(near_, far_);
  }
  update();
}

void GlWidget::wheelEvent(QWheelEvent *event) {
  double wheel_y = event->angleDelta().y();
  double new_scale = wheel_y > 0 ? last_scale_ + 0.1 : last_scale_ - 0.1;
  if (0.1 <= new_scale && new_scale <= 3) {
    controller_.Scale(new_scale / last_scale_);
    update();
    emit ChangeTextScale(new_scale);
    last_scale_ = new_scale;
  }
}

GlWidget::~GlWidget() { Cleanup(); }

void GlWidget::Cleanup() {
  makeCurrent();

  vbo_.destroy();
  ibo_.destroy();
  vao_.destroy();

  DeleteShaders();

  doneCurrent();
  QObject::disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this,
                      &GlWidget::Cleanup);
}

void GlWidget::DeleteShaders() {
  delete transform_;
  transform_ = 0;
  DeleteLineShaders();
  DeletePointShaders();
}

void GlWidget::DeleteLineShaders() {
  delete line_fragment_;
  line_fragment_ = 0;
  delete line_geometry_;
  line_fragment_ = 0;
  delete line_;
  line_ = 0;
  delete line_thick_;
  line_thick_ = 0;
}

void GlWidget::DeletePointShaders() {
  delete point_fragment_;
  point_fragment_ = 0;
  delete point_square_geometry_;
  point_square_geometry_ = 0;
  delete point_circle_geometry_;
  point_circle_geometry_ = 0;
  delete point_circle_;
  point_circle_ = 0;
  delete point_square_;
  point_square_ = 0;
}

void GlWidget::Screenshot(const QString &path) {
  QImage image = grabFramebuffer();
  image.save(path);
}

void GlWidget::InitGif() {
  gif_timer_ = new QTimer(this);
  gif_timer_->setSingleShot(true);
  QObject::connect(gif_timer_, &QTimer::timeout, this,
                   &GlWidget::EndGifCapture);

  frame_timer_ = new QTimer(this);
  QObject::connect(frame_timer_, &QTimer::timeout, this,
                   &GlWidget::AddGifFrame);

  gif_image_.setDefaultDelay(100);
}

void GlWidget::Gif(const QString &path) {
  if (gif_timer_->isActive()) return;
  gif_path_ = path;
  gif_timer_->start(5000);
  frame_timer_->start(100);
}

void GlWidget::AddGifFrame() {
  QImage image = grabFramebuffer();
  gif_image_.addFrame(image);
}

void GlWidget::EndGifCapture() {
  frame_timer_->stop();
  gif_image_.save(gif_path_);
}

bool GlWidget::isGifCapturing() { return gif_timer_->isActive(); }

double GlWidget::GetLastScale() const noexcept { return last_scale_; }
void GlWidget::SetLastScale(const double new_value) noexcept {
  last_scale_ = new_value;
}

}  // namespace s21
