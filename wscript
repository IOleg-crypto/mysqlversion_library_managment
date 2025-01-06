

def configure(conf):
    """Set up the environment for building."""
    # Set the output directory (optional)
    conf.find_program('g++')
    conf.env['OUT'] = 'build_output'  # Output directory for compiled files
    
    # Set the C++ compiler (ensure MinGW path is correct)
    conf.env.CC = '/c/msys64/mingw64/bin/g++'

    # Optionally, set C++ compiler flags
    conf.env.CXXFLAGS = ['-Wall', '-lmysql']  # Enable warnings for C++ and link with MySQL
    
    # Include path for MySQL headers
    conf.env.INCLUDES = ['C:\Program Files\MySQL\MySQL Server 8.0\include']

    # Library path for MySQL libraries
    conf.env.LIBPATH = ['C:\Program Files\MySQL\MySQL Server 8.0\lib']

    # Libraries to link against (MySQL client library)
    conf.env.LIB = ['mysql']  # Use `mysqlclient` for dynamic linking

    # Check if MySQL client library is available
    conf.check(lib='mysqlclienxt', uselib_store='mysqlclient')  # Check for MySQL client library

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
        linkflags=['-L"C:\\Program Files\\MySQL\\MySQL Server 8.0\\lib"', '-lmysqlclient'],  # Link dynamic libraries
        env=bld.env  # Ensure the environment variables are included
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
