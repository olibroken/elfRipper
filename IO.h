#pragma once

//
// Created by Oliver James on 04/09/2016.
//

#include <string.h>
#include <fstream>
#include <vector>

class IO {
public:
    static bool ReadFile(std::string path, std::vector<char>& data);
    static bool WriteFile(std::string path, std::vector<char> data);
};