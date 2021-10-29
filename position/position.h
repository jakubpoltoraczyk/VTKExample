#pragma once

#include <vtkActor.h>
#include <vtkNew.h>

void customizeDeskPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeTrumpetPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeLampPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeNotebookPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeCupPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizePillPosition(vtkNew<vtkActor> & actor, double coordinates[]);

void customizePillBottle(vtkNew<vtkActor> & actor, double coordinates[]);

void customizeFloor(vtkNew<vtkActor> & actor, double coordinates[]);

void customizeChair(vtkNew<vtkActor> & actor, double coordinates[]);

void customizeCoffeTable(vtkNew<vtkActor> & actor, double coordinates[]);

void customizeBed(vtkNew<vtkActor> & actor, double coordinates[]);

void customizeBook(vtkNew<vtkActor> & actor, double coordinates[]);

void customizePen(vtkNew<vtkActor> & actor, double coordinates[]);