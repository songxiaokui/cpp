//
// Created by austsxk on 2021/8/2.
//
#include <vtkPoints.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataWriter.h>
#include <vtkLine.h>
#include <vtkFloatArray.h>
#include <vtkIntArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
using namespace std;
// 将零维拓扑图改为一维拓扑图
int main() {
    // 创建三个坐标点
    vtkNew<vtkPoints> points;
    points->InsertNextPoint(1, 0, 0);
    points->InsertNextPoint(2, 0, 0);
    points->InsertNextPoint(3, 0, 0);

    // 创建一个多边形数据集
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
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

    // 给线条上点添加标量数据
    //创建一个可以存储浮点型数据的标量属性数据数组（组元为1，及一维数据）
    vtkNew<vtkFloatArray> floatArrScalar;
    //向数据尾部插入浮点型数据
    floatArrScalar->InsertTuple1(0, 1.0);
    floatArrScalar->InsertTuple1(1, 2.0);
    floatArrScalar->InsertTuple1(2, 3.0);
    floatArrScalar->SetName("B");

    //创建一个可以存储浮点型数据的矢量属性数据数组（组元为3，及三维数据）
    vtkNew<vtkFloatArray> floatArrVector;
    //设置组元大小为3
    floatArrVector->SetNumberOfComponents(3);
    //向数据尾部插入浮点型向量
    floatArrVector->InsertTuple3(0, 1.0, 1.0, 1.0);
    floatArrVector->InsertTuple3(1, 2.0, 2.0, 2.0);
    floatArrVector->InsertTuple3(2, 3.0, 3.0, 3.0);
    floatArrVector->SetName("A");

    //将标量属性数据与数据集中的点相关联
    //创建多边形数据集对象
    //将标量属性数据设置到数据点集中
    polyData->GetPointData()->SetScalars(floatArrScalar);
    //将矢量属性数据设置到单元数据集中
    polyData->GetCellData()->SetVectors(floatArrVector);

    vtkNew<vtkPolyDataWriter> writer;
    writer->SetFileName("pointsAndLines.vtk");
    writer->SetInputData(polyData);
    writer->Write();
    return 0;
}