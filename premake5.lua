-- ********************Build External Depedencies ********************--

-- If on WINDOWS.
if (package.config:sub(1,1) == '\\') then

    -- Build GLFW.
    os.execute("cd depedencies/GLFW && cmake ../../LearnOpenGL/GLFW")

    -- Build ASSIMP.
    os.execute("cd depedencies/ASSIMP && cmake ../../LearnOpenGL/ASSIMP")


-- On Unix Systems.
else

    -- Build GLFW.
    os.execute("cd depedencies/GLFW && cmake ../../LearnOpenGL/GLFW")
    os.execute("cd depedencies/GLFW && make")

    -- Build ASSIMP.
    os.execute("cd depedencies/ASSIMP && cmake ../../LearnOpenGL/ASSIMP")
    os.execute("cd depedencies/ASSIMP && make")

end
-- ********************Build External Depedencies ********************--





-- ==================LearnOpenGL WorkSpace================== --
workspace "LearnOpenGL"
    configurations {"Debug", "Release"}
    platforms "x64"
    architecture "x86_64"
    language "C++"
	
	
	
	-- You the /MDd and /MD option for all projects.
	filter {"system:windows", "configurations:Debug"}
		buildoptions{
			"/MDd",
		}
	filter {"system:windows", "configurations:Release"}
		buildoptions{
			"/MD",
		}
	filter {}
	
	


    -- ==================GLAD Project================== --
    project "GLAD"
        removeconfigurations "Release"
        kind "StaticLib"
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
        kind "StaticLib"
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

        -- Add precompiled header.
        pchheader "pch.h"
        pchsource "%{wks.name}/%{prj.name}/src/pch.cpp"

        -- Source Files.
        files {
            "%{wks.name}/%{prj.name}/src/**.cpp",
            "%{wks.name}/%{prj.name}/src/**.hpp",
            "%{wks.name}/%{prj.name}/src/**.h",
            "%{wks.name}/%{prj.name}/src/**.c"
        }

        --Include Directories.
        includedirs{
            "%{wks.name}/%{prj.name}/src",
            "%{wks.name}/GLFW/include",
            "%{wks.name}/GLAD/include",
            "%{wks.name}/STB_IMAGE",
            "%{wks.name}/GLM/",
            "depedencies/ASSIMP/include",
            "%{wks.name}/ASSIMP/include",
            "%{wks.name}/SPDLOG/include",
        }

        -- Library Directories.
        libdirs{
            "depedencies/GLFW/src",
			"depedencies/GLFW/src/Debug",
            "depedencies/ASSIMP/bin",
			"depedencies/ASSIMP/lib/Debug",
            "bin/%{cfg.shortname}"
			
        }

        -- Links.
        links{
            "GLAD",
            "STB_IMAGE"
        }

        -- Linux.
        filter "system:linux"
            links{
                "glfw3",
                "GL",
                "dl",
                "pthread",
                "assimp"
            }
			
		-- WINDOWS.
        filter "system:windows"
            links{
                "glfw3",
				"assimp-vc142-mtd",
				"opengl32"
            }

            defines{
                "ENGINE_WINDOWS"
            }
     -- ==================LearnOpenGL Project================== --

-- ==================LearnOpenGL WorkSpace================== --


-- If on WINDOWS.
if (package.config:sub(1,1) == '\\') then
    print("")


-- On Linux.
else
    print("")
    print("===================|FINISHED GENERATING PROJECTS|===================")
    print("Run 'make' to build LearnOpenGL")
    print("===================|FINISHED GENERATING PROJECTS|===================")
    print("")
end