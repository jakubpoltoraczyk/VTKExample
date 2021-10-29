
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(demo)

find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkFiltersSources
  vtkIOGeometry
  vtkIOImport
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingContext2D
  vtkViewsContext2D
  vtkRenderingContextOpenGL2
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkInteractionStyle
  vtkRenderingOpenGL2
  QUIET
)

add_executable(${PROJECT_NAME} 
  position/position.cpp
  main.cpp 
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS demo
  MODULES ${VTK_LIBRARIES}
)
