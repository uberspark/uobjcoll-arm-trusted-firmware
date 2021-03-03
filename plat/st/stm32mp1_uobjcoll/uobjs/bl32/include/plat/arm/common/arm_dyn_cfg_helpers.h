/*
 * Copyright (c) 2018-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef ARM_DYN_CFG_HELPERS_H
#define ARM_DYN_CFG_HELPERS_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libc/stddef.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libc/stdint.h>

/* Function declarations */
int arm_dyn_tb_fw_cfg_init(void *dtb, int *node);
int arm_set_dtb_mbedtls_heap_info(void *dtb, void *heap_addr,
	size_t heap_size);

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_MEASURED_BOOT__
int arm_set_bl2_hash_info(void *dtb, void *data);
#endif

#endif /* ARM_DYN_CFG_HELPERS_H */
