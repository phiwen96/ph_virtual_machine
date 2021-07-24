set (include_dir "${CMAKE_CURRENT_LIST_DIR}/../include/ph_virtual_machine")
set (src_dir "${CMAKE_CURRENT_LIST_DIR}")

ph_create_modules (

	MODULES 
		"virtual_machine"
		"common"
		"value"
		"opcode"


	INCLUDE
		"${include_dir}"

	SRC 
		"${src_dir}"
)

file(GLOB_RECURSE HEADER_LIST "${include_dir}/*.hpp")
file(GLOB SOURCE_LIST "${src_dir}/*.cpp")

add_library (ph_virtual_machine
	${SOURCE_LIST}  ${HEADER_LIST} 
)

target_compile_definitions (${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:DEBUG> $<$<CONFIG:RELEASE>:RELEASE>")


# target_sources (ph_network PRIVATE in/platform.hpp)
set (self ${PROJECT_NAME})

set_target_properties (${self} PROPERTIES CXX_STANDARD 20)
target_compile_features (${self} PUBLIC cxx_std_20)




# add_custom_target(
#     custom_header_target
#     DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/custom_header.h
# )
# ph_precompile (TARGET ph_concepts PRIVATE PCH ${std_pch} ${boost_pch})

add_library (ph::virtual_machine ALIAS ph_virtual_machine)
target_link_libraries (ph_virtual_machine PUBLIC ph::concepts ph::data_structures ${Boost_LIBRARIES})
target_include_directories (ph_virtual_machine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories (ph_virtual_machine PUBLIC ${Boost_INCLUDE_DIRS})
#  OpenSSL::SSL
target_compile_features (ph_virtual_machine PUBLIC cxx_std_20)

# target_compile_options(ph_network PUBLIC "-ast-dump  -fsyntax-only")


target_include_directories(ph_virtual_machine PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ph_virtual_machine>
    $<INSTALL_INTERFACE:include/ph_virtual_machine>
)

target_include_directories(ph_virtual_machine PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

else()
    set_target_properties(${PROJECT_NAME}          PROPERTIES FOLDER "dependencies")
endif()
