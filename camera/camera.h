#pragma once

#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLight.h>
#include <vtkNew.h>
#include <vtkOpenGLRenderer.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

class CustomInteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
  static CustomInteractorStyle *New();
  vtkTypeMacro(CustomInteractorStyle, vtkInteractorStyleTrackballCamera);

  enum class ButtonStatus { Active, InActive };

  void OnMouseMove() override;

  void OnLeftButtonDown() override;

  void OnMiddleButtonDown() override;

  void OnRightButtonDown() override;

  virtual void OnKeyPress() override;

  std::vector<std::pair<vtkActor *, ButtonStatus>> buttons;
  std::vector<vtkActor *> walls;
  std::vector<vtkActor *> Actors;
  vtkActor *movedActor = nullptr;
  double newActorPosition[3];

  void setMainLight(vtkLight *light) { mainLight = light; };

private:
  void customizePanelButtons(vtkNew<vtkPropPicker> &picker);
  void customizeBackground(vtkActor *button);
  void changeWallsVisiblity(double cameraPosition[]);

  vtkLight *mainLight;
  bool interactive = false;
};
