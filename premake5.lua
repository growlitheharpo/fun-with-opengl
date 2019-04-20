#!lua

-- Stolen from https://github.com/premake/premake-core/issues/935#
function os.winSdkVersion()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

workspace "fun-with-opengl"
    location "./"
    language "C++"
    cppdialect "c++17"

    architecture "x86_64"
    configurations { "Debug", "Release" }

    filter { "configurations:Debug" }
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"
    
    filter {"system:windows", "action:vs*"}
        systemversion(os.winSdkVersion() .. ".0")

    filter {}

    flags {
        "FatalWarnings"
    }
    

	targetdir ("bin/%{prj.name}/%{cfg.longname}")
	objdir ("obj/%{prj.name}/%{cfg.longname}")

project "opengl-demo"
    kind "ConsoleApp"
    
    files "src/**"
    includedirs "src/"
    location "proj/"
    debugdir "src/"

    nuget {
        "nupengl.core.redist:0.1.0.1",
        "nupengl.core:0.1.0.1",
        "glm:0.9.9",
    }
