#define  BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <srook/optional.hpp>

SROOK_ST_ASSERT(srook::is_default_constructible<srook::bad_optional_access>{});

struct trivially_destructible
    : public srook::enable_copy_move<false, false, false, false, trivially_destructible> {
    trivially_destructible() SROOK_DEFAULT
        ~trivially_destructible() SROOK_DEFAULT
};
SROOK_ST_ASSERT(std::is_trivially_destructible<trivially_destructible>{});

BOOST_AUTO_TEST_CASE(optional)
{
    using srook::optional;
    using namespace srook::type_traits::detail;
    SROOK_ST_ASSERT(std::is_trivially_destructible<optional<trivially_destructible> >{});

    {
        struct no_default_ctor { no_default_ctor() SROOK_EQ_DELETE };
        typedef no_default_ctor T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O>{});
        {
            O o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O>{});
        {
            O o, p;
            p = srook::move(o);
        }
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O_safe>{});
        {
            O_safe o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O_safe>{});
        {
            O_safe o, p;
            p = srook::move(o);
        }
    }

    {
        typedef srook::enable_copy_move<false, false, true, true> no_copy_ctor;
        typedef no_copy_ctor T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT(Lnot<srook::is_copy_constructible<O> >{});
        SROOK_ST_ASSERT(Lnot<srook::is_copy_assignable<O> >{});
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O>{});
        {
            O o, p;
            p = srook::move(o);
        }
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT(Lnot<srook::is_copy_constructible<O_safe> >{});
        SROOK_ST_ASSERT(Lnot<srook::is_copy_assignable<O_safe> >{});
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O_safe>{});
        {
            O_safe o, p;
            p = srook::move(o);
        }
    }

    {
        typedef srook::enable_copy_move<true, false, true, true> no_copy_assignment;
        typedef no_copy_assignment T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O>{});
        {
            O o;
            auto p = o;
        }
        SROOK_ST_ASSERT(Lnot<srook::is_copy_assignable<O> >{});
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O>{});
        {
            O o, p;
            p = srook::move(o);
        }
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O_safe>{});
        {
            O_safe o;
            auto p = o;
        }
        SROOK_ST_ASSERT(Lnot<srook::is_copy_assignable<O_safe> >{});
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O_safe>{});
        {
            O_safe o, p;
            p = srook::move(o);
        }
    }

    {
        typedef srook::enable_copy_move<false, false, true, true> no_copy;
        typedef no_copy T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT((Land<Lnot<srook::is_copy_constructible<O>>, Lnot<srook::is_copy_assignable<O>>>::value));
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O>{});
        {
            O o, p;
            p = srook::move(o);
        }
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT((Land<Lnot<srook::is_copy_constructible<O_safe>>, Lnot<srook::is_copy_assignable<O_safe>>>::value));
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O_safe>{});
        {
            O_safe o, p;
            p = srook::move(o);
        }
    }

    {
        typedef srook::enable_copy_move<true, true, false, true> no_move_ctor;
        typedef no_move_ctor T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O>{});
        {
            O o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O>{});
        {
            O o, p;
            p = srook::move(o);
        }
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O_safe>{});
        {
            O_safe o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O_safe>{});
        {
            O_safe o, p;
            p = srook::move(o);
        }
    }

    {
        typedef srook::enable_copy_move<true, true, true, false> no_move_assignment;
        typedef no_move_assignment T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O>{});
        {
            O o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O>{});
        {
            O o, p;
            p = srook::move(o);
        }
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O_safe>{});
        {
            O_safe o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O_safe>{});
        {
            O_safe o, p;
            p = srook::move(o);
        }
    }

    {
        typedef srook::enable_copy_move<true, true, false, false> no_move;
        typedef no_move T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O>{});
        {
            O o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O>{});
        {
            O o, p;
            p = srook::move(o);
        }
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT(srook::is_copy_constructible<O_safe>{});
        {
            O_safe o;
            auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            auto p = srook::move(o);
        }
        SROOK_ST_ASSERT(srook::is_move_assignable<O_safe>{});
        {
            O_safe o, p;
            p = srook::move(o);
        }
    }

    {
        struct only_destructible { only_destructible(only_destructible&&) SROOK_EQ_DELETE };
        typedef only_destructible T;
        typedef optional<T> O;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O>{});
        {
            O o;
        }
        SROOK_ST_ASSERT((Land<Lnot<srook::is_copy_constructible<O>>, Lnot<srook::is_copy_assignable<O>>, Lnot<srook::is_move_constructible<O>>, Lnot<srook::is_move_assignable<O>>>::value));
        typedef optional<T, srook::optionally::safe_optional_payload> O_safe;
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME O_safe::value_type, T>{}));
        SROOK_ST_ASSERT(srook::is_default_constructible<O_safe>{});
        {
            O_safe o;
        }
        SROOK_ST_ASSERT((Land<Lnot<srook::is_copy_constructible<O_safe>>, Lnot<srook::is_copy_assignable<O_safe>>, Lnot<srook::is_move_constructible<O_safe>>, Lnot<srook::is_move_assignable<O_safe>>>::value));
    }

    {
        optional<const int> o1 { 42 };
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME SROOK_DECLTYPE(o1)::value_type, const int>{}));
        assert(o1);
        BOOST_CHECK_EQUAL(*o1, 42);

        struct X {
            X(const int x) : constant_data(srook::move(x)) {}
            const int constant_data = 42;
        };
        optional<X, srook::optionally::safe_optional_payload> o2 { 42 };
        o2.emplace(32);
        SROOK_ST_ASSERT((srook::is_same<SROOK_DEDUCED_TYPENAME SROOK_DECLTYPE(o2)::value_type, X>{}));
        BOOST_TEST(bool(o2));
        BOOST_CHECK_EQUAL((*o2).constant_data, 32);
    }

    typedef optional<int&> A;
    typedef optional<int&&> B;
    typedef optional<srook::in_place_t> C1;
    typedef optional<const srook::in_place_t> C2;
    typedef optional<volatile srook::in_place_t> C3;
    typedef optional<const volatile srook::in_place_t> C4;
    typedef optional<srook::nullopt_t> D1;
    typedef optional<const srook::nullopt_t> D2;
    typedef optional<volatile srook::nullopt_t> D3;
    typedef optional<const volatile srook::nullopt_t> D4;
    typedef optional<int&, srook::optionally::safe_optional_payload> E;
    typedef optional<int&&, srook::optionally::safe_optional_payload> F;
    typedef optional<srook::in_place_t, srook::optionally::safe_optional_payload> G1;
    typedef optional<const srook::in_place_t, srook::optionally::safe_optional_payload> G2;
    typedef optional<volatile srook::in_place_t, srook::optionally::safe_optional_payload> G3;
    typedef optional<const volatile srook::in_place_t, srook::optionally::safe_optional_payload> G4;
    typedef optional<srook::nullopt_t, srook::optionally::safe_optional_payload> H1;
    typedef optional<const srook::nullopt_t, srook::optionally::safe_optional_payload> H2;
    typedef optional<volatile srook::nullopt_t, srook::optionally::safe_optional_payload> H3;
    typedef optional<const volatile srook::nullopt_t, srook::optionally::safe_optional_payload> H4;

    // Should not complain about 'invalid' specializations as long as they're not instantiated.
    typedef std::tuple<A, B, C1, C2, C3, C4, D1, D2, D3, D4, E, F, G1, G2, G3, G4, H1, H2, H3, H4> X; 
}
