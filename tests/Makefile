all:clang_target1 gcc_target1

clang_target1: range_adaptor_print_exp.cpp
	clang-5.0 -lstdc++ -Wall -Wextra -pedantic -std=c++1z -I../ range_adaptor_print_exp.cpp -o 0x01_clang.out
gcc_target1: range_adaptor_print_exp.cpp
	g++-6 -Wall -Wextra -pedantic -std=c++1z -I../ range_adaptor_print_exp.cpp -o 0x01_gcc.out
clean:
	rm 0x01_clang.out 0x01_gcc.out
