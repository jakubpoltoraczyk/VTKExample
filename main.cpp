#include "camera/camera.h"
#include "factory/actors.h"
#include "factory/colors.h"
#include "factory/importers.h"
#include "factory/mappers.h"
#include "factory/panel/panel.h"
#include "factory/position/importer/position.h"
#include "factory/position/reader/position.h"
#include "factory/readers.h"

#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkLight.h>
#include <vtkLightActor.h>
#include <vtkLightCollection.h>
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
  customizeReaderObjectsPositions(actorsVector);

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

  /************* Creating lighting ******************/
  vtkNew<vtkLight> mainLight;
  mainLight->SetPosition(actorsVector[12]->GetPosition()[0], 10000,
                         actorsVector[12]->GetPosition()[2]);
  mainLight->SetFocalPoint(actorsVector[12]->GetPosition());
  mainLight->SetColor(colorsVector[13].GetData());
  mainLight->SwitchOn();
  renderer->AddLight(mainLight);

  /************ Creating renderer window ************/
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Demo project");

  /******* Creating renderer window interactor ******/
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  /**** Creating renderer window interactor style ***/
  vtkNew<CustomMouseInteractorStyle> style;
  style->setMainLight(mainLight);
  style->SetDefaultRenderer(renderer);
  for (auto &panelButton : panelButtonsVector) {
    style->buttons.emplace_back(std::make_pair(
        panelButton.Get(), CustomMouseInteractorStyle::ButtonStatus::InActive));
  }
  renderWindowInteractor->SetInteractorStyle(style);

  /********* Management of importer objects *********/
  auto importersVector = getImportersVector();
  for (auto &importer : importersVector) {
    importer->SetRenderWindow(renderWindow);
    importer->Update();
  }

  auto actors = renderer->GetActors();
  actors->InitTraversal();
  int otherActorsSize = actorsVector.size() + panelButtonsVector.size() + 1;
  for (int i = 0; i < otherActorsSize; ++i) {
    actors->GetNextActor();
  }

  int importerActorsSize = actors->GetNumberOfItems() - otherActorsSize;
  customizeImporterObjectsPositions(actorsVector[0], actors,
                                    importerActorsSize);

  auto actors2 = renderer->GetActors();
  actors2->InitTraversal();
  for (int i = 0; i < otherActorsSize; ++i) {
    actors2->GetNextActor();
  }
  for (int i = 0; i < 4; ++i) {
    actors2->GetNextActor();
    style->walls.emplace_back(actors2->GetNextActor());
  }

  /************** Final preparations ***************/
  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
