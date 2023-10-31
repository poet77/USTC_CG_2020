function(Ubpa_SetupTarget)
    # https://www.cnblogs.com/cynchanpin/p/7354864.html
	# https://blog.csdn.net/fuyajun01/article/details/9036443
	cmake_parse_arguments("ARG" "" "MODE;NAME" "SOURCES;LIBS" ${ARGN})
	
	message(STATUS "----------")
	
	#message("ARG_DEFAULT_ARGS is ${ARG_DEFAULT_ARGS} from ${ARGN}")
	message(STATUS "mode: ${ARG_MODE}")
	message(STATUS "name: ${ARG_NAME}")
	message(STATUS "sources:")
	foreach(source ${ARG_SOURCES})
	    message(STATUS "  ${source}")
	endforeach()
	message(STATUS "libs:")
	foreach(lib ${ARG_LIBS})
	    message(STATUS "  ${lib}")
	endforeach()
	
	if(sourcesNum EQUAL 0)
		message(WARNING "Target [${ARG_NAME}] has no source, so it won't be generated.")
	else()
		set(isSupport ON)
		if(${ARG_MODE} STREQUAL "EXE")
			add_executable(${ARG_NAME} ${ARG_SOURCES})
			if(MSVC)
				set_target_properties(${ARG_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
			endif()
			set_target_properties(${ARG_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
		elseif(${ARG_MODE} STREQUAL "LIB")
			add_library(${ARG_NAME} ${ARG_SOURCES})
			# 无需手动设置
			#set_target_properties(${ARG_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
		elseif(${ARG_MODE} STREQUAL "DLL")
			add_library(${ARG_NAME} SHARED ${ARG_SOURCES})
		else()
			message(FATAL_ERROR "mode [${ARG_MODE}] is not supported")
			set(isSupport OFF)
		endif()
		if(isSupport)
			if( NOT ${FOLDER_NAME} STREQUAL " ")
				SET_TARGET_PROPERTIES(${ARG_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
			endif()
			target_link_libraries(${ARG_NAME} ${ARG_LIBS})
			install(TARGETS ${ARG_NAME}
					RUNTIME DESTINATION "bin"
					ARCHIVE DESTINATION "lib/${FOLDER_NAME}")
		endif()
	endif()
	
	message(STATUS "----------")
endfunction()

function(Ubpa_AddSubDirs)
	file(GLOB _children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
	set(_dirlist "")
	foreach(_child ${_children})
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_child})
			list(APPEND _dirlist ${_child})
		endif()
	endforeach()
	foreach(_subdir ${_dirlist})
		add_subdirectory(${_subdir})
	endforeach()
endfunction()

function(Ubpa_GetDirName DIRNAME)
	string(REGEX MATCH "([^/]*)$" TMP ${CMAKE_CURRENT_SOURCE_DIR})
	# 这里使用 PARENT_SCOPE 是因为函数会构建一个局部作用域
	set(${DIRNAME} ${TMP} PARENT_SCOPE)
endfunction()
