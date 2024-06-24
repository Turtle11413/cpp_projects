#include "object.h"

#include <cmath>

namespace s21 {
void Object::MoveX(const double x) noexcept {
  for (unsigned int i = 0; i < GetVerticesCount(); i += 3) {
    vertices_[i] += x;
  }
}

void Object::MoveY(const double y) noexcept {
  for (unsigned int i = 1; i < GetVerticesCount(); i += 3) {
    vertices_[i] += y;
  }
}

void Object::MoveZ(const double z) noexcept {
  for (unsigned int i = 2; i < GetVerticesCount(); i += 3) {
    vertices_[i] += z;
  }
}

double Object::ConvertToRad(const double angle) const noexcept {
  return acos(-1) * angle / 180;
}

void Object::RotateX(const double angle) noexcept {
  double sin_x = sin(ConvertToRad(angle));
  double cos_x = cos(ConvertToRad(angle));
  for (unsigned int i = 0; i < GetVerticesCount(); i += 3) {
    double y = vertices_[i + 1];
    double z = vertices_[i + 2];
    vertices_[i + 1] = cos_x * y - sin_x * z;
    vertices_[i + 2] = cos_x * z + sin_x * y;
  }
}

void Object::RotateY(const double angle) noexcept {
  double sin_y = sin(ConvertToRad(angle));
  double cos_y = cos(ConvertToRad(angle));
  for (unsigned int i = 0; i < GetVerticesCount(); i += 3) {
    double x = vertices_[i];
    double z = vertices_[i + 2];
    vertices_[i] = cos_y * x + sin_y * z;
    vertices_[i + 2] = cos_y * z - sin_y * x;
  }
}

void Object::RotateZ(const double angle) noexcept {
  double sin_z = sin(ConvertToRad(angle));
  double cos_z = cos(ConvertToRad(angle));
  for (unsigned int i = 0; i < GetVerticesCount(); i += 3) {
    double x = vertices_[i];
    double y = vertices_[i + 1];
    vertices_[i] = cos_z * x - sin_z * y;
    vertices_[i + 1] = cos_z * y + sin_z * x;
  }
}

void Object::Scale(const double scale) noexcept {
  for (unsigned int i = 0; i < GetVerticesCount(); ++i) {
    vertices_[i] *= scale;
  }
}

}  // namespace s21
