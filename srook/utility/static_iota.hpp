#ifndef INCLUDED_STATIC_IOTA
#define INCLUDED_STATIC_IOTA
#include<boost/preprocessor/repetition/repeat_from_to.hpp>
#define static_iota_t(z,x,text) x,
#define static_iota(x,y) BOOST_PP_REPEAT_FROM_TO(x,y,static_iota_t,_)
#define IIOTA static_iota
#define INIT_IOTA static_iota
#endif
