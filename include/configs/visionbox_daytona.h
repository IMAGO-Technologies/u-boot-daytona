/*
 * Copyright (c), IMAGO Technologies GmbH.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _VISIONBOX_DAYTONA_H
#define _VISIONBOX_DAYTONA_H

#include <linux/sizes.h>

#include "tegra186-common.h"

/* High-level configuration options */
#define CONFIG_TEGRA_BOARD_STRING	"IMAGO VisionBox DAYTONA"

/* I2C */
#define CONFIG_SYS_I2C_TEGRA

/* SD/MMC */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_TEGRA_MMC

/* Environment in eMMC, at the end of 2nd "boot sector" */
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_SYS_MMC_ENV_PART		2
#define CONFIG_ENV_OFFSET		(-CONFIG_ENV_SIZE)

/* PCI host support */
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_CMD_PCI

#define BOARD_EXTRA_ENV_SETTINGS \
	"calculated_vars=kernel_addr_r fdt_addr_r scriptaddr pxefile_addr_r " \
		"ramdisk_addr_r\0" \
	"kernel_addr_r_align=00200000\0" \
	"kernel_addr_r_offset=00080000\0" \
	"kernel_addr_r_size=02000000\0" \
	"kernel_addr_r_aliases=loadaddr\0" \
	"fdt_addr_r_align=00200000\0" \
	"fdt_addr_r_offset=00000000\0" \
	"fdt_addr_r_size=00200000\0" \
	"scriptaddr_align=00200000\0" \
	"scriptaddr_offset=00000000\0" \
	"scriptaddr_size=00200000\0" \
	"pxefile_addr_r_align=00200000\0" \
	"pxefile_addr_r_offset=00000000\0" \
	"pxefile_addr_r_size=00200000\0" \
	"ramdisk_addr_r_align=00200000\0" \
	"ramdisk_addr_r_offset=00000000\0" \
	"ramdisk_addr_r_size=02000000\0"

#define CONFIG_BOOTCOMMAND "run mmc_boot"

#define _CONFIG_CMD_DISTRO_BOOTCMD_H
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_PART
#define BOOTENV \
	"bootfile=Image.gz\0" \
	"prefix=/boot/\0" \
	"mmc_boot=setenv devtype mmc;" \
	" setenv devnum 1;" \
	" setenv bootargs ${cbootargs} root=/dev/mmcblk2p1 rootfstype=ext4;" \
	" run bootcmd_mmc; " \
	" setenv devnum 0; setenv bootargs ${cbootargs} rootfstype=ext4; run bootcmd_mmc;\0" \
	"bootcmd_mmc=if mmc dev ${devnum}; then run scan_dev_for_image; fi\0" \
	"scan_dev_for_image=if test -e ${devtype} ${devnum}:1 ${prefix}${bootfile}; then" \
	" echo Found ${prefix}${bootfile};" \
	" ext4load ${devtype} ${devnum}:${distro_bootpart} 0x88000000 ${prefix}${bootfile};" \
	" unzip 0x88000000 ${kernel_addr_r}; booti ${kernel_addr_r} - ${fdt_addr}; fi\0"

#include "tegra-common-post.h"

/* Crystal is 38.4MHz. clk_m runs at half that rate */
#define COUNTER_FREQUENCY	19200000

#undef CONFIG_NR_DRAM_BANKS
#define CONFIG_NR_DRAM_BANKS	(1024 + 2)

#define CONFIG_CMD_UNZIP	/* enable unzip command support for compressed images */

#endif
