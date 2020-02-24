workspace "damage"

	configurations { "Debug", "Release" }
	location ( "build" )
	
	--system { "Windows", "Unix" }
	platforms {"native", "x32"}
	
	project "damage"
	
		kind "WindowedApp"
		language "C"
		targetdir("build")
		files { "main.c" }
		includedirs {"include"}

		filter "system:Windows"
			system "windows"
			libdirs("lib/Debug_Win32")
			links { "glfw3dll", "libGLESv2", "libEGL", "OpenGL32"}

		filter "system:Unix"
			system "linux"
			libdirs("glfw/lib/Debug_Linux_x64")
			links {"m", "glfw3", "GLESv2", "dl", "X11", "pthread" }
				
		filter "configurations:Debug"
		  defines { "DEBUG" }
		  symbols "On"

		filter "configurations:Release"
		  defines { "NDEBUG" }
		  optimize "On"

