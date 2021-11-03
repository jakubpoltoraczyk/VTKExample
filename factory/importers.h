#pragma once

#include <vtkNew.h>
#include <vtkOBJImporter.h>

#include <vector>

std::vector<vtkNew<vtkOBJImporter>> getImportersVector() {
  std::vector<vtkNew<vtkOBJImporter>> importersVector;

  vtkNew<vtkOBJImporter> importer;
  importer->SetFileName("../images/wall/wall.obj");
  importer->SetFileNameMTL("../images/wall/wall.mtl");
  importer->SetTexturePath("../images/wall/tex");
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

  vtkNew<vtkOBJImporter> importer4;
  importer4->SetFileName("../images/wall/wall.obj");
  importer4->SetFileNameMTL("../images/wall/wall.mtl");
  importer4->SetTexturePath("../images/wall/tex");
  importersVector.emplace_back(std::move(importer4));

  vtkNew<vtkOBJImporter> importer5;
  importer5->SetFileName("../images/corona/Corona.obj");
  importer5->SetFileNameMTL("../images/corona/Corona.mtl");
  importer5->SetTexturePath("../images/corona/tex");
  importersVector.emplace_back(std::move(importer5));

  return importersVector;
}