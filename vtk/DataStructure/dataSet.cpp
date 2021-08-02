//
// Created by austsxk on 2021/8/2.
//
#include "iostream"
#include <vtkDataSet.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
using namespace std;
int main() {
    vtkNew<vtkPoints> points;
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);

    vtkNew<vtkPolyData> polyData;
    polyData->SetPoints(points);

    vtkNew<vtkPolyDataWriter> writer;
    writer->SetFileName("points.vtk");
    writer->SetInputData(polyData);
    writer->Write();
    return 0;
}