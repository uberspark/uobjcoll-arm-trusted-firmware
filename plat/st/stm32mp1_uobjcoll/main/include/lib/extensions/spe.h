/*
 * Copyright (c) 2017-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SPE_H
#define SPE_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/main/include/lib/libc/stdbool.h>

bool spe_supported(void);
void spe_enable(bool el2_unused);
void spe_disable(void);

#endif /* SPE_H */
