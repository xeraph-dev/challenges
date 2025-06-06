#include "pig_latin.h"
#include "test-framework/unity.h"
#include <stdlib.h>

static char *res = NULL;
void setUp(void) {}

void tearDown(void) {
    if (res)
        free(res);
    res = NULL;
}

static void check_translate(const char *phrase, const char *expected) {
    res = translate(phrase);
    TEST_ASSERT_EQUAL_STRING(expected, res);
}

static void test_word_beginning_with_a(void) {
    check_translate("apple", "appleay");
}

static void test_word_beginning_with_e(void) {
    check_translate("ear", "earay");
}

static void test_word_beginning_with_i(void) {
    check_translate("igloo", "iglooay");
}

static void test_word_beginning_with_o(void) {
    check_translate("object", "objectay");
}

static void test_word_beginning_with_u(void) {
    check_translate("under", "underay");
}

static void test_word_beginning_with_a_vowel_and_followed_by_a_qu(void) {
    check_translate("equal", "equalay");
}

static void test_word_beginning_with_p(void) {
    check_translate("pig", "igpay");
}

static void test_word_beginning_with_k(void) {
    check_translate("koala", "oalakay");
}

static void test_word_beginning_with_x(void) {
    check_translate("xenon", "enonxay");
}

static void test_word_beginning_with_q_without_a_following_u(void) {
    check_translate("qat", "atqay");
}

static void test_word_beginning_with_consonant_and_vowel_containing_qu(void) {
    check_translate("liquid", "iquidlay");
}

static void test_word_beginning_with_ch(void) {
    check_translate("chair", "airchay");
}

static void test_word_beginning_with_qu(void) {
    check_translate("queen", "eenquay");
}

static void test_word_beginning_with_qu_and_a_preceding_consonant(void) {
    check_translate("square", "aresquay");
}

static void test_word_beginning_with_th(void) {
    check_translate("therapy", "erapythay");
}

static void test_word_beginning_with_thr(void) {
    check_translate("thrush", "ushthray");
}

static void test_word_beginning_with_sch(void) {
    check_translate("school", "oolschay");
}

static void test_word_beginning_with_yt(void) {
    check_translate("yttria", "yttriaay");
}

static void test_word_beginning_with_xr(void) {
    check_translate("xray", "xrayay");
}

static void
test_y_is_treated_like_a_consonant_at_the_beginning_of_a_word(void) {
    check_translate("yellow", "ellowyay");
}

static void
test_y_is_treated_like_a_vowel_at_the_end_of_a_consonant_cluster(void) {
    check_translate("rhythm", "ythmrhay");
}

static void test_y_as_second_letter_in_two_letter_word(void) {
    check_translate("my", "ymay");
}

static void test_a_whole_phrase(void) {
    check_translate("quick fast run", "ickquay astfay unray");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_word_beginning_with_a);
    RUN_TEST(test_word_beginning_with_e);
    RUN_TEST(test_word_beginning_with_i);
    RUN_TEST(test_word_beginning_with_o);
    RUN_TEST(test_word_beginning_with_u);
    RUN_TEST(test_word_beginning_with_a_vowel_and_followed_by_a_qu);
    RUN_TEST(test_word_beginning_with_p);
    RUN_TEST(test_word_beginning_with_k);
    RUN_TEST(test_word_beginning_with_x);
    RUN_TEST(test_word_beginning_with_q_without_a_following_u);
    RUN_TEST(test_word_beginning_with_consonant_and_vowel_containing_qu);
    RUN_TEST(test_word_beginning_with_ch);
    RUN_TEST(test_word_beginning_with_qu);
    RUN_TEST(test_word_beginning_with_qu_and_a_preceding_consonant);
    RUN_TEST(test_word_beginning_with_th);
    RUN_TEST(test_word_beginning_with_thr);
    RUN_TEST(test_word_beginning_with_sch);
    RUN_TEST(test_word_beginning_with_yt);
    RUN_TEST(test_word_beginning_with_xr);
    RUN_TEST(test_y_is_treated_like_a_consonant_at_the_beginning_of_a_word);
    RUN_TEST(test_y_is_treated_like_a_vowel_at_the_end_of_a_consonant_cluster);
    RUN_TEST(test_y_as_second_letter_in_two_letter_word);
    RUN_TEST(test_a_whole_phrase);

    return UNITY_END();
}
