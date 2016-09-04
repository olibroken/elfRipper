#include <iostream>

#include "IO.h"
#include "elf_headers.h"

std::vector<char> elf_data;
std::vector<char> section_data;

bool ExtractSection(std::string section_name, std::vector<char>& data)
{
    auto header = reinterpret_cast<ELF::elf_header32*>(&elf_data[0]);

    // todo: header validation

    // parse sections
    auto section_headers = reinterpret_cast<ELF::elf_section_header32*>(&elf_data[header->e_shoff]);
    auto name_header = section_headers[header->e_shstrndx];

    for (unsigned i = 0; i < header->e_shnum; i++)
    {
        auto section = section_headers[i];
        std::string section_name_string(&elf_data[name_header.offset + section.name]);

        if (section_name_string.compare(section_name) == 0)
        {
            data.insert(data.end(), &elf_data[section.offset], &elf_data[section.offset + section.size]);
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> args;
    std::string output_path;

    for (unsigned i = 0; i < argc; i++)
        args.push_back(argv[i]);

    if (args.size() < 3) {
        std::cout << "example: 'elfRipper main.o .text'" << std::endl;
        return -1;
    }

    if (!IO::ReadFile(args[1], elf_data))
    {
        std::cout << "failed to open file: " << args[1].c_str() << std::endl;
        return -1;
    }

    if (!ExtractSection(args[2], section_data))
    {
        std::cout << "failed to extract section" << std::endl;
        return -1;
    }

    output_path.append(args[2]);
    output_path.erase(0, 1);
    output_path.append(".dump");

    std::cout << "writing section to file: " << output_path.c_str() << std::endl;
    if (!IO::WriteFile(output_path, section_data))
    {
        std::cout << "failed to write file..." << std::endl;
        return -1;
    }

    return 0;
}