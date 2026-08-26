/**********************************************************************************************************************
 *  EcuM_Stub.c — Boot entry without EcuM BSW
 *********************************************************************************************************************/
#include "EcuM.h"
#include "Os.h"
#include "Boot_Init.h"

void EcuM_Init(void)
{
  Boot_Init();
  StartOS(OSDEFAULTAPPMODE);
}

void EcuM_StartupTwo(void)
{
  Boot_StartCommunication();
}

void EcuM_Shutdown(void)
{
}
