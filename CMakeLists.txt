cmake_minimum_required(VERSION 3.20)
project(Airline)

set(CMAKE_CXX_STANDARD 14)

add_executable(Airline main.cpp air_line/Flight.cpp air_line/Flight.h air_line/Airplane.cpp air_line/Airplane.h air_line/Service.cpp air_line/Service.h air_line/Passenger.cpp air_line/Passenger.h air_line/Date.cpp air_line/Date.h air_line/Schedule.cpp air_line/Schedule.h air_line/Time.cpp air_line/Time.h air_line/Airline.cpp air_line/Airline.h)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
        COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)