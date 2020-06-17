MAKEFILE_NAME = $(lastword $(MAKEFILE_LIST))

ROOT_DIR = $(dir $(MAKEFILE_NAME))

COMPILER	= g++
STD		= c++17

INCLUDE_DIRS	= $(ROOT_DIR)/include
INCLUDE_OPTIONS = $(foreach dir, $(INCLUDE_DIRS), -I$(dir))

COMPILING_OPTIONS	= -c $(LINKING_OPTIONS)
LINKING_OPTIONS		= $(INCLUDE_OPTIONS) -Wall -Wextra -std=$(STD) -g

%.o : %.cpp
	$(COMPILER) $(COMPILING_OPTIONS) $< -o $@

%_exe : %.o
	$(COMPILER) $(LINKING_OPTIONS) $< -o $@

clean :
	rm -f *_exe *.o
