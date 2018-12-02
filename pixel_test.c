#include "pixel.h"
#include "test_utils.h"

void assert_pixel_eq(pixel a, pixel b) {
    assert_eq(a.red, b.red);
    assert_eq(a.green, b.green);
    assert_eq(a.blue, b.blue);
}

void test_grayscale(void) {
    // a pixel from the peppers.bmp file
    const pixel original = { 101, 0, 0 };
    const pixel grayscale = pixel_rgb_to_grayscale(original);

    const pixel expected = { 30, 30, 30 };

    assert_pixel_eq(expected, grayscale);
}

void test_xor(void) {
    const u32 a = 0xEDFAB0;
    const pixel pa = u32_to_pixel(a);

    const u32 b = 0xAA1FCD;
    const pixel pb = u32_to_pixel(b);

    const pixel exp_a = {
        .blue = 176,
        .green = 250,
        .red = 237,
    };

    // verific ca merge conversia
    assert_pixel_eq(exp_a, pa);

    // verific bijectivitatea conversiei
    assert_eq(b, pixel_to_u32(pb));

    // testez xor pe pixeli
    const pixel axb = pixel_xor(pa, pb);

    const pixel exp_axb = {
        .blue = 0x7D,
        .green = 0xE5,
        .red = 0x47,
    };

    assert_pixel_eq(exp_axb, axb);
}

int main() {
    test_grayscale();
    test_xor();
}
