/*
 * Copyright (c) 2021, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TS_ATTESTATION_OPCODES_H
#define TS_ATTESTATION_OPCODES_H

/* C/C++ definition of attestation service opcodes
 */

/* Report generation and retrieval operations */
#define TS_ATTESTATION_OPCODE_GET_TOKEN             (0x0001)
#define TS_ATTESTATION_OPCODE_GET_TOKEN_SIZE        (0x0002)

/* Provisioning operations */
#define TS_ATTESTATION_OPCODE_EXPORT_IAK_PUBLIC_KEY (0x0003)
#define TS_ATTESTATION_OPCODE_IMPORT_IAK            (0x0004)
#define TS_ATTESTATION_OPCODE_IAK_EXISTS            (0x0005)

#endif /* TS_ATTESTATION_OPCODES_H */