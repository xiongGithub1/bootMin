/**********************************************************************************************************************
 * Boot_Init.c 鈥� Mcu/Port/Can stack init (no EcuM/ComM/CanSM)
 *********************************************************************************************************************/
#include "Boot_Init.h"

#include "Mcu.h"
#include "Port.h"
#include "Can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "SchM_CanTp.h"
#include "PduR.h"
#include "FlsLoader.h"
#include "Boot_PFlashSmoke.h"
#include "Mcu_PBcfg.h"
#include "Port_PBcfg.h"
#include "Can_Cfg.h"
#include "Dio.h"
#include "Os.h"
#include "Boot_FlashProg.h"
#include "Boot_Dcm.h"
#include "Boot_Uds.h"
#include "Boot_Uds_Sm.h"
#include "Boot_App.h"
#include "Wdg_17_Scu.h"
static volatile uint8 Boot_RxCnt;
static volatile uint8 Boot_RxSid;
static volatile uint8 Boot_RxPdu;

void Boot_CanRxNotify(uint8 pduId, uint8 sid)
{
  Boot_RxCnt++;
  Boot_RxPdu = pduId;
  Boot_RxSid = sid;
}

/* Temporary TX probe: Trace should show ID 0x123 every ~200ms. Set to 0 to disable. */
#ifndef BOOT_CAN_TX_TEST
# define BOOT_CAN_TX_TEST  1
#endif

#if (BOOT_CAN_TX_TEST == 1)
# define BOOT_CAN_TX_TEST_ID     ((Can_IdType)0x123u)
# define BOOT_STM0_TIM0          (*(volatile uint32 *)0xF0001010u)
/* STM ~100 MHz 鈫� 20e6 ticks 鈮� 200 ms */
# define BOOT_CAN_TX_TEST_TICKS  (20000000u)

static void Boot_CanTxTest(void)
{
  static uint32 lastTick = 0u;
  static uint8 started = 0u;
  static uint8 seq = 0u;
  static uint8 data[8];
  uint32 now;
  Can_PduType pdu;

  now = BOOT_STM0_TIM0;
  if (started == 0u)
  {
    lastTick = now;
    started = 1u;
    return;
  }
  if ((uint32)(now - lastTick) < BOOT_CAN_TX_TEST_TICKS)
  {
    return;
  }
  lastTick = now;
  Dio_FlipChannel(DioConf_DioChannel_DioChannel_led2);
//  data[0] = (uint8)'B';
//  data[1] = (uint8)'O';
//  data[2] = (uint8)'O';
//  data[3] = (uint8)'T';
//  data[4] = seq;
//  data[5] = Boot_RxCnt;
//  data[6] = Boot_RxSid;
//  data[7] = Boot_RxPdu;
//  seq++;
//
//  pdu.id = BOOT_CAN_TX_TEST_ID;
//  pdu.length = 8u;
//  pdu.sdu = data;
//  pdu.swPduHandle = 0u;
//  (void)Can_Write(CanConf_CN_CAN00_5e566ad9_Tx, &pdu);
}
#endif

void Boot_Init(void)
{


  Can_InitMemory();
  CanIf_InitMemory();
  PduR_InitMemory();
  CanTp_InitMemory();

  Mcu_Init(&Mcu_Config);
  (void)Mcu_InitClock(McuConf_McuModeSettingConf_McuModeSettingConf_0);
  while (Mcu_GetPllStatus() != MCU_PLL_LOCKED)
  {
    /* wait lock */
  }
  (void)Mcu_DistributePllClock();
  /* Jump before any Boot stack/com init when APP image is valid. */
  Boot_App_TryStart();
  Port_Init(&Port_Config);

  Can_Init(Can_Config_Ptr);
  CanIf_Init(CanIf_Config_Ptr);
  /* MICROSAR PduR requires PreInit before Init; without it PduR_Init is a no-op
   * (PDUR_E_NO_PREINIT) and CanTp never reaches Cdd_StartOfReception. */
  PduR_PreInit(PduR_Config_Ptr);
  PduR_Init(PduR_Config_Ptr);
  CanTp_Init(CanTp_Config_Ptr);

  (void)FlsLoader_Init(NULL_PTR);
  Boot_App_NotifyFlsInit();
#if (BOOT_PFLASH_SMOKE_TEST == 1)
  Boot_PFlashSmoke_Init();
#endif
  Boot_Sm_Init();
  Boot_FlashProg_Init();
  Boot_Dcm_Init();
//  Wdg_17_Scu_Init(&Wdg_17_Scu_Config_0);
}

void Boot_StartCommunication(void)
{
  (void)CanIf_SetControllerMode(CanIfConf_CanIfCtrlCfg_CT_CAN00_9df8a959, CANIF_CS_STARTED);
  (void)CanIf_SetPduMode(CanIfConf_CanIfCtrlCfg_CT_CAN00_9df8a959, CANIF_SET_ONLINE);
  Boot_App_NotifyComStart();
}

void Boot_ComMainFunctions(void)
{
  static uint8 canIsrEnabled = 0u;

  /* CanIsr_0 is generated with IsEnabledOnInitialization=FALSE, so
   * Os_InitialEnableInterruptSources() never unmasks it. Without this,
   * CanIf/CanTp/Cdd never see RX frames and Cdd_TpRxIndication never runs. */
  if (canIsrEnabled == 0u)
  {
    canIsrEnabled = 1u;
    (void)Os_EnableInterruptSource(CanIsr_0, FALSE);
  }

  /* TX is POLLING; RX/BusOff via CanIsr_0 */
  Can_MainFunction_Write();
  Can_MainFunction_Mode();
  CanTp_MainFunction();
  Boot_Uds_MainFunction();
  Boot_Dcm_MainFunction();
#if (BOOT_CAN_TX_TEST == 1)
  Boot_CanTxTest();
#endif
}
