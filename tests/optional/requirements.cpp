// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#define  BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include <srook/optional.hpp>

BOOST_AUTO_TEST_SUITE(sroptional_test)

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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(Lnot<srook::is_copy_assignable<O> >{});
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(Lnot<srook::is_copy_assignable<O_safe> >{});
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O>{});
        {
            O o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O>{});
        {
            O o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
            SROOK_ATTRIBUTE_UNUSED auto p = o;
        }
        SROOK_ST_ASSERT(srook::is_copy_assignable<O_safe>{});
        {
            O_safe o, p;
            p = o;
        }
        SROOK_ST_ASSERT(srook::is_move_constructible<O_safe>{});
        {
            O_safe o;
            SROOK_ATTRIBUTE_UNUSED auto p = srook::move(o);
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
        BOOST_TEST(bool(o1));
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
}

typedef boost::mpl::list<
    int&, int&&, 
    srook::in_place_t, const srook::in_place_t, volatile srook::in_place_t, const volatile srook::in_place_t,    
    srook::nullopt_t, const srook::nullopt_t, volatile srook::nullopt_t, const volatile srook::nullopt_t
> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(optional_test, T, test_types)
{
    // Should not complain about 'invalid' specializations as long as they're not instantiated.
    SROOK_ATTRIBUTE_UNUSED typedef srook::optional<T> type;
}

BOOST_AUTO_TEST_SUITE_END()
