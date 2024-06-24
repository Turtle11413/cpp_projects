#ifndef VIEWER_V2_0_VIEWER_OBJECT_H_
#define VIEWER_V2_0_VIEWER_OBJECT_H_

#include <vector>

namespace s21 {

class Object {
 public:
  void MoveX(const double x) noexcept;
  void MoveY(const double y) noexcept;
  void MoveZ(const double z) noexcept;

  void RotateX(const double angle) noexcept;
  void RotateY(const double angle) noexcept;
  void RotateZ(const double angle) noexcept;

  void Scale(const double scale) noexcept;

  std::vector<float> &Vertices() noexcept { return vertices_; }
  std::vector<unsigned int> &Indexes() noexcept { return indexes_; }
  unsigned int GetVerticesCount() const noexcept { return vertices_.size(); }

  void SetVertices(const std::vector<float> &vertices) { vertices_ = vertices; }

  float &operator[](int i) noexcept { return vertices_[i]; }

 private:
  double ConvertToRad(const double angle) const noexcept;

  std::vector<unsigned int> indexes_;
  std::vector<float> vertices_;
};
}  // namespace s21

#endif  // VIEWER_V2_0_VIEWER_OBJECT_H_
