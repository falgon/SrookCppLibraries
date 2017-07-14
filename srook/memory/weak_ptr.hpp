// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_MEMORY_WEAK_PTR_HPP
#define INCLUDED_SROOK_MEMORY_WEAK_PTR_HPP

#if __has_include(<memory>)
#	include<memory>
#	define POSSIBLE_TO_USE_STD_WEAK_PTR
#elif __has_include(boost/weak_ptr.hpp>)
#	include<boost/weak_ptr.hpp>
#	define POSSIBLE_TO_USE_BOOST_WEAK_PTR
#else
// C++03 code..

#include<srook/config/nullptr.hpp>
#include<srook/memory/shared_ptr.hpp>

#ifdef POSSIBLE_TO_USE_STD_SHARED_PTR
#	define SHARED_PTR std::shared_ptr
#elif POSSIBLE_TO_USE_BOOST_SHARED_PTR
#	define SHARED_PTR boost::shared_ptr
#else
#	define SHARED_PTR srook::shared_ptr
#endif

namespace srook{

template<class>
class weak_ptr;

namespace{
	template<class U>
	struct mover{
		U& u_ptr;
		explicit mover(U& u_ptr)throw():u_ptr(u_ptr){}
	};
}

template<class T>
mover<weak_ptr<T> > move(weak_ptr<T>&)throw();

template<class T>
class weak_ptr{
public:
	typedef T element_type;
	typedef T* pointer_type;
	typedef pointer_type pointer;
private:
	const SHARED_PTR<element_type>* source_;
public:
	weak_ptr()throw():source_(NULLPTR){}
	
	weak_ptr(const weak_ptr& other)throw():source_(other.source_){}

	template<class U>
	weak_ptr(const weak_ptr<U>& other)throw():source_(other.source_){}

	template<class U>
	weak_ptr(const SHARED_PTR<U>& r)throw():source_(&r){}

	template<class U>
	weak_ptr(mover<U> m)throw():source_(m.u_ptr.source_) // simulating move ctor
	{
		m.u_ptr.source_=NULLPTR;
	}

	weak_ptr& operator=(const weak_ptr& other)throw()
	{
		source_=other.source_;
		return *this;
	}

	template<class U>
	weak_ptr& operator=(const weak_ptr<U>& other)throw()
	{
		source_=other.source_;
		return *this;
	}

	template<class U>
	weak_ptr& operator=(mover<U> m)throw() // simulating move assign
	{
		source_=m.u_ptr.source_;
		m.u_ptr.source_=NULLPTR;
		return *this;
	}

	template<class U>
	weak_ptr& operator=(const SHARED_PTR<U>& shared)throw()
	{
		source_=&shared;
		return *this;
	}

	template<class U>
	void swap(weak_ptr<U>& other)throw()
	{
		std::swap(other.source_,source_);
	}
	
	void reset()throw()
	{
		weak_ptr().swap(*this);
	}

	long use_count()const throw()
	{
		if(source_)return source_->use_count();
		return 0;
	}

	operator bool()
	{
		return use_count();
	}

	template<class U>
	bool owner_before(const SHARED_PTR<U>& shptr)const
	{
		return data_<shptr.get();
	}

	template<class U>
	bool owner_before(const weak_ptr<U>& other)const
	{
		return data_<other;
	}

	bool expired()const throw()
	{
		return use_count()==0;
	}

	SHARED_PTR<element_type> lock()throw() const
	{
		return expired()?SHARED_PTR<element_type>():SHARED_PTR<T>(data_->get());
	}

	friend mover<weak_ptr<element_type> > move<element_type>(weak_ptr<element_type>&)throw();
};

template<class T>
mover<weak_ptr<T> >  move(weak_ptr<T>& wk)throw()
{
	return mover<weak_ptr<T> >(wk);
}

} // namespace srook

#endif
#endif
