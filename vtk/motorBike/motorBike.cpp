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

#define FILE_PATH "/Users/austsxk/github_sxk_repo/c++/cpp/vtk/motorBike/motorbike.vtk"

int main() {
    // 使用vtk非结构网格读取vtk源文件
    vtkNew<vtkUnstructuredGridReader> reader;
    reader->SetFileName(FILE_PATH);
    reader->Update();
    reader->SetReadAllScalars(true);
    std::cout << "源文件的点数量" << reader->GetOutput()->GetNumberOfPoints() << std::endl;
    std::cout << "源文件单元数量" << reader->GetOutput()->GetNumberOfCells() << std::endl;
    // 获取边界值 X、 Y、 Z三个方向
    double bounds[6];
    reader->GetOutput()->GetBounds(bounds);
    std::cout << "Bound0 " << bounds[0] << std::endl;  // Xmin
    std::cout << "Bound1 " << bounds[1] << std::endl;  // Xmax
    std::cout << "Bound2 " << bounds[2] << std::endl;  // Ymin
    std::cout << "Bound3 " << bounds[3] << std::endl;  // Ymax
    std::cout << "Bound4 " << bounds[4] << std::endl;  // Zmin
    std::cout << "Bound5 " << bounds[5] << std::endl;  // Zmax

    std::cout << "Bound " << (bounds[1] - bounds[0]) / 2.0 + bounds[0] << std::endl;
    std::cout << "Bound " << (bounds[3] - bounds[2]) / 2.0 + bounds[2] << std::endl;
    std::cout << "Bound " << (bounds[5] - bounds[4]) / 2.0 + bounds[4] << std::endl;

    double minBoxPoint[3];
    double maxBoxPoint[3];
    minBoxPoint[0] = (bounds[1] - bounds[0]) / 2.0 + bounds[0];
    minBoxPoint[1] = (bounds[3] - bounds[2]) / 2.0 + bounds[2];
    minBoxPoint[2] = (bounds[5] - bounds[4]) / 2.0 + bounds[4];
    maxBoxPoint[0] = bounds[1];
    maxBoxPoint[1] = bounds[3];
    maxBoxPoint[2] = bounds[5];

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

    // 将数据转化为图元进行渲染
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(geo->GetOutput());
    mapper->Update();

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> render;
    render->AddActor(actor);

    vtkNew<vtkRenderWindow> rw;
    rw->AddRenderer(render);
    rw->SetSize(600, 600);

    vtkNew<vtkOBJExporter> exporter;
    exporter->SetInput(rw);
    exporter->SetFilePrefix("clip");
    exporter->Write();
    return 0;
}