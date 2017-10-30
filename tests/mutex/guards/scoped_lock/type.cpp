#include <srook/mutex.hpp>
#include <srook/type_traits/is_same.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
typedef std::mutex test_mutex;
#elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
#include <cassert>
typedef boost::mutex test_mutex;
#endif

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
static_assert(srook::is_same<typename srook::scoped_lock<srook::mutex>::mutex_type, srook::mutex>());
static_assert(srook::is_same<typename srook::scoped_lock<std::mutex>::mutex_type, std::mutex>());
static_assert(srook::is_same<typename srook::scoped_lock<std::mutex, srook::mutex>::mutexes_type, srook::pack<std::mutex, srook::mutex>>());
#elif !(SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT) && SROOK_HAS_INCLUDE(<boost/thread.hpp>)
bool b1 = srook::is_same<srook::scoped_lock<srook::mutex>::mutex_type, srook::mutex>::value,
	 b2 = srook::is_same<srook::scoped_lock<boost::mutex>::mutex_type, boost::mutex>::value;
#endif

int main() 
{
	assert(b1 && b2);
}
