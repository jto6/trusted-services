/*
 * Copyright (c) 2021, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SERVICE_CLIENT_H
#define SERVICE_CLIENT_H

#include <stddef.h>
#include <psa/error.h>
#include <rpc_caller.h>
#include <service/common/client/service_access_info.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      Common service client structure
 *
 * Holds common service objects needed for client access to a service instance.
 * Includes common information about the service that will have been discovered
 * in some way.  The TS discovery protocol provides a way to do this.  If
 * service info is not available, the service_access_info structure stays in its
 * initialied state.
 */
struct service_client
{
	struct rpc_caller *caller;
	int rpc_status;
	struct service_access_info service_access_info;
};

/**
 * @brief      Initialises the service client
 *
 * Initialises the service client, including discovery of service info
 * if supported by the service provider.
 *
 * @param[in]  context 	service_client instance
 * @param[in]  rpc_caller RPC caller to use
 *
 * @return     A status indicating the success/failure of the operation
 */
psa_status_t service_client_init(
	struct service_client *context,
	struct rpc_caller *caller);

/**
 * @brief      De-initialises the service client
 *
 * @param[in]  context 	service_client instance
 */
void service_client_deinit(
	struct service_client *context);

/**
 * @brief      Set the service info
 *
 * Service info will have been discovered in some way.
 *
 * @param[in]  context 	service_client instance
 * @param[in]  service_access_info service_access_info object
 */
void service_client_set_service_access_info(
	struct service_client *context,
	const struct service_access_info *service_access_info);

#ifdef __cplusplus
}
#endif

#endif /* SERVICE_CLIENT_H */
