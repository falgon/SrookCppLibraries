// Copyright (C) 2011-2019 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_MEMORY_SHARED_PTR
#define INCLUDED_SROOK_MEMORY_SHARED_PTR

#if __has_include(<memory>)
#	include<memory>
#	define POSSIBLE_TO_USE_STD_SHARED_PTR
#elif __has_include(<boost/shared_ptr.hpp>)
#	include<boost/shared_ptr.hpp>
#	define POSSIBLE_TO_USE_BOOST_SHARED_PTR
#else

// C++03 or other code ...

#include<srook/config/require.hpp>
#include<srook/type_traits/add_pointer.hpp>
#include<srook/config/nullptr.hpp>

#ifdef POSSIBLE_TO_USE_STD_NULLPTR
#define NULLPTR nullptr
#define NULLPTR_T std::nullptr_t
#else
#define NULLPTR srook::nullptr
#define NULLPTR_T srook::nullptr_t
#endif

namespace srook{

template<class T>
struct shared_ptr_core{
public:
	typedef T element_type;
	typedef element_type* pointer_type;
	typedef T& reference_type;
	typedef std::size_t reference_count_type;
private:
	void* operator new(std::size_t);
	void* operator new[](std::size_t);
	void operator delete(void*,std::size_t);
	void operator delete[](void*,std::size_t);
protected:
	struct bool_tester{
	private:
		void operator delete(void*,std::size_t);
		void operator delete[](void*,std::size_t);
	};
};


template<class T>
class shared_ptr:protected shared_ptr_core<T>{
public:
	typedef typename shared_ptr_core<T>::element_type element_type;
	typedef typename shared_ptr_core<T>::pointer_type pointer_type;
	typedef typename shared_ptr_core<T>::reference_type reference_type;
	typedef typename shared_ptr_core<T>::reference_count_type reference_count_type;
private:
	pointer_type data_;

	struct UInt_Constructor{
		void swap(UInt_Constructor& other)throw()
		{
			std::swap(counter,other.counter);
		}
		
		reference_count_type& operator*()const throw()
		{
			return counter;
		}
		
		UInt_Constructor& operator++()throw()
		{
			++counter;
			return *this;
		}
		
		UInt_Constructor& operator++(int)throw()
		{
			UInt_Constructor tmp=*this;
			++counter;
			return tmp;
		}

		UInt_Constructor& operator--()throw()
		{
			--counter;
			return *this;
		}

		UInt_Constructor& operator--(int)throw()
		{
			UInt_Constructor tmp=*this;
			--counter;
			return *this;
		}

		UInt_Constructor* operator&()
		{
			return this;
		}

		operator bool()
		{
			return static_cast<bool>(counter);
		}

		static UInt_Constructor* instance(std::size_t x)
		{
			return new UInt_Constructor(x);
		}

		void destroy()throw()
		{
			delete this;
		}
	private:
		explicit UInt_Constructor(reference_count_type counter):counter(counter){}

		reference_count_type counter;
	}* reference_count;

public:
	shared_ptr()throw():data_(NULLPTR),reference_count(NULLPTR){}
	shared_ptr(NULLPTR_T)throw():data_(NULLPTR),reference_count(NULLPTR){}
	
	shared_ptr(pointer_type ptr)
		:data_(ptr),reference_count(UInt_Constructor::instance(1))
	{}

	template<class U>
	shared_ptr(shared_ptr<U>& other)
		:data_(other.get()),reference_count(other.use_count())
	{
		if(other.data_!=data_)++(*other.reference_count);
	}
	
	shared_ptr(shared_ptr& other)throw()
		:data_(other.data_),reference_count(&(++(*other.reference_count)))
	{}

	shared_ptr& operator=(shared_ptr& other)throw()
	{
		if(other.data_!=data_){
			data_=other.data_;
			reference_count=other.reference_count;
			++(*other.reference_count);
		}
		return *this;
	}

	~shared_ptr()throw()
	{
		if(!--(*reference_count)){
			delete data_;
			reference_count->destroy();
		}
	}

	T& operator*()const
	{
		return *data_;
	}

	T* operator->()const throw()
	{
		return data_;
	}

	T* get()const
	{
		return data_;
	}

	const reference_count_type& use_count()const throw()
	{
		return **reference_count;
	}

	bool unique()const throw()
	{
		return use_count()==1;
	}

	operator typename shared_ptr_core<T>::bool_tester*()const throw()
	{
		if(!data_)return NULLPTR;
		static typename shared_ptr_core<T>::bool_tester tester;
		return &tester;
	}

	void swap(shared_ptr& other)throw()
	{
		std::swap(other.data_,data_);
		reference_count->swap(*other.reference_count);
	}

	void reset()throw()
	{
		data_=NULLPTR;
		--(*reference_count);
	}

	template<class U>
	void reset(U* ptr)
	{
		data_=ptr;
		if(!--(*reference_count))reference_count->destroy();;
		reference_count=UInt_Constructor::instance(1);
	}
	
	template<class L>
	friend bool operator==(const shared_ptr<L>& l,NULLPTR_T)throw()
	{
		return l.data_==NULLPTR;
	}
	template<class R>
	friend bool operator==(NULLPTR_T,const shared_ptr<R>& r)throw()
	{
		return operator==(r,NULLPTR);
	}
	template<class L,class R>
	friend bool operator==(const shared_ptr<L>& l,const shared_ptr<R>& r)throw()
	{
		return l.data_==r.data_;
	}
	
	template<class L>
	friend bool operator!=(const shared_ptr<L>& l,NULLPTR_T)throw()
	{
		return !operator==(l,NULLPTR);
	}
	template<class R>
	friend bool operator!=(NULLPTR_T,const shared_ptr<R>& r)throw()
	{
		return !operator==(r,NULLPTR);
	}
	template<class L,class R>
	friend bool operator!=(const shared_ptr<L>& l,const shared_ptr<R>& r)throw()
	{
		return !operator==(l,r);
	}

	template<class L>
	friend bool operator<(const shared_ptr<L>&,NULLPTR_T)throw()
	{
		return false;
	}
	template<class R>
	friend bool operator<(NULLPTR_T,const shared_ptr<R>&)throw()
	{
		return true;
	}
	template<class L,class R>
	friend bool operator<(const shared_ptr<L>& l,const shared_ptr<R>& r)throw()
	{
		return l.data_<r.data_;
	}
	
	template<class L>
	friend bool operator>(const shared_ptr<L>&,NULLPTR_T)throw()
	{
		return true;
	}
	template<class R>
	friend bool operator>(NULLPTR_T,const shared_ptr<R>&)throw()
	{
		return false;
	}
	template<class L,class R>
	friend bool operator>(const shared_ptr<L>& l,const shared_ptr<R>& r)throw()
	{
		return !operator<(l,r);
	}
	
	template<class L>
	friend bool operator<=(const shared_ptr<L>& l,NULLPTR_T)throw()
	{
		return !l.data_;
	}
	template<class R>
	friend bool operator<=(NULLPTR_T,const shared_ptr<R>&)throw()
	{
		return true;
	}
	template<class L,class R>
	friend bool operator<=(const shared_ptr<L>& l,const shared_ptr<R>& r)throw()
	{
		return operator<(l,r) or l.data_==r.data_;
	}
	
	template<class L>
	friend bool operator>=(const shared_ptr<L>&,NULLPTR_T)throw()
	{
		return true;
	}
	template<class R>
	friend bool operator>=(NULLPTR_T,const shared_ptr<R>& r)throw()
	{
		return !r.data_;
	}
	template<class L,class R>
	friend bool operator>=(const shared_ptr<L>& l,const shared_ptr<R>& r)throw()
	{
		return operator>(l,r) or l.data_==r.data_;
	}

	template<class R>
	friend std::ostream& operator<<(std::ostream& os,const shared_ptr<R>& ptr)
	{
		return os<<ptr.get();
	}
};


} // namespace srook
#endif
#endif
