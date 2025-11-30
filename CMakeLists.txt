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
  entity.h entity.cpp
  enums.h enums.cpp
  item.h item.cpp
  weapon.h weapon.cpp
  armor.h armor.cpp
  skills_1_2.h skills_1_2.cpp
  trainer_1_2.h trainer_1_2.cpp
  achievement_1_2.h achievement_1_2.cpp
  enemy_1_2.h enemy_1_2.cpp
  location_1_2.h location_1_2.cpp
  dungeon_1_2.h dungeon_1_2.cpp
  achievementsystem.h achievementsystem.cpp
  gameworld.h gameworld.cpp
  player_1_2.h player_1_2.cpp
  gamemap.h gamemap.cpp
  battleengine.h battleengine.cpp
  savesystem.h savesystem.cpp
  gameengine.h gameengine.cpp
)
target_link_libraries(test1 Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS test1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)



