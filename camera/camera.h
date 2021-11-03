#pragma once

#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNew.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>

#include <algorithm>
#include <utility>
#include <vector>

class CustomMouseInteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
  static CustomMouseInteractorStyle *New();
  vtkTypeMacro(CustomMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

  enum class ButtonStatus { Active, InActive };

  void OnMouseMove() override;

  void OnLeftButtonDown() override;

  void OnMiddleButtonDown() override;

  void OnRightButtonDown() override;

  std::vector<std::pair<vtkActor *, ButtonStatus>> buttons;
  std::vector<vtkActor *> walls;

private:
  void customizePanelButtons(vtkNew<vtkPropPicker> &picker);
  void customizeBackground(vtkActor *button);
  void changeWallsVisiblity(double cameraPosition[]);
};