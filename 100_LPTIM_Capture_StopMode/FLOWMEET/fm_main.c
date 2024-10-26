/*
 * @brief 	Este proyecto se crea para investigar porque los LPTIM, usados en el modo captura, fallan de la siguiente manera:
 * 			Usando un GPIO como disparo para la captura, si el micro esta en bajo consumo. el CCRx se actualiza correctamente
 * 			si la cantida de pulsos recibidos fue impar, pero el CCRx se mantiene congelado, no se actualiza, si la cantidad
 * 			de pulsos recibidos fuer par, lo anterior hace evidente que el CCRx realemnte se actualiza, seguramente por medio
 * 			de un registro shadow, al desperatar el micro, esta actualizacion falla para en la situacion mencionada.
 * 			La forma de solucionar lo anterior es borrando un resgistro, el de over-caputre.
 *
 * Fecha: 11/10/2024
 * Version: 1
 * Modificaiones.
 */

// Includes.
#include "fm_main.h"
#include "fm_debug.h"
#include "main.h"

// Typedef.

// Const data.

// Defines.

// Debug.

// Project variables, non-static, at least used in other file.

// External variables.
extern LPTIM_HandleTypeDef hlptim1;

// Global variables, statics.

// Private function prototypes.

// Private function bodies.

// Public function bodies.

/*
 * @brief   Loop infinito flowmeet.
 * @Note    El programa princial se derarrolla en este modulo. No escribir codigo en archivos
 *          generados automaticamente por los IDEs.
 * @param   Ninguno.
 * @retval  Ninguno.
 *
 */
void FM_MAIN_Main()
{
	uint16_t capture;

	HAL_LPTIM_IC_Start(&hlptim1, LPTIM_CHANNEL_1);
	__HAL_RCC_LPTIM1_CLKAM_ENABLE();

	HAL_Delay(100);

	for (;;)
	{
		//LL_LPTIM_ClearFlag_CC1O(LPTIM1);

		capture=LPTIM1->CCR1;
		FM_DEBUG_UartUint16(capture);

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_SuspendTick();
		HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
		HAL_ResumeTick();
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	}
}

// Interrupts


/*** end of file ***/

