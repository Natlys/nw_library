--==<library project>==--
project "nw_lib"
	kind "staticlib"
	staticruntime "on"
	language "c++"
	cppdialect "c++17"
	targetdir(dir_out_res)
	objdir(dir_out_int)
	pchheader "nwl_pch.hpp"
	pchsource "src_cpp/nwl_pch.cpp"
	files
	{
		"%{dir_cpp.own}**.c**",
		"%{dir_cpp.own}**.h**",
	}
	includedirs
	{
		"%{dir_cpp.own}",
		"%{dir_cpp.ext}",
	}
	filter "system:windows"
		systemversion "latest"
		defines "NWL_PLATFORM_WINDOWS"
	filter "configurations:debug"
		defines { "NWL_DEBUG" }
		symbols "on"
	filter "configurations:release"
		defines { "NWL_RELEASE" }
		optimize "on"
--==</library project>==--