#pragma once
#include <fstream>
#include <string>
#include <streambuf>
#include <vector>

inline std::string read_file(const std::string& file_name) {
    std::ifstream ifs(file_name);
    return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}

inline std::vector<std::string> read_file_lines(const std::string& file_name) {
    std::ifstream ifs(file_name);
    std::vector<std::string> result;
    std::string l;
    while (std::getline(ifs, l)) {
        result.push_back(std::move(l));
    }
    return result;
}
