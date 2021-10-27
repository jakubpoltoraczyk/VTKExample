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

int main(int argc, char *argv[]) {
  /* Defining colors structure */
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

  /* Reading OBJ file */
  std::vector<std::string> fileNames{"../desk.obj", "../trumpet.obj",
                                     "../lamp.obj", "../notebook.obj",
                                     "../glass.obj"};
  std::vector<vtkNew<vtkOBJReader>> vectorReader;
  for (const auto &fileName : fileNames) {
    vtkNew<vtkOBJReader> reader;
    reader->SetFileName(fileName.c_str());
    reader->Update();
    vectorReader.emplace_back(std::move(reader));
  }

  /* Creating mapper */
  std::vector<vtkNew<vtkPolyDataMapper>> vectorMapper;
  for (const auto &reader : vectorReader) {
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    vectorMapper.emplace_back(std::move(mapper));
  }

  /* Creating actor */
  std::vector<vtkNew<vtkActor>> vectorActor;
  for (int i = 0; i < vectorMapper.size(); ++i) {
    vtkNew<vtkActor> actor;
    actor->SetMapper(vectorMapper[i]);
    actor->GetProperty()->SetColor(colorsVector[i].GetData());
    vectorActor.emplace_back(std::move(actor));
  }

  /* Moving desk */
  vectorActor[0]->RotateY(180);

  /* Moving trumpet */
  vectorActor[1]->RotateZ(90);
  auto *coordinates = vectorActor[0]->GetCenter();
  coordinates[0] += 100;
  coordinates[1] += 540;
  coordinates[2] += 250;
  vectorActor[1]->SetPosition(coordinates);

  /* Moving lamp */
  vectorActor[2]->RotateY(45);
  coordinates = vectorActor[0]->GetCenter();
  coordinates[0] -= 500;
  coordinates[1] += 480;
  coordinates[2] -= 150;
  vectorActor[2]->SetPosition(coordinates);

  /* Moving monitor */
  vectorActor[3]->SetScale(180);
  vectorActor[3]->RotateY(90);
  coordinates = vectorActor[0]->GetCenter();
  coordinates[1] += 500;
  vectorActor[3]->SetPosition(coordinates);

  /* Moving glass */
  vectorActor[4]->SetScale(0.8);
  coordinates = vectorActor[0]->GetCenter();
  coordinates[0] -= 500;
  coordinates[1] += 450;
  coordinates[2] += 250;
  vectorActor[4]->SetPosition(coordinates);

  /* Rendering window */
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
