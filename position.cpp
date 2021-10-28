#include "position.h"

void customizeDeskPosition(vtkNew<vtkActor> & actor, double coordinates[]){
  actor->RotateY(180);    
}

void customizeTrumpetPosition(vtkNew<vtkActor> & actor, double coordinates[]){
  actor->RotateZ(90);
  coordinates[0] += 100;
  coordinates[1] += 540;
  coordinates[2] += 250;
  actor->SetPosition(coordinates);
}

void customizeLampPosition(vtkNew<vtkActor> & actor, double coordinates[]){
  actor->RotateY(45);
  coordinates[0] -= 500;
  coordinates[1] += 480;
  coordinates[2] -= 150;
  actor->SetPosition(coordinates);
}

void customizeNotebookPosition(vtkNew<vtkActor> & actor, double coordinates[]){
  actor->SetScale(180);
  actor->RotateY(90);
  coordinates[1] += 500;
  actor->SetPosition(coordinates);
}

void customizeGlassPosition(vtkNew<vtkActor> & actor, double coordinates[]){
  actor->SetScale(0.8);
  coordinates[0] -= 500;
  coordinates[1] += 450;
  coordinates[2] += 250;
  actor->SetPosition(coordinates);
}