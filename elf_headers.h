#pragma once
//
// Created by Oliver James on 05/09/2016.
//

#include <stdint.h>

namespace ELF {

    struct Elf32_Ehdr {
        uint8_t	    e_ident[16];
        uint16_t	e_type;
        uint16_t	e_machine;
        uint32_t	e_version;

        uint32_t	e_entry;  /* Entry point */
        uint32_t	e_phoff;
        uint32_t	e_shoff;

        uint32_t	e_flags;
        uint16_t	e_ehsize;
        uint16_t	e_phentsize;
        uint16_t	e_phnum;
        uint16_t	e_shentsize;
        uint16_t	e_shnum;
        uint16_t	e_shstrndx;
    };

    struct Elf64_Ehdr : Elf32_Ehdr {
        uint64_t	e_entry;  /* Entry point */
        uint64_t	e_phoff;
        uint64_t	e_shoff;
    };

    struct Elf32_Shdr {
        uint32_t	sh_name;
        uint32_t	sh_type;
        uint32_t	sh_flags;
        uint32_t	sh_addr;
        uint32_t	sh_offset;
        uint32_t	sh_size;
        uint32_t	sh_link;
        uint32_t	sh_info;
        uint32_t	sh_addralign;
        uint32_t	sh_entsize;
    };

    struct Elf64_Shdr : Elf32_Shdr {

        uint64_t	sh_flags;
        uint64_t	sh_addr;
        uint64_t	sh_offset;
        uint64_t	sh_size;

        uint64_t	sh_addralign;
        uint64_t	sh_entsize;
    };
}