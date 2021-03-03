/*
 * Copyright (c) 2016 - 2020, Broadcom
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#ifndef CHAL_TYPES_H
#define CHAL_TYPES_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libc/stdint.h>

//
// Generic cHAL handler
//
#ifndef CHAL_HANDLE
	typedef void *CHAL_HANDLE;	///< void pointer (32 bits wide)
#endif

#endif	/* _CHAL_TYPES_H_ */
