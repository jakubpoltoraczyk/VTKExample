#pragma once

#include <vtkActor.h>
#include <vtkNew.h>

#include <vector>

void customizeObjectsPositions(std::vector<vtkNew<vtkActor>> &vectorActor);

namespace CustomizePositionHelperFunctions {

void customizeDeskPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeTrumpetPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeLampPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeNotebookPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeCupPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizePillPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizePillBottlePosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeFloorPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeChairPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeCoffeTablePosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeBedPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizeBookPosition(vtkNew<vtkActor> &actor, double coordinates[]);

void customizePenPosition(vtkNew<vtkActor> &actor, double coordinates[]);

} // namespace CustomizePositionHelperFunctions