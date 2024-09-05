/********************************************************************************
 *  Module: Port
 *
 *	File Name: PORT.c
 *
 * Description: Source file for STM32f103C6T6 Microcontroller - Port Driver.
 *
 * Author: Mostafa Amr
 *
 *******************************************************************************/
#include "PORT.h"
#include "PORT_private.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"

#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

static const Port_ConfigChannel * Port_PortChannels = NULL_PTR;
static uint8 Port_Status = PORT_NOT_INITIALIZED;

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

void Port_Init(const Port_ConfigType* ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the init API's input is Null pointer*/
  if(NULL_PTR == ConfigPtr)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
  }
  else
#endif
  {
	uint8 counter = 0;
	uint8 PinNum = 0;

	boolean PortAClockEnabled = FALSE;
	boolean PortBClockEnabled = FALSE;
	boolean PortCClockEnabled = FALSE;


	/* Global variable to declare that the port is initialized successfully*/
	Port_Status = PORT_INITIALIZED;

	/* To address the first channel Channels[0]*/
	Port_PortChannels = ConfigPtr->Channels;


	/*Loop on all the controller pins*/
	for(counter = PORTA_START_CHANNEL_NUMBER; counter<PortNumberOfPortPins; counter++)
	{
		/*PORT A*/
		if(counter >= PORTA_START_CHANNEL_NUMBER && counter < PORTB_START_CHANNEL_NUMBER)
		{
			PinNum = counter;

			if(PortAClockEnabled==FALSE)
			{
				/*Enable clock for PORT A*/
				RCC_EnableClock(RCC_APB2,2);
				PortAClockEnabled = TRUE;
			}

			/*Set the required PORTA pin bits to the initial Mode*/
			if(Port_PortChannels[counter].Ch_Mode!=GPIO)
			{
				if(PinNum<=7)
				{
					GPIOA_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOA_CRL|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOA_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOA_CRH|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
				}
			}



			/*Set the required PORTA pin bits to the initial direction*/
			else
			{
				if(PinNum<=7)
				{
					GPIOA_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOA_CRL|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOA_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOA_CRH|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
				}



				/*Initializing the pin value*/
				if(Port_PortChannels[counter].Ch_Init_Value==STD_LOW)
				{
					CLR_BIT(GPIOA_ODR,PinNum);
				}
				else SET_BIT(GPIOA_ODR,PinNum);
			}


		}



		/*PORT B*/
		if(counter >= PORTB_START_CHANNEL_NUMBER && counter < PORTC_START_CHANNEL_NUMBER)
		{
			PinNum = counter%16;

			if(PortBClockEnabled==FALSE)
			{
				/*Enable clock for PORT B*/
				RCC_EnableClock(RCC_APB2,3);
				PortBClockEnabled = TRUE;
			}

			/*Set the required PORTB pin bits to the initial mode*/
			if(Port_PortChannels[counter].Ch_Mode!=GPIO)
			{
				if(PinNum<=7)
				{
					GPIOB_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOB_CRL|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOB_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOB_CRH|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
				}

			}

			/*Set the required PORTB pin bits to the initial direction*/
			else
			{
				if(PinNum<=7)
				{
					GPIOB_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOB_CRL|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOB_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOB_CRH|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
				}



				/*Initialize the pin value*/
				if(Port_PortChannels[counter].Ch_Init_Value==STD_LOW)
				{
					CLR_BIT(GPIOB_ODR,PinNum);
				}
				else SET_BIT(GPIOB_ODR,PinNum);
			}

		}


		/*PORT C*/
		if(counter >= PORTC_START_CHANNEL_NUMBER)
		{
			PinNum = counter%16;

			if(PortCClockEnabled==FALSE)
			{
				/*Enable clock for PORT C*/
				RCC_EnableClock(RCC_APB2,4);
				PortCClockEnabled = TRUE;
			}


			/*Set the required PORTC pin bits to the initial mode*/
			if(Port_PortChannels[counter].Ch_Mode!=GPIO)
			{
				if(PinNum<=7)
				{
					GPIOC_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOC_CRL|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOC_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOC_CRH|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
				}

			}


			/*Set the required PORTC pin bits to the initial direction*/
			else
			{
				if(PinNum<=7)
				{
					GPIOC_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOC_CRL|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOC_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOC_CRH|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
				}



				/*Initialize the pin value*/
				if(Port_PortChannels[counter].Ch_Init_Value==STD_LOW)
				{
					CLR_BIT(GPIOC_ODR,PinNum);
				}
				else SET_BIT(GPIOC_ODR,PinNum);
			}

		}


	}

  }

}






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
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	  boolean error = FALSE;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)

	  /* Check if the pin number is invalid*/
	  if(Pin >= PORT_CONFIGURED_CHANNELS)
	  {
	    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN );
	    error = TRUE;

	  }
	  else
	  {
	    /* Do nothing*/
	  }

	  /* Check that the initialization is done successfuly*/
	  if(Port_Status == PORT_NOT_INITIALIZED)
	  {
	    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT );
	    error = TRUE;
	  }
	  else
	  {
	    /* Do nothing*/
	  }

	  /* Check if the direction can't be changed in the run time*/
	  if(Port_PortChannels[Pin].PORT_PIN_DIRECTION_CHANGEABLE == STD_LOW)
	  {
	    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE );
	    error = TRUE;
	  }
	  else
	  {
	    /*Do nothing*/
	  }
	#endif

	uint8 PinNum = Pin%16;
	if(error == FALSE)
	{
		if(Pin>= PORTA_START_CHANNEL_NUMBER && Pin < PORTB_START_CHANNEL_NUMBER)
		{

				/*Set the required PORTA pin bits to the given direction*/
				if(PinNum<=7)

				{
					GPIOA_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOA_CRL|=(Direction<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOA_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOA_CRH|=(Direction<<(PinNum*4));
				}



		}


		else if(Pin>= PORTB_START_CHANNEL_NUMBER && Pin < PORTC_START_CHANNEL_NUMBER)
		{

			/*Set the required PORTB pin bits to the given direction*/

				if(PinNum<=7)

				{
					GPIOB_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOB_CRL|=(Direction<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOB_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOB_CRH|=(Direction<<(PinNum*4));
				}



		}



		else if(Pin>= PORTC_START_CHANNEL_NUMBER)
		{

			/*Set the required PORTC pin bits to the given direction*/

				if(PinNum<=7)

				{
					GPIOC_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOC_CRL|=(Direction<<(PinNum*4));
				}
				else if(PinNum<=15)
				{
					GPIOC_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
					GPIOC_CRH|=(Direction<<(PinNum*4));
				}



		}

	}

}


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
void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)

  /* Check that the initialization is done successfuly*/
  if(Port_Status == PORT_NOT_INITIALIZED)
  {
    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT );
  }
  else
#endif
  {

	  uint8 counter = 0;
	  uint8 PinNum = 0;

	  /*Loop on all the controller pins*/
	  for(counter = PORTA_START_CHANNEL_NUMBER; counter<PortNumberOfPortPins; counter++)
	  {
		  /*Refresh Port Pin direction only for those that are non-changeable*/
		  if(Port_PortChannels[counter].PortPinDirectionChangeable==STD_OFF)
		  {
			  /*PORT A*/
			  if(counter >= PORTA_START_CHANNEL_NUMBER && counter < PORTB_START_CHANNEL_NUMBER)
			  {
				  PinNum = counter;

				  /*Set the required PORTA pin bits to the initial Mode*/
				  if(Port_PortChannels[counter].Ch_Mode!=GPIO)
				  {
					  if(PinNum<=7)
					  {
						  GPIOA_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOA_CRL|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
					  }
					  else if(PinNum<=15)
					  {
						  GPIOA_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOA_CRH|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
					  }
				  }


				  /*Set the required PORTA pin bits to the initial direction*/
				  else
				  {
					  if(PinNum<=7)
					  {
						  GPIOA_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOA_CRL|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
					  }
					  else if(PinNum<=15)
					  {
						  GPIOA_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOA_CRH|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
					  }




					  /*Initializing the pin value*/
					  if(Port_PortChannels[counter].Ch_Init_Value==STD_LOW)
					  {
						  CLR_BIT(GPIOA_ODR,PinNum);
					  }
					  else SET_BIT(GPIOA_ODR,PinNum);
				  }

			  }



			  /*PORT B*/
			  if(counter >= PORTB_START_CHANNEL_NUMBER && counter < PORTC_START_CHANNEL_NUMBER)
			  {
				  PinNum = counter%16;

				  /*Set the required PORTB pin bits to the initial mode*/
				  if(Port_PortChannels[counter].Ch_Mode!=GPIO)
				  {
					  if(PinNum<=7)
					  {
						  GPIOB_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOB_CRL|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
					  }
					  else if(PinNum<=15)
					  {
						  GPIOB_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOB_CRH|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
					  }
				  }



				  /*Set the required PORTB pin bits to the initial direction*/
				  else
				  {
					  if(PinNum<=7)
					  {
						  GPIOB_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOB_CRL|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
					  }
					  else if(PinNum<=15)
					  {
						  GPIOB_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOB_CRH|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
					  }


					  /*Initialize the pin value*/
					  if(Port_PortChannels[counter].Ch_Init_Value==STD_LOW)
					  {
						  CLR_BIT(GPIOB_ODR,PinNum);
					  }
					  else SET_BIT(GPIOB_ODR,PinNum);
				  }

			  }


			  /*PORT C*/
			  if(counter >= PORTC_START_CHANNEL_NUMBER)
			  {
				  PinNum = counter%16;


				  /*Set the required PORTC pin bits to the initial mode*/
				  if(Port_PortChannels[counter].Ch_Mode!=GPIO)
				  {
					  if(PinNum<=7)
					  {
						  GPIOC_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOC_CRL|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
					  }
					  else if(PinNum<=15)
					  {
						  GPIOC_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOC_CRH|=(Port_PortChannels[counter].Ch_Mode<<(PinNum*4));
					  }
				  }


				  /*Set the required PORTC pin bits to the initial mode*/
				  else
				  {
					  if(PinNum<=7)
					  {
						  GPIOC_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOC_CRL|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
					  }
					  else if(PinNum<=15)
					  {
						  GPIOC_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
						  GPIOC_CRH|=(Port_PortChannels[counter].Ch_Direction<<(PinNum*4));
					  }



					  /*Initialize the pin value*/
					  if(Port_PortChannels[counter].Ch_Init_Value==STD_LOW)
					  {
						  CLR_BIT(GPIOC_ODR,PinNum);
					  }
					  else SET_BIT(GPIOC_ODR,PinNum);
				  }


			  }


		  }



	  }



  }

}




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
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif


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

void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
	  boolean error = FALSE;
	#if (PORT_DEV_ERROR_DETECT == STD_ON)

	  /* Check if the pin number is invalid*/
	  if(Pin >= PORT_CONFIGURED_CHANNELS)
	  {
	    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN );
	    error = TRUE;

	  }
	  else
	  {
	    /* Do nothing*/
	  }

	  /* Check that the initialization is done successfuly*/
	  if(Port_Status == PORT_NOT_INITIALIZED)
	  {
	    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT );
	    error = TRUE;
	  }
	  else
	  {
	    /* Do nothing*/
	  }

	  /* Check if the direction can't be changed in the run time*/
	  if(Port_PortChannels[Pin].PORT_PIN_MODE_CHANGEABLE == STD_LOW)
	  {
	    Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE );
	    error = TRUE;
	  }
	  else
	  {
	    /*Do nothing*/
	  }
	#endif

	  uint8 PinNum = Pin%16;
	  if(error == FALSE)
	  {
		  if(Pin>= PORTA_START_CHANNEL_NUMBER && Pin < PORTB_START_CHANNEL_NUMBER)
		  {

			  /*Set the required PORTA pin bits to the given Mode*/
			  if(PinNum<=7)

			  {
				  GPIOA_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
				  GPIOA_CRL|=(Mode<<(PinNum*4));
			  }
			  else if(PinNum<=15)
			  {
				  GPIOA_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
				  GPIOA_CRH|=(Mode<<(PinNum*4));
			  }



		  }


		  else if(Pin>= PORTB_START_CHANNEL_NUMBER && Pin < PORTC_START_CHANNEL_NUMBER)
		  {

			  /*Set the required PORTB pin bits to the given Mode*/

			  if(PinNum<=7)

			  {
				  GPIOB_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
				  GPIOB_CRL|=(Mode<<(PinNum*4));
			  }
			  else if(PinNum<=15)
			  {
				  GPIOB_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
				  GPIOB_CRH|=(Mode<<(PinNum*4));
			  }



		  }



		  else if(Pin>= PORTC_START_CHANNEL_NUMBER)
		  {

			  /*Set the required PORTC pin bits to the given Mode*/

			  if(PinNum<=7)

			  {
				  GPIOC_CRL&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
				  GPIOC_CRL|=(Mode<<(PinNum*4));
			  }
			  else if(PinNum<=15)
			  {
				  GPIOC_CRH&=~((PORT_PIN_CFG_REG_MASK)<<(PinNum*4));
				  GPIOC_CRH|=(Mode<<(PinNum*4));
			  }



		  }

	  }
}

