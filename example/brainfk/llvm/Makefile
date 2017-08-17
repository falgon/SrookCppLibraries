TARGET = brainfk_llvm_compiler_generator_example.cpp
CXX = /usr/local/Cellar/llvm/4.0.1/bin/clang++ # Any clang
FLAGS = -std=c++1z
INCLUDE_PATH = -I$(HOME)/Documents/src/cpp/IncludeLibraries/ -I /usr/local/Cellar/boost/1.64.0_1/include/ # Using boost
LIB_PATH = `llvm-config --cxxflags --ldflags --libs --system-libs`

target: $(TARGET)
	$(CXX) $(LIB_PATH) $(FLAGS) $(INCLUDE_PATH) $(TARGET)
run: $(TARGET)
	$(CXX) $(LIB_PATH) $(FLAGS) $(INCLUDE_PATH) $(TARGET)
	./a.out # dump
	./a.out 2>&1 | lli # pipe lli
	$(CXX) output.o -o fizzbuzz # assembly object file
	./fizzbuzz # execute binary
clean: a.out
	$(RM) output.o fizzbuzz a.out

