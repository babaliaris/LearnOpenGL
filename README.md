# LearnOpenGL

## Depedencies
[cmake](https://cmake.org/download/) and [premake5](https://premake.github.io/) Project generator tools).

Install them and add them to your **PATH** variable.

## Check Depedencies
Run in the terminal (both for windows and linux) `cmake -version` and `premake5 --version` .
If you get an error like "The command not found" it means you have not installed **cmake** and **premake** OR
you did not add them to your **PATH**.


## Clone
`git clone --recurse-submodules https://github.com/babaliaris/LearnOpenGL.git`
### The flag `--recurse-submodules` is **important**!!!

## Build for Linux
`cd <inside_the_root_directory_of_this_repository>`
`premake5 gmake`
`make`


## Build for Windows (Visual Studio)
This is a little more compilated.

`cd <inside_the_root_directory_of_this_repository>`
`premake5 vs2019` (if you want you can run premake5 with another visual studio target: **example: premake5 vs2017**)

Then open depedencies/GLFW/GLFW.sln and compile GLFW by right click the **GLFW** project and select BUILD.
Then open depedencies/ASSIMP/Assimp.sln and compile ASSIMP by right click the **BUILD_ALL** project and select BUILD.

Finally you can open the LearnOpenGL.sln solution and compile it by right click the **LearnOpenGL** project and select BUILD.

Do not forget to set the **LearnOpenGL** project as the **StartUp** project (Right click the project and select set as Start Up Project).
