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

  $PVCSPath: L:/src/asw/MM_DATA/vcs/dsat707vendctab.c_v   1.7   08 Jan 2003 12:27:58   sramacha  $
  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsat707vendctab.c#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $
  
when        who    what, where, why
--------    ---    ----------------------------------------------------------
06/27/14    sc      Added support for Dynamic ATCoP.
03/13/12    dvk    Merged enabling mdr val update always during powerup.
01/19/12    sk     Feature cleanup.
07/22/11    dvk    Global Variable Cleanup
07/05/11    nc     Added support for ^MODE,^CARDMODE,^SYSCONFIG,^SYSINFO,^DSCI. 
01/11/11    ad     Remove extern usage.used get/set API for command associated  
                   value pointers.
10/25/10    ad     Init Changes for DSDS. 
05/10/10    kk     Added support for $$GPS* and $SP* commands.
05/10/10    kk     Added support for ^HWVER, ^VOLT, ^RESET 
05/10/10    kk     Added support for $QCGSN and $SPMSID.
05/10/10    kk     Added ^SYSINFO, ^HDRCSQ, command.
01/15/10    ua     Added ^CPIN command. 
11/16/09    ca     Added support for MMGSDI Auth commands.
12/12/08    ua     Fixed Off target lint errors.
10/23/08    bs     Added support for 1X AT Phonebook commands.
11/21/02    rsl    Fixed merge issues with at$qcchv.
11/14/02    atp    Fixed minor compilation errors.
10/15/02    ak     Added support for AT$QCCHS, which is for control/hold
10/15/02    ak     Updated FEATURE_JCDMA_DS to FEATURE_JCDMA_DS_1X
09/24/02    atp    Added support for QOS. (1x Release-A feature).
4/3/01      rsl    Initial release.

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
/* IS-707 Vendor Specific AT parameter command table */
/*=========================================================================*/
const dsati_cmd_ex_type dsat707_vend_para_table_ex [] =
{
/*lint -save -e785*/
/*-------------------------------------------------------------------------*/
 { DSAT707_VEND_PARA_QCPREV_IDX,  dsat707_exec_qcprev_cmd }
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DS_AT_TEST_ONLY

 ,{ DSAT707_VEND_PARA_QCMDR_IDX,    dsat707_exec_qcmdr_cmd }

#endif /* FEATURE_DS_AT_TEST_ONLY */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_IS2000_R_SCH
#ifdef FEATURE_DS_AT_TEST_ONLY

 ,{ DSAT707_VEND_PARA_QCSCRM_IDX,    dsat707_exec_qcscrm_cmd }
/*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_PARA_QCTRTL_IDX,    dsat707_exec_qctrtl_cmd }
#endif /* FEATURE_DS_AT_TEST_ONLY */
#endif /* FEATURE_IS2000_R_SCH */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DS_QNC

 ,{ DSAT707_VEND_PARA_QCQNC_IDX,    dsat707_exec_qcqnc_cmd}

#endif /* FEATURE_DS_QNC */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DS_CHOOSE_SO
#ifdef FEATURE_DS_AT_TEST_ONLY
 ,{ DSAT707_VEND_PARA_QCSO_IDX,    dsat707_exec_qcso_cmd }
#endif /* FEATURE_DS_AT_TEST_ONLY */
#endif /* FEATURE_DS_CHOOSE_SO */
/*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_PARA_QCVAD_IDX,    dsat707_exec_qcvad_cmd}
/*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_PARA_QCCAV_IDX,    dsat707_exec_qccav_cmd }
/*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_PARA_QCCHV_IDX,    dsat707_exec_qcchv_cmd  }
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_IS2000_REL_A
 ,{ DSAT707_VEND_PARA_QCQOSPRI_IDX,   dsat707_exec_qcqospri_cmd }
#endif /* FEATURE_IS2000_REL_A */
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_IS2000_CHS

 ,{ DSAT707_VEND_PARA_QCCHS_IDX,    dsat707_exec_qcchs_cmd }

#endif /* FEATURE_IS2000_CHS */
/*-------------------------------------------------------------------------*/
,{ DSAT707_VEND_PARA_HDRCSQ_IDX,    dsat707_exec_hdrcsq_cmd }
 /*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_PARA_GSN_IDX,     dsatvend_exec_qcgsn_cmd }
/*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_PARA_CGSN_IDX,     dsatvend_exec_qcgsn_cmd }
/*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_PARA_MEID_IDX,     dsatvend_exec_qcgsn_cmd }
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*lint -restore */
};

/*=========================================================================*/
/* IS-707 Vendor Specific AT parameter command table */
/*=========================================================================*/
const dsati_cmd_ex_type dsat707_vend_action_table_ex [] =
{
#ifdef FEATURE_DSAT_EXTENDED_CMD
/*-------------------------------------------------------------------------*/
  { DSAT707_VEND_ACT_CPBR_IDX,    dsatme_exec_cpbr_cmd },
/*-------------------------------------------------------------------------*/
  { DSAT707_VEND_ACT_CPBF_IDX,    dsatme_exec_cpbf_cmd },
/*-------------------------------------------------------------------------*/
  { DSAT707_VEND_ACT_CPBW_IDX,    dsatme_exec_cpbw_cmd },
#endif /* FEATURE_DSAT_EXTENDED_CMD */
/*-------------------------------------------------------------------------*/
 { DSAT707_VEND_ACT_QCCAV_IDX,   dsat707_exec_qccav_cmd }
/*-------------------------------------------------------------------------*/
 ,{ DSAT707_VEND_ACT_QCCHV_IDX,   dsat707_exec_qcchv_cmd }
/*-------------------------------------------------------------------------*/
  ,{ DSAT707_VEND_ACT_HWVER_IDX,  dsatvend_exec_qchwrev_cmd }
/*-------------------------------------------------------------------------*/
  ,{DSAT707_VEND_ACT_RESET_IDX,   dsat707_exec_reset_cmd }
/*-------------------------------------------------------------------------*/
  ,{ DSAT707_VEND_ACT_VOLT_IDX,   dsatvend_exec_qcvolt_cmd }
/*-------------------------------------------------------------------------*/
#ifdef FEATURE_DSAT_CDMA_PIN 
  ,{ DSAT707_VEND_ACT_CPIN_IDX,   dsat707_exec_cpin_cmd }
#endif /* FEATURE_DSAT_CDMA_PIN*/
/*-------------------------------------------------------------------------*/

/*lint -restore */
};

#endif /* FEATURE_DATA_IS707 */
