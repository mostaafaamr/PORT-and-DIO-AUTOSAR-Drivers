/********************************************************************************
 *  Module: Dio
 *
 *	File Name: DIO.c
 *
 * Description: Source file for STM32f103C6T6 Microcontroller - Dio Driver.
 *
 * Author: Mostafa Amr
 *
 *******************************************************************************/
#include "Dio.h"
#include "PORT_private.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/************************************************************************************
* Service Name: Dio_WriteChannel
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - ChannelId : ID of DIO channel
*                  - Level : Value to be written
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service to set a level of a channel.
************************************************************************************/

void Dio_WriteChannel(Dio_ChannelType ChannelId,Dio_LevelType Level)
{
	Dio_ChannelType PinNum;
	/*The pin is in PORT A*/
	if(ChannelId>=PORTA_START_CHANNEL_NUMBER && ChannelId<PORTB_START_CHANNEL_NUMBER)
	{
		PinNum = ChannelId;
		if(Level == STD_HIGH)
		{
			/*Set the pin level as high*/
			SET_BIT(GPIOA_BSRR,PinNum);
		}
		else SET_BIT(GPIOA_BRR,PinNum);			/*Set the pin level as low*/
	}
	/*The pin is in PORT B*/
	else if(ChannelId>=PORTB_START_CHANNEL_NUMBER && ChannelId<PORTC_START_CHANNEL_NUMBER)
	{
		PinNum = ChannelId%16;
		if(Level == STD_HIGH)
		{
			/*Set the pin level as high*/
			SET_BIT(GPIOB_BSRR,PinNum);
		}
		else SET_BIT(GPIOB_BRR,PinNum);		/*Set the pin level as low*/
	}
	/*The pin is in PORT C*/
	else if(ChannelId>=PORTC_START_CHANNEL_NUMBER && ChannelId<=PortNumberOfPortPins)
	{
		PinNum = ChannelId%16;
		if(Level == STD_HIGH)
		{
			/*Set the pin level as high*/
			SET_BIT(GPIOB_BSRR,PinNum);
		}
		else SET_BIT(GPIOB_BRR,PinNum);		/*Set the pin level as low*/
	}
	else Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
}




/************************************************************************************
* Service Name: Dio_ReadChannel
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
				STD_HIGH The physical level of the corresponding Pin is STD_HIGH
				STD_LOW The physical level of the corresponding Pin is STD_LOW
* Description: Returns the value of the specified DIO channel.
************************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType PinValue = 0;
	Dio_ChannelType PinNum;

	/*The pin is in PORT A*/
	if(ChannelId>=PORTA_START_CHANNEL_NUMBER && ChannelId<PORTB_START_CHANNEL_NUMBER)
	{
		PinNum = ChannelId;
		PinValue = GET_BIT(GPIOA_IDR,PinNum);		/*Get the pin value from input data register*/
	}
	else if(ChannelId>=PORTB_START_CHANNEL_NUMBER && ChannelId<PORTC_START_CHANNEL_NUMBER)
	{
		PinNum = ChannelId%16;
		PinValue = GET_BIT(GPIOB_IDR,PinNum);		/*Get the pin value from input data register*/
	}
	else if(ChannelId>=PORTC_START_CHANNEL_NUMBER && ChannelId<=PortNumberOfPortPins)
	{
		PinNum = ChannelId%16;
		PinValue = GET_BIT(GPIOC_IDR,PinNum);		/*Get the pin value from input data register*/
	}
	else Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);

	return PinValue;
}


/************************************************************************************
* Service Name: Dio_WritePort
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): - PortId : ID of DIO Port
*                  - Level : Value to be written
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service to set a value of the port.
************************************************************************************/

void Dio_WritePort(Dio_PortType PortId,Dio_PortLevelType Level)
{
	switch(PortId)
	{
	case PORTA_NUM: GPIOA_ODR = Level;		/*If it is PORT A, put the value in PORT A data register*/
	break;
	case PORTB_NUM: GPIOB_ODR = Level;		/*If it is PORT B, put the value in PORT B data register*/
	break;
	case PORTC_NUM: GPIOC_ODR = Level;		/*If it is PORT C, put the value in PORT C data register*/
	break;
	}
}


/************************************************************************************
* Service Name: Dio_ReadPort
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId : ID of DIO Port
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType : Level of all channels of that port
* Description: Returns the level of all channels of that port.
************************************************************************************/

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	Dio_PortLevelType PortValue = 0;
	switch(PortId)
		{/*Port A*/
		case PORTA_NUM: PortValue = GPIOA_ODR;		/*Get the port value from output data register*/
		break;
		/*Port B*/
		case PORTB_NUM: PortValue = GPIOB_ODR;		/*Get the port value from output data register*/
		break;
		/*Port C*/
		case PORTC_NUM: PortValue = GPIOC_ODR;		/*Get the port value from output data register*/
		break;
		}
	return PortValue;
}


/************************************************************************************
* Service Name: Dio_FlipChannel
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
				STD_HIGH The physical level of the corresponding Pin is STD_HIGH
				STD_LOW The physical level of the corresponding Pin is STD_LOW
* Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return
the level of the channel after flip.
************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	Dio_ChannelType PinNum;
	Dio_LevelType PinValue = 0;
	if(ChannelId>=PORTA_START_CHANNEL_NUMBER && ChannelId<PORTB_START_CHANNEL_NUMBER)
	{
		PinNum = ChannelId;
		TOG_BIT(GPIOA_IDR,PinNum);						/*Toggle the pin value*/
		PinValue = GET_BIT(GPIOA_IDR,PinNum);			/*Get the pin value after flipping*/
	}
	else if(ChannelId>=PORTB_START_CHANNEL_NUMBER && ChannelId<PORTC_START_CHANNEL_NUMBER)
	{
		PinNum = ChannelId%16;
		TOG_BIT(GPIOB_IDR,PinNum);						/*Toggle the pin value*/
		PinValue = GET_BIT(GPIOB_IDR,PinNum);			/*Get the pin value after flipping*/
	}
	else if(ChannelId>=PORTC_START_CHANNEL_NUMBER && ChannelId<=PortNumberOfPortPins)
	{
		PinNum = ChannelId%16;
		TOG_BIT(GPIOC_IDR,PinNum);						/*Toggle the pin value*/
		PinValue = GET_BIT(GPIOC_IDR,PinNum);			/*Get the pin value after flipping*/
	}
	else Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,DIO_FLIP_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);

	return PinValue;
}
#endif


/************************************************************************************
* Service Name: Dio_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo : Pointer to where to store the version information of this module.
* Return value: None
* Description: Service to get the version information of this module.
************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType* VersionInfo)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	}

#endif
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)DIO_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
}
#endif
