/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architectures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:50:46 by rkirszba          #+#    #+#             */
/*   Updated: 2021/01/19 20:02:40 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_arch	g_archs[] = {
    { "any",	CPU_TYPE_ANY,	  CPU_SUBTYPE_MULTIPLE },
    { "little",	CPU_TYPE_ANY,	  CPU_SUBTYPE_LITTLE_ENDIAN },
    { "big",	CPU_TYPE_ANY,	  CPU_SUBTYPE_BIG_ENDIAN },
    { "ppc64",     CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_ALL },
    { "x86_64",    CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL },
    { "x86_64h",   CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_H },
    { "arm64",     CPU_TYPE_ARM64,     CPU_SUBTYPE_ARM64_ALL },
    { "ppc970-64", CPU_TYPE_POWERPC64, CPU_SUBTYPE_POWERPC_970 },
    { "ppc",    CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_ALL },
    { "i386",   CPU_TYPE_I386,    CPU_SUBTYPE_I386_ALL },
    { "m68k",   CPU_TYPE_MC680x0, CPU_SUBTYPE_MC680x0_ALL },
    { "hppa",   CPU_TYPE_HPPA,    CPU_SUBTYPE_HPPA_ALL },
    { "sparc",	CPU_TYPE_SPARC,   CPU_SUBTYPE_SPARC_ALL },
    { "m88k",   CPU_TYPE_MC88000, CPU_SUBTYPE_MC88000_ALL },
    { "i860",   CPU_TYPE_I860,    CPU_SUBTYPE_I860_ALL },
    { "arm",    CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_ALL },
    { "ppc601", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_601 },
    { "ppc603", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603 },
    { "ppc603e",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_603e },
    { "ppc603ev",CPU_TYPE_POWERPC,CPU_SUBTYPE_POWERPC_603ev },
    { "ppc604", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604 },
    { "ppc604e",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_604e },
    { "ppc750", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_750 },
    { "ppc7400",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7400 },
    { "ppc7450",CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_7450 },
    { "ppc970", CPU_TYPE_POWERPC, CPU_SUBTYPE_POWERPC_970 },
    { "i486",   CPU_TYPE_I386,    CPU_SUBTYPE_486 },
    { "i486SX", CPU_TYPE_I386,    CPU_SUBTYPE_486SX },
    { "pentium",CPU_TYPE_I386,    CPU_SUBTYPE_PENT },
    { "i586",   CPU_TYPE_I386,    CPU_SUBTYPE_586 },
    { "pentpro", CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO },
    { "i686",   CPU_TYPE_I386, CPU_SUBTYPE_PENTPRO },
    { "pentIIm3",CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M3 },
    { "pentIIm5",CPU_TYPE_I386, CPU_SUBTYPE_PENTII_M5 },
    { "pentium4",CPU_TYPE_I386, CPU_SUBTYPE_PENTIUM_4 },
    { "m68030", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68030_ONLY },
    { "m68040", CPU_TYPE_MC680x0, CPU_SUBTYPE_MC68040 },
    { "hppa7100LC", CPU_TYPE_HPPA,  CPU_SUBTYPE_HPPA_7100LC },
    { "armv4t", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V4T},
    { "armv5",  CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V5TEJ},
    { "xscale", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_XSCALE},
    { "armv6",  CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V6 },
    { "armv6m", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V6M },
    { "armv7",  CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7 },
    { "armv7f", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7F },
    { "armv7s", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7S },
    { "armv7k", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7K },
    { "armv7m", CPU_TYPE_ARM,     CPU_SUBTYPE_ARM_V7M },
    { "armv7em", CPU_TYPE_ARM,    CPU_SUBTYPE_ARM_V7EM },
    { "arm64v8",CPU_TYPE_ARM64,   CPU_SUBTYPE_ARM64_V8 },
    { "",	0,		  0 }
};

char	*get_file_arch_64(struct fat_arch_64 *arch, t_endian endian)
{
	uint32_t		i;
	cpu_type_t		cpu_type;
	cpu_subtype_t	cpu_subtype;

	i = 0;
	//voir si utilisation de masques binaires
	cpu_type = endian_wrap_u32(arch->cputype, endian);
	cpu_subtype = endian_wrap_u32(arch->cpusubtype, endian);
	while (g_archs[i].cpu_type)
	{
		if (cpu_type == g_archs[i].cpu_type
			&& cpu_subtype == g_archs[i].cpu_subtype)
			return (g_archs[i].str);
		i++;
	}
	return(g_archs[i].str);
}

char	*get_file_arch_32(struct fat_arch *arch, t_endian endian)
{
	uint32_t		i;
	cpu_type_t		cpu_type;
	cpu_subtype_t	cpu_subtype;

	i = 0;
	cpu_type = endian_wrap_u32(arch->cputype, endian);
	cpu_subtype = endian_wrap_u32(arch->cpusubtype, endian);
	while (g_archs[i].cpu_type)
	{
		if (cpu_type == g_archs[i].cpu_type
			&& cpu_subtype == g_archs[i].cpu_subtype)
			return (g_archs[i].str);
		i++;
	}
	return(g_archs[i].str);
}
