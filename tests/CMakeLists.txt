# ------------------- Define CMake and Project properties ------------------- #

IF(WIN32)
	set (BOOST_ROOT C:/Program Files/boost)
	set (BOOST_LIBRARYDIR C:/Program Files/boost/lib)
	set (Boost_USE_STATIC_LIBS ON)
ELSEIF(APPLE)
	set (BOOST_ROOT /opt/boost_1_60)
	set (BOOST_LIBRARYDIR /opt/boost_1_60/lib)
  set (Boost_USE_STATIC_LIBS OFF)
ENDIF()

# --------------------        Try and find Boost         -------------------- #

# Make sure that the required boost libraries are installed
find_package (Boost COMPONENTS unit_test_framework REQUIRED)

include_directories (${Boost_INCLUDE_DIRS})

# --------------------      Set Test Bin Directory       -------------------- #

set (TestExeDir bin/)

# --------------------      Function to make a test      -------------------- #

function (MakeTest TestName TestFiles Libs TestsBinDir)
  # Add all the test .cpp file for the Diagnostics tests
  add_executable (${${TestName}} ${TestFiles})

  # Link all the libraries which the Diagnostics module uses
  target_link_libraries ( ${${TestName}}
                          ${${Libs}}
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                        )

  # Move the test binary into the TestsBin directory
  set_target_properties ( ${${TestName}} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                          ${Nano_SOURCE_DIR}/${${TestsBinDir}}
                        )

  # Add the test to the test execution
  add_test (  NAME ${${TestName}} WORKING_DIRECTORY
              ${Nano_SOURCE_DIR}/${${TestsBinDir}} COMMAND
              ${Nano_SOURCE_DIR}/${${TestsBinDir}}/${${TestName}}
          )
endfunction()

# --------------------            Nano Tests             -------------------- #

set (Tests     tests)
set (TestFiles "tests.cpp")
set (TestLibs )

MakeTest (Tests TestFiles TestLibs TestExeDir)

# --------------------------------------------------------------------------- #
