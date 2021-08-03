//
// Created by austsxk on 2021/8/2.
//
#include <vtkPoints.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkCellArray.h>
#include <vtkPolyDataWriter.h>
using namespace std;

int main() {
    // 创建点坐标
    double X[3] = {1.0, 0, 0};
    double Y[3] = {0, 0, 1.0};
    double Z[3] = {0, 0, 0.0};

    vtkNew<vtkPoints> points;
    vtkNew<vtkCellArray> vertices;
    for (unsigned i=0; i<3; i++) {
        vtkIdType pid[1];
        pid[0] = points->InsertNextPoint(X[i], Y[i], Z[i]);
        vertices->InsertNextCell(1, pid);
    }

    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(points);
    polyData->SetVerts(vertices);

    vtkNew<vtkPolyDataWriter> writer;
    writer->SetFileName("pointsAndVertices.vtk");
    writer->SetInputData(polyData);
    writer->Write();
    return 0;
}