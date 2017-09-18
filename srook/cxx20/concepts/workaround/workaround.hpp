#ifndef INLCLUDED_SROOK_CXX20_CONCEPT_WORK_AROUND_HPP
#define INLCLUDED_SROOK_CXX20_CONCEPT_WORK_AROUND_HPP

#ifdef __cpp_concepts
#	define SROOK_HAS_CONCEPTS 1
#		if __cpp_concepts >= 201507
#			define SROOK_CONCEPT concept bool // This is a Concept TS, not C++20
//		
//#		elif __cpp_concepts ....
//#			define SROOK_CONCEPT concept // Any compilers are not supported C++20 concept at 2017-09-19
#		endif
#else
#	define SROOK_HAS_CONCEPTS 0
#endif

#endif
