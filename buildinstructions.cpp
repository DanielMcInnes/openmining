/*! \page pagebi Build Instructions
\section bisec000001 Setting up a build environment
\subsection siss000001 Ubuntu 12.04

- sudo apt-get install build-essential perl python git "^libxcb.*" libx11-xcb-dev libglu1-mesa-dev libxrender-dev flex bison gperf libicu-dev libxslt-dev ruby libasound2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libpq5 libpq-dev libboost-serialization1.48
- mkdir ~/openmining 

- cd ~
- git clone https://github.com/DanielMcInnes/openmining.git

- cd ~/openmining
- git submodule init
- git submodule update 
- sudo chmod -R a+rw /opt/qt5 /opt/openmining
- cd /opt/openmining/thirdparty/qt5/src
- ./init-repository
- cd /opt/qt5/build
- ../src/configure -opensource -confirm-license
- make
- sudo make install

# add the following to ~/.bashrc
if [ -d ~/openmining/thirdparty/qtbuild/qtbase/bin/ ]; then
    export PATH=$PATH:~/openmining/thirdparty/qtbuild/qtbase/bin
fi


- cd /opt/qt5/build/
- wget http://sourceforge.net/projects/qwtplot3d/files/qwtplot3d/0.2.7/qwtplot3d-0.2.7.tgz
- tar xvf qwtplot3d-0.2.7.tgz
- cd /opt/qt5/build/qwtplot3d
- qmake
- make




- git clone git://gitorious.org/qt/qt3d.git /opt/qt5

- cd qt3d; qmake; make; sudo make install

- download qwtplot3d-0.2.7.zip from http://qwtplot3d.sourceforge.net/web/navigation/download_frame.html into /opt/qt5
- /opt/qt5$ unzip ./qwtplot3d-0.2.7.zip

- cd /opt
- git clone https://github.com/DanielMcInnes/openmining /opt

- cd ../openmining
- qmake; make;



**/
