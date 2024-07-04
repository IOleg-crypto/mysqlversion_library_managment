cmake_minimum_required(VERSION 3.11)
project(MySQLLibrary VERSION 1.0.0)

add_executable(${PROJECT_NAME} mysql_connect.h library_table.sql Functionatlity.h mysqlversion_vs.cpp)

include_directories("C:\\Program Files\\MySQL\\mysql-connector-c++-8.4.0-winx64\\include")
include_directories("C:\\Program Files\\MySQL\\MySQL Server 8.0\\include")

link_directories("C:\\Program Files\\MySQL\\mysql-connector-c++-8.4.0-winx64\\lib64")
link_directories("C:\\Program Files\\MySQL\\MySQL Server 8.0\\lib")

add_library(mysqlcppconn STATIC IMPORTED GLOBAL)
add_library(libmysql STATIC IMPORTED GLOBAL)

# Set properties for the imported libraries
set_target_properties(mysqlcppconn PROPERTIES
    IMPORTED_LOCATION "${MYSQLCPPCONN_LIB}"
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
)

set_target_properties(libmysql PROPERTIES
    IMPORTED_LOCATION "${MYSQL_LIB}"
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
)

set_target_properties(libmysql PROPERTIES
    IMPORTED_IMPLIB "${MYSQL_LIB}"
    IMPORTED_LOCATION "C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.dll"
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
)

# Link libraries to the project
target_link_libraries(${PROJECT_NAME} mysqlcppconn libmysql)
# Link libraries to the project
target_link_libraries(${PROJECT_NAME} mysqlcppconn libmysql)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Specify the C++ standard (optional, but recommended)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure Visual Studio generates solution files
set(CMAKE_GENERATOR "Visual Studio 17 2022" CACHE STRING "CMake generator")