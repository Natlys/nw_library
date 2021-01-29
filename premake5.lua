--==<library project>==--
project "nw_lib"
	kind "staticlib"
	staticruntime "on"
	language "c++"
	cppdialect "c++17"
	targetdir("bin/"..dir_out.."%{prj.name}")
	objdir("bin/"..dir_out.."%{prj.name}")
	files
	{
		"src_cpp/**.c**",
		"src_cpp/**.h**",
	}
	includedirs
	{
		"src_cpp/",
	}
	links
	{
	}
	defines
	{
		--"NWL_LINK_DYNAMIC",
		"NWL_LINK_STATIC",
		"NWL_BUILD_LIB"
	}
	filter "system:windows"
		systemversion "latest"
		defines "NWL_PLATFORM_WINDOWS"
	filter "configurations:debug"
		defines {"NWL_DEBUG"}
		symbols "on"
	filter "configurations:release"
		defines {"NWL_RELEASE"}
		optimize "on"
--==</library project>==--