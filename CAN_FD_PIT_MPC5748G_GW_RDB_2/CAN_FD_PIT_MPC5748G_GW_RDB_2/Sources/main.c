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
#include "pit1.h"			/**타이머 인터럽트, 클럭매니저 1에서 8개 채널 설정**/
#include "clockMan1.h"		/**CAN 및 타이머 사용시 클럭 매니지먼트가 상위에 설정되어야 함**/
#include "pin_mux.h"

#include "canCom1.h"		/**CAN예제에서는 canCom1 헤더만 넣던데**/
#include "canCom2.h"		/**코드 젠 상황 보면 활성화된 채널 다 넣어야 하는거 같음**/
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

  /**FlexCAN 예제의 버스 역활에 따른 TX, RX메세지 버퍼 정의를 그대로 긁어옴 **/
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
  /**그런데 FlexCAN은 메일박스가 유연하게 쓸 수 있다라고 쓰여진 문서도 있고 CAN은 마스터/슬레이브 **/
  /**개념도 없기에 어떤 의미가 있는지 모르겠음 TX_MAILBOX랑 RX_MAILBOX는 8개씩 총 16개**/
  /**를 임의로 만들어도 될거 같은데 흠..**/

  /**별도로 정의한 CAN 채널 매크로**/
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

  /**SendCANData 함수는 채널별로 따로 지정하지말고 채널명 매개변수로 넣자**/
  #ifdef CAN_SEND
  void SendCANData(uint8_t can_ch, uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len);
  #endif

  void BoardInit(void);
  /**MPC5748G GW RDB 보드는 아래 두 함수를 설정해 줘야함 -> MPC5748G DEV kit과의 차이점**/
  void Peripheral_Power_Supply_Init(void);
  void CAN_TJA1043T_Enable(void);

  void PIT_FlexCan_Init(void);


  /**타이머 인터럽트 함수 선언시 같이 긁어온 딜레이 함수 -> 근데 이거 클럭스피드인데 시간은???**/
  void delay(volatile int cycles)
  {
      /* Delay function - do nothing for a number of cycles */
      while(cycles--);
      //delay(720000);	//Insert a small delay to make the blinking visible
  }

  /*영어가 약하니 한글로 번역해서 적자..
   *SendCANData 함수는 4개의 매개변수 입력, 반환값 없는 형태이다.
   *매개변수 1: 특정 mailbox 번호 -> 이거때문에 여러개 메일박스 아무거나 설정해도 되나??
   *매개변수 2: 메세지 ID -> Standard message ID라고 표현된거 보니 CAN 데이터 메시지 ID를 의미하는듯
   *매개변수 3: CAN 데이터 필드에 넣을 변수 -> FD니까 최대 64byte짜리 배열변수
   *매개변수 4: 데이터 필드의 길이 -> FD니까 최대 64, 아이오닉은 32까지만 씀
   */
  #ifdef CAN_SEND
  void SendCANData(uint8_t can_ch, uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len)
  {
  	/**원래 아래 구조체 변수는 다른 c파일에 선언되는데 **/
  	/**뭐.. 아무튼 보내는 CAN데이터가 어느 포멧인지 알려주는 정보가 담긴 구조체이다..**/
      flexcan_data_info_t dataInfo =
      {
              .data_length = len,		//데이터 길이
              .msg_id_type = FLEXCAN_MSG_ID_STD,	//표준 CAN ID
              .enable_brs  = true,	//데이터 세그먼트에 대해 다른 비트 전송률을 사용하도록 활성화된 비트전송률 스위치???
              .fd_enable   = true,	//유연한 데이터 속도
              .fd_padding  = 0U		//FD 패딩에 0씀 -> 패딩비트를 쓰면 데이터 필드 길이가 항시고정됨??
      };

      /**여기는 내가 can 통신채널별로 지정하려고 만든 코드 -> 문제는 없지않을까? **/
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

  /**타이머 인터럽트 사용을 위한 flag변수선언**/
  uint8_t can_tx_periodic_flag[8] = {0};

  /**startup_MPC5748G.S에 정의된 Periodic Interrupt Timer (PIT0~7)**/
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
  void BoardInit(void) //추가 초기화 및 시작은 다른 함수로 쓰자
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

  /**PIT 및 flexcan 초기화 및 시작은 여기 함수에 넣자**/
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

      /**CAN 통신의 TX및 RX 버퍼를 구성하는 함수**/
  	#ifdef CAN_RECEIVE
      /**이거를 main문에서 쓰는 이유 : CAN채널별로 설정한게 다를 수 있기대문에**/
      /**지금이야 모두다 CAN FD 설정으로 맞췄으니까 한개 공통으로 쓰지만, 다르면 구조체 변수를 여러개 만들어야함**/
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
      /**앞서 선언한 RX컨피그에 사용하는거랑 동일한 구조체**/
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
    /**추가로 설정한 FlexCAN 및  PIT 초기화&start 함수**/
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
    	/**CAN 데이터 TX 부분**/
    	SendCANData(TX_MAILBOX, TX_MSG_ID, Tx_Buffer, 64);
    	/**CAN 데이터 TX 부분**/
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
