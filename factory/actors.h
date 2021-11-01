#pragma once

#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>

#include <vector>

std::vector<vtkNew<vtkActor>>
getActorsVector(std::vector<vtkNew<vtkPolyDataMapper>> &mappersVector, std::vector<vtkColor3d> colorsVector ) {
  std::vector<vtkNew<vtkActor>> actorsVector;

  for (int i = 0; i < mappersVector.size(); ++i) {
    vtkNew<vtkActor> actor;
    actor->SetMapper(mappersVector[i]);
    actor->GetProperty()->SetColor(colorsVector[i].GetData());
    actorsVector.emplace_back(std::move(actor));
  }

  return actorsVector;
}