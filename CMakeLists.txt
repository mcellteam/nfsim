cmake_minimum_required(VERSION 2.8.9)

project(NFsim)

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/libs)

if (NOT WIN32)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

  # disable some warnings, not neccesarily safe ones, but we do not expect any firther modifications to nfsim from our side
  set(DISABLE_WARNINGS_FLAGS_C_CXX 
    "-Wno-unknown-warning-option -Wno-return-type -Wno-shadow -Wno-sign-compare -Wno-write-strings -Wno-unused-variable -Wno-maybe-uninitialized -Wno-type-limits -Wno-sequence-point -Wno-strict-aliasing -Wno-extra -Wmisleading-indentation -Wno-unused-but-set-variable -Wno-misleading-indentation "
  )
    
  set(DISABLE_WARNINGS_FLAGS_CXX 
    "${DISABLE_WARNINGS_FLAGS_C_CXX} -Wno-delete-non-virtual-dtor -Wno-reorder "
  )
    
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DISABLE_WARNINGS_FLAGS_C_CXX} ") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DISABLE_WARNINGS_FLAGS_CXX} ")
  
  add_definitions("-Wno-deprecated-declarations")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  
endif()

set(SUB_DIRS
    include/
    include/nauty24 
    include/NFutil 
    include/NFutil/MTrand 
    include/NFtest/transcription 
    include/NFtest/tlbr 
    include/NFtest/simple_system 
    include/NFtest/agentcell/cell 
    include/NFtest/agentcell 
    include/NFproperty
    include/NFscheduler 
    include/NFreactions/transformations 
    include/NFreactions/reactions 
    include/NFreactions/reactantLists 
    include/NFreactions/mappings 
    include/NFreactions 
    include/NFoutput 
    include/NFinput 
    include/NFinput/TinyXML 
    include/NFinput/json 
    include/NFfunction/muParser 
    include/NFfunction 
    include/NFcore 
    include/NFcore/reactionSelector 
    include/NFcore/moleculeLists 
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SUB_DIRS})

                                                                                                                        
file(GLOB_RECURSE src_files  "${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp")
file(GLOB_RECURSE c_src_files  "${CMAKE_CURRENT_SOURCE_DIR}/src/*c")


set(SRC_FILES 
    ${src_files} 
    ${c_src_files} 
)

# -- nfsim_EXE --
if (NOT WIN32)
# with MSVC, the .ilk file gets broken
add_executable(${PROJECT_NAME}_EXE ${SRC_FILES} )
set_target_properties(${PROJECT_NAME}_EXE PROPERTIES OUTPUT_NAME "NFsim")
endif()

# -- nfsim_static --
add_library(${PROJECT_NAME}_static STATIC ${SRC_FILES})
# -- nfsim_static_fpic --

add_library(${PROJECT_NAME}_static_fpic STATIC ${SRC_FILES})
set_target_properties(${PROJECT_NAME}_static_fpic PROPERTIES POSITION_INDEPENDENT_CODE 1)

# -- nfsim (dynamic) --

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE 1)
