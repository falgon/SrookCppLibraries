#include <srook/brainfk/llvm/brainfk_compiler.hpp>

int main()
{
    using namespace std::string_literals;
    namespace br_keywords = srook::brainfk::label;
    
	const auto bk_keywords = srook::brainfk::make_keywords((
        br_keywords::_INCREMENT_THE_POINTER = ">"s,
        br_keywords::_DECREMENT_THE_POINTER = "<"s,
        br_keywords::_INCREMENT_THE_BYTE_AT_THE_POINTER = "+"s,
        br_keywords::_DECREMENT_THE_BYTE_AT_THE_POINTER = "-"s,
        br_keywords::_OUTPUT = "."s,
        br_keywords::_INPUT = ","s,
        br_keywords::_JUMP_FORWARD = "["s,
        br_keywords::_JUMP_BACKWARD = "]"s));

    srook::brainfk::brainfk_syntax_llvm_compiler<std::string> bkcomp(bk_keywords);
	if(!bkcomp.file_open("../sample_bf/fizzbuzz.bf")){
		return EXIT_FAILURE;
	}
	if(!bkcomp.analyze()){
		return EXIT_FAILURE;
	}
	bkcomp.exec();
	bkcomp.dump_IR();
	bkcomp.output_object("output.o");
}
