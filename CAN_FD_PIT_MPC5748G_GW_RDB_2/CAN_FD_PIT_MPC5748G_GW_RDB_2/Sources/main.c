/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/* ###################################################################
**     Filename    : main.c
**     Project     : CANFD_PIT_MPC5748G_GW_RDB
**     Processor   : MPC5748G_324
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2017-03-14, 14:08, # CodeGen: 1
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "pit1.h"			/**Ÿ�̸� ���ͷ�Ʈ, Ŭ���Ŵ��� 1���� 8�� ä�� ����**/
#include "clockMan1.h"		/**CAN �� Ÿ�̸� ���� Ŭ�� �Ŵ�����Ʈ�� ������ �����Ǿ�� ��**/
#include "pin_mux.h"

#include "canCom1.h"		/**CAN���������� canCom1 ����� �ִ���**/
#include "canCom2.h"		/**�ڵ� �� ��Ȳ ���� Ȱ��ȭ�� ä�� �� �־�� �ϴ°� ����**/
#include "canCom3.h"
#include "canCom4.h"
#include "canCom5.h"
#include "canCom6.h"
#include "canCom7.h"
#include "canCom8.h"

  volatile int exit_code = 0;
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdint.h>
#include <stdbool.h>

  /**FlexCAN ������ ���� ��Ȱ�� ���� TX, RX�޼��� ���� ���Ǹ� �״�� �ܾ�� **/
  #define MASTER
  #if defined(MASTER)
      #define TX_MAILBOX  (1UL)
      #define TX_MSG_ID   (1UL)
      #define RX_MAILBOX  (0UL)
      #define RX_MSG_ID   (2UL)
  #elif defined(SLAVE)
      #define TX_MAILBOX  (0UL)
      #define TX_MSG_ID   (2UL)
      #define RX_MAILBOX  (1UL)
      #define RX_MSG_ID   (1UL)
  #endif
  /**�׷��� FlexCAN�� ���Ϲڽ��� �����ϰ� �� �� �ִٶ�� ������ ������ �ְ� CAN�� ������/�����̺� **/
  /**���䵵 ���⿡ � �ǹ̰� �ִ��� �𸣰��� TX_MAILBOX�� RX_MAILBOX�� 8���� �� 16��**/
  /**�� ���Ƿ� ���� �ɰ� ������ ��..**/

  /**������ ������ CAN ä�� ��ũ��**/
  #define CH_1 (0U)
  #define CH_2 (1U)
  #define CH_3 (2U)
  #define CH_4 (3U)
  #define CH_5 (4U)
  #define CH_6 (5U)
  #define CH_7 (6U)
  #define CH_8 (7U)


  #define CAN_SEND
  #define CAN_RECEIVE

  /**SendCANData �Լ��� ä�κ��� ���� ������������ ä�θ� �Ű������� ����**/
  #ifdef CAN_SEND
  void SendCANData(uint8_t can_ch, uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len);
  #endif

  void BoardInit(void);
  /**MPC5748G GW RDB ����� �Ʒ� �� �Լ��� ������ ����� -> MPC5748G DEV kit���� ������**/
  void Peripheral_Power_Supply_Init(void);
  void CAN_TJA1043T_Enable(void);

  void PIT_FlexCan_Init(void);


  /**Ÿ�̸� ���ͷ�Ʈ �Լ� ����� ���� �ܾ�� ������ �Լ� -> �ٵ� �̰� Ŭ�����ǵ��ε� �ð���???**/
  void delay(volatile int cycles)
  {
      /* Delay function - do nothing for a number of cycles */
      while(cycles--);
      //delay(720000);	//Insert a small delay to make the blinking visible
  }

  /*��� ���ϴ� �ѱ۷� �����ؼ� ����..
   *SendCANData �Լ��� 4���� �Ű����� �Է�, ��ȯ�� ���� �����̴�.
   *�Ű����� 1: Ư�� mailbox ��ȣ -> �̰Ŷ����� ������ ���Ϲڽ� �ƹ��ų� �����ص� �ǳ�??
   *�Ű����� 2: �޼��� ID -> Standard message ID��� ǥ���Ȱ� ���� CAN ������ �޽��� ID�� �ǹ��ϴµ�
   *�Ű����� 3: CAN ������ �ʵ忡 ���� ���� -> FD�ϱ� �ִ� 64byte¥�� �迭����
   *�Ű����� 4: ������ �ʵ��� ���� -> FD�ϱ� �ִ� 64, ���̿����� 32������ ��
   */
  #ifdef CAN_SEND
  void SendCANData(uint8_t can_ch, uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len)
  {
  	/**���� �Ʒ� ����ü ������ �ٸ� c���Ͽ� ����Ǵµ� **/
  	/**��.. �ƹ�ư ������ CAN�����Ͱ� ��� �������� �˷��ִ� ������ ��� ����ü�̴�..**/
      flexcan_data_info_t dataInfo =
      {
              .data_length = len,		//������ ����
              .msg_id_type = FLEXCAN_MSG_ID_STD,	//ǥ�� CAN ID
              .enable_brs  = true,	//������ ���׸�Ʈ�� ���� �ٸ� ��Ʈ ���۷��� ����ϵ��� Ȱ��ȭ�� ��Ʈ���۷� ����ġ???
              .fd_enable   = true,	//������ ������ �ӵ�
              .fd_padding  = 0U		//FD �е��� 0�� -> �е���Ʈ�� ���� ������ �ʵ� ���̰� �׽ð�����??
      };

      /**����� ���� can ���ä�κ��� �����Ϸ��� ���� �ڵ� -> ������ ����������? **/
      switch (can_ch)
      {
      	case CH_1 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM1, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN0*/
      		break;
      	case CH_2 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM2, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN1*/
      		break;
      	case CH_3 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM3, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN2*/
      		break;
      	case CH_4 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM4, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN3*/
      		break;
      	case CH_5 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM5, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN4*/
      		break;
      	case CH_6 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM6, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN5*/
      		break;
      	case CH_7 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM7, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN6*/
      		break;
      	case CH_8 :
      		while(FLEXCAN_DRV_Send(INST_CANCOM8, mailbox, &dataInfo, messageId, data) == STATUS_BUSY);  /*CAN7*/
      		break;
      	default :
      		break;
      }
  }
  #endif

  /**Ÿ�̸� ���ͷ�Ʈ ����� ���� flag��������**/
  uint8_t can_tx_periodic_flag[8] = {0};

  /**startup_MPC5748G.S�� ���ǵ� Periodic Interrupt Timer (PIT0~7)**/
  void PIT_Ch0_IRQHandler(void)
  {
  	can_tx_periodic_flag[0] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig0.hwChannel);     /* Clear channel 0 interrupt flag */
  }
  void PIT_Ch1_IRQHandler(void)
  {
  	can_tx_periodic_flag[1] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig1.hwChannel);     /* Clear channel 0 interrupt flag */
  }
  void PIT_Ch2_IRQHandler(void)
  {
  	can_tx_periodic_flag[2] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig2.hwChannel);     /* Clear channel 0 interrupt flag */
  }
  void PIT_Ch3_IRQHandler(void)
  {
  	can_tx_periodic_flag[3] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig3.hwChannel);     /* Clear channel 0 interrupt flag */
  }
  void PIT_Ch4_IRQHandler(void)
  {
  	can_tx_periodic_flag[4] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig4.hwChannel);     /* Clear channel 0 interrupt flag */
  }
  void PIT_Ch5_IRQHandler(void)
  {
  	can_tx_periodic_flag[5] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig5.hwChannel);     /* Clear channel 0 interrupt flag */
  }
  void PIT_Ch6_IRQHandler(void)
  {
  	can_tx_periodic_flag[6] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig6.hwChannel);     /* Clear channel 0 interrupt flag */
  }
  void PIT_Ch7_IRQHandler(void)
  {
  	can_tx_periodic_flag[7] = true;
  	PIT_DRV_ClearStatusFlags(INST_PIT1, pit1_ChnConfig7.hwChannel);     /* Clear channel 0 interrupt flag */
  }


  /*
   * @brief : Initialize clocks, pins and power modes
   */
  void BoardInit(void) //�߰� �ʱ�ȭ �� ������ �ٸ� �Լ��� ����
  {

      /* Initialize and configure clocks
       *  -   Setup system clocks, dividers
       *  -   Configure FlexCAN clock, GPIO, LPSPI
       *  -   see clock manager component for more details
       */
      CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,
                     g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
      CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_FORCIBLE);

      /* Initialize pins -> FlexCAN */
      PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
  }


  void Peripheral_Power_Supply_Init(void)
  {
      PINS_DRV_WritePin(PTD, 12, 1);
      PINS_DRV_WritePin(PTD, 13, 1);
  }

  void CAN_TJA1043T_Enable(void)
  {
  	PINS_DRV_WritePin(PTB, 3, 1);     /* Initialize high CAN4 EN */
  	PINS_DRV_WritePin(PTA, 2, 1);     /* Initialize high CAN5 EN */
  	PINS_DRV_WritePin(PTG, 9, 1);     /* Initialize high CAN6 EN */
  	PINS_DRV_WritePin(PTH, 14, 1);    /* Initialize high CAN7 EN */

  	PINS_DRV_WritePin(PTJ, 4, 1);     /* Initialize high CAN4 STB */
  	PINS_DRV_WritePin(PTE, 10, 1);    /* Initialize high CAN5 STB */
  	PINS_DRV_WritePin(PTF, 12, 1);    /* Initialize high CAN6 STB */
  	PINS_DRV_WritePin(PTI, 7, 1);     /* Initialize high CAN7 STB */
  }

  /**PIT �� flexcan �ʱ�ȭ �� ������ ���� �Լ��� ����**/
  void PIT_FlexCan_Init(void)
  {
      PIT_DRV_Init(INST_PIT1, &pit1_InitConfig);	/* Initialize PIT */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig0);	/* Initialize PIT channel 0 */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig1);	/* Initialize PIT channel 1 */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig2);	/* Initialize PIT channel 2 */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig3);	/* Initialize PIT channel 3 */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig4);	/* Initialize PIT channel 4 */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig5);	/* Initialize PIT channel 5 */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig6);	/* Initialize PIT channel 6 */
      PIT_DRV_InitChannel(INST_PIT1, &pit1_ChnConfig7);	/* Initialize PIT channel 7 */

      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig0.hwChannel);	/* Start channel 1 counting */
      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig1.hwChannel);	/* Start channel 2 counting */
      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig2.hwChannel);	/* Start channel 3 counting */
      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig3.hwChannel);	/* Start channel 4 counting */
      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig4.hwChannel);	/* Start channel 5 counting */
      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig5.hwChannel);	/* Start channel 6 counting */
      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig6.hwChannel);	/* Start channel 7 counting */
      PIT_DRV_StartChannel(INST_PIT1, pit1_ChnConfig7.hwChannel);	/* Start channel 8 counting */

      /* Initialize FlexCAN driver */
      FLEXCAN_DRV_Init(INST_CANCOM1, &canCom1_State, &canCom1_InitConfig0);  //CAN0
      FLEXCAN_DRV_Init(INST_CANCOM2, &canCom2_State, &canCom2_InitConfig0);  //CAN1
      FLEXCAN_DRV_Init(INST_CANCOM3, &canCom3_State, &canCom3_InitConfig0);  //CAN2
      FLEXCAN_DRV_Init(INST_CANCOM4, &canCom4_State, &canCom4_InitConfig0);  //CAN3
      FLEXCAN_DRV_Init(INST_CANCOM5, &canCom5_State, &canCom5_InitConfig0);  //CAN4
      FLEXCAN_DRV_Init(INST_CANCOM6, &canCom6_State, &canCom6_InitConfig0);  //CAN5
      FLEXCAN_DRV_Init(INST_CANCOM7, &canCom7_State, &canCom7_InitConfig0);  //CAN6
      FLEXCAN_DRV_Init(INST_CANCOM8, &canCom8_State, &canCom8_InitConfig0);  //CAN7

      /**CAN ����� TX�� RX ���۸� �����ϴ� �Լ�**/
  	#ifdef CAN_RECEIVE
      /**�̰Ÿ� main������ ���� ���� : CANä�κ��� �����Ѱ� �ٸ� �� �ֱ�빮��**/
      /**�����̾� ��δ� CAN FD �������� �������ϱ� �Ѱ� �������� ������, �ٸ��� ����ü ������ ������ ��������**/
      flexcan_data_info_t RXdataInfo =
      {
              .data_length = 64U,
              .msg_id_type = FLEXCAN_MSG_ID_STD,
              .enable_brs  = true,
              .fd_enable   = true,
              .fd_padding  = 0U
      };
      /* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM1, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM2, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM3, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM4, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM5, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM6, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM7, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);
      FLEXCAN_DRV_ConfigRxMb(INST_CANCOM8, RX_MAILBOX, &RXdataInfo, RX_MSG_ID);

      #elif defined CAN_SEND
      /**�ռ� ������ RX���Ǳ׿� ����ϴ°Ŷ� ������ ����ü**/
      flexcan_data_info_t TXdataInfo =
      {
              .data_length = 64U,
              .msg_id_type = FLEXCAN_MSG_ID_STD,
              .enable_brs  = true,
              .fd_enable   = true,
              .fd_padding  = 0U
      };

      /* Configure TX message buffer with index TX_MSG_ID and TX_MAILBOX*/
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM1, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM2, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM3, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM4, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM5, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM6, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM7, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      FLEXCAN_DRV_ConfigTxMb(INST_CANCOM8, TX_MAILBOX, &TXdataInfo, TX_MSG_ID);
      #endif
  }



  /*!
    \brief The main function for the project.
    \details The startup initialization sequence is the following:
   * - startup asm routine
   * - main()
  */
int main(void)
{
	/* Write your local variable definition here */
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
    /*** End of Processor Expert internal initialization.                    ***/

    /* Do the initializations required for this application */
    BoardInit();
    Peripheral_Power_Supply_Init();
    CAN_TJA1043T_Enable();
    /**�߰��� ������ FlexCAN ��  PIT �ʱ�ȭ&start �Լ�**/
    PIT_FlexCan_Init();

    while(1)
    {
	  #ifdef CAN_RECEIVE
    	/* Define receive buffer */
    	flexcan_msgbuff_t recvBuff;

//    	/* Start receiving data in RX_MAILBOX. */
//    	FLEXCAN_DRV_Receive(INST_CANCOM1, RX_MAILBOX, &recvBuff);
//    	FLEXCAN_DRV_Receive(INST_CANCOM2, RX_MAILBOX, &recvBuff);
//    	FLEXCAN_DRV_Receive(INST_CANCOM3, RX_MAILBOX, &recvBuff);
//    	FLEXCAN_DRV_Receive(INST_CANCOM4, RX_MAILBOX, &recvBuff);
//    	FLEXCAN_DRV_Receive(INST_CANCOM5, RX_MAILBOX, &recvBuff);
//    	FLEXCAN_DRV_Receive(INST_CANCOM6, RX_MAILBOX, &recvBuff);
//    	FLEXCAN_DRV_Receive(INST_CANCOM7, RX_MAILBOX, &recvBuff);
//    	FLEXCAN_DRV_Receive(INST_CANCOM8, RX_MAILBOX, &recvBuff);
//
//    	/* Wait until the previous FlexCAN receive is completed */
//    	while((FLEXCAN_DRV_GetTransferStatus(INST_CANCOM1, RX_MAILBOX) & \
//    		   FLEXCAN_DRV_GetTransferStatus(INST_CANCOM2, RX_MAILBOX) & \
//    		   FLEXCAN_DRV_GetTransferStatus(INST_CANCOM3, RX_MAILBOX) & \
//    		   FLEXCAN_DRV_GetTransferStatus(INST_CANCOM4, RX_MAILBOX) & \
//    		   FLEXCAN_DRV_GetTransferStatus(INST_CANCOM5, RX_MAILBOX) & \
//    		   FLEXCAN_DRV_GetTransferStatus(INST_CANCOM6, RX_MAILBOX) & \
//    		   FLEXCAN_DRV_GetTransferStatus(INST_CANCOM7, RX_MAILBOX) & \
//    		   FLEXCAN_DRV_GetTransferStatus(INST_CANCOM8, RX_MAILBOX) ) == STATUS_BUSY);

	  #elif defined CAN_SEND
    	/**CAN ������ TX �κ�**/
    	SendCANData(TX_MAILBOX, TX_MSG_ID, Tx_Buffer, 64);
    	/**CAN ������ TX �κ�**/
	  #endif
    }

    /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
