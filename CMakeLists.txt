cmake_minimum_required(VERSION 3.2)

project(EconomicEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (HEADERS
    ${HEADER_DIR}/Agent.h
    ${HEADER_DIR}/Engine.h
    ${HEADER_DIR}/EngineFactory.h
    ${HEADER_DIR}/Entity.h
    ${HEADER_DIR}/Farmer.h
    ${HEADER_DIR}/GameObject.h
    ${HEADER_DIR}/Job.h
    ${HEADER_DIR}/Parser.h
    ${HEADER_DIR}/Simulation.h
    ${HEADER_DIR}/WoodCutter.h
)

set (SOURCES
    ${SOURCE_DIR}/Agent.cpp
    ${SOURCE_DIR}/Engine.cpp
    ${SOURCE_DIR}/Entity.cpp
    ${SOURCE_DIR}/Farmer.cpp
    ${SOURCE_DIR}/GameObject.cpp
    ${SOURCE_DIR}/Job.cpp
    ${SOURCE_DIR}/Parser.cpp
    ${SOURCE_DIR}/Simulation.cpp
    ${SOURCE_DIR}/WoodCutter.cpp
    EconomicEngine.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_auto_type)
target_include_directories(${PROJECT_NAME} PUBLIC
    "."
    ${HEADER_DIR}
)
