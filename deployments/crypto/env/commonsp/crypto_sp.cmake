#-------------------------------------------------------------------------------
# Copyright (c) 2022, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
# Includes components needed for deploying the crypto service provider
# within a secure partition.
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Common components for crypto sp deployments
#
#-------------------------------------------------------------------------------
add_components(TARGET "crypto"
	BASE_DIR ${TS_ROOT}
	COMPONENTS
		"components/common/fdt"
		"components/common/trace"
		"components/common/utils"
		"components/config/ramstore"
		"components/config/loader/sp"
		"components/messaging/ffa/libsp"
		"components/rpc/ffarpc/endpoint"
)

target_sources(crypto PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/crypto_sp.c
)