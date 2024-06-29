cmake_minimum_required(VERSION 3.16.0)
project(MyLibraryManagementSQL VERSION 0.1.0)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Установка исходных файлов
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")
add_executable(MyLibraryManagementSQL ${SOURCES})

# Проверка, что файлы найдены
if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in the src directory")
endif()

# Добавление директории с заголовочными файлами
include_directories("C:/Program Files/MySQL/mysql-connector-c++-8.4.0-winx64/include")
include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")

# Добавление директории с библиотеками
link_directories("C:/Program Files/MySQL/mysql-connector-c++-8.4.0-winx64/lib64")
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")

# Создание исполняемого файла

# Линковка с библиотеками MySQL

# Путь к дополнительным библиотекам
find_library(MYSQL_LIB NAMES mysqlcppconn PATHS "C:/Program Files/MySQL/mysql-connector-c++-8.4.0-winx64/lib64")
find_library(MYSQL_SERVER_LIB NAMES mysqlclient PATHS "C:/Program Files/MySQL/MySQL Server 8.0/lib")

# Линковка с дополнительными библиотеками, если они найдены
if(MYSQL_LIB)
target_link_libraries(MyLibraryManagementSQL ${MYSQL_LIB})
else()
message(WARNING "MySQL Connector library not found")
endif()

if(MYSQL_SERVER_LIB)
target_link_libraries(MyLibraryManagementSQL ${MYSQL_SERVER_LIB})
else()
message(WARNING "MySQL Server library not found")
endif()

target_link_libraries(MyLibraryManagementSQL mysqlcppconn)