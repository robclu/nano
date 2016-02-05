# --------------------      CMakeLists.txt for Nano       ------------------- #

cmake_minimum_required (VERSION 3.4)
project (Nano)

# --------------------         Set Subdirectories         ------------------- #

add_subdirectory (${Nano_SOURCE_DIR}/doc)
add_subdirectory (${Nano_SOURCE_DIR}/tests)

# --------------------           Enable Testing           ------------------- #

enable_testing()

# --------------------         Rule for installing        ------------------- #

# Copy everything in /include to the install destination
install(DIRECTORY include DESTINATION include 
        PATTERN ".DS_Store" EXCLUDE)




