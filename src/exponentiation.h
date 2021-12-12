#include <stdint.h>

template <typename T>
constexpr T pow(T val, uint16_t n) 
{
    T out = 1;

    while (n > 0)
    {
        if (n % 2 == 1) 
        {
            out *= val;
        }
        val *= val;
        n = n / 2;
    }
    return out;
}

void test_pow() 
{
    static_assert(pow<uint32_t>(3, 0) == 1,    "3^0 = 1");
    static_assert(pow<uint32_t>(3, 1) == 3,    "3^1 = 3");
    static_assert(pow<uint32_t>(3, 2) == 9,    "3^2 = 9");
    static_assert(pow<uint32_t>(3, 3) == 27,   "3^3 = 27");
    static_assert(pow<uint32_t>(3, 4) == 81,   "3^4 = 81");
    static_assert(pow<uint32_t>(3, 5) == 243,  "3^5 = 243");
    static_assert(pow<uint32_t>(3, 6) == 729,  "3^6 = 729");
    static_assert(pow<uint32_t>(3, 7) == 2187, "3^7 = 2187");
    static_assert(pow<uint32_t>(3, 8) == 6561, "3^8 = 6561");
    static_assert(pow<uint32_t>(1, 21) == 1,   "1^21 = 1");
    static_assert(pow<uint32_t>(2, 30) == 1073741824, "2^30 = 1073741824");
    static_assert(pow<uint32_t>(2, 31) == 2147483648, "2^31 = 2147483648");

    // numeric overflow for 32bit unsigned int
    static_assert(pow<uint32_t>(2, 32) == 0, "2^32 = 4294967296");
    static_assert(pow<uint64_t>(2, 32) == 4294967296, "2^32 = 4294967296");

    // not sure if it should work with floats, but this test passes :)
    static_assert(51.53632 <= pow<float>(2.2, 5) && pow<float>(2.2, 5) < 51.53633, "2.2^5 = 51.53632000000002");
}
