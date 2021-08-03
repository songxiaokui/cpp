#!/bin/bash

# vtk_auto_install_centos7.sh
# Centos7安装VTK脚本

echo "install cmake 3"
yum -y install wget
yum -y install gcc gcc-c++

wget https://github.com/Kitware/CMake/releases/download/v3.15.5/cmake-3.15.5.tar.gz
tar -zxf cmake-3.15.5.tar.gz
cd cmake-3.15.5 || true
./bootstrap --prefix=/usr --datadir=share/cmake --docdir=doc/cmake && make
sudo make install
cmake --version

echo "install osmesa"
yum install mesa-libOSMesa-devel -y
yum install libXt-devel -y
yum install mesa-libGL-devel  mesa-libGLU-devel -y
yum install glx-utils -y

echo "osmesa install path"
ldconfig -p | grep  libOSMesa.so.8

echo "osmesa h file path"
find / -name "osmesa.h"

sudo mkdir -p /opt/thirdpart/vtk
cd dependence || true
unzip VTK-8.90.zip
cd VTK-8.90  || true
mkdir build_linux
cd build_linux || true
cmake -DBUILD_SHARED_LIBS:BOOL=FALSE \
      -DVTK_USE_X:BOOL=FALSE \
      -DOSMESA_INCLUDE_DIR:PATH=/usr/include \
      -DOSMESA_LIBRARY=/lib64/libOSMesa.so.8 \
      -DVTK_OPENGL_HAS_OSMESA:BOOL=TRUE \
      -DVTK_DEFAULT_RENDER_WINDOW_OFFSCREEN:BOOL=TRUE \
      -DCMAKE_INSTALL_PREFIX=/opt/thirdpart/vtk \
      -DVTK_FORBID_DOWNLOADS:BOOL=TRUE \
      -DVTK_MODULE_ENABLE_VTK_hdf5:STRING="NO" \
      -DBUILD_TYPE=Release ..
sudo cmake --build .  --target install

echo "VTK install success!"
