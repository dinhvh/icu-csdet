cmake_minimum_required (VERSION 2.6)
project (icu-csdet) 

file(COPY
  src/icu-csdet.h
  DESTINATION
  ${CMAKE_CURRENT_BINARY_DIR}/include/icu-csdet
)

add_subdirectory (src)
