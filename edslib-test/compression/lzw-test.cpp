#include "catch.hpp"
#include "compression/lzw.h"
#include <random>
#include <functional>

TEST_CASE("::compression")
{
    static constexpr auto kTestEpoch = 20;
    static constexpr auto kTestScale = 1000;

    using namespace std;
    using namespace eds::compression;

    random_device rd;
    default_random_engine gen{rd()};
    uniform_int_distribution<> dis_len{0, 255};

    for (int i = 0; i < kTestEpoch; ++i)
    {
        vector<uint8_t> v(kTestScale);
        generate(v.begin(), v.end(), bind(dis_len, gen));

        auto e = EncodeLzw(v.begin(), v.end());
        auto d = DecodeLzw(e.begin(), e.end());

        CHECK(d == v);
    }
}