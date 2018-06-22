# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_subdirectory(src/main/cpp/glm)

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp
             src/main/cpp/Loader.cpp
             src/main/cpp/Renderer.cpp
             src/main/cpp/Player.cpp
             src/main/cpp/Camera.cpp
             src/main/cpp/Frustum.cpp
             src/main/cpp/TickEngine.cpp
             src/main/cpp/world/World.cpp
             src/main/cpp/world/Chunk.cpp
             src/main/cpp/world/Section.cpp
             src/main/cpp/render/SectionRenderer.cpp
             src/main/cpp/render/AsyncSectionQueue.cpp
             src/main/cpp/block/Block.cpp
             src/main/cpp/block/BlockRegistry.cpp
             src/main/cpp/gui/ControlPad.cpp
             src/main/cpp/gui/GuiRenderer.cpp
             src/main/cpp/gui/FontRenderer.cpp
             src/main/cpp/net/PacketHandler.cpp
             src/main/cpp/net/PacketBuffer.cpp
             src/main/cpp/util/jtime.cpp
             src/main/cpp/lodepng/lodepng.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       GLESv3)