#pragma once

#include <vtkInteractorStyleTrackballCamera.h>

class CustomMouseInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
  static CustomMouseInteractorStyle* New();
  vtkTypeMacro(CustomMouseInteractorStyle, vtkInteractorStyleTrackballCamera);

  virtual void OnLeftButtonDown() override
  {
    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
  }

  virtual void OnMiddleButtonDown() override
  {
    // Forward events
    vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
  }

  virtual void OnRightButtonDown() override
  {
    // Forward events
    vtkInteractorStyleTrackballCamera::OnRightButtonDown();
  }
};