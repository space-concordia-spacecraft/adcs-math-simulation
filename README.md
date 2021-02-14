# SC-ODIN ADCS Algorithm

## Pre-requisites

In order to run the project, the following software is required:

- [x] CLion
- [x] Python 3.9.1 (32-bit)
- [x] vcpkg

### CLion
CLion is a C++ IDE distributed by JetBrains. You may get a free student license if you connect your JetBrains account to a GitHub account with the GitHub Student Pack. I strongly recommend using CLion for the project as it provides a ton of useful features and facilitates the development job. Its code completion and warnings seem to be much more robust than Visual Studio and it provides CMake support out of the box. You may download CLion [from here](https://www.jetbrains.com/clion/).

### Python 3.9.1 (32-bit)
Python is an interpreted, high-level and general-purpose programming language. Download the appropriate Python distribution for your operating system [from here](https://www.python.org/downloads/release/python-391/). In order to run this on Windows, be sure to grab the 32-bit version of Python. Make sure to install Tk/Tlc support as well as to add Python to the **PATH** on Windows when prompted. As an additional final step of the process for Windows users, copy the new entry to the **PATH** added by the Python installer to the **_PYTHONHOME_** environment variable. Once installed, you will need to use **_pip_** (python's package manager) to install the following two packages:
```
pip install numpy
pip install matplotlib
```

### vcpkg
vcpkg is a multi-platform package manager for C and C++ projects. You may clone the tool from the official repository [here](https://github.com/microsoft/vcpkg). Once cloned, execute the appropriate **_bootstrap-vcpkg_** script for your platform. You may also add the cloned folder to your **PATH** variable on Windows in order to facilitate the tool's usage. Once setup, you will need to install the following packages using the **_vcpkg install_** command:
```
vcpkg install glm
vcpkg install matplotlib-cpp 
```

## Configuration
Once all the pre-requisites are installed, you may clone this repository and open it as a CLion project. Before running the project, you will need to setup a CMake profile with the correct settings. To do so, follow these steps:

1. In CLion, open the **File** => **Settings** menu from the toolbar.

2. On the left-hand side, navigate to **Build, Execution, Deployment** => **CMake**.

3. Create a new CMake profile using the **+** icon.

4. Set the **Build Type** to **Release** (always use **Release** on Windows as **Debug** changes DLL symbols).

5. Add the following CMake options, where **_\<PATH TO VCPKG\>_** should point to the directory where **_vcpkg_** was cloned:
    ```
    -DCMAKE_TOOLCHAIN_FILE=<PATH TO VCPKG>/scripts/buildsystems/vcpkg.cmake
    ```
   
6. Delete the __cmake-build-*__ directories and reload the CMake project.

7. Run the project through the CMake profile created earlier.

**Note:** _You must have configured your toolchain before being able to compile the project in CLion. I used a Visual Studio toolchain on Windows. If you do the same, make sure to check that your Visual Studio is up-to-date through the Visual Studio Installer._

## Troubleshooting
If you are met with compilation errors in the **matplotlibcpp.h** file, you may need to remove the 4 lines (lines 340-343) causing the errors in the header, as well as including the **\<string\>** module from the standard library at the top of the file.