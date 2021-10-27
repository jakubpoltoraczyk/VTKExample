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
  colors->SetColor("TrumpetColor", "#CC9900");
  colors->SetColor("DeskColor", "#663300");
  colors->SetColor("BackgroundColor", "#FFFFFF");

  std::vector<vtkColor3d> colorsVector{colors->GetColor3d("TrumpetColor"),
                                 colors->GetColor3d("DeskColor"),
                                 colors->GetColor3d("BackgroundColor")};

  /* Reading OBJ file */
  std::vector<std::string> fileNames{"../trumpet.obj", "../desk.obj"};
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

  auto *coordinates = vectorActor[1]->GetCenter();
  coordinates[1] += 540;
  coordinates[2] += 100;
  vectorActor[0]->SetPosition(coordinates);
  vectorActor[0]->RotateZ(90);

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
