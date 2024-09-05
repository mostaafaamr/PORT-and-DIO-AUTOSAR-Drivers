/********************************************************************************
 *  Module: Port
 *
 *	File Name: PORT_config.h
 *
 * Description: Pre-Compile Configuration Header file for STM32f103C6T6 Microcontroller - Port Driver.
 *
 * Author: Mostafa Amr
 *
 *******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* For development error detection*/
#define PORT_DEV_ERROR_DETECT           (STD_OFF)

/* For enabling the Port_SetPinDirection API*/
#define PORT_SET_PIN_DIRECTION_API      (STD_ON)

/* For enabling the Port_SetPinMode API*/
#define PORT_SET_PIN_MODE_API           (STD_ON)

/* For enabling the Port_GetVersionInfo API*/
#define PORT_VERSION_INFO_API           (STD_OFF)


/* For the number of channels in the microcontroller*/
#define PortNumberOfPortPins        (48U)

/* For the number of port A*/
#define PORTA_NUM                       (0U)

/* For the number of port B*/
#define PORTB_NUM                       (1U)

/* For the number of port C*/
#define PORTC_NUM                       (2U)

/* For the start channel number of port A*/
#define PORTA_START_CHANNEL_NUMBER      (0U)

/* For the start channel number of port B*/
#define PORTB_START_CHANNEL_NUMBER      (16U)

/* For the start channel number of port C*/
#define PORTC_START_CHANNEL_NUMBER      (32U)

/* For the default value of the channel mode*/
#define PORT_DEFAULT_MODE_VALUE         (GPIO)

/* For the default value of the channel direction*/
#define PORT_DEFAULT_DIRECTION_VALUE            (INPUT_PULLUP_PULLDOWN)

/* For the default value of the channel level*/
#define PORT_DEFAULT_LEVEL_VALUE                (STD_LOW)

/* For the default changeability of the channel direction*/
#define PORT_DEFAULT_DIRECTION_CHANGEABLE       (STD_ON)

/* For the default changeability of the channel mode*/
#define PORT_DEFAULT_MODE_CHANGEABLE            (STD_ON)

/* For the default internal pull up setting*/
#define PORT_DEFAULT_INTERNAL_PULL_UP           (STD_OFF)

/* For the default internal pull down setting*/
#define PORT_DEFAULT_INTERNAL_PULL_DOWN         (STD_OFF)

/* Bits used for reseting of port cfg register bits */
#define PORT_PIN_CFG_REG_MASK          (0b1111)


#endif /* PORT_CFG_H_ */
