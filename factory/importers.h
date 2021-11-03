#pragma once

#include <vtkOBJImporter.h>
#include <vtkNew.h>

#include <vector>

std::vector<vtkNew<vtkOBJImporter>> getImportersVector() {
  std::vector<vtkNew<vtkOBJImporter>> importersVector;

  vtkNew<vtkOBJImporter> importer;
  importer->SetFileName("../images/corona/Corona.obj");
  importer->SetFileNameMTL("../images/corona/Corona.mtl");
  importer->SetTexturePath("../images/corona/tex");
  importersVector.emplace_back(std::move(importer));

  vtkNew<vtkOBJImporter> importer2;
  importer2->SetFileName("../images/wall/wall.obj");
  importer2->SetFileNameMTL("../images/wall/wall.mtl");
  importer2->SetTexturePath("../images/wall/tex");
  importersVector.emplace_back(std::move(importer2));

  vtkNew<vtkOBJImporter> importer3;
  importer3->SetFileName("../images/wall/wall.obj");
  importer3->SetFileNameMTL("../images/wall/wall.mtl");
  importer3->SetTexturePath("../images/wall/tex");
  importersVector.emplace_back(std::move(importer3));

  return importersVector;
}