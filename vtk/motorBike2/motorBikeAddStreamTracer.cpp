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
#include <vtkPlaneSource.h>
#include <vtkStreamTracer.h>
#include <vtkAssembly.h>
#include <vtkPolyDataWriter.h>
#include <vtkLineSource.h>
#include <vtkCellDataToPointData.h>

#define FILE_PATH "/Users/austsxk/github_sxk_repo/c++/cpp/vtk/motorBike/motorbike.vtk"
// 流线处理

int main() {
    // 使用vtk非结构网格读取vtk源文件
    vtkNew<vtkUnstructuredGridReader> reader;
    reader->SetFileName(FILE_PATH);
    reader->Update();
    reader->SetReadAllScalars(true);
    std::cout << "源文件的点数量" << reader->GetOutput()->GetNumberOfPoints() << std::endl;
    std::cout << "源文件单元数量" << reader->GetOutput()->GetNumberOfCells() << std::endl;

    vtkNew<vtkCellDataToPointData> c2p;
    c2p->SetInputConnection(reader->GetOutputPort());
    c2p->Update();
    c2p->GetOutput()->GetPointData()->SetActiveVectors("U");
    c2p->Update();

    // 提取表面
    vtkNew<vtkDataSetSurfaceFilter> extractSurface;
    extractSurface->SetInputConnection(reader->GetOutputPort());
    extractSurface->Update();
    std::cout << "提取表面后的点数量 " << extractSurface->GetOutput()->GetNumberOfPoints() << std::endl;
    std::cout << "提取表面后单元数量 " << extractSurface->GetOutput()->GetNumberOfCells() << std::endl;

    // box clip
    vtkNew<vtkBoxClipDataSet> clip;

    // GenerateClippedOutputOn 要第二部分，提取之外的部分
    clip->SetInputConnection(extractSurface->GetOutputPort());
    clip->Update();
    clip->SetOrientation(1);

    // 当坐标轴平行时，直接取边界范围的box进行提取
    clip->SetBoxClip(-2, 2, -2, 3, 0.00001, 3);
    clip->GenerateClippedOutputOn();

    // 将裁剪后的数据集转化为几何
    vtkNew<vtkGeometryFilter> geo;
    geo->SetInputConnection(clip->GetOutputPort());
    geo->Update();

    // 创建平面
    vtkNew<vtkPlaneSource> plane;
    plane->SetXResolution(6);
    plane->SetYResolution(6);
    plane->SetOrigin(-2, 2, 2);
    plane->SetPoint1(-2, 2, 0);
    plane->SetPoint2(-2, -2, 2);
    plane->Update();

    // 创建流线
    vtkNew<vtkLineSource> line;
    line->SetResolution(100);
    line->SetPoint1(-0.5, 0, 1);
    line->SetPoint2(2, 0, 0.5);
    line->Update();

    // 创建流线
    vtkNew<vtkStreamTracer> lineTracer;
    lineTracer->SetInputConnection(c2p->GetOutputPort());
    // 设置积分种子
    lineTracer->SetSourceConnection(plane->GetOutputPort());
    // 设置积分方向
    lineTracer->SetIntegrationDirectionToBoth();
    // 设置积分算法
    lineTracer->SetIntegratorTypeToRungeKutta45();
    lineTracer->SetMaximumPropagation(7.2);
    lineTracer->SetComputeVorticity(1);
    lineTracer->Update();

    // 将流线数据导出
    vtkNew<vtkPolyDataWriter> w;
    w->SetInputConnection(lineTracer->GetOutputPort());
    w->SetFileName("tracer.vtk");
    w->Update();
    w->Write();

    // 将数据转化为图元进行渲染
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(geo->GetOutput());
    mapper->Update();

    vtkNew<vtkPolyDataMapper> tracerMapper;
    tracerMapper->SetInputConnection(lineTracer->GetOutputPort());
    tracerMapper->Update();


    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkActor> lineActor;
    lineActor->SetMapper(tracerMapper);

    // 将clip与流线组合成为一个整体
    vtkNew<vtkAssembly> assembly;
    assembly->AddPart(actor);
    assembly->AddPart(lineActor);

    vtkNew<vtkRenderer> render;
    render->AddActor(assembly);

    vtkNew<vtkRenderWindow> rw;
    rw->AddRenderer(render);
    rw->SetSize(600, 600);

    vtkNew<vtkOBJExporter> exporter;
    exporter->SetInput(rw);
    exporter->SetFilePrefix("tracer");
    exporter->Write();
    return 0;
}