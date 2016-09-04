#include <iostream>
#include <string>
#include <cassert>
#include <vector>

class converter
{
public:
    void chain(converter* next) {
        this->next = next;
    }
    void push(char c) {
        if (c == this->c) {
            ++a;
        } else {
            flush();
            a = 1;
            this->c = c;
        }
    }
    void flush() {
        if (a > 0) {
            std::string s = std::to_string(a) + static_cast<char>(c);
            l += s.length();
            if (next)
                for (char c : s)
                    next->push(c);
        }
    }
    int size() const {
        return l;
    }
private:
    converter* next = nullptr;
    int c = -1;
    int a = 0;
    int l = 0;
};

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

int solve_simple(std::string s, int steps) {
    for (int i = 0; i < steps; ++i)
        s = step(s);
    return s.length();
}

int solve_mem_eff(std::string s, int steps) {
    std::vector<converter> converters(steps);
    for (size_t i = 1; i < converters.size(); ++i)
        converters[i - 1].chain(&converters[i]);
    for (char c : s)
        converters.front().push(c);
    for (auto& c : converters)
        c.flush();
    return converters.back().size();
}

int solve(std::string s, int steps) {
    int result = solve_simple(s, steps);
    assert(result == solve_mem_eff(s, steps));
    return result;
}

int main() {
    assert(step("1") == "11");
    assert(step("11") == "21");
    assert(step("21") == "1211");
    assert(step("1211") == "111221");
    assert(step("111221") == "312211");

    std::string s = "3113322113";
    std::cout << solve(s, 40) << "\n";
    std::cout << solve(s, 50) << "\n";

    return 0;
}
