project "googletest"
	removeplatforms { "html5" }
	
	kind "StaticLib"
	language "C++"
	location "."
	files {
		"src/gtest-all.cc"
	}
	includedirs {
		"."
	}

	configuration { "debug"}
		defines { "_DEBUG" }

	-- linux
	configuration { "linux" }
		buildoptions { "-std=c++11", "-isystem include", "-pthread" }

	-- windows
	--configuration { "windows", "x32" }

	-- macos
	configuration { "macosx" }
		buildoptions { "-std=c++11", "-isystem include", "-pthread" }

	-- emscripten
	configuration { "emscripten" }
		buildoptions { "-std=c++11", "-isystem include", "-pthread" }