// Copyright (C) 2017 Roki
#ifndef INCLUDED_SROOK_EXT_OPTIONAL
#define INCLUDED_SROOK_EXT_OPTIONAL
#include<exception>
#include<memory>
#include<type_traits>
#include<utility>
#include<initializer_list>
#include<srook/utility/in_place.hpp>
namespace srook{
namespace detail{
#define EXT_OPTIONAL_REQUIRES(...) std::enable_if_t<__VA_ARGS__::value,std::nullptr_t> = nullptr
struct nullopt_t{
	struct init{};
	constexpr explicit nullopt_t(init){}
};
constexpr nullopt_t nullopt{nullopt_t::init()};

template<class T>
struct optional{
	constexpr explicit optional()
		:data_{},init_(false){}
	constexpr explicit optional(nullopt_t)
		:data_{},init_(false){}
	template<EXT_OPTIONAL_REQUIRES(std::is_copy_constructible<T>)>
	optional(const optional& other)
		:data_(other.data_),init_(other.init_){}
	template<EXT_OPTIONAL_REQUIRES(std::is_move_constructible<T>)>
	optional(optional&& other)
		:data_(std::move(other.data_)),init_(std::move(other.init_)){}
	template<
		class U,
			  EXT_OPTIONAL_REQUIRES(
					  std::is_constructible<T,const U&>::value &&
					  !std::is_constructible<T,optional<U>&>::value &&
					  !std::is_constructible<T,const optional<U>&>::value &&
					  !std::is_constructible<T,optional<U>&&>::value &&
					  !std::is_constructible<T,const optional<U>&&>::value &&
					  !std::is_constructible<optional<U>&,T>::value &&
					  !std::is_constructible<const optional<U>&,T>::value &&
					  !std::is_constructible<optional<U>&&,T>::value &&
					  !std::is_constructible<const optional<U>&&,T>::value &&
					  !std::is_convertible<const U&,T>
			)
	>
	explicit optional(const optional<U>& other)
		:data_(other.data_),init_(other.init_){}
	template<
		class U,
			  EXT_OPTIONAL_REQUIRES(
					  std::is_constructible<T,U&&>::value &&
					  !std::is_constructible<T,optional<U>&>::value &&
					  !std::is_constructible<T,const optional<U>&>::value &&
					  !std::is_constructible<T,optional<U>&&>::value &&
					  !std::is_constructible<T,const optional<U>&&>::value &&
					  !std::is_constructible<optional<U>&,T>::value &&
					  !std::is_constructible<const optional<U>&,T>::value &&
					  !std::is_constructible<optional<U>&&,T>::value &&
					  !std::is_constructible<const optional<U>&&,T>::value &&
					  !std::is_convertible<U&&,T>
			)
	>		
	explicit optional(optional<U>&& other)
		:data_(std::move(other.data_)),init_(std::move(other.init_)){}
	template<class... Args,EXT_OPTIONAL_REQUIRES(std::is_constructible<T,Args...>)>
	constexpr explicit optional(in_place_t,Args&&... args)
		:data_(std::forward<Args>(args)...),init_(true){}
	template<class U,class... Args,EXT_OPTIONAL_REQUIRES(std::is_constructible<T,std::initializer_list<U>&,Args&&...>)>
	constexpr explicit optional(in_place_t,std::initializer_list<U> ilist,Args&&... args)
		:data_(std::move(ilist),std::forward<Args>(args)...),init_(true){}
	template<
		class U=T,
		EXT_OPTIONAL_REQUIRES(
				std::is_constructible<T, U&&>::value &&
				!std::is_same<std::decay_t<U>,optional<T>>::value &&
				!std::is_same<std::decay_t<U>,in_place_t>
		)
	>
	constexpr optional(U&& value)
		:data_(std::forward<U>(value)),init_(true){}

	void reset()noexcept
	{
		init_=false;
		value().T::~T();
	}

	optional& operator=(nullopt_t)
	{
		reset();
		return *this;
	}
	template<EXT_OPTIONAL_REQUIRES(std::is_copy_constructible<T>::value && std::is_copy_assignable<T>)>
	optional& operator=(const optional& other)
	{
		if(*this && other){
			init_=other.init_;
			data_=other.data_;
		}
		return *this;
	}
	template<EXT_OPTIONAL_REQUIRES(std::is_move_constructible<T>::value && std::is_move_assignable<T>)>
	optional& operator=(optional&& other)
	{
		if(*this && other){
			init_=std::move(other.init_);
			data_=std::move(other.data_);
		}
		return *this;
	}
	template<class U=T,EXT_OPTIONAL_REQUIRES(!std::is_same<std::decay_t<U>,optional<T>>)>
	optional& operator=(U&& value)
	{
		data_=std::forward<U>(value);
		init_=true;
		return *this;
	}
	template<
		class U,
		EXT_OPTIONAL_REQUIRES(
				!std::is_constructible<T,optional<U>&>::value &&
				!std::is_constructible<T,const optional<U>&>::value &&
				!std::is_constructible<T,optional<U>&&>::value &&
				!std::is_constructible<T,const optional<U>&&>::value &&
				!std::is_convertible<optional<U>&,T>::value &&
				!std::is_convertible<const optional<U>&,T>::value &&
				!std::is_convertible<optional<U>&&,T>::value &&
				!std::is_convertible<const optional<U>&&,T>::value &&
				!std::is_assignable<T&,optional<U>&>::value&&
				!std::is_assignable<T&,const optional<U>&>::value &&
				!std::is_assignable<T&,optional<U>&&>::value &&
				!std::is_assignable<T&,const optional<U>&&>::value &&
				std::is_constructible<T,const U&>::value &&
				std::is_assignable<T&,const U&> 
		)
	>
	optional& operator=(const optional<U>& other)
	{
		if(*this && other){
			if(!other){
				value().T::~T();
				init_=other.init_;
			}else{
				data_=other.data_;
				init_=other.init_;
			}
		}
		return *this;
	}
	template<
		class U,
		EXT_OPTIONAL_REQUIRES(
				!std::is_constructible<T,optional<U>&>::value &&
				!std::is_constructible<T,const optional<U>&>::value &&
				!std::is_constructible<T,optional<U>&&>::value &&
				!std::is_constructible<T,const optional<U>&&>::value &&
				!std::is_convertible<optional<U>&,T>::value &&
				!std::is_convertible<const optional<U>&,T>::value &&
				!std::is_convertible<optional<U>&&,T>::value &&
				!std::is_convertible<const optional<U>&&,T>::value &&
				!std::is_assignable<T&,optional<U>&>:: value&&
				!std::is_assignable<T&,const optional<U>&>::value &&
				!std::is_assignable<T&,optional<U>&&>::value &&
				!std::is_assignable<T&,const optional<U>&&>::value &&
				std::is_constructible<T,U>::value &&
				std::is_assignable<T&,U> 
		)
	>
	optional operator=(optional<U>&& other)
	{
		if(*this && other){
			if(!other){
				value().T::~T();
				init_=std::move(other.init_);
			}else{
				data_=std::move(other.data_);
				init_=std::move(other.init_);
			}
		}
		return *this;
	}
		
	explicit constexpr operator bool()const{return init_;}
	constexpr bool has_value()const{return bool(*this);}
	constexpr const T* operator->()const{return &data_;}
	constexpr T* operator->(){return &data_;}
	constexpr const T& operator*()const&{return data_;}
	constexpr T& operator*()&{return data_;}
	constexpr const T&& operator*()const&&{return std::move(data_);}
	constexpr T&& operator*()&&{return std::move(data_);}

	constexpr T& value()&{return (**this);}
	constexpr const T& value()const&{return (**this);}
	constexpr T&& value()&&{return std::move((**this));}
	constexpr const T&& value()const&&{return std::move((**this));}

	template<class U,EXT_OPTIONAL_REQUIRES(std::is_convertible<U,T>)>
	constexpr T value_or(U&& default_value)const&{return bool(*this)?**this:static_cast<T>(std::forward<U>(default_value));}
	template<class U,EXT_OPTIONAL_REQUIRES(std::is_convertible<U,T>)>
	constexpr T value_or(U&& default_value)&&{return bool(*this)?std::move(**this):static_cast<T>(std::forward<U>(default_value));}

	template<class... Args>
	void emplace(Args&&... args)noexcept(noexcept(T(std::forward<Args>(args)...)))
	{
		reset();
		::new (static_cast<void*>(dataptr())) T(std::forward<Args>(args)...);
		init_=true;
	}
	template<class U,class... Args>
	void emplace(std::initializer_list<U> ilist,Args&&... args)noexcept(noexcept(T(ilist,std::forward<Args>(args)...)))
	{
		::new (static_cast<void*>(dataptr())) T(std::move(ilist),std::forward<Args>(args)...);
		init_=true;
	}

	void swap(optional& other)noexcept(std::is_nothrow_move_constructible<T>::value && std::__is_nothrow_swappable<T>::value)
	{
		if(!*this && !other)return;
		if(init_ && !other.init_){
			other.data_=std::move(**this);
			value().T::~T();
		}else if(!init_ && other.init_){
			data_=std::move(other.data_);
			other.value().T::~T();
		}else{
			std::swap(**this,*other);
		}
	}

	using value_type=T;
	using pointer=T*;
	using reference=T&;
private:
	std::remove_const_t<T>* dataptr(){return std::addressof(data_);}
	T data_;
	bool init_;
};

template<class T>
constexpr bool operator==(const optional<T>& lhs,const optional<T>& rhs)
{
	return bool(lhs)!=bool(rhs)?false:bool(lhs)==false&&bool(rhs)==false?true:*lhs==*rhs;
}
template<class T>
constexpr bool operator!=(const optional<T>& lhs,const optional<T>& rhs)
{
	return !operator==(lhs,rhs);
}
template<class T>
constexpr bool operator<(const optional<T>& lhs,const optional<T>& rhs)
{
	return bool(rhs)==false?false:bool(lhs)==false?true:*lhs<*rhs;
}
template<class T>
constexpr bool operator>(const optional<T>& lhs,const optional<T>& rhs)
{
	return !operator<(lhs,rhs);
}
template<class T>
constexpr bool operator<=(const optional<T>& lhs,const optional<T>& rhs)
{
	return bool(lhs)==false?true:bool(rhs)==false?false:*lhs<=*rhs;
}
template<class T>
constexpr bool operator>=(const optional<T>& lhs,const optional<T>& rhs)
{
	return operator<=(lhs,rhs);
}
template<class T>
constexpr bool operator==(const optional<T>& opt,nullopt_t)noexcept
{
	return !opt;
}
template<class T>
constexpr bool operator==(nullopt_t,optional<T>& opt)noexcept
{
	return !opt;
}
template<class T>
constexpr bool operator!=(const optional<T>& opt,nullopt_t)noexcept
{
	return bool(opt);
}
template<class T>
constexpr bool operator!=(nullopt_t,const optional<T>& opt)noexcept
{
	return bool(opt);
}
template<class T>
constexpr bool operator<(const optional<T>&,nullopt_t)noexcept
{
	return false;
}
template<class T>
constexpr bool operator<(nullopt_t,const optional<T>& opt)noexcept
{
	return bool(opt);
}
template<class T>
constexpr bool operator>(const optional<T>& opt,nullopt_t)noexcept
{
	return bool(opt);
}
template<class T>
constexpr bool operator>(nullopt_t,const optional<T>&)noexcept
{
	return false;
}
template<class T>
constexpr bool operator<=(const optional<T>& opt,nullopt_t)noexcept
{
	return !opt;
}
template<class T>
constexpr bool operator<=(nullopt_t,const optional<T>&)noexcept
{
	return true;
}
template<class T>
constexpr bool operator>=(const optional<T>&,nullopt_t)noexcept
{
	return true;
}
template<class T>
constexpr bool operator>=(nullopt_t,const optional<T>& opt)noexcept
{
	return !opt;
}
template<class T>
constexpr bool operator==(const optional<T>& opt,const T& value)
{
	return bool(opt)?*opt==value:false;
}
template<class T>
constexpr bool operator==(const T& value,const optional<T>& opt)
{
	return bool(opt)?value==*opt:false;
}
template<class T>
constexpr bool operator!=(const optional<T>& opt,const T& value)
{
	return bool(opt)?*opt!=value:true;
}
template<class T>
constexpr bool operator!=(const T& value,const optional<T>& opt)
{
	return bool(opt)?value!=*opt:true;
}
template<class T>
constexpr bool operator<(const optional<T>& opt,const T& value)
{
	return bool(opt)?*opt<value:true;
}
template<class T>
constexpr bool operator<(const T& value,const optional<T>& opt)
{
	return bool(opt)?value<*opt:false;
}
template<class T>
constexpr bool operator>(const optional<T>& opt,const T& value)
{
	return bool(opt)?*opt>value:false;
}
template<class T>
constexpr bool operator>(const T& value,const optional<T>& opt)
{
	return bool(opt)?value>*opt:true;
}
template<class T>
constexpr bool operator<=(const optional<T>& opt,const T& value)
{
	return bool(opt)?*opt<=value:true;	
}
template<class T>
constexpr bool operator<=(const T& value,const optional<T>& opt)
{
	return bool(opt)?value<=*opt:false;
}
template<class T>
constexpr bool operator>=(const optional<T>& opt,const T& value)
{
	return bool(opt)?*opt>=value:false;
}
template<class T>
constexpr bool operator>=(const T& value,const optional<T>& opt)
{
	return bool(opt)?value>=*opt:true;
}

template<class T>
constexpr optional<std::decay_t<T>> make_optional(T&& value)
{
	return optional<std::decay_t<T>>(std::forward<T>(value));
}
template<class T,class... Args>
constexpr optional<T> make_optional(Args&&... args)
{
	return optional<T>(in_place,std::forward<Args>(args)...);
}
template<class T,class U,class... Args>
constexpr optional<T> make_optional(std::initializer_list<U> ilist,Args&&... args)
{
	return optional<T>(in_place,std::move(ilist),std::forward<Args>(args)...);
}
} // namespace detail

using detail::optional;
using detail::nullopt_t;
using detail::nullopt;

} // namespace srook
#endif
