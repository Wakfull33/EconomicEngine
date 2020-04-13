cmake_minimum_required(VERSION 3.2)

project(EconomicEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

set (HEADERS
    ${HEADER_DIR}/Core/Signal.h
    ${HEADER_DIR}/Core/StructUtils.h
    ${HEADER_DIR}/Core/GameplayStatics.h
    ${HEADER_DIR}/Engine/Engine.h
    ${HEADER_DIR}/Engine/Parser/Parser.h
    ${HEADER_DIR}/Engine/Parser/Json.h
    ${HEADER_DIR}/Engine/Parser/Librairy/json.hpp
    ${HEADER_DIR}/Simulation/Event.h
    ${HEADER_DIR}/Simulation/Simulation.h
    ${HEADER_DIR}/Simulation/ObjectManager.h
    ${HEADER_DIR}/Simulation/Agent/Agent.h
    ${HEADER_DIR}/Simulation/Global/GameMode.h
)

set (SOURCES
    ${SOURCE_DIR}/Core/GameplayStatics.cpp
    ${SOURCE_DIR}/Engine/Engine.cpp
    ${SOURCE_DIR}/Engine/Parser/Json.cpp
    ${SOURCE_DIR}/Simulation/Event.cpp
    ${SOURCE_DIR}/Simulation/Simulation.cpp
    ${SOURCE_DIR}/Simulation/Agent/Agent.cpp
    ${SOURCE_DIR}/Simulation/Global/GameMode.cpp
    EconomicEngine.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_auto_type)
target_include_directories(${PROJECT_NAME} 
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
  PRIVATE
    ${SOURCE_DIR}
)
