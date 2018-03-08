// Reference: https://www.jstage.jst.go.jp/article/itej/64/5/64_5_729/_pdf/-char/ja
#ifndef INCLUDED_SROOK_IO2D_OPENCV_ALGORITHM_POISSON_POISSON_HPP
#define INCLUDED_SROOK_IO2D_OPENCV_ALGORITHM_POISSON_POISSON_HPP
#include <srook/io2d/opencv/algorithm/poisson/config.hpp>
#include <srook/array.hpp>
#include <srook/limits/numeric_limits.hpp>
#include <srook/type_traits/iterator/is_randomaccessiterator.hpp>
#include <srook/type_traits/is_pointer.hpp>
#include <srook/type_traits/detail/logical.hpp>

SROOK_NESTED_NAMESPACE(srook, io2d, opencv, algorithm) {
SROOK_INLINE_NAMESPACE(v1)

class poisson {
public:
    SROOK_INLINE_VARIABLE static SROOK_CONSTEXPR std::size_t default_loop_max = 2 << 10;
    typedef srook::float32_t float32_t;
    typedef srook::float64_t float64_t;

    template <class Range, SROOK_REQUIRES(type_traits::detail::Lor<is_randomaccessiterator<SROOK_DEDUCED_TYPENAME Range::iterator>, is_pointer<SROOK_DEDUCED_TYPENAME Range::iterator>>::value)>
    cv::Mat operator()(const cv::Mat& src, const cv::Mat& dst, const cv::Mat& img_mask, const Range& offset, const std::size_t loop_max = default_loop_max)
    {
        cv::Mat result = cv::Mat::zeros(dst.size(), dst.type());

        for (std::size_t channel = 0; channel < 3; ++channel) {
            cv::Mat img_out = (cv::Mat_<float64_t>(dst.rows, dst.cols));
            int i, j;
            for (i = 0; i < dst.rows; ++i) {
                for (j = 0; j < dst.cols; ++j) {
                    img_out.ptr<float64_t>(i)[j] = static_cast<float64_t>(dst.ptr<cv::Vec3b>(i)[j][channel]);
                }
            }

            std::size_t neighbor, cneighbors;
            constexpr srook::array<srook::array<int, 2>, 4> naddr = {{ {{-1, 0}}, {{0, -1}}, {{0, 1}}, {{1, 0}} }};
            float32_t fp;
            bool check = true, fedge = true;

            for (std::size_t loop = 0; loop < loop_max && check; ++loop) {
                check = false;
                for (i = 0; i < img_mask.rows; i++) {
                    for (j = 0; j < img_mask.cols; j++) {
                        if (static_cast<int>(img_mask.ptr<cv::Vec3b>(i)[j][0]) > 0) {
                            float32_t sum_f = .0f, sum_fstar = .0f, sum_vpq = .0f;
                            cneighbors = 0;
                            fedge = false;
                            for (neighbor = 0; neighbor < naddr.size(); ++neighbor) {
                                if (!img_mask.ptr<cv::Vec3b>(i + naddr[neighbor][0])[j + naddr[neighbor][1]][0]) {
                                    fedge = 1;
                                    break;
                                }
                            }
                            if (!fedge) {
                                for (auto&& n : naddr) {
                                    if (i + offset[0] + n[0] >= 0 && j + offset[1] + n[1] >= 0 && i + offset[0] + n[0] < dst.rows && j + offset[1] + n[1] < dst.cols) {
                                        sum_f += img_out.ptr<float64_t>(i + offset[0] + n[0])[j + offset[1] + n[1]];
                                        sum_vpq += static_cast<float32_t>(src.ptr<cv::Vec3b>(i)[j][channel]) - static_cast<float32_t>(src.ptr<cv::Vec3b>(i + n[0])[j + n[1]][channel]);
                                        ++cneighbors;
                                    }
                                }
                            } else {
                                for (auto&& n : naddr) {
                                    if (i + offset[0] + n[0] >= 0 && j + offset[1] + n[1] >= 0 && i + offset[0] + n[0] < dst.rows && j + offset[1] + n[1] < dst.cols) {
                                        fp = static_cast<float32_t>(dst.ptr<cv::Vec3b>(i + offset[0])[j + offset[1]][channel]);
                                        const float32_t fq = static_cast<float32_t>(dst.ptr<cv::Vec3b>(i + offset[0] + n[0])[j + offset[1] + n[1]][channel]);
                                        const float32_t gp = static_cast<float32_t>(src.ptr<cv::Vec3b>(i)[j][channel]);
                                        const float32_t gq = static_cast<float32_t>(src.ptr<cv::Vec3b>(i + n[1])[j + n[1]][channel]);
                                        sum_fstar += fq;
                                        sum_vpq += std::fabs(fp - fq) > std::fabs(gp - gq) ? fp - fq : gp - gq;
                                        ++cneighbors;
                                    }
                                }
                            }
                            fp = (sum_f + sum_fstar + sum_vpq) / static_cast<float32_t>(cneighbors);
                            if (std::fabs(fp - img_out.ptr<float64_t>(i + offset[0])[j + offset[1]]) > srook::numeric_limits<float64_t>::epsilon() * (1 + std::fabs(fp))) check = true;
                            img_out.ptr<float64_t>(i + offset[0])[j + offset[1]] = fp;
                        }
                    }
                }
            }

            for (i = 0; i < dst.rows; ++i) {
                for (j = 0; j < dst.cols; ++j) {
                    if (img_out.ptr<float64_t>(i)[j] > 255)
                        img_out.ptr<float64_t>(i)[j] = 255.0;
                    else if (img_out.ptr<float64_t>(i)[j] < 0)
                        img_out.ptr<float64_t>(i)[j] = 0.0;
                    result.ptr<cv::Vec3b>(i)[j][channel] = static_cast<unsigned char>(img_out.ptr<float64_t>(i)[j]);
                }
            }
        }
        return result;
    }
};

template <class Range, SROOK_REQUIRES(type_traits::detail::Lor<is_randomaccessiterator<SROOK_DEDUCED_TYPENAME Range::iterator>, is_pointer<SROOK_DEDUCED_TYPENAME Range::iterator>>::value)>
SROOK_FORCE_INLINE cv::Mat poisson_compute(const cv::Mat& src, const cv::Mat& dst, const cv::Mat& mask, const Range& offset, const std::size_t loop_max = poisson::default_loop_max)
{
    return poisson()(src, dst, mask, offset, loop_max);
}

SROOK_INLINE_NAMESPACE_END 
} SROOK_NESTED_NAMESPACE_END(algorithm, opencv, io2d, srook)
#endif
