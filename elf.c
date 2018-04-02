#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "bele.h"
#include "elf.h"
#include "dat.h"
#include "fns.h"

static int verbose;

typedef struct Data Data;
typedef struct Class Class;

struct Data {
	int type;
	char *name;
	unsigned int (*get8)(void*, uint8_t*);
	unsigned int (*get16)(void*, uint16_t*);
	unsigned int (*get32)(void*, uint32_t*);
	unsigned int (*get64)(void*, uint64_t*);
};

struct Class {
	int type;
	char *name;
	int ehsize;
	int shentsize;
	int phentsize;
	int (*readelfehdr)(FILE*, Fhdr*);
	int (*readelfshdr)(FILE*, Fhdr*);
	int (*readelfphdr)(FILE*, Fhdr*);
	int (*readelfstrndx)(FILE*, Fhdr*);
};

static int readelf32ehdr(FILE*, Fhdr*);
static int readelf32shdr(FILE*, Fhdr*);
static int readelf32phdr(FILE*, Fhdr*);
static int readelf32strndx(FILE*, Fhdr*);

static int readelf64ehdr(FILE*, Fhdr*);
static int readelf64shdr(FILE*, Fhdr*);
static int readelf64phdr(FILE*, Fhdr*);
static int readelf64strndx(FILE*, Fhdr*);

static Data data[] = {
	{
		ELFDATANONE,
		"invalid",
		NULL,
		NULL,
		NULL,
		NULL
	},
	{
		ELFDATA2LSB,
		"little-endian",
		le8get,
		le16get,
		le32get,
		le64get
	},
	{
		ELFDATA2MSB,
		"big-endian",
		be8get,
		be16get,
		be32get,
		be64get
	}
};

static Class class[] = {
	{
		ELFCLASSNONE,
		"invalid",
		0,
		0,
		0,
		NULL,
		NULL,
		NULL,
		NULL,
	},
	{
		ELFCLASS32,
		"32-bit",
		sizeof(Elf32_Ehdr),
		sizeof(Elf32_Shdr),
		sizeof(Elf32_Phdr),
		readelf32ehdr,
		readelf32shdr,
		readelf32phdr,
		readelf32strndx,
	},
	{
		ELFCLASS64,
		"64-bit",
		sizeof(Elf64_Ehdr),
		sizeof(Elf64_Shdr),
		sizeof(Elf64_Phdr),
		readelf64ehdr,
		readelf64shdr,
		readelf64phdr,
		readelf64strndx,
	}
};

/*
 * Read ELF32 Header
 */
static int
readelf32ehdr(FILE *f, Fhdr *fp)
{
	uint8_t buf[Eh32sz];
	Elf32_Ehdr e;
	uint8_t *p;

	p = buf;

	if (fseek(f, 0, SEEK_SET) < 0)
		return -1;

	if (fread(p, fp->ehsize, 1, f) != 1)
		return -1;

	memmove(&e.ident, p, sizeof(e.ident));
	p += sizeof(e.ident);
	p += fp->get16(p, &e.type);
	p += fp->get16(p, &e.machine);
	p += fp->get32(p, &e.version);
	p += fp->get32(p, &e.entry);
	p += fp->get32(p, &e.phoff);
	p += fp->get32(p, &e.shoff);
	p += fp->get32(p, &e.flags);
	p += fp->get16(p, &e.ehsize);
	p += fp->get16(p, &e.phentsize);
	p += fp->get16(p, &e.phnum);
	p += fp->get16(p, &e.shentsize);
	p += fp->get16(p, &e.shnum);
	p += fp->get16(p, &e.shstrndx);

	if (verbose)
		printelf32ehdr(&e, fp);

	if (e.type != ET_REL && e.type != ET_EXEC && e.type != ET_DYN && e.type != ET_CORE) {
		fprintf(stderr, "unsupported file type %d\n", e.type);
		return -1;
	}

	if (fp->ehsize != e.ehsize) {
		fprintf(stderr, "ehsize mismatch; want %u; got %u\n", fp->ehsize, e.ehsize);
		return -1;
	}

	if (fp->shentsize != e.shentsize) {
		fprintf(stderr, "shentsize mismatch; want %u; got %u\n", fp->ehsize, e.ehsize);
		return -1;
	}

	if (fp->phentsize != e.phentsize) {
		fprintf(stderr, "phentsize mismatch; want %u; got %u\n", fp->ehsize, e.ehsize);
		return -1;
	}

	fp->type = e.type;
	fp->machine = e.machine;
	fp->version = e.version;
	fp->entry = e.entry;

	fp->shoff = e.shoff;
	fp->phoff = e.phoff;
	fp->phnum = e.phnum;
	fp->shnum = e.shnum;
	fp->shstrndx = e.shstrndx;

	return (int)(p - buf);
}

/*
 * Read ELF64 Header
 */
static int
readelf64ehdr(FILE *f, Fhdr *fp)
{
	uint8_t buf[Eh64sz];
	Elf64_Ehdr e;
	uint8_t *p;

	p = buf;

	if (fseek(f, 0, SEEK_SET) < 0)
		return -1;

	if (fread(p, fp->ehsize , 1, f) != 1)
		return -1;

	memmove(&e.ident, p, sizeof(e.ident));
	p += sizeof(e.ident);
	p += fp->get16(p, &e.type);
	p += fp->get16(p, &e.machine);
	p += fp->get32(p, &e.version);
	p += fp->get64(p, &e.entry);
	p += fp->get64(p, &e.phoff);
	p += fp->get64(p, &e.shoff);
	p += fp->get32(p, &e.flags);
	p += fp->get16(p, &e.ehsize);
	p += fp->get16(p, &e.phentsize);
	p += fp->get16(p, &e.phnum);
	p += fp->get16(p, &e.shentsize);
	p += fp->get16(p, &e.shnum);
	p += fp->get16(p, &e.shstrndx);

	if (verbose)
		printelf64ehdr(&e, fp);

	if (e.type != ET_REL && e.type != ET_EXEC && e.type != ET_DYN && e.type != ET_CORE) {
		fprintf(stderr, "unsupported file type %d\n", e.type);
		return -1;
	}

	if (fp->ehsize != e.ehsize) {
		fprintf(stderr, "ehsize mismatch; want %u; got %u\n", fp->ehsize, e.ehsize);
		return -1;
	}

	if (fp->shentsize != e.shentsize) {
		fprintf(stderr, "shentsize mismatch; want %u; got %u\n", fp->ehsize, e.ehsize);
		return -1;
	}

	if (fp->phentsize != e.phentsize) {
		fprintf(stderr, "phentsize mismatch; want %u; got %u\n", fp->ehsize, e.ehsize);
		return -1;
	}

	fp->type = e.type;
	fp->machine = e.machine;
	fp->version = e.version;
	fp->entry = e.entry;

	fp->shoff = e.shoff;
	fp->phoff = e.phoff;
	fp->phnum = e.phnum;
	fp->shnum = e.shnum;
	fp->shstrndx = e.shstrndx;

	return (int)(p - buf);
}

/*
 * Unpack ELF32 Section Header
 */
int
unpackelf32shdr(uint8_t *buf, int len, Elf32_Shdr *sh, Fhdr *fp)
{
	uint8_t *p;

	if (len < Sh32sz)
		return -1;

	p = buf;

	p += fp->get32(p, &sh->name);
	p += fp->get32(p, &sh->type);
	p += fp->get32(p, &sh->flags);
	p += fp->get32(p, &sh->addr);
	p += fp->get32(p, &sh->offset);
	p += fp->get32(p, &sh->size);
	p += fp->get32(p, &sh->link);
	p += fp->get32(p, &sh->info);
	p += fp->get32(p, &sh->addralign);
	p += fp->get32(p, &sh->entsize);

	return p - buf;
}

/*
 * Read ELF32 Section Header
 */
static int
readelf32shdr(FILE *f, Fhdr *fp)
{
	uint8_t buf[Sh32sz];
	Elf32_Shdr sh;

	if (fread(buf, fp->shentsize, 1, f) != 1)
		return -1;

	if (unpackelf32shdr(buf, sizeof(buf), &sh, fp) < 0)
		return -1;

	fp->name = sh.name;
	fp->offset = sh.offset;
	fp->size = sh.size;

	if (verbose)
		printelf32shdr(&sh, fp);

	return 0;
}

/*
 * Unpack ELF32 Program Header
 */
int
unpackelf32phdr(uint8_t *buf, int len, Elf32_Phdr *ph, Fhdr *fp)
{
	uint8_t *p;

	if (len < Ph32sz)
		return -1;

	p = buf;

	p += fp->get32(p, &ph->type);
	p += fp->get32(p, &ph->offset);
	p += fp->get32(p, &ph->vaddr);
	p += fp->get32(p, &ph->paddr);
	p += fp->get32(p, &ph->filesz);
	p += fp->get32(p, &ph->memsz);
	p += fp->get32(p, &ph->flags);
	p += fp->get32(p, &ph->align);

	return p - buf;
}

/*
 * Read ELF32 Program Header
 */
static int
readelf32phdr(FILE *f, Fhdr *fp)
{
	uint8_t buf[Ph32sz];
	Elf32_Phdr ph;

	if (fread(buf, fp->phentsize, 1, f) != 1)
		return -1;

	if (unpackelf32phdr(buf, sizeof(buf), &ph, fp) < 0)
		return -1;

	if (verbose)
		printelf32phdr(&ph, fp);

	return 0;
}

/*
 * Unpack ELF64 Section Header
 */
int
unpackelf64shdr(uint8_t *buf, int len, Elf64_Shdr *sh, Fhdr *fp)
{
	uint8_t *p;

	if (len < Sh64sz)
		return -1;

	p = buf;

	p += fp->get32(p, &sh->name);
	p += fp->get32(p, &sh->type);
	p += fp->get64(p, &sh->flags);
	p += fp->get64(p, &sh->addr);
	p += fp->get64(p, &sh->offset);
	p += fp->get64(p, &sh->size);
	p += fp->get32(p, &sh->link);
	p += fp->get32(p, &sh->info);
	p += fp->get64(p, &sh->addralign);
	p += fp->get64(p, &sh->entsize);

	return p - buf;
}

/*
 * Read ELF64 Section Header
 */
static int
readelf64shdr(FILE *f, Fhdr *fp)
{
	uint8_t buf[Sh64sz];
	Elf64_Shdr sh;

	if (fread(buf, fp->shentsize, 1, f) != 1)
		return -1;

	if (unpackelf64shdr(buf, sizeof(buf), &sh, fp) < 0)
		return -1;

	fp->name = sh.name;
	fp->offset = sh.offset;
	fp->size = sh.size;

	if (verbose)
		printelf64shdr(&sh, fp);

	return 0;
}

/*
 * Unpack ELF64 Program Header
 */
int
unpackelf64phdr(uint8_t *buf, int len, Elf64_Phdr *ph, Fhdr *fp)
{
	uint8_t *p;

	if (len < Ph64sz)
		return -1;

	p = buf;

	p += fp->get32(p, &ph->type);
	p += fp->get32(p, &ph->flags);
	p += fp->get64(p, &ph->offset);
	p += fp->get64(p, &ph->vaddr);
	p += fp->get64(p, &ph->paddr);
	p += fp->get64(p, &ph->filesz);
	p += fp->get64(p, &ph->memsz);
	p += fp->get64(p, &ph->align);

	return p - buf;
}

/*
 * Read ELF64 Program Header
 */
static int
readelf64phdr(FILE *f, Fhdr *fp)
{
	uint8_t buf[Ph64sz];
	Elf64_Phdr ph;

	if (fread(buf, fp->phentsize, 1, f) != 1)
		return -1;

	if (unpackelf64phdr(buf, sizeof(buf), &ph, fp) < 0)
		return -1;

	if (verbose)
		printelf64phdr(&ph, fp);

	return 0;
}

/*
 * Read ELF ident
 */
int
readident(FILE *f, Fhdr *fp)
{
	uint8_t buf[EI_NIDENT];
	unsigned int i;
	uint8_t *p;

	if (fseek(f, 0, SEEK_SET) < 0)
		return -1;

	p = buf;
	if (fread(p, EI_NIDENT, 1, f) != 1)
		return -1;

	p += EI_NIDENT;

	if (buf[EI_MAG0] != ELFMAG0)
		return -1;
	if (buf[EI_MAG1] != ELFMAG1)
		return -1;
	if (buf[EI_MAG2] != ELFMAG2)
		return -1;
	if (buf[EI_MAG3] != ELFMAG3)
		return -1;

	if(buf[EI_VERSION] != EV_CURRENT) {
		fprintf(stderr, "unsupported file version %d\n", buf[EI_VERSION]);
		return -1;
	}

	for (i = 0; i < nelem(class); i++) {
		if (buf[EI_CLASS] != class[i].type)
			continue;
		if (class[i].readelfehdr == NULL)
			return -1;
		fp->readelfehdr = class[i].readelfehdr;
		fp->readelfshdr = class[i].readelfshdr;
		fp->readelfphdr = class[i].readelfphdr;
		fp->readelfstrndx = class[i].readelfstrndx;
		fp->ehsize = class[i].ehsize;
		fp->shentsize = class[i].shentsize;
		fp->phentsize = class[i].phentsize;
		break;
	}

	if (i == nelem(class))
		return -1;

	for (i = 0; i < nelem(data); i++) {
		if (buf[EI_DATA] != data[i].type)
			continue;
		if (data[i].get8 == NULL)
			return -1;
		fp->get8 = data[i].get8;
		fp->get16 = data[i].get16;
		fp->get32 = data[i].get32;
		fp->get64 = data[i].get64;
		break;
	}

	if (i == nelem(data))
		return -1;

	fp->class = buf[EI_CLASS];
	fp->data = buf[EI_DATA];
	fp->elfversion = buf[EI_VERSION];
	fp->osabi = buf[EI_OSABI];
	fp->abiversion = buf[EI_ABIVERSION];

	return (int)(p - buf);
}

/*
 * Read ELF Section Headers
 */
int
readelfshdrs(FILE *f, Fhdr *fp)
{
	unsigned int i;

	if (fseek(f, fp->shoff, SEEK_SET) < 0)
		return -1;

	for (i = 0; i < fp->shnum; i++) {
		if (fp->readelfshdr(f, fp) < 0)
			return -1;
	}

	return 0;
}

/*
 * Read ELF Program Headers
 */
int
readelfphdrs(FILE *f, Fhdr *fp)
{
	unsigned int i;

	if (fseek(f, fp->phoff, SEEK_SET) < 0)
		return -1;

	for (i = 0; i < fp->phnum; i++) {
		if (fp->readelfphdr(f, fp) < 0)
			return -1;
	}

	return 0;
}

/*
 * Read ELF32 String Table
 */
static int
readelf32strndx(FILE *f, Fhdr *fp)
{
	uint8_t buf[Sh32sz];
	Elf32_Shdr sh;

	if (fseek(f, fp->shoff + (uint64_t)(fp->shstrndx * fp->shentsize), SEEK_SET) < 0)
		return -1;

	if (fread(buf, fp->shentsize, 1, f) != 1)
		return -1;

	if (unpackelf32shdr(buf, sizeof(buf), &sh, fp) < 0)
		return -1;

	fp->offset = sh.offset;
	fp->strndxsize = sh.size;

	return 0;
}

/*
 * Read ELF64 String Table
 */
static int
readelf64strndx(FILE *f, Fhdr *fp)
{
	uint8_t buf[Sh64sz];
	Elf64_Shdr sh;

	if (fseek(f, fp->shoff + (uint64_t)(fp->shstrndx * fp->shentsize), SEEK_SET) < 0)
		return -1;

	if (fread(buf, fp->shentsize, 1, f) != 1)
		return -1;

	if (unpackelf64shdr(buf, sizeof(buf), &sh, fp) < 0)
		return -1;

	fp->offset = sh.offset;
	fp->strndxsize = sh.size;

	return 0;
}

static uint8_t*
newsection(FILE *f, uint64_t offset, uint64_t size)
{
	uint8_t *sect;

	sect = malloc(size);
	if (sect == NULL)
		return NULL;

	if (fseek(f, offset, SEEK_SET) < 0) {
		free(sect);
		return NULL;
	}

	if (fread(sect, size, 1, f) != 1) {
		free(sect);
		return NULL;
	}

	return sect;
}

/*
 * Read ELF String Table
 */
static int
readelfstrndx(FILE *f, Fhdr *fp)
{
	if (fp->shstrndx == SHN_UNDEF) {
		fprintf(stderr, "missing string table\n");
		return -1;
	}

	if (fp->readelfstrndx(f, fp) < 0)
		return -1;

	fp->strndx = newsection(f, fp->offset, fp->strndxsize);
	if (fp->strndx == NULL)
		return -1;

	return 0;
}

/*
 * Get string from index in String Table
 */
char* getstr(Fhdr *fp, uint32_t i)
{
	if (fp->strndx == NULL)
		return NULL;

	if (i >= fp->strndxsize)
		return NULL;

	return (char*)&fp->strndx[i];
}

/*
 * Read ELF Section Headers
 */
uint8_t*
readelfsect(FILE *f, char *name, Fhdr *fp)
{
	unsigned int i;
	char *n;

	if (fseek(f, fp->shoff, SEEK_SET) < 0)
		return NULL;

	for (i = 0; i < fp->shnum; i++) {
		if (fp->readelfshdr(f, fp) < 0)
			return NULL;
		n = getstr(fp, fp->name);
		if (n == NULL)
			return NULL;
		if (strcmp(n, name) == 0)
			return newsection(f, fp->offset, fp->size);
	}

	fprintf(stderr, "section %s not found\n", name);

	return NULL;
}

/*
 * Read ELF File
 */
int
readelf(FILE *f, Fhdr *fp)
{
	memset(fp, 0, sizeof(*fp));

	if (readident(f, fp) < 0)
		return -1;

	if (fp->readelfehdr(f, fp) < 0)
		return -1;

	if (readelfstrndx(f, fp) < 0)
		return -1;

	if (readelfshdrs(f, fp) < 0)
		return -1;

	if (readelfphdrs(f, fp) < 0)
		return -1;

	return 0;
}

/*
 * Read ELF Section
 */
uint8_t*
readelfsection(FILE *f, char *name, uint64_t *size, Fhdr *fp)
{
	uint8_t *sect;

	memset(fp, 0, sizeof(*fp));

	if (readident(f, fp) < 0)
		return NULL;

	if (fp->readelfehdr(f, fp) < 0)
		return NULL;

	if (readelfstrndx(f, fp) < 0)
		return NULL;

	sect = readelfsect(f, name, fp);
	if (sect == NULL)
		return NULL;

	*size = fp->size;

	return sect;
}


void
freeelf(Fhdr *fp)
{
	if (fp->strndx != NULL)
		free(fp->strndx);
}
