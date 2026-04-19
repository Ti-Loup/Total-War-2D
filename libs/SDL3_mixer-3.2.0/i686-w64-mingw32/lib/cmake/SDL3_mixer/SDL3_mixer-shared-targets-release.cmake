#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SDL3_mixer::SDL3_mixer-shared" for configuration "Release"
set_property(TARGET SDL3_mixer::SDL3_mixer-shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SDL3_mixer::SDL3_mixer-shared PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libSDL3_mixer.dll.a"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "SDL3::SDL3-shared"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/SDL3_mixer.dll"
  )

list(APPEND _cmake_import_check_targets SDL3_mixer::SDL3_mixer-shared )
list(APPEND _cmake_import_check_files_for_SDL3_mixer::SDL3_mixer-shared "${_IMPORT_PREFIX}/lib/libSDL3_mixer.dll.a" "${_IMPORT_PREFIX}/bin/SDL3_mixer.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
