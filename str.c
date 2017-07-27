#include <stdint.h>

#include "dat.h"

static char* classstr[] = {
	[ELFCLASSNONE] = "Invalid class",
	[ELFCLASS32] = "32-bit objects",
	[ELFCLASS64] = "64-bit objects",
};

char*
elfclass(uint8_t class)
{
        if(class < nelem(classstr) && classstr[class])
                return classstr[class];

        return "Unknown class";
}

static char* datastr[] = {
	[ELFDATANONE] = "Invalid data encoding",
	[ELFDATA2LSB] = "Litte-endian",
	[ELFDATA2MSB] = "Big-endian",
};

char*
elfdata(uint8_t data)
{
        if(data < nelem(datastr) && datastr[data])
                return datastr[data];

        return "Unknown data";
}

static char* osabistr[] = {
	[ELFOSABI_NONE] = "No extensions or unspecified",
	[ELFOSABI_HPUX] = "Hewlett-Packard HP-UX",
	[ELFOSABI_NETBSD] = "NetBSD",
	[ELFOSABI_GNU] = "GNU ",
	[ELFOSABI_SOLARIS] = "Sun Solaris",
	[ELFOSABI_AIX] = "AIX",
	[ELFOSABI_IRIX] = "IRIX",
	[ELFOSABI_FREEBSD] = "FreeBSD",
	[ELFOSABI_TRU64] = "Compaq TRU64 UNIX",
	[ELFOSABI_MODESTO] = "Novell Modesto",
	[ELFOSABI_OPENBSD] = "Open BSD",
	[ELFOSABI_OPENVMS] = "Open VMS",
	[ELFOSABI_NSK] = "Hewlett-Packard Non-Stop Kernel",
	[ELFOSABI_AROS] = "Amiga Research OS",
	[ELFOSABI_FENIXOS] = "The FenixOS highly scalable multi-core OS",
	[ELFOSABI_CLOUDABI] = "Nuxi CloudABI",
	[ELFOSABI_OPENVOS] = "Stratus Technologies OpenVOS",
};

char*
elfosabi(uint8_t data)
{
        if(data < nelem(osabistr) && osabistr[data])
                return osabistr[data];

        return "Unknown osabi";
}

char *machinestr[] = {
	[EM_NONE] = "No machine",
	[EM_M32] = "AT&T WE 32100",
	[EM_SPARC] = "SPARC",
	[EM_386] = "Intel 80386",
	[EM_68K] = "Motorola 68000",
	[EM_88K] = "Motorola 88000",
	[EM_IAMCU] = "Intel MCU",
	[EM_860] = "Intel 80860",
	[EM_MIPS] = "MIPS I Architecture",
	[EM_S370] = "IBM System/370 Processor",
	[EM_MIPS_RS3_LE] = "MIPS RS3000 Little-endian",
	[EM_PARISC] = "Hewlett-Packard PA-RISC",
	[EM_VPP500] = "Fujitsu VPP500",
	[EM_SPARC32PLUS] = "Enhanced instruction set SPARC",
	[EM_960] = "Intel 80960",
	[EM_PPC] = "PowerPC",
	[EM_PPC64] = "64-bit PowerPC",
	[EM_S390] = "IBM System/390 Processor",
	[EM_SPU] = "IBM SPU/SPC",
	[EM_V800] = "NEC V800",
	[EM_FR20] = "Fujitsu FR20",
	[EM_RH32] = "TRW RH-32",
	[EM_RCE] = "Motorola RCE",
	[EM_ARM] = "ARM 32-bit architecture (AARCH32)",
	[EM_ALPHA] = "Digital Alpha",
	[EM_SH] = "Hitachi SH",
	[EM_SPARCV9] = "SPARC Version 9",
	[EM_TRICORE] = "Siemens TriCore embedded processor",
	[EM_ARC] = "Argonaut RISC Core, Argonaut Technologies Inc.",
	[EM_H8_300] = "Hitachi H8/300",
	[EM_H8_300H] = "Hitachi H8/300H",
	[EM_H8S] = "Hitachi H8S",
	[EM_H8_500] = "Hitachi H8/500",
	[EM_IA_64] = "Intel IA-64 processor architecture",
	[EM_MIPS_X] = "Stanford MIPS-X",
	[EM_COLDFIRE] = "Motorola ColdFire",
	[EM_68HC12] = "Motorola M68HC12",
	[EM_MMA] = "Fujitsu MMA Multimedia Accelerator",
	[EM_PCP] = "Siemens PCP",
	[EM_NCPU] = "Sony nCPU embedded RISC processor",
	[EM_NDR1] = "Denso NDR1 microprocessor",
	[EM_STARCORE] = "Motorola Star*Core processor",
	[EM_ME16] = "Toyota ME16 processor",
	[EM_ST100] = "STMicroelectronics ST100 processor",
	[EM_TINYJ] = "Advanced Logic Corp. TinyJ embedded processor family",
	[EM_X86_64] = "AMD x86-64 architecture",
	[EM_PDSP] = "Sony DSP Processor",
	[EM_PDP10] = "Digital Equipment Corp. PDP-10",
	[EM_PDP11] = "Digital Equipment Corp. PDP-11",
	[EM_FX66] = "Siemens FX66 microcontroller",
	[EM_ST9PLUS] = "STMicroelectronics ST9+ 8/16 bit microcontroller",
	[EM_ST7] = "STMicroelectronics ST7 8-bit microcontroller",
	[EM_68HC16] = "Motorola MC68HC16 Microcontroller",
	[EM_68HC11] = "Motorola MC68HC11 Microcontroller",
	[EM_68HC08] = "Motorola MC68HC08 Microcontroller",
	[EM_68HC05] = "Motorola MC68HC05 Microcontroller",
	[EM_SVX] = "Silicon Graphics SVx",
	[EM_ST19] = "STMicroelectronics ST19 8-bit microcontroller",
	[EM_VAX] = "Digital VAX",
	[EM_CRIS] = "Axis Communications 32-bit embedded processor",
	[EM_JAVELIN] = "Infineon Technologies 32-bit embedded processor",
	[EM_FIREPATH] = "Element 14 64-bit DSP Processor",
	[EM_ZSP] = "LSI Logic 16-bit DSP Processor",
	[EM_MMIX] = "Donald Knuth's educational 64-bit processor",
	[EM_HUANY] = "Harvard University machine-independent object files",
	[EM_PRISM] = "SiTera Prism",
	[EM_AVR] = "Atmel AVR 8-bit microcontroller",
	[EM_FR30] = "Fujitsu FR30",
	[EM_D10V] = "Mitsubishi D10V",
	[EM_D30V] = "Mitsubishi D30V",
	[EM_V850] = "NEC v850",
	[EM_M32R] = "Mitsubishi M32R",
	[EM_MN10300] = "Matsushita MN10300",
	[EM_MN10200] = "Matsushita MN10200",
	[EM_PJ] = "picoJava",
	[EM_OPENRISC] = "OpenRISC 32-bit embedded processor",
	[EM_ARC_COMPACT] = "ARC International ARCompact processor (old spelling/synonym: EM_ARC_A5)",
	[EM_XTENSA] = "Tensilica Xtensa Architecture",
	[EM_VIDEOCORE] = "Alphamosaic VideoCore processor",
	[EM_TMM_GPP] = "Thompson Multimedia General Purpose Processor",
	[EM_NS32K] = "National Semiconductor 32000 series",
	[EM_TPC] = "Tenor Network TPC processor",
	[EM_SNP1K] = "Trebia SNP 1000 processor",
	[EM_ST200] = "STMicroelectronics (www.st.com) ST200 microcontroller",
	[EM_IP2K] = "Ubicom IP2xxx microcontroller family",
	[EM_MAX] = "MAX Processor",
	[EM_CR] = "National Semiconductor CompactRISC microprocessor",
	[EM_F2MC16] = "Fujitsu F2MC16",
	[EM_MSP430] = "Texas Instruments embedded microcontroller msp430",
	[EM_BLACKFIN] = "Analog Devices Blackfin (DSP) processor",
	[EM_SE_C33] = "S1C33 Family of Seiko Epson processors",
	[EM_SEP] = "Sharp embedded microprocessor",
	[EM_ARCA] = "Arca RISC Microprocessor",
	[EM_UNICORE] = "Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University",
	[EM_EXCESS] = "eXcess: 16/32/64-bit configurable embedded CPU",
	[EM_DXP] = "Icera Semiconductor Inc. Deep Execution Processor",
	[EM_ALTERA_NIOS2] = "Altera Nios II soft-core processor",
	[EM_CRX] = "National Semiconductor CompactRISC CRX microprocessor",
	[EM_XGATE] = "Motorola XGATE embedded processor",
	[EM_C166] = "Infineon C16x/XC16x processor",
	[EM_M16C] = "Renesas M16C series microprocessors",
	[EM_DSPIC30F] = "Microchip Technology dsPIC30F Digital Signal Controller",
	[EM_CE] = "Freescale Communication Engine RISC core",
	[EM_M32C] = "Renesas M32C series microprocessors",
	[EM_TSK3000] = "Altium TSK3000 core",
	[EM_RS08] = "Freescale RS08 embedded processor",
	[EM_SHARC] = "Analog Devices SHARC family of 32-bit DSP processors",
	[EM_ECOG2] = "Cyan Technology eCOG2 microprocessor",
	[EM_SCORE7] = "Sunplus S+core7 RISC processor",
	[EM_DSP24] = "New Japan Radio (NJR) 24-bit DSP Processor",
	[EM_VIDEOCORE3] = "Broadcom VideoCore III processor",
	[EM_LATTICEMICO32] = "RISC processor for Lattice FPGA architecture",
	[EM_SE_C17] = "Seiko Epson C17 family",
	[EM_TI_C6000] = "The Texas Instruments TMS320C6000 DSP family",
	[EM_TI_C2000] = "The Texas Instruments TMS320C2000 DSP family",
	[EM_TI_C5500] = "The Texas Instruments TMS320C55x DSP family",
	[EM_TI_ARP32] = "Texas Instruments Application Specific RISC Processor, 32bit fetch",
	[EM_TI_PRU] = "Texas Instruments Programmable Realtime Unit",
	[EM_MMDSP_PLUS] = "STMicroelectronics 64bit VLIW Data Signal Processor",
	[EM_CYPRESS_M8C] = "Cypress M8C microprocessor",
	[EM_R32C] = "Renesas R32C series microprocessors",
	[EM_TRIMEDIA] = "NXP Semiconductors TriMedia architecture family",
	[EM_QDSP6] = "QUALCOMM DSP6 Processor",
	[EM_8051] = "Intel 8051 and variants",
	[EM_STXP7X] = "STMicroelectronics STxP7x family of configurable and extensible RISC processors",
	[EM_NDS32] = "Andes Technology compact code size embedded RISC processor family",
	[EM_ECOG1X] = "Cyan Technology eCOG1X family",
	[EM_MAXQ30] = "Dallas Semiconductor MAXQ30 Core Micro-controllers",
	[EM_XIMO16] = "New Japan Radio (NJR) 16-bit DSP Processor",
	[EM_MANIK] = "M2000 Reconfigurable RISC Microprocessor",
	[EM_CRAYNV2] = "Cray Inc. NV2 vector architecture",
	[EM_RX] = "Renesas RX family",
	[EM_METAG] = "Imagination Technologies META processor architecture",
	[EM_MCST_ELBRUS] = "MCST Elbrus general purpose hardware architecture",
	[EM_ECOG16] = "Cyan Technology eCOG16 family",
	[EM_CR16] = "National Semiconductor CompactRISC CR16 16-bit microprocessor",
	[EM_ETPU] = "Freescale Extended Time Processing Unit",
	[EM_SLE9X] = "Infineon Technologies SLE9X core",
	[EM_L10M] = "Intel L10M",
	[EM_K10M] = "Intel K10M",
	[EM_AARCH64] = "ARM 64-bit architecture (AARCH64)",
	[EM_AVR32] = "Atmel Corporation 32-bit microprocessor family",
	[EM_STM8] = "STMicroeletronics STM8 8-bit microcontroller",
	[EM_TILE64] = "Tilera TILE64 multicore architecture family",
	[EM_TILEPRO] = "Tilera TILEPro multicore architecture family",
	[EM_MICROBLAZE] = "Xilinx MicroBlaze 32-bit RISC soft processor core",
	[EM_CUDA] = "NVIDIA CUDA architecture",
	[EM_TILEGX] = "Tilera TILE-Gx multicore architecture family",
	[EM_CLOUDSHIELD] = "CloudShield architecture family",
	[EM_COREA_1ST] = "KIPO-KAIST Core-A 1st generation processor family",
	[EM_COREA_2ND] = "KIPO-KAIST Core-A 2nd generation processor family",
	[EM_ARC_COMPACT2] = "Synopsys ARCompact V2",
	[EM_OPEN8] = "Open8 8-bit RISC soft processor core",
	[EM_RL78] = "Renesas RL78 family",
	[EM_VIDEOCORE5] = "Broadcom VideoCore V processor",
	[EM_78KOR] = "Renesas 78KOR family",
	[EM_56800EX] = "Freescale 56800EX Digital Signal Controller (DSC)",
	[EM_BA1] = "Beyond BA1 CPU architecture",
	[EM_BA2] = "Beyond BA2 CPU architecture",
	[EM_XCORE] = "XMOS xCORE processor family",
	[EM_MCHP_PIC] = "Microchip 8-bit PIC(r) family",
	[EM_INTEL205] = "Reserved by Intel",
	[EM_INTEL206] = "Reserved by Intel",
	[EM_INTEL207] = "Reserved by Intel",
	[EM_INTEL208] = "Reserved by Intel",
	[EM_INTEL209] = "Reserved by Intel",
	[EM_KM32] = "KM211 KM32 32-bit processor",
	[EM_KMX32] = "KM211 KMX32 32-bit processor",
	[EM_KMX16] = "KM211 KMX16 16-bit processor",
	[EM_KMX8] = "KM211 KMX8 8-bit processor",
	[EM_KVARC] = "KM211 KVARC processor",
	[EM_CDP] = "Paneve CDP architecture family",
	[EM_COGE] = "Cognitive Smart Memory Processor",
	[EM_COOL] = "Bluechip Systems CoolEngine",
	[EM_NORC] = "Nanoradio Optimized RISC",
	[EM_CSR_KALIMBA] = "CSR Kalimba architecture family",
	[EM_Z80] = "Zilog Z80",
	[EM_VISIUM] = "Controls and Data Services VISIUMcore processor",
	[EM_FT32] = "FTDI Chip FT32 high performance 32-bit RISC architecture",
	[EM_MOXIE] = "Moxie processor family",
	[EM_AMDGPU] = "AMD GPU architecture",
	[EM_RISCV] = "RISC-V"
};

char *typestr[] = {
	[ET_NONE] = "No file type",
	[ET_REL] = "Relocatable file",
	[ET_EXEC] = "Executable file",
	[ET_DYN] = "Shared object file",
	[ET_CORE] = "Core file",
};

char*
elftype(uint16_t type)
{
        if(type < nelem(typestr) && typestr[type])
                return typestr[type];

	if (type >= ET_LOOS && type <= ET_HIOS)
		return "Operating system-specific";

	if (type >= ET_LOPROC)
		return "Processor-specific";

        return "Unknown type";
}

char*
elfmachine(uint16_t machine)
{
        if(machine < nelem(machinestr) && machinestr[machine])
                return machinestr[machine];

        return "Unknown machine";
}

char *versionstr[] = {
	[EV_NONE] = "Invalid",
	[EV_CURRENT] = "Current",
};

char*
elfversion(uint8_t version)
{
        if(version < nelem(versionstr) && versionstr[version])
                return versionstr[version];

        return "Unknown version";
}
