//
// Created by austsxk on 2021/8/4.
//

// 自定义正方体

#include <array>
#include <vtkPolyData.h>
#include <vtkArrayData.h>
#include <vtkTriangle.h>
#include <vtkPolygon.h>
#include <vtkPoints.h>
#include <vtkNew.h>
#include <vtkPolyDataWriter.h>
#include <vtkCellData.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkPlaneSource.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkPolyDataMapper.h>
#include <vtkIntArray.h>

int main() {
    // 定义顶点
    std::array<std::array<double, 3>, 8> pointsList;
    pointsList[0] = {0, 0, 0};
    pointsList[1] = {1, 0, 0};
    pointsList[2] = {1, 1, 0};
    pointsList[3] = {0, 1, 0};
    pointsList[4] = {0, 0, 1};
    pointsList[5] = {1, 0, 1};
    pointsList[6] = {1, 1, 1};
    pointsList[7] = {0, 1, 1};

    // 定义单元数组 6个面所组成的id数组
    std::array<std::array<vtkIdType , 4>, 6> cellsList;
    cellsList[0] = {0, 1, 2, 3};
    cellsList[1] = {4, 5, 6, 7};
    cellsList[2] = {0, 1, 5, 4};
    cellsList[3] = {3, 2, 6, 7};
    cellsList[4] = {1, 2, 6, 5};
    cellsList[5] = {0, 3, 7, 4};

    // 创建多边形数据集 用来存储几何数据和拓扑数据
    vtkNew<vtkPolyData> polyDataCube;

    // 添加点集
    vtkNew<vtkPoints> points;
    vtkNew<vtkFloatArray> scalars;
    // 给标量添加属性名称
    scalars->SetName("myScalars");
    scalars->SetNumberOfComponents(1);
    scalars->SetNumberOfTuples(pointsList.size());
    for (int i=0; i<pointsList.size(); i++) {
        points->InsertNextPoint(pointsList[i].data());
        scalars->SetTuple1(i, i);
    };

    // 添加单元
    vtkNew<vtkCellArray> cells;
    for (int i=0; i<cellsList.size(); i++) {
        cells->InsertNextCell(4, cellsList[i].data());
    };

    // 给点数据添加属性
    polyDataCube->SetPoints(points);
    polyDataCube->SetPolys(cells);
    polyDataCube->GetPointData()->SetScalars(scalars);

    // 写入vtk文件中
    vtkNew<vtkPolyDataWriter> writer;
    writer->SetFileName("cube.vtk");
    writer->SetInputData(polyDataCube);
    writer->Write();
}