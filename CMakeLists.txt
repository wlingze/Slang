cmake_minimum_required(VERSION 3.10)

project(SLang C)

include_directories(include)

find_package(BISON)
find_package(FLEX)
BISON_TARGET(Parser com/gram.y  ${CMAKE_CURRENT_BINARY_DIR}/gram.c)
FLEX_TARGET(Scanner com/token.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)
message(STATUS "BISON: " ${BISON_Parser_OUTPUTS})
message(STATUS "FLEX: " ${FLEX_Scanner_OUTPUTS})

message(STATUS "build: " ${CMAKE_CURRENT_BINARY_DIR})

set(MAIN SLang.c)

file(GLOB_RECURSE LIB_SOURCE "lib/*.c")

file(GLOB_RECURSE FILE_SOURCE "file/*.c")

file(GLOB_RECURSE COM_C_SOURCE "com/*.c")
set(COM_SOURCE ${COM_C_SOURCE} ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})


file(GLOB_RECURSE GC_SOURCE "vm/gc/*.c")
file(GLOB_RECURSE RUNTIME_SOURCE "vm/runtime/*.c")
set(VM_SOURCE ${GC_SOURCE} ${RUNTIME_SOURCE})

message(STATUS "MAIN: " ${MAIN})
message(STATUS "LIB_SOURCE: " ${LIB_SOURCE})
message(STATUS "FILE_SOURCE: " ${FILE_SOURCE})
message(STATUS "COM_SOURCE: " ${COM_SOURCE})
message(STATUS "VM_SOURCE: " ${VM_SOURCE})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


add_executable(slang ${MAIN} 
        ${LIB_SOURCE} ${FILE_SOURCE} 
        ${VM_SOURCE} ${COM_SOURCE})