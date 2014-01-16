TEMPLATE = app
TARGET = openmining
QT += 3d
QT += sql 	# dhm - needed for postgres interface
CONFIG += c++11
CONFIG += exceptions # dhm - without this, exceptions are disabled. We need exceptions enabled to use boost::serialization.
INCLUDEPATH += /usr/include/qwtplot3d-qt4

SOURCES = \
    cube.cpp \
    database.cpp \
    elevation.cpp \
    location.cpp \
    main.cpp \
    modelview.cpp \
    simpleplot.cpp \
    utils.cpp \

HEADERS = \
    cube.h \
    database.h \
    elevation.h \
    find_or_return_default.h \
    location.h \
    modelview.h \
    mytypes.h \
    simpleplot.h \
    utils.h \

RESOURCES = model.qrc

# put the path to shared libraries here
QMAKE_LFLAGS += -Wl,--rpath=/home/dmcinnes/qt5/qwtplot3d/lib # dhm - this is needed to make the executable know where to find .so files. Adding it to 'LIBS' isn't enough. See http://developer.nokia.com/Community/Wiki/How_to_deploy_and_link_a_shared_library_on_Harmattan

LIBS += -L/home/dmcinnes/qt5/qwtplot3d/lib -lqwtplot3d 
LIBS += -lboost_serialization
LIBS +=	-lGLU  					# this is required by qwtplot3d

