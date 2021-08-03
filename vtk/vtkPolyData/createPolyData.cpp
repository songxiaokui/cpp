//
// Created by austsxk on 2021/8/3.
//

#include "createPolyData.h"

void CreatePolyData() {
    // 1. 创建点
    vtkNew<vtkPoints> points;
    points->InsertNextPoint(0,0,0);
    points->InsertNextPoint(1,0,0);
    points->InsertNextPoint(1,1,0);
    points->InsertNextPoint(0,1,0);
    points->InsertNextPoint(2,0,0);

    // 2. 创建四边形
    vtkNew<vtkPolygon> polygon;
    // Return the list of point ids defining the cell. 获取多边形对象点id列表并设置点个数为4个
    polygon->GetPointIds()->SetNumberOfIds(4);
    // 使用点编号为1， 2， 3， 4定义这四边形的4个点
    polygon->GetPointIds()->SetId(0, 0);
    polygon->GetPointIds()->SetId(1, 1);
    polygon->GetPointIds()->SetId(2, 2);
    polygon->GetPointIds()->SetId(3, 3);

    // 3. 创建三角形
    vtkNew<vtkTriangle> triangle;
    triangle->GetPointIds()->SetNumberOfIds(3);
    triangle->GetPointIds()->SetId(0, 1);
    triangle->GetPointIds()->SetId(1, 4);
    triangle->GetPointIds()->SetId(2, 2);

    // 4. 添加至单元数组中
    vtkNew<vtkCellArray> cellArray;
    cellArray->InsertNextCell(polygon);
    cellArray->InsertNextCell(triangle);

    // 5. 创建polyData数据结构，添加几何数据和拓扑数据
    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(points);
    polyData->SetPolys(cellArray);

    // 定义颜色
    // red green blue
    unsigned char red[3] = {255, 0, 0};
    unsigned char green[3] = {0, 255, 0};
    unsigned char blue[3] = {0, 0, 255};

    // 点着色
    vtkNew<vtkUnsignedCharArray> pointsColors;
    pointsColors->SetNumberOfComponents(3);
    pointsColors->InsertNextTuple3(255, 0, 0);
    pointsColors->InsertNextTuple3(0, 255, 0);
    pointsColors->InsertNextTuple3(255, 0, 255);
    pointsColors->InsertNextTuple3(255, 0, 0);
    pointsColors->InsertNextTuple3(0, 255, 0);

    polyData->GetPointData()->SetScalars(pointsColors);

    // 单元着色
    vtkNew<vtkUnsignedCharArray> cellColors;
    cellColors->SetNumberOfComponents(3);
    cellColors->InsertNextTuple3(255, 0, 0);
    cellColors->InsertNextTuple3(0, 255, 0);
    polyData->GetPointData()->SetScalars(cellColors);
    // 6. 写入文件中
    vtkNew<vtkPolyDataWriter> writer;
    writer->SetInputData(polyData);
    writer->SetFileName("createPolyData.vtk");
    writer->Write();
}