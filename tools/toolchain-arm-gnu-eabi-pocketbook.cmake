# CMake toolchain file for building Pocketbook Free SDK software using

# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /usr/bin/arm-linux-gnueabi-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
SET(CMAKE_STRIP /usr/local/pocketbook/bin/arm-linux-gnueabi-strip)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /usr/local/pocketbook_eabi)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
