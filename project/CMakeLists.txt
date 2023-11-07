cmake_minimum_required(VERSION 3.6)
project(Chess)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH
    "src/CMAKE/cmake_modules"
     ${CMAKE_MODULE_PATH})

find_package(SFML COMPONENTS system window graphics REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Chess  src/Main.cpp
					src/Field.cpp
					src/Field.h
					src/figure.cpp
					src/figure.h
					src/GameManager.cpp
					src/GameManager.h
					src/color_rect_changer.h
					src/SimpleButton.h
					src/CenteredText.h
					src/resources.h)


FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/textures"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/fonts"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

if (WIN32)

	include_directories(${SFML_INCLUDE_DIR})


	FILE(
		COPY "${SFML_ROOT}/bin/sfml-graphics-2.dll"
		DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
	)

	FILE(
		COPY "${SFML_ROOT}/bin/sfml-window-2.dll"
		DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
	)

	FILE(
		COPY "${SFML_ROOT}/bin/sfml-system-2.dll"
		DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
	)


	target_link_libraries(Chess  ${SFML_LIBRARIES})
else (WIN32)

	include_directories("${SFML_ROOT}/include")

	target_link_libraries(Chess  ${SFML_LIBRARIES} sfml-graphics sfml-window sfml-system)
	
endif (WIN32)


