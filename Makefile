########################################################################################
#				 	                EXECUTABLE NAME 	                               #
########################################################################################

EXE 			:= nano_test_suite

########################################################################################
#                                   INSTALL DIRECTORY                                  #
########################################################################################

INSTALL_DIR     := /usr/include
UNINSTALL_DIR   := $(addsuffix /nano, $(INSTALL_DIR))

########################################################################################
#					                  COMPILERS						                   #
########################################################################################

CXX 			:= g++ 

########################################################################################
#				                    INCLUDE DIRECTORIES 		                       #
########################################################################################

INCLUDE         :=

########################################################################################
#				   	                   LIBRARIES 						               #
########################################################################################

LIBS 		    := -lboost_unit_test_framework      
LDIR  	        := 

########################################################################################
#					                COMPILER FLAGS 					                   #
#                                                                                      #
# NOTE: To enable compiler warnings, remove -w and replace with :                      #
# 		--compiler-options -Wall                                                       #
########################################################################################

CXX_FLAGS 		:= -std=c++11 -w -O3

########################################################################################
# 					                TARGET RULES 					                   #
#######################################################################################

.PHONY: all build_and_run build install uninstall
	
all: build_and_run

build_and_run: build_tests
	rm -rf *.o
	./$(EXE) --log_level=test_suite
	
run:
	./#(EXE) --log_level=test_suite
	
build: build_tests
	
nano_tests.o: nano_tests.cpp 
	$(CXX) $(INCLUDE) $(CXX_FLAGS) -o $@ -c $<

build_tests: nano_tests.o 
	$(CXX) -o $(EXE) $+ $(LDIR) $(LIBS)
	
install:
	cp -r nano $(INSTALL_DIR)
	
uninstall:
	rm -rf $(UNINSTALL_DIR)
	
clean:
	rm -rf *.o
	rm -rf $(EXE) 

clobber: clean