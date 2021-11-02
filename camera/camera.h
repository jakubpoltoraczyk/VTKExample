#pragma once

#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNew.h>
#include <vtkPropPicker.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>

#include <algorithm>
#include <vector>

class CustomMouseInteractorStyle : public vtkInteractorStyleTrackballCamera {
public:
  static CustomMouseInteractorStyle *New();
  vtkTypeMacro(CustomMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

  void OnLeftButtonDown() override;

  void OnMiddleButtonDown() override;

  void OnRightButtonDown() override;

  std::vector<vtkActor *> buttons;

  private:
    void customizePanelButtons(vtkNew<vtkPropPicker> & picker);
};