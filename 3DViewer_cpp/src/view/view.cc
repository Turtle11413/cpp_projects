#include "view.h"

#include <QColor>
#include <QColorDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <string>

namespace s21 {
View::View(Controller& controller) : QWidget(nullptr), controller_(controller) {
  InitMainWidget();
  LoadSettings();
}

View::~View() { SaveSettings(); }

// ============ MODEL LAYOUT ============ //
void View::InitModelLabels() {
  filename_label_ = new QLabel();
  filename_label_->setText(QString::fromStdString(object_name_));

  vertex_count_label_ = new QLabel();
  vertex_count_label_->setText(tr("vertex count"));

  vertex_count_label_1 = new QLabel();
  vertex_count_label_1->setText(tr("0"));

  edges_count_label_ = new QLabel();
  edges_count_label_->setText(tr("edges count"));

  edges_count_label_1 = new QLabel();
  edges_count_label_1->setText(tr("0"));
}

void View::InitModelButtons() {
  file_load_button_ = new QPushButton();
  file_load_button_->setText(tr("LOAD FILE"));

  screenshot_button_ = new QPushButton();
  screenshot_button_->setText(tr("SCREENSHOT"));

  gif_button_ = new QPushButton();
  gif_button_->setText(tr("GIF"));

  ConnectModelLayoutSignals();
}

void View::ConnectModelLayoutSignals() {
  QObject::connect(file_load_button_, &QPushButton::clicked, this,
                   &View::OnLoadFileButtonClicked);
  QObject::connect(screenshot_button_, &QPushButton::clicked, this,
                   &View::OnScreenshotButtonClicked);
  QObject::connect(gif_button_, &QPushButton::clicked, this,
                   &View::OnGifButtonClicked);
}

void View::ResetMoveSpinBoxes() noexcept {
  move_x_spin_box_value_ = 0;
  move_y_spin_box_value_ = 0;
  move_z_spin_box_value_ = 0;

  move_x_spin_box_->setValue(move_x_spin_box_value_);
  move_y_spin_box_->setValue(move_y_spin_box_value_);
  move_z_spin_box_->setValue(move_z_spin_box_value_);
}

void View::ResetRotateSpinBoxes() noexcept {
  rotate_x_spin_box_value_ = 0;
  rotate_y_spin_box_value_ = 0;
  rotate_z_spin_box_value_ = 0;

  rotate_x_spin_box_->setValue(rotate_x_spin_box_value_);
  rotate_y_spin_box_->setValue(rotate_y_spin_box_value_);
  rotate_z_spin_box_->setValue(rotate_z_spin_box_value_);
}

void View::ResetScaleSpinBoxes() noexcept {
  scale_spin_box_value_ = 1;

  scale_spin_box_->setValue(scale_spin_box_value_);
}

void View::ResetSpinBoxes() noexcept {
  ResetMoveSpinBoxes();
  ResetRotateSpinBoxes();
  ResetScaleSpinBoxes();
}

void View::OnLoadFileButtonClicked() {
  QString filename = QFileDialog::getOpenFileName(this);
  try {
    controller_.Parse(filename.toStdString());
    controller_.NormalizeObject();
    glwidget_->LoadNewObject();
    UpdateObjectName(filename.toStdString());
    ResetSpinBoxes();
  } catch (std::invalid_argument& e) {
    QMessageBox::warning(this, "Incorrect input", e.what());
  }
}

void View::OnScreenshotButtonClicked() {
  QString path =
      QFileDialog::getSaveFileName(this, "Select screenshot location");
  glwidget_->Screenshot(path);
}

void View::OnGifButtonClicked() {
  if (glwidget_->isGifCapturing()) return;
  QString path = QFileDialog::getSaveFileName(this, "Select GIF location");
  glwidget_->Gif(path);
}

void View::UpdateObjectName(const std::string new_filename) noexcept {
  object_name_ = new_filename;
  auto slash_position = object_name_.rfind('/') + 1;
  object_name_.erase(object_name_.begin(),
                     object_name_.begin() + slash_position);

  filename_label_->setText(QString::fromStdString(object_name_));
  UpdateObjectVertexCount();
  UpdateObjectEdgesCount();
}

void View::UpdateObjectVertexCount() noexcept {
  vertex_count_label_1->setText(
      QString::number(controller_.Vertices().size() / 3));
}

void View::UpdateObjectEdgesCount() noexcept {
  edges_count_label_1->setText(
      QString::number(controller_.Indexes().size() / 4));
}

void View::ModelPlaceItems() {
  model_layout_ = new QGridLayout();
  model_layout_->addWidget(filename_label_, 0, 0);
  model_layout_->addWidget(vertex_count_label_, 0, 1);
  model_layout_->addWidget(vertex_count_label_1, 0, 2);
  model_layout_->addWidget(edges_count_label_, 1, 1);
  model_layout_->addWidget(edges_count_label_1, 1, 2);
  model_layout_->addWidget(file_load_button_, 1, 0);
  model_layout_->addWidget(screenshot_button_, 2, 0);
  model_layout_->addWidget(gif_button_, 3, 0);
}

void View::InitModelLayout() {
  InitModelLabels();
  InitModelButtons();
  ModelPlaceItems();
}

// ============ CONTROLS LAYOUT ============ //

void View::InitControlLabels() {
  x_label_ = new QLabel();
  x_label_->setText(tr("X"));

  y_label_ = new QLabel();
  y_label_->setText(tr("Y"));

  z_label_ = new QLabel();
  z_label_->setText(tr("Z"));

  move_label_ = new QLabel();
  move_label_->setText(tr("move"));

  rotate_label_ = new QLabel();
  rotate_label_->setText(tr("rotate"));

  scale_label_ = new QLabel();
  scale_label_->setText(tr("scale"));
}

void View::InitControlSpinBoxes() {
  move_x_spin_box_ = new QDoubleSpinBox();
  move_x_spin_box_->setDecimals(4);
  move_x_spin_box_->setSingleStep(0.0001);
  move_x_spin_box_->setRange(-5, 5);

  move_y_spin_box_ = new QDoubleSpinBox();
  move_y_spin_box_->setDecimals(4);
  move_y_spin_box_->setSingleStep(0.0001);
  move_y_spin_box_->setRange(-5, 5);

  move_z_spin_box_ = new QDoubleSpinBox();
  move_z_spin_box_->setDecimals(4);
  move_z_spin_box_->setSingleStep(0.0001);
  move_z_spin_box_->setRange(-5, 5);

  rotate_x_spin_box_ = new QDoubleSpinBox();
  rotate_x_spin_box_->setRange(-360, 360);

  rotate_y_spin_box_ = new QDoubleSpinBox();
  rotate_y_spin_box_->setRange(-360, 360);

  rotate_z_spin_box_ = new QDoubleSpinBox();
  rotate_z_spin_box_->setRange(-360, 360);

  scale_spin_box_ = new QDoubleSpinBox();
  scale_spin_box_->setDecimals(2);
  scale_spin_box_->setSingleStep(0.1);
  scale_spin_box_->setRange(0.1, 3);
  scale_spin_box_->setValue(1);

  ConnectControlsLayoutStgnals();
}

void View::ConnectControlsLayoutStgnals() {
  QObject::connect(move_x_spin_box_, &QDoubleSpinBox::valueChanged, this,
                   &View::MoveXSpinBoxValueChanged);
  QObject::connect(move_y_spin_box_, &QDoubleSpinBox::valueChanged, this,
                   &View::MoveYSpinBoxValueChanged);
  QObject::connect(move_z_spin_box_, &QDoubleSpinBox::valueChanged, this,
                   &View::MoveZSpinBoxValueChanged);

  QObject::connect(rotate_x_spin_box_, &QDoubleSpinBox::valueChanged, this,
                   &View::RotateXSpinBoxValueChanged);
  QObject::connect(rotate_y_spin_box_, &QDoubleSpinBox::valueChanged, this,
                   &View::RotateYSpinBoxValueChanged);
  QObject::connect(rotate_z_spin_box_, &QDoubleSpinBox::valueChanged, this,
                   &View::RotateZSpinBoxValueChanged);

  QObject::connect(scale_spin_box_, &QDoubleSpinBox::valueChanged, this,
                   &View::ScaleSpinBoxValueChanged);
  QObject::connect(glwidget_, &GlWidget::ChangeTextMove, this,
                   &View::ChangeMoveSpinBox);
  QObject::connect(glwidget_, &GlWidget::ChangeTextRotate, this,
                   &View::ChangeRotateSpinBox);
  QObject::connect(glwidget_, &GlWidget::ChangeTextScale, this,
                   &View::ChangeScaleSpinBox);
}

void View::ChangeSpinBoxValuesHelperMouseEvent(QDoubleSpinBox* spinBox1,
                                               QDoubleSpinBox* spinBox2,
                                               double& value1, double& value2,
                                               QPoint diff_position) {
  spinBox1->blockSignals(true);
  spinBox2->blockSignals(true);

  double new_value1 = value1;
  double new_value2 = value2;

  if (spinBox1 == move_x_spin_box_ && spinBox2 == move_y_spin_box_) {
    new_value1 -= diff_position.x() / 1000.0;
    new_value2 += diff_position.y() / 1000.0;
  } else if (spinBox1 == rotate_x_spin_box_ && spinBox2 == rotate_y_spin_box_) {
    new_value1 += diff_position.y();
    new_value2 += diff_position.x();
  }

  CheckSpinBoxNewValue(spinBox1, new_value1);
  CheckSpinBoxNewValue(spinBox2, new_value2);

  spinBox1->setValue(new_value1);
  spinBox2->setValue(new_value2);

  value1 = new_value1;
  value2 = new_value2;

  spinBox1->blockSignals(false);
  spinBox2->blockSignals(false);
}

void View::CheckSpinBoxNewValue(QDoubleSpinBox* spinBox, double& new_value) {
  if (spinBox == rotate_x_spin_box_ || spinBox == rotate_y_spin_box_ ||
      spinBox == rotate_z_spin_box_) {
    if (new_value >= 180) {
      new_value = -360 + new_value;
    } else if (new_value < -180) {
      new_value = 360 + new_value;
    }
  }
}

void View::ChangeMoveSpinBox(QPoint diff_position) {
  ChangeSpinBoxValuesHelperMouseEvent(move_x_spin_box_, move_y_spin_box_,
                                      move_x_spin_box_value_,
                                      move_y_spin_box_value_, diff_position);
}

void View::ChangeRotateSpinBox(QPoint diff_position) {
  ChangeSpinBoxValuesHelperMouseEvent(rotate_x_spin_box_, rotate_y_spin_box_,
                                      rotate_x_spin_box_value_,
                                      rotate_y_spin_box_value_, diff_position);
}

void View::ChangeScaleSpinBox(double new_scale) {
  scale_spin_box_->blockSignals(true);

  scale_spin_box_->setValue(new_scale);

  scale_spin_box_->blockSignals(false);
}

void View::ChangeValueHelper(QDoubleSpinBox* spinBox, double& spinBoxValue,
                             std::function<void(double)> controllerFunction) {
  spinBox->blockSignals(true);

  double new_value = spinBox->value();
  CheckSpinBoxNewValue(spinBox, new_value);

  double diff_value = spinBoxValue - new_value;
  controllerFunction(diff_value);

  spinBoxValue = new_value;
  spinBox->setValue(new_value);

  glwidget_->update();

  spinBox->blockSignals(false);
}

void View::MoveXSpinBoxValueChanged() {
  ChangeValueHelper(
      move_x_spin_box_, move_x_spin_box_value_,
      [this](double diff_value) { controller_.MoveX(-diff_value); });
}

void View::MoveYSpinBoxValueChanged() {
  ChangeValueHelper(
      move_y_spin_box_, move_y_spin_box_value_,
      [this](double diff_value) { controller_.MoveY(-diff_value); });
}

void View::MoveZSpinBoxValueChanged() {
  ChangeValueHelper(
      move_z_spin_box_, move_z_spin_box_value_,
      [this](double diff_value) { controller_.MoveZ(diff_value); });
}

void View::RotateXSpinBoxValueChanged() {
  ChangeValueHelper(
      rotate_x_spin_box_, rotate_x_spin_box_value_,
      [this](double diff_value) { controller_.RotateX(diff_value); });
}

void View::RotateYSpinBoxValueChanged() {
  ChangeValueHelper(
      rotate_y_spin_box_, rotate_y_spin_box_value_,
      [this](double diff_value) { controller_.RotateY(diff_value); });
}

void View::RotateZSpinBoxValueChanged() {
  ChangeValueHelper(
      rotate_z_spin_box_, rotate_z_spin_box_value_,
      [this](double diff_value) { controller_.RotateZ(diff_value); });
}

void View::ScaleSpinBoxValueChanged() {
  double new_value = scale_spin_box_->value();
  controller_.Scale(new_value / glwidget_->GetLastScale());
  glwidget_->SetLastScale(new_value);
  glwidget_->update();
}

void View::ControlPlaceItems() {
  controls_layout_ = new QGridLayout();

  controls_layout_->addWidget(move_label_, 0, 0, Qt::AlignHCenter);
  controls_layout_->addWidget(rotate_label_, 0, 2, Qt::AlignHCenter);

  controls_layout_->addWidget(move_x_spin_box_, 1, 0, Qt::AlignHCenter);
  controls_layout_->addWidget(x_label_, 1, 1, Qt::AlignHCenter);
  controls_layout_->addWidget(rotate_x_spin_box_, 1, 2, Qt::AlignHCenter);

  controls_layout_->addWidget(move_y_spin_box_, 2, 0, Qt::AlignHCenter);
  controls_layout_->addWidget(y_label_, 2, 1, Qt::AlignHCenter);
  controls_layout_->addWidget(rotate_y_spin_box_, 2, 2, Qt::AlignHCenter);

  controls_layout_->addWidget(move_z_spin_box_, 3, 0, Qt::AlignHCenter);
  controls_layout_->addWidget(z_label_, 3, 1, Qt::AlignHCenter);
  controls_layout_->addWidget(rotate_z_spin_box_, 3, 2, Qt::AlignHCenter);

  controls_layout_->addWidget(scale_label_, 4, 0, 1, 3, Qt::AlignHCenter);

  controls_layout_->addWidget(scale_spin_box_, 5, 0, 1, 3, Qt::AlignHCenter);
}

void View::InitControlLayout() {
  InitControlLabels();
  InitControlSpinBoxes();
  ControlPlaceItems();
}

// ============ PERSONALIZATION LAYOUT ============ //

void View::InitPersonalizationLabels() {
  projection_label_ = new QLabel();
  projection_label_->setText(tr("Projection"));

  edge_type_label_ = new QLabel();
  edge_type_label_->setText(tr("Edge type"));

  vertex_type_label_ = new QLabel();
  vertex_type_label_->setText(tr("Vertex type"));

  edge_thickness_label_ = new QLabel();
  edge_thickness_label_->setText(tr("Edge thickness"));

  vertex_thickness_label_ = new QLabel();
  vertex_thickness_label_->setText(tr("Vertex thickness"));

  colors_label_ = new QLabel();
  colors_label_->setText(tr("COLORS"));
}

void View::InitPersonalizationDoubleSpinBoxes() {
  edge_thickness_spin_box_ = new QDoubleSpinBox();
  edge_thickness_spin_box_->setRange(0, 10);

  vertex_thickness_spin_box_ = new QDoubleSpinBox();
  vertex_thickness_spin_box_->setRange(0, 10);
}

void View::InitPersonalizationButtons() {
  background_color_button_ = new QPushButton();
  background_color_button_->setText(tr("Background"));

  edges_color_button_ = new QPushButton();
  edges_color_button_->setText(tr("Edges"));

  vertices_color_button_ = new QPushButton();
  vertices_color_button_->setText(tr("Vertices"));
}

void View::InitPersonalizationComboBoxes() {
  projection_type_combo_box_ = new QComboBox();
  projection_type_combo_box_->addItem("Central");
  projection_type_combo_box_->addItem("Parallel");

  edge_type_combo_box_ = new QComboBox();
  edge_type_combo_box_->addItem("Solid");
  edge_type_combo_box_->addItem("Dashed");

  vertex_type_combo_box_ = new QComboBox();
  vertex_type_combo_box_->addItem("None");
  vertex_type_combo_box_->addItem("Circle");
  vertex_type_combo_box_->addItem("Square");
}

void View::ConnectPersonalizationLayoutSignals() {
  QObject::connect(background_color_button_, &QPushButton::clicked, this,
                   &View::OnChangeBGColorButtonClicked);
  QObject::connect(edges_color_button_, &QPushButton::clicked, this,
                   &View::OnChangeEdgeColorButtonClicked);
  QObject::connect(vertices_color_button_, &QPushButton::clicked, this,
                   &View::OnChangeVerticesColorButtonClicked);
  QObject::connect(edge_thickness_spin_box_, &QDoubleSpinBox::valueChanged,
                   this, &View::EdgeThicknessSpinBoxValueChanged);
  QObject::connect(vertex_thickness_spin_box_, &QDoubleSpinBox::valueChanged,
                   this, &View::VertexThicknessSpinBoxValueChanged);
  QObject::connect(edge_type_combo_box_, &QComboBox::currentTextChanged, this,
                   &View::ChangeEdgeType);
  QObject::connect(vertex_type_combo_box_, &QComboBox::currentTextChanged, this,
                   &View::ChangeVertexType);
  QObject::connect(projection_type_combo_box_, &QComboBox::currentTextChanged,
                   this, &View::ChangeProjectionType);
}

void View::OnChangeBGColorButtonClicked() {
  QColor color = QColorDialog::getColor(Qt::black, this);
  if (color.isValid()) {
    glwidget_->SetBackgroundColor(color);
    settings_.setValue("background_color", color.name(QColor::HexArgb));
  }
}

void View::OnChangeEdgeColorButtonClicked() {
  QColor color = QColorDialog::getColor(Qt::black, this);
  if (color.isValid()) {
    glwidget_->SetEdgeColor(color);
    settings_.setValue("edge_color", color.name(QColor::HexArgb));
  }
}

void View::OnChangeVerticesColorButtonClicked() {
  QColor color = QColorDialog::getColor(Qt::black, this);
  if (color.isValid()) {
    glwidget_->SetVertexColor(color);
    settings_.setValue("vertex_color", color.name(QColor::HexArgb));
  }
}

void View::EdgeThicknessSpinBoxValueChanged() {
  glwidget_->SetEdgeSize(edge_thickness_spin_box_->value());
}

void View::VertexThicknessSpinBoxValueChanged() {
  glwidget_->SetVertexSize(vertex_thickness_spin_box_->value());
}

void View::ChangeEdgeType(const QString& text) {
  if (text == "Solid") {
    glwidget_->SetEdgeType(EdgeType::kSolid);
  } else {
    glwidget_->SetEdgeType(EdgeType::kDashed);
  }
}

void View::ChangeVertexType(const QString& text) {
  if (text == "Square") {
    glwidget_->SetVertexType(VertexType::kSquare);
  } else if (text == "Circle") {
    glwidget_->SetVertexType(VertexType::kCircle);
  } else {
    glwidget_->SetVertexType(VertexType::kNone);
  }
}

void View::ChangeProjectionType(const QString& text) {
  if (text == "Parallel") {
    glwidget_->SetProjectionType(ProjectionType::kParallel);
  } else {
    glwidget_->SetProjectionType(ProjectionType::kCentral);
  }
}

void View::PersonalizationPlaceItems() {
  colors_layout_ = new QGridLayout();
  colors_layout_->addWidget(colors_label_, 0, 1, 1, 2);
  colors_layout_->addWidget(background_color_button_, 1, 0);
  colors_layout_->addWidget(edges_color_button_, 1, 1);
  colors_layout_->addWidget(vertices_color_button_, 1, 2);

  personalization_layout_ = new QGridLayout();
  personalization_layout_->addWidget(projection_label_, 0, 0);
  personalization_layout_->addWidget(projection_type_combo_box_, 0, 1);

  personalization_layout_->addWidget(edge_type_label_, 1, 0);
  personalization_layout_->addWidget(edge_type_combo_box_, 1, 1);
  personalization_layout_->addWidget(edge_thickness_label_, 1, 2);
  personalization_layout_->addWidget(edge_thickness_spin_box_, 1, 3);

  personalization_layout_->addWidget(vertex_type_label_, 2, 0);
  personalization_layout_->addWidget(vertex_type_combo_box_, 2, 1);
  personalization_layout_->addWidget(vertex_thickness_label_, 2, 2);
  personalization_layout_->addWidget(vertex_thickness_spin_box_, 2, 3);

  personalization_layout_->addLayout(colors_layout_, 3, 0, 2, 4,
                                     Qt::AlignCenter);
}

void View::InitPersonalizationLayout() {
  InitPersonalizationLabels();
  InitPersonalizationDoubleSpinBoxes();
  InitPersonalizationButtons();
  InitPersonalizationComboBoxes();
  PersonalizationPlaceItems();
  ConnectPersonalizationLayoutSignals();
}

// ============== MAIN WIDGET ============== //

void View::InitMainWidgetLabels() {
  model_label_ = new QLabel();
  model_label_->setText(tr("MODEL"));

  controls_label_ = new QLabel();
  controls_label_->setText(tr("CONTROLS"));

  personalization_label_ = new QLabel();
  personalization_label_->setText(tr("PERSONALIZATION"));
}

void View::InitGlWidget() {
  glwidget_ = new GlWidget(controller_);
  glwidget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void View::MainWidgetPlaceItems() {
  main_layout_ = new QGridLayout();
  main_layout_->addWidget(glwidget_, 0, 0, 1, 3);
  main_layout_->addWidget(model_label_, 1, 0, Qt::AlignCenter);
  main_layout_->addWidget(controls_label_, 1, 1, Qt::AlignCenter);
  main_layout_->addWidget(personalization_label_, 1, 2, Qt::AlignCenter);
  main_layout_->addLayout(model_layout_, 2, 0);
  main_layout_->addLayout(controls_layout_, 2, 1);
  main_layout_->addLayout(personalization_layout_, 2, 2);
}

void View::InitMainWidget() {
  InitGlWidget();
  InitMainWidgetLabels();

  InitModelLayout();
  InitControlLayout();
  InitPersonalizationLayout();

  MainWidgetPlaceItems();

  setLayout(main_layout_);
}

void View::SaveSettings() {
  settings_.setValue("projection", projection_type_combo_box_->currentIndex());
  settings_.setValue("edge_type", edge_type_combo_box_->currentIndex());
  settings_.setValue("vertex_type", vertex_type_combo_box_->currentIndex());
  settings_.setValue("edge_thickness", edge_thickness_spin_box_->value());
  settings_.setValue("vertex_thickness", vertex_thickness_spin_box_->value());
}

void View::LoadSettings() {
  projection_type_combo_box_->setCurrentIndex(
      settings_.value("projection", 0).toInt());
  edge_type_combo_box_->setCurrentIndex(
      settings_.value("edge_type", 0).toInt());
  vertex_type_combo_box_->setCurrentIndex(
      settings_.value("vertex_type", 0).toInt());
  edge_thickness_spin_box_->setValue(
      settings_.value("edge_thickness", 1.0).toDouble());
  vertex_thickness_spin_box_->setValue(
      settings_.value("vertex_thickness", 1.0).toDouble());
  glwidget_->SetBackgroundColor(
      settings_.value("background_color", QColor(0, 0, 0, 255)).toString());
  glwidget_->SetEdgeColor(
      settings_.value("edge_color", QColor(255, 255, 255, 255)).toString());
  glwidget_->SetVertexColor(
      settings_.value("vertex_color", QColor(255, 0, 0, 255)).toString());
}

}  // namespace s21
