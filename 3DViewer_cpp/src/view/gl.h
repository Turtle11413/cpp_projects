#ifndef VIEWER_V2_0_VIEW_GL_H_
#define VIEWER_V2_0_VIEW_GL_H_

#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QSize>
#include <QTimer>

#include "../controller/controller.h"
#include "../qtgifimage/src/gifimage/qgifimage.h"

namespace s21 {

enum class VertexType {
  kNone,
  kSquare,
  kCircle,
};

enum class EdgeType {
  kSolid,
  kDashed,
};

enum class ProjectionType {
  kCentral,
  kParallel,
};

class GlWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  GlWidget(Controller &controller, QWidget *parent = nullptr);
  ~GlWidget();

  void LoadNewObject();
  void SetBackgroundColor(const QColor color);
  void SetEdgeColor(const QColor color);
  void SetVertexColor(const QColor color);

  void SetVertexSize(const float size);
  void SetEdgeSize(const float size);

  void SetVertexType(const VertexType type);
  void SetEdgeType(const EdgeType type);

  void SetProjectionType(const ProjectionType type);

  void Screenshot(const QString &path);
  void Gif(const QString &path);
  bool isGifCapturing();

  double GetLastScale() const noexcept;
  void SetLastScale(const double new_value) noexcept;

 protected:
  virtual void initializeGL() override;
  virtual void paintGL() override;

  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

 signals:
  void ChangeTextMove(const QPoint diff_position);
  void ChangeTextRotate(const QPoint diff_position);
  void ChangeTextScale(const double new_scale);

 private:
  void Cleanup();

  void InitShaders();
  void AllocateShaders();
  void CompileShaders();
  void BuildShaders();

  QOpenGLShaderProgram *BuildLineShader();
  QOpenGLShaderProgram *BuildThickLineShader();
  QOpenGLShaderProgram *BuildSquarePointShader();
  QOpenGLShaderProgram *BuildCirclePointShader();

  void DeleteShaders();
  void DeleteLineShaders();
  void DeletePointShaders();

  void DrawEdges();
  void DrawPoints();

  void InitGif();
  void AddGifFrame();
  void EndGifCapture();

  Controller &controller_;

  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer vbo_, ibo_;

  QOpenGLShader *transform_ = 0;

  QOpenGLShader *line_fragment_ = 0, *point_fragment_ = 0;

  QOpenGLShader *line_geometry_ = 0;
  QOpenGLShader *point_square_geometry_ = 0, *point_circle_geometry_ = 0;

  QOpenGLShaderProgram *line_ = 0, *line_thick_ = 0;
  QOpenGLShaderProgram *point_square_ = 0, *point_circle_ = 0;

  QPoint mouse_last_position_;
  double last_scale_ = 1;

  QColor background_color_ = QColor(0, 0, 0);
  QColor edge_color_ = QColor(255, 255, 255);
  QColor vertex_color_ = QColor(255, 0, 0);

  float point_size_ = 1.0, line_size_ = 1.0;
  VertexType vertex_type_ = VertexType::kNone;
  float fov_ = 90.0, near_ = 0.0, far_ = 10.0;
  float dash_threshold_ = 1.0;

  QTimer *gif_timer_ = 0, *frame_timer_ = 0;
  QString gif_path_;
  QGifImage gif_image_ = QGifImage(QSize(640, 480));
};

}  // namespace s21

#endif  // VIEWER_V2_0_VIEW_GL_H_
