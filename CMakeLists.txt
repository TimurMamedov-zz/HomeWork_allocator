cmake_minimum_required (VERSION 3.2)

#project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
project(allocator)

#SET (BOOST_ROOT "C:/Library/boost_1_62_0")
#SET (BOOST_INCLUDEDIR "C:/Library/boost_1_62_0/boost")
#SET (BOOST_LIBRARYDIR "C:/Library/boost_1_62_0/stage/lib")
#SET (Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)

#find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

#set(SOURCES CustomContainer.cpp)
set(HEADERS CustomAllocator.h ChunkPool.h functions.h CustomContainer.h)

add_executable(allocator ${HEADERS} ${SOURCES} main.cpp)

#set (TEST test_allocator)
#add_executable (${TEST} test_allocator.cpp)

set_target_properties (allocator ${TEST} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

#set_target_properties (${TEST} PROPERTIES
#        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#)

#target_link_libraries(${TEST}
#        ${Boost_LIBRARIES}
#)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tima_mamedxp@mail.ru)

include(CPack)

#enable_testing()

#add_test (${TEST} ${TEST})
