#include "camera/camera.h"
#include "colors/colors.h"
#include "position/position.h"
#include "factory/importer.h"

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
  /**************************************************/
  /*************** Defining colors ******************/
  /**************************************************/

  std::vector<vtkColor3d> colorsVector = getColorsVector();

  /**************************************************/
  /************** Reading OBJ files *****************/
  /**************************************************/
  std::vector<std::string> fileNames{
      "../images/desk.obj",       "../images/trumpet.obj",
      "../images/lamp.obj",       "../images/notebook.obj",
      "../images/cup.obj",        "../images/pill.obj",
      "../images/pill.obj",       "../images/pill.obj",
      "../images/pill.obj",       "../images/pill.obj",
      "../images/pill.obj",       "../images/pillbottle.obj",
      "../images/floor.obj",      "../images/chair.obj",
      "../images/coffetable.obj", "../images/bed.obj",
      "../images/book.obj",       "../images/book.obj",
      "../images/pen.obj"};
  std::vector<vtkNew<vtkOBJReader>> vectorReader;
  for (const auto &fileName : fileNames) {
    vtkNew<vtkOBJReader> reader;
    reader->SetFileName(fileName.c_str());
    reader->Update();
    vectorReader.emplace_back(std::move(reader));
  }

  /**************************************************/
  /*************** Creating mappers *****************/
  /**************************************************/
  std::vector<vtkNew<vtkPolyDataMapper>> vectorMapper;
  for (const auto &reader : vectorReader) {
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    vectorMapper.emplace_back(std::move(mapper));
  }

  /**************************************************/
  /*************** Creating actors ******************/
  /**************************************************/
  std::vector<vtkNew<vtkActor>> vectorActor;
  for (int i = 0; i < vectorMapper.size(); ++i) {
    vtkNew<vtkActor> actor;
    actor->SetMapper(vectorMapper[i]);
    actor->GetProperty()->SetColor(colorsVector[i].GetData());
    vectorActor.emplace_back(std::move(actor));
  }

  /**************************************************/
  /************* Customizing positions **************/
  /**************************************************/
  customizeDeskPosition(vectorActor[0], vectorActor[0]->GetCenter());
  customizeTrumpetPosition(vectorActor[1], vectorActor[0]->GetCenter());
  customizeLampPosition(vectorActor[2], vectorActor[0]->GetCenter());
  customizeNotebookPosition(vectorActor[3], vectorActor[0]->GetCenter());
  customizeCupPosition(vectorActor[4], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[5], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[6], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[7], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[8], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[9], vectorActor[0]->GetCenter());
  customizePillPosition(vectorActor[10], vectorActor[0]->GetCenter());
  customizePillBottle(vectorActor[11], vectorActor[0]->GetCenter());
  customizeFloor(vectorActor[12], vectorActor[0]->GetCenter());
  customizeChair(vectorActor[13], vectorActor[0]->GetCenter());
  customizeCoffeTable(vectorActor[14], vectorActor[0]->GetCenter());
  customizeBed(vectorActor[15], vectorActor[0]->GetCenter());
  customizeBook(vectorActor[16], vectorActor[0]->GetCenter());
  customizeBook(vectorActor[17], vectorActor[0]->GetCenter());
  customizePen(vectorActor[18], vectorActor[0]->GetCenter());

  /**************************************************/
  /*************** Rendering window *****************/
  /**************************************************/
  vtkNew<vtkRenderer> renderer;
  for (const auto &actor : vectorActor) {
    renderer->AddActor(actor);
  }
  renderer->SetBackground(255, 255, 255);

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Example");

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

  vtkActor *actor = actors->GetLastActor();
  actor->RotateX(-90);
  actor->SetScale(6);
  auto * coordinates = vectorActor[0]->GetCenter();
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
