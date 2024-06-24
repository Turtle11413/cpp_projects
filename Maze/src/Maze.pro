QT+=core gui
greaterThan(QT_MAJOR_VERSION, 4): QT+=widgets

CONFIG+=c++17

SOURCES+=                               \
				view/view.cc                    \
				view/maze_widget/maze_widget.cc \
				controller/controller.cc        \
				model/model.cc                  \
				model/maze/maze.cc              \
				main.cc

HEADERS+=                              \
				view/view.h                    \
				view/maze_widget/maze_widget.h \
				controller/controller.h        \
				model/maze/maze.h              \
				model/model.h

DESTDIR     = build/
MOC_DIR		  = build/moc
OBJECTS_DIR = build/obj


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS+=target
