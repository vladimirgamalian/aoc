#include <iostream>
#include <string>
#include <cassert>

std::string step(const std::string& s) {
    assert(!s.empty());

    std::string result;
    int adj = 1;
    char c = s[0];
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == c) {
            ++adj;
        } else {
            result += std::to_string(adj) + c;
            c = s[i];
            adj = 1;
        }
    }

    result += std::to_string(adj) + c;
    return result;
}

int main() {
    assert(step("1") == "11");
    assert(step("11") == "21");
    assert(step("21") == "1211");
    assert(step("1211") == "111221");
    assert(step("111221") == "312211");

    std::string s = "3113322113";
    for (int i = 0; i < 40; ++i)
        s = step(s);

    assert(s.length() == 329356);

    std::cout << s.length() << "\n";

    return 0;
}
