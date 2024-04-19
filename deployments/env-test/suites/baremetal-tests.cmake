#-------------------------------------------------------------------------------
# Copyright (c) 2022-2023, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
# Baremetal driver test cases to test paltform driver operation from within
# a secure execution environment.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
#  Components-under-test and test cases baremetal platform tests.
#
#-------------------------------------------------------------------------------
add_components(TARGET "env-test"
	BASE_DIR ${TS_ROOT}
	COMPONENTS
		"components/common/uuid"
		"components/service/crypto/backend/mbedcrypto"
		"components/service/crypto/backend/mbedcrypto/trng_adapter/platform"
		"components/service/crypto/backend/mbedcrypto/trng_adapter/test"
		"components/service/secure_storage/include"
		"components/service/secure_storage/frontend/psa/its"
		"components/service/secure_storage/backend/secure_storage_client"
		"components/config/test/sp"
		"components/rpc/common/caller"
		"components/service/block_storage/block_store"
		"components/service/block_storage/block_store/device"
		"components/service/block_storage/block_store/device/semihosting"
		"components/service/block_storage/block_store/device/semihosting/test"
		"components/service/log/backend/uart"
		"components/service/log/backend/uart/uart_adapter/platform"
		"components/service/log/backend/uart/uart_adapter/test"
)

target_sources(env-test PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/registration/baremetal_tests.c
)

#-------------------------------------------------------------------------------
#  Components used from external projects
#
#-------------------------------------------------------------------------------

# Mbed TLS provides libmbedcrypto
set(MBEDTLS_USER_CONFIG_FILE "${TS_ROOT}/external/MbedTLS/config/libmbed_only.h"
	CACHE STRING "Configuration file for Mbed TLS" FORCE)
include(${TS_ROOT}/external/MbedTLS/MbedTLS.cmake)
target_link_libraries(env-test PRIVATE MbedTLS::mbedcrypto)

# Provide the config path to mbedtls
target_compile_definitions(env-test
	PRIVATE
		MBEDTLS_USER_CONFIG_FILE="${MBEDTLS_USER_CONFIG_FILE}"
)

#-------------------------------------------------------------------------------
#  This test suite depends on platform specific drivers
#
#-------------------------------------------------------------------------------
add_platform(TARGET "env-test")
