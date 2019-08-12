cmake_minimum_required(VERSION 2.8.12)

set(TOPOLOGY_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(TOPOLOGY_GENERATED_HEADER "${TOPOLOGY_DIR}/Push2Topology.h")
set(TOPOLOGY_SOURCE_JSON "${TOPOLOGY_DIR}/Push2Topology.json")

#message( "TOPOLOGY_CODE_GEN_TOOL: "${TOPOLOGY_CODE_GEN_TOOL} )

add_custom_command(
    OUTPUT ${TOPOLOGY_GENERATED_HEADER}
    COMMAND python ${TOPOLOGY_CODE_GEN_TOOL} ${TOPOLOGY_SOURCE_JSON}
    WORKING_DIRECTORY ${TOPOLOGY_DIR}
    COMMENT "Generating Widget-Topology header"
    DEPENDS ${TOPOLOGY_SOURCE_JSON})

add_custom_target(generateTopologyHeader DEPENDS "${TOPOLOGY_GENERATED_HEADER}" "${TOPOLOGY_CODE_GEN_TOOL}")

add_library(Push2DeviceTopology INTERFACE)
target_include_directories(Push2DeviceTopology INTERFACE ${CMAKE_CURRENT_LIST_DIR})
#add_dependencies(Push2DeviceTopology generateTopologyHeader)