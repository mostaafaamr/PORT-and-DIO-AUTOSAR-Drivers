/*
 * RCC_interface.h
 *
 *  Created on: Aug 2, 2023
 *      Author: Mostafa Amr
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

#define RCC_AHB 0
#define RCC_APB1 1
#define RCC_APB2 2

void RCC_EnableClock (uint8 Copy_BusID,uint8 Copy_perID);

void RCC_InitSysClock();

void RCC_DisableClock (uint8 Copy_BusID,uint8 Copy_perID);

#endif /* RCC_INTERFACE_H_ */
