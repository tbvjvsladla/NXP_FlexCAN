/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : pit1.h
**     Project     : CAN_FD_PIT_MPC5748G_GW_RDB_2
**     Processor   : MPC5748G_176
**     Component   : pit
**     Version     : Component SDK_S32_PA_11, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32_PA_11
**     Compiler    : GNU C Compiler
**     Date/Time   : 2023-01-25, 14:01, # CodeGen: 2
**     Contents    :
**         PIT_DRV_GetDefaultConfig        - void PIT_DRV_GetDefaultConfig(pit_config_t * const config);
**         PIT_DRV_GetDefaultChanConfig    - void PIT_DRV_GetDefaultChanConfig(pit_channel_config_t * const config);
**         PIT_DRV_Init                    - void PIT_DRV_Init(const uint32_t instance, const pit_config_t * const config);
**         PIT_DRV_Deinit                  - void PIT_DRV_Deinit(const uint32_t instance);
**         PIT_DRV_InitChannel             - status_t PIT_DRV_InitChannel(const uint32_t instance, const...
**         PIT_DRV_ConfigChannel           - status_t PIT_DRV_ConfigChannel(const uint32_t instance, const uint8_t...
**         PIT_DRV_StartChannel            - void PIT_DRV_StartChannel(const uint32_t instance, const uint8_t channel);
**         PIT_DRV_StopChannel             - void PIT_DRV_StopChannel(const uint32_t instance, const uint8_t channel);
**         PIT_DRV_SetTimerPeriodByUs      - status_t PIT_DRV_SetTimerPeriodByUs(const uint32_t instance, const uint8_t...
**         PIT_DRV_GetCurrentTimerUs       - uint64_t PIT_DRV_GetCurrentTimerUs(const uint32_t instance, const uint8_t...
**         PIT_DRV_SetTimerPeriodByCount   - void PIT_DRV_SetTimerPeriodByCount(const uint32_t instance, const uint8_t...
**         PIT_DRV_GetCurrentTimerCount    - uint32_t PIT_DRV_GetCurrentTimerCount(const uint32_t instance, const uint8_t...
**         PIT_DRV_SetLifetimeTimerCount   - uint64_t PIT_DRV_SetLifetimeTimerCount(const uint32_t instance);
**         PIT_DRV_GetLifetimeTimerCount   - uint64_t PIT_DRV_GetLifetimeTimerCount(const uint32_t instance);
**         PIT_DRV_GetLifetimeTimerUs      - uint64_t PIT_DRV_GetLifetimeTimerUs(const uint32_t instance);
**         PIT_DRV_EnableChannelInterrupt  - void PIT_DRV_EnableChannelInterrupt(const uint32_t instance, const uint8_t...
**         PIT_DRV_DisableChannelInterrupt - void PIT_DRV_DisableChannelInterrupt(const uint32_t instance, const uint8_t...
**         PIT_DRV_GetStatusFlags          - uint32_t PIT_DRV_GetStatusFlags(const uint32_t instance, const uint8_t channel);
**         PIT_DRV_ClearStatusFlags        - void PIT_DRV_ClearStatusFlags(const uint32_t instance, const uint8_t channel);
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc. 
**     Copyright 2016-2017 NXP 
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file pit1.h
** @version 01.00
*/         
/*!
**  @addtogroup pit1_module pit1 module documentation
**  @{
*/         
#ifndef pit1_H
#define pit1_H

/* MODULE pit1.
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * The global macro will be used in function call of the module.
 */

/* Include inherited beans */
#include "clockMan1.h"
#include "Cpu.h"
#include "pit_driver.h"

/*! Device instance number */
#define INST_PIT1 (0U)

/*! Global configuration of pit1 */
extern const pit_config_t  pit1_InitConfig;
/*! User channel configuration 0 */
extern pit_channel_config_t pit1_ChnConfig0;
/*! User channel configuration 1 */
extern pit_channel_config_t pit1_ChnConfig1;
/*! User channel configuration 2 */
extern pit_channel_config_t pit1_ChnConfig2;
/*! User channel configuration 3 */
extern pit_channel_config_t pit1_ChnConfig3;
/*! User channel configuration 4 */
extern pit_channel_config_t pit1_ChnConfig4;
/*! User channel configuration 5 */
extern pit_channel_config_t pit1_ChnConfig5;
/*! User channel configuration 6 */
extern pit_channel_config_t pit1_ChnConfig6;
/*! User channel configuration 7 */
extern pit_channel_config_t pit1_ChnConfig7;

#endif
/* END pit1 */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP C55 series of microcontrollers.
**
** ###################################################################
*/

