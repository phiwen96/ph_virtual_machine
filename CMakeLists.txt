cmake_minimum_required(VERSION 3.18)
project(ph_virtual_machine CXX)
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set (CMAKE_CXX_STANDARD 20)
	set (CMAKE_CXX_STANDARD_REQUIRED ON)
	set (CMAKE_CXX_EXTENSIONS ON)
	set_property (GLOBAL PROPERTY USE_FOLDERS ON)
	find_package (Boost 1.74 REQUIRED)
	# find_package(OpenSSL REQUIRED)
endif()
if (NOT TARGET phake)
	add_subdirectory (cmake/phake)
endif ()
if (NOT TARGET ph_concepts)
	add_subdirectory (dependencies/ph_concepts)
endif ()
if (NOT TARGET ph_system)
	add_subdirectory (dependencies/ph_system)
endif ()
if (NOT TARGET ph_data_structures)
	add_subdirectory (dependencies/ph_data_structures)
endif ()
add_subdirectory(src)
add_subdirectory(tests)







ph_create_modules (

	MODULES 
		"virtual_machine"
		"common"

	INCLUDE
		"${CMAKE_CURRENT_LIST_DIR}/include/ph_virtual_machine"

	SRC
		"${CMAKE_CURRENT_LIST_DIR}/src"
)




# cmake -Wno-dev -DCMAKE_CONFIGURATION_TYPES="Debug;Release;Kuk" -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/usr/bin/g++ -S . -B xbuild -GXcode && cmake --open xbuild
# cmake -Wno-dev -DCMAKE_CONFIGURATION_TYPES="Debug;Release;Kuk" -DCMAKE_CXX_COMPILER=/Applications/Xcode.app/Contents/Developer/usr/bin/g++ -S . -B xbuild -GXcode