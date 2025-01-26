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

**Important:**

- Ensure that `libmysql.dll` is in the same directory as the executable or in a directory included in the system PATH. Without `libmysql.dll`, the program will not start.

### WAF Build/Compile

For building with WAF, refer to the official [WAF Documentation](https://waf.io/apidocs/index.html).

**To install WAF:**

- Visit the WAF [GitLab repository](https://gitlab.com/ita1024/waf/blob/master/README.md#L20) for installation instructions.


**Inside WAF Script**

```python
#! /usr/bin/env python
# encoding: utf-8
# I#Oleg

"""
Custom Waf script for building a MySQL-based C++ application.
"""

import os , sys

VERSION = "2.1.4"
APPNAME = 'mysqlversion_vs'
REVISION = ''

top = '.'
out = 'build_output'

def options(opt):
    opt.add_option('--debug', action='store_true', help='Show debug time', default=False)

def configure(conf):
    """Set up the environment for building."""
    directory = os.getcwd()  # Get the current working directory

    # Print the current directory for debugging
    print(f"Current directory: {directory}")

    # Only check if running on Windows
    if sys.platform.startswith('win'):
        # On Windows, check for 'libmysql.dll' in the 'bin' folder
        libmysql_path = os.path.join(directory, 'bin', 'libmysql.dll')
        
        # Debug output to ensure path is correct
        print(f"Checking for {libmysql_path}...")

        # Check if the file exists in the specified path
        if os.path.exists(libmysql_path):
            print(f"Library {libmysql_path} found in the directory (Windows).")
        else:
            print(f"Library {libmysql_path} not found in the directory (Windows).")
    else:
        print("This script is only intended for Windows.")

    conf.find_program('g++')
    conf.env['OUT'] = 'build_output'  # Output directory for compiled files
    # Set the C++ compiler (ensure MinGW path is correct)
    conf.env.CC = '/c/msys64/mingw64/bin/g++'
   
    # Optionally, set C++ compiler flags
    conf.env.CXXFLAGS = ['-Wall', '-lmysql']  # Enable warnings for C++ and link with MySQL
    
    # Include path for MySQL headers(Don`t forget to change it)
    conf.env.INCLUDES = ['C:/Program Files/MySQL/MySQL Server 8.0/include']  # Using quotes for path with spaces
  
    # Library path for MySQL libraries(Don`t forget to change it)
    conf.env.LIBPATH = ['C:/Program Files/MySQL/MySQL Server 8.0/lib', '../dll']  # Using quotes for path with spaces

    # Libraries to link against (MySQL client library)
    conf.env.LIB = ['mysql']  # Use `mysqlclient` for dynamic linking
    conf.env.LIB_MYSQL = ['mysqlclient']  # Name of the MySQL library (libmysql.dll or libmysql.so)
    conf.env.LIBPATH += ['./bin']  # Assuming the DLL is in ./bin

    if conf.options.debug:
        conf.env.CXXFLAGS += ['-g', '-DDEBUG_TIME']

    # Load the C++ compiler
    conf.load('g++')


def build(bld):

    bld.program(
        target='main',  # Output binary name
        source=['mysqlversion_vs.cpp', 'mysql_connect.cpp'],  # Source files
        includes=bld.env.INCLUDES,  # Include paths for headers
        libpath=bld.env.LIBPATH,  # Library paths
        libs=bld.env.LIB,  # Libraries to link against (MySQL client)
        linkflags=['-L"C:/Program Files/MySQL/MySQL Server 8.0/lib"', '-lmysqlclient'],  # Link dynamic libraries
        env=bld.env,  # Ensure the environment variables are included
        use = ['mysql'],
        cxxflags=['-std=c++17'],  # Flags for c++
    )

    

def post_build(bld):
    """Run after the build process (e.g., for post-processing or testing)."""
    print("Build complete!")
    print(f"Executable created at: {bld.env['OUT']}/main")
```

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