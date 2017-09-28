// Copyright (C) 2017 roki
#ifndef INCLUDED_SROOK_CONFIG_NULLPTR_T
#define INCLUDED_SROOK_CONFIG_NULLPTR_T

namespace srook {

const class nullptr_t{
public:
	template <class T>
	operator T*() const { return 0; }

	template <class C, class T>
	operator T C::*() const { return 0; }
private:
	void operator&() const;
} nullptr = {};

} // namespace srook

#endif
