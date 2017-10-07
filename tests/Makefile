FLAGS := -Wall -Wextra -pedantic -std=c++1z
INCLUDE_PATH := -I../
GXX = g++-7

TEST1 = cxx17/array_view/at_test.o\
	cxx17/array_view/back_test.o\
	cxx17/array_view/front_test.o\
	cxx17/array_view/type_check_test.o\
	cxx17/array_view/substr_test.o\
	mpl/constant_sequence/constant_exp.o\
	mpl/math/compile_time_four_arithmetic_operations_parser_test.o\
	cxx17/any_pack/meta_random_engine_test.o\
       	range/adaptor/adaptor_exp.o

all: gcc_target1

gcc_target1: $(TEST1)

$(TEST1): %.o: %.cpp
	cppcheck --enable=all $<
	$(GXX) $(FLAGS) $(INCLUDE_PATH) $< -o $@
run:
	./cxx17/array_view/at_test.o
	./cxx17/any_pack/meta_random_engine_test.o
	./range/adaptor/adaptor_exp.o
clean:
	$(RM) $(TEST1)
