#include "camera/camera.h"
#include "factory/colors.h"
#include "factory/importers.h"
#include "factory/readers.h"
#include "factory/position/reader/position.h"
#include "factory/mappers.h"
#include "factory/actors.h"

#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

vtkStandardNewMacro(CustomMouseInteractorStyle);

int main(int argc, char *argv[]) {
  /*************** Defining colors ******************/
  std::vector<vtkColor3d> colorsVector = getColorsVector();

  /************** Reading OBJ files *****************/
  std::vector<vtkNew<vtkOBJReader>> readersVector = getReadersVector();

  /*************** Creating mappers *****************/
  std::vector<vtkNew<vtkPolyDataMapper>> mappersVector = getMappersVector(readersVector);

  /*************** Creating actors ******************/
  std::vector<vtkNew<vtkActor>> actorsVector = getActorsVector(mappersVector, colorsVector);

  /************* Customizing positions **************/
  customizeObjectsPositions(actorsVector);

  /*************** Rendering window *****************/
  vtkNew<vtkRenderer> renderer;
  for (const auto &actor : actorsVector) {
    renderer->AddActor(actor);
  }
  renderer->SetBackground(255, 255, 255);

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Demo project");

  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkNew<CustomMouseInteractorStyle> style;
  renderWindowInteractor->SetInteractorStyle(style);

  /* USER CODE BEGIN */
  auto importersVector = getImportersVector();
  for (auto &importer : importersVector) {
    importer->SetRenderWindow(renderWindow);
    importer->Update();
  }

  auto actors = renderer->GetActors();
  actors->InitTraversal();

  vtkActor *actor = actors->GetLastActor();
  actor->RotateX(-90);
  actor->SetScale(6);
  auto *coordinates = actorsVector[0]->GetCenter();
  coordinates[0] += 1250;
  coordinates[1] += 32;
  coordinates[2] += 2300;
  actor->SetPosition(coordinates);
  /* USER CODE END */

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
