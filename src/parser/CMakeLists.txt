
set(Parser_SOURCE
        parser.cpp
        ast.cpp
        type_helper.h
        type_helper.cpp
        )


set(PARSER_HEADERS_DIR
        ${CMAKE_CURRENT_SOURCE_DIR};
        PARENT_SCOPE
        )

add_library(angreal_parser STATIC ${Parser_SOURCE})

target_include_directories(angreal_parser PRIVATE ${LEX_HEADERS_DIR} ${PARSER_HEADERS_DIR})