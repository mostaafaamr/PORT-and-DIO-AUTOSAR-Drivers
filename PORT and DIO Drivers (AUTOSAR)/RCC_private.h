/*
 * RCC_private.h
 *
 *  Created on: Aug 2, 2023
 *      Author: Mostafa Amr
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/*RCC Registers*/
#define RCC_CR                 *((volatile uint32*)0x40021000)
#define RCC_CFGR               *((volatile uint32*)0x40021004)
#define RCC_CIR                *((volatile uint32*)0x40021008)
#define RCC_APB2RSTR           *((volatile uint32*)0x4002100C)
#define RCC_APB1RSTR           *((volatile uint32*)0x40021010)
#define RCC_AHBENR             *((volatile uint32*)0x40021014)
#define RCC_APB2ENR            *((volatile uint32*)0x40021018)
#define RCC_APB1ENR            *((volatile uint32*)0x4002101C)
#define RCC_BDCR               *((volatile uint32*)0x40021020)
#define RCC_CSR                *((volatile uint32*)0x40021024)
#define RCC_AHBSTR             *((volatile uint32*)0x40021028)
#define RCC_CFGR2              *((volatile uint32*)0x4002102C)


/*Clock Types*/
#define RCC_HSE_CRYSTAL 0
#define RCC_HSE_RC 1
#define RCC_HSI 2
#define RCC_PLL 3

/*PLL Options*/
#define RCC_PLL_IN_HSI_DIV2 0
#define RCC_PLL_IN_HSE_DIV2 1
#define RCC_PLL_IN_HSE 2




#endif /* RCC_PRIVATE_H_ */
