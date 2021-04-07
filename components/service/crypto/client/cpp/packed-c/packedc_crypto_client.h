/*
 * Copyright (c) 2020-2021, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PACKEDC_CRYPTO_CLIENT_H
#define PACKEDC_CRYPTO_CLIENT_H

#include <service/crypto/client/cpp/crypto_client.h>
#include <protocols/service/crypto/packed-c/key_attributes.h>

/*
 * A concrete crypto_client that uses the packed-c based crypto access protocol
 */
class packedc_crypto_client : public crypto_client
{
public:
    packedc_crypto_client();
    packedc_crypto_client(struct rpc_caller *caller);
    virtual ~packedc_crypto_client();

    /* Key lifecycle methods */
    psa_status_t generate_key(const psa_key_attributes_t *attributes, psa_key_id_t *id);
    psa_status_t destroy_key(psa_key_id_t id);
    psa_status_t import_key(const psa_key_attributes_t *attributes,
                            const uint8_t *data, size_t data_length, psa_key_id_t *id);

    /* Key export methods */
    psa_status_t export_key(psa_key_id_t id,
                            uint8_t *data, size_t data_size,
                            size_t *data_length);
    psa_status_t export_public_key(psa_key_id_t id,
                            uint8_t *data, size_t data_size, size_t *data_length);

    /* Sign/verify methods */
    psa_status_t sign_hash(psa_key_id_t id, psa_algorithm_t alg,
                            const uint8_t *hash, size_t hash_length,
                            uint8_t *signature, size_t signature_size, size_t *signature_length);
    psa_status_t verify_hash(psa_key_id_t id, psa_algorithm_t alg,
                            const uint8_t *hash, size_t hash_length,
                            const uint8_t *signature, size_t signature_length);

    /* Asymmetric encrypt/decrypt */
    psa_status_t asymmetric_encrypt(psa_key_id_t id, psa_algorithm_t alg,
                            const uint8_t *input, size_t input_length,
                            const uint8_t *salt, size_t salt_length,
                            uint8_t *output, size_t output_size, size_t *output_length);
    psa_status_t asymmetric_decrypt(psa_key_id_t id, psa_algorithm_t alg,
                            const uint8_t *input, size_t input_length,
                            const uint8_t *salt, size_t salt_length,
                            uint8_t *output, size_t output_size, size_t *output_length);

    /* Random number generation */
    psa_status_t generate_random(uint8_t *output, size_t output_size);

private:

    void translate_key_attributes(struct ts_crypto_key_attributes &proto_attributes,
                            const psa_key_attributes_t &psa_attributes);
};

#endif /* PACKEDC_CRYPTO_CLIENT_H */