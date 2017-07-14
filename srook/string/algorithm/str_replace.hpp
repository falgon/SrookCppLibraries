// Copyright (C) 2017 Roki
#ifndef INCLUDED_STRING_REPLACE
#define INLCUDED_STRING_REPLACE
#include<string>
#include<cstring>

namespace srook{
inline namespace v1{
	
std::string& str_replace(std::string& str,const char* src,const char* rhs)
{
	if(str.empty()||!src||!*src||!rhs||!std::strcmp(src,rhs))return str;
	
	const size_t src_len=std::strlen(src);
	const size_t rhs_len=std::strlen(rhs);
	for(std::string::size_type i=0;
			(i=str.find(src,i,src_len))!=std::string::npos;
			i+=rhs_len)
		str.replace(i,src_len,rhs,rhs_len);
	return str;
}

}
}
#endif
