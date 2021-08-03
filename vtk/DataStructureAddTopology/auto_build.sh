rm -rf build
mkdir build
cd build

cmake -DBUILD_SHARED_LIBS:BOOL=FALSE \
      -DVTK_DIR:PATH=${THIRD_PART_DIR}/vtk/lib/cmake/vtk-8.2/ \
      -DCMAKE_BUILD_TYPE=Release ..

cmake --build . --config Release
cd ..