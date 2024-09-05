/********************************************************************************
 *  Module: Port
 *
 *	File Name: PORT.h
 *
 * Description: Header file for STM32f103C6T6 Microcontroller - Port Driver.
 *
 * Author: Mostafa Amr
 *
 *******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

#include "Std_Types.h"

#define PORT_VENDOR_ID       (1000U)

/*Port Module ID*/
#define PORT_MODULE_ID       (124U)

/*Port Instance ID*/
#define PORT_INSTANCE_ID     (0U)

/*
 * Port Module Software Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION   (1U)
#define PORT_SW_MINOR_VERSION   (0U)
#define PORT_SW_PATCH_VERSION   (0U)

/*
 * Port Module Autosar Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for PORT Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "PORT_cfg.h"
#include "PORT_private.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT init*/
#define PORT_INIT_SID                               (uint8)(0x00)

/* Service ID for PORT set pin direction*/
#define PORT_SET_PIN_DIRECTION_SID                  (uint8)(0x01)

/* Service ID for PORT refresh direction*/
#define PORT_REFRESH_PORT_DIRECTION_SID             (uint8)(0x02)

/* Service ID for PORT get version info*/
#define PORT_GET_VERSION_INFO_SID                   (uint8)(0x03)

/* Service ID for PORT set pin mode*/
#define PORT_SET_PIN_MODE_SID                       (uint8)(0x04)


/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* Det code to report invalid pin ID*/
#define PORT_E_PARAM_PIN                        (uint8)(0x0A)

/* Det code to report changing unconfigured pin*/
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)(0x0B)

/* Det code to report calling Port_init with wrong paramter*/
#define PORT_E_PARAM_CONFIG                     (uint8)(0x0C)

/* Det code to report invalid mode*/
#define PORT_E_PARAM_INVALID_MODE               (uint8)(0x0D)

/* Det code to report Port_SetPinMode when the mode is unchangeable*/
#define PORT_E_MODE_UNCHANGEABLE                (uint8)(0x0E)

/* Det code to report calling Api service without initialization*/
#define PORT_E_UNINIT                           (uint8)(0x0F)

/* Det code to report calling APIs with NULL_Ptr*/
#define PORT_E_PARAM_POINTER                    (uint8)(0x10)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Port_PinDirectionType used by port APIs*/
typedef enum{
	INPUT_ANALOG = 0b0000,
	INPUT_FLOATING = 0b0100,
	INPUT_PULLUP_PULLDOWN = 0b1000,
	OUTPUT_PUSH_PULL_10_MHZ = 0b0100,
	OUTPUT_PUSH_PULL_2_MHZ = 0b1000,
	OUTPUT_PUSH_PULL_50_MHZ = 0b1100,
	OUTPUT_OPEN_DRAIN_10_MHZ = 0b0101,
	OUTPUT_OPEN_DRAIN_2_MHZ = 0b1001,
	OUTPUT_OPEN_DRAIN_50_MHZ = 0b1101
}Port_PinDirectionType;

/* Type definition for Port_PinModeType used by port APIs*/
typedef enum{
	GPIO = 0b1000,
	OUTPUT_AF_PUSH_PULL_10_MHZ = 0b0110,
	OUTPUT_AF_PUSH_PULL_2_MHZ = 0b1010,
	OUTPUT_AF_PUSH_PULL_50_MHZ = 0b1110,
	OUTPUT_AF_OPEN_DRAIN_10_MHZ = 0b0111,
	OUTPUT_AF_OPEN_DRAIN_2_MHZ = 0b1011,
	OUTPUT_AF_OPEN_DRAIN_50_MHZ = 0b1111

}Port_PinModeType;

/* Type definition for Port_PinType used by port APIs*/
typedef uint8 Port_PinType;


typedef struct{
	  /* Num to contain the mode in the channel*/
	  Port_PinModeType Ch_Mode;

	  /* Num to select the channel direction*/
	  Port_PinDirectionType Ch_Direction;

	  /* Num to select the initial Channel value*/
	  uint8 Ch_Init_Value;

	  /* Boolean to set if port direction changeable or not*/
	  boolean PortPinDirectionChangeable;

	  /* Boolean to set if port mode changeable or not*/
	  boolean PortPinModeChangeable;

	  /* Boolean to set the internal pull up*/
	  boolean PortPinInternalPullUpEnable;

	  /* Boolean to set the internal pull down*/
	  boolean PortPinInternalPullDownEnable;

}Port_ConfigChannel;

typedef struct{
	Port_ConfigChannel Channels[PortNumberOfPortPins];
}Port_ConfigType;



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr);

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - pin: Port Pin ID number
*                  - Direction: Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction
************************************************************************************/
void Port_RefreshPortDirection(void);

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo: Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - Pin:  Port Pin ID number
*                  - Mode: New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H_ */
