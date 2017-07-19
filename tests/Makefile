FLAGS := -Wall -Wextra -pedantic -std=c++1z
INCLUDE_PATH := -I../
CLANG = clang++
#-5.0
GXX = /usr/local/Cellar/gcc/7.1.0/bin/g++-7
#g++-6

all:clang_target1 gcc_target1
clang_target1: range/adaptor/adaptor_exp.cpp
	$(CLANG) $(FLAGS) $(INCLUDE_PATH) range/adaptor/adaptor_exp.cpp -o 0x01_clang.out
gcc_target1: range/adaptor/adaptor_exp.cpp
	$(GXX)  $(FLAGS) $(INCLUDE_PATH) range/adaptor/adaptor_exp.cpp -o 0x01_gcc.out
clean:
	$(RM) tests/0x01_clang.out tests/0x01_gcc.out
