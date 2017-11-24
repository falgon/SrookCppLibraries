#include <srook/scope/unique_resource.hpp>
#include <srook/semaphore.hpp>
#include <srook/thread.hpp>

srook::semaphore sbs, s(4);
srook::timed_semaphore tsbs, ts(4);
srook::binary_semaphore bs;
srook::binary_timed_semaphore bts;

using namespace srook::mutexes::includes;

const auto lm = [](auto&& x) { srook::forward<SROOK_DECLTYPE(x)>(x).up_all(); };
template <class T>
using scoped_upall = srook::unique_resource<T, SROOK_DECLTYPE(lm)>;

void f(srook::unique_lock<srook::binary_semaphore>) {}       // unlocked by scoped guard
void g(srook::unique_lock<srook::binary_timed_semaphore>) {} // unlocked by scoped guard

int main()
{
    {
        scoped_upall<srook::semaphore&> rs(s, lm);
        s.down_all();
        SROOK_ST_ASSERT(noexcept(s.is_binary()));
        assert(!s.is_binary() && !s.try_lock());
    }
    {
        scoped_upall<srook::timed_semaphore&> rs(ts, lm);
        ts.down_all();
        assert(!ts.try_lock_for(chrono::nanoseconds(1)));
        assert(!ts.try_lock_until(chrono::system_clock::now() + chrono::nanoseconds(1)));
        SROOK_ST_ASSERT(noexcept(ts.is_binary()));
        assert(!ts.is_binary());
    }
    {
        scoped_upall<srook::binary_semaphore&> rs(bs, lm);
        SROOK_ST_ASSERT(noexcept(bs.is_binary()));
        assert(bs.is_binary());
        bs.lock();
        assert(!bs.try_lock());
        srook::unique_lock<srook::binary_semaphore> lk(bs, srook::adopt_lock);
        srook::thread th(f, srook::move(lk));
        th.join();
    }
    {
        scoped_upall<srook::binary_timed_semaphore&> rs(bts, lm);
        SROOK_ST_ASSERT(noexcept(bs.is_binary()));
        assert(bts.is_binary());
        bts.lock();
        assert(!bts.try_lock_for(chrono::nanoseconds(1)));
        assert(!bts.try_lock_until(chrono::system_clock::now() + chrono::nanoseconds(1)));
        srook::unique_lock<srook::binary_timed_semaphore> lk(bts, chrono::nanoseconds(1));
        assert(!lk.owns_lock());
        srook::thread th(g, srook::move(lk));
        th.join();
    }
}
