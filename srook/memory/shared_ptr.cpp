#include<iostream>

#ifndef INCLUDED_SROOK_MEMORY_SHARED_PTR
#define INCLUDED_SROOK_MEMORY_SHARED_PTR

#if __has_include(<memory>)
#include<memory>
#define POSSIBLE_TO_INCLUDE_STD_MEMORY
#elif __has_include(<boost/shared_ptr.hpp>)
#include<boost/shared_ptr.hpp>
#define POSSIBLE_TO_INCLUDE_BOOST_SHARED_PTR
#else

// then,C++03 or other code ...

#include<srook/config/require.hpp>
#include<srook/type_traits/add_pointer.hpp>
#include<srook/config/nullptr.hpp>

#ifdef POSSIBLE_TO_USE_STD_NULLPTR
#define NULLPTR nullptr
#else
#define NULLPTR srook::nullptr
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
	reference_count_type* reference_count;
public:
	shared_ptr()throw():data_(NULLPTR),reference_count(NULLPTR){}
	shared_ptr(std::nullptr_t)throw():data_(NULLPTR),reference_count(NULLPTR){}
	
	shared_ptr(pointer_type ptr)
		:data_(std::move(ptr))
	{
		static reference_count_type counter=1;
		reference_count=&counter;
	}

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
		if(!--*(reference_count))
			delete data_;
	}

	T& operator*()
	{
		return *data_;
	}

	T* operator->()
	{
		return data_;
	}

	T* get()
	{
		return data_;
	}

	const reference_count_type& use_count()const throw()
	{
		return *reference_count;
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
		std::swap(other.reference_count,reference_count);
	}

	void reset()
	{
		data_=NULLPTR;
		--(*reference_count);
	}

	template<class U>
	void reset(U* ptr)
	{
		data_=ptr;
		--(*reference_count);
		static reference_count_type counter=1;
		reference_count=&counter;
	}
};


} // namespace srook
#endif
#endif
