file(GLOB_RECURSE
    source_files
    *.c
    icu/*.cpp
    icu/*.c
)

SET_SOURCE_FILES_PROPERTIES(
	${source_files}
  PROPERTIES LANGUAGE C
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/icu/include
)

add_library (icu-csdet
  ${source_files}
)
