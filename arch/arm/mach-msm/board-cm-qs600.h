/*
 * Copyright (c) 2014, CompuLab ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ARCH_ARM_MACH_MSM_BOARD_APQ8064_H
#define __ARCH_ARM_MACH_MSM_BOARD_APQ8064_H

#include <linux/if_ether.h>
#include <linux/regulator/msm-gpio-regulator.h>
#include <linux/mfd/pm8xxx/pm8921.h>
#include <linux/mfd/pm8xxx/pm8821.h>
#include <mach/msm_memtypes.h>
#include <mach/irqs.h>
#include <mach/rpm-regulator.h>
#include <mach/msm_rtb.h>
#include <mach/msm_cache_dump.h>

/* Macros assume PMIC GPIOs and MPPs start at 1 */
#define PM8921_GPIO_BASE		NR_GPIO_IRQS
#define PM8921_GPIO_PM_TO_SYS(pm_gpio)	(pm_gpio - 1 + PM8921_GPIO_BASE)
#define PM8921_MPP_BASE			(PM8921_GPIO_BASE + PM8921_NR_GPIOS)
#define PM8921_MPP_PM_TO_SYS(pm_mpp)	(pm_mpp - 1 + PM8921_MPP_BASE)
#define PM8921_IRQ_BASE			(NR_MSM_IRQS + NR_GPIO_IRQS)

#define PM8821_MPP_BASE			(PM8921_MPP_BASE + PM8921_NR_MPPS)
#define PM8821_MPP_PM_TO_SYS(pm_mpp)	(pm_mpp - 1 + PM8821_MPP_BASE)
#define PM8821_IRQ_BASE			(PM8921_IRQ_BASE + PM8921_NR_IRQS)

#define TABLA_INTERRUPT_BASE		(PM8821_IRQ_BASE + PM8821_NR_IRQS)

extern struct pm8xxx_regulator_platform_data
	cm_qs600_pm8921_regulator_pdata[] __devinitdata;

extern int cm_qs600_pm8921_regulator_pdata_len __devinitdata;

#define GPIO_VREG_ID_EXT_5V		0
#define GPIO_VREG_ID_EXT_3P3V		1
#define GPIO_VREG_ID_EXT_TS_SW		2
#define GPIO_VREG_ID_EXT_MPP8		3

#define GPIO_VREG_ID_AVC_1P2V		0
#define GPIO_VREG_ID_AVC_1P8V		1
#define GPIO_VREG_ID_AVC_2P2V		2
#define GPIO_VREG_ID_AVC_5V		3
#define GPIO_VREG_ID_AVC_3P3V		4

#define CM_QS600_EXT_3P3V_REG_EN_GPIO	77

extern struct gpio_regulator_platform_data
	cm_qs600_gpio_regulator_pdata[] __devinitdata;

extern struct rpm_regulator_platform_data
	cm_qs600_rpm_regulator_pdata __devinitdata;

extern struct rpm_regulator_platform_data
	cm_qs600_rpm_regulator_pm8921_pdata __devinitdata;

extern struct regulator_init_data cm_qs600_saw_regulator_pdata_8921_s5;
extern struct regulator_init_data cm_qs600_saw_regulator_pdata_8921_s6;
extern struct regulator_init_data cm_qs600_saw_regulator_pdata_8821_s0;
extern struct regulator_init_data cm_qs600_saw_regulator_pdata_8821_s1;

struct mmc_platform_data;
int __init apq8064_add_sdcc(unsigned int controller,
		struct mmc_platform_data *plat);
int __init apq8064_add_uio(void);

void apq8064_init_mmc(void);
void cm_qs600_init_gpiomux(void);
void cm_qs600_init_pmic(void);


#define APQ_8064_GSBI1_QUP_I2C_BUS_ID	0
#define APQ_8064_GSBI2_QUP_I2C_BUS_ID	2
#define APQ_8064_GSBI3_QUP_I2C_BUS_ID	3
#define APQ_8064_GSBI4_QUP_I2C_BUS_ID	4
#define APQ_8064_GSBI5_QUP_I2C_BUS_ID	5

struct i2c_registry {
	u8			machs;
	int			bus;
	struct i2c_board_info	*info;
	int			len;
};

#define I2C_CM_QS600			BIT(0)


extern struct i2c_registry cm_qs600_camera_i2c_devices[];
void cm_qs600_init_camera(void);


unsigned char apq8064_hdmi_as_primary_selected(void);
unsigned char apq8064_mhl_display_enabled(void);
void apq8064_init_fb(void);
void apq8064_allocate_fb_region(void);
void apq8064_mdp_writeback(struct memtype_reserve *reserve_table);
void __init apq8064_set_display_params(char *prim_panel, char *ext_panel,
		unsigned char resolution);

void apq8064_init_gpu(void);
void cm_qs600_pm8xxx_gpio_mpp_init(void);

#define GPIO_EXPANDER_IRQ_BASE		(TABLA_INTERRUPT_BASE + NR_TABLA_IRQS)
#define GPIO_EXPANDER_GPIO_BASE		(PM8821_MPP_BASE + PM8821_NR_MPPS)
#define GPIO_EPM_EXPANDER_BASE		GPIO_EXPANDER_GPIO_BASE

extern struct msm_rtb_platform_data apq8064_rtb_pdata;
extern struct msm_cache_dump_platform_data apq8064_cache_dump_pdata;

/* CM-QS600 on-board EEPROM layout */
#define EEPROM_MAJ_REV_LEN		2
#define EEPROM_MIN_REV_LEN		2
#define EEPROM_MAC_ADDR_NUM		2
#define EEPROM_MAC_ADDR_LEN		ETH_ALEN
#define EEPROM_DATE_LEN			4
#define EEPROM_SERIAL_LEN		12
#define EEPROM_NAME_LEN			16
#define EEPROM_PROD_OPT_NUM		3
#define EEPROM_PROD_OPT_LEN		16

struct cm_qs600_eeprom_config {
	char maj_rev[EEPROM_MAJ_REV_LEN];
	char min_rev[EEPROM_MIN_REV_LEN];
	char mac_addr[EEPROM_MAC_ADDR_NUM][EEPROM_MAC_ADDR_LEN];
	char prod_date[EEPROM_DATE_LEN];
	char serial_num[EEPROM_SERIAL_LEN];
	char wifi_mac_addr[EEPROM_MAC_ADDR_LEN];
	char bt_mac_addr[EEPROM_MAC_ADDR_LEN];
	char layout_ver;
	char res[83];
	char name[EEPROM_NAME_LEN];
	char prod_options[EEPROM_PROD_OPT_NUM][EEPROM_PROD_OPT_LEN];
};

#endif	/* __ARCH_ARM_MACH_MSM_BOARD_APQ8064_H */
