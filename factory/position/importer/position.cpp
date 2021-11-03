#include "position.h"

void customizeImporterObjectsPositions(vtkNew<vtkActor> &centerActor,
                                       vtkActorCollection *actors,
                                       int actorsLimit) {
  using namespace CustomizeImporterObjectsHelperFunctions;
  for (int i = 0; i < actorsLimit; ++i) {
    vtkActor *actor = actors->GetNextActor();
    switch (i) {
    case 1:
      customizeRightWall(actor, centerActor->GetCenter());
      break;
    case 3:
      customizeBackWall(actor, centerActor->GetCenter());
      break;
    case 5:
      customizeLeftWall(actor, centerActor->GetCenter());
      break;
    case 7:
      customizeForeWall(actor, centerActor->GetCenter());
      break;
    case 9:
      customizeCoronaBottle(actor, centerActor->GetCenter());
      break;
    }
  }
}

void CustomizeImporterObjectsHelperFunctions::customizeCoronaBottle(
    vtkActor *actor, double coordinates[]) {
  actor->RotateX(-90);
  actor->SetScale(6);
  coordinates[0] += 1250;
  coordinates[1] += 32;
  coordinates[2] += 2300;
  actor->SetPosition(coordinates);
}

void CustomizeImporterObjectsHelperFunctions::customizeRightWall(
    vtkActor *actor, double coordinates[]) {
  actor->SetScale(1020, 800, 1);
  actor->RotateY(90);
  coordinates[0] += 4560;
  coordinates[1] += 1000;
  coordinates[2] += 2160;
  actor->SetPosition(coordinates);
}

void CustomizeImporterObjectsHelperFunctions::customizeBackWall(
    vtkActor *actor, double coordinates[]) {
  actor->SetScale(1480, 800, 1);
  coordinates[0] += 200;
  coordinates[1] += 1000;
  coordinates[2] -= 830;
  actor->SetPosition(coordinates);
}

void CustomizeImporterObjectsHelperFunctions::customizeLeftWall(
    vtkActor *actor, double coordinates[]) {
  actor->SetScale(1020, 800, 1);
  actor->RotateY(90);
  coordinates[0] -= 1355;
  coordinates[1] += 1000;
  coordinates[2] += 2160;
  actor->SetPosition(coordinates);
}

void CustomizeImporterObjectsHelperFunctions::customizeForeWall(
    vtkActor *actor, double coordinates[]) {
  actor->VisibilityOff();
  actor->SetScale(1480, 800, 1);
  coordinates[0] += 200;
  coordinates[1] += 1000;
  coordinates[2] += 3225;
  actor->SetPosition(coordinates);
}