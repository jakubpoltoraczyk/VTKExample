#include "camera/camera.h"
#include "factory/importer.h"
#include "position/position.h"

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkOBJReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <string>

vtkStandardNewMacro(CustomMouseInteractorStyle);

int main(int argc, char *argv[]) {
  vtkNew<vtkRenderer> renderer;
  renderer->SetBackground(255, 255, 255);

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Demo project");
  renderWindow->SetSize(640, 480);

  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkNew<CustomMouseInteractorStyle> style;
  renderWindowInteractor->SetInteractorStyle(style);

  /* USER CODE BEGIN */
  auto importerVector = getImporterVector();
  for (auto &importer : importerVector) {
    importer->SetRenderWindow(renderWindow);
    importer->Update();
  }

  auto actors = renderer->GetActors();
  actors->InitTraversal();

  for (vtkIdType i = 0; i < actors->GetNumberOfItems(); ++i) {
    vtkActor *actor = actors->GetNextActor();
    actor->RotateX(90);
  }
  /* USER CODE END */

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
