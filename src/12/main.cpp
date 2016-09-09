#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include "../common/json.hpp"

using json = nlohmann::json;

std::string readFile(const std::string& file_name) {
    std::ifstream ifs(file_name);
    return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}

int solve_part_a(const std::string& input) {
    int sum = 0;
    bool inside_string = false;
    std::string number_string;
    for (char c : input) {
        if (c == '\"') {
            inside_string = !inside_string;
            continue;
        }
        if (inside_string)
            continue;
        if ((c >= '0' && c <= '9') || (c == '-')) {
            number_string += c;
        } else {
            if (!number_string.empty()) {
                int n = std::stoi(number_string);
                number_string = "";
                sum += n;
            }
        }
    }
    return sum;
}

int recursive_pass_obj(const json j);

int recursive_pass_array(const json j) {
    int sum = 0;
    for (auto& e : j) {
        if (e.is_array())
            sum += recursive_pass_array(e);
        else if (e.is_object())
            sum += recursive_pass_obj(e);
        else if (e.is_number())
            sum += e.get<int>();
    }
    return sum;
}

int recursive_pass_obj(const json j) {
    int sum = 0;
    bool is_red = false;
    for (json::const_iterator it = j.begin(); it != j.end(); ++it) {
        json e = it.value();
        if (e.is_array())
            sum += recursive_pass_array(e);
        else if (e.is_object())
            sum += recursive_pass_obj(e);
        else if (e.is_number())
            sum += e.get<int>();
        else if (e.is_string() && e.get<std::string>() == "red")
            is_red = true;
    }
    return is_red ? 0 : sum;
}

int solve_part_b(const std::string& input) {
    auto j = json::parse(input);
    return j.is_array() ? recursive_pass_array(j) : recursive_pass_obj(j);
}

int main() {
    std::string input = readFile("input.txt");
    std::cout << solve_part_a(input) << "\n";
    std::cout << solve_part_b(input) << "\n";
    return 0;
}
