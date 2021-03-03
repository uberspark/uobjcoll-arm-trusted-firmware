/*
 * Copyright (c) 2020, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MEASURED_BOOT_H
#define MEASURED_BOOT_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libc/stdint.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/drivers/measured_boot/event_log.h>

/* Platform specific table of image IDs, names and PCRs */
extern const image_data_t images_data[];

/* Functions' declarations */
void measured_boot_init(void);
void measured_boot_finish(void);

#endif /* MEASURED_BOOT_H */
