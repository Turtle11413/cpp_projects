#include "maze_widget.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <iostream>

namespace s21 {

void MazeWidget::paintEvent(QPaintEvent*) {
  // std::cout << "\t\tpaintEvent called\n";
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2));

  painter.fillRect(rect(), QColor(255, 255, 255));

  DrawBoarders(&painter);
  DrawMaze(&painter);

  DrawStartPoint();
  DrawEndPoint();

  if (start_point_x_ == end_point_x_ && start_point_y_ == end_point_y_) {
    DrawCombinedPoints();
  }
}

void MazeWidget::DrawBoarders(QPainter* painter) {
  painter->drawLine(left_top_x_, left_top_y_, left_top_x_ + maze_size_,
                    left_top_y_);
  painter->drawLine(left_top_x_, left_top_y_, left_top_x_,
                    left_top_y_ + maze_size_);
  painter->drawLine(left_top_x_, left_top_y_ + maze_size_,
                    left_top_x_ + maze_size_, left_top_y_ + maze_size_);
  painter->drawLine(left_top_x_ + maze_size_, left_top_y_,
                    left_top_x_ + maze_size_, left_top_y_ + maze_size_);
}

void MazeWidget::DrawMaze(QPainter* painter) {
  cell_width_ = maze_size_ / controller_.GetMazeSize().first;
  cell_height_ = maze_size_ / controller_.GetMazeSize().second;

  for (int i = 0, end_i = controller_.GetMazeSize().first; i < end_i; ++i) {
    for (int j = 0, end_j = controller_.GetMazeSize().second; j < end_j; ++j) {
      if (controller_.GetMaze()(i, j).first) {
        DrawRightWall(painter, i, j);
      }

      if (controller_.GetMaze()(i, j).second) {
        DrawDownWall(painter, i, j);
      }
    }
  }
}

void MazeWidget::DrawRightWall(QPainter* painter, const int i, const int j) {
  double x = (j + 1) * cell_width_;
  double y1 = i * cell_height_;
  double y2 = (i + 1) * cell_height_;
  painter->drawLine(std::round(left_top_x_ + x), std::round(left_top_y_ + y1),
                    std::round(left_top_x_ + x), std::round(left_top_y_ + y2));
}

void MazeWidget::DrawDownWall(QPainter* painter, const int i, const int j) {
  double x1 = j * cell_width_;
  double x2 = (j + 1) * cell_width_;
  double y = (i + 1) * cell_height_;
  painter->drawLine(std::round(left_top_x_ + x1), std::round(left_top_y_ + y),
                    std::round(left_top_x_ + x2), std::round(left_top_y_ + y));
}

void MazeWidget::DrawStartPoint() {
  // std::cout << "start point drawing\n";

  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2));

  painter.setBrush(Qt::red);
  painter.drawEllipse(start_point_x_ * cell_width_ + cell_width_ / 2,
                      start_point_y_ * cell_height_ + cell_height_ / 2, 10, 10);
}

void MazeWidget::DrawEndPoint() {
  // std::cout << "end point drawing\n";
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2));

  painter.setBrush(Qt::blue);
  painter.drawEllipse(end_point_x_ * cell_width_ + cell_width_ / 2,
                      end_point_y_ * cell_height_ + cell_height_ / 2, 10, 10);
}

void MazeWidget::ChangeStartPointPosition(const int new_start_x_position,
                                          const int new_start_y_position,
                                          const int new_end_x_position,
                                          const int new_end_y_position) {
  start_point_x_ = new_start_x_position;
  start_point_y_ = new_start_y_position;

  end_point_x_ = new_end_x_position;
  end_point_y_ = new_end_y_position;

  this->repaint();
}

void MazeWidget::DrawCombinedPoints() {
  QPainter painter(this);
  painter.setPen(QPen(Qt::black, 2));

  int combined_x = (start_point_x_ + end_point_x_) / 2;
  int combined_y = (start_point_y_ + end_point_y_) / 2;

  QColor startColor = Qt::red;
  QColor endColor = Qt::blue;

  double startColorRatio = 0.5;
  double endColorRatio = 1.0 - startColorRatio;

  QColor blendedColor = QColor(
      startColor.red() * startColorRatio + endColor.red() * endColorRatio,
      startColor.green() * startColorRatio + endColor.green() * endColorRatio,
      startColor.blue() * startColorRatio + endColor.blue() * endColorRatio);

  painter.setBrush(blendedColor);
  painter.drawEllipse(combined_x * cell_width_ + cell_width_ / 2,
                      combined_y * cell_height_ + cell_height_ / 2, 10, 10);
}

void MazeWidget::mousePressEvent(QMouseEvent* event) {
  QPoint new_point = event->pos();
  if (event->buttons() & Qt::LeftButton) {
    start_point_x_ = (new_point.x() - start_point_x_) / cell_width_;
    start_point_y_ = (new_point.y() - start_point_y_) / cell_height_;
  } else if (event->buttons() & Qt::RightButton) {
    end_point_x_ = (new_point.x() - end_point_x_) / cell_width_;
    end_point_y_ = (new_point.y() - end_point_y_) / cell_height_;
  }

  emit ChangePosition(start_point_x_, start_point_y_, end_point_x_,
                      end_point_y_);

  repaint();
}

}  // namespace s21
