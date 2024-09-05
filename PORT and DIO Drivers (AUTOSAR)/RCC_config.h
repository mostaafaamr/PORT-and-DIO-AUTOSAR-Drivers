/*
 * RCC_config.h
 *
 *  Created on: Aug 2, 2023
 *      Author: Mostafa Amr
 */

#ifndef RCC_CONFIG_H_
#define RCC_CONFIG_H_


/*Options:  RCC_HSE_CRYSTAL
 * 			RCC_HSE_RC
 * 			RCC_HSI
 * 			RCC_PLL
*/
#define RCC_CLOCK_TYPE RCC_HSE_RC


/*Options:  RCC_PLL_IN_HSI_DIV2
 * 			RCC_PLL_IN_HSE_DIV2
 * 			RCC_PLL_IN_HSE
*/

#if RCC_CLOCK_TYPE==RCC_PLL
#define RCC_PLL_INPUT RCC_PLL_IN_HSE
#endif

/*Options: 6.5 and 4 to 9*/
#if RCC_CLOCK_TYPE==RCC_PLL
#define RCC_PLL_MUL_VAL 4
#endif

#endif /* RCC_CONFIG_H_ */
