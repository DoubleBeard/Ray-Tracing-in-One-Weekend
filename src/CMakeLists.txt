# CMakeList.txt : CMake project for RayTracingInOneWeekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("RayTracingInOneWeekend")

# Add source to this project's executable.
add_executable (RayTracingInOneWeekend "main.cpp" "main.h" "vec3.h" "color.h" "ray.h" "hittable.h" "sphere.h" "hittable_list.h" "interval.h" "third-party/stb")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RayTracingInOneWeekend PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
