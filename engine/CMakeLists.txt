cmake_minimum_required(VERSION 3.0.0)
project(RSS VERSION 0.1.0)

set(RSS_PATH ".")
include("rss.cmake")

set (SRC
    ${SRC}
    main.cpp
)

set_source_files_properties(${HEADERS} PROPERTIES HEADER_FILE_ONLY TRUE)
include_directories(".")
add_executable(RSS ${HEADERS} ${SRC})
target_link_libraries(RSS ${PROJECT_LIBS})

