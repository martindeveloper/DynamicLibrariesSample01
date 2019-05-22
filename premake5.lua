workspace "Game"
   configurations { "Debug", "Release" }
   platforms { "Win32", "Win64" }
   location "ProjectFiles/"

   filter "platforms:Win32"
      system "Windows"
      architecture "x86"
      systemversion "10.0.17763.0"

   filter "platforms:Win64"
      systemversion "10.0.17763.0"
      system "Windows"
      architecture "x86_64"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

project "Bootstrap"
   kind "ConsoleApp"
   language "C++"
   characterset "ASCII"
   entrypoint "main"
   flags { }

   toolset "v142" -- VS2017

   files { "Source/Bootstrap/**.h", "Source/Bootstrap/**.cpp" }

   targetdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"
   objdir "Intermediate/%{cfg.platform}/%{cfg.buildcfg}"
   debugdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"

   dependson { "Engine", "Components", "Game" }

project "Engine"
   kind "SharedLib"
   language "C++"
   characterset "ASCII"

   toolset "v142"

   targetdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"
   objdir "Intermediate/%{cfg.platform}/%{cfg.buildcfg}"
   debugdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"

   files { "Source/Engine/**.h", "Source/Engine/**.cpp" }

   defines { "ENGINE_EXPORTS=1" }

project "Components"
   kind "SharedLib"
   language "C++"
   characterset "ASCII"

   toolset "v142"

   targetdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"
   objdir "Intermediate/%{cfg.platform}/%{cfg.buildcfg}"
   debugdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"

   files { "Source/Components/**.h", "Source/Components/**.cpp" }

   defines { "COMPONENTS_EXPORTS=1" }

project "Game"
   kind "SharedLib"
   language "C++"
   characterset "ASCII"
   
   toolset "v142"

   targetdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"
   objdir "Intermediate/%{cfg.platform}/%{cfg.buildcfg}"
   debugdir "Binaries/%{cfg.platform}/%{cfg.buildcfg}"

   files { "Source/Game/**.h", "Source/Game/**.cpp" }

   defines { "GAME_EXPORTS=1" }

   -- Uncomment `links` statement if you want to use Load-Time Linking
   -- links { "Engine" }
   dependson { "Engine" }
