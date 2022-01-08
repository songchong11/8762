/**
*********************************************************************************************************
*               Copyright(c) 2018, Realtek Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file     board.h
* @brief    Pin definitions and dlps config
* @details
* @author
* @date     2018-01-19
* @version  v0.1
* *********************************************************************************************************
*/

#ifndef _BOARD_H_
#define _BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FLASH_SPI                   SPI0

/* SPI pin define*/
#define SPI0_SCK_PIN                P4_0
#define SPI0_MOSI_PIN               P4_1
#define SPI0_MISO_PIN               P4_2
#define SPI0_CS_PIN                 P4_3


#define DLPS_EN                         0

/* if use user define dlps enter/dlps exit callback function */
#define USE_USER_DEFINE_DLPS_ENTER_CB   1
#define USE_USER_DEFINE_DLPS_EXIT_CB    1

/* if use any peripherals below, #define it 1 */
#define USE_ADC_DLPS                0
#define USE_CODEC_DLPS              0
#define USE_DMIC_DLPS               0
#define USE_GPIO_DLPS               0
#define USE_I2C0_DLPS               0
#define USE_I2C1_DLPS               0
#define USE_I2S0_DLPS               0
#define USE_I2S1_DLPS               0
#define USE_IR_DLPS                 0
#define USE_KEYSCAN_DLPS            0
#define USE_PWM0_DLPS               0
#define USE_PWM1_DLPS               0
#define USE_PWM2_DLPS               0
#define USE_PWM3_DLPS               0
#define USE_QDECODER_DLPS           0
#define USE_RTC_DLPS                0
#define USE_SPI0_DLPS               0
#define USE_SPI1_DLPS               0
#define USE_SPI2W_DLPS              0
#define USE_TIM_DLPS                0
#define USE_UART0_DLPS              0
#define USE_UART1_DLPS              0
#define USE_LOG_UART2_DLPS          0

#define USE_GDMACHANNEL0_DLPS       0
#define USE_GDMACHANNEL1_DLPS       0
#define USE_GDMACHANNEL2_DLPS       0
#define USE_GDMACHANNEL3_DLPS       0
#define USE_GDMACHANNEL4_DLPS       0
#define USE_GDMACHANNEL5_DLPS       0
#define USE_GDMA_DLPS               (USE_GDMACHANNEL0_DLPS | USE_GDMACHANNEL1_DLPS | USE_GDMACHANNEL2_DLPS\
                                     | USE_GDMACHANNEL3_DLPS | USE_GDMACHANNEL4_DLPS | USE_GDMACHANNEL5_DLPS)

/* do not modify USE_IO_DRIVER_DLPS macro */
#define USE_IO_DRIVER_DLPS          (USE_ADC_DLPS | USE_CODEC_DLPS | USE_DMIC_DLPS | USE_GPIO_DLPS\
                                     | USE_I2C0_DLPS | USE_I2C1_DLPS\
                                     | USE_I2S0_DLPS | USE_I2S1_DLPS| USE_IR_DLPS\
                                     | USE_KEYSCAN_DLPS| USE_PWM0_DLPS | USE_PWM1_DLPS\
                                     | USE_PWM2_DLPS | USE_PWM3_DLPS | USE_QDECODER_DLPS\
                                     | USE_RTC_DLPS | USE_SPI0_DLPS | USE_SPI1_DLPS\
                                     | USE_SPI2W_DLPS | USE_TIM_DLPS | USE_UART0_DLPS\
                                     | USE_UART1_DLPS | USE_LOG_UART2_DLPS | USE_GDMA_DLPS\
                                     | USE_USER_DEFINE_DLPS_ENTER_CB\
                                     | USE_USER_DEFINE_DLPS_EXIT_CB)
#ifdef __cplusplus
}
#endif

#endif

