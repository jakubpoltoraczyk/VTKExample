#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkOBJReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <string>
#include <vector>

#include "position.h"

int main(int argc, char *argv[]) {
  /**************************************************/
  /*************** Defining colors ******************/
  /**************************************************/
  vtkNew<vtkNamedColors> colors;
  colors->SetColor("DeskColor", "#663300");
  colors->SetColor("TrumpetColor", "#CC9900");
  colors->SetColor("LampColor", "#E0E0E0");
  colors->SetColor("NotebookColor", "#C0C0C0");
  colors->SetColor("GlassColor", "#F0FFFF");
  colors->SetColor("BackgroundColor", "#FFFFFF");

  std::vector<vtkColor3d> colorsVector{
      colors->GetColor3d("DeskColor"), colors->GetColor3d("TrumpetColor"),
      colors->GetColor3d("LampColor"), colors->GetColor3d("NotebookColor"),
      colors->GetColor3d("GlassColor")};

  /**************************************************/
  /************** Reading OBJ files *****************/
  /**************************************************/
  std::vector<std::string> fileNames{
      "../images/desk.obj", "../images/trumpet.obj", "../images/lamp.obj",
      "../images/notebook.obj", "../images/glass.obj"};
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
  customizeGlassPosition(vectorActor[4], vectorActor[0]->GetCenter());

  /**************************************************/
  /*************** Rendering window *****************/
  /**************************************************/
  vtkNew<vtkRenderer> renderer;
  for (const auto &actor : vectorActor) {
    renderer->AddActor(actor);
  }
  renderer->SetBackground(colors->GetColor3d("BackgroundColor").GetData());

  vtkNew<vtkRenderWindow> renderWindow;
  renderWindow->AddRenderer(renderer);
  renderWindow->SetWindowName("Example");

  vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
  renderWindowInteractor->SetRenderWindow(renderWindow);

  renderWindow->SetSize(640, 480);
  renderWindow->Render();

  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}
