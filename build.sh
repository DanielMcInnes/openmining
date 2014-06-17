#!/bin/sh

sudo apt-get install build-essential perl python git "^libxcb.*" libx11-xcb-dev libglu1-mesa-dev libxrender-dev flex bison gperf libicu-dev libxslt-dev ruby libasound2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libpq5 libpq-dev libboost-serialization1.48

sudo mkdir /opt/openmining 
sudo chmod -R a+rw /opt/openmining

cd /opt
git clone https://github.com/DanielMcInnes/openmining /opt

# build qt5
cd /opt/openmining/thirdparty/qt5/src
./init-repository --no-webkit
cd /opt/openmining/thirdparty/qt5/build
../src/configure -opensource -confirm-license
make
sudo make install
# for some reason qmake gets built but not installed. Do it manually:
sudo ln -s /opt/openmining/thirdparty/qt5/build/qtbase/bin/qmake /usr/bin/qmake  

# build qt3d
cd /opt/openmining/thirdparty/qt5/qt3d
qmake
make
sudo make install

# build qwtplot3d
cd /opt/openmining/thirdparty/qwtplot3d
qmake
make 
sudo make install

# build openmining
cd /opt/openmining
qmake
make
