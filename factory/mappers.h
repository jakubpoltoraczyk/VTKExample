#pragma once

#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkOBJReader.h>

#include <vector>

std::vector<vtkNew<vtkPolyDataMapper>>
getMappersVector(std::vector<vtkNew<vtkOBJReader>> &readersVector) {
  std::vector<vtkNew<vtkPolyDataMapper>> mappersVector;

  for (const auto &reader : readersVector) {
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    mappersVector.emplace_back(std::move(mapper));
  }
  
  return mappersVector;
}