cmake_minimum_required(VERSION 3.16)
project(Chess  LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

add_executable(Chess  src/Main.cpp
					src/Field.cpp
					src/Field.h
					src/figure.cpp
					src/figure.h
					src/GameManager.cpp
					src/GameManager.h
					src/color_rect_changer.h
					src/SimpleButton.h
					src/resources.h)
target_link_libraries(Chess  PRIVATE sfml-graphics)
target_compile_features(Chess  PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET Chess
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Chess>
        VERBATIM)
endif()

FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/textures"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/fonts"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)
install(TARGETS Chess)
