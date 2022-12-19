/*
 * Copyright (c) 2022, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BLOCK_STORAGE_PROVIDER_H
#define BLOCK_STORAGE_PROVIDER_H

#include "rpc/common/endpoint/rpc_interface.h"
#include "service/common/provider/service_provider.h"
#include "service/block_storage/block_store/block_store.h"
#include "service/block_storage/provider/serializer/block_storage_serializer.h"
#include "protocols/rpc/common/packed-c/encoding.h"

#ifdef __cplusplus
extern "C" {
#endif

/* block_storage_provider service provider structure */
struct block_storage_provider
{
	struct service_provider base_provider;
	const struct block_storage_serializer *serializers[TS_RPC_ENCODING_LIMIT];
	struct block_store *block_store;
};

struct rpc_interface *block_storage_provider_init(
	struct block_storage_provider *context,
	struct block_store *block_store);

void block_storage_provider_deinit(
	struct block_storage_provider *context);

void block_storage_provider_register_serializer(
	struct block_storage_provider *context,
	unsigned int encoding,
	const struct block_storage_serializer *serializer);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* BLOCK_STORAGE_PROVIDER_H */
