#include <QApplication>
#include <QSurfaceFormat>

#include "controller/controller.h"
#include "view/view.h"
#include "viewer/model.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // MACOS FUCKING SUCKS LOL
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  s21::Model model;
  s21::Controller controller(model);

  s21::View view(controller);
  view.show();

  return app.exec();
}
