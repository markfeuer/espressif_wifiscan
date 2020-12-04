FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/*.*)
idf_component_register(SRCS ${app_sources})
#idf_component_register(SRCS "main.cpp")