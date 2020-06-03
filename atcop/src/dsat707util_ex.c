/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

               I S - 7 0 7   C O M M A N D   T A B L E S

GENERAL DESCRIPTION
  This module contains generic function definitions used by the IS707
  AT command processor.
  
EXTERNALIZED FUNCTIONS
  dsat707_unrec_func_ptr
    This function processess unrecognized commands, and commands with
    parameter errors which will cause a connection to the base station
    if +CXT=1.
    
INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

  Copyright (c) 1995-2014 by Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsat707util_ex.c#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/27/14   tk      Initial revision (created file for Dynamic ATCoP).

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"
#include "ps_utils.h"

#ifdef FEATURE_DATA_IS707
#include "amssassert.h"
#include "dsati.h"
#include "dsatdl.h"
#include "dsat707extctab.h"
#include "ps_in.h"
#ifdef FEATURE_HDR
#include "dsat707hdrctab.h"
#endif /* FEATURE_HDR */
#ifdef FEATURE_DS_MOBILE_IP
#include "dsat707mipctab.h"
#endif /* FEATURE_DS_MOBILE_IP */
#include "dsat707vendctab.h"
#include "dsat707util.h"
#include "dsatparm.h"
#include "msg.h"
#include "dstaski.h"
#include "dsatact.h"
#include "dsat707mip.h"
#include "dsat707mipctab.h"
#include "ds_1x_profile.h"
#include "err.h"

#include <stringl/stringl.h>

#include "ds707_jcdma_m51.h"
#include "ds707_epzid.h"
#ifdef FEATURE_DS_EPZID_HYSTERESIS
#include "ds707_epzid_hyst.h"
#endif /* FEATURE_DS_EPZID_HYSTERESIS */

#include "dsat707extctab.h"

#include "ds707_roaming.h"

/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

  This section contains local definitions for constants, macros, types,
  variables and other items needed by this module.

===========================================================================*/
/*===========================================================================

FUNCTION DSAT_IS_STATUS

DESCRIPTION
  This function returns TRUE if the argument string begins with
  the numeric character (1-8)  or the word corresponding to the
  result specified by the second arg.  Trailing characters are ignored.
  Other wise if returns FALSE.

DEPENDENCIES
  None

RETURN VALUE
  See description.

SIDE EFFECTS
  None
===========================================================================*/

boolean dsat_is_status
(
  byte *a_ptr,
  dsat_result_enum_type result
)
{
  DSAT_DL_CHECK_SYMBOL_ADDR(dsatdl_vtable.dsat707_is_status_fp);

  return dsatdl_vtable.dsat707_is_status_fp(a_ptr, result);
} /* dsat_is_status */


/*===========================================================================
  FUNCTION DSAT707_IP_UINT32_TO_STR

  DESCRIPTION
    This function takes an IP address in uint32 format and returns a string.

  DEPENDENCIES
    None

  RETURN VALUE
    rb_ptr incremented by the size of the ASCII representation of the IP
    address.

  SIDE EFFECTS
    None
===========================================================================*/
byte * dsat707_ip_uint32_to_str
(
  uint32 ip_uint32,
  byte   *rb_ptr
)
{
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  rb_ptr = psutil_itoa(((ip_uint32 >> 24) & 0xFF ),rb_ptr,10);
  *rb_ptr++ = '.';
  rb_ptr = psutil_itoa(((ip_uint32 >> 16) & 0xFF),rb_ptr,10);
  *rb_ptr++ = '.';
  rb_ptr = psutil_itoa(((ip_uint32 >>  8) & 0xFF),rb_ptr,10);
  *rb_ptr++ = '.';
  rb_ptr = psutil_itoa((ip_uint32 & 0xFF),rb_ptr,10);

  return rb_ptr;

} /* dsat707_ip_uint32_to_str () */

#endif /* FEATURE_DATA_IS707 */
