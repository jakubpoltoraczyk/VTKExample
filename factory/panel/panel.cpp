#include "panel.h"

#include <vtkCubeSource.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSphereSource.h>

namespace {
void customizePanelBackground(vtkNew<vtkActor> &actor, double coordinates[]) {
  /* Color */
  vtkNew<vtkNamedColors> color;
  color->SetColor("PanelBackground", "#FAFAD2");
  actor->GetProperty()->SetColor(
      color->GetColor3d("PanelBackground").GetData());
  /* Position */
  actor->SetScale(1000);
  coordinates[0] += 4500;
  coordinates[1] += 1000;
  coordinates[2] += 2000;
  actor->SetPosition(coordinates);
}

void customizePanelButton(vtkNew<vtkActor> &actor, double coordinates[]) {
  /* Color */
  vtkNew<vtkNamedColors> color;
  color->SetColor("PanelButton", "#FF0000");
  actor->GetProperty()->SetColor(color->GetColor3d("PanelButton").GetData());
  /* Position */
  actor->SetScale(100);
  static int moveY = -300;
  double x = coordinates[0] - 50;
  double y = coordinates[2] + moveY;
  double z = coordinates[1] - 75;
  double newCoordinates[] = {x, z, y};
  actor->SetPosition(newCoordinates);
  moveY += 300;
}
} // namespace

std::vector<vtkNew<vtkActor>> getPanelButtonsVector(double coordinates[]) {
  std::vector<vtkNew<vtkSphereSource>> panelButtonsSourceVector;
  for (int i = 0; i < 3; ++i) {
    vtkNew<vtkSphereSource> panelButtonSource;
    panelButtonSource->SetThetaResolution(200);
    panelButtonSource->SetPhiResolution(200);
    panelButtonSource->Update();
    panelButtonsSourceVector.emplace_back(std::move(panelButtonSource));
  }

  std::vector<vtkNew<vtkPolyDataMapper>> panelButtonsMapperVector;
  for (auto &panelButtonSource : panelButtonsSourceVector) {
    vtkNew<vtkPolyDataMapper> panelButtonMapper;
    panelButtonMapper->SetInputConnection(panelButtonSource->GetOutputPort());
    panelButtonsMapperVector.emplace_back(std::move(panelButtonMapper));
  }

  std::vector<vtkNew<vtkActor>> panelButtonsActorVector;
  for (auto &panelButtonMapper : panelButtonsMapperVector) {
    vtkNew<vtkActor> panelButtonActor;
    panelButtonActor->SetMapper(panelButtonMapper);
    panelButtonActor->SetScale(100);
    customizePanelButton(panelButtonActor, coordinates);
    panelButtonsActorVector.emplace_back(std::move(panelButtonActor));
  }

  return panelButtonsActorVector;
}

vtkNew<vtkActor> getPanelBackground(double coordinates[]) {
  vtkNew<vtkCubeSource> panelBackgroundSource;
  panelBackgroundSource->SetXLength(0.1);
  panelBackgroundSource->SetYLength(0.5);
  panelBackgroundSource->SetZLength(1);

  vtkNew<vtkPolyDataMapper> panelBackgroundMapper;
  panelBackgroundMapper->SetInputConnection(
      panelBackgroundSource->GetOutputPort());

  vtkNew<vtkActor> panelBackgroundActor;
  panelBackgroundActor->SetMapper(panelBackgroundMapper);

  customizePanelBackground(panelBackgroundActor, coordinates);

  return panelBackgroundActor;
}