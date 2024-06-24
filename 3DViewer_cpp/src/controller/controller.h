#ifndef VIEWER_V2_0_CONTROLLER_CONTROLLER_H_
#define VIEWER_V2_0_CONTROLLER_CONTROLLER_H_

#include <QMatrix4x4>
#include <string>
#include <vector>

#include "../viewer/model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model &model) : model_(model) {}

  void MoveX(const double x) noexcept;
  void MoveY(const double y) noexcept;
  void MoveZ(const double z) noexcept;

  void RotateX(const double angle) noexcept;
  void RotateY(const double angle) noexcept;
  void RotateZ(const double angle) noexcept;

  void Scale(const double scale) noexcept;

  void Parse(const std::string &filename);
  void NormalizeObject() noexcept;

  unsigned int GetCountOfVertices() const noexcept;
  unsigned int GetCountOfEdges() const noexcept;

  std::vector<float> &Vertices() noexcept;
  std::vector<unsigned int> &Indexes() noexcept;

  QMatrix4x4 ProjectionMatrix();
  void SetPerspectiveProjection(const float fov, const float near,
                                const float far);
  void SetOrthographicProjection(const float near, const float far);

  QMatrix4x4 WorldMatrix();

 private:
  Model &model_;
};
}  // namespace s21

#endif  // VIEWER_V2_0_CONTROLLER_CONTROLLER_H_
