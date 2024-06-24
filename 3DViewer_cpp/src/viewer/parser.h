#ifndef VIEWER_V2_0_VIEWER_PARSER_H_
#define VIEWER_V2_0_VIEWER_PARSER_H_

#include <array>
#include <string>
#include <vector>

#include "object.h"

namespace s21 {

struct ParsedObject {
  std::vector<std::array<double, 3>> v;
  std::vector<std::vector<int>> f;
};

class Parser {
 public:
  Object Parse(const std::string &filename);

 private:
  void ParseLine(const std::string &line, ParsedObject &obj);
  void ParseV(const std::string::value_type *cur, ParsedObject &obj);
  void ParseF(const std::string::value_type *cur, ParsedObject &obj);
  void ConvertParsedObjectToObject(const ParsedObject &parsed, Object &object);
  size_t NormalizeIndex(const int index, const size_t vertex_list_size);

  std::ifstream TryOpening(const std::string &filename);
};

}  // namespace s21

#endif  // VIEWER_V2_0_VIEWER_PARSER_H_
