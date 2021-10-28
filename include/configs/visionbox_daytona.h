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

#define CONFIG_BOOTCOMMAND "run mmc1_boot; run mmc0_boot"

#define _CONFIG_CMD_DISTRO_BOOTCMD_H
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_PART
#define BOOTENV \
	"bootdir=/boot/\0" \
	"bootfile=Image.gz\0" \
	"bootpart=1\0" \
	"prefix=/boot/\0" \
	"mmc0_boot=setenv devtype mmc; setenv devnum 0;" \
	" setenv bootargs ${cbootargs} root=/dev/mmcblk0p1 rootfstype=ext4 ${optargs} quiet;" \
	" if mmc dev ${devnum}; then run scan_dev_for_env; run scan_dev_for_image; fi\0" \
	"mmc1_boot=setenv devtype mmc; setenv devnum 1;" \
	" setenv bootargs ${cbootargs} root=/dev/mmcblk2p1 rootfstype=ext4 ${optargs} quiet;" \
	" if mmc dev ${devnum}; then run scan_dev_for_env; run scan_dev_for_image; fi\0" \
	"scan_dev_for_image=if test -e ${devtype} ${devnum}:${bootpart} ${bootdir}${bootfile}; then" \
	" load ${devtype} ${devnum}:${bootpart} 0x88000000 ${bootdir}${bootfile};" \
	" unzip 0x88000000 ${kernel_addr_r}; booti ${kernel_addr_r} - ${fdt_addr}; fi\0" \
	"scan_dev_for_env=if test -e ${devtype} ${devnum}:${bootpart} ${bootdir}uEnv.txt;" \
	" then echo Importing U-Boot environment ${bootdir}uEnv.txt;" \
	" if load ${devtype} ${devnum}:${bootpart} ${scriptaddr} ${bootdir}uEnv.txt;" \
	" then env import -t ${scriptaddr} ${filesize};" \
	" if test -n $uenvcmd; then echo Running uenvcmd ...;run uenvcmd; fi; fi; fi\0" \
	"optargs=isolcpus=1,2\0"

#include "tegra-common-post.h"

/* Crystal is 38.4MHz. clk_m runs at half that rate */
#define COUNTER_FREQUENCY	19200000

#undef CONFIG_NR_DRAM_BANKS
#define CONFIG_NR_DRAM_BANKS	(1024 + 2)

#define CONFIG_CMD_UNZIP	/* enable unzip command support for compressed images */

#define CONFIG_BOOTP_DHCP_REQUEST_DELAY 50000	/* workaround for Windows Server DHCP server */

#endif
