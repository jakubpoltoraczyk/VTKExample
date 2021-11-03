#pragma once

#include <vtkActorCollection.h>
#include <vtkNew.h>

void customizeImporterObjectsPositions(vtkNew<vtkActor> &centerActor,
                                       vtkActorCollection *actors,
                                       int actorsLimit);

namespace CustomizeImporterObjectsHelperFunctions {
void customizeCoronaBottle(vtkActor *actor, double coordinates[]);

void customizeRightWall(vtkActor *actor, double coordinates[]);

void customizeBackWall(vtkActor *actor, double coordinates[]);

void customizeLeftWall(vtkActor *actor, double coordinates[]);

void customizeForeWall(vtkActor *actor, double coordinates[]);
} // namespace CustomizeImporterObjectsHelperFunctions