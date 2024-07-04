![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91.svg?style=for-the-badge&logo=visual-studio&logoColor=white)
![VSCode](https://img.shields.io/badge/Vscode-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white)
![Sublime Text](https://img.shields.io/badge/sublime_text-%23575757.svg?style=for-the-badge&logo=sublime-text&logoColor=important)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Windows Terminal](https://img.shields.io/badge/Windows%20Terminal-%234D4D4D.svg?style=for-the-badge&logo=windows-terminal&logoColor=white)
![Subtext](https://img.shields.io/badge/sublime%20text-%23FF9800.svg?&style=for-the-badge&logo=sublime%20text&logoColor=black)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)
![Windows](https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)
![Win](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white")
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# MySQL Connector + C++ Project(Library Management)

This project demonstrates how to connect to a MySQL database using C++ and the MySQL Connector. It includes basic operations such as connecting to the database, executing queries, and fetching results.

## Requirements

- C++ Compiler (e.g., `g++` from MinGW or MSYS2 on Windows)
- MySQL Server
- MySQL Connector/C++ libraries
- CMake (optional, if you use a build system)
- Visual Studio Code (optional, for code editing and task management)

## Setup

### Install MySQL Server

1. Download and install MySQL Server from the [official website](https://dev.mysql.com/downloads/mysql/).
2. Set up your MySQL instance and note down the username, password, and database name.

### Install MySQL Connector/C++

1. Download and install MySQL Connector/C++ from the [official website](https://dev.mysql.com/downloads/connector/cpp/).
2. Make sure to note the installation directory as you will need to link against these libraries.

### Install MSYS2 (for Windows users)

1. Download and install MSYS2 from the [official website](https://www.msys2.org/).
2. Open MSYS2 terminal and update the package database:

   ```sh

   pacman -Syu

   ```

### To build in Visual Studio Code

Use `CTRL + SHIFT + B` or `CTRL + SHIFT + P` -> Run Build Task

# Tasks.json (_Complier args_)

![Tasks.json](image.png)

# c*cpp_properties(\_Include path*)

![C_CPP_Properties](image-1.png)

After that you may be able to run **mysqlversion_vs.exe**

```sh
start mysqlversion_vs.exe
```

# CMake

**To compile**

'''sh
cd mysqlversion_vs
cmake .
cd build
make
'''
!Don't forget `libmysql.dll`(without .dll the program will not start)

![alt text](image-2.png)

Replace `"username"`, `"password"`, and `"database_name"` with your actual MySQL credentials and database name in the sample code.
