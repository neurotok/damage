solution "damage"
	location ( "build" )
	configurations { "Debug", "Release" }
	platforms {"native", "x64"}

	project "damage"
		kind "WindowedApp"
		language "C"
		targetdir("build")
		files { "main.c" }
		includedirs { "glfw/include" }
		libdirs("lib")
		links { "glfw3" }

		configuration { "linux" }
			defines { "_GLFW_WIN32" }
			links {"m", "GLESv2", "dl", "X11", "pthread" }:wq

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols", "ExtraWarnings"}

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize", "ExtraWarnings"}

