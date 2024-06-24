#include "model.h"

#include <array>
#include <cmath>
#include <vector>

namespace s21 {
void Model::MoveX(const double x) noexcept { world_matrix_[3] += x; }

void Model::MoveY(const double y) noexcept { world_matrix_[7] += y; }

void Model::MoveZ(const double z) noexcept { world_matrix_[11] += z; }

void Model::RotateX(const double angle) noexcept { object_.RotateX(angle); }

void Model::RotateY(const double angle) noexcept { object_.RotateY(angle); }

void Model::RotateZ(const double angle) noexcept { object_.RotateZ(angle); }

void Model::Scale(const double scale) noexcept { object_.Scale(scale); }

void Model::Parse(const std::string &filename) {
  object_ = parser_.Parse(filename);
}

Object &Model::Obj() noexcept { return object_; }

std::array<float, 16> &Model::ProjectionMatrix() { return projection_matrix_; }

void Model::SetPerspectiveProjection(const float fov, const float near,
                                     const float far) {
  projection_matrix_ = {};
  float fov_factor = tan(fov * M_PI / 360.0);

  projection_matrix_[0] = 1.0 / fov_factor;
  projection_matrix_[5] = 1.0 / fov_factor;
  projection_matrix_[10] = -(far + near) / (far - near);
  projection_matrix_[11] = -2 * (far * near) / (far - near);
  projection_matrix_[14] = -1;
}

void Model::SetOrthographicProjection(const float near, const float far) {
  projection_matrix_ = {};
  projection_matrix_[0] = 1;
  projection_matrix_[5] = 1;
  projection_matrix_[10] = -2 / (far - near);
  projection_matrix_[11] = -(far + near) / (far - near);
  projection_matrix_[15] = 1;
}

std::array<float, 16> &Model::WorldMatrix() { return world_matrix_; }

void Model::Normalize() noexcept {
  // x_min, x_max, y_min, y_max, z_min, z_max
  float dimensions[6] = {0};

  for (size_t i = 0; i < object_.Vertices().size(); ++i) {
    int low = (i % 3) * 2 + 0;  // indexes for current vertex coordinate
    int high = (i % 3) * 2 + 1;

    if (object_[i] < dimensions[low]) dimensions[low] = object_[i];
    if (object_[i] > dimensions[high]) dimensions[high] = object_[i];
  }

  float size_x = dimensions[1] - dimensions[0];
  float size_y = dimensions[3] - dimensions[2];
  float size_z = dimensions[5] - dimensions[4];

  world_matrix_ = {};
  world_matrix_[0] = 1;
  world_matrix_[5] = 1;
  world_matrix_[10] = 1;
  world_matrix_[15] = 1;

  object_.MoveX(-(dimensions[0] + dimensions[1]) / 2.0);
  object_.MoveY(-(dimensions[2] + dimensions[3]) / 2.0);
  object_.MoveZ(-(dimensions[4] + dimensions[5]) / 2.0);

  float max_size = size_x > size_y ? size_x : size_y;
  max_size = max_size > size_z ? max_size : size_z;
  Scale(2.0 / max_size);
}

}  // namespace s21
