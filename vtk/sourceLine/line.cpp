//
// Created by austsxk on 2021/8/4.
//

#include <vtkUnstructuredGridReader.h>
#include <vtkNew.h>
#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellArray.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkBoxClipDataSet.h>
#include <vtkGeometryFilter.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOBJExporter.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkLineSource.h>
#include <array>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkPolyDataWriter.h>

int main() {
    // 定义两个点
    double p0[3] = {1.0, 0.0, 0.0};
    double p1[3] = {0.0, 1.0, 0.0};

    // 定义一个线，添加两个点
    vtkNew<vtkLineSource> line;
    line->SetPoint2(p0);
    line->SetPoint1(p1);
    line->Update();

    vtkNew<vtkPolyDataWriter> w;
    w->SetInputData(line->GetOutput());
    w->SetFileName("line.vtk");
    w->Write();


    // 创建一个颜色表
    vtkNew<vtkNamedColors> colors;

    // 将单元转化为图元
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(line->GetOutput());
    mapper->Update();

    // 定义一个actor
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    // 获取actor的属性数据
    actor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData()); //颜色
    actor->GetProperty()->SetLineWidth(4); //线宽

    vtkNew<vtkRenderer> render;
    render->AddActor(actor);
    render->SetBackground(colors->GetColor3d("Silver").GetData());

    vtkNew<vtkRenderWindow> rw;
    rw->AddRenderer(render);
    rw->SetWindowName("line");

    // 将其导出为obj
    vtkNew<vtkOBJExporter> exporter;
    exporter->SetInput(rw);
    exporter->SetFilePrefix("line");
    exporter->Write();
    return 0;
}