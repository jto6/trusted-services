/*
 * Copyright (c) 2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sfs_flash.h"
#include "sfs_flash_ram.h"
#include "../sfs_utils.h"

#define SFS_FLASH_AREA_ADDR (0x0)

/* Adjust to a size that will allow all assets to fit */
#define SFS_FLASH_AREA_SIZE (0x4000)

/* Adjust to match the size of the flash device's physical erase unit */
#define SFS_SECTOR_SIZE (0x1000)

/* Adjust so that the maximum required asset size will fit in one block */
#define SFS_SECTORS_PER_BLOCK (0x1)

/* Adjust to match the size of the flash device's physical program unit */
#define SFS_FLASH_PROGRAM_UNIT (0x1)

/* The maximum asset size to be stored in the SFS area */
#define SFS_MAX_ASSET_SIZE (4096)

/* The maximum number of assets to be stored in the SFS area */
#define SFS_NUM_ASSETS (10)

/* Calculate the block layout */
#define FLASH_INFO_BLOCK_SIZE (SFS_SECTOR_SIZE * SFS_SECTORS_PER_BLOCK)
#define FLASH_INFO_NUM_BLOCKS (SFS_FLASH_AREA_SIZE / FLASH_INFO_BLOCK_SIZE)

/* Maximum file size */
#define FLASH_INFO_MAX_FILE_SIZE SFS_UTILS_ALIGN(SFS_MAX_ASSET_SIZE, \
                                                 SFS_FLASH_ALIGNMENT)

/* Maximum number of files */
#define FLASH_INFO_MAX_NUM_FILES SFS_NUM_ASSETS

/* Default value of each byte in the flash when erased */
#define FLASH_INFO_ERASE_VAL 0xFFU

/* Allocate a static buffer to emulate storage in RAM */
static uint8_t sfs_block_data[FLASH_INFO_BLOCK_SIZE * FLASH_INFO_NUM_BLOCKS];
#define FLASH_INFO_DEV sfs_block_data

const struct sfs_flash_info_t sfs_flash_info_internal = {
    .init = sfs_flash_ram_init,
    .read = sfs_flash_ram_read,
    .write = sfs_flash_ram_write,
    .flush = sfs_flash_ram_flush,
    .erase = sfs_flash_ram_erase,
    .flash_dev = (void *)FLASH_INFO_DEV,
    .flash_area_addr = SFS_FLASH_AREA_ADDR,
    .sector_size = SFS_SECTOR_SIZE,
    .block_size = FLASH_INFO_BLOCK_SIZE,
    .num_blocks = FLASH_INFO_NUM_BLOCKS,
    .program_unit = SFS_FLASH_ALIGNMENT,
    .max_file_size = FLASH_INFO_MAX_FILE_SIZE,
    .max_num_files = FLASH_INFO_MAX_NUM_FILES,
    .erase_val = FLASH_INFO_ERASE_VAL,
};

/* Checks at compile time that the flash device configuration is valid */
#include "../flash_fs/sfs_flash_fs_check_info.h"
