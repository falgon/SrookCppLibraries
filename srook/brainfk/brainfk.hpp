#ifndef INCLUDED_SROOK_BRAINFXXK_INTERPINTER_HPP
#define INCLUDED_SROOK_BRAINFXXK_INTERPINTER_HPP
#include<fstream>
#include<sstream>
#include<array>
#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<locale>
#include<codecvt>

#include<boost/optional.hpp>
#include<boost/algorithm/cxx11/all_of.hpp>
#include<srook/mpl/variadic_player.hpp>
#include<srook/config/require.hpp>

namespace srook{

template<class String,class FileStream,class BYTE,std::size_t BUFFER_SIZE=300000>
struct brainfk_syntax_core{
	using string_type=std::string;
	using byte=BYTE;

	brainfk_syntax_core(const std::array<String,8>& tokens)
		:token(tokens),
		token_syn{{Syn::LEFT_ARROW,Syn::RIGHT_ARROW,Syn::PLUS,Syn::MINUS,Syn::DOT,Syn::CAMMA,Syn::LEFT_BRACE,Syn::RIGHT_BRACE}}
	{}
	
	const boost::optional<String>& file_open(std::string file_name)
	{
		FileStream ifs;
		return file_open_core(ifs,std::move(file_name));
	}

	const boost::optional<String>& analyze()
	{
		return analyze_core(String());
	}

	const boost::optional<String>& exec()
	{
		return exec_core(String());
	}

	void* operator new(std::size_t)=delete;
	void operator delete(void*)=delete;
private:
	enum struct Syn{
		LEFT_ARROW,RIGHT_ARROW,PLUS,MINUS,DOT,CAMMA,LEFT_BRACE,RIGHT_BRACE
	};
	static constexpr std::size_t syntax_size=8;

	const std::array<String,syntax_size>& token;
	const std::array<Syn,syntax_size> token_syn;
	std::vector<Syn> tokenizer;

	const boost::optional<std::string>& file_open_core(std::ifstream& ifs,std::string file_name)
	{
		if(ifs.fail())return(fl=boost::none);
		
		ifs.open(std::move(file_name),std::ios::in);
		std::ostringstream os;
		os<<ifs.rdbuf();
		return (fl=os.str());
	}
	
	const boost::optional<std::wstring>& file_open_core(std::wifstream& ifs,std::string file_name)
	{
		const std::codecvt_mode kBom = static_cast<std::codecvt_mode>(std::generate_header | std::consume_header);
		using WideConvUtf8Bom=std::codecvt_utf8<wchar_t, 0x10ffff, kBom>;
		WideConvUtf8Bom cvt(1);
		
		std::locale loc(ifs.getloc(),&cvt);
		auto oldLocale=ifs.imbue(std::move(loc));
		ifs.open(std::move(file_name),std::ios::in | std::ios::binary);
		
		std::wstringstream wss;
		wss<<ifs.rdbuf();
		
		std::wstring removeStr=L"\r";
		auto pos(wss.str().find(removeStr));

		while(pos!=std::wstring::npos){
			wss.str().replace(pos,removeStr.length(),L"");
			pos=wss.str().find(removeStr,pos);
		}
		ifs.close();
		ifs.imbue(oldLocale);

		return (fl=wss.str());
	}

	const boost::optional<String>& analyze_core(const std::string&&)
	{
		return analyzer(std::string::npos);
	}
	const boost::optional<String>& analyze_core(const std::wstring&&)
	{
		return analyzer(std::string::npos);
	}

	template<class T>
	const boost::optional<String>& analyzer(const T& npos)
	{
		if(!fl){return fl;}
		const std::size_t fl_size=fl->size();
		for(std::size_t c=0; !(*fl).empty() || c<fl_size; ++c){
			std::map<std::size_t,std::pair<String,Syn>> indexer;
			std::array<bool,syntax_size> bits; bits.fill(true);

			std::size_t pos=0,i=0;
			for(const auto& t:token){
				if((pos=(*fl).find(t))==npos)bits[i]=false;
				else indexer[pos]=std::make_pair(t,token_syn[i]);
				++i;
			}
			if(boost::algorithm::all_of(bits,[](const bool b){return b==false;}))break;

			tokenizer.emplace_back(indexer.begin()->second.second);
			(*fl).erase(indexer.begin()->first,indexer.begin()->second.first.size());
		}
		return fl;
	}

	template<class Str>
	const boost::optional<String>& exec_core(const Str&&)
	{
		return execer(std::cout);
	}

	const boost::optional<String>& execer(decltype(std::cout)& outer)
	{
		std::array<byte,BUFFER_SIZE> buff;
		std::size_t buff_ptr=0,loop_b=0;
	
		if(!fl){return fl;}
		for(std::size_t i=0; i<tokenizer.size(); ++i){
			switch(tokenizer[i]){
				case Syn::LEFT_ARROW: ++buff_ptr; break;
				case Syn::RIGHT_ARROW: --buff_ptr; break;
				case Syn::PLUS: ++buff[buff_ptr]; break;
				case Syn::MINUS: --buff[buff_ptr]; break;
				case Syn::DOT: outer<<buff[buff_ptr]; break;
				case Syn::CAMMA: buff[buff_ptr]=std::getchar(); break;
				case Syn::LEFT_BRACE:
								 if(buff[buff_ptr]==0)
									 for(++i; loop_b>0 || tokenizer[i]!=Syn::RIGHT_BRACE; ++i){
										 if(tokenizer[i]==Syn::LEFT_BRACE)++loop_b;
										 else if(tokenizer[i]==Syn::RIGHT_BRACE)--loop_b;
									 }
								 break;
				case Syn::RIGHT_BRACE:
								 if(buff[buff_ptr]!=0){
									 for(--i; loop_b>0 || tokenizer[i]!=Syn::LEFT_BRACE; --i){
										 if(tokenizer[i]==Syn::RIGHT_BRACE)++loop_b;
										 if(tokenizer[i]==Syn::LEFT_BRACE)--loop_b;
									 }
									 --i;
								 }
								 break;
			}
		}
		return fl;
	}

public:
	boost::optional<String> fl;
};

template<class,class,std::size_t=300000>
struct brainfk_syntax;
template<class BYTE,std::size_t size>
struct brainfk_syntax<std::string,BYTE,size> final:brainfk_syntax_core<std::string,std::ifstream,BYTE,size>{
	using brainfk_syntax_core<std::string,std::ifstream,BYTE,size>::brainfk_syntax_core;
};
template<class BYTE,std::size_t size>
struct brainfk_syntax<std::wstring,BYTE,size> final:brainfk_syntax_core<std::wstring,std::wifstream,BYTE,size>{
	using brainfk_syntax_core<std::wstring,std::wifstream,BYTE,size>::brainfk_syntax_core;
};

} // namespace srook
#endif
