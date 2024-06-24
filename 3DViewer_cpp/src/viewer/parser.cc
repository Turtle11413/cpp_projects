#include "parser.h"

#include <array>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

namespace s21 {

Object Parser::Parse(const std::string &filename) {
  std::ifstream file = TryOpening(filename);
  ParsedObject parsed;
  Object obj;
  std::string line;

  while (std::getline(file, line)) {
    ParseLine(line, parsed);
  }
  ConvertParsedObjectToObject(parsed, obj);

  return obj;
}

void Parser::ParseLine(const std::string &line, ParsedObject &obj) {
  if (strncmp(line.data(), "v ", 2) == 0) {
    ParseV(line.data() + 2, obj);
  } else if (strncmp(line.data(), "f ", 2) == 0) {
    ParseF(line.data() + 2, obj);
  }
}

void Parser::ParseV(const std::string::value_type *cur, ParsedObject &obj) {
  std::array<double, 3> vertices;
  for (int i = 0; i < 3; ++i) {
    size_t offset;
    vertices[i] = std::stod(cur, &offset);
    cur += offset;
  }
  obj.v.push_back(vertices);
}

void Parser::ParseF(const std::string::value_type *cur, ParsedObject &obj) {
  std::vector<int> points;
  std::stringstream stream(cur);
  std::string token;
  while (getline(stream, token, ' ')) {
    try {
      points.push_back(std::stoi(token));
    } catch (std::invalid_argument &e) {
      break;
    }
  }
  obj.f.push_back(points);
}

void Parser::ConvertParsedObjectToObject(const ParsedObject &parsed,
                                         Object &object) {
  for (size_t i = 0; i < parsed.v.size(); ++i) {
    for (size_t j = 0; j < parsed.v[i].size(); ++j) {
      object.Vertices().push_back(parsed.v[i][j]);
    }
  }

  for (size_t i = 0; i < parsed.f.size(); ++i) {
    for (size_t j = 0; j < parsed.f[i].size(); ++j) {
      if (j == 0) {
        object.Indexes().push_back(
            NormalizeIndex(parsed.f[i][parsed.f[i].size() - 1],
                           parsed.v.size()));  // last index
        object.Indexes().push_back(
            NormalizeIndex(parsed.f[i][0], parsed.v.size()));  // first index
      } else {
        object.Indexes().push_back(
            NormalizeIndex(parsed.f[i][j],
                           parsed.v.size()));  // this index
        object.Indexes().push_back(
            NormalizeIndex(parsed.f[i][j - 1],
                           parsed.v.size()));  // previous index
      }
    }
  }
}

size_t Parser::NormalizeIndex(const int index, const size_t vertex_list_size) {
  if ((index > 0 && index > (int)vertex_list_size) ||
      (index < 0 && -index > (int)vertex_list_size) || index == 0) {
    throw std::invalid_argument(std::to_string(index) +
                                std::string(" индекс массивтан читкә чыга"));
  }
  return index > 0 ? index - 1 : vertex_list_size + index;
}

std::ifstream Parser::TryOpening(const std::string &filename) {
  std::ifstream file;
  file.open(filename);
  if (!file.is_open()) {
    throw std::invalid_argument(std::string("Файл \'") + filename +
                                std::string("\' юк"));
  }
  return file;
}

}  // namespace s21
