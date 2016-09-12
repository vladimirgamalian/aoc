#include <iostream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <cassert>
#include "../common/read_file.h"

class reindeer {
public:
    reindeer(std::string name, int speed, int fly_time, int rest_time) :
            name(name), speed(speed), fly_time(fly_time), rest_time(rest_time), counter(fly_time) {}

    void step() {
        if (!rest)
            distance += speed;

        --counter;
        if (!counter) {
            rest = !rest;
            counter = rest ? rest_time : fly_time;
        }
    }

    int get_distance() const {
        return distance;
    }

    std::string name;
    int speed;
    int fly_time;
    int rest_time;

private:
    int distance = 0;
    bool rest = false;
    int counter;
};

std::vector<reindeer> read_data(const std::string& file_name) {
    std::vector<reindeer> result;
    std::vector<std::string> input = read_file_lines(file_name);
    std::regex e("^(\\w+) can fly (\\d+) km\\/s for (\\d+) seconds, but then must rest for (\\d+) seconds\\.$");
    for (const auto& s : input) {
        std::smatch sm;
        assert(std::regex_match(s, sm, e));
        result.push_back(reindeer(sm[1], stoi(sm[2]), stoi(sm[3]), stoi(sm[4])));
    }
    return result;
}

int main() {
    std::vector<reindeer> data = read_data("input.txt");
    const int total_time = 2503;
    for (int i = 0; i < total_time; ++i) {
        for (auto& r : data)
            r.step();
    }

    int max_distance = 0;
    for (auto& r : data) {
        int d = r.get_distance();
        if (d > max_distance)
            max_distance = d;
    }

    std::cout << max_distnace << std::endl;

    return 0;
}
