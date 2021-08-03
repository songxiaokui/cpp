//
// Created by austsxk on 2021/8/3.
//

// 给点数据添加标量

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

using namespace std;

int main() {
    vtkNew<vtkPoints> points;
    points->InsertNextPoint(1, 0, 0);
    points->InsertNextPoint(0, 0, 0);

    // 创建多边形数据
    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);

    // 给点数据添加标量
    vtkNew<vtkDoubleArray> data;
    data->SetNumberOfValues(2);
    data->SetValue(0, 10);
    data->SetValue(1, 20);

    // 给多边形数据设置标量,先获取点集，在设置标量
    polyData->GetPointData()->SetScalars(data);

    double d = (vtkDoubleArray::SafeDownCast(polyData->GetPointData()->GetScalars()))->GetValue(1);
    // 输出为 20
    std::cout << d << std::endl;

    // 导出vtk文件
    vtkNew<vtkPolyDataWriter> w;
    w->SetInputData(polyData);
    w->SetFileName("addScalars.vtk");
    w->Write();

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polyData);
    mapper->Update();

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> render;
    render->AddActor(actor);

    vtkNew<vtkRenderWindow> rw;
    rw->AddRenderer(render);
    rw->SetSize(600, 600);


    // 转化为obj文件
    vtkNew<vtkOBJExporter> writer;
    writer->SetFilePrefix("addScalars");
    writer->SetInput(rw);
    writer->Write();
    return 0;
}