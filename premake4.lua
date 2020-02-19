solution "damage"
	location ( "build" )
	configurations { "Debug", "Release" }
	platforms {"native", "x64"}

	project "damage"
		kind "WindowedApp"
		language "C"
		targetdir("build")
		files { "main.c" }
		includedirs { "include" }
		libdirs("lib")
		links { "glfw3" }

		configuration { "linux" }
			links {"m", "GLESv2", "dl", "X11", "pthread" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols", "ExtraWarnings"}

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize", "ExtraWarnings"}

