cmake_minimum_required(VERSION 3.16)

project(test1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(test1
  main.cpp
  map_old.h map_old.cpp
  location_old.h
  location_old.cpp
  game.h game.cpp
  player.h player.cpp
  map_renderer.h map_renderer.cpp
  enemy.h enemy.cpp
  items.h items.cpp
  battle.h battle.cpp
  achievements.h achievements.cpp
  skills.h skills.cpp
  class_skills.h class_skills.cpp
  save.h save.cpp
)
target_link_libraries(test1 Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS test1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



