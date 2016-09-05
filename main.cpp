#include <iostream>
#include "IO.h"
#include "elf_headers.h"


bool ExtractSection(std::string section_name, std::vector<char> elf_data, std::vector<char>& section_data)
{
    auto header = reinterpret_cast<ELF::Elf32_Ehdr*>(&elf_data[0]);
    auto section_headers = reinterpret_cast<ELF::Elf32_Shdr*>(&elf_data[header->e_shoff]);

    if (memcmp(&header->e_ident[1], "ELF", 3) != 0)
    {
        std::cout << "invalid elf header" << std::endl;
        return false;
    }

    if (header->e_ident[4] != 1)
    {
        std::cout << "elf image is 64bit" << std::endl;
        header = reinterpret_cast<ELF::Elf64_Ehdr*>(&elf_data[0]);
        section_headers = reinterpret_cast<ELF::Elf64_Shdr*>(&elf_data[0]);
    }

    std::cout << "image has " << header->e_shnum << " section headers." << std::endl;

    // parse sections
    auto name_header = section_headers[header->e_shstrndx];

    for (unsigned i = 0; i < header->e_shnum; i++)
    {
        auto section = section_headers[i];
        std::string section_name_string(&elf_data[name_header.sh_offset + section.sh_name]);

        std::cout << "Section name: " << section_name_string.c_str() << std::endl;

        if (section_name_string.compare(section_name) == 0)
        {
            section_data.insert(section_data.end(),
                                &elf_data[section.sh_offset],
                                &elf_data[section.sh_offset + section.sh_size]);

            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    std::vector<std::string> args;
    std::string output_path;

    std::vector<char> elf_data;
    std::vector<char> section_data;

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

    if (!ExtractSection(args[2], elf_data, section_data))
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