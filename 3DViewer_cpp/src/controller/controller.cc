#include "controller.h"

#include <QMatrix4x4>
#include <string>
#include <vector>

namespace s21 {
void Controller::MoveX(const double x) noexcept { model_.MoveX(x); }
void Controller::MoveY(const double y) noexcept { model_.MoveY(y); }
void Controller::MoveZ(const double z) noexcept { model_.MoveZ(z); }

void Controller::RotateX(const double angle) noexcept { model_.RotateX(angle); }
void Controller::RotateY(const double angle) noexcept { model_.RotateY(angle); }
void Controller::RotateZ(const double angle) noexcept { model_.RotateZ(angle); }

void Controller::Scale(const double scale) noexcept { model_.Scale(scale); }

void Controller::Parse(const std::string &filename) { model_.Parse(filename); }

unsigned int Controller::GetCountOfVertices() const noexcept {
  return model_.Obj().Vertices().size();
}

unsigned int Controller::GetCountOfEdges() const noexcept {
  return model_.Obj().Indexes().size();
}

std::vector<float> &Controller::Vertices() noexcept {
  return model_.Obj().Vertices();
}
std::vector<unsigned int> &Controller::Indexes() noexcept {
  return model_.Obj().Indexes();
}

QMatrix4x4 Controller::ProjectionMatrix() {
  float *values = model_.ProjectionMatrix().data();
  return QMatrix4x4(values[0], values[1], values[2], values[3], values[4],
                    values[5], values[6], values[7], values[8], values[9],
                    values[10], values[11], values[12], values[13], values[14],
                    values[15]);
}

void Controller::SetPerspectiveProjection(const float fov, const float near,
                                          const float far) {
  model_.SetPerspectiveProjection(fov, near, far);
}
void Controller::SetOrthographicProjection(const float near, const float far) {
  model_.SetOrthographicProjection(near, far);
}

QMatrix4x4 Controller::WorldMatrix() {
  float *values = model_.WorldMatrix().data();
  return QMatrix4x4(values[0], values[1], values[2], values[3], values[4],
                    values[5], values[6], values[7], values[8], values[9],
                    values[10], values[11], values[12], values[13], values[14],
                    values[15]);
}

void Controller::NormalizeObject() noexcept { model_.Normalize(); }

}  // namespace s21
