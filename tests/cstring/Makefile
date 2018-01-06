#
# Copyright (C) 2011-2017 Roki. Distributed under the MIT License
#

FLAGS := -DSROOK_CONFIG_ENABLE_AVX512_MEMCPY -mavx512f -Wall -Wextra -pedantic -std=c++1z -pthread
INCLUDE_PATH := -I../ -I../include -L../lib
GXX = g++-7
BOOST_TEST_OP := --show_progress=yes --build_info=yes --detect_memory_leak=1 --result_code=yes --log_level=all

TEST1 := cstring/memcpy/avx512_test.o

all: gcc_target1

gcc_target1: $(TEST1)

$(TEST1): %.o: %.cpp
	cppcheck --enable=all $<
	$(GXX) $(FLAGS) $(INCLUDE_PATH) $< -o $@
run:
	../sde-external-8.12.0-2017-10-23-lin/sde64 -knl -- ./cstring/memcpy/avx512_test.o $(BOOST_TEST_OP)
clean:
	$(RM) $(TEST1)
