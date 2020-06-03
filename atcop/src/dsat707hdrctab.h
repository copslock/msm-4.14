#ifndef DSAT707HDRCTAB_H
#define DSAT707HDRCTAB_H
/*===========================================================================

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

               I S - 7 0 7   C O M M A N D   T A B L E S                
                I N T E R N A L   H E A D E R   F I L E


DESCRIPTION
  This file contains the definitions of data structures, defined and
  enumerated constants, and function prototypes required for the
  data services AT command processor command tables that define
  HDR related commands specific to IS-707 mode of operation.
  
Copyright (c) 1995,1996,1997 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
Copyright (c) 1998 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
Copyright (c) 1999, 2000, 2001 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
Copyright (c) 2012 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
Copyright (c) 2014 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsat707hdrctab.h#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $
		      
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/27/14   sc      Added support for Dynamic ATCoP.
01/19/12   sk      Feature cleanup.
01/11/11   ad      Remove extern usage.used get/set API for command associated  
                   value pointers.
04/03/02   rsl     Initial version of file.

===========================================================================*/

#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"

#ifdef FEATURE_DATA_IS707
#include "dsati.h"
#include "dsatctab.h"

/*=========================================================================*/
/* IS-707 HDR related AT command table */
/*=========================================================================*/

#ifdef FEATURE_HDR
extern const dsati_cmd_type dsat707_hdr_table[ ];
extern const dsati_cmd_ex_type dsat707_hdr_table_ex[ ];
extern const unsigned int dsat707_hdr_table_size;

/* Data declarations for HDR commands */

extern const dsat_string_item_type dsat707_hdrc_valstr [][8];
extern const dsat_string_item_type dsat707_hdrr_valstr [][8];

#endif /* FEATURE_HDR */

#endif /* FEATURE_DATA_IS707 */
#endif /* DSAT707HDRCTAB_H */
