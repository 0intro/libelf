#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "elf.h"
#include "dat.h"
#include "fns.h"

void
printelf32ehdr(Elf32_Ehdr *e, Fhdr *fp)
{
	USED(fp);
	printf("ident %.2x %c %c %c %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n",
		e->ident[0], e->ident[1], e->ident[2], e->ident[3], e->ident[4], e->ident[5], e->ident[6], e->ident[7],
		e->ident[8], e->ident[9], e->ident[10], e->ident[11], e->ident[12], e->ident[13], e->ident[14], e->ident[15]);
	printf("type %u\n", e->type);
	if (machines[e->machine] != NULL)
		printf("machine %s (0x%.4x)\n", machines[e->machine], e->machine);
	else
		printf("machine 0x%.4x\n", e->machine);
	printf("version %u\n", e->version);
	printf("entry 0x%.8x\n", e->entry);
	printf("phoff %u\n", e->phoff);
	printf("shoff %u\n", e->shoff);
	printf("flags 0x%.8x\n", e->flags);
	printf("ehsize %u\n", e->ehsize);
	printf("phentsize %u\n", e->phentsize);
	printf("phnum %u\n", e->phnum);
	printf("shentsize %u\n", e->shentsize);
	printf("shnum %u\n", e->shnum);
	printf("shstrndx %u\n", e->shstrndx);
	printf("\n");
}

void
printelf64ehdr(Elf64_Ehdr *e, Fhdr *fp)
{
	USED(fp);
	printf("ident %.2x %c %c %c %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n",
		e->ident[0], e->ident[1], e->ident[2], e->ident[3], e->ident[4], e->ident[5], e->ident[6], e->ident[7],
		e->ident[8], e->ident[9], e->ident[10], e->ident[11], e->ident[12], e->ident[13], e->ident[14], e->ident[15]);
	printf("type %u\n", e->type);
	if (machines[e->machine] != NULL)
		printf("machine %s (0x%.4x)\n", machines[e->machine], e->machine);
	else
		printf("machine 0x%.4x\n", e->machine);
	printf("version %u\n", e->version);
	printf("entry 0x%.16" PRIx64 "\n", e->entry);
	printf("phoff %" PRIu64 "\n", e->phoff);
	printf("shoff %" PRIu64 "\n", e->shoff);
	printf("flags 0x%.8x\n", e->flags);
	printf("ehsize %u\n", e->ehsize);
	printf("phentsize %u\n", e->phentsize);
	printf("phnum %u\n", e->phnum);
	printf("shentsize %u\n", e->shentsize);
	printf("shnum %u\n", e->shnum);
	printf("shstrndx %u\n", e->shstrndx);
	printf("\n");
}

void
printelf32shdr(Elf32_Shdr *sh, Fhdr *fp)
{
	printf("section header\n");
	printf("name %s (%u)\n", getstr(fp, sh->name), sh->name);
	printf("type %u\n", sh->type);
	printf("flags 0x%.8x\n", sh->flags);
	printf("addr 0x%.8x\n", sh->addr);
	printf("offset 0x%.8x\n", sh->offset);
	printf("size %u\n", sh->size);
	printf("link %u\n", sh->link);
	printf("info %u\n", sh->info);
	printf("addralign 0x%.8x\n", sh->addralign);
	printf("entsize %u\n", sh->entsize);
	printf("\n");
}

void
printelf32phdr(Elf32_Phdr *ph, Fhdr *fp)
{
	USED(fp);
	printf("program header\n");
	printf("type %u\n", ph->type);
	printf("offset 0x%.8x\n", ph->offset);
	printf("vaddr 0x%.8x\n", ph->vaddr);
	printf("paddr 0x%.8x\n", ph->paddr);
	printf("filesz %u\n", ph->filesz);
	printf("memsz %u\n", ph->memsz);
	printf("flags 0x%.8x\n", ph->flags);
	printf("align 0x%.8x\n", ph->align);
	printf("\n");
}

void
printelf64shdr(Elf64_Shdr *sh, Fhdr *fp)
{
	printf("section header\n");
	printf("name %s (%u)\n", getstr(fp, sh->name), sh->name);
	printf("type %u\n", sh->type);
	printf("flags 0x%.16" PRIx64 "\n", sh->flags);
	printf("addr 0x%.16" PRIx64 "\n", sh->addr);
	printf("offset 0x%.16" PRIx64 "\n", sh->offset);
	printf("size %" PRIu64 "\n", sh->size);
	printf("link %u\n", sh->link);
	printf("info %u\n", sh->info);
	printf("addralign 0x%.16" PRIx64 "\n", sh->addralign);
	printf("entsize %" PRIu64 "\n", sh->entsize);
	printf("\n");
}

void
printelf64phdr(Elf64_Phdr *ph, Fhdr *fp)
{
	USED(fp);
	printf("program header\n");
	printf("type %u\n", ph->type);
	printf("flags 0x%.8x\n", ph->flags);
	printf("offset 0x%.16" PRIx64 "\n", ph->offset);
	printf("vaddr 0x%.16" PRIx64 "\n", ph->vaddr);
	printf("paddr 0x%.16" PRIx64 "\n", ph->paddr);
	printf("filesz %" PRIu64 "\n", ph->filesz);
	printf("memsz %" PRIu64 "\n", ph->memsz);
	printf("align 0x%.16" PRIx64 "\n", ph->align);
	printf("\n");
}
