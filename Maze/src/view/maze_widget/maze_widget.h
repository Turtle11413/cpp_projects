#ifndef MAZE_VIEW_MAZE_WIDGET_MAZE_WIDGET_H_
#define MAZE_VIEW_MAZE_WIDGET_MAZE_WIDGET_H_

#include <QPainter>
#include <QWidget>

#include "../../controller/controller.h"

namespace s21 {

class MazeWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MazeWidget(QWidget *parent, Controller &controller)
      : QWidget(parent), controller_(controller) {}

 public slots:
  void ChangeStartPointPosition(const int new_start_x_position,
                                const int new_start_y_position,
                                const int new_end_x_position,
                                const int new_end_y_position);
 signals:
  void ChangePosition(int new_start_x_position, int new_start_y_position,
                      int new_end_x_position, int new_end_y_position);

 protected:
  virtual void paintEvent(QPaintEvent *) override;
  virtual void mousePressEvent(QMouseEvent *event) override;

 private:
  void DrawBoarders(QPainter *painter);
  void DrawRightWall(QPainter *painter, const int i, const int j);
  void DrawDownWall(QPainter *painter, const int i, const int j);
  void DrawMaze(QPainter *painter);

  void DrawStartPoint();
  void DrawEndPoint();
  void DrawCombinedPoints();

  double cell_width_ = 0;
  double cell_height_ = 0;

  const double left_top_x_ = 5;
  const double left_top_y_ = 5;
  const double maze_size_ = 490;

  int start_point_x_ = 0;
  int start_point_y_ = 0;
  int end_point_x_ = 0;
  int end_point_y_ = 0;

  Controller &controller_;
};
}  // namespace s21

#endif  // MAZE_VIEW_MAZE_WIDGET_MAZE_WIDGET_H_
