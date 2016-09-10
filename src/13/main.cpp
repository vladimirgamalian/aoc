#include <iostream>
#include <regex>
#include <cassert>
#include <unordered_map>
#include "../common/read_file.h"
#include "../common/permutation.h"

typedef std::unordered_map<std::string, std::unordered_map<std::string, int>> relations;

int calc_happiness(relations& r,
                   const std::vector<std::string>& names,
                   const std::vector<int>& pos) {

    assert(pos.size() > 2);

    std::string first_person = names[pos[0]];
    std::string second_person = names[pos[pos.size() - 1]];
    int result = r[first_person][second_person] + r[second_person][first_person];

    for (size_t i = 1; i < pos.size(); ++i) {
        first_person = names[pos[i - 1]];
        second_person = names[pos[i]];
        result += r[first_person][second_person] + r[second_person][first_person];
    }

    return result;
}

relations read_relations(const std::string& file_name) {
    std::vector<std::string> input = read_file_lines(file_name);
    std::regex e("^(\\w+) would (gain|lose) (\\d+) happiness units by sitting next to (\\w+).$");
    relations result;
    for (const auto& s : input) {
        std::smatch sm;
        assert(std::regex_match(s, sm, e));
        std::string person = sm[1];
        std::string other_person = sm[4];
        int happiness = stoi(sm[3]);
        if (sm[2] == "lose")
            happiness = -happiness;
        result[person][other_person] = happiness;
    }
    return result;
}

int solve(relations& r) {
    std::vector<std::string> names;
    for (const auto& k : r)
        names.push_back(k.first);

    assert(names.size() > 2);

    std::vector<int> permutations(names.size());
    for (size_t i = 0; i < permutations.size(); ++i)
        permutations[i] = i;

    int max_happiness = calc_happiness(r, names, permutations);
    while (next_set(&permutations[0], permutations.size())) {
        int happiness = calc_happiness(r, names, permutations);
        if (happiness > max_happiness) {
            max_happiness = happiness;
        }
    };

    return max_happiness;
}

int main() {
    relations r = read_relations("input.txt");
    std::cout << solve(r) << "\n";
    r["Me"][""] = 0;
    std::cout << solve(r) << "\n";
    return 0;
}
