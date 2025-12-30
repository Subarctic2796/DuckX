cmake_minimum_required(VERSION 3.31)

project(duckx VERSION 1.2.3)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_SAMPLES "Build provided samples" OFF)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES src/duckx.cpp
	    src/thirdparty/zip/zip.c)

if(BUILD_SHARED_LIBS)
    add_library(duckx SHARED ${SOURCES})
else()
    add_library(duckx STATIC ${SOURCES})
endif()

add_library(duckx::duckx ALIAS duckx)

target_include_directories(duckx PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

mark_as_advanced(CLEAR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR)

if (BUILD_SAMPLES)
	# Sample executable
	set(SAMPLE1_SOURCES samples/sample1.cpp)
	add_executable(duckx_sample1 ${SAMPLE1_SOURCES})
	target_link_libraries(duckx_sample1 duckx)

	set(SAMPLE2_SOURCES samples/sample2.cpp)
	add_executable(duckx_sample2 ${SAMPLE2_SOURCES})
	target_link_libraries(duckx_sample2 duckx)

        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/samples/my_test.docx
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

include(GNUInstallDirs)
install(
    TARGETS duckx
    EXPORT duckxConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(EXPORT duckxConfig NAMESPACE duckx:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/duckx)
install(FILES ${HEADERS} DESTINATION include/duckx)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
	enable_testing()
	add_subdirectory(test)
endif()

