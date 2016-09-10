#include <iostream>
#include "../common/read_file.h"
#include "../common/json.hpp"

using json = nlohmann::json;

int recursive_pass(const json& j, bool exclude_red) {
    int sum = 0;
    bool is_red = false;

    if (j.is_array()) {
        for (auto& e : j) {
            sum += recursive_pass(e, exclude_red);
        }
    } else if (j.is_object()) {
        for (json::const_iterator it = j.begin(); it != j.end(); ++it) {
            json e = it.value();
            sum += recursive_pass(e, exclude_red);
            if (exclude_red && e.is_string() && e == "red")
                is_red = true;
        }
    } else if (j.is_number()) {
        sum = j;
    }

    return is_red ? 0 : sum;
}

int main() {
    json j = json::parse(read_file("input.txt"));
    std::cout << recursive_pass(j, false) << "\n";
    std::cout << recursive_pass(j, true) << "\n";
    return 0;
}
