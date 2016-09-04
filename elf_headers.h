#pragma once

//
// Created by Oliver James on 04/09/2016.
//

#include <stdint.h>

namespace ELF {

    struct elf_header32 {
        uint8_t EI_MAG0[4];      // EI_MAG0 sig for elf files: 0x7f, 0x45, 0x4c, 0x46 (ELF)
        uint8_t EI_CLASS;        // 1 = 32 | 2 = 64
        uint8_t EI_DATA;            // 1 = little | 2 = big
        uint8_t EI_VERSION;         // should always be 1?
        uint8_t EI_OSABI;           // abi type.. i assume this will probably be 0x03?
        uint8_t EI_ABIVERSION;     // ignored if linux
        uint8_t EI_PAD[7];     // EI_PAD.....
        uint16_t e_type;       // reloc, exec, shared, core?
        uint16_t e_machine;       // machine type.. should be arm in this case (0x28)
        uint32_t e_version;     // not sure?

        uint32_t e_entry;       // entrypoint
        uint32_t e_phoff;       // start of header table
        uint32_t e_shoff;       // start of section table

        uint32_t e_flags;       // architecture dependant flags
        uint16_t e_ehsize;      // size of header

        uint16_t e_phentsize;   // size of program header
        uint16_t e_phnum;       // program entry count

        uint16_t e_shentsize;   // section header size
        uint16_t e_shnum;       // section entry count
        uint16_t e_shstrndx;    // section name index
    };

    struct elf_header64 {
        uint8_t EI_MAG0[4];      // EI_MAG0 sig for elf files: 0x7f, 0x45, 0x4c, 0x46 (ELF)
        uint8_t EI_CLASS;        // 1 = 32 | 2 = 64
        uint8_t EI_DATA;            // 1 = little | 2 = big
        uint8_t EI_VERSION;         // should always be 1?
        uint8_t EI_OSABI;           // abi type.. i assume this will probably be 0x03?
        uint8_t EI_ABIVERSION;     // ignored if linux
        uint8_t EI_PAD[7];     // EI_PAD.....
        uint16_t e_type;       // reloc, exec, shared, core?
        uint16_t e_machine;       // machine type.. should be arm in this case (0x28)
        uint32_t e_version;     // not sure?

        uint64_t e_entry;       // entrypoint
        uint64_t e_phoff;       // start of header table
        uint64_t e_shoff;       // start of section table

        uint32_t e_flags;       // architecture dependant flags
        uint16_t e_ehsize;      // size of header

        uint16_t e_phentsize;   // size of program header
        uint16_t e_phnum;       // program entry count

        uint16_t e_shentsize;   // section header size
        uint16_t e_shnum;       // section entry count
        uint16_t e_shstrndx;    // section name index
    };

    struct elf_section_header32 {
        uint32_t name;      // offset to section name string
        uint32_t type;      // type of header
        uint32_t flags;     // ?
        uint32_t address;   // address of section in memory
        uint32_t offset;    // offset to section on disk
        uint32_t size;      // size of section on disk
        uint8_t padding[0x10];
    };
}