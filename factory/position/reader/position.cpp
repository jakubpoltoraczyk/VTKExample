#include "position.h"

#include <random>
#include <stdlib.h>

void customizeObjectsPositions(std::vector<vtkNew<vtkActor>> &vectorActor) {
  using namespace CustomizePositionHelperFunctions;
  customizeDeskPosition(vectorActor[0], vectorActor[0]->GetCenter());
  customizeTrumpetPosition(vectorActor[1], vectorActor[0]->GetCenter());
  customizeLampPosition(vectorActor[2], vectorActor[0]->GetCenter());
  customizeNotebookPosition(vectorActor[3], vectorActor[0]->GetCenter());
  customizeCupPosition(vectorActor[4], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[5], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[6], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[7], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[8], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[9], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[10], vectorActor[0]->GetCenter());
  customizePillBottlePosition(vectorActor[11], vectorActor[0]->GetCenter());
  customizeFloorPosition(vectorActor[12], vectorActor[0]->GetCenter());
  customizeChairPosition(vectorActor[13], vectorActor[0]->GetCenter());
  customizeCoffeTablePosition(vectorActor[14], vectorActor[0]->GetCenter());
  customizeBedPosition(vectorActor[15], vectorActor[0]->GetCenter());
  customizeBookPosition(vectorActor[16], vectorActor[0]->GetCenter());
  customizeBookPosition(vectorActor[17], vectorActor[0]->GetCenter());
  customizePenPosition(vectorActor[18], vectorActor[0]->GetCenter());
}

void CustomizePositionHelperFunctions::customizeDeskPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->RotateY(180);
}

void CustomizePositionHelperFunctions::customizeTrumpetPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->RotateX(90);
  actor->RotateY(45);
  coordinates[0] += 820;
  coordinates[1] -= 190;
  coordinates[2] += 780;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeLampPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->RotateY(45);
  coordinates[0] -= 500;
  coordinates[1] += 470;
  coordinates[2] -= 150;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeNotebookPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(180);
  actor->RotateY(90);
  coordinates[1] += 500;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeCupPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(8);
  actor->RotateY(-45);
  coordinates[0] -= 500;
  coordinates[1] += 475;
  coordinates[2] += 250;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizePillPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  static int counter = 0;
  static int movementX = 400;
  static int movementZ = 0;

  switch (counter) {
  case 0:
    break;
  case 1:
    movementX += 50;
    movementZ += 50;
    break;
  case 2:
    movementX += 50;
    movementZ += 50;
    break;
  case 3:
    movementX += 50;
    movementZ += 50;
    break;
  case 4:
    movementX -= 50;
    movementZ -= 200;
    break;
  case 5:
    movementX += 75;
    break;
  case 6:
    movementX += 50;
    movementZ += 50;
    break;
  default:
    break;
  }
  ++counter;

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(1, 90);
  int angle = dist(mt);

  actor->SetScale(0.08);
  actor->RotateY(angle);
  actor->RotateZ(90);
  coordinates[0] += movementX;
  coordinates[1] += 485;
  coordinates[2] += movementZ;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizePillBottlePosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(10);
  actor->RotateX(-90);
  coordinates[0] += 520;
  coordinates[1] += 480;
  coordinates[2] += 60;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeFloorPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(120);
  actor->RotateX(-90);
  coordinates[0] += 1600;
  coordinates[1] -= 590;
  coordinates[2] += 1200;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeChairPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(1.3);
  actor->RotateY(180);
  coordinates[1] -= 490;
  coordinates[2] += 500;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeCoffeTablePosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(30);
  coordinates[0] -= 3000;
  coordinates[1] -= 250;
  coordinates[2] += 2300;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeBedPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(10);
  coordinates[0] += 3200;
  coordinates[1] -= 600;
  coordinates[2] += 300;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizeBookPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  static int counter = 0;
  actor->SetScale(15);

  if (counter == 0) {
    actor->RotateY(30);
    coordinates[0] += 1500;
    coordinates[1] += 35;
  } else {
    actor->RotateY(45);
    coordinates[0] += 1550;
    coordinates[1] += 72;
  }
  ++counter;

  coordinates[2] += 2100;
  actor->SetPosition(coordinates);
}

void CustomizePositionHelperFunctions::customizePenPosition(
    vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->RotateY(-35);
  coordinates[0] += 1100;
  coordinates[1] += 30;
  coordinates[2] += 2200;
  actor->SetPosition(coordinates);
}