#include "camera.h"

#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <vtkMath.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>

#include <algorithm>

void CustomMouseInteractorStyle::OnMouseMove() {
  /* Wall visibility depends on camera position */
  if (auto currentRenderer = this->GetCurrentRenderer();
      currentRenderer != nullptr) {
    changeWallsVisiblity(currentRenderer->GetActiveCamera()->GetPosition());
  }

  // Forward events
  vtkInteractorStyleTrackballCamera::OnMouseMove();
}

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
  vtkNew<vtkNamedColors> colors;
  colors->SetColor("MainLightOn", "#FFFFFF");
  colors->SetColor("MainLightOff", "#303030");
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
    mainLight->SetIntensity(1);
  } else {
    mainLight->SetIntensity(0.25);
    /* Block slider */
  }
}

void CustomMouseInteractorStyle::changeWallsVisiblity(double cameraPosition[]) {
  std::vector<double> cameraAndWallDistances;

  /* Creating vector with points distance */
  std::transform(walls.begin(), walls.end(),
                 std::back_inserter(cameraAndWallDistances),
                 [cameraPosition](auto it) {
                   return vtkMath::Distance2BetweenPoints(cameraPosition,
                                                          it->GetPosition());
                 });

  /* Looking for two smallest values */
  auto min_elem_first = std::min_element(cameraAndWallDistances.begin(),
                                         cameraAndWallDistances.end());
  auto min_elem_second = std::min_element(
      cameraAndWallDistances.begin(), cameraAndWallDistances.end(),
      [min_elem_first](double a, double b) {
        if (b == *min_elem_first) {
          b = a;
        }
        return (a <= b && a != *min_elem_first);
      });

  /* Setting each wall visibility as true */
  for (int i = 0; i < cameraAndWallDistances.size(); ++i) {
    walls[i]->VisibilityOn();
  }

  /* Hiding appropriate two walls */
  for (int i = 0; i < cameraAndWallDistances.size(); ++i) {
    if (cameraAndWallDistances[i] == *min_elem_first ||
        cameraAndWallDistances[i] == *min_elem_second) {
      walls[i]->VisibilityOff();
    }
  }
}
