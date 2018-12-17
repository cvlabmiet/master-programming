#ifndef __IMGPROC_HPP__
#define __IMGPROC_HPP__

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

#include <boost/gil.hpp>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/gil/image_view_factory.hpp>

#include "imgproc-version.hpp"

namespace imgproc
{

template<class GrayView>
std::vector<double> histogram(const GrayView& view)
{
    const auto type_width = static_cast<size_t>(std::exp2(8 * sizeof(typename GrayView::value_type)));
    std::vector<size_t> cumsum(type_width + 1);
    for (const auto pixel : view)
    {
        if (cumsum.back() == std::numeric_limits<size_t>::max())
            std::for_each(cumsum.begin(), cumsum.end(), [](auto& x) { x /= 2; });

        std::for_each(cumsum.begin() + pixel, cumsum.end(), [](auto& x) { ++x; });
    }

    const double m = cumsum.back();
    std::vector<double> hist(cumsum.size() - 1);
    hist.front() = cumsum.front() / m;
    std::transform(cumsum.begin() + 1, cumsum.end() - 1, cumsum.begin(), hist.begin() + 1, [m](double x, double p) { return (x - p) / m; });

    return hist;
}

template<class Image = boost::gil::gray8_image_t>
Image bar(const std::vector<double>& bars, long width = 512, long height = 512)
{
    Image out{{width, height}};
    auto view = boost::gil::view(out);

    auto step = view.width() / bars.size();

    for (size_t i = 0, s = bars.size(); i < s; ++i)
    {
        const auto h = height * bars[i];
        auto v = boost::gil::subimage_view(view, i * step, height - h, step, h);
        std::fill(v.begin(), v.end(), 255);
    }

    return out;
}

template<class View, class Image = boost::gil::gray8_image_t>
Image transform(const View& view)
{
    namespace bg = boost::gil;

    Image img(view.dimensions());
    bg::matrix3x2<double> mat =
        bg::matrix3x2<double>::get_translate(-bg::point2<double>(200,250)) *
        bg::matrix3x2<double>::get_rotate(-15*3.14/180.0);

    bg::resample_pixels(view, bg::view(img), mat, bg::nearest_neighbor_sampler{});
    return img;
}

} // namespace imgproc

#endif // __IMGPROC_HPP__
