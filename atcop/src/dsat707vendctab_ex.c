/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

               I S - 7 0 7   C O M M A N D   T A B L E S

GENERAL DESCRIPTION
  This module contains the command tables and data definitions required
  to define the vendor specific AT modem commands for the IS-707 mode.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

  Copyright (c) 1995 - 2014 by Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsat707vendctab_ex.c#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $
  
when        who    what, where, why
--------    ---    ----------------------------------------------------------
06/27/14   sc      Initial revision (created file for Dynamic ATCoP).

===========================================================================*/


/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"

#ifdef FEATURE_DATA_IS707
#include "dsati.h"
#include "ds707.h"
#include "dsatvend.h"
#include "dsat707ext.h"
#include "dsat707vend.h"
#include "dsat707vendctab.h"
#include "dsat707extctab.h"
#include "ds_1x_profile.h"
#include "dsatctab.h"
#include "dsatme.h"
#include "dsatparm.h"
#include "dstaski.h"
#include "err.h"
#include "msg.h"
#include "nv.h"



/*=========================================================================*/
/* Defaults & Limits for HDR commands */
/*=========================================================================*/

LOCAL const dflm_type dsat707_qcvad_dflm [] =
{
  { 0  , 0  , 4    },
} ;



/*=========================================================================*/
/* IS-707 Vendor Specific AT parameter command table */
/*=========================================================================*/
const dsati_cmd_type dsat707_vend_para_table [] =
{
/*lint -save -e785*/
/*-------------------------------------------------------------------------*/
 { "$QCPREV",
    EXTENDED  | READ_ONLY | DO_PREF_CMD,
    SPECIAL_QCPREV,
    0,
    DSAT707_VEND_PARA_QCPREV_IDX,
    NULL}
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DS_AT_TEST_ONLY

 ,{ "$QCMDR",
    EXTENDED  | LOCAL_TEST | COMMON_CMD,
    SPECIAL_QCMDR,
    1,
    DSAT707_VEND_PARA_QCMDR_IDX,
    NULL}

#endif /* FEATURE_DS_AT_TEST_ONLY */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_IS2000_R_SCH
#ifdef FEATURE_DS_AT_TEST_ONLY

 ,{ "$QCSCRM",
    EXTENDED  | LOCAL_TEST | COMMON_CMD,
    SPECIAL_QCSCRM,
    1,
    DSAT707_VEND_PARA_QCSCRM_IDX,
    NULL }
/*-------------------------------------------------------------------------*/
 ,{ "$QCTRTL",
    EXTENDED  | LOCAL_TEST | COMMON_CMD,
    SPECIAL_QCTRTL,
    1,
    DSAT707_VEND_PARA_QCTRTL_IDX,
    NULL}
#endif /* FEATURE_DS_AT_TEST_ONLY */
#endif /* FEATURE_IS2000_R_SCH */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DS_QNC

 ,{ "$QCQNC",
    EXTENDED  | LOCAL_TEST | COMMON_CMD,
    SPECIAL_QCQNC,
    1,
    DSAT707_VEND_PARA_QCQNC_IDX,
    NULL}

#endif /* FEATURE_DS_QNC */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DS_CHOOSE_SO
#ifdef FEATURE_DS_AT_TEST_ONLY
 ,{ "$QCSO",
    EXTENDED  | LOCAL_TEST | COMMON_CMD,
    SPECIAL_QCSO,
    1,
    DSAT707_VEND_PARA_QCSO_IDX,
    NULL}
#endif /* FEATURE_DS_AT_TEST_ONLY */
#endif /* FEATURE_DS_CHOOSE_SO */
/*-------------------------------------------------------------------------*/
 ,{ "$QCVAD",
    EXTENDED | CONFIG | LOCAL_TEST | CDMA_CMD,
    SPECIAL_QCVAD,
    1,
    DSAT707_VEND_PARA_QCVAD_IDX,
    &dsat707_qcvad_dflm[0] }
/*-------------------------------------------------------------------------*/
 ,{ "$QCCAV",
    EXTENDED | CDMA_CMD,
    SPECIAL_QCCAV ,
    0,
    DSAT707_VEND_PARA_QCCAV_IDX,
    NULL}
/*-------------------------------------------------------------------------*/
 ,{ "$QCCHV",
    EXTENDED | CDMA_CMD,
    SPECIAL_QCCHV ,
    0,
    DSAT707_VEND_PARA_QCCHV_IDX,
    NULL }
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_IS2000_REL_A
 ,{ "$QCQOSPRI",
    EXTENDED  | LOCAL_TEST | COMMON_CMD,
    SPECIAL_QCQOSPRI,
    1,
    DSAT707_VEND_PARA_QCQOSPRI_IDX,
    NULL}
#endif /* FEATURE_IS2000_REL_A */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_IS2000_CHS

 ,{ "$QCCHS",
    EXTENDED  | LOCAL_TEST | COMMON_CMD,
    SPECIAL_QCCHS,
    1,
    DSAT707_VEND_PARA_QCCHS_IDX,
    NULL}

#endif /* FEATURE_IS2000_CHS */
/*-------------------------------------------------------------------------*/
,{ "^HDRCSQ",
    READ_ONLY | RESTRICTED | DO_PREF_CMD,
    SPECIAL_NONE, 
    0,
    DSAT707_VEND_PARA_HDRCSQ_IDX,
    NULL }
 /*-------------------------------------------------------------------------*/
 ,{ "^GSN",
     EXTENDED | READ_ONLY | RESTRICTED | DO_PREF_CMD,
     SPECIAL_NONE, 
     0,
     DSAT707_VEND_PARA_GSN_IDX,
     NULL }
/*-------------------------------------------------------------------------*/
 ,{ "^CGSN",
     EXTENDED | READ_ONLY | RESTRICTED | DO_PREF_CMD,
     SPECIAL_NONE, 
     0,
     DSAT707_VEND_PARA_CGSN_IDX,
     NULL }
/*-------------------------------------------------------------------------*/
 ,{ "^MEID",
     EXTENDED | READ_ONLY | RESTRICTED | DO_PREF_CMD,
     SPECIAL_NONE, 
     0,
     DSAT707_VEND_PARA_MEID_IDX,
     NULL }
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*lint -restore */
};

/*=========================================================================*/
/* IS-707 Vendor Specific AT parameter command table */
/*=========================================================================*/
const dsati_cmd_type dsat707_vend_action_table [] =
{
#ifdef FEATURE_DSAT_EXTENDED_CMD
/*-------------------------------------------------------------------------*/
  { "^CPBR",
    ATTRIB_NONE  ,
    SPECIAL_NONE,
    2,
    DSAT707_VEND_ACT_CPBR_IDX,
    NULL },
/*-------------------------------------------------------------------------*/
  { "^CPBF",
    ATTRIB_NONE ,
    SPECIAL_NONE,
    1,
    DSAT707_VEND_ACT_CPBF_IDX,
    NULL},
/*-------------------------------------------------------------------------*/
  { "^CPBW",
    ATTRIB_NONE ,
    SPECIAL_NONE,
    10,
    DSAT707_VEND_ACT_CPBW_IDX,
    NULL },
#endif /* FEATURE_DSAT_EXTENDED_CMD */
/*-------------------------------------------------------------------------*/
  { "$QCCAV",
    EXTENDED | CDMA_CMD,
    SPECIAL_QCCAV,
    0,
    DSAT707_VEND_ACT_QCCAV_IDX,
    NULL }
/*-------------------------------------------------------------------------*/
 ,{ "$QCCHV",
    EXTENDED | CDMA_CMD,
    SPECIAL_QCCHV ,
    0,
    DSAT707_VEND_ACT_QCCHV_IDX,
    NULL }
/*-------------------------------------------------------------------------*/
  ,{ "^HWVER",
    READ_ONLY | RESTRICTED,
    SPECIAL_NONE, 
    0,
    DSAT707_VEND_ACT_HWVER_IDX,
    NULL }
/*-------------------------------------------------------------------------*/
  ,{"^RESET",
    READ_ONLY | RESTRICTED,
    SPECIAL_NONE, 
    0,
    DSAT707_VEND_ACT_RESET_IDX,
    NULL }
/*-------------------------------------------------------------------------*/
  ,{ "^VOLT",
    READ_ONLY | RESTRICTED,
    SPECIAL_NONE, 
    0,
    DSAT707_VEND_ACT_VOLT_IDX,
    NULL }
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DSAT_CDMA_PIN 
  ,{ "^CPIN",
     EXTENDED | CONFIG | MIXED_PARAM | LIST | LOCAL_TEST | RESTRICTED | DO_PREF_CMD,
     SPECIAL_NONE,
     2,
     DSAT707_VEND_ACT_CPIN_IDX,
     &dsat707_cpin_mixed_dfl[0] }
#endif /* FEATURE_DSAT_CDMA_PIN*/
/*-------------------------------------------------------------------------*/

/*lint -restore */
};

  /* Size of vendor specific command table */
const unsigned int dsat707_vend_para_table_size = ARR_SIZE( dsat707_vend_para_table );
const unsigned int dsat707_vend_action_table_size = ARR_SIZE( dsat707_vend_action_table );

#endif /* FEATURE_DATA_IS707 */
