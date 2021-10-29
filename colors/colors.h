#pragma once

#include <vtkNamedColors.h>
#include <vtkNew.h>

#include <vector>

std::vector<vtkColor3d> getColorsVector() {
  vtkNew<vtkNamedColors> colors;
  colors->SetColor("DeskColor", "#663300");
  colors->SetColor("TrumpetColor", "#CC9900");
  colors->SetColor("LampColor", "#E0E0E0");
  colors->SetColor("NotebookColor", "#C0FAFA");
  colors->SetColor("CupColor", "#FEFEFE");
  colors->SetColor("PillColorRed", "#E78686");
  colors->SetColor("PillColorGreen", "#A0EAAB");
  colors->SetColor("PillBottle", "#FFFFFF");
  colors->SetColor("Floor", "#E1E5E5");
  colors->SetColor("Chair", "#404747");
  colors->SetColor("CoffeTable", " 	#A0522D");
  colors->SetColor("Bed", "#FFFFE0");

  return {
      colors->GetColor3d("DeskColor"),    colors->GetColor3d("TrumpetColor"),
      colors->GetColor3d("LampColor"),    colors->GetColor3d("NotebookColor"),
      colors->GetColor3d("CupColor"),     colors->GetColor3d("PillColorRed"),
      colors->GetColor3d("PillColorRed"), colors->GetColor3d("PillColorGreen"),
      colors->GetColor3d("PillColorRed"), colors->GetColor3d("PillColorGreen"),
      colors->GetColor3d("PillColorRed"), colors->GetColor3d("PillBottle"),
      colors->GetColor3d("Floor"),        colors->GetColor3d("Chair"),
      colors->GetColor3d("CoffeTable"), colors->GetColor3d("Bed")};
}