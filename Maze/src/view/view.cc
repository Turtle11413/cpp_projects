#include "view.h"

#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>
#include <iostream>

namespace s21 {

View::View(Controller& controller) : QWidget(nullptr), controller_(controller) {
  InitMainWidget();
}

void View::InitMainWidget() {
  InitMazeWidget();
  InitPushButtons();
  InitSpinBoxes();
  InitLabels();

  MainWidgetPlaseItems();

  ConnectSignals();

  setLayout(main_layout_);
}

void View::InitMazeWidget() {
  widget_maze_ = new MazeWidget(this, controller_);
  widget_maze_->setMinimumSize(500, 500);
  widget_maze_->setMaximumSize(500, 500);
  // widget_maze_->setStyleSheet("background-color:white");
  // widget_maze_->setStyleSheet("color:red");
}

void View::InitSpinBoxes() {
  spin_box_maze_length_ = new QSpinBox();
  spin_box_maze_length_->setRange(0, 50);
  spin_box_maze_length_->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);

  spin_box_maze_width_ = new QSpinBox();
  spin_box_maze_width_->setRange(0, 50);
  spin_box_maze_width_->setSizePolicy(QSizePolicy::Expanding,
                                      QSizePolicy::Expanding);

  spin_box_start_point_x_ = new QSpinBox();
  spin_box_start_point_x_->setRange(0, spin_box_maze_length_->value());
  spin_box_start_point_x_->setSizePolicy(QSizePolicy::Expanding,
                                         QSizePolicy::Expanding);

  spin_box_start_point_y_ = new QSpinBox();
  spin_box_start_point_y_->setRange(0, spin_box_maze_width_->value());
  spin_box_start_point_y_->setSizePolicy(QSizePolicy::Expanding,
                                         QSizePolicy::Expanding);

  spin_box_end_point_x_ = new QSpinBox();
  spin_box_end_point_x_->setRange(0, spin_box_maze_length_->value());
  spin_box_end_point_x_->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);

  spin_box_end_point_y_ = new QSpinBox();
  spin_box_end_point_y_->setRange(0, spin_box_maze_width_->value());
  spin_box_end_point_y_->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
}

void View::InitPushButtons() {
  button_generate_maze_ = new QPushButton("Generate maze");
  button_generate_maze_->setSizePolicy(QSizePolicy::Expanding,
                                       QSizePolicy::Expanding);
  button_generate_maze_->setStyleSheet(
      "color: white; "
      "border-style: solid;"
      "border-style: solid;"
      "border-radius: 7;"
      "padding: 3px;"
      "padding-left: 5px;"
      "padding-right: 5px;"
      "border-color: #339;"
      "border-width: 1px;"
      "font:Bold;"
      "font-family:Georgia");

  button_find_path_ = new QPushButton("Find path");
  button_find_path_->setSizePolicy(QSizePolicy::Expanding,
                                   QSizePolicy::Expanding);
  button_find_path_->setStyleSheet(
      "color: white; "
      "border-style: solid;"
      "border-style: solid;"
      "border-radius: 7;"
      "padding: 3px;"
      "padding-left: 5px;"
      "padding-right: 5px;"
      "border-color: #339;"
      "border-width: 1px;"
      "font:Bold;"
      "font-family:Georgia");

  button_load_file_ = new QPushButton("Load file");
  button_load_file_->setSizePolicy(QSizePolicy::Expanding,
                                   QSizePolicy::Expanding);
  button_load_file_->setStyleSheet(
      "color: white; "
      "border-style: solid;"
      "border-style: solid;"
      "border-radius: 7;"
      "padding: 3px;"
      "padding-left: 5px;"
      "padding-right: 5px;"
      "border-color: #339;"
      "border-width: 1px;"
      "font:Bold;"
      "font-family:Georgia");

  button_save_in_file_ = new QPushButton("Save");
  button_save_in_file_->setSizePolicy(QSizePolicy::Expanding,
                                      QSizePolicy::Expanding);
  button_save_in_file_->setStyleSheet(
      "color: white; "
      "border-style: solid;"
      "border-style: solid;"
      "border-radius: 7;"
      "padding: 3px;"
      "padding-left: 5px;"
      "padding-right: 5px;"
      "border-color: #339;"
      "border-width: 1px;"
      "font:Bold;"
      "font-family:Georgia");
}

void View::InitLabels() {
  label_maze_length_ = new QLabel("Maze length");
  label_maze_length_->setAlignment(Qt::AlignHCenter);
  label_maze_length_->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);

  label_maze_width_ = new QLabel("Maze width");
  label_maze_width_->setAlignment(Qt::AlignHCenter);
  label_maze_width_->setSizePolicy(QSizePolicy::Expanding,
                                   QSizePolicy::Expanding);

  label_start_point_ = new QLabel("Start point");
  label_start_point_->setAlignment(Qt::AlignHCenter);
  label_start_point_->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);

  label_end_point_ = new QLabel("End point");
  label_end_point_->setAlignment(Qt::AlignHCenter);
  label_end_point_->setSizePolicy(QSizePolicy::Expanding,
                                  QSizePolicy::Expanding);

  label_x_ = new QLabel("x");
  label_x_->setAlignment(Qt::AlignHCenter);
  label_x_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  label_y_ = new QLabel("y");
  label_y_->setAlignment(Qt::AlignHCenter);
  label_y_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void View::MainWidgetPlaseItems() {
  main_layout_ = new QGridLayout();
  main_layout_->addWidget(widget_maze_, 0, 0, 1, 6, Qt::AlignHCenter);

  main_layout_->addWidget(button_load_file_, 1, 0, 1, 1);
  main_layout_->addWidget(button_save_in_file_, 1, 1, 1, 1);

  main_layout_->addWidget(label_maze_length_, 2, 0, 1, 1);
  main_layout_->addWidget(spin_box_maze_length_, 2, 1, 1, 1);

  main_layout_->addWidget(label_maze_width_, 3, 0, 1, 1);
  main_layout_->addWidget(spin_box_maze_width_, 3, 1, 1, 1);

  main_layout_->addWidget(button_generate_maze_, 4, 0, 1, 2);

  main_layout_->addWidget(label_start_point_, 1, 3, 1, 1);
  main_layout_->addWidget(spin_box_start_point_x_, 2, 3, 1, 1);
  main_layout_->addWidget(spin_box_start_point_y_, 3, 3, 1, 1);

  main_layout_->addWidget(label_end_point_, 1, 5, 1, 1);
  main_layout_->addWidget(label_x_, 2, 4, 1, 1);
  main_layout_->addWidget(spin_box_end_point_x_, 2, 5, 1, 1);
  main_layout_->addWidget(label_y_, 3, 4, 1, 1);
  main_layout_->addWidget(spin_box_end_point_y_, 3, 5, 1, 1);

  main_layout_->addWidget(button_find_path_, 4, 3, 1, 3);
}

void View::ConnectSignals() {
  QObject::connect(button_load_file_, &QPushButton::clicked, this,
                   &View::OnLoadFileButtonClicked);
  QObject::connect(button_save_in_file_, &QPushButton::clicked, this,
                   &View::OnSaveButtonClicked);
  QObject::connect(button_find_path_, &QPushButton::clicked, this,
                   &View::OnFindPathButtonClicked);
  QObject::connect(button_generate_maze_, &QPushButton::clicked, this,
                   &View::OnGenerateButtonClicked);
  QObject::connect(spin_box_start_point_x_,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   &View::OnSpinBoxValueChanged);
  QObject::connect(spin_box_start_point_y_,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   &View::OnSpinBoxValueChanged);
  QObject::connect(spin_box_end_point_x_,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   &View::OnSpinBoxValueChanged);
  QObject::connect(spin_box_end_point_y_,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   &View::OnSpinBoxValueChanged);
  QObject::connect(spin_box_maze_length_,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   [=](int value) {
                     spin_box_start_point_x_->setRange(0, value - 1);
                     spin_box_end_point_x_->setRange(0, value - 1);
                   });
  QObject::connect(spin_box_maze_width_,
                   QOverload<int>::of(&QSpinBox::valueChanged), this,
                   [=](int value) {
                     spin_box_start_point_y_->setRange(0, value - 1);
                     spin_box_end_point_y_->setRange(0, value - 1);
                   });
  QObject::connect(widget_maze_, &MazeWidget::ChangePosition, this,
                   &View::ChangeSpinBoxValue);
}

void View::OnLoadFileButtonClicked() {
  std::cout << "load file\n";
  QString filename = QFileDialog::getOpenFileName(this);
  try {
    if (!filename.isEmpty()) {
      controller_.LoadFile(filename.toStdString());
      ChangeMazeSize();
      widget_maze_->repaint();
    }
  } catch (std::invalid_argument& e) {
    QMessageBox::warning(this, "Incorrect input", e.what());
  }
}

void View::ChangeMazeSize() {
  std::pair<int, int> size = controller_.GetMazeSize();
  spin_box_maze_length_->setValue(size.first);
  spin_box_maze_width_->setValue(size.second);
}

void View::OnSaveButtonClicked() {
  std::cout << "\t\tSave file\n";
  // save file (qt)
}
void View::OnFindPathButtonClicked() {
  std::cout << "\t\tfind path called\n";
  // controller_.FildPath();
}

void View::OnGenerateButtonClicked() {
  std::cout << "\t\tGenerate maze called\n";

  // controller_.GenerateMaze();

  widget_maze_->repaint();
}

void View::OnSpinBoxValueChanged() {
  widget_maze_->ChangeStartPointPosition(
      spin_box_start_point_x_->value(), spin_box_start_point_y_->value(),
      spin_box_end_point_x_->value(), spin_box_end_point_y_->value());
}

void View::ChangeSpinBoxValue(const int new_start_x_position,
                              const int new_start_y_position,
                              const int new_end_x_position,
                              const int new_end_y_position) {
  spin_box_start_point_x_->setValue(new_start_x_position);
  spin_box_start_point_y_->setValue(new_start_y_position);
  spin_box_end_point_x_->setValue(new_end_x_position);
  spin_box_end_point_y_->setValue(new_end_y_position);
}

}  // namespace s21
