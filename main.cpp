#include <algorithm>

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

vtkStandardNewMacro(CustomInteractorStyle);

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
  mainLight->SetColor(colorsVector[15].GetData());
  mainLight->SetIntensity(0.25);
  mainLight->PositionalOn();
  renderer->AddLight(mainLight);

  /* Read ToDo about lamp light

  vtkNew<vtkLight> lampLight;
  lampLight->SetPosition(actorsVector[2]->GetPosition()[0],
                         actorsVector[2]->GetPosition()[1] + 500,
                         actorsVector[2]->GetPosition()[2]);
  lampLight->SetFocalPoint(actorsVector[2]->GetPosition());
  lampLight->SetColor(colorsVector[15].GetData());
  lampLight->SetIntensity(1);
  lampLight->PositionalOn();
  renderer->AddLight(lampLight);
  std::cout << lampLight->GetLightType();
*/
  /************ Creating renderer window ************/
  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Demo project");

  /******* Creating renderer window interactor ******/
  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  /**** Creating renderer window interactor style ***/
  vtkNew<CustomInteractorStyle> style;
  style->setMainLight(mainLight);
  style->SetDefaultRenderer(renderer);
  for (auto &panelButton : panelButtonsVector) {
    style->buttons.emplace_back(std::make_pair(
        panelButton.Get(), CustomInteractorStyle::ButtonStatus::InActive));
  }
  std::transform(actorsVector.begin(), actorsVector.end(),
                 std::back_inserter(style->Actors),
                 [](vtkActor *a) { return a; });
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
  mainLight->SwitchOn();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
