#include "maze.h"

#include <stdexcept>

namespace s21 {

Maze::Maze()
    : rows_(0),
      cols_(0),
      walls_matrix_(0, std::vector<std::pair<bool, bool>>(0)) {}

Maze::Maze(const int rows, const int cols)
    : rows_(rows),
      cols_(cols),
      walls_matrix_(rows,
                    std::vector<std::pair<bool, bool>>(cols, {false, false})) {}

std::pair<bool&, bool&> Maze::operator()(const int i, const int j) {
  if (i < rows_ && j < cols_) {
    return {walls_matrix_[i][j].first, walls_matrix_[i][j].second};
  } else {
    throw std::out_of_range("Index out of range");
  }
}

std::pair<int, int> Maze::GetSize() const noexcept {
  return std::make_pair(rows_, cols_);
}

void Maze::SetSize(const int rows, const int cols) noexcept {
  rows_ = rows;
  cols_ = cols;
}

void Maze::ResizeWallsMatrix() {
  walls_matrix_.resize(
      rows_, std::vector<std::pair<bool, bool>>(cols_, {false, false}));
}

void Maze::ResizeWallsMatrix(const int rows, const int cols) {
  SetSize(rows, cols);
  ResizeWallsMatrix();
}

}  // namespace s21
