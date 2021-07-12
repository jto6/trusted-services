/*
 * Copyright (c) 2021, Arm Limited and Contributors. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TS_CRYPTO_HASH_H
#define TS_CRYPTO_HASH_H

#include <stdint.h>

/**
 * Hash operations on arbitrary sized data involve three operations,
 * a setup, called once, an update called 1..* times and a finish
 * to finalise theh hash operation.
 */


/********
 * hash_setup operation definition
 */

/* Mandatory fixed sized input parameters */
struct __attribute__ ((__packed__)) ts_crypto_hash_setup_in
{
  uint32_t alg;
};

/* Mandatory fixed sized output parameters */
struct __attribute__ ((__packed__)) ts_crypto_hash_setup_out
{
  uint32_t op_handle;
};

/*********
 * hash_update operation definition
 */

/* Mandatory fixed sized input parameters */
struct __attribute__ ((__packed__)) ts_crypto_hash_update_in
{
  uint32_t op_handle;
};

/* Variable length input parameter tags */
enum
{
    TS_CRYPTO_HASH_UPDATE_IN_TAG_DATA  = 1
};

/*********
 * hash_finish operation definition
 */

/* Mandatory fixed sized input parameters */
struct __attribute__ ((__packed__)) ts_crypto_hash_finish_in
{
  uint32_t op_handle;
};

/* Variable length output parameter tags */
enum
{
    TS_CRYPTO_HASH_FINISH_OUT_TAG_HASH  = 1
};


#endif /* TS_CRYPTO_HASH_H */