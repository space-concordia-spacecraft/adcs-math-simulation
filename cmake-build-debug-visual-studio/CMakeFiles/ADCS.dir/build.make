# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio

# Include any dependencies generated for this target.
include CMakeFiles\ADCS.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\ADCS.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\ADCS.dir\flags.make

CMakeFiles\ADCS.dir\src\Main.cpp.obj: CMakeFiles\ADCS.dir\flags.make
CMakeFiles\ADCS.dir\src\Main.cpp.obj: ..\src\Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ADCS.dir/src/Main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ADCS.dir\src\Main.cpp.obj /FdCMakeFiles\ADCS.dir\ /FS -c C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\src\Main.cpp
<<

CMakeFiles\ADCS.dir\src\Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ADCS.dir/src/Main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe > CMakeFiles\ADCS.dir\src\Main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\src\Main.cpp
<<

CMakeFiles\ADCS.dir\src\Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ADCS.dir/src/Main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ADCS.dir\src\Main.cpp.s /c C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\src\Main.cpp
<<

CMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.obj: CMakeFiles\ADCS.dir\flags.make
CMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.obj: ..\src\simulation\Simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ADCS.dir/src/simulation/Simulation.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.obj /FdCMakeFiles\ADCS.dir\ /FS -c C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\src\simulation\Simulation.cpp
<<

CMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ADCS.dir/src/simulation/Simulation.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe > CMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\src\simulation\Simulation.cpp
<<

CMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ADCS.dir/src/simulation/Simulation.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.s /c C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\src\simulation\Simulation.cpp
<<

# Object files for target ADCS
ADCS_OBJECTS = \
"CMakeFiles\ADCS.dir\src\Main.cpp.obj" \
"CMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.obj"

# External object files for target ADCS
ADCS_EXTERNAL_OBJECTS =

ADCS.exe: CMakeFiles\ADCS.dir\src\Main.cpp.obj
ADCS.exe: CMakeFiles\ADCS.dir\src\simulation\Simulation.cpp.obj
ADCS.exe: CMakeFiles\ADCS.dir\build.make
ADCS.exe: C:\Users\Ruben\AppData\Local\Programs\Python\Python38\libs\python38.lib
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D.lib"
ADCS.exe: C:\Users\Ruben\AppData\Local\Programs\Python\Python38\libs\python38.lib
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_assimp_assimp-vc142-mt.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_assimp_IrrXML.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_glew.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_glfw3.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_jpeg.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_jsoncpp.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_lzf.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_libpng.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_zlib.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_rply.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_tinyfiledialogs.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_qhullcpp.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_qhull_r.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_imgui.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filameshio.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filament.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filamat_lite.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filaflat.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filabridge.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_geometry.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_backend.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_bluegl.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_ibl.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_image.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_meshoptimizer.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_smol-v.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_utils.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_bluevk.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_tbb_tbb_static.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_tbb_tbbmalloc_static.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_intel_ilp64.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_core.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_sequential.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_tbb_thread.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_tbb_static.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_ippicv_ippiw.lib"
ADCS.exe: "C:\Program Files\Open3D\lib\Open3D_3rdparty_ippicv_ippicvmt.lib"
ADCS.exe: CMakeFiles\ADCS.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ADCS.exe"
	"C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\ADCS.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x64\mt.exe --manifests -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\ADCS.dir\objects1.rsp @<<
 /out:ADCS.exe /implib:ADCS.lib /pdb:C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio\ADCS.pdb /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console  C:\Users\Ruben\AppData\Local\Programs\Python\Python38\libs\python38.lib "C:\Program Files\Open3D\lib\Open3D.lib" C:\Users\Ruben\AppData\Local\Programs\Python\Python38\libs\python38.lib "C:\Program Files\Open3D\lib\Open3D_3rdparty_assimp_assimp-vc142-mt.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_assimp_IrrXML.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_glew.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_glfw3.lib" gdi32.lib "C:\Program Files\Open3D\lib\Open3D_3rdparty_jpeg.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_jsoncpp.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_lzf.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_libpng.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_zlib.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_rply.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_tinyfiledialogs.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_qhullcpp.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_qhull_r.lib" opengl32.lib "C:\Program Files\Open3D\lib\Open3D_3rdparty_imgui.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filameshio.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filament.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filamat_lite.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filaflat.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_filabridge.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_geometry.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_backend.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_bluegl.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_ibl.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_image.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_meshoptimizer.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_smol-v.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_utils.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_filament_bluevk.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_tbb_tbb_static.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_tbb_tbbmalloc_static.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_intel_ilp64.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_core.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_sequential.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_mkl_tbb_thread.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_mkl_tbb_static.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_ippicv_ippiw.lib" "C:\Program Files\Open3D\lib\Open3D_3rdparty_ippicv_ippicvmt.lib" kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -noprofile -executionpolicy Bypass -file C:/Users/Ruben/OneDrive/Desktop/space/vcpkg/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary C:/Users/Ruben/OneDrive/Desktop/space/adcs-math-simulation/cmake-build-debug-visual-studio/ADCS.exe -installedDir C:/Users/Ruben/OneDrive/Desktop/space/vcpkg/installed/x64-windows/debug/bin -OutVariable out

# Rule to build all files generated by this target.
CMakeFiles\ADCS.dir\build: ADCS.exe
.PHONY : CMakeFiles\ADCS.dir\build

CMakeFiles\ADCS.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ADCS.dir\cmake_clean.cmake
.PHONY : CMakeFiles\ADCS.dir\clean

CMakeFiles\ADCS.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio C:\Users\Ruben\OneDrive\Desktop\space\adcs-math-simulation\cmake-build-debug-visual-studio\CMakeFiles\ADCS.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\ADCS.dir\depend

