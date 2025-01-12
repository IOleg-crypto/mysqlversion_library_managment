#! /usr/bin/env python
# encoding: utf-8
# Thomas Nagy, 2005-2018

"""
Custom Waf script for building a MySQL-based C++ application.
"""

import os , sys

VERSION = "2.1.4"
APPNAME = 'mysqlversion_vs'
REVISION = ''

top = '.'
out = 'build_output'

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
    
    # Include path for MySQL headers
    conf.env.INCLUDES = ['C:/Program Files/MySQL/MySQL Server 8.0/include']  # Using quotes for path with spaces
  
    # Library path for MySQL libraries
    conf.env.LIBPATH = ['C:/Program Files/MySQL/MySQL Server 8.0/lib', '../dll']  # Using quotes for path with spaces

    # Libraries to link against (MySQL client library)
    conf.env.LIB = ['mysql']  # Use `mysqlclient` for dynamic linking
    conf.env.LIB_MYSQL = ['mysqlclient']  # Name of the MySQL library (libmysql.dll or libmysql.so)
    conf.env.LIBPATH += ['./bin']  # Assuming the DLL is in ./bin

    # Load the C++ compiler
    conf.load('g++')


def build(bld):
    """Define the build process."""
    # Specify the output directory and source files

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

    # Additional compiler flags for debug or optimization
    if bld.env['DEBUG']:
        bld.env.CXXFLAGS.append('-g')  # Include debug symbols for debugging
    else:
        bld.env.CXXFLAGS.append('-O2')  # Optimize the build for release

def post_build(bld):
    """Run after the build process (e.g., for post-processing or testing)."""
    print("Build complete!")
    print(f"Executable created at: {bld.env['OUT']}/main")