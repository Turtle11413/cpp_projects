#include "controller.h"

#include <iostream>

namespace s21 {
void Controller::LoadFile(const std::string& filename) {
  model_.LoadFile(filename);
}

std::pair<int, int> Controller::GetMazeSize() {
  return std::make_pair(model_.GetMaze().GetSize().first,
                        model_.GetMaze().GetSize().second);
}

Maze& Controller::GetMaze() { return model_.GetMaze(); }

}  // namespace s21
