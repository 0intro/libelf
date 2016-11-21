/*
 * print.c
 */
void printelf32ehdr(Elf32_Ehdr*, Fhdr*);
void printelf64ehdr(Elf64_Ehdr*, Fhdr*);
void printelf32shdr(Elf32_Shdr*, Fhdr*);
void printelf64shdr(Elf64_Shdr*, Fhdr*);
void printelf32phdr(Elf32_Phdr*, Fhdr*);
void printelf64phdr(Elf64_Phdr*, Fhdr*);

char* getstr(Fhdr*, uint32_t);
