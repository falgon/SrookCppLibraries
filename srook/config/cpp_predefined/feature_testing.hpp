// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONFIG_CPP_PREDEFINED_FEATURE_TESTING_HPP
#define INCLUDED_SROOK_CONFIG_CPP_PREDEFINED_FEATURE_TESTING_HPP

#include <srook/config/cpp_predefined/__cplusplus_constant.hpp>
#include <srook/config/cpp_predefined/macro_names.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS14_CONSTANT
#    define SROOK_HAS_INCLUDE(header) __has_include(header)
#    define SROOK_HAS_CPP_ATTRIBUTE(ATTR) __has_cpp_attribute(ATTR)
#    define SROOK_CPP_RTTI __cpp_rtti
#    define SROOK_CPP_UNICODE_CHARACTERS __cpp_unicode_characters
#    define SROOK_CPP_EXCEPTIONS __cpp_exceptions
#    define SROOK_CPP_RAW_STRINGS __cpp_raw_strings
#    define SROOK_CPP_UNICODE_LITERALS __cpp_unicode_literals
#    define SROOK_CPP_USER_DEFINED_LITERALS __cpp_user_defined_literals
#    define SROOK_CPP_LAMBDAS __cpp_lambdas
#    define SROOK_CPP_CONSTEXPR __cpp_constexpr
#    define SROOK_CPP_RANGE_BASED_FOR __cpp_range_based_for
#    define SROOK_CPP_STATIC_ASSERT __cpp_static_assert
#    define SROOK_CPP_DECLTYPE __cpp_decltype
#    define SROOK_CPP_ATTRIBUTES __cpp_attributes
#    define SROOK_CPP_HAS_CPP_ATTRIBUTE_NORETURN SROOK_HAS_CPP_ATTRIBUTE(noreturn)
#    define SROOK_CPP_HAS_CPP_ATTRIBUTE_CARRIES_DEPENDENCY SROOK_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define SROOK_CPP_RVALUE_REFERENCES __cpp_rvalue_references
#    define SROOK_CPP_VARIADIC_TEMPLATES __cpp_variadic_templates
#    define SROOK_CPP_INITIALIZER_LISTS __cpp_initializer_lists
#    define SROOK_CPP_DELEGATING_CONSTRUCTORS __cpp_delegating_constructors
#    define SROOK_CPP_NSDMI __cpp_nsdmi
#    define SROOK_CPP_INHERITING_CONSTRUCTORS __cpp_inheriting_constructors
#    define SROOK_CPP_REF_QUALIFIERS __cpp_ref_qualifiers
#    define SROOK_CPP_ALIAS_TEMPLATES __cpp_alias_templates
#    define SROOK_CPP_BINARY_LITERALS __cpp_binary_literals
#    define SROOK_CPP_DIGIT_SEPARATORS __cpp_digit_separators
#    define SROOK_CPP_INIT_CAPUTURES __cpp_init_captures
#    define SROOK_CPP_GENERIC_LAMBDAS __cpp_generic_lambdas
#    define SROOK_CPP_SIZED_DEALLOCATION __cpp_sized_deallocation
#    define SROOK_CPP_DECLTYPE_AUTO __cpp_decltype_auto
#    define SROOK_CPP_RETURN_TYPE_DEDUCTION __cpp_return_type_deduction
#    define SROOK_CPP_VARIABLE_TEMPLATES __cpp_variable_templates
#    define SROOK_CPP_LIB_EXCHANGE_FUNCTION __cpp_lib_exchange_function
#    define SROOK_CPP_LIB_TUPLES_BY_TUPLE __cpp_lib_tuples_by_tuple
#    define SROOK_CPP_LIB_TUPLE_ELEMENT_T __cpp_lib_tuple_element_t
#    define SROOK_CPP_LIB_MAKE_UNIQUE __cpp_lib_make_unique
#    define SROOK_CPP_LIB_TRANSPARENT_OPERATORS __cpp_lib_transparent_operators
#    define SROOK_CPP_LIB_RESULT_OF_SFINAE __cpp_lib_result_of_sfinae
#    define SROOK_CPP_LIB_INTEGRAL_CONSTANT_CALLABLE __cpp_lib_integral_constant_callable
#    define SROOK_CPP_LIB_TRANSFORMATION_TRAIT_ALIASES __cpp_lib_transformation_trait_aliases
#    define SROOK_CPP_LIB_IS_FINAL __cpp_lib_is_final
#    define SROOK_CPP_LIB_IS_NULL_POINTER __cpp_lib_is_null_pointer
#    define SROOK_CPP_LIB_CHRONO_UDLS __cpp_lib_chrono_udls
#    define SROOK_CPP_LIB_STRING_UDLS __cpp_lib_string_udls
#    define SROOK_CPP_LIB_GENERIC_ASSCIATIVE_LOOKUP __cpp_lib_generic_associative_lookup
#    define SROOK_CPP_LIB_NULL_ITERATORS __cpp_lib_null_iterators
#    define SROOK_CPP_LIB_MAKE_REVERSE_ITERATOR __cpp_lib_make_reverse_iterator
#    define SROOK_CPP_LIB_ROBUST_NONMODIFYING_SEQ_OPS __cpp_lib_robust_nonmodifying_seq_ops
#    define SROOK_CPP_LIB_COMPLEX_UDLS __cpp_lib_complex_udls
#    define SROOK_CPP_LIB_QUOTED_STRING_IO __cpp_lib_quoted_string_io
#    define SROOK_CPP_LIB_SHARED_TIMED_MUTEX __cpp_lib_shared_timed_mutex
#    define SROOK_CPP_LIB_INTEGER_SEQUENCE __cpp_lib_integer_sequence

    // C++17
#    if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#        define SROOK_CPP_INLINE_VARIABLES __cpp_inline_variables
#        define SROOK_CPP_HEX_FLOAT __cpp_hex_float
#        define SROOK_CPP_NOEXCEPT_FUNCTION_TYPE __cpp_noexcept_function_type
#        define SROOK_CPP_FOLD_EXPRESSIONS __cpp_fold_expressions
#        define SROOK_CPP_CAPTURE_STAR_THIS __cpp_capture_star_this
#        define SROOK_CPP_NESTED_NAMESPACE_DEFINITIONS __cpp_nested_namespace_definitions
#        define SROOK_HAS_CPP_ATTRIBUTE_FALLTHROUGH SROOK_HAS_CPP_ATTRIBUTE(fallthrough)
#        define SROOK_HAS_CPP_ATTRIBUTE_NODISCARD SROOK_HAS_CPP_ATTRIBUTE(nodiscard)
#        define SROOK_HAS_CPP_ATTRIBUTE_MAYBE_UNUSED SROOK_HAS_CPP_ATTRIBUTE(maybe_unused)
#        define SROOK_CPP_IF_CONSTEXPR __cpp_if_constexpr
#        define SROOK_CPP_DEDUCTION_GUIDES __cpp_deduction_guides
#        define SROOK_CPP_TEMPLATE_AUTO __cpp_template_auto
#        define SROOK_CPP_STRUCTURED_BINDINGS __cpp_structured_bindings
#        define SROOK_CPP_VARIADIC_USING __cpp_variadic_using
#        define SROOK_CPP_LIB_LAUNDER __cpp_lib_launder
#        define SROOK_CPP_LIB_BYTE __cpp_lib_byte
#        define SROOK_CPP_LIB_HARDWARE_INTERFERENCE_SIZE __cpp_lib_hardware_interference_size
#        define SROOK_CPP_LIB_UNCAUGHT_EXCEPTIONS __cpp_lib_uncaught_exceptions
#        define SROOK_CPP_LIB_TO_CHARS __cpp_lib_to_chars
#        define SROOK_CPP_LIB_OPTIONAL __cpp_lib_optional
#        define SROOK_CPP_LIB_ANY __cpp_lib_any
#        define SROOK_CPP_LIB_STRING_VIEW __cpp_lib_string_view
#        define SROOK_CPP_LIB_APPLY __cpp_lib_apply
#        define SROOK_CPP_LIB_SHARED_PTR_ARRAYS __cpp_lib_shared_ptr_arrays
#        define SROOK_CPP_LIB_BOYER_MOORE_SEARCHER __cpp_lib_boyer_moore_searcher
#        define SROOK_CPP_LIB_SAMPLE __cpp_lib_sample
#        define SROOK_CPP_LIB_AS_CONST __cpp_lib_as_const
#        define SROOK_CPP_LIB_MAKE_FROM_TUPLE __cpp_lib_make_from_tuple
#        define SROOK_CPP_LIB_VARIANT __cpp_lib_variant
#        define SROOK_CPP_LIB_ADDRESSOF_CONSTEXPR __cpp_lib_addressof_constexpr
#        define SROOK_CPP_LIB_TRANSPARENT_OPERATORS __cpp_lib_transparent_operators
#        define SROOK_CPP_LIB_ENABLE_SHARED_FROM_THIS __cpp_lib_enable_shared_from_this
#        define SROOK_CPP_LIB_SHARED_PTR_WEAK_TYPE __cpp_lib_shared_ptr_weak_type
#        define SROOK_CPP_LIB_SHARED_PTR_ARRAYS __cpp_lib_shared_ptr_arrays
#        define SROOK_CPP_LIB_INVOKE __cpp_lib_invoke
#        define SROOK_CPP_LIB_NOT_FN __cpp_lib_not_fn
#        define SROOK_CPP_LIB_VOID_T __cpp_lib_void_t
#        define SROOK_CPP_LIB_BOOL_CONSTANT __cpp_lib_bool_constant
#        define SROOK_CPP_LIB_TYPE_TRAIT_VARIABLE_TEMPLATES __cpp_lib_type_trait_variable_templates
#        define SROOK_CPP_LIB_LOGICAL_TRAITS __cpp_lib_logical_traits
#        define SROOK_CPP_LIB_IS_SWAPPABLE __cpp_lib_is_swappable
#        define SROOK_CPP_LIB_IS_INVOCABLE __cpp_lib_is_invocable
#        define SROOK_CPP_LIB_HAS_UNIQUE_OBJECT_REPRESENTATIONS __cpp_lib_has_unique_object_representations
#        define SROOK_CPP_LIB_IS_AGGREGATE __cpp_lib_is_aggregate
#        define SROOK_CPP_LIB_CHRONO __cpp_lib_chrono
#        define SROOK_CPP_LIB_ALLOCATOR_TRAITS_IS_ALYWAYS_EQUAL __cpp_lib_allocator_traits_is_always_equal
#        define SROOK_CPP_LIB_INCOMPLETE_CONTAINER_ELEMENTS __cpp_lib_incomplete_container_elements
#        define SROOK_CPP_LIB_MAP_TRY_EMPLACE __cpp_lib_map_try_emplace
#        define SROOK_CPP_LIB_UNORDERED_MAP_TRY_EMPLACE __cpp_lib_unordered_map_try_emplace
#        define SROOK_CPP_LIB_NODE_EXTRACT __cpp_lib_node_extract
#        define SROOK_CPP_LIB_NONMEMBER_CONTAINER_ACCESS __cpp_lib_nonmember_container_access
#        define SROOK_CPP_LIB_ARRAY_CONSTEXPR __cpp_lib_array_constexpr
#        define SROOK_LIB_CPP_EXECUTION __lib_cpp_execution
#        define SROOK_CPP_LIB_PARALLEL_ALGORITHM __cpp_lib_parallel_algorithm
#        define SROOK_CPP_LIB_CLAMP __cpp_lib_clamp
#        define SROOK_CPP_LIB_GCD __cpp_lib_gcd
#        define SROOK_CPP_LIB_LCM __cpp_lib_lcm
#        define SROOK_CPP_LIB_HYPOT __cpp_lib_hypot
#        define SROOK_CPP_LIB_MATH_SPECIAL_FUNCTIONS __cpp_lib_math_special_functions
#        define SROOK_CPP_LIB_FILESYSTEM __cpp_lib_filesystem
#        define SROOK_CPP_LIB_ATOMIC_IS_ALWAYS_LOCK_FREE __cpp_lib_atomic_is_always_lock_free
#        define SROOK_CPP_LIB_SHARED_MUTEX __cpp_lib_shared_mutex
#        define SROOK_CPP_LIB_SCOPED_LOCK __cpp_lib_scoped_lock
#    else
#        define SROOK_CPP_INLINE_VARIABLES 0
#        define SROOK_CPP_HEX_FLOAT 0
#        define SROOK_CPP_NOEXCEPT_FUNCTION_TYPE 0
#        define SROOK_CPP_FOLD_EXPRESSIONS 0
#        define SROOK_CPP_CAPTURE_STAR_THIS 0
#        define SROOK_CPP_NESTED_NAMESPACE_DEFINITIONS 0
#        define SROOK_HAS_CPP_ATTRIBUTE_FALLTHROUGH 0
#        define SROOK_HAS_CPP_ATTRIBUTE_NODISCARD 0
#        define SROOK_HAS_CPP_ATTRIBUTE_MAYBE_UNUSED 0
#        define SROOK_CPP_IF_CONSTEXPR 0
#        define SROOK_CPP_DEDUCTION_GUIDES 0
#        define SROOK_CPP_TEMPLATE_AUTO 0
#        define SROOK_CPP_STRUCTURED_BINDINGS 0
#        define SROOK_CPP_VARIADIC_USING 0
#        define SROOK_CPP_LIB_LAUNDER 0
#        define SROOK_CPP_LIB_BYTE 0
#        define SROOK_CPP_LIB_HARDWARE_INTERFERENCE_SIZE 0
#        define SROOK_CPP_LIB_UNCAUGHT_EXCEPTIONS 0
#        define SROOK_CPP_LIB_TO_CHARS 0
#        define SROOK_CPP_LIB_OPTIONAL 0
#        define SROOK_CPP_LIB_ANY 0
#        define SROOK_CPP_LIB_STRING_VIEW 0
#        define SROOK_CPP_LIB_APPLY 0
#        define SROOK_CPP_LIB_SHARED_PTR_ARRAYS 0
#        define SROOK_CPP_LIB_BOYER_MOORE_SEARCHER 0
#        define SROOK_CPP_LIB_SAMPLE 0
#        define SROOK_CPP_LIB_AS_CONST 0
#        define SROOK_CPP_LIB_MAKE_FROM_TUPLE 0
#        define SROOK_CPP_LIB_VARIANT 0
#        define SROOK_CPP_LIB_ADDRESSOF_CONSTEXPR 0
#        define SROOK_CPP_LIB_ENABLE_SHARED_FROM_THIS 0
#        define SROOK_CPP_LIB_SHARED_PTR_WEAK_TYPE 0
#        define SROOK_CPP_LIB_SHARED_PTR_ARRAYS 0
#        define SROOK_CPP_LIB_INVOKE 0
#        define SROOK_CPP_LIB_NOT_FN 0
#        define SROOK_CPP_LIB_VOIT_T 0
#        define SROOK_CPP_LIB_BOOL_CONSTANT 0
#        define SROOK_CPP_LIB_TYPE_TRAIT_VARIABLE_TEMPLATES 0
#        define SROOK_CPP_LIB_LOGICAL_TRAITS 0
#        define SROOK_CPP_LIB_IS_SWAPPABLE 0
#        define SROOK_CPP_LIB_IS_INVOCABLE 0
#        define SROOK_CPP_LIB_HAS_UNIQUE_OBJECT_REPRESENTATIONS 0
#        define SROOK_CPP_LIB_IS_AGGREGATE 0
#        define SROOK_CPP_LIB_CHRONO 0
#        define SROOK_CPP_LIB_ALLOCATOR_TRAITS_IS_ALYWAYS_EQUAL 0
#        define SROOK_CPP_LIB_INCOMPLETE_CONTAINER_ELEMENTS 0
#        define SROOK_CPP_LIB_MAP_TRY_EMPLACE 0
#        define SROOK_CPP_LIB_UNORDERED_MAP_TRY_EMPLACE 0
#        define SROOK_CPP_LIB_NODE_EXTRACT 0
#        define SROOK_CPP_LIB_NONMEMBER_CONTAINER_ACCESS 0
#        define SROOK_CPP_LIB_ARRAY_CONSTEXPR 0
#        define SROOK_LIB_CPP_EXECUTION 0
#        define SROOK_CPP_LIB_PARALLEL_ALGORITHM 0
#        define SROOK_CPP_LIB_CLAMP 0
#        define SROOK_CPP_LIB_GCD 0
#        define SROOK_CPP_LIB_LCM 0
#        define SROOK_CPP_LIB_HYPOT 0
#        define SROOK_CPP_LIB_MATH_SPECIAL_FUNCTIONS 0
#        define SROOK_CPP_LIB_FILESYSTEM 0
#        define SROOK_CPP_LIB_ATOMIC_IS_ALWAYS_LOCK_FREE 0
#        define SROOK_CPP_LIB_SHARED_MUTEX 0
#        define SROOK_CPP_LIB_SCOPED_LOCK 0
#    endif

#else
#    if defined(__clang__) || defined(__has_include)
#        define SROOK_HAS_INCLUDE(header) __has_include(header)
#    else
#        define SROOK_HAS_INCLUDE(header)
#    endif

#    define SROOK_HAS_CPP_ATTRIBUTE(attributes) 0

#    if defined(__clang__)
#        define SROOK_CPP_RTTI __has_feature(cxx_rtti)
#    else
#        define SROOK_CPP_RTTI __cpp_rtti
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_EXCEPTIONS __has_feature(cxx_exceptions)
#    else
#        define SROOK_CPP_EXCEPTIONS __cpp_exceptions
#    endif

#    define SROOK_CPP_UNICODE_CHARACTERS __cpp_unicode_characters

#    if defined(__clang__)
#        define SROOK_CPP_RAW_STRINGS __has_feature(cxx_raw_string_literals)
#    else
#        define SROOK_CPP_RAW_STRINGS __cpp_raw_strings
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_UNICODE_LITERALS __has_feature(cxx_unicode_literals)
#    else
#        define SROOK_CPP_UNICODE_LITERALS __cpp_unicode_literals
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_USER_DEFINED_LITERALS __has_feature(cxx_user_literals)
#    else
#        define SROOK_CPP_USER_DEFINED_LITERALS __cpp_user_defined_literals
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_LAMBDAS __has_feature(cxx_lambdas)
#    else
#        define SROOK_CPP_LAMBDAS __cpp_lambdas
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_CONSTEXPR __has_feature(cxx_constexpr)
#    else
#        define SROOK_CPP_CONSTEXPR __cpp_constexpr
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_RANGE_BASED_FOR __has_feature(cxx_range_for)
#    else
#        define SROOK_CPP_RANGE_BASED_FOR __cpp_range_based_for
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_STATIC_ASSERT __has_feature(cxx_static_assert)
#    else
#        define SROOK_CPP_STATIC_ASSERT __cpp_static_assert
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_DECLTYPE __has_feature(cxx_decltype)
#    else
#        define SROOK_CPP_DECLTYPE __cpp_decltype
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_ATTRIBUTES __has_feature(cxx_attributes)
#    else
#        define SROOK_CPP_ATTRIBUTES __cpp_attributes
#    endif

#    define SROOK_CPP_HAS_CPP_ATTRIBUTE_NORETURN SROOK_HAS_CPP_ATTRIBUTE(noreturn)

#    define SROOK_CPP_HAS_CPP_ATTRIBUTE_CARRIES_DEPENDENCY SROOK_HAS_CPP_ATTRIBUTE(carries_dependency)

#    if (__GNUC__ >= 4 && __GNUC__MINOR__ >= 3) || (_MSC_VER >= 1600)
#        if __EDG_VERSION__ > 0
#            define SROOK_CPP_RVALUE_REFERENCES __EDG_VERSION >= 410
#        else
#            define SROOK_CPP_RVALUE_REFERENCES 200610
#        endif
#    elif __clang__
#        define SROOK_CPP_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#    else
#        define SROOK_CPP_RVALUE_REFERENCES __cpp_rvalue_references
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_VARIADIC_TEMPLATES __has_feature(cxx_variadic_templates)
#    else
#        define SROOK_CPP_VARIADIC_TEMPLATES __cpp_variable_templates
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_INITIALIZER_LISTS __has_feature(cxx_generalized_initializers)
#    else
#        define SROOK_CPP_INITIALIZER_LISTS __cpp_initializer_lists
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_DELEGATING_CONSTRUCTORS __has_feature(cxx_delegating_constructors)
#    else
#        define SROOK_CPP_DELEGATING_CONSTRUCTORS __cpp_delegating_constructors
#    endif

#    define SROOK_CPP_NSDMI

#    if defined(__clang__)
#        define SROOK_CPP_INHERITING_CONSTRUCTORS __has_feature(cxx_inheriting_construtors)
#    else
#        define SROOK_CPP_INHERITING_CONSTRUCTORS __cpp_inheriting_constructors
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_REF_QUALIFIERS __has_feature(cxx_reference_qualifiers_functions)
#    else
#        define SROOK_CPP_REF_QUALIFIERS __cpp_ref_qualifiers
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_ALIAS_TEMPLATES __has_feature(cxx_alias_templates)
#    else
#        define SROOK_CPP_ALIAS_TEMPLATES __cpp_alias_templates
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_BINARY_LITERALS __has_feature(cxx_binary_literals)
#    else
#        define SROOK_CPP_BINARY_LITERALS 0
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_DIGIT_SEPARATORS 0
#    else
#        define SROOK_CPP_DIGIT_SEPARATORS 0
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_INIT_CAPUTURES __has_feature(cxx_init_captures)
#    else
#        define SROOK_CPP_INIT_CAPUTURES 0
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_GENERIC_LAMBDAS __has_feature(cxx_generic_lambdas)
#    else
#        define SROOK_CPP_GENERIC_LAMBDAS 0
#    endif

#    define SROOK_CPP_SIZED_DEALLOCATION 0

#    if defined(__clang__)
#        define SROOK_CPP_DECLTYPE_AUTO __has_feature(cxx_decltype_auto)
#    else
#        define SROOK_CPP_DECLTYPE_AUTO 0
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_RETURN_TYPE_DEDUCTION __has_feature(cxx_return_type_deduction)
#    else
#        define SROOK_CPP_RETURN_TYPE_DEDUCTION 0
#    endif

#    if defined(__clang__)
#        define SROOK_VARIABLE_TEMPLATES __has_feature(cxx_variable_templates)
#    else
#        define SROOK_VARIABLE_TEMPLATES 0
#    endif

#    if defined(__clang__)
#        define SROOK_CPP_AGGREGATE_NSDMI __has_feature(cxx_aggregate_nsdmi)
#    else
#        define SROOK_CPP_AGGREGATE_NSDMI 0
#    endif

#    define SROOK_CPP_LIB_EXCHANGE_FUNCTION 0
#    define SROOK_CPP_LIB_TUPLES_BY_TUPLE 0
#    define SROOK_CPP_LIB_TUPLE_ELEMENT_T 0
#    define SROOK_CPP_LIB_MAKE_UNIQUE 0
#    define SROOK_CPP_LIB_TRANSPARENT_OPERATORS 0
#    define SROOK_CPP_LIB_RESULT_OF_SFINAE 0
#    define SROOK_CPP_LIB_INTEGRAL_CONSTANT_CALLABLE 0
#    define SROOK_CPP_LIB_TRANSFORMATION_TRAIT_ALIASES 0
#    define SROOK_CPP_LIB_IS_FINAL 0

#    if defined(__clang__)
#        define SROOK_CPP_LIB_IS_NULL_POINTER __has_feature(cxx_nullptr)
#    else
#        define SROOK_CPP_LIB_IS_NULL_POINTER 1 // fix
#    endif

#    define SROOK_CPP_LIB_CHRONO_UDLS 0
#    define SROOK_CPP_LIB_STRING_UDLS 0
#    define SROOK_CPP_LIB_GENERIC_ASSCIATIVE_LOOKUP 0
#    define SROOK_CPP_LIB_NULL_ITERATORS 0
#    define SROOK_CPP_LIB_MAKE_REVERSE_ITERATOR 0
#    define SROOK_CPP_LIB_ROBUST_NONMODIFYING_SEQ_OPS 0
#    define SROOK_CPP_LIB_COMPLEX_UDLS 0
#    define SROOK_CPP_LIB_QUOTED_STRING_IO 0
#    define SROOK_CPP_LIB_SHARED_TIMED_MUTEX 0
#    define SROOK_CPP_LIB_INTEGER_SEQUENCE 0

    // C++17
#    define SROOK_CPP_INLINE_VARIABLES 0
#    define SROOK_CPP_HEX_FLOAT 0
#    define SROOK_CPP_NOEXCEPT_FUNCTION_TYPE 0
#    define SROOK_CPP_FOLD_EXPRESSIONS 0
#    define SROOK_CPP_CAPTURE_STAR_THIS 0
#    define SROOK_CPP_NESTED_NAMESPACE_DEFINITIONS 0
#    define SROOK_HAS_CPP_ATTRIBUTE_FALLTHROUGH 0
#    define SROOK_HAS_CPP_ATTRIBUTE_NODISCARD 0
#    define SROOK_HAS_CPP_ATTRIBUTE_MAYBE_UNUSED 0
#    define SROOK_CPP_IF_CONSTEXPR 0
#    define SROOK_CPP_DEDUCTION_GUIDES 0
#    define SROOK_CPP_TEMPLATE_AUTO 0
#    define SROOK_CPP_STRUCTURED_BINDINGS 0
#    define SROOK_CPP_VARIADIC_USING 0
#    define SROOK_CPP_LIB_LAUNDER 0
#    define SROOK_CPP_LIB_BYTE 0
#    define SROOK_CPP_LIB_HARDWARE_INTERFERENCE_SIZE 0
#    define SROOK_CPP_LIB_UNCAUGHT_EXCEPTIONS 0
#    define SROOK_CPP_LIB_TO_CHARS 0
#    define SROOK_CPP_LIB_OPTIONAL 0
#    define SROOK_CPP_LIB_ANY 0
#    define SROOK_CPP_LIB_STRING_VIEW 0
#    define SROOK_CPP_LIB_APPLY 0
#    define SROOK_CPP_LIB_SHARED_PTR_ARRAYS 0
#    define SROOK_CPP_LIB_BOYER_MOORE_SEARCHER 0
#    define SROOK_CPP_LIB_SAMPLE 0
#    define SROOK_CPP_LIB_AS_CONST 0
#    define SROOK_CPP_LIB_MAKE_FROM_TUPLE 0
#    define SROOK_CPP_LIB_VARIANT 0
#    define SROOK_CPP_LIB_ADDRESSOF_CONSTEXPR 0
#    define SROOK_CPP_LIB_ENABLE_SHARED_FROM_THIS 0
#    define SROOK_CPP_LIB_SHARED_PTR_WEAK_TYPE 0
#    define SROOK_CPP_LIB_SHARED_PTR_ARRAYS 0
#    define SROOK_CPP_LIB_INVOKE 0
#    define SROOK_CPP_LIB_NOT_FN 0
#    define SROOK_CPP_LIB_VOIT_T 0
#    define SROOK_CPP_LIB_BOOL_CONSTANT 0
#    define SROOK_CPP_LIB_TYPE_TRAIT_VARIABLE_TEMPLATES 0
#    define SROOK_CPP_LIB_LOGICAL_TRAITS 0
#    define SROOK_CPP_LIB_IS_SWAPPABLE 0
#    define SROOK_CPP_LIB_IS_INVOCABLE 0
#    define SROOK_CPP_LIB_HAS_UNIQUE_OBJECT_REPRESENTATIONS 0
#    define SROOK_CPP_LIB_IS_AGGREGATE 0
#    define SROOK_CPP_LIB_CHRONO 0
#    define SROOK_CPP_LIB_ALLOCATOR_TRAITS_IS_ALYWAYS_EQUAL 0
#    define SROOK_CPP_LIB_INCOMPLETE_CONTAINER_ELEMENTS 0
#    define SROOK_CPP_LIB_MAP_TRY_EMPLACE 0
#    define SROOK_CPP_LIB_UNORDERED_MAP_TRY_EMPLACE 0
#    define SROOK_CPP_LIB_NODE_EXTRACT 0
#    define SROOK_CPP_LIB_NONMEMBER_CONTAINER_ACCESS 0
#    define SROOK_CPP_LIB_ARRAY_CONSTEXPR 0
#    define SROOK_LIB_CPP_EXECUTION 0
#    define SROOK_CPP_LIB_PARALLEL_ALGORITHM 0
#    define SROOK_CPP_LIB_CLAMP 0
#    define SROOK_CPP_LIB_GCD 0
#    define SROOK_CPP_LIB_LCM 0
#    define SROOK_CPP_LIB_HYPOT 0
#    define SROOK_CPP_LIB_MATH_SPECIAL_FUNCTIONS 0
#    define SROOK_CPP_LIB_FILESYSTEM 0
#    define SROOK_CPP_LIB_ATOMIC_IS_ALWAYS_LOCK_FREE 0
#    define SROOK_CPP_LIB_SHARED_MUTEX 0
#    define SROOK_CPP_LIB_SCOPED_LOCK 0
#endif

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS17_CONSTANT
#   ifdef __cpp_concepts
#       define SROOK_CPP_CONCEPTS __cpp_concepts
#   else
#       define SROOK_CPP_CONCEPTS 0
#   endif
#endif
#endif
