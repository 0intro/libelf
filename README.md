[![Build Status](https://travis-ci.org/0intro/libelf.svg?branch=master)](https://travis-ci.org/0intro/libelf)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/0intro-libelf/badge.svg)](https://scan.coverity.com/projects/0intro-libelf)

libelf
======

Libelf is a simple library which provides functions to read ELF files.

Headers
-------

```
#include <stdint.h>
#include <elf.h>
```

Structures
----------

```
typedef struct Fhdr Fhdr;

/*
 * Portable ELF file header
 */
struct Fhdr {
	/* Private */
	...

	/* ELF Identification */
	uint8_t		class;		/* File class */
	uint8_t		data;		/* Data encoding */
	uint8_t		elfversion;	/* File version */
	uint8_t		osabi;		/* Operating system/ABI identification */
	uint8_t		abiversion;	/* ABI version */

	/* ELF Header */
	uint16_t	type;
	uint16_t	machine;
	uint32_t	version;
	uint64_t	entry;
	uint64_t	phoff;
	uint64_t	shoff;
	uint16_t	ehsize;		/* ELF Header size */
	uint16_t	phentsize;	/* Section Header size */
	uint16_t	phnum;
	uint16_t	shentsize;	/* Program Header size */
	uint16_t	shnum;
	uint16_t	shstrndx;

	/* Section Header */
	uint32_t	name;
	uint64_t	offset;
	uint64_t	size;

	/* String Table */
	uint32_t	strndxsize;	/* String Table Size */
	uint8_t		*strndx;	/* Copy of String Table */
};
```

Functions
---------

```
/* Read */
int readelf(FILE *f, Fhdr *fp);
uint8_t* readelfsection(FILE *f, char *name, uint64_t *size, Fhdr *fp);
void freeelf(Fhdr *fp);

/* Print */
void printelfhdr(Fhdr *fp);

/* String */
char* elfclass(uint8_t class);
char* elfdata(uint8_t data);
char* elfosabi(uint8_t osabi);
char* elftype(uint16_t type);
char* elfmachine(uint16_t machine);
char* elfversion(uint8_t version);
```

Example
-------

```
Fhdr fhdr;
FILE *f;
uint8_t *buf;
uint64_t len;

f = fopen("/bin/ls", "rb");
if (f == NULL)
	return -1;

buf = readelfsection(f, ".text", &len, &fhdr);
if (buf == NULL)
	return -1;

// ...

freeelf(&fhdr);
```
