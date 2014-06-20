TEMPLATE = app
TARGET = openmining
QT += sql  	# dhm - needed for postgres interface
CONFIG += c++11
CONFIG += exceptions # dhm - without this, exceptions are disabled. We need exceptions enabled to use boost::serialization.
INCLUDEPATH += /usr/local/Qt-5.3.0/include/
INCLUDEPATH += /usr/local/Qt-5.3.0/include/Qt3D/
INCLUDEPATH += /usr/local/Qt-5.3.0/include/QtWidgets/
INCLUDEPATH += thirdparty/qwtplot3d/include/


SOURCES = \
    Cube.cpp \
    Database.cpp \
    Point3D.cpp \
    Points3D.cpp \
    main.cpp \
    modelview.cpp \
    simpleplot.cpp \
    utils/contains_key.cpp \
    utils/copy_mapped_value.cpp \
    utils/get_mapped_value.cpp \
    utils/find_or_exit.cpp \
    utils/usage.cpp \
    utils/utils.cpp \
    utils/csl_2_vec.cpp \

HEADERS = \
    Cube.h \
    Database.h \
    Point3D.h \ 
    Points3D.h \
    Points3DSqlQuery.h \
    Points3DGrid.h \
    modelview.h \
    mytypes.h \
    simpleplot.h \
    utils/between.h \
    utils/check_argv.h \
    utils/contains.h \
    utils/contains_key.h \
    utils/copy_mapped_value.h \
    utils/get_mapped_value.h \
    utils/Exit.h \
    utils/find_or_exit.h \
    utils/find_or_return_default.h \
    utils/load.h \
    utils/percent.h \
    utils/same_size.h \
    utils/save.h \
    utils/update_progress.h \
    utils/usage.h \
    utils/utils.h \
    utils/csl_2_vec.h \

QMAKE_CXXFLAGS += -std=c++0x

QMAKE_LFLAGS += -Wl,--rpath=thirdparty/qwtplot3d/lib # dhm - this is needed to make the executable know where to find .so files. Adding it to 'LIBS' isn't enough. See http://developer.nokia.c

# put the path to shared libraries here
LIBS += -Lthirdparty/qwtplot3d/lib -lqwtplot3d 
LIBS += -Lthirdparty/qt3d/lib -lQt53D 
LIBS += -L/usr/local/Qt-5.3.0/lib/ -lQt5OpenGL
LIBS += -lboost_serialization
LIBS +=	-lGLU  					# this is required by qwtplot3d
