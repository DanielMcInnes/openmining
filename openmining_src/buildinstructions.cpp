/*! \page pagebi Build Instructions
\section bisec000001 Setting up a build environment
\subsection siss000001 Ubuntu 12.04

- sudo apt-get install build-essential perl python git"^libxcb.*" libx11-xcb-dev libglu1-mesa-dev libxrender-dev flex bison gperf libicu-dev libxslt-dev ruby libasound2-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
- sudo mkdir /opt/qt5 /opt/openmining 
- sudo chmod -r a+rwx /opt/qt5 /opt/openmining
- git clone git://gitorious.org/qt/qt5.git /opt

# for some reason qmake gets built but not installed. Do it manually:
- sudo ln -s /opt/qt5/qtbase/bin/qmake /usr/bin/qmake  

- git clone git://gitorious.org/qt/qt3d.git /opt/qt5
- cd qt3d; qmake; make; sudo make install

- download qwtplot3d-0.2.7.zip from http://qwtplot3d.sourceforge.net/web/navigation/download_frame.html into /opt/qt5
- /opt/qt5$ unzip ./qwtplot3d-0.2.7.zip

- cd /opt
- git clone https://github.com/DanielMcInnes/openmining /opt

- cd ../openmining
- qmake; make;



**/