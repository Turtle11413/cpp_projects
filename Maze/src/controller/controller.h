#ifndef MAZE_CONTROLLER_CONTROLLER_H_
#define MAZE_CONTROLLER_CONTROLLER_H_

#include "../model/maze/maze.h"
#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model& model) : model_(model) {}

  void LoadFile(const std::string& filemane);

  Maze& GetMaze();
  std::pair<int, int> GetMazeSize();

 private:
  Model& model_;
};
}  // namespace s21

#endif  // MAZE_CONTROLLER_CONTROLLER_H_
