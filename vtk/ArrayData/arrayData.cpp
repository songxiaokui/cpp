//
// Created by austsxk on 2021/8/3.
//

// vtk数据存储

#include <vtkPoints.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataWriter.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vtkOBJExporter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkArrayData.h>
#include <vtkFloatArray.h>

using namespace std;

int main() {
    vtkNew<vtkFloatArray> array;
    // 创建固定长度的数组
    array->SetNumberOfComponents(1);
    // 设置为2，其实长度自动分配的是4个
    array->SetNumberOfTuples(2);
    array->SetTuple1(0, 222);
    array->SetTuple1(1, 333);
    array->SetTuple1(2, 444);
    array->SetComponent(3, 0, 555);
    array->SetComponent(4, 0, 123);

    std::cout << array->GetComponent(0, 0) << std::endl;
    std::cout << array->GetComponent(1, 0) << std::endl;
    std::cout << array->GetValue(2) << std::endl;
    std::cout << array->GetComponent(3, 0) << std::endl;
    std::cout << array->GetComponent(4, 0) << std::endl;

    vtkNew<vtkFloatArray> array2;
    array2->SetNumberOfComponents(1);
    array2->InsertNextTuple1(10);
    array2->InsertNextTuple1(20);
    array2->InsertNextTuple1(30);
    double d = array2->GetComponent(1, 0);
    std::cout << d << std::endl;

    return 0;
}