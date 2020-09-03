-- ********************Build External Depedencies ********************--

-- If on WINDOWS.
if (package.config:sub(1,1) == '\\') then
    print("Building Deps")


-- On Unix Systems.
else

    -- Build GLFW.
    os.execute("cd depedencies/GLFW && ccmake ../../LearnOpenGL/GLFW")
    os.execute("cd depedencies/GLFW && make")

    -- Build ASSIMP.
    os.execute("cd depedencies/ASSIMP && ccmake ../../LearnOpenGL/ASSIMP")
    os.execute("cd depedencies/ASSIMP && make")

end
-- ********************Build External Depedencies ********************--





-- ==================LearnOpenGL WorkSpace================== --
workspace "LearnOpenGL"
    configurations {"Debug", "Release"}
    platforms "x64"
    architecture "x86_64"
    language "C++"


    -- ==================GLAD Project================== --
    project "GLAD"
        removeconfigurations "Release"
        kind "SharedLib"
        targetdir "bin/%{cfg.shortname}"
        objdir "bin-int/%{prj.name}_%{cfg.shortname}"

        files {
            "%{wks.name}/%{prj.name}/**.cpp",
            "%{wks.name}/%{prj.name}/**.hpp",
            "%{wks.name}/%{prj.name}/**.h",
            "%{wks.name}/%{prj.name}/**.c"
        }

        includedirs{
            "%{wks.name}/%{prj.name}/include"
        }
    -- ==================GLAD Project================== --




    -- ==================STB_IMAGE Project================== --
    project "STB_IMAGE"
        removeconfigurations "Release"
        kind "SharedLib"
        targetdir "bin/%{cfg.shortname}"
        objdir "bin-int/%{prj.name}_%{cfg.shortname}"

        files {
            "%{wks.name}/%{prj.name}/**.cpp",
            "%{wks.name}/%{prj.name}/**.hpp",
            "%{wks.name}/%{prj.name}/**.h",
            "%{wks.name}/%{prj.name}/**.c"
        }
    -- ==================STB_IMAGE Project================== --




    
    -- ==================LearnOpenGL Project================== --
    project "LearnOpenGL"
        removeconfigurations "Release"
        kind "ConsoleApp"
        targetdir "bin/%{cfg.shortname}"
        objdir "bin-int/%{prj.name}_%{cfg.shortname}"

        files {
            "%{wks.name}/%{prj.name}/src/**.cpp",
            "%{wks.name}/%{prj.name}/src/**.hpp",
            "%{wks.name}/%{prj.name}/src/**.h",
            "%{wks.name}/%{prj.name}/src/**.c"
        }

        includedirs{
            "%{wks.name}/%{prj.name}/src",
            "%{wks.name}/GLFW/include",
            "%{wks.name}/GLAD/include",
            "%{wks.name}/STB_IMAGE",
            "%{wks.name}/GLM/",
            "depedencies/ASSIMP/include",
            "%{wks.name}/ASSIMP/include",
        }

        libdirs{
            "depedencies/GLFW/src",
            "depedencies/ASSIMP/bin",
            "bin/%{cfg.shortname}"
        }

        links{
            "GLAD",
            "STB_IMAGE"
        }

        -- Linux Links.
        filter "system:linux"
            links{
                "glfw",
                "GL",
                "assimp"
            }
     -- ==================LearnOpenGL Project================== --

-- ==================LearnOpenGL WorkSpace================== --