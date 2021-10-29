
#pragma once

#include <vtkOBJImporter.h>
#include <vtkNew.h>

#include <vector>

std::vector<vtkNew<vtkOBJImporter>> getImporterVector() {
  std::vector<vtkNew<vtkOBJImporter>> importerVector;
  vtkNew<vtkOBJImporter> importer;
  
  importerVector.emplace_back(std::move(importer));
  importerVector[0]->SetFileName("../images/corona/Corona.obj");
  importerVector[0]->SetFileNameMTL("../images/corona/Corona.mtl");
  importerVector[0]->SetTexturePath("../images/corona/tex");

  return importerVector;
}