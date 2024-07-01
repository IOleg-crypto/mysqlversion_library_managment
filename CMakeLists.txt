cmake_minimum_required(VERSION 3.11)
project(MySQLLibrary VERSION 1.0.0)

add_executable(${PROJECT_NAME} mysql_connect.h library_table.sql Functionatlity.h mysqlversion_vs.cpp)

include_directories("C:\\Program Files\\MySQL\\mysql-connector-c++-8.4.0-winx64\\include")
include_directories("C:\\Program Files\\MySQL\\MySQL Server 8.0\\include")

link_directories("C:\\Program Files\\MySQL\\mysql-connector-c++-8.4.0-winx64\\lib64")
link_directories("C:\\Program Files\\MySQL\\MySQL Server 8.0\\lib")

#target_link_libraries(${PROJECT_NAME} "C:\\Program Files\\MySQL\\mysql-connector-c++-8.4.0-winx64\\lib64\\mysqlcppconn.dll")
#target_link_libraries(${PROJECT_NAME} "C:\\Program Files\\MySQL\\MySQL Server 8.0\\lib\\libmysql.dll")

find_library(MYSQLCPPCONN_LIB NAMES mysqlcppconn PATHS "C:/Program Files/MySQL/mysql-connector-c++-8.4.0-winx64/lib64")
find_library(MYSQL_LIB NAMES libmysql PATHS "C:/Program Files/MySQL/MySQL Server 8.0/lib")

# Link libraries to the project
target_link_libraries(MySQLLibrary C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib C:/Program Files/MySQL/mysql-connector-c++-8.4.0-winx64/lib64/libmysqlcppconn.lib)



#set_target_properties(MySQLLibrary PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON IMPORTED_LOCATION "C:\\Program Files\\MySQL\\mysql-connector-c++-8.4.0-winx64\\lib64\\libmysqlcppconn.lib") 
#set_target_properties(MySQLLibrary PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON IMPORTED_LOCATION "C:\\Program Files\\MySQL\\MySQL Server 8.0\\lib\\libmysql.lib")

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()