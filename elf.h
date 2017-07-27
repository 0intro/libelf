typedef struct Fhdr Fhdr;

/*
 * Portable ELF file header
 */
struct Fhdr {
	/* ELF Data */
	unsigned int (*get8)(void*, uint8_t*);
	unsigned int (*get16)(void*, uint16_t*);
	unsigned int (*get32)(void*, uint32_t*);
	unsigned int (*get64)(void*, uint64_t*);

	/* ELF Class */
	int (*readelfehdr)(FILE*, Fhdr*);
	int (*readelfshdr)(FILE*, Fhdr*);
	int (*readelfphdr)(FILE*, Fhdr*);
	int (*readelfstrndx)(FILE*, Fhdr*);

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
	uint32_t	strndxsize;	/* String Table size */
	uint8_t		*strndx;	/* Copy of String Table */
};

/* Read */
int readelf(FILE*, Fhdr*);
uint8_t* readelfsection(FILE*, char*, uint64_t*, Fhdr*);
void freeelf(Fhdr*);

/* Print */
void printelfhdr(Fhdr*);

/* String */
char* elfclass(uint8_t);
char* elfdata(uint8_t);
char* elfosabi(uint8_t);
char* elftype(uint16_t);
char* elfmachine(uint16_t);
char* elfversion(uint8_t);
