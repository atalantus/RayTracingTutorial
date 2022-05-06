-- premake5.lua
workspace "RayTracingTutorial"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "RayTracingTutorial"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "RayTracingTutorial"