MAKEFILE_NAME = $(lastword $(MAKEFILE_LIST))

ROOT_DIR = $(dir $(MAKEFILE_NAME))

COMPILER	= g++
STD		= c++17

INCLUDE_DIRS	= $(ROOT_DIR)/include
SOURCE_DIRS	= $(wildcard $(ROOT_DIR)/ch*)

INCLUDE_OPTIONS		= $(foreach dir, $(INCLUDE_DIRS), -I$(dir))
ERROR_OPTIONS		= -pedantic-errors -Wall -Wextra -Winvalid-pch
LINKING_OPTIONS		= -g -std=$(STD) $(INCLUDE_OPTIONS) $(ERROR_OPTIONS)
COMPILING_OPTIONS	= -c $(LINKING_OPTIONS)

CPPS = $(foreach dir, $(SOURCE_DIRS),  $(wildcard $(dir)/*.cpp))
HPPS = $(foreach dir, $(INCLUDE_DIRS), $(wildcard $(dir)/*.hpp))

GCHS	= $(HPPS:.hpp=.hpp.gch)
OBJECTS	= $(CPPS:.cpp=.o)
EXES	= $(CPPS:.cpp=_exe)

all : headers exes

headers : $(GCHS)

%.hpp.gch : %.hpp
	$(COMPILER) $(COMPILING_OPTIONS) $< -o $@

%.o : %.cpp
	$(COMPILER) $(COMPILING_OPTIONS) $< -o $@

%_exe : %.o
	$(COMPILER) $(LINKING_OPTIONS) $< -o $@

clean :
	rm -f $(OBJECTS) $(EXES)

.PHONY : all clean headers
