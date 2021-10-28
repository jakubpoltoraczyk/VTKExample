#include "position.h"

#include <random>
#include <stdlib.h>

void customizeDeskPosition(vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->RotateY(180);
}

void customizeTrumpetPosition(vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->RotateZ(90);
  coordinates[0] += 100;
  // coordinates[1] += 540;
  coordinates[1] -= 500;
  coordinates[2] += 250;
  actor->SetPosition(coordinates);
}

void customizeLampPosition(vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->RotateY(45);
  coordinates[0] -= 500;
  coordinates[1] += 470;
  coordinates[2] -= 150;
  actor->SetPosition(coordinates);
}

void customizeNotebookPosition(vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(180);
  actor->RotateY(90);
  coordinates[1] += 500;
  actor->SetPosition(coordinates);
}

void customizeWineGlassPosition(vtkNew<vtkActor> &actor, double coordinates[]) {
  actor->SetScale(25);
  coordinates[0] -= 500;
  coordinates[1] += 475;
  coordinates[2] += 250;
  actor->SetPosition(coordinates);
}

void customizePillPosition(vtkNew<vtkActor> &actor, double coordinates[]) {
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

void customizePillBottle(vtkNew<vtkActor> & actor, double coordinates[]){
  actor->SetScale(10);
  actor->RotateX(-90);
  coordinates[0] += 520;
  coordinates[1] += 480;
  coordinates[2] += 60;
  actor->SetPosition(coordinates);
}