//
// Created by austsxk on 2021/8/3.
//

#include "addScalarsVectors.h"

// 给单元添加标量数据和矢量数据

void AddScalarsAndVectors() {
    vtkNew<vtkPlaneSource> plane;
    plane->SetXResolution(5);
    plane->SetYResolution(5);
    plane->Update();

    vtkSmartPointer<vtkPolyData> polyData = plane->GetOutput();

    // add scalar array and vector array
    vtkNew<vtkFloatArray> scalarArray;
    vtkNew<vtkFloatArray> vectorsArray;
    vectorsArray->SetNumberOfComponents(3);
    for (int i=1; i<9; i++) {
        scalarArray->InsertNextValue(i);
        vectorsArray->InsertNextTuple3(0.0, 0.0, 1.0);
    }

    polyData->GetCellData()->SetScalars(scalarArray);
    polyData->GetCellData()->SetScalars(vectorsArray);

    // create a color look up table
    vtkNew<vtkLookupTable> lookup;
    lookup->SetNumberOfTableValues(10);
    lookup->Build();
    lookup->SetTableValue(0,0,0,0, 1);
    lookup->SetTableValue(1, 0.8900, 0.8100, 0.3400, 1);
    lookup->SetTableValue(2, 1.0000, 0.3882, 0.2784, 1);
    lookup->SetTableValue(3, 0.9608, 0.8706, 0.7020, 1);
    lookup->SetTableValue(4, 0.9020, 0.9020, 0.9804, 1);
    lookup->SetTableValue(5, 1.0000, 0.4900, 0.2500, 1);
    lookup->SetTableValue(6, 0.5300, 0.1500, 0.3400, 1);
    lookup->SetTableValue(7, 0.9804, 0.5020, 0.4471, 1);
    lookup->SetTableValue(8, 0.7400, 0.9900, 0.7900, 1);
    lookup->SetTableValue(9, 0.2000, 0.6300, 0.7900, 1);

    // 使用自定义数组进行着色
    vtkNew<vtkIntArray> intArray;
    intArray->SetName("myFiled");
    intArray->SetNumberOfComponents(3);
    intArray->InsertNextTuple3(1, 0, 0);
    intArray->InsertNextTuple3(2, 0, 0);
    intArray->InsertNextTuple3(3, 0, 0);
    intArray->InsertNextTuple3(4, 0, 0);
    intArray->InsertNextTuple3(5, 0, 0);

    polyData->GetPointData()->SetScalars(intArray);

    // create a mapper
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polyData);
    // mapper->SetScalarRange(0, 9);
    // mapper->SetLookupTable(lookup);
    // 使用点数据的标量进行着色
    mapper->SetScalarModeToUsePointData();
    mapper->SelectColorArray("myFiled");
}