/*===========================================================================

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

DESCRIPTION
  This module executes AT commands. It executes IS-707 vendor specific
  AT commands.

EXTERNALIZED FUNCTIONS
dsat707_set_mdr_val
  This function writes the MDR value to NV and does any required sync
  in the phone (such as enabling/disabling various service options)

dsat707_exec_qcprev_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCPREV command.
  Returns protocol revision in use.

dsat707_exec_qcmdr_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCMDR command.
  Set Medium Data Rate.

dsat707_exec_qcscrm_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCSCRM command.
  Enable/Disable mobile from SCRMing.

dsat707_exec_qctrtl_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCTRTL command.
  Enable/Dsiable R_SCH throttling.

dsat707_exec_qcchs_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCCHS command.
  Enable/Dsiable mobile originated control/hold.
  
dsat707_exec_qcqnc_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCQNC command.
  Enable/Dsiable Quick Net Connect.

dsat707_exec_qcso_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCSO command.
  Set Data Service Option number.

dsat707_exec_qcvad_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCVAD command.
  Prearrangement setting. Respond to page message that has a voice service
  option with a page response that has a data service option.

dsat707_exec_qccav_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCCAV command.
  Answer incoming voice call.

dsat707_exec_qcqospri_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT$QCQOSPRI command.
  Set desired value of QOS non-assured priority adjustment.

dsat707_exec_cave_cmd
  This function takes the result from the command line parser and
  executes it. It executes AT^CAVE command. Client sends CAVE authentication
  related parameter (RANDU) to datacard, datacard returns the response. 

dsat707_exec_ssdupdcfm_cmd
  This function takes the result from the command line parser 
  and executes it. It executes AT^SSDUPDCFM command. Client sends 
  updated SSD confirmation (AUTHBS) to datacard.

dsat707_exec_vpm_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^VPM command. Client asks datacard 
  to generate key.

dsat707_exec_uimauth_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^UIMAUTH command. Client queries 
  UIM to check the authentication algorithm it supports.

dsat707_exec_gsn_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^GSN command. Client checks
  datacard/module�s ESN and UIMID. If terminal uses MEID, 
  then it returns MEID, and if terminal uses ESN, then it
  returns ESN.

dsat707_exec_ssdupd_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^SSDUPD command. Client sends RANDSSD
  to datacard, datacard calculates and reports result.

dsat707_exec_md5_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^MD5 command. 
  It Generates the CHAP Response for the received CHAP Challenge in 
  HRDP authentication. 


dsat707_exec_hdrcsq_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^HDRCSQ command. It provides
  the intensity level of current hdr_rssi.
  
dsat707_exec_reset_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^RESET command. This command
  reboots the device.

  Copyright (c) 2002 - 2016 by Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.

===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$PVCSPath: L:/src/asw/MM_DATA/vcs/dsat707vend.c_v   1.14   23 Jan 2003 16:40:12   randrew  $
$Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsat707vend.c#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/27/14   sc      Added support for Dynamic ATCoP.
05/30/14   sc      Fixed ATCoP KW errors.
05/23/14   pg      Fixed LLVM warnings.
04/23/14   sc      Fixed +CFUN issue.
04/17/14   sc      Fixed ATCoP KW errors.
03/11/14   tk/sc   Optimized debug macros usage in ATCoP.
08/30/13   pg      Fixed predictable random number generation issue.
01/04/13   tk      ATCoP changes for DSDX C/G+G with True World Mode Support.
11/30/12   tk      ATCoP changes for Triton DSDA.
08/22/12   sk      Mainlining Nikel Changes.
05/18/12   tk      Migrated to MSG 2.0 macros
09/27/11   ht      Included dsut header to support offtarget stubs.
07/05/11   nc      Added support for ^MODE,^CARDMODE,^SYSCONFIG,^SYSINFO,^DSCI.
01/11/11   ad      Remove extern usage.used get/set API for command associated  
                   value pointers.
10/06/10   ad      Added Error msg before Assert(0).
06/04/10   bs      MMGSDI SESSION Migration.
05/10/10   kk      Added support for $$GPS* and $SP* commands.
05/10/10   kk      Added support for ^RESET.
05/10/10   kk      Added support for $QCGSN and $SPMSID.
05/10/10   kk      Added ^SYSINFO, ^HDRCSQ commands.
11/16/09   ca      Added support for the MMGSDI authentication
                   interface commands.
12/12/08   ua      Fixed Off target lint errors.
05/05/03   jd      Removed dependencies on dsiface.h, AT$QCMDR and 
                   AT$QCQOSPRI are set directly
03/05/03   rsl     Fixed at$qcvad.
01/20/03   ar      Added dialstr_modifiers to ds707_async_dial_str_cb 
                   interface.
11/21/02   rsl     Fixed merge issues with at$qcchv.
11/14/02   jd      featurized dsat707mip.h inclusion, cleanup
10/15/02   ak      Added exec_qcchs(), which is for control/hold.
09/30/02   ar      Accomodate changed interface to proc_dial_string
09/24/02   atp     Added support for QOS. (1x Release-A feature).
09/10/02   ak      Fixed bugs in exec_qcscrm() where at$qcscrm? was failing.
09/03/02   ak      In set_mdr_val, no longer write to NV.
07/12/02   ak      Function dsat707_set_mdr_val made available.  Called by
                   dsiface_set_opt.
07/03/02   ak      For QCMDR, QCQNC, QCSCRM, QCTRTL, call dsatpar_exec_param_
                   _cmd, so that input is filtered by common function.
04/03/02   rsl     Initial version of file.

===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"

#include <stringl/stringl.h>
#include "ps_utils.h"
#ifdef FEATURE_DATA_IS707
#include "dsati.h"
#include "dsatctab.h"
#include "dsat707vend.h"
#include "dsat707vendctab.h"
#include "dsat707util.h"
#include "dsat707mipctab.h"
#include "ds_1x_profile.h"
#include "dstaski.h"
#include "ds707.h"
#include "ds707_so_pkt.h"
#include "dsatparm.h"
#include "mc.h"
#include "msg.h"
#include "dsatact.h"
#include "dsatvoice.h"
#include "dsrlp_v.h"
#include "db.h"
#include "cm.h"
#include "dsatcmif.h"
#include "dsat_v.h"
#include "dsatme.h"
#include "dstask.h"
#include "dsat707ext.h"
#include "ds707_pkt_mgr.h"
#include "dsatetsipkt.h"
#include "dsatetsictab.h"

#if defined(T_WINNT) || defined(T_UNIX)
#ifdef TEST_FRAMEWORK
#error code not present
#endif /* TEST_FRAMEWORK */
#endif /* WINNT || UNIX */




#ifdef FEATURE_DS_MOBILE_IP
#include "dsat707mip.h"
#endif /* FEATURE_DS_MOBILE_IP */



#include "ds_profile.h"

/*===========================================================================

                           GLOBAL DATA

===========================================================================*/

/*===========================================================================
                                 LOCAL DATA
===========================================================================*/
#ifdef FEATURE_CDMA
#define DSAT707_NV_IMSI_S_LENGTH 11
#endif /* FEATURE_CDMA */

#define UNUSED_ARG(_x)        (void)(_x)




/*===========================================================================
                  INTERNAL FUNCTION FORWARD DECLARATIONS
===========================================================================*/

/*===========================================================================
                       EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
  FUNCTION DSAT707_EXEC_QCPREV_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCPREV command.
  Returns protocol revision in use.
  1 - JSTD008
  3 - IS_95A
  4 - IS_95B
  6 - IS2000

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcprev_cmd
(
  dsat_mode_enum_type mode,                /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,         /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,       /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr              /*  Place to put response       */
)
{
  /*lint -esym(715,rb_ptr)*/ 
  /*lint -esym(715,tab_entry)*/ 
  /*lint -esym(715,tok_ptr)*/ 
  /*lint -esym(715,mode)*/ 
  byte *rb_ptr = res_buff_ptr->data_ptr;
/*-------------------------------------------------------------------------*/
  rb_ptr = psutil_itoa( mc_get_p_rev_in_use(), rb_ptr, 10);
  res_buff_ptr->used = (word)strlen((char *)res_buff_ptr->data_ptr);
  return(DSAT_OK);
} /* dsat707_exec_qcprev_cmd */


#ifdef FEATURE_DS_AT_TEST_ONLY
/*===========================================================================
  FUNCTION DSAT707_EXEC_QCMDR_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCMDR command.
  Set Medium Data Rate.
  0: MDR service only
  1: MDR service if available
  2: LSPD only
  3: SO 33, if available

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcmdr_cmd
(
  dsat_mode_enum_type mode,                /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,         /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,       /*  Command tokens from parser  */
  dsm_item_type *rb_ptr                    /*  Place to put response       */
)
{
  dsat_num_item_type    temp_val = DS_MDR_MODE_DEFAULT;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (tok_ptr->op == (NA|EQ|AR) || (tok_ptr->op == NA)) 
  {
    if(FALSE == DSAT_VALIDATE_SET_707_PKTMGR(DS707_MDR_VAL,DS_MDR_MODE_MAX - 1 ) ||
       FALSE == ds707_pkt_mgr_set_mdr_val_and_so_pkt_recal((dsat_num_item_type)temp_val))
    {
      DS_ATCOP_ERROR_LOG_1("$QCMDR: Invalid Number of arguements  =d", tok_ptr->args_found);
      return DSAT_ERROR;
    }
  }
  else if (tok_ptr->op == (NA|EQ|QU) )
  {
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                          "$QCMDR: (0 - %d)\n",DS_MDR_MODE_MAX - 1);
  }
  else  if(tok_ptr->op == (NA|QU))
  {
    ds707_pkt_mgr_get_1x_profile_val(DS707_MDR_VAL,(void *)&temp_val,0);
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                           "$QCMDR: %d\n",
                                           temp_val);
  }
  else
  {
    /* Not Supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_qcmdr_cmd */


#ifdef FEATURE_IS2000_R_SCH
/*===========================================================================
  FUNCTION DSAT707_EXEC_QCSCRM_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCSCRM command.
  Enable/Disable mobile from SCRMing.
  0 - Mobile never SCRMs
  1 - Mobile can SCRM as needed.

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcscrm_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
)
{
  dsat_num_item_type    temp_val = DS_SCRM_DEFAULT;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (tok_ptr->op == (NA|EQ|AR) || (tok_ptr->op == NA)) 
  {
    if(FALSE == DSAT_VALIDATE_SET_707_PKTMGR(DS707_QCSCRM_VAL,1 ) )
    {
      DS_ATCOP_ERROR_LOG_1("$QCSCRM: Invalid Number of arguements  =d", tok_ptr->args_found);
      return DSAT_ERROR;
    }
    /*-----------------------------------------------------------------------
      Store the new SCRM Mode setting in NV
    -----------------------------------------------------------------------*/
    /*lint -save -e734 -e534*/
    ds_nv_item.data_scrm_enabled = temp_val;
    dsatutil_put_nv_item(NV_DATA_SCRM_ENABLED_I, &ds_nv_item);
  }
  else if (tok_ptr->op == (NA|EQ|QU) )
  {
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                          "$QCSCRM: (0 - 1)\n");
  }
  else  if(tok_ptr->op == (NA|QU))
  {
     ds707_pkt_mgr_get_1x_profile_val(DS707_QCSCRM_VAL,(void *)&temp_val,0);
     rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                            rb_ptr->size,
                                            "$QCSCRM: %d\n",
                                            temp_val);
  }
  else
  {
    /* Not Supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_qcscrm_cmd */


/*===========================================================================
  FUNCTION DSAT707_EXEC_QCTRTL_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCTRTL command.
  Enable/Dsiable R_SCH throttling.
  0 - Mobile never throttles R-SCH
  1 - Mobile can throttle R-SCH as needed.

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qctrtl_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
)
{
  dsat_num_item_type    temp_val = DS_TRTL_DEFAULT;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (tok_ptr->op == (NA|EQ|AR) || (tok_ptr->op == NA)) 
  {
    if(FALSE == DSAT_VALIDATE_SET_707_PKTMGR(DS707_QCTRTL_VAL,1 ) )
  {
      DS_ATCOP_ERROR_LOG_1("$QCTRTL: Invalid Number of arguements  =d", tok_ptr->args_found);
      return DSAT_ERROR;
    }
    /*-----------------------------------------------------------------------
      Store the new TRTL Mode setting in NV
    -----------------------------------------------------------------------*/
    /*lint -save -e734 -e534*/
    ds_nv_item.data_trtl_enabled = (dsat_num_item_type)temp_val;
    dsatutil_put_nv_item(NV_DATA_TRTL_ENABLED_I, &ds_nv_item);
  }
  else if (tok_ptr->op == (NA|EQ|QU) )
  {
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                          "$QCTRTL: (0 - 1)\n");
  }
  else  if(tok_ptr->op == (NA|QU))
  {
     ds707_pkt_mgr_get_1x_profile_val(DS707_QCTRTL_VAL,(void *)&temp_val,0);
     rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                            rb_ptr->size,
                                            "$QCTRTL: %d\n",
                                            temp_val);
  }
  else
  {
    /* Not Supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_qctrtl_cmd */
#endif /* FEATURE_IS2000_R_SCH */
#endif /* FEATURE_DS_AT_TEST_ONLY */


#ifdef FEATURE_IS2000_CHS
/*===========================================================================
  FUNCTION DSAT707_EXEC_QCQNC_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCCHS command.
  Enable/Dsiable mobile originated control/hold.
  0 - Disable mobile-originated control/hold.
  1-255 - Enable mobile-originated control-hold.  Mobile waits for this many
          idle (both tx and rx) 20-msec frames before asking BS for
          control/hold.  

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcchs_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
)
{
  dsat_num_item_type    temp_val   = DS_CHS_DEFAULT;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (tok_ptr->op == (NA|EQ|AR) || (tok_ptr->op == NA)) 
  {
    if(FALSE == DSAT_VALIDATE_SET_707_PKTMGR(DS707_QCCHS_VAL,255 ) )
    {
      DS_ATCOP_ERROR_LOG_1("$QCCHS: Invalid Number of arguements  =d", tok_ptr->args_found);
      return DSAT_ERROR;
    }
  }
  else if (tok_ptr->op == (NA|EQ|QU) )
  {
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                          "$QCCHS: (0 - 255)\n");
  }
  else  if(tok_ptr->op == (NA|QU))
  {
     ds707_pkt_mgr_get_1x_profile_val(DS707_QCCHS_VAL,(void *)&temp_val,0);
     rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                            rb_ptr->size,
                                            "$QCCHS: %d\n",
                                            temp_val);
  }
  else
  {
    /* Not Supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_qcchs_cmd */
#endif /* FEATURE_IS2000_CHS */

#ifdef FEATURE_DS_QNC
/*===========================================================================
  FUNCTION DSAT707_EXEC_QCQNC_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCQNC command.
  Enable/Dsiable Quick Net Connect.
  0 - Disable QNC capability
  1 - Enable QNC capability

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcqnc_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
)
{
  dsat_num_item_type    temp_val = DS_QNC_DEFAULT;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (tok_ptr->op == (NA|EQ|AR) || (tok_ptr->op == NA)) 
  {
    if(FALSE == DSAT_VALIDATE_SET_707_PKTMGR(DS707_QCQNC_VAL,1))
    {
      DS_ATCOP_ERROR_LOG_1("$QCQNC: Invalid Number of arguements  =d", tok_ptr->args_found);
      return DSAT_ERROR;
    }
    ds_nv_item.data_qnc_enabled = (dsat_num_item_type)temp_val;
    dsatutil_put_nv_item( NV_DATA_QNC_ENABLED_I, &ds_nv_item );
    /*lint -restore */
    /*-----------------------------------------------------------------------
     Set service options according to values read from NV
    -----------------------------------------------------------------------*/
     ds707_so_pkt_recal();
  }
  else if (tok_ptr->op == (NA|EQ|QU) )
  {
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                          "$QCQNC: (0 - 1)\n");
  }
  else  if(tok_ptr->op == (NA|QU))
  {
     ds707_pkt_mgr_get_1x_profile_val(DS707_QCQNC_VAL,(void *)&temp_val,0);
     rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                            rb_ptr->size,
                                            "$QCQNC: %d\n",
                                            temp_val);
  }
  else
  {
    /* Not Supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_qcqnc_cmd */
#endif /* FEATURE_DS_QNC */
#ifdef FEATURE_DS_CHOOSE_SO
#ifdef FEATURE_DS_AT_TEST_ONLY
/*===========================================================================
  FUNCTION DSAT707_EXEC_QCSO_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCSO command.
  Set Data Service Option number.
  0 - pre-707 numbers
  1 - proprietary 707 numbers
  2 - IS-707 SO numbers

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcso_cmd
(
  dsat_mode_enum_type mode,               /*  AT command mode:             */
  const dsati_cmd_type *tab_entry,        /*  Ptr to cmd in parse table    */
  const tokens_struct_type *tok_ptr,      /*  Command tokens from parser   */
  dsm_item_type *rb_ptr                   /*  Place to put response        */
)
{
  dsat_num_item_type    temp_val = DS_SO_SET_DEFAULT;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (tok_ptr->op == (NA|EQ|AR) || (tok_ptr->op == NA)) 
  {
    if(FALSE == DSAT_VALIDATE_SET_707_PKTMGR(DS707_QCSO_VAL,DS_SO_SET_COUNT-1 ))
  {
      DS_ATCOP_ERROR_LOG_1("$QCSO: Invalid Number of arguements  =d", tok_ptr->args_found);
      return DSAT_ERROR;
    }
    /*-----------------------------------------------------------------------
      Store the new SO Mode setting in NV
    -----------------------------------------------------------------------*/
    /*lint -save -e734 -e534*/
    ds_nv_item.data_so_set =(dsat_num_item_type)temp_val;
    dsatutil_put_nv_item( NV_DATA_SO_SET_I, &ds_nv_item );
    /*lint -restore */
    /*-----------------------------------------------------------------------
      Enable/Disable the appropriate data service options in SNM based
      on the service option set now in use
    -----------------------------------------------------------------------*/
    ds707_so_pkt_recal();
  }
  else if (tok_ptr->op == (NA|EQ|QU) )
  {
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                          "$QCSO: (0 - %d)\n",DS_SO_SET_COUNT-1);
  }
  else  if(tok_ptr->op == (NA|QU))
  {
     ds707_pkt_mgr_get_1x_profile_val(DS707_QCSO_VAL,(void *)&temp_val,0);
     rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                            rb_ptr->size,
                                            "$QCSO: %d\n",
                                            temp_val);
  }
  else
  {
    /* Not Supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_qcso_cmd */
#endif /* FEATURE_DS_AT_TEST_ONLY */
#endif /* FEATURE_DS_CHOOSE_SO */



/*===========================================================================
  FUNCTION DSAT707_EXEC_QCVAD_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCVAD command.
  Prearrangement setting. Respond to page message that has a voice service
  option with a page response that has a data service option.
  0 - Off
  1 - Fax for next call
  2 - Fax for all calls
  3 - Async. for next call
  4 - Async. for all calls

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcvad_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type result;
  db_items_value_type   dbi;
  dsat_num_item_type    temp_val; 

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  if (tok_ptr->op == (NA | QU)) 
  {
    db_get (DB_VOICE_AS_DATA, &dbi);
    DSATUTIL_SET_VAL(DSAT707_VEND_PARA_QCVAD_IDX,0,0,0,dbi.voice_as_data,NUM_TYPE)
  }

  result = dsatparm_exec_param_cmd(mode,
                                   tab_entry,
                                   tok_ptr,
                                   rb_ptr);

  if ((result == DSAT_OK) &&
     ((tok_ptr->op == (NA|EQ|AR)) || (tok_ptr->op == (NA))))
  {
    /*-----------------------------------------------------------------------
     The call manager does the work of changing the VAD setting.
     Note, the cast of the qcvad_val setting is OK because the
     CM type gets its values from the DB type, qcvad_val gets
     its value from the DB.
    -----------------------------------------------------------------------*/
    temp_val = (dsat_num_item_type) dsatutil_get_val(DSAT707_VEND_PARA_QCVAD_IDX,0,0,NUM_TYPE);
    
#ifdef FEATURE_DATA_MPSS_AT20_DEV
    cm_ph_cmd_answer_voice(NULL,
                           NULL,
                           dsatcm_client_id,
                           (cm_answer_voice_e_type)temp_val,
                           600
                           );
#else
	/*lint -save -e534*/
    cm_ph_cmd_answer_voice1(NULL,
                           NULL,
                           dsatcm_client_id,
                           (cm_answer_voice_e_type)temp_val,
                           600,
                           dsat_get_current_subs_id(TRUE)
                           );
    /*lint -restore */
#endif /* FEATURE_DATA_MPSS_AT20_DEV */
  }
  return result;
} /* dsat707_exec_qcvad_cmd */



/*===========================================================================
  FUNCTION DSAT707_EXEC_QCCAV_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCCAV command.
  Answer incoming voice call.

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qccav_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type  result       = DSAT_OK;
  sys_modem_as_id_e_type subs_id      = dsat_get_current_1x_subs_id();
  dsati_mode_e_type      current_mode = dsatcmdp_get_current_mode();

  /*-----------------------------------------------------------------*/
  if (IS_CDMA_MODE(current_mode) && dsatvoice_is_voice(subs_id))
  {
    result = dsatvoice_answer_cmd(subs_id);
  }
  else
  {
    result = DSAT_ERROR;
  }
  return result;
} /* dsat707_exec_qccav_cmd */

/*===========================================================================
  FUNCTION DSAT707_EXEC_QCCHV_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCCHV command.
  Hangs up incoming voice call.

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcchv_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type  result       = DSAT_OK;
  sys_modem_as_id_e_type subs_id      = dsat_get_current_1x_subs_id();
  dsati_mode_e_type      current_mode = dsatcmdp_get_current_mode();

  /*-----------------------------------------------------------------*/
  if(IS_CDMA_MODE(current_mode) && dsatvoice_is_voice(subs_id))
  {
    result = dsatvoice_end_voice_call(subs_id);
  }
  else
  {
    result = DSAT_ERROR;
  }
  return result;
} /* dsat707_exec_qcchv_cmd */

#ifdef FEATURE_IS2000_REL_A
/*===========================================================================
  FUNCTION DSAT707_EXEC_QCQOSPRI_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT$QCQOSPRI command.
  Sets desired value of QOS non-assured priority adjustment.
  (Can range from 0 to DS707_QOS_DESIRED_PRI_MAX (0xF).)

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.
===========================================================================*/
dsat_result_enum_type dsat707_exec_qcqospri_cmd
(
  dsat_mode_enum_type mode,                /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,         /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,       /*  Command tokens from parser  */
  dsm_item_type *rb_ptr                    /*  Place to put response       */
)
{
  dsat_num_item_type    temp_val   = DS707_QOS_DESIRED_PRI_DEFAULT;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  if (tok_ptr->op == (NA|EQ|AR) || (tok_ptr->op == NA)) 
  {
    if(FALSE == DSAT_VALIDATE_SET_707_PKTMGR(DS707_QCQOSPRI_VAL,DS707_QOS_DESIRED_PRI_MAX ) )
  {
      DS_ATCOP_ERROR_LOG_1("$QCQOSPRI: Invalid Number of arguements  =d", tok_ptr->args_found);
      return DSAT_ERROR;
    }
    /*-----------------------------------------------------------------------
      assume range checking is done beforehand
      ds707_qcqospri_val must be between
      DS707_QOS_DESIRED_PRI_MIN .. DS707_QOS_DESIRED_PRI_MAX
    -----------------------------------------------------------------------*/
    dsrlp_set_desired_qos_non_assur_pri( (byte) temp_val );
  }
  else if (tok_ptr->op == (NA|EQ|QU) )
  {
    rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                           rb_ptr->size,
                                          "$QCQOSPRI: (0 - %d)\n",DS707_QOS_DESIRED_PRI_MAX);
  }
  else  if(tok_ptr->op == (NA|QU))
  {
     ds707_pkt_mgr_get_1x_profile_val(DS707_QCQOSPRI_VAL,(void *)&temp_val,0);
     rb_ptr->used = (word) snprintf((char *)rb_ptr->data_ptr,
                                            rb_ptr->size,
                                            "$QCQOSPRI: %d\n",
                                            temp_val);
  }
  else
  {
    /* Not Supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_qcqospri_cmd */
#endif /* FEATURE_IS2000_REL_A    */


/*===========================================================================
  FUNCTION DSAT707_EXEC_HDRCSQ_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT^HDRCSQ command.

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.

===========================================================================*/
dsat_result_enum_type dsat707_exec_hdrcsq_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,      /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
  /* Read Command */
  if ( tok_ptr->op == (NA) )
  {
    uint16 hdr_rssi_intensity = 0;

    hdr_rssi_intensity = dsatcmif_cm_get_hdr_rssi_intensity_level(); 
    
    res_buff_ptr->used = (word)snprintf(
                              (char*)res_buff_ptr->data_ptr,
                               res_buff_ptr->size,
                               "^HDRCSQ: %d",
                               hdr_rssi_intensity);
  }
  /* Test Command */
  else if (tok_ptr->op == (NA|EQ|QU))
  {
    res_buff_ptr->used = 
      (word) snprintf ((char*)res_buff_ptr->data_ptr, 
                              res_buff_ptr->size,
                              "^HDRCSQ: (0, 20, 40, 60, 80, 99)" );
  }
  else
  {
    /* other commands are not supported */
    return DSAT_ERROR;
  }
  return DSAT_OK;
} /* dsat707_exec_hdrcsq_cmd */



/*===========================================================================
                       INTERNAL FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
  FUNCTION DSAT707_EXEC_RESET_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT^RESET command. This causes the
  device to reboot.

  DEPENDENCIES
  None

  RETURN VALUE
  Returns an enum that describes the result of the command execution.
  Possible values:
  DSAT_ERROR : if there was any problem in executing the command
  DSAT_OK : if it is a success.

  SIDE EFFECTS
  None.

===========================================================================*/
/*ARGSUSED*/
dsat_result_enum_type dsat707_exec_reset_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,      /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
)
{
  dsat_result_enum_type result = DSAT_ERROR;
  /* Read Command */
  if ( tok_ptr->op == (NA) )
  {
    sys_oprt_mode_e_type  new_opmode = SYS_OPRT_MODE_PWROFF;

    SET_PENDING(DSAT707_VEND_ACT_RESET_IDX, 0, DSAT_PENDING_RESET_WRITE);

    result = dsatcmif_change_operating_mode(new_opmode);
    if (DSAT_ASYNC_CMD != result)
    {
      SET_PENDING(DSAT707_VEND_ACT_RESET_IDX, 0, DSAT_PENDING_RESET_NONE);
    }
  }
  return result;
} /* dsat707_exec_reset_cmd */

#endif /* FEATURE_DATA_IS707 */
