//
// Created by austsxk on 2021/8/5.
//

// vtkCutter cut剪切数据集
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
#include <vtkTubeFilter.h>
#include <vtkNamedColors.h>
#include <vtkCellData.h>
#include <vtkLookupTable.h>
#include <vtkCubeSource.h>
#include <vtkPlane.h>
#include <vtkCutter.h>
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkCutter.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPlane.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPolyDataWriter.h>

int main() {
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkCubeSource> cube;
    cube->SetXLength(40);
    cube->SetYLength(30);
    cube->SetZLength(20);
    vtkNew<vtkPolyDataMapper> cubeMapper;
    cubeMapper->SetInputConnection(cube->GetOutputPort());

    vtkNew<vtkPlane> plane;
    plane->SetOrigin(10, 0, 0);
    plane->SetNormal(1, 0, 0);

    // Create cutter
    vtkNew<vtkCutter> cutter;
    cutter->SetCutFunction(plane);
    cutter->SetInputConnection(cube->GetOutputPort());
    cutter->Update();

    // 导出切出的数据
    vtkNew<vtkPolyDataWriter> w;
    w->SetFileName("c.vtk");
    w->SetInputConnection(cutter->GetOutputPort());
    w->Write();

    vtkNew<vtkPolyDataMapper> cutterMapper;
    cutterMapper->SetInputConnection(cutter->GetOutputPort());
    cutterMapper->SetResolveCoincidentTopologyToPolygonOffset();

    // Create plane actor
    vtkNew<vtkActor> planeActor;
    planeActor->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
    planeActor->GetProperty()->SetLineWidth(2);
    planeActor->GetProperty()->SetAmbient(1.0);
    planeActor->GetProperty()->SetDiffuse(0.0);
    planeActor->SetMapper(cutterMapper);

    // Create cube actor
    vtkNew<vtkActor> cubeActor;
    cubeActor->GetProperty()->SetColor(
            colors->GetColor3d("Aquamarine").GetData());
    cubeActor->GetProperty()->SetOpacity(0.5);
    cubeActor->SetMapper(cubeMapper);

    // Create renderers and add actors of plane and cube
    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(planeActor);
    // cut
    renderer->AddActor(cubeActor);

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(600, 600);

    vtkNew<vtkOBJExporter> exporter;
    exporter->SetInput(renderWindow);
    exporter->SetFilePrefix("cutter");
    exporter->Update();
    exporter->Write();
}