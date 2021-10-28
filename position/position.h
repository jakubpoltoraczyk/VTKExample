#pragma once

#include <vtkActor.h>
#include <vtkNew.h>

void customizeDeskPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeTrumpetPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeLampPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeNotebookPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeWineGlassPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizePillPosition(vtkNew<vtkActor> & actor, double coordinates[]);

void customizePillBottle(vtkNew<vtkActor> & actor, double coordinates[]);

void customizeFloor(vtkNew<vtkActor> & actor, double coordinates[]);

void customizeChair(vtkNew<vtkActor> & actor, double coordinates[]);