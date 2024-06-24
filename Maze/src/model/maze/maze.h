#ifndef MAZE_MODEL_MAZE_MAZE_H_
#define MAZE_MODEL_MAZE_MAZE_H_

#include <stdexcept>
#include <vector>

namespace s21 {

class Maze {
 public:
  Maze();
  Maze(const int rows, const int cols);
  ~Maze() = default;

  std::pair<bool&, bool&> operator()(const int i, const int j);

  std::pair<int, int> GetSize() const noexcept;
  void SetSize(const int rows, const int cols) noexcept;

  void ResizeWallsMatrix();
  void ResizeWallsMatrix(const int rows, const int cols);

 private:
  int rows_;
  int cols_;
  std::vector<std::vector<std::pair<bool, bool>>> walls_matrix_{};
};

}  // namespace s21

#endif  // MAZE_MODEL_MAZE_MAZE_H_
