#ifndef INCLUDED_SROOK_MEMORY_UNIQUE_PTR_HPP
#define INCLUDED_SROOK_MEMORY_UNIQUE_PTR_HPP
#if __has_include(<memory>)
#include<memory>
#define POSSIBLE_TO_INCLUDE_STD_MEMORY
#elif __has_include(<boost/unique_ptr.hpp>)
#include<boost/unique_ptr.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_UNIQUE_PTR
#else
// C++03 or etc ...

#include<srook/config/nullptr.hpp>
#ifdef POSSIBLE_TO_USE_STD_NULLPTR
#define NULLPTR nullptr
#define NULLPTR_T std::nullptr_t
#else
#define NULLPTR srook::nullptr
#define NULLPTR_T srook::nullptr_t
#endif

namespace srook{
namespace detail{

template<class>
class unique_ptr;

namespace{
	template<class U>
	struct mover{
		U& u_ptr;
		explicit mover(U& u_ptr)throw():u_ptr(u_ptr){}
	};
}

template<class T>
mover<unique_ptr<T> > move(unique_ptr<T>&)throw();

template<class T>
struct unique_ptr_core{
	typedef T element_type;
	typedef T* pointer_type;
	typedef T& reference_type;
private:
	void* operator new(std::size_t);
	void* operator new[](std::size_t);
	void operator delete(void*);
	void operator delete[](void*);
protected:
	struct bool_tester{
	private:
		void operator delete(void*);
		void operator delete[](void*);
	};
};

template<class T>
class unique_ptr:private unique_ptr_core<T>{
public:
	typedef typename unique_ptr_core<T>::element_type element_type;
	typedef typename unique_ptr_core<T>::pointer_type pointer_type;
	typedef pointer_type pointer;
	typedef typename unique_ptr_core<T>::reference_type reference_type;
protected:
	pointer_type data_;
	bool is_array;
	unique_ptr(const unique_ptr&);

	static mover<unique_ptr<T> > move_impl(unique_ptr& ot)throw()
	{
		return mover<unique_ptr<T> >(ot);
	}

	explicit unique_ptr(pointer_type ptr,bool b)throw():data_(ptr),is_array(b){}
public:
	explicit unique_ptr()throw():data_(NULLPTR),is_array(false){}

	explicit unique_ptr(NULLPTR_T)throw():data_(NULLPTR),is_array(false){}
	
	explicit unique_ptr(pointer_type ptr)throw():data_(ptr),is_array(false){}

	unique_ptr(mover<unique_ptr> other)throw():data_(other.u_ptr.data_),is_array(other.is_array) // simulating move constructor
	{
		other.u_ptr.data_=NULLPTR;
		other.u_ptr.is_array=false;
	}

	template<class U>
	unique_ptr(mover<unique_ptr<U> > other)throw():data_(other.u_ptr.data_),is_array(other.is_array) // simulating move constructor
	{
		other.u_ptr.data_=NULLPTR;
		other.u_ptr.is_array=false;
	}

	unique_ptr& operator=(mover<unique_ptr> other)throw() // simulating move assign
	{
		data_=other.u_ptr.data_;
		is_array=other.u_ptr.is_array;
		other.u_ptr.data_=NULLPTR;
		other.u_ptr.is_array=false;
		return *this;
	}

	template<class U>
	unique_ptr& operator=(mover<unique_ptr<U> > other)throw() // simulating move assign
	{
		data_=other.u_ptr.data_;
		is_array=other.u_ptr.is_array;
		other.u_ptr.data_=NULLPTR;
		other.u_ptr.is_array=false;
		return *this;
	}

	reference_type operator*()throw()
	{
		return *data_;
	}

	pointer_type operator->()throw()
	{
		return data_;
	}

	pointer_type release()throw()
	{
		pointer_type tmp=data_;
		data_=NULLPTR;
		return tmp;
	}

	pointer_type get()const throw()
	{
		return data_;;
	}

	void reset(pointer_type ptr=pointer_type())throw()
	{
		if(data_)delete data_;
		data_=ptr;
	}

	operator typename unique_ptr_core<T>::bool_tester*()const throw()
	{
		if(!data_)return NULLPTR;
		static typename unique_ptr_core<T>::bool_tester tester;
		return &tester;
	}

	void swap(unique_ptr& other)throw()
	{
		std::swap(other.data_,data_);
	}

	~unique_ptr()throw()
	{
		if(!is_array and data_)delete data_;
		else if(is_array and data_)delete[] data_;
	}

	friend mover<unique_ptr<element_type> > move<element_type>(unique_ptr<element_type>&)throw();

	template<class L>
	friend bool operator==(const unique_ptr<L>& l,NULLPTR_T)throw()
	{
		return l.data_==NULLPTR;
	}
	template<class R>
	friend bool operator==(NULLPTR_T,const unique_ptr<R>& r)throw()
	{
		return operator==(r,NULLPTR);
	}
	template<class L,class R>
	friend bool operator==(const unique_ptr<L>& l,const unique_ptr<R>& r)throw()
	{
		return l.data_==r.data_;
	}
	
	template<class L>
	friend bool operator!=(const unique_ptr<L>& l,NULLPTR_T)throw()
	{
		return !operator==(l,NULLPTR);
	}
	template<class R>
	friend bool operator!=(NULLPTR_T,const unique_ptr<R>& r)throw()
	{
		return !operator==(r,NULLPTR);
	}
	template<class L,class R>
	friend bool operator!=(const unique_ptr<L>& l,const unique_ptr<R>& r)throw()
	{
		return !operator==(l,r);
	}

	template<class L>
	friend bool operator<(const unique_ptr<L>&,NULLPTR_T)throw()
	{
		return false;
	}
	template<class R>
	friend bool operator<(NULLPTR_T,const unique_ptr<R>&)throw()
	{
		return true;
	}
	template<class L,class R>
	friend bool operator<(const unique_ptr<L>& l,const unique_ptr<R>& r)throw()
	{
		return l.data_<r.data_;
	}
	
	template<class L>
	friend bool operator>(const unique_ptr<L>&,NULLPTR_T)throw()
	{
		return true;
	}
	template<class R>
	friend bool operator>(NULLPTR_T,const unique_ptr<R>&)throw()
	{
		return false;
	}
	template<class L,class R>
	friend bool operator>(const unique_ptr<L>& l,const unique_ptr<R>& r)throw()
	{
		return !operator<(l,r);
	}
	
	template<class L>
	friend bool operator<=(const unique_ptr<L>& l,NULLPTR_T)throw()
	{
		return !l.data_;
	}
	template<class R>
	friend bool operator<=(NULLPTR_T,const unique_ptr<R>&)throw()
	{
		return true;
	}
	template<class L,class R>
	friend bool operator<=(const unique_ptr<L>& l,const unique_ptr<R>& r)throw()
	{
		return operator<(l,r) or l.data_==r.data_;
	}
	
	template<class L>
	friend bool operator>=(const unique_ptr<L>&,NULLPTR_T)throw()
	{
		return true;
	}
	template<class R>
	friend bool operator>=(NULLPTR_T,const unique_ptr<R>& r)throw()
	{
		return !r.data_;
	}
	template<class L,class R>
	friend bool operator>=(const unique_ptr<L>& l,const unique_ptr<R>& r)throw()
	{
		return operator>(l,r) or l.data_==r.data_;
	}
};

template<class T>
class unique_ptr<T[]>:public unique_ptr<T>{
public:
	typedef typename unique_ptr<T>::element_type element_type;
	typedef typename unique_ptr<T>::pointer_type pointer_type;
	typedef typename unique_ptr<T>::pointer pointer;
	typedef typename unique_ptr<T>::reference_type reference_type;
	
	explicit unique_ptr(pointer_type ptr):unique_ptr<T>::unique_ptr(ptr,true){}

	reference_type operator[](std::size_t index)throw()
	{
		return *(this->data_+index);
	}
};

template<class T>
mover<unique_ptr<T> > move(unique_ptr<T>& ot)throw()
{
	return unique_ptr<T>::move_impl(ot);
}


} // namespace detail

using detail::unique_ptr;
using detail::move;

} // namespace srook

#endif
#endif
