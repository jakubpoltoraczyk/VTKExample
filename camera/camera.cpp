#include "camera.h"

#include <vtkNamedColors.h>

void CustomMouseInteractorStyle::OnLeftButtonDown() {
  int *clickPos = this->GetInteractor()->GetEventPosition();
  vtkNew<vtkPropPicker> picker;
  picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
  if (auto *button = picker->GetActor();
      std::find(buttons.begin(), buttons.end(), button) != buttons.end()) {
    customizePanelButtons(picker);
  }
  // Forward events
  vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void CustomMouseInteractorStyle::OnMiddleButtonDown() {
  // Forward events
  vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
}

void CustomMouseInteractorStyle::OnRightButtonDown() {
  // Forward events
  vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}

void CustomMouseInteractorStyle::customizePanelButtons(
    vtkNew<vtkPropPicker> &picker) {
  vtkNew<vtkNamedColors> colors;
  colors->SetColor("PanelButtonRed", "#FF0000");
  colors->SetColor("PanelButtonGreen", "#00FF00");
  if (auto *prop = picker->GetActor()->GetProperty();
      colors->GetColor3d("PanelButtonRed").GetData()[0] ==
      picker->GetActor()->GetProperty()->GetColor()[0]) {
    for (auto &button : buttons) {
      button->GetProperty()->SetColor(
          colors->GetColor3d("PanelButtonRed").GetData());
    }
    prop->SetColor(colors->GetColor3d("PanelButtonGreen").GetData());
  } else {
    for (auto &button : buttons) {
      button->GetProperty()->SetColor(
          colors->GetColor3d("PanelButtonGreen").GetData());
    }
    prop->SetColor(colors->GetColor3d("PanelButtonRed").GetData());
  }
}