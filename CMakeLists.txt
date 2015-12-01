cmake_minimum_required(VERSION 2.8.4)

project(NFsim)

set(CMAKE_BUILD_TYPE Debug)

set(SUB_DIRS
    src/nauty24 
    src/NFutil 
    src/NFutil/MTrand 
    src/NFtest/transcription 
    src/NFtest/tlbr 
    src/NFtest/simple_system 
    src/NFtest/agentcell/cell 
    src/NFtest/agentcell 
    src/NFscheduler 
    src/NFreactions/transformations 
    src/NFreactions/reactions 
    src/NFreactions/reactantLists 
    src/NFreactions/mappings 
    src/NFreactions 
    src/NFoutput 
    src/NFinput 
    src/NFinput/TinyXML 
    src/NFfunction/muParser 
    src/NFfunction 
    src/NFcore 
    src/NFcore/reactionSelector 
    src/NFcore/moleculeLists 
)


include_directories(${CMAKE_CURRENT_SOURCE_DIR} include ${SUB_DIRS})

file(GLOB_RECURSE src_files  "${CMAKE_CURRENT_SOURCE_DIR}/src/*cpp")
file(GLOB_RECURSE c_src_files  "${CMAKE_CURRENT_SOURCE_DIR}/src/*c")


set(SRC_FILES 
    ${src_files} 
    ${c_src_files} 
)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

link_libraries(xmlrpc_server_abyss++.a xmlrpc_server_abyss.a xmlrpc_server.a xmlrpc_server++.a xmlrpc++.a xmlrpc.a xmlrpc_xmlparse.a xmlrpc_xmltok.a xmlrpc_util.a  xmlrpc_abyss.a libxmlrpc_util.a pthread)

add_executable(NFsim ${SRC_FILES})