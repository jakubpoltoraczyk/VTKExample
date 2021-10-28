#pragma once

#include <vtkActor.h>
#include <vtkNew.h>

void customizeDeskPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeTrumpetPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeLampPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeNotebookPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeGlassPosition(vtkNew<vtkActor> &actor, double coordinates[]);