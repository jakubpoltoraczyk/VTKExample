#include "camera.h"

#include <vtkNamedColors.h>
#include <vtkRenderer.h>

void CustomMouseInteractorStyle::OnLeftButtonDown() {
  int *clickPos = this->GetInteractor()->GetEventPosition();
  vtkNew<vtkPropPicker> picker;
  picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
  /* When button from panel is clicked */
  if (auto *button = picker->GetActor();
      std::find_if(buttons.begin(), buttons.end(),
                   [button](auto buttonsIterator) {
                     return buttonsIterator.first == button;
                   }) != buttons.end()) {
    customizePanelButtons(picker);
    customizeBackground(button);
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
  /* Colors definition */
  vtkNew<vtkNamedColors> colors;
  colors->SetColor("PanelButtonRed", "#FF0000");
  colors->SetColor("PanelButtonGreen", "#00FF00");
  auto *redColor = colors->GetColor3d("PanelButtonRed").GetData();
  auto *greenColor = colors->GetColor3d("PanelButtonGreen").GetData();
  /* Changing buttons colors */
  for (auto &button : buttons) {
    if (picker->GetActor() == button.first) {
      ButtonStatus currentStatus = button.second;
      if (currentStatus == ButtonStatus::Active) {
        button.first->GetProperty()->SetColor(redColor);
        button.second = ButtonStatus::InActive;
      } else {
        button.first->GetProperty()->SetColor(greenColor);
        button.second = ButtonStatus::Active;
      }
      break;
    }
  }
}

void CustomMouseInteractorStyle::customizeBackground(vtkActor *button) {
  auto *currentRenderer = this->GetCurrentRenderer();
  /* First button */
  if (buttons[0].second == ButtonStatus::Active) {
    currentRenderer->SetBackground(0, 0, 0);
    currentRenderer->SetBackground2(255, 185, 180);
  } else {
    currentRenderer->SetBackground(255, 255, 255);
    currentRenderer->SetBackground2(10, 10, 100);
  }
  /* Second button */
  if (buttons[1].second == ButtonStatus::Active) {
    currentRenderer->GradientBackgroundOn();
  } else {
    currentRenderer->GradientBackgroundOff();
  }
  /* Third button */
  if (buttons[2].second == ButtonStatus::Active) {
    /* Activate slider */
  } else {
    /* Block slider */
  }
}