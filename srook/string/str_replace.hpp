#ifndef INCLUDED_STRING_REPLACE
#define INLCUDED_STRING_REPLACE
#include<string>
#include<cstring>

namespace srook{
<<<<<<< HEAD
namespace v1{
=======
inline namespace v1{
>>>>>>> 3fcc3fa90d2434943b137c5f6ea2d36a1277fa08

std::string& str_replace(std::string& str,const char* src,const char* rhs)
{
	if(str.empty()||!src||!*src||!rhs||!strcmp(src,rhs))
		return str;
	const size_t src_len=strlen(src);
	const size_t rhs_len=strlen(rhs);
	for(std::string::size_type i=0;
			(i=str.find(src,i,src_len))!=std::string::npos;
			i+=rhs_len)
		str.replace(i,src_len,rhs,rhs_len);
	return str;
}

}
}
#endif
