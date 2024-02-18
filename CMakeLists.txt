if(WIN32)
    set(TgbotLib TgBot.lib)
    if (EXISTS $ENV{APPDATA}/../Local/vcpkg/vcpkg.path.txt)
        set(FILE $ENV{APPDATA}/../Local/vcpkg/vcpkg.path.txt)
        file(READ ${FILE} FILE_CONTENTS)
        set(CMAKE_TOOLCHAIN_FILE ${FILE_CONTENTS}/scripts/buildsystems/vcpkg.cmake)
    else()
        set(FILE $ENV{LOCALAPPDATA}/vcpkg/vcpkg.path.txt)
        file(READ ${FILE} FILE_CONTENTS)
        set(CMAKE_TOOLCHAIN_FILE ${FILE_CONTENTS}/scripts/buildsystems/vcpkg.cmake)
    endif()
else()
    set(TgbotLib libTgBot.a)
    if (EXISTS $ENV{HOME}/.vcpkg/vcpkg.path.txt)
        set(FILE $ENV{HOME}/.vcpkg/vcpkg.path.txt)
        file(READ ${FILE} FILE_CONTENTS)
        set(CMAKE_TOOLCHAIN_FILE ${FILE_CONTENTS}/scripts/buildsystems/vcpkg.cmake)
    else()
        set(FILE /var/.vcpkg/vcpkg.path.txt)
        file(READ ${FILE} FILE_CONTENTS)
        set(CMAKE_TOOLCHAIN_FILE ${FILE_CONTENTS}/scripts/buildsystems/vcpkg.cmake)
    endif()
endif()
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)

cmake_minimum_required(VERSION 3.23)
project(WeatherBot)
set(CMAKE_CXX_STANDARD 20)
set(path ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib/${TgbotLib})

set(DEP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/WeatherBot/dependencies)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/WeatherBot/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/WeatherBot/headers)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.cpp")

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
find_package(cpr REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    add_custom_target(
            documentation
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )
endif()

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

include_directories(include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${DEP_DIR})

add_executable(WeatherBot WeatherBot/main.cpp)
target_sources(WeatherBot PUBLIC ${PROJECT_SOURCES})
target_include_directories(WeatherBot PUBLIC ${HEADER_DIR} ${DEP_DIR})
target_link_libraries(WeatherBot cpr::cpr ${path} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} unofficial::sqlite3::sqlite3)
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/res/.env
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} DESTINATION ${CMAKE_INSTALL_PREFIX})   
