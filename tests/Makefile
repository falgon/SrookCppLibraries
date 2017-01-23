FLAGS := -Wall -Wextra -pedantic -std=c++1z
INCLUDE_PATH := -I../

all:clang_target1 gcc_target1
clang_target1: range/adaptor/adaptor_exp.cpp
	clang-5.0 -lstdc++ $(FLAGS) $(INCLUDE_PATH) range/adaptor/adaptor_exp.cpp -o 0x01_clang.out
gcc_target1: range/adaptor/adaptor_exp.cpp
	g++-6 $(FLAGS) $(INCLUDE_PATH) range/adaptor/adaptor_exp.cpp -o 0x01_gcc.out
clean:
	$(RM) testts/0x01_clang.out tests/0x01_gcc.out
