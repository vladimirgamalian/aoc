#pragma once
#include <fstream>
#include <string>
#include <streambuf>

inline std::string read_file(const std::string& file_name) {
    std::ifstream ifs(file_name);
    return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}
