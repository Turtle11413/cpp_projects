#ifndef VIEWER_V2_0_VIEWER_MODEL_H_
#define VIEWER_V2_0_VIEWER_MODEL_H_

#include <array>
#include <string>

#include "object.h"
#include "parser.h"

namespace s21 {

class Model {
 public:
  Object &Obj() noexcept;

  void MoveX(const double x) noexcept;
  void MoveY(const double y) noexcept;
  void MoveZ(const double z) noexcept;

  void RotateX(const double angle) noexcept;
  void RotateY(const double angle) noexcept;
  void RotateZ(const double angle) noexcept;

  void Scale(const double scale) noexcept;

  void Parse(const std::string &filename);
  void Normalize() noexcept;

  void SetPerspectiveProjection(const float fov, const float near,
                                const float far);
  void SetOrthographicProjection(const float near, const float far);

  std::array<float, 16> &ProjectionMatrix();
  std::array<float, 16> &WorldMatrix();

 private:
  Object object_;
  Parser parser_;
  std::array<float, 16> projection_matrix_;
  std::array<float, 16> world_matrix_;
};
}  // namespace s21

#endif  // VIEWER_V2_0_VIEWER_MODEL_H_
