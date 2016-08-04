/*  This file is part of The Firekylin Operating System.
 *
 *  Copyright 2016 Liuxiaofeng
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _ELF_H
#define _ELF_H

typedef unsigned int    Elf32_Addr ;
typedef unsigned short  Elf32_Half ;
typedef unsigned int    Elf32_Off  ;
typedef signed   int    Elf32_Sword;
typedef unsigned int    Elf32_Word ;

#define EI_NIDENT	16
typedef struct {
	unsigned char e_ident[EI_NIDENT];
	Elf32_Half    e_type;
	Elf32_Half    e_machine;
	Elf32_Word    e_version;
	Elf32_Addr    e_entry;
	Elf32_Off     e_phoff;
	Elf32_Off     e_shoff;
	Elf32_Word    e_flags;
	Elf32_Half    e_ehsize;
	Elf32_Half    e_phentsize;
	Elf32_Half    e_phnum;
	Elf32_Half    e_shentsize;
	Elf32_Half    e_shnum;
	Elf32_Half    e_shstrndx;
} Elf32_Ehdr ;

/* Values of e_type */
#define ET_REL   1
#define ET_EXEC  2
#define ET_DYN   3

/* Values of e_machine */
#define EM_M32   1   /* AT&T WE 32100 */
#define EM_SPARC 2   /* SPARC */
#define EM_386   3   /* Intel x86 */
#define EM_68K   4   /* Motorola 68000 */
#define EM_88K   5   /* Motorola 88000 */
#define EM_860   6   /* Intel 80860 */

typedef struct {
	Elf32_Word  p_type;
	Elf32_Off   p_offset;
	Elf32_Addr  p_vaddr;
	Elf32_Addr  p_paddr;
	Elf32_Word  p_filesz;
	Elf32_Word  p_memsz;
	Elf32_Word  p_flags;
	Elf32_Word  p_align;
} Elf32_Phdr;

typedef struct {
	Elf32_Word  sh_name;
	Elf32_Word  sh_type;
	Elf32_Word  sh_flags;
	Elf32_Word  sh_addr;
	Elf32_Word  sh_offset;
	Elf32_Word  sh_size;
	Elf32_Word  sh_link;
	Elf32_Word  sh_info;
	Elf32_Word  sh_addralign;
	Elf32_Word  sh_entsize;
} Elf32_Shdr ;

/* Values of sh_type */
#define SHT_NULL       0
#define SHT_PROGBITS   1
#define SHT_SYMTAB     2
#define SHT_STRTAB     3
#define SHT_RELA       4
#define SHT_HASH       5
#define SHT_SYNAMIC    6
#define SHT_NOTE       7
#define SHT_NOBITS     8
#define SHT_REL        9
#define SHT_SHLIB      10
#define SHT_DNYSYM     11

/* Values of sh_flags */
#define SHF_WRITE      1
#define SHF_ALLOC      2
#define SHF_EXECINSTR  4

#endif
