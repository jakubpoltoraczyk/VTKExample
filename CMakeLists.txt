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
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkCommonDataModel
  QUIET
)

add_executable(${PROJECT_NAME}
  factory/position/reader/position.cpp
  factory/position/importer/position.cpp
  factory/panel/panel.cpp
  camera/camera.cpp
  main.cpp 
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE ${VTK_LIBRARIES}
)

vtk_module_autoinit(
  TARGETS demo
  MODULES ${VTK_LIBRARIES}
)
