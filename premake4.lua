-- A solution contains projects, and defines the available configurations
solution ( "KillWinKey" )
	configurations { "Debug", "Release" }

	project ( "KeyHook" )
		kind ( "SharedLib" )
		language ( "C" )
		files { "hook.h", "hook_main.c" }
		flags { "StaticRuntime" }

		configuration ( "Debug" )
			targetdir ( "bin" )
			objdir ( "obj/debug" )
			defines { "DEBUG", "_DEBUG", "HOOK_EXPORTS" }
			flags { "Symbols" }
			targetsuffix ( "d" )

		configuration ( "Release" )
			targetdir ( "bin" )
			objdir ( "obj/release" )
			defines { "NDEBUG", "_NDEBUG", "HOOK_EXPORTS" }
			flags { "Optimize" }
		
		configuration ( "vs*" )
			defines { "WIN32", "_WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }


	project ( "KillWinKey" )
		kind ( "WindowedApp" )
		language ( "C" )
		files { "app_main.c", "resource.h", "resource.rc" }
		flags { "WinMain", "StaticRuntime" }

		configuration ( "Debug" )
			targetdir ( "bin" )
			objdir ( "obj/debug" )
			defines { "DEBUG", "_DEBUG" }
			flags { "Symbols" }
			targetsuffix ( "d" )

		configuration ( "Release" )
			targetdir ( "bin" )
			objdir ( "obj/release" )
			defines { "NDEBUG", "_NDEBUG" }
			flags { "Optimize" }
		
		configuration ( "vs*" )
			defines { "WIN32", "_WIN32", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
			links { "KeyHook" }
