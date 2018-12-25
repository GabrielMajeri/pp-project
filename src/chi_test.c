#include "chi.h"
#include "test_utils.h"

void assert_chi2_eq(chi2_values expected, chi2_values actual) {
    assert_almost_eq(expected.red, actual.red);
    assert_almost_eq(expected.green, actual.green);
    assert_almost_eq(expected.blue, actual.blue);
}

int main() {
    chi2_values unencrypted = chi2_image("test_data/peppers.bmp");
    assert_chi2_eq((chi2_values){ 529917.10, 606801.97, 1053070.31 }, unencrypted);

    chi2_values encrypted = chi2_image("test_data/enc_peppers_ok.bmp");
    assert_chi2_eq((chi2_values){ 286.68, 250.71, 226.36 }, encrypted);
}
