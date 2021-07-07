# ---[ Projects.
# Toolkits.
add_subdirectory ("CfgTest")
add_subdirectory ("CfgControl")

set_property (DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT "CfgTest")
