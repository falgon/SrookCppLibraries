#
# Copyright (C) 2011-2017 Roki. Distributed under the MIT License
#

FLAGS := -Wall -Wextra -pedantic -std=c++1z -pthread
INCLUDE_PATH := -I../ -I../include -L../lib
GXX = g++-7
BOOST_TEST_OP := --show_progress=yes --build_info=yes --detect_memory_leak=1 --result_code=yes --log_level=all

TEST1 = cxx17/array_view/at_test.o\
	cxx17/array_view/back_test.o\
	cxx17/array_view/front_test.o\
	cxx17/array_view/type_check_test.o\
	cxx17/array_view/substr_test.o\
	mpl/constant_sequence/constant_exp.o\
	mpl/math/compile_time_four_arithmetic_operations_parser_test.o\
	mpl/string/stoi.o\
	cxx17/any_pack/meta_random_engine_test.o\
    range/adaptor/adaptor_exp.o\
	optional/nullopt.o\
	optional/requirements.o\
	optional/make_optional.o\
	optional/swap.o\
	optional/monad.o\
	semaphore/t.o\
	semaphore/t1.o\
	expected/test.o\
	memory/singleton/singleton.o\
	thread/safe/memory/singleton/test1.o\
	hash/sha2/sha2_test.o

all: gcc_target1

gcc_target1: $(TEST1)

$(TEST1): %.o: %.cpp
	cppcheck --enable=all $<
	$(GXX) $(FLAGS) $(INCLUDE_PATH) $< -o $@
run:
	./cxx17/array_view/at_test.o
	./range/adaptor/adaptor_exp.o $(BOOST_TEST_OP)
	./optional/nullopt.o $(BOOST_TEST_OP)
	./optional/requirements.o $(BOOST_TEST_OP)
	./optional/make_optional.o $(BOOST_TEST_OP)
	./optional/swap.o $(BOOST_TEST_OP)
	./optional/monad.o $(BOOST_TEST_OP)
	./semaphore/t.o $(BOOST_TEST_OP)
	./semaphore/t1.o
	./expected/test.o $(BOOST_TEST_OP)
	./memory/singleton/singleton.o $(BOOST_TEST_OP)
	./thread/safe/memory/singleton/test1.o $(BOOST_TEST_OP)
	./hash/sha2/sha2_test.o $(BOOST_TEST_OP)
clean:
	$(RM) $(TEST1)
