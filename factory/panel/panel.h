#pragma once

#include <vtkNew.h>
#include <vtkActor.h>

#include <vector>

std::vector<vtkNew<vtkActor>> getPanelButtonsVector(double coordinates[]);

vtkNew<vtkActor> getPanelBackground(double coordinates[]);