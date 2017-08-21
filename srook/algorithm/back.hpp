// Copyright (C) 2017 roki
#ifndef INCLUDED_EMPLACE_BACK_HPP
#define INCLUDED_EMPLACE_BACK_HPP

namespace srook{
inline namespace v1{
	template<class Container,class... Args>
	inline void emplace_back(Container& container,Args&&... args)
	{
		container.emplace_back(args...);
	}

	template<class Container,class Add_Element>
	inline void push_back(Container& container,Add_Element&& args)
	{
		container.push_back(args);
	}
}
}

#endif
