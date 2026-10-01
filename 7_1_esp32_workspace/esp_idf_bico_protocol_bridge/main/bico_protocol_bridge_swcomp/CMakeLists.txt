include(${CMAKE_CURRENT_LIST_DIR}/../../../../3_swComp/bicoProtocolBridgeSwComp.cmake)

# The port implementations are linked after the software so that the symbols they provide are resolved.
idf_component_register(
    SRCS ${BICO_PROTOCOL_BRIDGE_SWCOMP_SOURCES}
    INCLUDE_DIRS ${BICO_PROTOCOL_BRIDGE_SWCOMP_INCLUDE_DIRS}
    REQUIRES bico_protocol_bridge_port_esp32
)
