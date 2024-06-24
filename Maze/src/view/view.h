#ifndef MAZE_VIEW_VIEW_H_
#define MAZE_VIEW_VIEW_H_

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

#include "../controller/controller.h"
#include "maze_widget/maze_widget.h"

namespace s21 {

class View : public QWidget {
  Q_OBJECT

 public:
  View(Controller &controller);
  // ~View();

 public slots:
  void OnLoadFileButtonClicked();
  void OnSaveButtonClicked();
  void OnGenerateButtonClicked();
  void OnFindPathButtonClicked();

  void OnSpinBoxValueChanged();
  void ChangeSpinBoxValue(const int new_start_x_position,
                          const int new_start_y_position,
                          const int new_end_x_position,
                          const int new_end_y_position);

 private:
  void InitMainWidget();
  void MainWidgetPlaseItems();
  void InitMazeWidget();
  void InitPushButtons();
  void InitSpinBoxes();
  void InitLabels();
  void ConnectSignals();

  void ChangeMazeSize();

 private:
  // ========== main layout ========== //

  // widgets
  MazeWidget *widget_maze_;

  // spin boxes
  QSpinBox *spin_box_start_point_x_;
  QSpinBox *spin_box_start_point_y_;
  QSpinBox *spin_box_end_point_x_;
  QSpinBox *spin_box_end_point_y_;
  QSpinBox *spin_box_maze_length_;
  QSpinBox *spin_box_maze_width_;

  // push buttons
  QPushButton *button_generate_maze_;
  QPushButton *button_find_path_;
  QPushButton *button_load_file_;
  QPushButton *button_save_in_file_;

  // labels
  QLabel *label_maze_length_;
  QLabel *label_maze_width_;
  QLabel *label_start_point_;
  QLabel *label_end_point_;
  QLabel *label_x_;
  QLabel *label_y_;

  // grid layouts
  QGridLayout *main_layout_;

  // graphics scene
  // QGraphicsView *graphics_view_;
  // QGraphicsScene *graphics_scene_;

  // painter
  // QPainter *painter;
  // ================================= //

  Controller &controller_;
};

}  // namespace s21

#endif  // MAZE_VIEW_VIEW_H_
