/* linux/arch/arm/plat-s5p/cpu.c
 *
 * Copyright (c) 2009-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * S5P CPU Support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
#include <linux/module.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include <mach/map.h>
#include <mach/regs-clock.h>

#include <plat/cpu.h>
#include <plat/s5p6442.h>

/* table of supported CPUs */

static const char name_s5p6442[] = "S5P6442";

static struct cpu_table cpu_ids[] __initdata = {
	{
		.idcode		= S5P6442_CPU_ID,
		.idmask		= S5P64XX_CPU_MASK,
		.map_io		= s5p6442_map_io,
		.init_clocks	= s5p6442_init_clocks,
		.init_uarts	= s5p6442_init_uarts,
		.init		= s5p6442_init,
		.name		= name_s5p6442,
	},
};

/* minimal IO mapping */

static struct map_desc s5p_iodesc[] __initdata = {
	{
		.virtual	= (unsigned long)S5P_VA_CHIPID,
		.pfn		= __phys_to_pfn(S5P_PA_CHIPID),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_SYS,
		.pfn		= __phys_to_pfn(S5P_PA_SYSCON),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_TIMER,
		.pfn		= __phys_to_pfn(S5P_PA_TIMER),
		.length		= SZ_16K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S3C_VA_WATCHDOG,
		.pfn		= __phys_to_pfn(S3C_PA_WDT),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= (unsigned long)S5P_VA_SROMC,
		.pfn		= __phys_to_pfn(S5P_PA_SROMC),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
};

/* read cpu identification code */

void __init s5p_init_io(struct map_desc *mach_desc,
			int size, void __iomem *cpuid_addr)
{
	unsigned long samsung_cpu_id;

	/* initialize the io descriptors we need for initialization */
	iotable_init(s5p_iodesc, ARRAY_SIZE(s5p_iodesc));
	if (mach_desc)
		iotable_init(mach_desc, size);

	samsung_cpu_id = __raw_readl(cpuid_addr);
	s3c_init_cpu(samsung_cpu_id, cpu_ids, ARRAY_SIZE(cpu_ids));
}
