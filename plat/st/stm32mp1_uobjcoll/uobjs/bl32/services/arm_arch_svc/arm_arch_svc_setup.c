/*
 * Copyright (c) 2018-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <uberspark/uobjcoll/platform/st/stm32mp1/include/uobjcoll.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/common/debug.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/common/runtime_svc.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/cpus/errata_report.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/cpus/wa_cve_2017_5715.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/cpus/wa_cve_2018_3639.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/lib/smccc.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/services/arm_arch_svc.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/arch/smccc_helpers.h>
#include <uberspark/uobjcoll/platform/st/stm32mp1/uobjs/bl32/include/plat/common/platform.h>

static int32_t smccc_version(void)
{
	return MAKE_SMCCC_VERSION(SMCCC_MAJOR_VERSION, SMCCC_MINOR_VERSION);
}

static int32_t smccc_arch_features(u_register_t arg1)
{
	switch (arg1) {
	case SMCCC_VERSION:
	case SMCCC_ARCH_FEATURES:
		return SMC_ARCH_CALL_SUCCESS;
	case SMCCC_ARCH_SOC_ID:
		return plat_is_smccc_feature_available(arg1);
#if __UBERSPARK_UOBJCOLL_CONFIGDEF_WORKAROUND_CVE_2017_5715__
	case SMCCC_ARCH_WORKAROUND_1:
		if (check_wa_cve_2017_5715() == ERRATA_NOT_APPLIES)
			return 1;
		return 0; /* ERRATA_APPLIES || ERRATA_MISSING */
#endif

#if __UBERSPARK_UOBJCOLL_CONFIGDEF_WORKAROUND_CVE_2018_3639__
	case SMCCC_ARCH_WORKAROUND_2: {
#if __UBERSPARK_UOBJCOLL_CONFIGDEF_DYNAMIC_WORKAROUND_CVE_2018_3639__
		unsigned long long ssbs;

		/*
		 * Firmware doesn't have to carry out dynamic workaround if the
		 * PE implements architectural Speculation Store Bypass Safe
		 * (SSBS) feature.
		 */
		ssbs = (read_id_aa64pfr1_el1() >> ID_AA64PFR1_EL1_SSBS_SHIFT) &
			ID_AA64PFR1_EL1_SSBS_MASK;

		/*
		 * If architectural SSBS is available on this PE, no firmware
		 * mitigation via SMCCC_ARCH_WORKAROUND_2 is required.
		 */
		if (ssbs != SSBS_UNAVAILABLE)
			return 1;

		/*
		 * On a platform where at least one CPU requires
		 * dynamic mitigation but others are either unaffected
		 * or permanently mitigated, report the latter as not
		 * needing dynamic mitigation.
		 */
		if (wa_cve_2018_3639_get_disable_ptr() == NULL)
			return 1;
		/*
		 * If we get here, this CPU requires dynamic mitigation
		 * so report it as such.
		 */
		return 0;
#else
		/* Either the CPUs are unaffected or permanently mitigated */
		return SMC_ARCH_CALL_NOT_REQUIRED;
#endif
	}
#endif

	/* Fallthrough */

	default:
		return SMC_UNK;
	}
}

/* return soc revision or soc version on success otherwise
 * return invalid parameter */
static int32_t smccc_arch_id(u_register_t arg1)
{
	if (arg1 == SMCCC_GET_SOC_REVISION) {
		return plat_get_soc_revision();
	}
	if (arg1 == SMCCC_GET_SOC_VERSION) {
		return plat_get_soc_version();
	}
	return SMC_ARCH_CALL_INVAL_PARAM;
}

/*
 * Top-level Arm Architectural Service SMC handler.
 */
static uintptr_t arm_arch_svc_smc_handler(uint32_t smc_fid,
	u_register_t x1,
	u_register_t x2,
	u_register_t x3,
	u_register_t x4,
	void *cookie,
	void *handle,
	u_register_t flags)
{
	switch (smc_fid) {
	case SMCCC_VERSION:
		SMC_RET1(handle, smccc_version());
	case SMCCC_ARCH_FEATURES:
		SMC_RET1(handle, smccc_arch_features(x1));
	case SMCCC_ARCH_SOC_ID:
		SMC_RET1(handle, smccc_arch_id(x1));
#if __UBERSPARK_UOBJCOLL_CONFIGDEF_WORKAROUND_CVE_2017_5715__
	case SMCCC_ARCH_WORKAROUND_1:
		/*
		 * The workaround has already been applied on affected PEs
		 * during entry to EL3.  On unaffected PEs, this function
		 * has no effect.
		 */
		SMC_RET0(handle);
#endif
#if __UBERSPARK_UOBJCOLL_CONFIGDEF_WORKAROUND_CVE_2018_3639__
	case SMCCC_ARCH_WORKAROUND_2:
		/*
		 * The workaround has already been applied on affected PEs
		 * requiring dynamic mitigation during entry to EL3.
		 * On unaffected or statically mitigated PEs, this function
		 * has no effect.
		 */
		SMC_RET0(handle);
#endif
	default:
		WARN("Unimplemented Arm Architecture Service Call: 0x%x \n",
			smc_fid);
		SMC_RET1(handle, SMC_UNK);
	}
}

/* Register Standard Service Calls as runtime service */
DECLARE_RT_SVC(
		arm_arch_svc,
		OEN_ARM_START,
		OEN_ARM_END,
		SMC_TYPE_FAST,
		NULL,
		arm_arch_svc_smc_handler
);
