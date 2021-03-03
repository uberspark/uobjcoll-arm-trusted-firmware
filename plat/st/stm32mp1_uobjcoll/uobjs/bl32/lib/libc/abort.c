/*
 * Copyright (c) 2013-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libc/stdlib.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/common/debug.h>

void abort(void)
{
	ERROR("ABORT\n");
	panic();
}
