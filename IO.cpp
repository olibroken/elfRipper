//
// Created by Oliver James on 04/09/2016.
//

#include "IO.h"

bool IO::ReadFile(std::string path, std::vector<char>& data)
{
    std::ifstream file_stream(path.c_str(), std::ios::in | std::ios::binary);

    if (file_stream.is_open())
    {
        data.clear();
        file_stream.seekg(0, file_stream.end);

        try {
            data.resize(file_stream.tellg());
        } catch (const std::bad_alloc& e)
        {
            // probably a huge file
            return false;
        }

        file_stream.seekg(0, file_stream.beg);
        file_stream.read(&data[0], data.size());
        file_stream.close();

        return true;
    }

    return false;
}

bool IO::WriteFile(std::string path, std::vector<char> data)
{
    std::ofstream file_stream(path.c_str(), std::ios::out | std::ios::binary);

    if (file_stream.is_open())
    {
        try {
            file_stream.write(&data[0], data.size());
        } catch (const std::exception& e)
        {
            return false;
        }

        file_stream.flush();
        file_stream.close();
        return true;
    }

    return false;

}