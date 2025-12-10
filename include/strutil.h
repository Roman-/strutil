/**
******************************************************************************
*
*  @mainpage strutil v1.1.0 - header-only string utility library documentation
*  @see https://github.com/Shot511/strutil
*
*  @copyright  Copyright (C) 2020 Tomasz Galaj (Shot511) and Roman Strakhov (Roman-)
*  @file       strutil.h
*  @brief      Library public interface header
*
******************************************************************************
*/

#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <iomanip>

//! The strutil namespace
namespace strutil {
/**
 * @brief Converts any datatype into std::string.
 *        Datatype must support << operator.
 * @tparam T
 * @param value - will be converted into std::string.
 * @return Converted value as std::string.
 */
template<typename T>
static inline std::string to_string(T value) {
    std::stringstream ss;
    ss << value;

    return ss.str();
}

/** 
 * @brief Converts std::string to lower case.
 * @param str - string that needs to be converted.
 * @return Lower case input std::string.
 */
static inline std::string to_lower(std::string_view str) {
    std::string result{str};
    std::transform(result.begin(), result.end(), result.begin(), [](char c) {
        return static_cast<char>(std::tolower(c));
    });

    return result;
}

/**
 * @brief Converts std::string to upper case.
 * @param str - string that needs to be converted.
 * @return Upper case input std::string.
 */
static inline std::string to_upper(std::string_view str) {
    std::string result{str};
    std::transform(result.begin(), result.end(), result.begin(), [](char c) {
        return static_cast<char>(std::toupper(c));
    });

    return result;
}

/**
 * @brief Converts the first character of a string to uppercase letter and lowercases all other characters, if any.
 * @param str - input string to be capitalized.
 * @return A string with the first letter capitalized and all other characters lowercased. It doesn't modify the input string.
 */
static inline std::string capitalize(std::string_view str) {
    std::string result{str};
    if (!result.empty()) {
        result.front() = static_cast<char>(std::toupper(result.front()));
    }

    return result;
}

/**
 * @brief Converts only the first character of a string to uppercase letter, all other characters stay unchanged.
 * @param str - input string to be modified.
 * @return A string with the first letter capitalized. All other characters stay unchanged. It doesn't modify the input string.
 */
static inline bool contains(std::string_view str, std::string_view substring) {
    return str.find(substring) != std::string::npos;
}

/**
 * @brief Checks if input std::string_view str contains specified character.
 * @param str - std::string to be checked.
 * @param character - searched character.
 * @return True if character was found in str, false otherwise.
 */
static inline bool contains(std::string_view str, const char character) {
    return str.find(character) != std::string::npos;
}

/**
 * @brief Compares two strings ignoring their case (lower/upper).
 * @param str1 - string to compare
 * @param str2 - string to compare
 * @return True if str1 and str2 are equal, false otherwise.
 */
static inline bool compare_ignore_case(std::string_view str1, std::string_view str2) {
    return str1.size() == str2.size()
           && std::equal(str1.begin(),
                         str1.end(),
                         str2.begin(),
                         [](char c1, char c2) { return std::tolower(c1) == std::tolower(c2); });
}

/**
 * @brief Trims (in-place) white spaces from the left side of std::string.
 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 */
static inline void trim_left(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); }));
}

/**
 * @brief Trims (in-place) white spaces from the right side of std::string.
 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 */
static inline void trim_right(std::string& str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base(), str.end());
}

/**
 * @brief Trims (in-place) white spaces from the both sides of std::string.
 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 */
static inline void trim(std::string& str) {
    trim_left(str);
    trim_right(str);
}

/**
 * @brief Trims white spaces from the left side of std::string.
 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
 * @param str - input std::string to remove white spaces from.
 * @return Copy of input str with trimmed white spaces.
 */
static inline std::string trim_left_copy(std::string str) {
    trim_left(str);
    return str;
}

/**
  * @brief Trims white spaces from the right side of std::string.
  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
  * @param str - input std::string to remove white spaces from.
  * @return Copy of input str with trimmed white spaces.
  */
static inline std::string trim_right_copy(std::string str) {
    trim_right(str);
    return str;
}

/**
  * @brief Trims white spaces from the both sides of std::string.
  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
  * @param str - input std::string to remove white spaces from.
  * @return Copy of input str with trimmed white spaces.
  */
static inline std::string trim_copy(std::string str) {
    trim(str);
    return str;
}

/**
 * @brief Replaces (in-place) the first occurance of target with replacement.
 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
 * @param str - input std::string that will be modified.
 * @param target - substring that will be replaced with replacement.
 * @param replecament - substring that will replace target.
 * @return True if replacement was successful, false otherwise.
 */
static inline bool replace_first(std::string& str, const std::string& target, const std::string& replecament) {
    size_t start_pos = str.find(target);
    if (start_pos == std::string::npos) {
        return false;
    }

    str.replace(start_pos, target.length(), replecament);
    return true;
}

/**
 * @brief Replaces (in-place) last occurance of target with replacement.
 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
 * @param str - input std::string that will be modified.
 * @param target - substring that will be replaced with replacement.
 * @param replecament - substring that will replace target.
 * @return True if replacement was successful, false otherwise.
 */
static inline bool replace_last(std::string& str, const std::string& target, const std::string& replecament) {
    size_t start_pos = str.rfind(target);
    if (start_pos == std::string::npos) {
        return false;
    }

    str.replace(start_pos, target.length(), replecament);
    return true;
}

/**
 * @brief Replaces (in-place) all occurances of target with replacement.
 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
 * @param str - input std::string that will be modified.
 * @param target - substring that will be replaced with replacement.
 * @param replacement - substring that will replace target.
 * @return True if replacement was successful, false otherwise.
 */
static inline bool replace_all(std::string& str, const std::string& target, const std::string& replacement) {
    if (str.empty() || target.empty()) {
        return false;
    }

    size_t start_pos = 0;
    const bool found_substring = str.find(target, start_pos) != std::string::npos;

    while ((start_pos = str.find(target, start_pos)) != std::string::npos) {
        str.replace(start_pos, target.length(), replacement);
        start_pos += replacement.length();
    }

    return found_substring;
}

/**
 * @brief Checks if std::string_view str ends with specified suffix.
 * @param str - input std::string_view that will be checked.
 * @param suffix - searched suffix in str.
 * @return True if suffix was found, false otherwise.
 */
static inline bool ends_with(std::string_view str, std::string_view suffix) {
    const auto suffix_start = str.size() - suffix.size();
    const auto result = str.find(suffix, suffix_start);
    return (result == suffix_start) && (result != std::string::npos);
}

/**
 * @brief Checks if std::string_view str ends with specified character.
 * @param str - input std::string_view that will be checked.
 * @param suffix - searched character in str.
 * @return True if ends with character, false otherwise.
 */
static inline bool ends_with(std::string_view str, const char suffix) {
    return !str.empty() && (str.back() == suffix);
}

/**
 * @brief Checks if std::string_view str starts with specified prefix.
 * @param str - input std::string_view that will be checked.
 * @param prefix - searched prefix in str.
 * @return True if prefix was found, false otherwise.
 */
static inline bool starts_with(std::string_view str, std::string_view prefix) {
    return str.rfind(prefix, 0) == 0;
}

/**
 * @brief Checks if std::string_view str starts with specified character.
 * @param str - input std::string_view that will be checked.
 * @param prefix - searched character in str.
 * @return True if starts with character, false otherwise.
 */
static inline bool starts_with(std::string_view str, const char prefix) {
    return !str.empty() && (str.front() == prefix);
}

/**
 * @brief Splits input string according to input character delimiter.
 * @param s - string that will be splitted.
 * @param delim - the delimiter.
 * @return std::vector<std::string> that contains all splitted tokens.
 */
static inline std::vector<std::string> split(std::string_view s, const char delim) {
    std::vector<std::string> out;

    // Reserve exactly how many tokens we'll produce: #delims + 1
    out.reserve(s.empty() ? 1u
                          : 1u + static_cast<unsigned>(std::count(s.begin(), s.end(), delim)));

    std::size_t start = 0;
    while(true) {
        std::size_t pos = s.find(delim, start);
        if (pos == std::string_view::npos) {
            // Final segment (possibly empty if s ended with delim or s is empty)
            out.emplace_back(s.substr(start));
            break;
        }
        out.emplace_back(s.substr(start, pos - start));
        start = pos + 1;
    }
    return out;
}

/**
 * @brief Splits input string according to input delimiter substring.
 *        Taken from: https://stackoverflow.com/a/46931770/1892346.
 * @param str - string that will be split.
 * @param delim - the delimiter.
 * @return std::vector<std::string> that contains all splitted tokens.
 */
static inline std::vector<std::string> split(std::string_view str, std::string_view delim) {
    size_t pos_start = 0, pos_end, delim_len = delim.size();
    std::string token;
    std::vector<std::string> tokens;

    while ((pos_end = str.find(delim, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        tokens.emplace_back(std::move(token));
    }

    tokens.emplace_back(str.substr(pos_start));
    return tokens;
}

/**
 * @brief Splits input string into lines separated by "\n" or "\r\n".
 * @param str - string that will be split.
 * @return std::vector<std::string> that contains the lines.
 */
static inline std::vector<std::string> split_lines(std::string_view str) {
    std::vector<std::string> tokens = split(str, '\n');
    for (auto& token : tokens) {
        if (!token.empty() && token.back() == '\r') {
            token.pop_back();
        }
    }

    return tokens;
}

/**
 * @brief Splits input string into lines separated by "\n" or "\r\n", trims them and removes empty lines.
 * @param str - string that will be split.
 * @return std::vector<std::string> that contains trimmed non-empty lines.
 */
static inline std::vector<std::string> split_lines_clean(std::string_view str) {
    std::vector<std::string> tokens;
    std::stringstream ss{std::string(str)};

    std::string token;
    while (std::getline(ss, token)) {
        trim(token);
        if (!token.empty()) {
            tokens.emplace_back(std::move(token));
        }
    }

    return tokens;
}

/**
 * @brief Splits input string using any delimiter in the given set.
 * @param str - string that will be split.
 * @param delims - the set of delimiter characters.
 * @return vector of resulting tokens.
 */
static inline std::vector<std::string> split_any(std::string_view str, std::string_view delims) {
    std::string token;
    std::vector<std::string> tokens;

    size_t pos_start = 0;
    for (size_t pos_end = 0; pos_end < str.length(); ++pos_end) {
        if (contains(delims, str[pos_end])) {
            token = str.substr(pos_start, pos_end - pos_start);
            tokens.push_back(token);
            pos_start = pos_end + 1;
        }
    }

    tokens.emplace_back(str.substr(pos_start));
    return tokens;
}

/**
 * @brief Joins all elements of std::vector tokens of arbitrary datatypes
 *        into one std::string with delimiter delim.
 * @tparam Container - type of iterable container.
 * @param tokens - container of tokens. @note that int8_t and uint8_t are treated as int.
 * @param delim - the delimiter.
 * @return std::string with joined elements of vector tokens with delimiter delim.
 */
template<typename Container>
static inline std::string join(const Container& tokens, std::string_view delim) {
    std::ostringstream result;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it != tokens.begin()) {
            result << delim;
        }

        // treat Container<int8_t> and Container<uint8_t> as Container<int>
        using ValueType = std::decay_t<decltype(*it)>;
        if constexpr (std::is_same_v<ValueType, int8_t> || std::is_same_v<ValueType, uint8_t>) {
            result << static_cast<int>(*it);
        } else {
            result << *it;
        }
    }

    return result.str();
}

/**
 * @brief Inplace removal of all empty strings in a vector<string>
 * @param tokens - vector of strings.
 */
static inline void drop_empty(std::vector<std::string>& tokens) {
    auto last = std::remove_if(tokens.begin(), tokens.end(), [](const std::string& s) { return s.empty(); });
    tokens.erase(last, tokens.end());
}

/**
 * @brief Inplace removal of all empty strings in a vector<string>
 * @param tokens - vector of strings.
 * @return vector of non-empty tokens.
 */
static inline std::vector<std::string> drop_empty_copy(std::vector<std::string> tokens) {
    drop_empty(tokens);
    return tokens;
}

/** 
 * @brief Creates new std::string with repeated n times substring str.
 * @param str - substring that needs to be repeated.
 * @param n - number of iterations.
 * @return std::string with repeated substring str.
 */
static inline std::string repeat(std::string_view str, unsigned n) {
    std::ostringstream ss;

    for (unsigned i = 0; i < n; ++i) {
        ss << str;
    }

    return ss.str();
}

/**
 * @brief Creates new std::string with repeated n times char c.
 * @param c - char that needs to be repeated.
 * @param n - number of iterations.
 * @return std::string with repeated char c.
 */
static inline std::string repeat(char c, unsigned n) {
    return std::string(n, c);
}

/**
 * @brief Sort input std::vector<std::string> strs in ascending order.
 * @param strs - std::vector<std::string> to be checked.
 */
template<typename T>
static inline void sorting_ascending(std::vector<T>& strs) {
    std::sort(strs.begin(), strs.end());
}

/**
 * @brief Sorted input std::vector<std::string> strs in descending order.
 * @param strs - std::vector<std::string> to be checked.
 */
template<typename T>
static inline void sorting_descending(std::vector<T>& strs) {
    std::sort(strs.begin(), strs.end(), std::greater<T>());
}

/**
 * @brief Reverse input std::vector<std::string> strs.
 * @param strs - std::vector<std::string> to be checked.
 */
template<typename T>
static inline void reverse_inplace(std::vector<T>& strs) {
    std::reverse(strs.begin(), strs.end());
}

/**
 * @brief Reverse input std::vector<std::string> strs.
 * @param strs - std::vector<std::string> to be checked.
 */
template<typename T>
static inline std::vector<T> reverse_copy(std::vector<T> strs) {
    std::reverse(strs.begin(), strs.end());
    return strs;
}

/**
 * @brief Generate string of given size consisting of random alphanumeric characters
 * @param size - number of chars in string
 */
static inline std::string random_alphanumeric_string(size_t size) {
    static const char symbols[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string result;
    result.reserve(size);
    std::generate_n(std::back_inserter(result), size, []() { return symbols[rand() % (sizeof(symbols) - 1)]; });
    return result;
}

/**
 * @brief generates string of random lowercase latin characters
 * @param size - number of chars in string
 */
static inline std::string random_lowercase_string(size_t size) {
    std::string result;
    result.reserve(size);
    std::generate_n(std::back_inserter(result), size, []() { return 'a' + char(rand() % ('z' - 'a')); });
    return result;
}

/**
 * @brief Truncates the source string so that the result does not exceed
 *        max_output_string_length characters. If truncation happens, the
 *        ellipsis string is appended to the truncated substring.
 * @param source_string - the input string that may need to be truncated.
 * @param max_output_string_length - maximum length of the returned string.
 * @param ellipsis - string appended when truncation occurs.
 * @return Truncated string with optional ellipsis.
 */
static inline std::string truncate(std::string_view source_string,
                                   size_t max_output_string_length = 100,
                                   std::string_view ellipsis = "...") {
    if (source_string.size() <= max_output_string_length) {
        return std::string(source_string);
    }

    if (max_output_string_length <= ellipsis.size()) {
        return std::string(ellipsis.substr(0, max_output_string_length));
    }

    std::string result(source_string.substr(0, max_output_string_length - ellipsis.size()));
    result.append(ellipsis);
    return result;
}

/**
 * @brief Produce a sanitized preview of the input string where non-printable
 *        characters are replaced with escape sequences. The result is then
 *        truncated using the same rules as strutil::truncate.
 *
 * @param source_string - the input string that may contain non-printable
 *                        characters.
 * @param max_output_string_length - maximum length of the returned string.
 * @param ellipsis - string appended when truncation occurs.
 * @return Sanitized and possibly truncated string.
 */
static inline std::string preview(std::string_view source_string,
                                  size_t max_output_string_length = 100,
                                  std::string_view ellipsis = "...") {
    static constexpr char HEX_DIGITS[] = "0123456789ABCDEF";

    std::string sanitized;
    sanitized.reserve(source_string.size());

    for (unsigned char ch : source_string) {
        switch (ch) {
            case '\\':
                sanitized.append("\\\\");
                break;
            case '\n':
                sanitized.append("\\n");
                break;
            case '\r':
                sanitized.append("\\r");
                break;
            case '\t':
                sanitized.append("\\t");
                break;
            case '\0':
                sanitized.append("\\0");
                break;
            case '\b':
                sanitized.append("\\b");
                break;
            case '\f':
                sanitized.append("\\f");
                break;
            case '\v':
                sanitized.append("\\v");
                break;
            default:
                if (std::isprint(ch)) {
                    sanitized.push_back(static_cast<char>(ch));
                } else {
                    char buffer[4] = {'\\', 'x', HEX_DIGITS[ch >> 4], HEX_DIGITS[ch & 0x0F]};
                    sanitized.append(buffer, 4);
                }
                break;
        }
    }

    return truncate(sanitized, max_output_string_length, ellipsis);
}

/**
 * @brief converts a byte array to its hexadecimal string representation.
 * @param size - number of chars in string
 */
static inline std::string to_hex_string(const uint8_t* data, size_t size, bool uppercase = true) {
    std::ostringstream oss;

    // Set uppercase or lowercase based on the 'uppercase' flag
    oss << (uppercase ? std::uppercase : std::nouppercase);
    oss << std::hex << std::setfill('0');

    for (size_t i = 0; i < size; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    return oss.str();
}

/**
 * @brief converts a byte array to its binary string representation.
 * @param size - number of chars in string
 */
static inline std::string to_binary_string(const uint8_t* data, size_t size) {
    std::string result(size * 8, '0');
    for (size_t i = 0; i < size; ++i) {
        for (int j = 7; j >= 0; --j) {
            result[i * 8 + (7 - j)] = (data[i] & (1 << j)) ? '1' : '0';
        }
    }
    return result;
}

/**
 * @returns true if string does not contain characters other than latin letters, both uppercase and lowercase, and digits
 */
static inline bool is_alphanumeric(std::string_view s) {
    return std::all_of(s.begin(), s.end(), [](char c) { return bool(std::isalnum(c)); });
}

}