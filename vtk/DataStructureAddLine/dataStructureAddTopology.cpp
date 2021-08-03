//
// Created by austsxk on 2021/8/2.
//
#include <vtkPoints.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataWriter.h>
#include <vtkLine.h>
using namespace std;
// 将零维拓扑图改为一维拓扑图
int main() {
    // 创建三个坐标点
    vtkNew<vtkPoints> points;
    points->InsertNextPoint(1, 0, 0);
    points->InsertNextPoint(0, 1, 0);
    points->InsertNextPoint(0, 0, 0);

    // 创建一个多边形数据集
    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(points);

    // 创建3条线,每两个点连一条线 SetId第一个参数是线段的端点id 第二个参数为点索引编号
    vtkNew<vtkLine> line0;
    line0->GetPointIds()->SetId(0, 0);
    line0->GetPointIds()->SetId(1, 1);

    vtkNew<vtkLine> line1;
    line1->GetPointIds()->SetId(0, 1);
    line1->GetPointIds()->SetId(1, 2);

    vtkNew<vtkLine> line2;
    line2->GetPointIds()->SetId(0, 2);
    line2->GetPointIds()->SetId(1, 0);

    // 创建单元数组，存储单元数据，即上面的三个线段
    vtkNew<vtkCellArray> lineArray;
    lineArray->InsertNextCell(line0);
    lineArray->InsertNextCell(line1);
    lineArray->InsertNextCell(line2);

    polyData->SetLines(lineArray);

    vtkNew<vtkPolyDataWriter> writer;
    writer->SetFileName("pointsAndLines.vtk");
    writer->SetInputData(polyData);
    writer->Write();
    return 0;
}