FLAGS := -Wall -Wextra -pedantic -std=c++1z
INCLUDE_PATH := -I../

all:clang_target1 gcc_target1
clang_target1: range/adaptor/adaptor_exp.cpp
	clang -lstdc++ $(FLAGS) $(INCLUDE_PATH) range/adaptor/adaptor_exp.cpp -o 0x01_clang.out
gcc_target1: range/adaptor/adaptor_exp.cpp
	g++ $(FLAGS) $(INCLUDE_PATH) range/adaptor/adaptor_exp.cpp -o 0x01_gcc.out
clean:
	$(RM) 0x01_clang.out 0x01_gcc.out
