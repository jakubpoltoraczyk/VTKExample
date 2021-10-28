#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCollisionDetectionFilter.h>
#include <vtkMatrix4x4.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTransform.h>

#include <chrono>
#include <sstream>
#include <string>
#include <thread>

int main(int argc, char* argv[])
{
  vtkNew<vtkSphereSource> sphere0;

  vtkNew<vtkSphereSource> sphere1;

  vtkNew<vtkMatrix4x4> matrix1;
  vtkNew<vtkTransform> transform0;

  vtkNew<vtkCollisionDetectionFilter> collide;
  collide->SetInputConnection(0, sphere0->GetOutputPort());
  collide->SetTransform(0, transform0);
  collide->SetInputConnection(1, sphere1->GetOutputPort());
  collide->SetMatrix(1, matrix1);

  vtkNew<vtkNamedColors> colors;
  vtkNew<vtkPolyDataMapper> mapper1;
  mapper1->SetInputConnection(collide->GetOutputPort(0));
  vtkNew<vtkActor> actor1;
  actor1->SetMapper(mapper1);
  actor1->SetUserTransform(transform0);
  actor1->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("Tomato").GetData());

  vtkNew<vtkPolyDataMapper> mapper2;
  mapper2->SetInputConnection(collide->GetOutputPort(1));
  vtkNew<vtkActor> actor2;
  actor2->SetMapper(mapper2);
  actor2->SetUserMatrix(matrix1);

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->SetBackground(colors->GetColor3d("Gray").GetData());

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->SetSize(640, 480);
  renderWindow->AddRenderer(renderer);

  vtkNew<vtkRenderWindowInteractor> interactor;
  interactor->SetRenderWindow(renderWindow);

  // Move the first object
  int numSteps = 100;
  double dx = 1.0 / static_cast<double>(numSteps) * 2.0;
  transform0->Translate(-numSteps * dx - .3, 0.0, 0.0);
  renderWindow->Render();

  renderWindow->SetWindowName("CollisionDetection");
  renderWindow->Render();

  for (int i = 0; i < numSteps; ++i)
  {
    transform0->Translate(dx, 0.0, 0.0);
    renderWindow->Render();
    if (collide->GetNumberOfContacts() > 0)
    {
      break;
    }
    // The total animation time is 3 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(3000 / numSteps));
  }
  renderer->ResetCamera();
  renderWindow->Render();
  interactor->Start();
  
  return EXIT_SUCCESS;
}
