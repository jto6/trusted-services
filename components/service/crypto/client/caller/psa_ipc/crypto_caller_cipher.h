/*
 * Copyright (c) 2021-2023, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PSA_IPC_CRYPTO_CALLER_CIPHER_H
#define PSA_IPC_CRYPTO_CALLER_CIPHER_H

#include <string.h>
#include <stdlib.h>
#include <psa/crypto.h>
#include <psa/client.h>
#include <psa/sid.h>
#include <service/common/client/service_client.h>
#include <service/crypto/backend/psa_ipc/crypto_ipc_backend.h>
#include <protocols/rpc/common/packed-c/status.h>
#include <protocols/service/crypto/packed-c/opcodes.h>
#include <protocols/service/crypto/packed-c/key_attributes.h>
#include <protocols/service/crypto/packed-c/import_key.h>
#include "crypto_caller_key_attributes.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline psa_status_t crypto_caller_cipher_encrypt_setup(
					      struct service_client *context,
					      uint32_t *op_handle,
					      psa_key_id_t key,
					      psa_algorithm_t alg)
{
	struct service_client *ipc = context;
	struct rpc_caller_interface *caller = ipc->session->caller;
	psa_status_t status;
	struct psa_ipc_crypto_pack_iovec iov = {
		.function_id = TFM_CRYPTO_CIPHER_ENCRYPT_SETUP_SID,
		.key_id = key,
		.alg = alg,
		.op_handle = *op_handle,
	};
	struct psa_invec in_vec[] = {
		{ .base = psa_ptr_to_u32(&iov), .len = iov_size },
	};
	struct psa_outvec out_vec[] = {
		{ .base = psa_ptr_to_u32(op_handle), .len = sizeof(uint32_t) }
	};

	status = psa_call(caller, TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec,
			  IOVEC_LEN(in_vec), out_vec, IOVEC_LEN(out_vec));

	return status;
}

static inline psa_status_t crypto_caller_cipher_decrypt_setup(
					      struct service_client *context,
					      uint32_t *op_handle,
					      psa_key_id_t key,
					      psa_algorithm_t alg)
{
	struct service_client *ipc = context;
	struct rpc_caller_interface *caller = ipc->session->caller;
	psa_status_t status;
	struct psa_ipc_crypto_pack_iovec iov = {
		.function_id = TFM_CRYPTO_CIPHER_DECRYPT_SETUP_SID,
		.key_id = key,
		.alg = alg,
		.op_handle = *op_handle,
	};
	struct psa_invec in_vec[] = {
		{ .base = psa_ptr_to_u32(&iov), .len = iov_size },
	};
	struct psa_outvec out_vec[] = {
		{ .base = psa_ptr_to_u32(op_handle), .len = sizeof(uint32_t) }
	};

	status = psa_call(caller, TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec,
			  IOVEC_LEN(in_vec), out_vec, IOVEC_LEN(out_vec));

	return status;
}

static inline psa_status_t crypto_caller_cipher_generate_iv(
					    struct service_client *context,
					    uint32_t op_handle,
					    uint8_t *iv,
					    size_t iv_size,
					    size_t *iv_length)
{
	struct service_client *ipc = context;
	struct rpc_caller_interface *caller = ipc->session->caller;
	psa_status_t status;
	struct psa_ipc_crypto_pack_iovec iov = {
		.function_id = TFM_CRYPTO_CIPHER_GENERATE_IV_SID,
		.op_handle = op_handle,
	};
	struct psa_invec in_vec[] = {
		{ .base = psa_ptr_to_u32(&iov), .len = iov_size },
	};
	struct psa_outvec out_vec[] = {
		{ .base = psa_ptr_to_u32(iv), .len = iv_size },
	};

	status = psa_call(caller, TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec,
			  IOVEC_LEN(in_vec), out_vec, IOVEC_LEN(out_vec));

	*iv_length = out_vec[0].len;

	return status;
}

static inline psa_status_t crypto_caller_cipher_set_iv(
					       struct service_client *context,
					       uint32_t op_handle,
					       const uint8_t *iv,
					       size_t iv_length)
{
	struct service_client *ipc = context;
	struct rpc_caller_interface *caller = ipc->session->caller;
	psa_status_t status;
	struct psa_ipc_crypto_pack_iovec iov = {
		.function_id = TFM_CRYPTO_CIPHER_SET_IV_SID,
		.op_handle = op_handle,
	};
	struct psa_invec in_vec[] = {
		{ .base = psa_ptr_to_u32(&iov), .len = iov_size },
		{ .base = psa_ptr_const_to_u32(iv), .len = iv_length },
	};
	struct psa_outvec out_vec[] = {
		{ .base = psa_ptr_to_u32(&op_handle), .len = sizeof(uint32_t) },
	};

	status = psa_call(caller, TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec,
			  IOVEC_LEN(in_vec), out_vec, IOVEC_LEN(out_vec));

	return status;
}

static inline psa_status_t crypto_caller_cipher_update(
					       struct service_client *context,
					       uint32_t op_handle,
					       const uint8_t *input,
					       size_t input_length,
					       uint8_t *output,
					       size_t output_size,
					       size_t *output_length)
{
	struct service_client *ipc = context;
	struct rpc_caller_interface *caller = ipc->session->caller;
	psa_status_t status;
	struct psa_ipc_crypto_pack_iovec iov = {
		.function_id = TFM_CRYPTO_CIPHER_UPDATE_SID,
		.op_handle = op_handle,
	};
	struct psa_invec in_vec[] = {
		{ .base = psa_ptr_to_u32(&iov), .len = iov_size },
		{ .base = psa_ptr_const_to_u32(input), .len = input_length },
	};
	struct psa_outvec out_vec[] = {
		{ .base = psa_ptr_to_u32(output), .len = output_size },
	};

	status = psa_call(caller, TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec,
			  IOVEC_LEN(in_vec), out_vec, IOVEC_LEN(out_vec));

	*output_length = out_vec[0].len;

	return status;
}

static inline psa_status_t crypto_caller_cipher_finish(
					       struct service_client *context,
					       uint32_t op_handle,
					       uint8_t *output,
					       size_t output_size,
					       size_t *output_length)
{
	struct service_client *ipc = context;
	struct rpc_caller_interface *caller = ipc->session->caller;
	psa_status_t status;
	struct psa_ipc_crypto_pack_iovec iov = {
		.function_id = TFM_CRYPTO_CIPHER_FINISH_SID,
		.op_handle = op_handle,
	};
	struct psa_invec in_vec[] = {
		{ .base = psa_ptr_to_u32(&iov), .len = iov_size },
	};
	struct psa_outvec out_vec[] = {
		{ .base = psa_ptr_to_u32(&op_handle), .len = sizeof(uint32_t) },
		{ .base = psa_ptr_to_u32(output), .len = output_size },
	};

	status = psa_call(caller, TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec,
			  IOVEC_LEN(in_vec), out_vec, IOVEC_LEN(out_vec));

	*output_length = out_vec[1].len;

	return status;
}

static inline psa_status_t crypto_caller_cipher_abort(
					      struct service_client *context,
					      uint32_t op_handle)
{
	struct service_client *ipc = context;
	struct rpc_caller_interface *caller = ipc->session->caller;
	psa_status_t status;
	struct psa_ipc_crypto_pack_iovec iov = {
		.function_id = TFM_CRYPTO_CIPHER_ABORT_SID,
		.op_handle = op_handle,
	};
	struct psa_invec in_vec[] = {
		{ .base = psa_ptr_to_u32(&iov), .len = iov_size },
	};
	struct psa_outvec out_vec[] = {
		{ .base = psa_ptr_to_u32(&op_handle), .len = sizeof(uint32_t) },
	};

	status = psa_call(caller, TFM_CRYPTO_HANDLE, PSA_IPC_CALL, in_vec,
			  IOVEC_LEN(in_vec), out_vec, IOVEC_LEN(out_vec));

	return status;
}

static inline size_t crypto_caller_cipher_max_update_size(const struct service_client *context)
{
	/* Returns the maximum number of bytes that may be
	 * carried as a parameter of the cipher_update operation
	 * using the ipc encoding.
	 */
	size_t payload_space = context->service_info.max_payload;
	size_t overhead = iov_size;

	/* Allow for output to be a whole number of blocks */
	overhead += PSA_BLOCK_CIPHER_BLOCK_MAX_SIZE;

	return (payload_space > overhead) ? payload_space - overhead : 0;
}

#ifdef __cplusplus
}
#endif

#endif /* PSA_IPC_CRYPTO_CALLER_CIPHER_H */
