/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef __ADC_H_
#define __ADC_H_

#define TVDIN_ADC_VER "2021/05/20 S4D dvbs clk support"

#define ADC_CLK_24M       24000
#define ADC_CLK_25M       25000

/* afe regisgers */
#define AFE_VAFE_CTRL0		(0x3B0)
#define AFE_VAFE_CTRL1		(0x3B1)
#define AFE_VAFE_CTRL2		(0x3B2)

#define HHI_CADC_CNTL           0x20
#define HHI_CADC_CNTL2          0x21

/* HIU registers */
#define HHI_DADC_CNTL		0x27
#define HHI_DADC_CNTL2		0x28
#define HHI_DADC_CNTL3		0x2a
#define HHI_DADC_CNTL4		0x2b
#define HHI_VDAC_CNTL1_T5	0xbc

#define HHI_ADC_PLL_CNTL3	0xac
#define HHI_ADC_PLL_CNTL	0xaa
#define HHI_ADC_PLL_CNTL1	0xaf
#define HHI_ADC_PLL_CNTL2	0xab
#define HHI_ADC_PLL_CNTL4	0xad
#define HHI_ADC_PLL_CNTL5	0x9e
#define HHI_ADC_PLL_CNTL6	0x9f
#define HHI_ADC_PLL_CNTL0_TL1	0xb0

#define HHI_DEMOD_CLK_CNTL	0x74

#define RESET1_REGISTER		0x1102

#define ADC_ADDR_TL1_TO_S4	.adc_addr = {\
		.dadc_cntl = 0x27,\
		.dadc_cntl_2 = 0x28,\
		.dadc_cntl_3 = 0x2a,\
		.dadc_cntl_4 = 0x2b,\
		.s2_dadc_cntl = 0x41,\
		.s2_dadc_cntl_2 = 0x42,\
		.vdac_cntl_0 = 0xbb,\
	}

#define ADC_ADDR_T3	.adc_addr = {\
		.dadc_cntl = 0x90,\
		.dadc_cntl_2 = 0x91,\
		.dadc_cntl_3 = 0x92,\
		.dadc_cntl_4 = 0x93,\
		.s2_dadc_cntl = 0x94,\
		.s2_dadc_cntl_2 = 0x95,\
		.vdac_cntl_0 = 0xb0,\
	}

#define ADC_PLL_ADDR_TL1	.pll_addr = {\
		.adc_pll_cntl_0 = 0xb0,\
		.adc_pll_cntl_1 = 0xb1,\
		.adc_pll_cntl_2 = 0xb2,\
		.adc_pll_cntl_3 = 0xb3,\
		.adc_pll_cntl_4 = 0xb4,\
		.adc_pll_cntl_5 = 0xb5,\
		.adc_pll_cntl_6 = 0xb6,\
	}

#define ADC_PLL_ADDR_T3		.pll_addr = {\
		.adc_pll_cntl_0 = 0x97,\
		.adc_pll_cntl_1 = 0x98,\
		.adc_pll_cntl_2 = 0x99,\
		.adc_pll_cntl_3 = 0x9a,\
		.adc_pll_cntl_4 = 0x9b,\
		.adc_pll_cntl_5 = 0x9c,\
		.adc_pll_cntl_6 = 0x9d,\
	}

enum adc_map_addr {
	MAP_ADDR_AFE,
	MAP_ADDR_HIU,
	MAP_ADDR_NUM
};

enum adc_chip_ver {
	ADC_CHIP_GXL = 0,
	ADC_CHIP_GXM,
	ADC_CHIP_TXL,
	ADC_CHIP_TXLX,
	ADC_CHIP_GXLX,
	ADC_CHIP_TXHD,
	ADC_CHIP_G12A,
	ADC_CHIP_G12B,
	ADC_CHIP_SM1,
	ADC_CHIP_TL1,
	ADC_CHIP_TM2,
	ADC_CHIP_T5,
	ADC_CHIP_T5D,
	ADC_CHIP_S4,
	ADC_CHIP_T3,
	ADC_CHIP_S4D,
};

struct adc_reg_phy {
	unsigned int phy_addr;
	unsigned int size;
};

struct adc_reg_addr {
	unsigned int dadc_cntl;
	unsigned int dadc_cntl_2;
	unsigned int dadc_cntl_3;
	unsigned int dadc_cntl_4;
	unsigned int s2_dadc_cntl;
	unsigned int s2_dadc_cntl_2;
	unsigned int vdac_cntl_0;
};

struct adc_pll_reg_addr {
	unsigned int adc_pll_cntl_0;
	unsigned int adc_pll_cntl_1;
	unsigned int adc_pll_cntl_2;
	unsigned int adc_pll_cntl_3;
	unsigned int adc_pll_cntl_4;
	unsigned int adc_pll_cntl_5;
	unsigned int adc_pll_cntl_6;
};

struct adc_platform_data_s {
	struct adc_reg_addr adc_addr;
	struct adc_pll_reg_addr pll_addr;
	enum adc_chip_ver chip_id;
};

struct tvin_adc_dev {
	struct device_node *node;
	struct device *dev;
	/*struct platform_device *pdev;*/
	dev_t dev_no;
	const struct of_device_id *of_id;
	/*struct device *cdev;*/

	struct adc_platform_data_s *plat_data;
	struct mutex ioctl_mutex;/* aviod re-entry of ioctl calling */
	struct mutex pll_mutex; /* protect pll setting for multi modules */
	struct mutex filter_mutex;
	unsigned int pll_flg;
	unsigned int filter_flg;
	unsigned int print_en;
	struct adc_reg_phy phy_addr[MAP_ADDR_NUM];
	void __iomem *vir_addr[MAP_ADDR_NUM];
};

#endif

