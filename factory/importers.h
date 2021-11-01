#pragma once

#include <vtkOBJImporter.h>
#include <vtkNew.h>

#include <vector>

std::vector<vtkNew<vtkOBJImporter>> getImportersVector() {
  std::vector<vtkNew<vtkOBJImporter>> importersVector;
  vtkNew<vtkOBJImporter> importer;
  
  importersVector.emplace_back(std::move(importer));
  importersVector[0]->SetFileName("../images/corona/Corona.obj");
  importersVector[0]->SetFileNameMTL("../images/corona/Corona.mtl");
  importersVector[0]->SetTexturePath("../images/corona/tex");

  return importersVector;
}