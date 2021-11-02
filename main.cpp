#include "camera/camera.h"
#include "factory/actors.h"
#include "factory/colors.h"
#include "factory/importers.h"
#include "factory/mappers.h"
#include "factory/panel/panel.h"
#include "factory/position/reader/position.h"
#include "factory/readers.h"

#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkPlaneSource.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSliderWidget.h>
#include <vtkSphereSource.h>

vtkStandardNewMacro(CustomMouseInteractorStyle);

int main(int argc, char *argv[]) {
  /*************** Defining colors ******************/
  std::vector<vtkColor3d> colorsVector = getColorsVector();

  /************** Reading OBJ files *****************/
  std::vector<vtkNew<vtkOBJReader>> readersVector = getReadersVector();

  /*************** Creating mappers *****************/
  std::vector<vtkNew<vtkPolyDataMapper>> mappersVector =
      getMappersVector(readersVector);

  /*************** Creating actors ******************/
  std::vector<vtkNew<vtkActor>> actorsVector =
      getActorsVector(mappersVector, colorsVector);

  /************* Customizing positions **************/
  customizeObjectsPositions(actorsVector);

  /************* Creating buttons panel *************/
  vtkNew<vtkActor> panelBackground =
      getPanelBackground(actorsVector[0]->GetCenter());
  std::vector<vtkNew<vtkActor>> panelButtonsVector =
      getPanelButtonsVector(panelBackground->GetCenter());

  /*************** Creating renderer ****************/
  vtkNew<vtkRenderer> renderer;
  for (const auto &actor : actorsVector) {
    renderer->AddActor(actor);
  }
  for (auto &panelButton : panelButtonsVector) {
    renderer->AddActor(panelButton);
  }
  renderer->AddActor(panelBackground);
  renderer->SetBackground(255, 255, 255);

  /************ Creating renderer window ************/
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Demo project");

  /******* Creating renderer window interactor ******/
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  /**** Creating renderer window interactor style ***/
  vtkNew<CustomMouseInteractorStyle> style;
  style->SetDefaultRenderer(renderer);
  for (auto &panelButton : panelButtonsVector) {
    style->buttons.emplace_back(std::make_pair(
        panelButton.Get(), CustomMouseInteractorStyle::ButtonStatus::InActive));
  }
  renderWindowInteractor->SetInteractorStyle(style);

  /* USER CODE BEGIN IMPORTER */
  auto importersVector = getImportersVector();
  for (auto &importer : importersVector) {
    importer->SetRenderWindow(renderWindow);
    importer->Update();
  }

  auto actors = renderer->GetActors();
  actors->InitTraversal();

  int normalActorLimit = actorsVector.size() + panelButtonsVector.size() + 1;
  for (int i = 0; i < normalActorLimit; ++i) {
    actors->GetNextActor();
  }

  int importerActorLimit = actors->GetNumberOfItems() - normalActorLimit;
  for (int i = 0; i < importerActorLimit; ++i) {
    std::cout << "Hello";
    vtkActor *actor = actors->GetNextActor();
    switch (i) {
    case 1: {
      actor->RotateX(-90);
      actor->SetScale(6);
      auto *coordinates = actorsVector[0]->GetCenter();
      coordinates[0] += 1250;
      coordinates[1] += 32;
      coordinates[2] += 2300;
      actor->SetPosition(coordinates);
      break;
    }
    case 3:{
      actor->SetScale(1200);
      actor->RotateY(87);
      auto *coordinates = actorsVector[0]->GetCenter();
      coordinates[0] += 4500;
      coordinates[1] += 1400;
      coordinates[2] += 2500;
      actor->SetPosition(coordinates);
    }
    }
  }
  /* USER CODE END IMPORTER */

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
