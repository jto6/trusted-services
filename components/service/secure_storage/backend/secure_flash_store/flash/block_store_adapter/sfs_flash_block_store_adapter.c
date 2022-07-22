/*
 * Copyright (c) 2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stddef.h>
#include <stdint.h>
#include "sfs_flash_block_store_adapter.h"

static inline struct sfs_flash_block_store_adapter *get_context(
	const struct sfs_flash_info_t *info)
{
	return (struct sfs_flash_block_store_adapter *)info->flash_dev;
}

static psa_status_t sfs_flash_init(
	const struct sfs_flash_info_t *info)
{
	struct sfs_flash_block_store_adapter *context;

	/* Ensure that adapter has already been initialised */
	if (!info || (context = get_context(info), !context->block_store))
		return PSA_ERROR_BAD_STATE;

	return PSA_SUCCESS;
}

static psa_status_t sfs_flash_read(
	const struct sfs_flash_info_t *info,
	uint32_t block_id,
	uint8_t *buff,
	size_t offset,
	size_t size)
{
	psa_status_t status = PSA_ERROR_GENERIC_ERROR;
	struct sfs_flash_block_store_adapter *context = get_context(info);
	size_t bytes_read = 0;

	status = block_store_read(context->block_store,
		context->client_id,
		context->partition_handle,
		block_id,
		offset,
		size,
		buff,
		&bytes_read);

	if ((status == PSA_SUCCESS) && (bytes_read != size))
		/* Requested size invalid */
		status = PSA_ERROR_INVALID_ARGUMENT;

	return status;
}

static psa_status_t sfs_flash_write(
	const struct sfs_flash_info_t *info,
	uint32_t block_id,
	const uint8_t *buff,
	size_t offset,
	size_t size)
{
	psa_status_t status = PSA_ERROR_GENERIC_ERROR;
	struct sfs_flash_block_store_adapter *context = get_context(info);
	size_t bytes_written = 0;

	status = block_store_write(context->block_store,
		context->client_id,
		context->partition_handle,
		block_id,
		offset,
		buff,
		size,
		&bytes_written);

	if ((status == PSA_SUCCESS) && (bytes_written != size))
		/* Requested size invalid */
		status = PSA_ERROR_INVALID_ARGUMENT;

	return status;
}

static psa_status_t sfs_flash_flush(
	const struct sfs_flash_info_t *info)
{
	/* Not supported by block_store */
	(void)info;
	return PSA_SUCCESS;
}

static psa_status_t sfs_flash_erase(
	const struct sfs_flash_info_t *info,
 	uint32_t block_id)
{
	psa_status_t status = PSA_ERROR_GENERIC_ERROR;
	struct sfs_flash_block_store_adapter *context = get_context(info);

	status = block_store_erase(context->block_store,
		context->client_id,
		context->partition_handle,
		block_id, 1);

	return status;
}

psa_status_t sfs_flash_block_store_adapter_init(
	struct sfs_flash_block_store_adapter *context,
	uint32_t client_id,
	struct block_store *block_store,
	const struct uuid_octets *partition_guid,
	size_t max_num_files,
	const struct sfs_flash_info_t **flash_info)
{
	psa_status_t status = PSA_SUCCESS;
	struct sfs_flash_info_t *info = &context->flash_info;
	struct storage_partition_info partition_info;

	*flash_info = info;

	/* Associate with the underlying block_store */
	context->block_store = block_store;
	context->client_id = client_id;

	/* Get information about the assigned storage partition */
	status = block_store_get_partition_info(context->block_store,
		partition_guid, &partition_info);
	if (status != PSA_SUCCESS)
		return status;

	/* Initialise interface used by sfs */
	info->flash_dev = context;
	info->init = sfs_flash_init,
	info->read = sfs_flash_read,
	info->write = sfs_flash_write,
	info->flush = sfs_flash_flush,
	info->erase = sfs_flash_erase,

	/* Attributes that are fixed when using a block_store */
	info->flash_area_addr = 0;
	info->program_unit = sizeof(uint8_t);
	info->erase_val = 0xff;

	/* Underlying storage partition parameters */
	info->sector_size = (uint16_t)partition_info.block_size;
	info->block_size = (uint16_t)partition_info.block_size;
	info->num_blocks = (uint16_t)partition_info.num_blocks;

	/* sfs specific configuration */
	info->max_file_size = (uint16_t)info->block_size;
	info->max_num_files = (uint16_t)max_num_files;

	/* Open the storage partition so that it's ready to use */
	status = block_store_open(context->block_store,
		context->client_id,
		partition_guid,
		&context->partition_handle);

	return status;
}

psa_status_t sfs_flash_block_store_adapter_deinit(
	struct sfs_flash_block_store_adapter *context)
{
	/* Close the storage partition */
	psa_status_t status = block_store_close(context->block_store,
		context->client_id,
		context->partition_handle);

	return status;
}
