QT+=core gui openglwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT+=widgets

CONFIG+=c++17

RESOURCES=shaders/shaders.qrc

SOURCES+=\
	viewer/model.cc\
	viewer/object.cc\
	viewer/parser.cc\
	controller/controller.cc\
        view/gl.cc\
				view/view.cc\
	main.cc

HEADERS+=\
	viewer/model.h\
	viewer/object.h\
	viewer/parser.h\
	controller/controller.h\
        view/gl.h\
				view/view.h

include(qtgifimage/src/gifimage/qtgifimage.pri)

DESTDIR=build/
MOC_DIR		  = build/moc
OBJECTS_DIR = build/obj

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS+=target
