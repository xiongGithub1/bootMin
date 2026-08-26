/**********************************************************************************************************************
 *  EcuM.h — Boot slim stub (no EcuM BSW module)
 *  BrsMain still calls EcuM_Init/StartupTwo; replace later with Boot_Init().
 *********************************************************************************************************************/
#ifndef ECUM_H
#define ECUM_H

#include "Std_Types.h"

void EcuM_Init(void);
void EcuM_StartupTwo(void);
void EcuM_Shutdown(void);

#endif /* ECUM_H */
