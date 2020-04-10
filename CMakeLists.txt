cmake_minimum_required(VERSION 3.2)

project(EconomicEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

set (HEADERS
    ${HEADER_DIR}/Core/Signal.h
    ${HEADER_DIR}/Core/Entity.h
    ${HEADER_DIR}/Core/GameObject.h
    ${HEADER_DIR}/Engine/Engine.h
    ${HEADER_DIR}/Engine/Parser.h
    ${HEADER_DIR}/Engine/EngineFactory.h
    ${HEADER_DIR}/Engine/json.hpp
    ${HEADER_DIR}/Simulation/Simulation.h
    ${HEADER_DIR}/Simulation/Agent/Agent.h
    ${HEADER_DIR}/Simulation/Jobs/Base/Job.h
    ${HEADER_DIR}/Simulation/Jobs/Implementations/Farmer.h
    ${HEADER_DIR}/Simulation/Jobs/Implementations/WoodCutter.h
)

set (SOURCES
    ${SOURCE_DIR}/Core/Signal.cpp
    ${SOURCE_DIR}/Core/Entity.cpp
    ${SOURCE_DIR}/Core/GameObject.cpp
    ${SOURCE_DIR}/Engine/Engine.cpp
    ${SOURCE_DIR}/Engine/Parser.cpp
    ${SOURCE_DIR}/Simulation/Simulation.cpp
    ${SOURCE_DIR}/Simulation/Agent/Agent.cpp
    ${SOURCE_DIR}/Simulation/Jobs/Base/Job.cpp
    ${SOURCE_DIR}/Simulation/Jobs/Implementations/Farmer.cpp
    ${SOURCE_DIR}/Simulation/Jobs/Implementations/WoodCutter.cpp
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
