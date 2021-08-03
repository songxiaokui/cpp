#!/bin/bash

# 使用sudo ./vtk_auto_install.sh 安装vtk

export DEBIAN_FRONTEND=noninteractive

sed -i 's/archive.ubuntu.com/mirrors.163.com/g' /etc/apt/sources.list
sed -i 's/security.ubuntu.com/mirrors.163.com/g' /etc/apt/sources.list
apt-get update

echo "install base dependence"
apt-get install gcc g++ cmake wget wget unzip  -y
echo "mesa dependence llvm"
echo "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic main" >> /etc/apt/sources.list
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key| sudo apt-key add -
apt-get install clang-7 lldb-7 lld-7 -y
apt-get install libllvm6.0 llvm-6.0 llvm-6.0-dev llvm-6.0-runtime llvm-6.0-tools -y

# 下载OS MESA
# https://github.com/mmatl/travis_debs/raw/master/xenial/mesa_18.3.3-0.deb
cd dependence || true
dpkg -i mesa_18.3.3-0.deb || true
apt install -f

# 安装openGL相关
sudo apt-get install build-essential libgl1-mesa-dev
sudo apt-get install libglew-dev libsdl2-dev libsdl2-image-dev libglm-dev libfreetype6-dev
sudo apt-get install libglfw3-dev libglfw3
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglu1-mesa-dev
sudo apt-get install freeglut3-dev

# 下载VTK-8.9
sudo mkdir -p /opt/thirdpart/vtk
unzip VTK-8.90.zip
cd VTK-8.90  || true

mkdir build_linux
cd build_linux || true
cmake -DBUILD_SHARED_LIBS:BOOL=FALSE \
      -DVTK_USE_X:BOOL=FALSE \
      -DOSMESA_INCLUDE_DIR:PATH=/usr/local/include \
			-DOSMESA_LIBRARY=/usr/local/lib/libOSMesa.so.8 \
      -DVTK_OPENGL_HAS_OSMESA:BOOL=TRUE \
      -DVTK_DEFAULT_RENDER_WINDOW_OFFSCREEN:BOOL=TRUE \
      -DCMAKE_INSTALL_PREFIX=/opt/thirdpart/vtk \
      -DVTK_FORBID_DOWNLOADS:BOOL=TRUE \
      -DVTK_MODULE_ENABLE_VTK_hdf5:STRING="NO" \
      -DBUILD_TYPE=Release ..
sudo cmake --build .  --target install

echo "VTK-8.9 INSTALL SUCCESS"

