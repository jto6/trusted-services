/*
 * Copyright (c) 2024, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CONFIG_LIBMBED_ONLY_H
#define CONFIG_LIBMBED_ONLY_H

#define MBEDTLS_PSA_CRYPTO_CONFIG
#define MBEDTLS_NO_UDBL_DIVISION
#undef MBEDTLS_HAVE_TIME
#undef MBEDTLS_HAVE_TIME_DATE
#undef MBEDTLS_FS_IO
#define MBEDTLS_ENTROPY_HARDWARE_ALT
#define MBEDTLS_NO_PLATFORM_ENTROPY
#undef MBEDTLS_SELF_TEST
#undef MBEDTLS_PLATFORM_C
#undef MBEDTLS_PSA_ITS_FILE_C
#undef MBEDTLS_TIMING_C
#undef MBEDTLS_AESNI_C
#undef MBEDTLS_AESCE_C
#undef MBEDTLS_PADLOCK_C

#define MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER
#define BACKEND_CRYPTO_API_ADD_PREFIX(f) __mbedtls_backend_##f
#include "../../../components/service/crypto/backend/prefixed_crypto_api.h"

#endif /* CONFIG_LIBMBED_ONLY_H */
