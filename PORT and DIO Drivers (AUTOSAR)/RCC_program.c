#include "std_types.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"


void RCC_InitSysClock()
{
#if RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
	RCC_CR=0x0001000;           /*Enable HSE with no bypass*/
	RCC_CFGR=0x00000001;

#elif	RCC_CLOCK_TYPE == RCC_HSE_RC
	RCC_CR=0x0005000;          /*Enable HSE with bypass*/
	RCC_CFGR=0x00000001;

#elif	RCC_CLOCK_TYPE == RCC_HSI
	RCC_CR=0x0000001;         /*Enable HSI*/
	RCC_CFGR=0x00000000;

#elif	RCC_CLOCK_TYPE == RCC_PLL

	#if RCC_PLL_INPUT== RCC_PLL_IN_HSI_DIV2
		RCC_CR=0x01000001;         /*Enable PLL with HSI/2*/
		RCC_CFGR=0x00000010;

	#elif RCC_PLL_INPUT== RCC_PLL_IN_HSE_DIV2
		RCC_CR=0x0101000;         /*Enable PLL with HSE/2*/
		RCC_CFGR=0x00030010;

	#elif RCC_PLL_INPUT== RCC_PLL_IN_HSE
		RCC_CR=0x0101000;         /*Enable PLL with HSE*/
		RCC_CFGR=0x00010010;

	#endif

#else #error("You chose wrong clock type")
#endif
}


void RCC_EnableClock (uint8 Copy_BusID,uint8 Copy_perID)
{
	if(Copy_perID<=31)
	{
		switch(Copy_BusID)
		{
		case RCC_AHB: SET_BIT(RCC_AHBENR,Copy_perID);
		break;
		case RCC_APB1: SET_BIT(RCC_APB1ENR,Copy_perID);
		break;
		case RCC_APB2: SET_BIT(RCC_APB2ENR,Copy_perID);
		break;
		}
	}

}

void RCC_DisableClock (uint8 Copy_BusID,uint8 Copy_perID)
{
	if(Copy_perID<=31)
	{
		switch(Copy_BusID)
		{
		case RCC_AHB: CLR_BIT(RCC_AHBENR,Copy_perID);
		break;
		case RCC_APB1: CLR_BIT(RCC_APB1ENR,Copy_perID);
		break;
		case RCC_APB2: CLR_BIT(RCC_APB2ENR,Copy_perID);
		break;
		}
	}

}
