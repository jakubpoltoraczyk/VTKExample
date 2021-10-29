#pragma once

#include <vtkOBJImporter.h>
#include <vtkNew.h>

#include <vector>

std::vector<vtkNew<vtkOBJImporter>> getImporterVector() {
  std::vector<vtkNew<vtkOBJImporter>> importerVector;
  vtkNew<vtkOBJImporter> importer;
  
  importerVector.emplace_back(std::move(importer));
  importerVector[0]->SetFileName("../images/Corona.obj");
  importerVector[0]->SetFileNameMTL("../images/Corona.mtl");
  importerVector[0]->SetTexturePath("../images/tex");

  return importerVector;
}