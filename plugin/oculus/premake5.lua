PROJECT_NAME = path.getname(os.getcwd())

if not minko.platform.supports { "windows32", "windows64", "linux32", "linux64", "osx64" } then
	return
end

minko.project.library("minko-plugin-" .. PROJECT_NAME)

	removeplatforms { "html5", "ios", "android" }

	files {
		"**.hpp",
		"**.h",
		"**.cpp",
		"**.c",
		"include/**.hpp",
		"lib/LibOVR/Src/**"
	}
	includedirs {
		"include",
		"src",
		"lib/LibOVR/Include",
		"lib/LibOVR/Src"
	}

	excludes { "lib/LibOVR/Include/OVRVersion.h" }

	configuration { "windows32 or windows64" }
		excludes {
			"lib/LibOVR/Src/OVR_Linux_*",
			"lib/LibOVR/Src/OVR_OSX_*",
			"lib/LibOVR/Src/Kernel/OVR_ThreadsPthread.cpp"
		}
		defines { "UNICODE", "_UNICODE" } -- should also undefine _MCBS

	configuration { "linux32 or linux64" }
		includedirs {
			"lib/lin/Xinerama/include",
			"lib/lin/libudev/include"
		}
		excludes {
			"lib/LibOVR/Src/OVR_Win32_*",
			"lib/LibOVR/Src/OVR_OSX_*",
			"lib/LibOVR/Src/Kernel/OVR_ThreadsWinAPI.cpp"
		}

	configuration { "osx64" }
		excludes {
			"lib/LibOVR/Src/OVR_Win32_*",
			"lib/LibOVR/Src/OVR_Linux_*",
			"lib/LibOVR/Src/Kernel/OVR_ThreadsWinAPI.cpp"
		}
