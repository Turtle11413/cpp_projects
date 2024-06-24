#include "model.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
void Model::LoadFile(const std::string& filename) {
  std::ifstream file_stream(filename);

  if (!file_stream.is_open()) {
    throw std::invalid_argument("Incorrect filename");
  }

  ReadMazeSize(file_stream);

  maze_.ResizeWallsMatrix();

  ReadMazeWalls(file_stream, WallMode::kRight);
  ReadMazeWalls(file_stream, WallMode::kDown);

  PrintMazeWalls();

  file_stream.close();
}

void Model::ReadMazeSize(std::ifstream& file_stream) {
  std::string cur_line;
  std::getline(file_stream, cur_line);

  std::istringstream iss(cur_line);

  int rows = 0, cols = 0;

  if (!(iss >> rows >> cols)) {
    file_stream.close();
    throw std::invalid_argument("Incorrect maze size");
  }

  if (rows <= 0 || cols <= 0) {
    file_stream.close();
    throw std::invalid_argument("Incorrect maze size. It must be more than 0");
  }

  maze_.SetSize(rows, cols);
}

void Model::ReadMazeWalls(std::ifstream& file_stream, WallMode mode) {
  std::string cur_line;

  while (std::getline(file_stream, cur_line) &&
         (cur_line.empty() ||
          cur_line.find_first_not_of(' ') == std::string::npos)) {
  }

  for (int i = 0; i < maze_.GetSize().first; ++i) {
    std::istringstream row(cur_line);
    for (int j = 0; j < maze_.GetSize().second; ++j) {
      int tmp_value;
      if (!(row >> tmp_value) || (tmp_value != 0 && tmp_value != 1)) {
        file_stream.close();
        throw std::invalid_argument("Invalid maze element. It must be 0 or 1");
      }
      switch (mode) {
        case WallMode::kRight:
          maze_(i, j).first = static_cast<bool>(tmp_value);
          break;
        case WallMode::kDown:
          maze_(i, j).second = static_cast<bool>(tmp_value);
          break;
        default:
          throw std::invalid_argument("Incorrect mode");
      }
    }
    std::getline(file_stream, cur_line);
  }
}

void Model::PrintMazeWalls() {
  for (int i = 0; i < maze_.GetSize().first; ++i) {
    for (int j = 0; j < maze_.GetSize().second; ++j) {
      std::cout << "[" << maze_(i, j).first << "," << maze_(i, j).second
                << "] ";
    }
    std::cout << std::endl;
  }
}

}  // namespace s21
