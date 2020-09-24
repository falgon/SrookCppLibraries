// Copyright (C) 2011-2020 Roki. Distributed under the MIT License
#ifndef INCLUDED_SROOK_K_MEANS_HPP
#define INCLUDED_SROOK_K_MEANS_HPP
#include <srook/config/cpp_predefined.hpp>

#if SROOK_CPLUSPLUS >= SROOK_CPLUSPLUS11_CONSTANT

#    include <cassert>
#    include <cmath>
#    include <fstream>
#    include <iostream>
#    include <random>
#    include <srook/limits/numeric_limits.hpp>
#    include <srook/utility/move.hpp>
#    include <srook/utility/forward.hpp>
#    include <srook/algorithm/for_each.hpp>
#    include <srook/config/require.hpp>
#    include <srook/config/feature.hpp>
#    include <srook/plot/gnu/ploter.hpp>
#    include <srook/type_traits/conditional.hpp>
#    include <srook/type_traits/decay.hpp>
#    include <srook/type_traits/detail/logical.hpp>
#    include <srook/type_traits/is_same.hpp>
#    include <vector>

namespace srook {
namespace clustering {
SROOK_INLINE_NAMESPACE(v1)

using Point = std::pair<double, double>;

struct k_means {
    k_means(const char* file, std::size_t clustering_size) : master_vec(srook::move(clustering_size)), initialized(false)
    {
		using namespace std;

        ifstream ifs(file);
        if (!ifs.fail()) {
			std::string one_point, first, second;
            while (getline(ifs, one_point)) {
				std::string::const_iterator iter = next(begin(one_point), one_point.find(","));
                copy(cbegin(one_point), iter, back_inserter(first));
                copy(next(iter, 1), cend(one_point), back_inserter(second));

                input_data.emplace_back(Point{stod(first), stod(second)});
                first.clear();
                second.clear();
            }
        }
    }

    template <class... Ts, SROOK_REQUIRES(((sizeof...(Ts) > 0) && type_traits::detail::Land<is_same<Point, Ts>...>::value))>
    void set_initial_point(Ts&&... ts) SROOK_MEMFN_NOEXCEPT(true)
    {
		const auto tpl = std::forward_as_tuple(srook::forward<Ts>(ts)...);
        assert(sizeof...(ts) == clustering_size());
        srook::for_each(srook::make_counter(tpl), [this](const auto& x, std::size_t i) { master_vec[i] = x; });
        initialized = true;
    }

    template <class T>
    using rand_type = typename conditional<
        !is_same<typename decay<T>::type, double>::value && !is_same<typename decay<T>::type, float>::value,
        std::uniform_int_distribution<typename decay<T>::type>,
        std::uniform_real_distribution<typename decay<T>::type> >::type;
    template <class X, class Y>
    void set_initial_point(X&& x_min, X&& x_max, Y&& y_min, Y&& y_max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        rand_type<X> x_dis(srook::forward<X>(x_min), srook::forward<X>(x_max));
        rand_type<Y> y_dis(srook::forward<Y>(y_min), srook::forward<Y>(y_max));

        for (auto& v : master_vec)
            v = Point{x_dis(gen), y_dis(gen)};
        initialized = true;
    }

    void clustering()
    {
		using namespace std;

        if (!initialized) {
            vector<Point::first_type> xs(input_data.size());
            vector<Point::second_type> ys(input_data.size());
            srook::for_each(srook::make_counter(xs), [this](auto& x, size_t i) { x = input_data[i].first; });
            srook::for_each(srook::make_counter(ys), [this](auto& y, size_t i) { y = input_data[i].second; });

            set_initial_point(
                *min_element(begin(xs), end(xs)), *max_element(begin(xs), end(xs)),
                *min_element(begin(ys), end(ys)), *max_element(begin(ys), end(ys)));
        }

        vector<int> prev_cluster(input_data.size(), 0);
        cluster.resize(input_data.size(), -1);

        while (!equal(begin(prev_cluster), end(prev_cluster), begin(cluster), end(cluster))) {
            prev_cluster = cluster;

            srook::for_each(
                srook::make_counter(input_data),
                [this](const auto& v, std::size_t i) {
                    int max_cluster = -1;
                    double arg_max = srook::numeric_limits<double>::infinity();

                    srook::for_each(
                        srook::make_counter(master_vec),
                        [this, &arg_max, &v, &max_cluster](const auto& mp, size_t j) {
                            if (arg_max > distance(v, mp)) {
                                arg_max = distance(v, mp);
                                max_cluster = j;
                            }
                        });
                    cluster[i] = max_cluster;
                });

            srook::for_each(
                srook::make_counter(master_vec),
                [this](auto& m, int i) {
                    int c = 0;
                    m.first = 0;
                    m.second = 0;
                    srook::for_each(
                        srook::make_counter(input_data),
                        [i, &c, &m, this](const auto& v, std::size_t j) {
                            if (cluster[j] == i) {
                                m.first += v.first;
                                m.second += v.second;
                                ++c;
                            }
                        });
                    if (c) {
                        m.first /= c;
                        m.second /= c;
                    }
                });
        }
    }

    std::vector<Point>::size_type clustering_size() 
	const SROOK_MEMFN_NOEXCEPT(true)
    {
        return master_vec.size();
    }

private:
    std::vector<Point> input_data;
    std::vector<int> cluster;
    std::vector<Point> master_vec;
    bool initialized;

private:
    double distance(const Point& l, const Point& r)
	const SROOK_MEMFN_NOEXCEPT(true)
    {
        return std::sqrt(std::pow(l.first - r.first, 2.0) + std::pow(l.second - r.second, 2.0));
    }

    friend std::ofstream& operator<<(std::ofstream& ofs, const k_means& km)
    {
        for (std::size_t i = 0; i < km.clustering_size(); ++i) {
            srook::for_each(
                srook::make_counter(km.input_data),
                [i, &ofs, &km](const auto& v, std::size_t j) {
                    if (std::size_t(km.cluster[j]) == i) {
                        ofs << v.first << " " << v.second << "\n";
                    }
                });
            ofs << "\n\n";
        }
        return ofs;
    }

    friend std::ostream& operator<<(std::ostream& os, const k_means& km)
    {
        for (std::size_t i = 0; i < km.clustering_size(); ++i) {
            srook::for_each(
                srook::make_counter(km.input_data),
                [i, &os, &km](const auto& v, std::size_t j) {
                    if (std::size_t(km.cluster[j]) == i) {
                        os << v.first << "," << v.second << "\n";
                    }
                });
            os << "\n";
        }
        return os;
    }
};

SROOK_INLINE_NAMESPACE_END
} // namespace clustering
} // namespace srook

#    endif
#endif
