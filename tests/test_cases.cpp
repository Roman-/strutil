/**
 * Copyright (C) 2020 Tomasz Galaj (Shot511) and Roman Strakhov (Roman-)
 */

#include <gtest/gtest.h>
#include <include/strutil.h>

/*
* Comparison tests
*/

TEST(Compare, compare_ignore_case) {
    EXPECT_TRUE(strutil::compare_ignore_case("", ""));
    EXPECT_FALSE(strutil::compare_ignore_case("", "non-empty string"));
    EXPECT_FALSE(strutil::compare_ignore_case("c1", "c2"));

    std::string str1 = "PoKeMoN!";
    std::string str2 = "pokemon!";
    std::string str3 = "POKEMON";

    EXPECT_TRUE(strutil::compare_ignore_case(str1, str2));
    EXPECT_FALSE(strutil::compare_ignore_case(str1, str3));
    EXPECT_FALSE(strutil::compare_ignore_case(str2, str3));
}

TEST(Compare, starts_with_str) {
    EXPECT_TRUE(strutil::starts_with("m_DiffuseTexture", "m_"));
    EXPECT_TRUE(strutil::starts_with("This is a simple test case", "This "));
    EXPECT_TRUE(strutil::starts_with("This is a simple test case", "This is a simple test case"));
    EXPECT_TRUE(strutil::starts_with("This is a simple test case", ""));
    EXPECT_TRUE(strutil::starts_with("", ""));

    EXPECT_FALSE(strutil::starts_with("p_DiffuseTexture", "m_"));
    EXPECT_FALSE(strutil::starts_with("This is a simple test case", "his "));
    EXPECT_FALSE(strutil::starts_with("abc", "abc_"));
    EXPECT_FALSE(strutil::starts_with("abc", "_abc"));

    EXPECT_FALSE(strutil::starts_with("", "m_"));
}

TEST(Compare, starts_with_char) {
    EXPECT_TRUE(strutil::starts_with("m_DiffuseTexture", 'm'));
    EXPECT_TRUE(strutil::starts_with("This is a simple test case", 'T'));

    EXPECT_FALSE(strutil::starts_with("p_DiffuseTexture", 'm'));
    EXPECT_FALSE(strutil::starts_with("This is a simple test case", 'h'));

    EXPECT_FALSE(strutil::starts_with("", 'm'));
}

TEST(Compare, ends_with_str) {
    EXPECT_TRUE(strutil::ends_with("DiffuseTexture_m", "_m"));
    EXPECT_TRUE(strutil::ends_with("This is a simple test case", " test case"));
    EXPECT_TRUE(strutil::ends_with("This is a simple test case", "This is a simple test case"));
    EXPECT_TRUE(strutil::ends_with("This is a simple test case", ""));
    EXPECT_TRUE(strutil::ends_with("", ""));

    EXPECT_FALSE(strutil::ends_with("DiffuseTexture_p", "_m"));
    EXPECT_FALSE(strutil::ends_with("This is a simple test case", "test cas"));
    EXPECT_FALSE(strutil::ends_with("abc", "_abc"));
    EXPECT_FALSE(strutil::ends_with("abc", "abc_"));

    EXPECT_FALSE(strutil::ends_with("", "_m"));
}

TEST(Compare, ends_with_char) {
    EXPECT_TRUE(strutil::ends_with("DiffuseTexture_m", 'm'));
    EXPECT_TRUE(strutil::ends_with("This is a simple test case", 'e'));

    EXPECT_FALSE(strutil::ends_with("DiffuseTexture_p", 'm'));
    EXPECT_FALSE(strutil::ends_with("This is a simple test case", 's'));

    EXPECT_FALSE(strutil::ends_with("", 'm'));
}

TEST(Compare, contains_str) {
    EXPECT_TRUE(strutil::contains("DiffuseTexture_m", "fuse"));
    EXPECT_TRUE(strutil::contains("", ""));
    EXPECT_FALSE(strutil::contains("DiffuseTexture_m", "fuser"));
    EXPECT_FALSE(strutil::contains("abc", "abc_"));
    EXPECT_FALSE(strutil::contains("", "abc"));
}

TEST(Compare, contains_char) {
    EXPECT_TRUE(strutil::contains("DiffuseTexture_m", 'f'));
    EXPECT_FALSE(strutil::contains("DiffuseTexture_m", 'z'));
    EXPECT_FALSE(strutil::contains("", 'z'));
}

/*
 * Parsing tests
 */

TEST(Parsing, short_int_to_string) {
    EXPECT_EQ("-255", strutil::to_string<short int>(-255));
}

TEST(Parsing, u_short_int_to_string) {
    EXPECT_EQ("255", strutil::to_string<unsigned short int>(255));
}

TEST(Parsing, int_to_string) {
    EXPECT_EQ("-255", strutil::to_string<int>(-255));
}

TEST(Parsing, u_int_to_string) {
    EXPECT_EQ("255", strutil::to_string<unsigned int>(255));
}

TEST(Parsing, long_int_to_string) {
    EXPECT_EQ("-255", strutil::to_string<long int>(-255));
}

TEST(Parsing, u_long_int_to_string) {
    EXPECT_EQ("255", strutil::to_string<unsigned long int>(255));
}

TEST(Parsing, long_long_int_to_string) {
    EXPECT_EQ("-255", strutil::to_string<long long int>(-255));
}

TEST(Parsing, u_long_long_int_to_string) {
    EXPECT_EQ("255", strutil::to_string<unsigned long long int>(255));
}

TEST(Parsing, char_to_string) {
    EXPECT_EQ("d", strutil::to_string<char>('d'));
}

TEST(Parsing, u_char_to_string) {
    EXPECT_EQ("d", strutil::to_string<unsigned char>('d'));
}

TEST(Parsing, float_to_string) {
    EXPECT_EQ("5.245", strutil::to_string<float>(5.245f));
}

TEST(Parsing, double_to_string) {
    EXPECT_EQ("5.245", strutil::to_string<double>(5.245));
}

TEST(Parsing, long_double_to_string) {
    EXPECT_EQ("-5.245", strutil::to_string<long double>(-5.245));
}

TEST(Parsing, bool_to_string) {
    EXPECT_EQ("1", strutil::to_string<bool>(true));
}

TEST(Parsing, neg_bool_to_string) {
    EXPECT_EQ("0", strutil::to_string<bool>(false));
}


TEST(StringPreview, replaces_control_characters) {
    std::string input = "Line1\nLine2\r\n\tEnd";
    input.push_back('\x01');
    EXPECT_EQ("Line1\\nLine2\\r\\n\\tEnd\\x01", strutil::preview(input, 100));
}

TEST(StringPreview, preserves_printable_characters) {
    std::string input = "Printable !@#";
    EXPECT_EQ(input, strutil::preview(input, 100));
}

TEST(StringPreview, handles_null_character) {
    const std::string input("A\0B", 3);
    EXPECT_EQ("A\\0B", strutil::preview(input, 100));
}

TEST(StringPreview, truncates_after_sanitizing) {
    std::string input = "abcdef";
    EXPECT_EQ("ab...", strutil::preview(input, 5));
}

/*
* Splitting and tokenizing
*/

TEST(Splitting, split_char_delim) {
    std::string str1 = "asdf;asdfgh;asdfghjk";
    std::vector<std::string> res = strutil::split(str1, ';');
    std::vector<std::string> expected = {"asdf", "asdfgh", "asdfghjk"};
    ASSERT_EQ(res.size(), expected.size()) << "Vectors are of unequal length";
    for (unsigned i = 0; i < res.size(); ++i) {
        EXPECT_EQ(expected[i], res[i]) << "Vectors differ at index " << i;
    }

    // Empty input => empty string
    res = strutil::split("", ';');
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "");

    // No matches => original string
    res = strutil::split(str1, ',');
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], str1);

    // Leading delimiter => leading empty string
    res = strutil::split(";abc", ';');
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "");
    EXPECT_EQ(res[1], "abc");

    // Trailing delimiter => trailing empty string
    res = strutil::split("abc;", ';');
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "");

    // Repeated delimiters => repeated empty strings
    res = strutil::split("abc;;;def", ';');
    expected = {"abc", "", "", "def"};
    ASSERT_EQ(res.size(), expected.size());
    for (unsigned i = 0; i < res.size(); ++i) {
        EXPECT_EQ(expected[i], res[i]);
    }
}

TEST(Splitting, split_string_delim) {
    std::string str1 = "asdf>=asdfgh>=asdfghjk";
    std::vector<std::string> res = strutil::split(str1, ">=");
    std::vector<std::string> expected = {"asdf", "asdfgh", "asdfghjk"};
    ASSERT_EQ(res.size(), expected.size()) << "Vectors are of unequal length";
    for (unsigned i = 0; i < res.size(); ++i) {
        EXPECT_EQ(expected[i], res[i]) << "Vectors differ at index " << i;
    }

    // Empty input => empty string
    res = strutil::split("", ">=");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "");

    // No matches => original string
    res = strutil::split(str1, "<>");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], str1);

    // Leading delimiter => leading empty string
    res = strutil::split(">=abc", ">=");
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "");
    EXPECT_EQ(res[1], "abc");

    // Trailing delimiter => trailing empty string
    res = strutil::split("abc>=", ">=");
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "");

    // Repeated delimiters => repeated empty strings
    res = strutil::split("abc>=>=>=def", ">=");
    expected = {"abc", "", "", "def"};
    ASSERT_EQ(res.size(), expected.size());
    for (unsigned i = 0; i < res.size(); ++i) {
        EXPECT_EQ(expected[i], res[i]);
    }
}

TEST(Splitting, split_lines) {
    const std::vector<std::pair<std::string, std::vector<std::string>>> test_cases = {
        {"1abc\ndef\nghi",           {"1abc",       "def",   "ghi"}},
        {"2abc\r\ndef\t\nghi",       {"2abc",       "def\t", "ghi"}},
        {"3abc\rde f\nghi",          {"3abc\rde f", "ghi"}},
        {"\r\n4abc\n\r\ndef\nghi\n", {"",           "4abc",  "", "def", "ghi", ""}},
        {"\n",                       {"",           ""}}, // exactly two
        {"",                         {""}},
    };
    for (const auto& t : test_cases) {
        auto result = strutil::split_lines(t.first);
        EXPECT_EQ(result, t.second) << t.first;
    }
}

TEST(Splitting, split_lines_clean) {
    const std::vector<std::pair<std::string, std::vector<std::string>>> test_cases = {
        {"1abc\ndef\nghi",              {"1abc", "def", "ghi"}},
        {"2abc\r\ndef\n ghi",           {"2abc", "def", "ghi"}},
        {"  \r\n  3abc\t\r\n\tdef ghi", {"3abc", "def ghi"}},
        {"\r\n\t\n\t",                  {}}, // no non-empty lines
        {"",                            {}}, // no non-empty lines
    };
    for (const auto& t : test_cases) {
        auto result = strutil::split_lines_clean(t.first);
        EXPECT_EQ(result, t.second) << t.first;
    }
}


TEST(Splitting, split_any) {
    std::vector<std::string> res;

    // Basic usage
    res = strutil::split_any("abc,def|ghi jkl", ",| ");
    ASSERT_EQ(res.size(), 4);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "def");
    EXPECT_EQ(res[2], "ghi");
    EXPECT_EQ(res[3], "jkl");

    // Empty input => empty string
    ASSERT_EQ(strutil::split_any("", ",:")[0], "");

    // No matches => original string
    res = strutil::split_any("abc_123", ",; ");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "abc_123");

    // Empty delimiters => original string
    res = strutil::split_any("abc;def", "");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "abc;def");

    // Leading delimiters => leading empty string
    res = strutil::split_any(";abc", ",; ");
    ASSERT_EQ(res.size(), 2);
    ASSERT_EQ(res[0], "");
    ASSERT_EQ(res[1], "abc");

    // Trailing delimiters => trailing empty string
    res = strutil::split_any("abc;", ",; ");
    ASSERT_EQ(res.size(), 2);
    ASSERT_EQ(res[0], "abc");
    ASSERT_EQ(res[1], "");

    // Consecutive delimiters => repeated empty strings
    res = strutil::split_any("abc,;123", ",;");
    ASSERT_EQ(res.size(), 3);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "");
    EXPECT_EQ(res[2], "123");
}

TEST(Splitting, join_vector) {
    std::string str1 = "Col1;Col2;Col3";
    std::vector<std::string> tokens1 = {"Col1", "Col2", "Col3"};

    EXPECT_EQ(str1, strutil::join(tokens1, ";"));

    std::string str2 = "1|2|3";
    std::vector<unsigned> tokens2 = {1, 2, 3};

    EXPECT_EQ(str2, strutil::join(tokens2, "|"));

    std::vector<std::string> empty_tokens;
    EXPECT_EQ(strutil::join(empty_tokens, ";"), "");

    std::vector<std::string> tokens3{"a", "b", "c"};
    EXPECT_EQ(strutil::join(tokens3, ""), "abc");
}

TEST(Splitting, join_set) {
    std::set<unsigned> tokens2 = {1, 2, 3, 42};
    EXPECT_EQ(strutil::join(tokens2, "|"), "1|2|3|42");
}

TEST(Splitting, join_vector_int8_t) {
    std::vector<int8_t> tokens2 = {1, 2, 3, 42};
    EXPECT_EQ(strutil::join(tokens2, "|"), "1|2|3|42");
}

TEST(Splitting, drop_empty) {
    std::vector<std::string> tokens = {"t1", "t2", "", "t4", ""};
    strutil::drop_empty(tokens);
    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens[0], "t1");
    ASSERT_EQ(tokens[1], "t2");
    ASSERT_EQ(tokens[2], "t4");
}

TEST(Splitting, drop_empty_copy) {
    std::vector<std::string> tokens = {"t1", "t2", "", "t4", ""};
    auto res = strutil::drop_empty_copy(tokens);
    ASSERT_EQ(res.size(), 3);
    ASSERT_EQ(res[0], "t1");
    ASSERT_EQ(res[1], "t2");
    ASSERT_EQ(res[2], "t4");
}

/*
 * Text manipulation tests
 */

TEST(TextManip, to_lower) {
    EXPECT_EQ("hello strutil", strutil::to_lower("HeLlo StRUTIL"));
    EXPECT_EQ("", strutil::to_lower(""));
}

TEST(TextManip, to_upper) {
    EXPECT_EQ("HELLO STRUTIL", strutil::to_upper("HeLlo StRUTIL"));
    EXPECT_EQ("", strutil::to_upper(""));
}

TEST(TextManip, capitalize) {
    EXPECT_EQ("HeLlo StRUTIL", strutil::capitalize("heLlo StRUTIL"));
    EXPECT_EQ("+ is an operator.", strutil::capitalize("+ is an operator."));
    EXPECT_EQ("", strutil::capitalize(""));
}

TEST(TextManip, trim_left_in_place) {
    std::string test = "   HeLlo StRUTIL ";
    strutil::trim_left(test);

    EXPECT_EQ("HeLlo StRUTIL ", test);
}

TEST(TextManip, trim_right_in_place) {
    std::string test = " HeLlo StRUTIL    ";
    strutil::trim_right(test);

    EXPECT_EQ(" HeLlo StRUTIL", test);
}

TEST(TextManip, trim_both_in_place) {
    std::string test = "   HeLlo StRUTIL    ";
    strutil::trim(test);

    EXPECT_EQ("HeLlo StRUTIL", test);
}

TEST(TextManip, trim_left) {
    EXPECT_EQ("HeLlo StRUTIL", strutil::trim_left_copy("     HeLlo StRUTIL"));
}

TEST(TextManip, trim_right) {
    EXPECT_EQ("HeLlo StRUTIL", strutil::trim_right_copy("HeLlo StRUTIL       "));
}

TEST(TextManip, trim_both) {
    EXPECT_EQ("HeLlo StRUTIL", strutil::trim_copy("    HeLlo StRUTIL      "));
}

TEST(TextManip, repeat) {
    EXPECT_EQ("GoGoGoGo", strutil::repeat("Go", 4));
    EXPECT_EQ("ZZZZZZZZZZ", strutil::repeat('Z', 10));
}

TEST(TextManip, truncate) {
    EXPECT_EQ("hello world", strutil::truncate("hello world", 100));
    EXPECT_EQ("he...", strutil::truncate("hello world", 5));
    EXPECT_EQ("h~", strutil::truncate("hello world", 2, "~"));
    EXPECT_EQ("", strutil::truncate("hello", 0));
    EXPECT_EQ("..", strutil::truncate("hello", 2));
}

TEST(TextManip, replace_first) {
    std::string str1 = "This is $name and that is also $name.";
    bool res = strutil::replace_first(str1, "$name", "Jon Doe");

    EXPECT_TRUE(res);
    EXPECT_EQ("This is Jon Doe and that is also $name.", str1);
}

TEST(TextManip, no_replace_first) {
    std::string str1 = "This is $name and that is also $name.";
    bool res = strutil::replace_first(str1, "$name$", "Jon Doe");

    EXPECT_FALSE(res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextManip, replace_last) {
    std::string str1 = "This is $name and that is also $name.";
    bool res = strutil::replace_last(str1, "$name", "Jon Doe");

    EXPECT_TRUE(res);
    EXPECT_EQ("This is $name and that is also Jon Doe.", str1);
}

TEST(TextManip, no_replace_last) {
    std::string str1 = "This is $name and that is also $name.";
    bool res = strutil::replace_last(str1, "$name$", "Jon Doe");

    EXPECT_FALSE(res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextManip, replace_all) {
    std::string str1 = "This is $name and that is also $name.";
    bool res = strutil::replace_all(str1, "$name", "Jon Doe");

    EXPECT_TRUE(res);
    EXPECT_EQ("This is Jon Doe and that is also Jon Doe.", str1);
}

TEST(TextManip, no_replace_all) {
    std::string str1 = "This is $name and that is also $name.";
    bool res = strutil::replace_last(str1, "$name$", "Jon Doe");

    EXPECT_FALSE(res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextManip, replace_all_target_empty) {
    std::string str1 = "This is $name and that is also $name.";
    bool res = strutil::replace_all(str1, "", "Jon Doe");

    EXPECT_FALSE(res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextSortAscending, sorting_ascending) {
    std::vector<std::string> str1 = {"ABC", "abc", "bcd", "", "-", "  ", "123", "-100"};
    strutil::sorting_ascending(str1);

    std::vector<std::string> str2 = {"", "  ", "-", "-100", "123", "ABC", "abc", "bcd"};
    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str2.cbegin()), true);
}

TEST(TextSortDescending, sorting_descending) {
    std::vector<std::string> str1 = {"ABC", "abc", "bcd", "", "-", "  ", "123", "-100"};
    strutil::sorting_descending(str1);

    std::vector<std::string> str2 = {"bcd", "abc", "ABC", "123", "-100", "-", "  ", ""};
    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str2.cbegin()), true);
}

TEST(TextReverseInplace, reverse_inplace) {
    std::vector<std::string> str1 = {"bcd", "abc", "ABC", "123", "-100", "-", "  ", ""};

    strutil::reverse_inplace(str1);

    std::vector<std::string> str2 = {"", "  ", "-", "-100", "123", "ABC", "abc", "bcd"};

    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str2.cbegin()), true);
}

TEST(TextReverseCopy, reverse_copy) {
    std::vector<std::string> str1 = {"bcd", "abc", "ABC", "123", "-100", "-", "  ", ""};
    std::vector<std::string> str3(str1.begin(), str1.end());

    auto str4 = strutil::reverse_copy(str1);

    std::vector<std::string> str2 = {"", "  ", "-", "-100", "123", "ABC", "abc", "bcd"};

    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str3.cbegin()), true);
    EXPECT_EQ(std::equal(str4.cbegin(), str4.cend(), str2.cbegin()), true);
}

TEST(Random, random_lowercase_string) {
    ASSERT_TRUE(strutil::random_lowercase_string(0).empty());

    // generate a bunch of 20-char strings, ensure each of them is 20 characters long, unique and lowercase
    const size_t num_strings{50};
    const size_t string_size{20};
    std::vector<std::string> strings;
    std::generate_n(std::back_inserter(strings),
                    num_strings,
                    [&]() { return strutil::random_lowercase_string(string_size); });
    for (const auto& s : strings) {
        ASSERT_EQ(s.size(), string_size);
        for (const char c : s) {
            ASSERT_TRUE(std::islower(c));
        }
    }
    std::sort(strings.begin(), strings.end()); // duplicate strings will be adjacent
    ASSERT_EQ(strings.end(), std::adjacent_find(strings.begin(), strings.end(), std::equal_to<>()));
}

TEST(Random, random_alphanumeric_string) {
    ASSERT_TRUE(strutil::random_alphanumeric_string(0).empty());

    // generate a bunch of 20-char strings, ensure each of them is 20 characters long, unique and alphanumeric
    const size_t num_strings{50};
    const size_t string_size{20};
    std::vector<std::string> strings;
    std::generate_n(std::back_inserter(strings),
                    num_strings,
                    [&]() { return strutil::random_alphanumeric_string(string_size); });
    for (const auto& s : strings) {
        ASSERT_EQ(s.size(), string_size);
        for (const char c : s) {
            ASSERT_TRUE(std::isalpha(c) || std::isdigit(c));
        }
    }
    std::sort(strings.begin(), strings.end()); // duplicate strings will be adjacent
    ASSERT_EQ(strings.end(), std::adjacent_find(strings.begin(), strings.end(), std::equal_to<>()));
}

TEST(BytesToString, to_hex_string) {
    EXPECT_EQ(strutil::to_hex_string(nullptr, 0, true), "");
    EXPECT_EQ(strutil::to_hex_string(nullptr, 0, false), "");

    uint8_t test_data1[] = {0xAA, 0xBB}; // Hex: AABB
    uint8_t test_data2[] = {0x01, 0xFF}; // Hex: 01FF

    EXPECT_EQ(strutil::to_hex_string(test_data1, sizeof(test_data1), true), "AABB");
    EXPECT_EQ(strutil::to_hex_string(test_data2, sizeof(test_data2), true), "01FF");

    EXPECT_EQ(strutil::to_hex_string(test_data1, sizeof(test_data1), false), "aabb");
    EXPECT_EQ(strutil::to_hex_string(test_data2, sizeof(test_data2), false), "01ff");
}

TEST(BytesToString, to_binary_string) {
    EXPECT_EQ(strutil::to_binary_string(nullptr, 0), "");

    uint8_t test_data1[] = {0b10101010, 0b10111011};
    uint8_t test_data2[] = {0b00000001, 0b11111111};

    EXPECT_EQ(strutil::to_binary_string(test_data1, sizeof(test_data1)), "1010101010111011");
    EXPECT_EQ(strutil::to_binary_string(test_data2, sizeof(test_data2)), "0000000111111111");
}

TEST(Checks, is_alphanumeric_positive) {
    const std::vector<std::string> alphanumeric{
        "",
        "a",
        "Z",
        "0",
        "9",
        "ioshnaet",
        "io9s8hnae8t0123456780"
    };

    for (const auto& s : alphanumeric) {
        ASSERT_TRUE(strutil::is_alphanumeric(s)) << s;
    }
}

TEST(Checks, is_alphanumeric_negative) {
    const std::vector<std::string> non_alphanumeric{
        "_",
        "-",
        "A!Z",
        "0.",
        "aaaaaa ",
        " aaaaaa",
        "..."
    };

    for (const auto& s : non_alphanumeric) {
        ASSERT_FALSE(strutil::is_alphanumeric(s)) << s;
    }
}