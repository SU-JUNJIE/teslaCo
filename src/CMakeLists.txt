file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/src/*.cc)

add_library(tesla_base ${srcs})
target_link_libraries(tesla_base pthread rt)

install(TARGETS tesla_base DESTINATION lib)
file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/tesla_base/base)
