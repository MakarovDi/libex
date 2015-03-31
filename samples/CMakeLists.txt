# Configure output path for samples
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin/samples")

# Get all files with cpp extension in current folder (samples/)
file(GLOB SAMPLES_SOURCES "*.cpp")

# Compile every .cpp file ass executable
foreach(sample_file ${SAMPLES_SOURCES})
    # cut off .cpp and full path
    get_filename_component(sample_name ${sample_file} NAME_WE)

    add_executable(${sample_name} ${sample_file})

    target_link_libraries(${sample_name} ex)
    set_target_properties(${sample_name} PROPERTIES LINKER_LANGUAGE CXX)
endforeach()
