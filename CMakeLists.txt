cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
foreach(p CMP0071) # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    if(POLICY ${p})
        cmake_policy(SET ${p} NEW)
    endif()
endforeach()
project(color_picker)

find_package(Qt5 REQUIRED COMPONENTS Concurrent Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC
    colorview.cpp
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    colorview.h
    mainwindow.h
)

set(LIBS Qt5::Concurrent Qt5::Widgets)
add_executable(${CMAKE_PROJECT_NAME} ${SRC} ${HEADERS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})


