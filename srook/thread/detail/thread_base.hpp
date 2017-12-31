// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_THREAD_DETAIL_THREAD_BASE_HPP
#define INCLUDED_SROOK_THREAD_DETAIL_THREAD_BASE_HPP
#include <srook/config/cpp_predefined.hpp>
#include <srook/config/feature.hpp>
#include <srook/config/require.hpp>
#include <srook/functional/invoke.hpp>
#include <srook/memory/unique_ptr.hpp>
#include <srook/mutex/includes/lib.hpp>
#include <srook/thread/detail/support.hpp>
#include <srook/type_traits/is_invocable.hpp>
#include <srook/utility/declval.hpp>
#include <srook/utility/forward.hpp>
#include <srook/utility/index_sequence.hpp>
#include <srook/utility/move.hpp>
#include <srook/utility/noncopyable.hpp>
#include <ostream>

#if SROOK_HAS_INCLUDE(<hash>) && SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    include <hash>
#    define HAS_STD_HASH
#elif SROOK_HAS_INCLUDE(<boost/functional/hash.hpp>) && SROOK_CPLUSPLUS < SROOK_CPLUSPLUS11_CONSTANT
#    include <boost/functional/hash.hpp>
#    include <srook/preprocessor/detail/iterate_def.hpp>
#    include <srook/preprocessor/detail/loop_def.hpp>
#    define HAS_BOOST_HASH
#endif
#if SROOK_CONFIG_THREAD_ENABLE_PHYSICAL_CONCURRENCY
#    include <fstream>
#    include <set>
#    include <vector>
#    if defined(__linux__) && SROOK_HAS_INCLUDE(<boost/algorithm/string.hpp>)
#        include <boost/algorithm/string.hpp>
#    elif defined(__linux__)
#        error the member function that physical concurrency need boost.string.split
#    endif
#endif

namespace srook {
namespace threading {
SROOK_INLINE_NAMESPACE(v1)
namespace detail {

extern "C" {
static void* execute_native_thread_routine(void*);
}

class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT thread : private noncopyable<thread> {
public:
    struct States {
        virtual ~States() SROOK_DEFAULT
            virtual void run()
            = 0;
    };
    typedef mutexes::includes::unique_ptr<States> State_ptr;
    typedef thread_type native_handle_type;

    class SROOK_ATTRIBUTE_TYPE_VIS_DEFAULT id {
        native_handle_type thread_;

    public:
        id() SROOK_NOEXCEPT_TRUE : thread_() {}

        explicit id(native_handle_type id_) : thread_(id_) {}

    private:
        friend class thread;
#if HAS_STD_HASH
        friend class std::hash<id>;
#    undef HAS_STD_HASH
#elif defined(HAS_BOOST_HASH)
        friend class boost::hash<id>;
#    undef HAS_BOOST_HASH
#endif

        friend bool operator==(id lhs, id rhs) SROOK_NOEXCEPT_TRUE
        {
            return lhs.thread_ == rhs.thread_;
        }
        friend bool operator!=(id lhs, id rhs) SROOK_NOEXCEPT_TRUE
        {
            return !(lhs == rhs);
        }
        friend bool operator<(id lhs, id rhs) SROOK_NOEXCEPT_TRUE
        {
            return lhs.thread_ < rhs.thread_;
        }
        friend bool operator<=(id lhs, id rhs) SROOK_NOEXCEPT_TRUE
        {
            return !(rhs < lhs);
        }
        friend bool operator>(id lhs, id rhs) SROOK_NOEXCEPT_TRUE
        {
            return rhs < lhs;
        }
        friend bool operator>=(id lhs, id rhs) SROOK_NOEXCEPT_TRUE
        {
            return !(lhs < rhs);
        }
        template <class charT, class Traits>
        friend std::basic_ostream<charT, Traits>&
        operator<<(std::basic_ostream<charT, Traits>& os, const id& id_)
        {
            return id() == id_ ? os << "thread::id of a non-executig thread" : os << id_.thread_;
        }
    };

private:
    id id_;

public:
    thread() SROOK_NOEXCEPT_TRUE SROOK_DEFAULT
        thread(thread&) SROOK_EQ_DELETE
        thread(const thread&) SROOK_EQ_DELETE
        thread(const thread&&) SROOK_EQ_DELETE
        thread(thread&& rhs) SROOK_NOEXCEPT_TRUE
    {
        swap(rhs);
    }

#if SROOK_HAS_THREAD_API_PTHREAD
#    define DEPEND_INIT = reinterpret_cast<void (*)()>(&pthread_create)
#else
#    define DEPEND_INIT = SROOK_NULLPTR
#endif
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
#    define THREAD_CTOR_PARAMS , class... Args, REQUIRES(is_invocable<Callable, Args...>::value)
#    define THREAD_CTOR_PARAMS_DECL Callable &&f, Args &&... args
#    define THREAD_CTOR_GEN_INVOKER \
        make_invoker(srook::forward<Callable>(f), srook::forward<Args>(args)...)
#else
#    define THREAD_CTOR_PARAMS
#    define THREAD_CTOR_PARAMS_DECL const Callable& f
#    define THREAD_CTOR_GEN_INVOKER f
#endif

    template <class Callable THREAD_CTOR_PARAMS>
    explicit thread(THREAD_CTOR_PARAMS_DECL)
    {
        void (*depend)() DEPEND_INIT;
        start_thread(make_state(THREAD_CTOR_GEN_INVOKER), depend);
    }

#undef DEPEND_INIT
#undef THREAD_CTOR_PARAMS
#undef THREAD_CTOR_PARAMS_DECL
#undef THREAD_CTOR_GEN_INVOKER

    ~thread()
    {
        if (joinable()) std::terminate();
    }

    thread& operator=(const thread&) SROOK_EQ_DELETE
        thread&
        operator=(thread&& rhs) SROOK_NOEXCEPT_TRUE
    {
        if (joinable()) std::terminate();
        swap(rhs);
        return *this;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY void swap(thread& rhs) SROOK_NOEXCEPT_TRUE
    {
        std::swap(id_, rhs.id_);
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY bool joinable() const SROOK_NOEXCEPT_TRUE
    {
        return !(id_ == id());
    }

    void join()
    {
        int e = EINVAL;
        if (id_ != id()) e = thread_join(&id_.thread_);
        if (e) mutexes::includes::throw_system_err(e);
        id_ = id();
    }

    void detach()
    {
        int e = EINVAL;
        if (id_ != id()) e = thread_detach(&id_.thread_);
        if (e) mutexes::includes::throw_system_err(e);
        id_ = id();
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY thread::id get_id() const SROOK_NOEXCEPT_TRUE
    {
        return id_;
    }

    SROOK_ATTRIBUTE_INLINE_VISIBILITY native_handle_type native_handle()
    {
        return id_.thread_;
    }

    static unsigned int hardware_concurrency() SROOK_NOEXCEPT_TRUE
    {
        const int n = get_nprocs();
        return n < 0 ? 0 : n;
    }
#if SROOK_CONFIG_THREAD_ENABLE_PHYSICAL_CONCURRENCY
    static unsigned int physical_concurrency() SROOK_NOEXCEPT_TRUE
    {
#    ifdef __linux__
        try {
            using namespace std;

            ifstream cpuinfo("/proc/cpuinfo");
            const string physical_id("physical id"), core_id("core id");
            typedef pair<unsigned, unsigned> core_entry;

            set<core_entry> cores;
            core_entry current_core_entry;
            string line;

            while (getline(proc_cpuinfo, line)) {
                if (line.empty()) continue;

                vector<string> key_val(2);
                boost::split(key_val, line, is_any_of(":"));

                if (key_val.size() != 2) return hardware_concurrency();

                string key = key_val[0];
                string value = key_val[1];
                boost::trim(key);
                boost::trim(value);

                if (key == physical_id) {
                    current_core_entry.first = boost::lexical_cast<unsigned>(value);
                    continue;
                }
                if (key == core_id) {
                    current_core_entry.second = boost::lexical_cast<unsigned>(value);
                    cores.insert(current_core_entry);
                    continue;
                }
            }
            return cores.size() != 0 ? cores.size() : hardware_concurrency();
        } catch (...) {
            return hardware_concurrency();
        }
#    elif defined(__APPLE__)
        int c;
        std::size_t size = sizeof(c);
        return sysctlbyname("hw.physicalcpu", &c, &size, SROOK_NULLPTR, 0) ? 0 : c;
#    else
        return hardware_concurrency();
#    endif
    }

#endif
private:
    friend inline void swap(thread& lhs, thread& rhs) SROOK_NOEXCEPT_TRUE
    {
        lhs.swap(rhs);
    }

    template <class Callable>
    struct States_impl SROOK_FINAL : public States {
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
		Callable f_;
        States_impl(Callable&& f) : f_(srook::forward<Callable>(f))
        {
        }
#else
        const Callable& f_;
        States_impl(const Callable& f) : f_(f)
        {
        }
#endif
        void run() SROOK_OVERRIDE
        {
            f_();
        }
    };

    void start_thread(State_ptr state, void (*)())
    {
        const int err = thread_create(&id_.thread_, &execute_native_thread_routine, state.get());
        if (err) mutexes::includes::throw_system_err(err);
        state.release();
    }

    template <class Callable>
    static State_ptr make_state(
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
        Callable&&
#else
        const Callable&
#endif
            f)
    {
        typedef States_impl<Callable> Stype;
        return State_ptr(new Stype(
#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
            srook::forward<Callable>(f)
#else
            f
#endif
                ));
    }

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT
    template <class Tuple>
    struct Invoker {
        Tuple t;

        template <std::size_t Idx>
        static typename mutexes::includes::tuple_element<Idx, Tuple>::type&&
        tuple_elem_declval();

        template <std::size_t... I>
        auto invoke(srook::index_sequence<I...>)
            SROOK_NOEXCEPT(srook::invoke(tuple_elem_declval<I>()...))
                -> decltype(srook::invoke(tuple_elem_declval<I>()...))
        {
            return srook::invoke(mutexes::includes::get<I>(srook::move(t))...);
        }

        using Indices = make_index_sequence<mutexes::includes::tuple_size<Tuple>::value>;

        auto operator()()
            SROOK_NOEXCEPT(declval<Invoker&>().invoke(Indices()))
                -> decltype(declval<Invoker&>().invoke(Indices()))
        {
            return invoke(Indices());
        }
    };

    template <class... Ts>
    using invoker_type = Invoker<decltype(mutexes::includes::make_tuple(declval<Ts>()...))>;
    template <class Callable, class... Args>
    static SROOK_CONSTEXPR invoker_type<Callable, Args...> make_invoker(Callable&& callable, Args&&... args)
    {
        return {{ mutexes::includes::make_tuple(srook::forward<Callable>(callable), srook::forward<Args>(args)...) }};
    }
#endif
};

extern "C" {
static void* execute_native_thread_routine(void* ptr)
{
    thread::State_ptr t(static_cast<thread::States*>(ptr));
    t->run();
    return SROOK_NULLPTR;
}
}

#ifdef HAS_STD_HASH
template <>
struct std::hash<thread::id> {
	SROOK_ATTRIBUTE_INLINE_VISIBILITY
	std::size_t operator()(thread::id v) const SROOK_NOEXCEPT_TRUE
	{
		return std::hash<threading::thread_id_type>(v.id_);
	}
};
#undef HAS_STD_HASH
#endif

} // namespace detail
SROOK_INLINE_NAMESPACE_END
} // namespace threading
} // namespace srook

#endif
