#ifndef INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_ROTATE_COPY_HPP
#define INCLUDED_SROOK_RANGE_PIPE_ALGORITHM_ROTATE_COPY_HPP
#include<srook/config/require.hpp>
#include<srook/type_traits/is_callable.hpp>
#include<srook/type_traits/has_iterator.hpp>
#include<srook/iterator/range_iterator.hpp>
#include<algorithm>
#include<type_traits>

namespace srook{
namespace pipealgo{
namespace detail{
inline namespace v1{

template<class InputIterator,class OutputIterator>
struct rotate_copy_t{
	template<
		REQUIRES(!has_iterator_v<InputIterator> and !has_iterator_v<OutputIterator>)
	>
	explicit constexpr rotate_copy_t(InputIterator input,OutputIterator output)
		:input_(std::move(input)),output_(std::move(output)){}

	template<
		class Range,
		REQUIRES(
				has_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>> or
				is_range_iterator_v<std::remove_reference_t<std::remove_cv_t<Range>>>
		)
	>
	OutputIterator operator()(Range&& r)
	{
		return std::rotate_copy(r.begin(),std::move(input_),r.end(),std::move(output_));
	}
private:
	InputIterator input_;
	OutputIterator output_;
};

template<
	class InputIterator,
	class OutputIterator,
	REQUIRES(
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<InputIterator>>> and
			!has_iterator_v<std::remove_reference_t<std::remove_cv_t<OutputIterator>>>
	)
>
constexpr rotate_copy_t<
	std::remove_reference_t<std::remove_cv_t<InputIterator>>,
	std::remove_reference_t<std::remove_cv_t<OutputIterator>>
>
rotate_copy(InputIterator&& input,OutputIterator&& output)
{
	return rotate_copy_t<
		std::remove_reference_t<std::remove_cv_t<InputIterator>>,
		std::remove_reference_t<std::remove_cv_t<OutputIterator>>
	>(std::forward<InputIterator>(input),std::forward<OutputIterator>(output));
}

} // inline namespace v1
} // namespace detail

using detail::rotate_copy;

} // namespace pipealgo
} // namespace srook

#endif
