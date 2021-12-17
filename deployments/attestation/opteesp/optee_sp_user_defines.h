/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2021-2022, Arm Limited and Contributors. All rights reserved.
 */

#ifndef SP_HEADER_DEFINES_H
#define SP_HEADER_DEFINES_H

/* To get UUID definition */
#include "attestation_sp.h"

#define OPTEE_SP_UUID				ATTESTATION_SP_UUID
#define OPTEE_SP_FLAGS				0

/* Provisioned stack size */
#define OPTEE_SP_STACK_SIZE			(64 * 1024)

#endif /* SP_HEADER_DEFINES_H */
