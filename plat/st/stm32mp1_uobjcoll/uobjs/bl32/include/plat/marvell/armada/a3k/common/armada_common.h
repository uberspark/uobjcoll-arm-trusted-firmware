/*
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 * https://spdx.org/licenses
 */

#ifndef ARMADA_COMMON_H
#define ARMADA_COMMON_H

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/libc/stdint.h>

#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/io_addr_dec.h>

int marvell_get_io_dec_win_conf(struct dec_win_config **win, uint32_t *size);

#endif /* ARMADA_COMMON_H */
