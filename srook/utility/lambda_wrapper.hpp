#ifndef INCLUDED_SROOK_UTILITY_LAMBDA_WRAPPER_HPP
#define INCLUDED_SROOK_UTILITY_LAMBDA_WRAPPER_HPP
#include<utility>
#include<srook/type_traits/is_callable.hpp>
#include<srook/config/require.hpp>

namespace srook{

template<class Lambda>
struct lambda_wrapper{
    lambda_wrapper(const Lambda& lambda):lambda_(lambda){}
	
	template<class Lambdas,REQUIRES(is_callable_v<std::decay_t<Lambdas>>)>
	lambda_wrapper& operator=(const Lambdas& lambda)
	{
		reset(lambda);
		return *this;
	}

	template<class Lambdas,REQUIRES(is_callable_v<std::decay_t<Lambdas>>)>
	void reset(const Lambdas& lambda)
	{
		lambda_.~Lambda();
		new (&lambda_) std::decay_t<Lambdas>(lambda);
	}

	template<class... Args>
	auto operator()(Args&&... value)const
	{
		return lambda_(std::forward<Args>(value)...);
	}
private:
    Lambda lambda_;
};

template<class Lambda>
lambda_wrapper<std::decay_t<Lambda>> make_lambda_wrapper(Lambda&& lambda)
{
	return lambda_wrapper<std::decay_t<Lambda>>(std::forward<Lambda>(lambda));
}

} // namespace srook
#endif
