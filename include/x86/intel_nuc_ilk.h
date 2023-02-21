/*
 * Author: Ambica Pramod <ambica.pramod@intel.com>
 * Copyright (c) 2023 Intel Corporation.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mraa_internal.h"

// +1 as pins are "1 indexed"
#define MRAA_INTEL_NUC_ILK_PINCOUNT (40 + 1)

mraa_board_t*
mraa_intel_nuc_ilk();

#ifdef __cplusplus
}
#endif
