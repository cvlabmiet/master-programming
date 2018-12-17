#include <catch2/catch.hpp>

#include <functional>
#include <vector>

struct custom_image
{
    custom_image(std::pair<long, long> p): w(p.first), h(p.second)
    {}

    struct view
    {
        long width() const
        {
            return parent->w;
        }

        custom_image* parent;
    };

    std::vector<std::tuple<int, int, int, int>> values;
    long w;
    long h;
};

struct custom_view
{
    std::pair<long, long> dimensions() const
    {
        return {1123, 579};
    }
};

namespace boost::gil
{

custom_image::view view(custom_image& im)
{
    return {&im};
}

custom_view view(custom_view& vw)
{
    return vw;
}

std::vector<int> subimage_view(custom_image::view& view, int x, int y, int w, int h)
{
    view.parent->values.emplace_back(x, y, w, h);
    return {0, 1, 2};
}

template<class Matrix, class Auto>
void resample_pixels(custom_view, custom_image::view, const Matrix& m, Auto)
{
    CHECK(m.a == Approx(0.96596));
    CHECK(m.b == Approx(-0.25869));
    CHECK(m.c == Approx(0.25869));
    CHECK(m.d == Approx(0.96596));
    CHECK(m.e == Approx(-257.86474));
    CHECK(m.f == Approx(-189.75187));
}

}

#include "imgproc.hpp"

TEST_CASE("imgproc::histogram")
{
    std::vector<uint8_t> custom_view = {5, 8, 9, 8, 5, 44, 56, 7, 8};
    std::vector<double> reference(256);
    reference[5] = 2 / 9.;
    reference[7] = 1 / 9.;
    reference[8] = 3 / 9.;
    reference[9] = reference[44] = reference[56] = 1 / 9.;

    auto hist = imgproc::histogram(custom_view);
    CHECK(hist == reference);
}

TEST_CASE("imgproc::bar")
{
    std::vector<double> custom_bar = {0.1, 0.2, 0.5, 0.1, 0.1};
    auto img = imgproc::bar<custom_image>(custom_bar, 720, 480);

    CHECK(720 == img.w);
    CHECK(480 == img.h);
    REQUIRE(img.values.size() == 5);

    // 144 = 720 / 5
    CHECK(std::tuple{0, 480 * (1 - 0.1), 144, 480 * 0.1} == img.values[0]);
    CHECK(std::tuple{144, 480 * (1 - 0.2), 144, 480 * 0.2} == img.values[1]);
    CHECK(std::tuple{2 * 144, 480 * (1 - 0.5), 144, 480 * 0.5} == img.values[2]);
    CHECK(std::tuple{3 * 144, 480 * (1 - 0.1), 144, 480 * 0.1} == img.values[3]);
    CHECK(std::tuple{4 * 144, 480 * (1 - 0.1), 144, 480 * 0.1} == img.values[4]);
}

TEST_CASE("imgproc::transform")
{
    auto img = imgproc::transform<custom_view, custom_image>(custom_view{});
    CHECK(1123 == img.w);
    CHECK(579 == img.h);
}
