/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

               I S - 7 0 7   C O M M A N D   T A B L E S

GENERAL DESCRIPTION
  This module contains the command tables and data definitions required
  to define the Protocol Statistics related AT modem commands for the
  IS-707 mode.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright (c) 2002 - 2014 by Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsat707pstatsctab.c#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $
			
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/27/14   sc      Added support for Dynamic ATCoP.
01/19/12   sk      Feature cleanup.
01/11/11   ad      Remove extern usage.used get/set API for command associated  
                   value pointers.
10/25/10   ad      Init Changes for DSDS. 
12/12/08   ua      Fixed Off target lint errors.
4/3/01     rsl     Initial release.

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"
#ifdef FEATURE_DATA_IS707
#endif /* FEATURE_DATA_IS707 */
