set(ATSDB_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
message("  Path: ${ATSDB_PATH}")

cmake_minimum_required(VERSION 3.1)

set ( CMAKE_BUILD_TYPE RelWithDebInfo ) #Debug RelWithDebInfo Release

project( ATSDB )
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "5")
SET(CPACK_PACKAGE_VERSION_PATCH "1")

message("  System: ${CMAKE_SYSTEM}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message("  Platform: Linux")
add_definitions ( -UNDEBUG -Wall -std=c++11)

#-Wno-deprecated-declarations -Wno-ignored-attributes -Wno-misleading-indentation for new compiler and old libs
# -UNDEBUG for enabling asserts in release buils (until testing/error management is improved)

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5OpenGL)

message("Qt Widgets version: ${Qt5Widgets_VERSION}")

set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#add_definitions(${Qt5Widgets_DEFINITIONS})
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

find_package ( Boost REQUIRED COMPONENTS regex system program_options filesystem iostreams)
message("  Boost_INCLUDE_DIR: ${Boost_INCLUDE_DIR}")
message("  Boost_LIBRARY_DIR: ${Boost_LIBRARY_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${ATSDB_PATH}/cmake_modules)
message("  CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}") 

find_package (Eigen3 3.2 REQUIRED)

find_package ( MySQLpp REQUIRED )
message("  MySQLpp_INCLUDE_DIR: ${MySQLpp_INCLUDE_DIR}") 
message("  MySQLpp_LIBRARY: ${MySQLpp_LIBRARY}") 

find_package ( MySQL REQUIRED )
message("  MYSQL_INCLUDE_DIR: ${MYSQL_INCLUDE_DIR}")
message("  MYSQL_LIBRARY: ${MYSQL_LIBRARY}")

find_package ( Sqlite3 REQUIRED )
message("  SQLite3_INCLUDE_DIR: ${SQLITE3_INCLUDE_DIR}")
message("  SQLite3_LIBRARY_DIR: ${SQLITE3_LIBRARIES}")

find_package ( LOG4CPP REQUIRED )
message("  LOG4CPP_INCLUDE_DIR: ${LOG4CPP_INCLUDE_DIR}")
message("  LOG4CPP_LIBRARY: ${LOG4CPP_LIBRARIES}") 

find_package ( GDAL REQUIRED )
message("  GDAL_INCLUDE_DIRS: ${GDAL_INCLUDE_DIRS}")
message("  GDAL_LIBRARIES: ${GDAL_LIBRARIES}")

#find_package ( TinyXML2 REQUIRED )
#message("  TINYXML2_INCLUDE_DIR: ${TINYXML2_INCLUDE_DIR}")
#message("  TINYXML2_LIBRARY: ${TINYXML2_LIBRARY}")

find_package ( LibArchive REQUIRED )
message("  LibArchive_INCLUDE_DIRS: ${LibArchive_INCLUDE_DIRS}")
message("  LibArchive_LIBRARIES: ${LibArchive_LIBRARIES}")

find_package(TBB REQUIRED)
message("  TBB_INCLUDE_DIRS: ${TBB_INCLUDE_DIRS}")
message("  TBB_LIBRARIES: ${TBB_LIBRARIES}")

find_package ( jASTERIX )
message("  jASTERIX found: ${jASTERIX_FOUND}")
message("  jASTERIX_INCLUDE_DIR: ${jASTERIX_INCLUDE_DIR}")
message("  jASTERIX_LIBRARIES: ${jASTERIX_LIBRARIES}")

find_package ( OpenSSL REQUIRED )
message("  OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
message("  OPENSSL_CRYPTO_LIBRARY: ${OPENSSL_CRYPTO_LIBRARY}")

#find_package ( JSONCPP REQUIRED )
#message("  JSONCPP_INCLUDE_DIR: ${JSONCPP_INCLUDE_DIR}")
#message("  JSONCPP_LIBRARY: ${JSONCPP_LIBRARY}")


add_library(atsdb "")

message("Install path: ${CMAKE_INSTALL_PREFIX}")

include(src/CMakeLists.txt)

set (EXPERIMENTAL_SRC true)
message("Experimental source: ${EXPERIMENTAL_SRC}")

IF (EXPERIMENTAL_SRC)
    IF(IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/experimental_src")
        MESSAGE(STATUS "Experimental source found")
    ELSE()
        MESSAGE(STATUS "Experimental source not found found, deactivating")
        set (EXPERIMENTAL_SRC false)
    ENDIF()
ENDIF()

IF (EXPERIMENTAL_SRC)
    MESSAGE(STATUS "Including experimental source")
    include(experimental_src/CMakeLists.txt)
ENDIF()

configure_file(src/util/global.h.in include/global.h)

# includes and library linking

include_directories (
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/include
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5OpenGL_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${SQLITE3_INCLUDE_DIR}
    ${MYSQL_INCLUDE_DIR}
    ${MySQLpp_INCLUDE_DIR}
    ${LOG4CPP_INCLUDE_DIR}
    ${GDAL_INCLUDE_DIRS}
#    ${TINYXML2_INCLUDE_DIR}
    ${OPENSCENEGRAPH_INCLUDE_DIRS}
    ${LibArchive_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${JSONCPP_INCLUDE_DIR}
    )

link_directories(
    ${Boost_LIBRARY_DIR}
    )

IF (jASTERIX_FOUND)
include_directories (
    ${jASTERIX_INCLUDE_DIR}
    )

link_directories(
    ${jASTERIX_LIBRARIES}
    )

target_link_libraries ( atsdb optimized
    ${jASTERIX_LIBRARIES})
ENDIF()

target_link_libraries ( atsdb optimized
    Qt5::Widgets
    Qt5::Core
    Qt5::OpenGL
    ${Boost_LIBRARIES}
    ${LOG4CPP_LIBRARIES}
    ${MySQLpp_LIBRARY}
    ${MYSQL_LIBRARY}
    ${GDAL_LIBRARIES}
    ${SQLITE3_LIBRARIES}
    ${LibArchive_LIBRARIES}
    ${JSONCPP_LIBRARY}
    ${TBB_LIBRARIES}
    ${OPENSSL_CRYPTO_LIBRARY}
    )


# installation stuff

message("Installing using prefix: ${CMAKE_INSTALL_PREFIX}")
install(DIRECTORY "conf" DESTINATION atsdb)
install(DIRECTORY "data" DESTINATION atsdb)

install (TARGETS atsdb DESTINATION lib
    PUBLIC_HEADER DESTINATION include/atsdb)

install (TARGETS atsdb_client DESTINATION bin)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include (CPack)


# add a target to generate API documentation with Doxygen
#find_package(Doxygen)
#if(DOXYGEN_FOUND)
#    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in @ONLY)
#    add_custom_target(doc
#        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
#        COMMENT "Generating API documentation with Doxygen" VERBATIM
#        )
#endif(DOXYGEN_FOUND)

#file(GLOB DOT ".*")
#file(GLOB TILD "*~")
#file(GLOB TEMP "*.cmake")





