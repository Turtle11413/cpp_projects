#ifndef MAZE_MODEL_MODEL_H_
#define MAZE_MODEL_MODEL_H_

#include <stdexcept>
#include <string>
#include <vector>

#include "maze/maze.h"

namespace s21 {

class Model {
 public:
  Model() = default;
  ~Model() = default;
  void LoadFile(const std::string& filename);

  Maze& GetMaze() { return maze_; }

 private:
  // ============== Parser ==============
  enum class WallMode { kRight, kDown };

  void ReadMazeSize(std::ifstream& file_stream);
  void ReadMazeWalls(std::ifstream& file_stream, WallMode mode);
  void PrintMazeWalls();
  // ============== ====== ==============

  // ============= Generate =============
  void GenerateMaze();
  // ============= ======== =============

  Maze maze_;
};
}  // namespace s21

#endif  // MAZE_MODEL_MODEL_H_
