#ifndef VIEWER_V2_0_VIEW_VIEW_H_
#define VIEWER_V2_0_VIEW_VIEW_H_

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPoint>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QWidget>

#include "../controller/controller.h"
#include "gl.h"

namespace s21 {
class View : public QWidget {
  Q_OBJECT
 public:
  View(Controller &controller);
  ~View();

 public slots:
  // load file
  void OnLoadFileButtonClicked();
  void OnScreenshotButtonClicked();
  void OnGifButtonClicked();

  // colors
  void OnChangeBGColorButtonClicked();
  void OnChangeEdgeColorButtonClicked();
  void OnChangeVerticesColorButtonClicked();

  // move transformation
  void MoveXSpinBoxValueChanged();
  void MoveYSpinBoxValueChanged();
  void MoveZSpinBoxValueChanged();

  // rotate transformation
  void RotateXSpinBoxValueChanged();
  void RotateYSpinBoxValueChanged();
  void RotateZSpinBoxValueChanged();

  // scale transformation
  void ScaleSpinBoxValueChanged();

  // update spin box value
  void ChangeMoveSpinBox(QPoint diff_position);
  void ChangeRotateSpinBox(QPoint diff_position);
  void ChangeScaleSpinBox(double new_scale);

  // set thickness
  void EdgeThicknessSpinBoxValueChanged();
  void VertexThicknessSpinBoxValueChanged();

  // set type
  void ChangeEdgeType(const QString &text);
  void ChangeVertexType(const QString &text);
  void ChangeProjectionType(const QString &text);

 private:
  // model layout
  void InitModelLabels();
  void InitModelButtons();
  void ConnectModelLayoutSignals();
  void ModelPlaceItems();
  void InitModelLayout();

  // controls layout
  void InitControlLabels();
  void InitControlSpinBoxes();
  void ConnectControlsLayoutStgnals();
  void ControlPlaceItems();
  void InitControlLayout();

  // personalization layout
  void InitPersonalizationLabels();
  void InitPersonalizationDoubleSpinBoxes();
  void InitPersonalizationButtons();
  void InitPersonalizationComboBoxes();
  void ConnectPersonalizationLayoutSignals();
  void PersonalizationPlaceItems();
  void InitPersonalizationLayout();

  // main widget
  void InitMainWidgetLabels();
  void InitGlWidget();
  void MainWidgetPlaceItems();
  void InitMainWidget();

  // after load file
  void UpdateObjectName(const std::string new_filename) noexcept;
  void UpdateObjectVertexCount() noexcept;
  void UpdateObjectEdgesCount() noexcept;

  // reset spin boxes after load file
  void ResetMoveSpinBoxes() noexcept;
  void ResetRotateSpinBoxes() noexcept;
  void ResetScaleSpinBoxes() noexcept;
  void ResetSpinBoxes() noexcept;

  // update spin boxes
  void ChangeValueHelper(QDoubleSpinBox *spinBox, double &spinBoxValue,
                         std::function<void(double)> controllerFunction);
  void ChangeSpinBoxValuesHelperMouseEvent(QDoubleSpinBox *spinBox1,
                                           QDoubleSpinBox *spinBox2,
                                           double &value1, double &value2,
                                           QPoint diff_position);
  // update spin boxes utility
  void CheckSpinBoxNewValue(QDoubleSpinBox *spinBox, double &new_value);

  // settings
  void SaveSettings();
  void LoadSettings();

 private:
  Controller &controller_;

  std::string object_name_ = "MacOS sucks";

  // ======== model layout ======== //
  // labels
  QLabel *filename_label_;
  QLabel *vertex_count_label_;
  QLabel *vertex_count_label_1;
  QLabel *edges_count_label_;
  QLabel *edges_count_label_1;

  // push buttons
  QPushButton *file_load_button_;
  QPushButton *screenshot_button_;
  QPushButton *gif_button_;

  // grid layouts
  QGridLayout *model_layout_;
  // ============================== //

  // ======= control layout ======= //
  // labels
  QLabel *x_label_;
  QLabel *y_label_;
  QLabel *z_label_;
  QLabel *move_label_;
  QLabel *rotate_label_;
  QLabel *scale_label_;

  // double spin boxes
  QDoubleSpinBox *move_x_spin_box_;
  QDoubleSpinBox *move_y_spin_box_;
  QDoubleSpinBox *move_z_spin_box_;
  QDoubleSpinBox *rotate_x_spin_box_;
  QDoubleSpinBox *rotate_y_spin_box_;
  QDoubleSpinBox *rotate_z_spin_box_;
  QDoubleSpinBox *scale_spin_box_;

  // grid layouts
  QGridLayout *controls_layout_;
  // ============================== //

  // === personalization layout === //

  // labels
  QLabel *projection_label_;
  QLabel *edge_type_label_;
  QLabel *vertex_type_label_;
  QLabel *edge_thickness_label_;
  QLabel *vertex_thickness_label_;
  QLabel *colors_label_;

  // double spin boxes
  QDoubleSpinBox *edge_thickness_spin_box_;
  QDoubleSpinBox *vertex_thickness_spin_box_;

  // push buttons
  QPushButton *background_color_button_;
  QPushButton *edges_color_button_;
  QPushButton *vertices_color_button_;

  // combo boxes
  QComboBox *projection_type_combo_box_;
  QComboBox *edge_type_combo_box_;
  QComboBox *vertex_type_combo_box_;

  // grid layouts
  QGridLayout *colors_layout_;
  QGridLayout *personalization_layout_;
  // ============================== //

  // ======== main layout ======== //
  // labels
  QLabel *model_label_;
  QLabel *controls_label_;
  QLabel *personalization_label_;

  // glwidget
  GlWidget *glwidget_;

  // grid layouts
  QGridLayout *main_layout_;
  // ============================== //

  // sipnbox values
  double move_x_spin_box_value_ = 0;
  double move_y_spin_box_value_ = 0;
  double move_z_spin_box_value_ = 0;

  double rotate_x_spin_box_value_ = 0;
  double rotate_y_spin_box_value_ = 0;
  double rotate_z_spin_box_value_ = 0;

  double scale_spin_box_value_ = 50;

  // settings
  QSettings settings_ = QSettings("CringeSoft", "Viewer2");
};
}  // namespace s21

#endif  // VIEWER_V2_0_VIEW_VIEW_H_
