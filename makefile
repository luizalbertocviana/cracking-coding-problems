COMPILER	= g++
STD		= c++17

COMPILING_OPTIONS	= -c $(LINKING_OPTIONS)
LINKING_OPTIONS		= -Wall -Wextra -std=$(STD) -O2

%.o : %.cpp
	$(COMPILER) $(COMPILING_OPTIONS) $< -o $@

%_exe : %.o
	$(COMPILER) $(LINKING_OPTIONS) $< -o $@
