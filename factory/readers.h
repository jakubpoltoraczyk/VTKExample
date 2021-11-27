#pragma once

#include <vtkNew.h>
#include <vtkOBJReader.h>

#include <vector>

std::vector<vtkNew<vtkOBJReader>> getReadersVector() {
  std::vector<std::string> files{
      "../images/desk.obj",       "../images/trumpet.obj",
      "../images/lamp.obj",       "../images/notebook.obj",
      "../images/cup.obj",        "../images/pill.obj",
      "../images/pill.obj",       "../images/pill.obj",
      "../images/pill.obj",       "../images/pill.obj",
      "../images/pill.obj",       "../images/pillbottle.obj",
      "../images/floor.obj",      "../images/chair.obj",
      "../images/coffetable.obj", "../images/bed.obj",
      "../images/book.obj",       "../images/book.obj",
      "../images/pen.obj"};

  std::vector<vtkNew<vtkOBJReader>> readersVector;
  for (const auto &file : files) {
    vtkNew<vtkOBJReader> reader;
    reader->SetFileName(file.c_str());
    reader->Update();
    readersVector.emplace_back(std::move(reader));
  }

  return readersVector;
}
