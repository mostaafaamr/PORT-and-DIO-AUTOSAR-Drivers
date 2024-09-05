/********************************************************************************
 *  Module: Dio
 *
 *	File Name: DIO_cfg.h
 *
 * Description: Pre-Compile Configuration Header file for STM32f103C6T6 Microcontroller - Dio Driver.
 *
 * Author: Mostafa Amr
 *
 *******************************************************************************/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION              (1U)
#define DIO_CFG_SW_MINOR_VERSION              (0U)
#define DIO_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* For the number of channels in the microcontroller*/
#define PortNumberOfPortPins        (48U)

/* For the number of port A*/
#define PORTA_NUM                       (Dio_PortType)(0U)

/* For the number of port B*/
#define PORTB_NUM                       (Dio_PortType)(1U)

/* For the number of port C*/
#define PORTC_NUM                       (Dio_PortType)(2U)

/* For the start channel number of port A*/
#define PORTA_START_CHANNEL_NUMBER      (0U)

/* For the start channel number of port B*/
#define PORTB_START_CHANNEL_NUMBER      (16U)

/* For the start channel number of port C*/
#define PORTC_START_CHANNEL_NUMBER      (32U)

/*Pins definitions*/
#define PA0  0
#define PA1  1
#define PA2  2
#define PA3  3
#define PA4  4
#define PA5  5
#define PA6  6
#define PA7  7
#define PA8  8
#define PA9  9
#define PA10 10
#define PA11 11
#define PA12 12
#define PA13 13
#define PA14 14
#define PA15 15

#define PB0  0
#define PB1  1
#define PB2  2
#define PB3  3
#define PB4  4
#define PB5  5
#define PB6  6
#define PB7  7
#define PB8  8
#define PB9  9
#define PB10 10
#define PB11 11
#define PB12 12
#define PB13 13
#define PB14 14
#define PB15 15

#define PC0  0
#define PC1  1
#define PC2  2
#define PC3  3
#define PC4  4
#define PC5  5
#define PC6  6
#define PC7  7
#define PC8  8
#define PC9  9
#define PC10 10
#define PC11 11
#define PC12 12
#define PC13 13
#define PC14 14
#define PC15 15

/* Pre-compile option for Development Error Detect */
#define DIO_DEV_ERROR_DETECT                (STD_OFF)

/* Pre-compile option for Version Info API */
#define DIO_VERSION_INFO_API                (STD_OFF)

/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (2U)





#endif /* DIO_CFG_H_ */
