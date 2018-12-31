// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_BRAINFXXK_LLVM_COMPILER_HPP
#define INCLUDED_SROOK_BRAINFXXK_LLVM_COMPILER_HPP

#include <functional>
#include <srook/brainfk/brainfk.hpp>
#include <srook/scope/unique_resource.hpp>

#if __has_include(<llvm/ADT/Optional.h>) 			and\
	__has_include(<llvm/IR/BasicBlock.h>) 			and\
	__has_include(<llvm/IR/IRBuilder.h>) 			and\
	__has_include(<llvm/IR/LegacyPassManager.h>) 	and\
	__has_include(<llvm/IR/Module.h>) 				and\
	__has_include(<llvm/Support/FileSystem.h>) 		and\
	__has_include(<llvm/Support/TargetRegistry.h>) 	and\
	__has_include(<llvm/Support/TargetSelect.h>) 	and\
	__has_include(<llvm/Support/raw_ostream.h>) 	and\
	__has_include(<llvm/Target/TargetMachine.h>) 	and\
	__has_include(<llvm/Target/TargetOptions.h>)
#include <llvm/ADT/Optional.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#else
#error "This feature needs llvm libraries"
#endif

namespace srook {
namespace brainfk{
SROOK_INLINE_NAMESPACE(v1)

template <class String, class FileStream, class BYTE, std::size_t BUFFER_SIZE = 300000>
struct brainfk_syntax_llvm_compiler_core : brainfk_syntax_core<String, FileStream, BYTE, BUFFER_SIZE> {

    using base_type = brainfk_syntax_core<String, FileStream, BYTE, BUFFER_SIZE>;

    brainfk_syntax_llvm_compiler_core(const std::array<String, 8>& tk)
     	: base_type::brainfk_syntax_core(tk),llvm_wrap(nullptr)
    {}

    const OPTIONAL<String>& execer(decltype(std::cout) & outer) override
    {
		llvm_wrap = std::make_unique<llvm_brainfk_wrapper>();
		
		llvm_wrap->allocate(BUFFER_SIZE);
		{
			auto scoped_llvm = srook::make_unique_resource(llvm_wrap.get(),[this](llvm_brainfk_wrapper*& ll){ll->destroy();});

			std::array<typename llvm_brainfk_wrapper::LoopBlock,BUFFER_SIZE> buff{};
			typename decltype(buff)::iterator iter = std::begin(buff);
        	std::size_t buff_index = 0;

        	if (!this -> fl) {
            	return this -> fl;
        	}
        	for (std::size_t i = 0; i < this->tokenizer.size(); ++i) {
            	switch (this->tokenizer[i]) {
            	case base_type::Syn::LEFT_ARROW:
                	llvm_wrap->move_ptr(1);
                	break;
            	case base_type::Syn::RIGHT_ARROW:
               		llvm_wrap->move_ptr(-1);
                	break;
            	case base_type::Syn::PLUS:
                	llvm_wrap->incdecr(1);
                	break;
            	case base_type::Syn::MINUS:
                	llvm_wrap->incdecr(-1);
                	break;
            	case base_type::Syn::DOT:
                	llvm_wrap->put();
                	break;
            	case base_type::Syn::CAMMA:
					llvm_wrap->get();
               	 	break;
            	case base_type::Syn::LEFT_BRACE:
					llvm_wrap->loop_start(iter++,buff_index++);
                	break;
            	case base_type::Syn::RIGHT_BRACE:
					if(--iter < std::begin(buff))return (this -> fl = NULLOPT);
					llvm_wrap->loop_end(iter);
                	break;
            	}
        	}
		}
		analyzed = true;

        return this -> fl;
    }

	void dump_IR()
	{
		if(analyzed){
			llvm_wrap->get_module()->dump();
		}
	}

	void output_object(std::string output_object_name)
	{
		if(!analyzed)return;

		using namespace llvm;

		InitializeAllTargetInfos();
		InitializeAllTargets();
		InitializeAllTargetMCs();
		InitializeAllAsmParsers();
		InitializeAllAsmPrinters();
		
		const std::string target_triple = sys::getDefaultTargetTriple();
		std::string err;
		const Target* target = TargetRegistry::lookupTarget(target_triple,err);
		if(!target){
			std::cerr << "Failed to lookup target: " << err << std::endl;
			return;
		}
		TargetOptions opt;
		TargetMachine* target_m = target->createTargetMachine(target_triple,"generic","",opt,Optional<Reloc::Model>());
		llvm_wrap->get_module()->setTargetTriple(target_triple);
		llvm_wrap->get_module()->setDataLayout(target_m->createDataLayout());

		std::error_code err_code;
		raw_fd_ostream dest(std::move(output_object_name),err_code,sys::fs::F_None);
		if(err_code){
			std::cerr << "Failed to open file: " << err_code.message() << "\n";
			return;
		}
		legacy::PassManager pass;
		if(target_m->addPassesToEmitFile(pass,dest,TargetMachine::CGFT_ObjectFile)){
			std::cerr << "Failed to emit a file of this type\n";
		}
		pass.run(*llvm_wrap->get_module());
		dest.flush();
	}
private:
	struct llvm_brainfk_wrapper{
		struct LoopBlock{
			llvm::BasicBlock* cond;
			llvm::BasicBlock* body;
			llvm::BasicBlock* end;
		};
		
		explicit llvm_brainfk_wrapper()
			: context_{},
			builder_{context_},
			module_{std::make_unique<llvm::Module>("top",context_)},
			main_function_{llvm::Function::Create(llvm::FunctionType::get(llvm::Type::getInt32Ty(context_),false),llvm::Function::ExternalLinkage,"main",module_.get())},
			data_{nullptr},ptr_{nullptr}
		{
			using namespace llvm;
			builder_.SetInsertPoint(BasicBlock::Create(context_,"",main_function_));
		}

		llvm::Value* allocate(const std::size_t size)
		{
			using namespace llvm;
			data_ = builder_.CreateAlloca(builder_.getInt8PtrTy(),nullptr,"data_");
			ptr_ = builder_.CreateAlloca(builder_.getInt8PtrTy(),nullptr,"ptr_");
			Function* calloc = cast<Function>(module_->getOrInsertFunction("calloc",builder_.getInt8PtrTy(),builder_.getInt64Ty(),builder_.getInt64Ty(),nullptr));
			Value* data_ptr = builder_.CreateCall(calloc,{builder_.getInt64(size),builder_.getInt64(1)});
			builder_.CreateStore(data_ptr,data_);
			builder_.CreateStore(data_ptr,ptr_);
			
			return data_;
		}

		void loop_start(typename std::array<LoopBlock,BUFFER_SIZE>::iterator iter,std::size_t index)
		{
			using namespace llvm;
			using namespace std::string_literals;
			
			iter->cond = BasicBlock::Create(context_,"loop_cond"s + std::to_string(index),main_function_);
			iter->body = BasicBlock::Create(context_,"loop_body"s + std::to_string(index),main_function_);
			iter->end = BasicBlock::Create(context_,"loop_end"s + std::to_string(index),main_function_);
			builder_.CreateBr(iter->cond);
			builder_.SetInsertPoint(iter->cond);
			builder_.CreateCondBr(builder_.CreateICmpNE(builder_.CreateLoad(builder_.CreateLoad(ptr_)),builder_.getInt8(0)),iter->body,iter->end);
			builder_.SetInsertPoint(iter->body);
		}

		void loop_end(typename std::array<LoopBlock,BUFFER_SIZE>::iterator iter)
		{
			builder_.CreateBr(iter->cond);
			builder_.SetInsertPoint(iter->end);
		}

		void move_ptr(int diff)
		{
			builder_.CreateStore(builder_.CreateInBoundsGEP(builder_.getInt8Ty(),builder_.CreateLoad(ptr_),builder_.getInt32(diff)),ptr_);
		}

		void incdecr(int diff)
		{
			using llvm::Value;
			Value* tmp = builder_.CreateLoad(ptr_);
			builder_.CreateStore(builder_.CreateAdd(builder_.CreateLoad(tmp),builder_.getInt8(diff)),tmp);
		}

		void put()
		{
			using namespace llvm;
			Function* putchar = cast<Function>(module_->getOrInsertFunction("putchar",builder_.getInt32Ty(),builder_.getInt32Ty(),nullptr));
			builder_.CreateCall(putchar,builder_.CreateSExt(builder_.CreateLoad(builder_.CreateLoad(ptr_)),builder_.getInt32Ty()));
		}

		void get()
		{
			using namespace llvm;
			Function* getchar = cast<Function>(module_->getOrInsertFunction("getchar",builder_.getInt32Ty(),builder_.getInt32Ty(),nullptr));
			builder_.CreateStore(builder_.CreateTrunc(builder_.CreateCall(getchar),builder_.getInt8Ty()),builder_.CreateLoad(ptr_));
		}

		void destroy()
		{
			using namespace llvm;
			Function* free = cast<Function>(module_->getOrInsertFunction("free",builder_.getVoidTy(),builder_.getInt8PtrTy(),nullptr));
			builder_.CreateCall(free,{builder_.CreateLoad(data_)});
			builder_.CreateRet(builder_.getInt32(EXIT_SUCCESS));
		}

		std::unique_ptr<llvm::Module>& get_module()
		{
			return module_;
		}
	private:
		llvm::LLVMContext context_;
		llvm::IRBuilder<> builder_;
		std::unique_ptr<llvm::Module> module_;
		llvm::Function* main_function_;
		llvm::Value* data_,*ptr_;
	};
private:
	std::unique_ptr<llvm_brainfk_wrapper> llvm_wrap;  
	bool analyzed = false;
};

template <class, class = unsigned char, std::size_t = 300000>
struct brainfk_syntax_llvm_compiler;
template <class BYTE, std::size_t size>
struct brainfk_syntax_llvm_compiler<std::string, BYTE, size> final : brainfk_syntax_llvm_compiler_core<std::string, std::ifstream, BYTE, size> {
    using brainfk_syntax_llvm_compiler_core<std::string, std::ifstream, BYTE, size>::brainfk_syntax_llvm_compiler_core;
};
template <class BYTE, std::size_t size>
struct brainfk_syntax_llvm_compiler<std::wstring, BYTE, size> final : brainfk_syntax_llvm_compiler_core<std::wstring, std::wifstream, BYTE, size> {
    using brainfk_syntax_llvm_compiler_core<std::wstring, std::wifstream, BYTE, size>::brainfk_syntax_llvm_compiler_core;
};

SROOK_INLINE_NAMESPACE_END
} // namespace brainfk
} // namespace srook
#endif
