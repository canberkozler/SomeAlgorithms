#pragma once
#include <iostream>
#include <string>
#include <algorithm>

void extra_space_deleter(std::string& str){
    str.erase(std::unique(str.begin(), str.end(), [](char c1, char c2)
                          { return static_cast<int>(std::isspace(c1)) && static_cast<int>(std::isspace(c2)); }),
              str.end());
}