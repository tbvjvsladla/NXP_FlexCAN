/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : canCom7.h
**     Project     : CAN_FD_PIT_MPC5748G_GW_RDB_2
**     Processor   : MPC5748G_176
**     Component   : flexcan
**     Version     : Component SDK_S32_PA_11, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32_PA_11
**     Compiler    : GNU C Compiler
**     Date/Time   : 2023-01-25, 14:09, # CodeGen: 3
**     Contents    :
**         FLEXCAN_DRV_SetBitrate             - void FLEXCAN_DRV_SetBitrate(uint8_t instance,const flexcan_time_segment_t *...
**         FLEXCAN_DRV_GetBitrate             - void FLEXCAN_DRV_GetBitrate(uint8_t instance,flexcan_time_segment_t * bitrate);
**         FLEXCAN_DRV_SetRxMaskType          - void FLEXCAN_DRV_SetRxMaskType(uint8_t instance,flexcan_rx_mask_type_t type);
**         FLEXCAN_DRV_SetRxFifoGlobalMask    - void FLEXCAN_DRV_SetRxFifoGlobalMask(uint8_t...
**         FLEXCAN_DRV_SetRxMbGlobalMask      - void FLEXCAN_DRV_SetRxMbGlobalMask(uint8_t instance,flexcan_msgbuff_id_type_t...
**         FLEXCAN_DRV_SetRxIndividualMask    - status_t FLEXCAN_DRV_SetRxIndividualMask(uint8_t...
**         FLEXCAN_DRV_Init                   - status_t FLEXCAN_DRV_Init(uint8_t instance,flexcan_state_t * state,const...
**         FLEXCAN_DRV_Deinit                 - status_t FLEXCAN_DRV_Deinit(uint8_t instance);
**         FLEXCAN_DRV_ConfigTxMb             - status_t FLEXCAN_DRV_ConfigTxMb(uint8_t instance,uint8_t mb_idx,const...
**         FLEXCAN_DRV_ConfigRemoteResponseMb - status_t FLEXCAN_DRV_ConfigRemoteResponseMb(uint8_t instance,uint8_t...
**         FLEXCAN_DRV_SendBlocking           - status_t FLEXCAN_DRV_SendBlocking(uint8_t instance,uint8_t mb_idx,const...
**         FLEXCAN_DRV_Send                   - status_t FLEXCAN_DRV_Send(uint8_t instance,uint8_t mb_idx,const...
**         FLEXCAN_DRV_AbortTransfer          - status_t FLEXCAN_DRV_AbortTransfer(uint8_t instance,uint8_t mb_idx);
**         FLEXCAN_DRV_ConfigRxMb             - status_t FLEXCAN_DRV_ConfigRxMb(uint8_t instance,uint8_t mb_idx,const...
**         FLEXCAN_DRV_ConfigRxFifo           - void FLEXCAN_DRV_ConfigRxFifo(uint8_t i...
**         FLEXCAN_DRV_ReceiveBlocking        - status_t FLEXCAN_DRV_ReceiveBlocking(uint8_t instance,uint8_t...
**         FLEXCAN_DRV_Receive                - status_t FLEXCAN_DRV_Receive(uint8_t instance,uint8_t...
**         FLEXCAN_DRV_RxFifoBlocking         - status_t FLEXCAN_DRV_RxFifoBlocking(uint8_t instance,flexcan_msgbuff_t *...
**         FLEXCAN_DRV_RxFifo                 - status_t FLEXCAN_DRV_RxFifo(uint8_t instance,flexcan_msgbuff_t * data);
**         FLEXCAN_DRV_GetTransferStatus      - status_t FLEXCAN_DRV_GetTransferStatus(uint8_t instance,uint8_t mb_idx);
**         FLEXCAN_DRV_InstallErrorCallback   - void FLEXCAN_DRV_InstallErrorCallback(uint8_t...
**         FLEXCAN_DRV_InstallEventCallback   - void FLEXCAN_DRV_InstallEventCallback(uint8_t instance,flexcan_callback_t...
**         FLEXCAN_DRV_GetDefaultConfig       - void FLEXCAN_DRV_GetDefaultConfig(flexcan_user_config_t * config);
**         FLEXCAN_DRV_SetRxMb14Mask          - void FLEXCAN_DRV_SetRxMb14Mask(uint8_t instance, flexcan_msgbuff_id_type_t...
**         FLEXCAN_DRV_SetRxMb15Mask          - void FLEXCAN_DRV_SetRxMb15Mask(uint8_t instance, flexcan_msgbuff_id_type_t...
**         FLEXCAN_DRV_GetErrorStatus         - uint32_t FLEXCAN_DRV_GetErrorStatus(uint8_t instance);
**         FLEXCAN_DRV_ConfigPN               - void FLEXCAN_DRV_ConfigPN(uint8_t instance,bool enable,const...
**         FLEXCAN_DRV_GetWMB                 - void FLEXCAN_DRV_GetWMB(uint8_t instance, uint8_t wmbIndex, flexcan_msgbuff_t...
**         FLEXCAN_DRV_SetBitrateCbt          - void FLEXCAN_DRV_SetBitrateCbt(uint8_t instance,const flexcan_time_segment_t...
**         FLEXCAN_DRV_GetBitrateFD           - void FLEXCAN_DRV_GetBitrateFD(uint8_t instance,flexcan_time_segment_t *...
**         FLEXCAN_DRV_SetTDCOffset           - void FLEXCAN_DRV_SetTDCOffset(uint8_t instance, bool enable, uint8_t offset);
**         FLEXCAN_DRV_GetTDCValue            - uint8_t FLEXCAN_DRV_GetTDCValue(uint8_t instance);
**         FLEXCAN_DRV_GetTDCFail             - bool FLEXCAN_DRV_GetTDCFail(uint8_t instance);
**         FLEXCAN_DRV_ClearTDCFail           - void FLEXCAN_DRV_ClearTDCFail(uint8_t instance);
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
** @file canCom7.h
** @version 01.00
*/         
/*!
**  @addtogroup canCom7_module canCom7 module documentation
**  @{
*/         
/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 8.1, types should be explicitly specified  
 * This rule applies only for C90 standard. Defining other integer types that are 
 * permitted in bit-field declarations is allowed in C99 standard.
 * 
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 2.5, Global macro not referenced.
 * This is required to enable the use of a macro needed by the application (even
 * if the macro is not used inside the driver code).
 *
 */
#ifndef canCom7_H
#define canCom7_H
/* MODULE canCom7. */

/* Include inherited beans */
#include "clockMan1.h"
#include "dmaController1.h"
#include "Cpu.h"

/*! @brief Device instance number */
#define INST_CANCOM7 (6U)
/*! @brief Driver state structure which holds driver runtime data */
extern flexcan_state_t canCom7_State; 
extern const flexcan_user_config_t canCom7_InitConfig0;


#endif
/* ifndef canCom7_H */
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

