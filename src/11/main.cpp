#include <iostream>
#include <string>
#include <cassert>
#include <set>

std::string inc(std::string s) {
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] == 'z') {
            s[i] = 'a';
        } else {
            ++s[i];
            break;
        }
    }
    return s;
}

bool has_three_increasing_straight_letters(const std::string& s) {
    int count = 1;
    for (int i = 1; i < s.length(); ++i) {
        if (s[i - 1] + 1 == s[i]) {
            ++count;
            if (count == 3)
                return true;
        } else {
            count = 1;
        }
    }
    return false;
}

bool has_forbidden_letters(const std::string& s) {
    return s.find_first_of("iol") != std::string::npos;
}

bool has_two_diff_pairs(const std::string& s) {
    std::set<char> set;
    for (int i = 1; i < s.length(); ++i) {
        if (s[i - 1] == s[i]) {
            set.insert(s[i]);
        }
    }
    return set.size() >= 2;
}

bool valid(const std::string& s) {
    return has_three_increasing_straight_letters(s)
           && !has_forbidden_letters(s)
            && has_two_diff_pairs(s);
}

std::string get_next_valid(std::string s) {
    assert(s.length() == 8);
    do {
        s = inc(s);
    } while (!valid(s));
    return s;
}

int main() {
    assert(inc("xx") == "xy");
    assert(inc("xy") == "xz");
    assert(inc("xz") == "ya");
    assert(inc("ya") == "yb");
    assert(inc("zz") == "aa");

    assert(has_three_increasing_straight_letters("abc"));
    assert(has_three_increasing_straight_letters("xabcy"));
    assert(has_three_increasing_straight_letters("xybcd"));
    assert(!has_three_increasing_straight_letters("xybcad"));
    assert(!has_three_increasing_straight_letters("abb"));

    assert(has_forbidden_letters("hijklmmn"));
    assert(has_forbidden_letters("hojkymmn"));
    assert(!has_forbidden_letters("hajkymmn"));

    assert(has_two_diff_pairs("aabb"));
    assert(has_two_diff_pairs("akkbllcc"));
    assert(has_two_diff_pairs("aabbcc"));
    assert(has_two_diff_pairs("zaaxbbycc"));
    assert(!has_two_diff_pairs("aabc"));
    assert(!has_two_diff_pairs("abab"));
    assert(!has_two_diff_pairs("aaab"));
    assert(!has_two_diff_pairs("aaaa"));
    assert(!has_two_diff_pairs("aabaa"));
    assert(!has_two_diff_pairs("abcdefgj"));

    assert(valid("abcdffaa"));
    assert(valid("ghjaabcc"));
    assert(!valid("hijklmmn"));
    assert(!valid("abbceffg"));
    assert(!valid("abbcegjk"));

    assert(get_next_valid("abcdefgh") == "abcdffaa");
    assert(get_next_valid("ghijklmn") == "ghjaabcc");

    std::string input = "hepxcrrq";
    std::string next = get_next_valid(input);
    std::cout << next << "\n";
    next = get_next_valid(next);
    std::cout << next << "\n";

    return 0;
}
