// Copyright (C) 2011-2018 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_CONTAINER_BLOCK_LIST_HPP
#define INCLUDED_SROOK_CONTAINER_BLOCK_LIST_HPP

#include <srook/container/detail/config_begin.hpp>
#include <srook/container/detail/list_node.hpp>
#include <srook/memory_resource/memory_resource.hpp>
#include <srook/intrusive/detail/circular_list_algorithms.hpp>
#include <srook/utility.hpp>

namespace srook {
namespace container {
namespace pmr {

namespace detail {

struct block_list_header : public list_node<std::size_t> {};

typedef intrusive::circular_list_algorithms<list_node_traits<list_node<std::size_t>>> list_algo;

template <class DerivedFromBlockListHeader = block_list_header>
class block_list_base : noncopyable<block_list_base<DerivedFromBlockListHeader>> {
    list_node<std::size_t> m_list;
    static SROOK_CONSTEXPR_OR_CONST std::size_t max_align_sub1 = srook::pmr::memory_resource::max_align - 1u;
public:
    static SROOK_CONSTEXPR_OR_CONST std::size_t header_size = std::size_t(sizeof(DerivedFromBlockListHeader) + max_align_sub1) & std::size_t(~max_align_sub1);

    explicit block_list_base()
    {
        list_algo::init_header(&m_list);
    }

    void* allocate(std::size_t size, srook::pmr::memory_resource& mr)
    {
        if ((std::size_t(-1) - header_size) < size) SROOK_THROW std::bad_alloc();
        void* p = mr.allocate(size + header_size);
        block_list_header& mb = *::new(p) DerivedFromBlockListHeader;
        mb.data_ = size + header_size;
        list_algo::link_after(&m_list, &mb);
        return static_cast<char*>(p) + header_size;
    }

    void deallocate(void* p, srook::pmr::memory_resource& mr) SROOK_NOEXCEPT_TRUE
    {
        DerivedFromBlockListHeader* ph = static_cast<DerivedFromBlockListHeader*>(static_cast<void*>((static_cast<char*>(p) - header_size)));
        list_algo::unlink(ph);
        const std::size_t size = ph->data_;
        static_cast<DerivedFromBlockListHeader*>(ph)->~DerivedFromBlockListHeader();
        mr.deallocate(ph, size, srook::pmr::memory_resource::max_align);
    }

    void release(srook::pmr::memory_resource& mr) SROOK_NOEXCEPT_TRUE
    {
        list_node<std::size_t>* n = list_algo::node_traits::get_next(&m_list);
        while (n != &m_list) {
            DerivedFromBlockListHeader& d = static_cast<DerivedFromBlockListHeader&>(*n);
            n = list_algo::node_traits::get_next(n);
            std::size_t size = d.data_;
            d.~DerivedFromBlockListHeader();
            mr.deallocate(reinterpret_cast<char*>(&d), size, srook::pmr::memory_resource::max_align);
        }
        list_algo::init_header(&m_list);
    }
};

} // namespace detail

} // namespace pmr
} // namespace container
} // namespace srook

#include <srook/container/detail/config_end.hpp>
#endif
