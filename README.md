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
![Win](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# MySQL Connector + C++ Project (Library Management)

This project demonstrates how to connect to a MySQL database using C++ and the MySQL Connector/C++ library. It includes basic operations such as connecting to the database, executing queries, and fetching results.

## Requirements

- **C++ Compiler** (e.g., `g++` from MinGW or MSYS2 on Windows)
- **MySQL Server**
- **MySQL Connector/C++ libraries**
- **CMake** (optional, for build system)
- **Visual Studio Code** (optional, for code editing and task management)
- **Windows Terminal** (optional, for running commands)

## Setup Instructions

### Install MySQL Server

1. Download and install MySQL Server from the [official website](https://dev.mysql.com/downloads/mysql/).
2. Set up your MySQL instance and note down the **username**, **password**, and **database name**.

### Install MySQL Connector/C++

1. Download and install MySQL Connector/C++ from the [official website](https://dev.mysql.com/downloads/connector/cpp/).
2. Make sure to note the **installation directory** as you'll need to link the libraries in your project.

### Install MSYS2 (For Windows Users)

1. Download and install MSYS2 from the [official website](https://www.msys2.org/).
2. Open the MSYS2 terminal and update the package database:

   ```bash
   pacman -Syu
   ```

### To build in Visual Studio Code

Use `CTRL + SHIFT + B` or `CTRL + SHIFT + P` -> Run Build Task

#### Tasks.json (_Compiler arguments_)

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-o", "mysqlversion_vs.exe",
                "mysqlversion_vs.cpp",
                "mysql_connect.cpp",
                "-I",
                "C:/Program Files/MySQL/MySQL Server 8.0/include",
                "-L",
                "C:/Program Files/MySQL/MySQL Server 8.0/lib",
                "-lmysql"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"],
            "detail": "Generated task for building MySQL Connector C++ project"
        }
    ]
}
```

#### C_CPP_Properties (_Include Path_)

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "C:/Program Files/MySQL/MySQL Server 8.0/include"
            ],
            "defines": [],
            "intelliSenseMode": "gcc-x86",
            "compilerPath": "C:/msys64/mingw64/bin/g++.exe",
            "cStandard": "c11",
            "cppStandard": "c++17"
        }
    ],
    "version": 4
}
```

## ! Paths to MySQL Connector can be changed

After configuring, you should be able to run `mysqlversion_vs.exe`:

```bash
start mysqlversion_vs.exe
```

or

```bash
./mysqlversion_vs.exe
```

### CMake

**To compile with CMake:**

1. Open your terminal and navigate to the project directory:
   ```bash
   cd mysqlversion_vs
   ```

2. Run CMake to generate build files:
   ```bash
   cmake .
   ```

3. Create a build directory and compile:
   ```bash
   cd build
   make
   ```

**Important:**
- Ensure that `libmysql.dll` is in the same directory as the executable or in a directory included in the system PATH. Without `libmysql.dll`, the program will not start.

### WAF Build/Compile

For building with WAF, refer to the official [WAF Documentation](https://waf.io/apidocs/index.html).

**To install WAF:**

- Visit the WAF [GitLab repository](https://gitlab.com/ita1024/waf/blob/master/README.md#L20) for installation instructions.

**To compile the project using WAF(if you using Git Bash or Linux):**

```bash
bash waf_script.sh
```

**If you using PowerShell:**

```bash
./build.ps1
```

### After Compiling the Project

Once the project is compiled successfully, ensure you replace the `"username"`, `"password"`, and `"database_name"` in the sample code with your actual MySQL credentials and database name.