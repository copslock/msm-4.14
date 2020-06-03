#ifndef DSAT707VEND_H
#define DSAT707VEND_H
/*===========================================================================

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

DESCRIPTION
  This file contains the definitions of data structures, defined and
  enumerated constants and function prototypes required for the
  data services AT command ( IS-707 mode vendor specific commands )
  processor.

EXTERNALIZED FUNCTIONS

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

dsat707_exec_hdrcsq_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^HDRCSQ command. It provides
  the intensity level of current hdr_rssi.

dsat707_exec_reset_cmd
  This function takes the result from the command line parser
  and executes it. It executes AT^RESET command. This command
  reboots the device.

  Copyright (c) 1995-2013, 2009-2011 by Qualcomm Technologies Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$PVCSPath: L:/src/asw/MM_DATA/vcs/dsat707vend.h_v   1.6   08 Jan 2003 12:27:58   sramacha  $
$Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/inc/dsat707vend.h#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $

when        who    what, where, why
--------    ---    ----------------------------------------------------------
03/13/12    dvk    Merged enabling mdr val update always during powerup.
13/11/11    ms     Fix compiler errors when MDR feature is turned off. 
07/05/11    nc     Added support for ^MODE,^CARDMODE,^SYSCONFIG,^SYSINFO,^DSCI.
05/10/10    kk     Added support for $$GPS* and $SP* commands.
05/10/10    kk     Added support for ^RESET .
05/10/10    kk     Added support for $QCGSN and $SPMSID.
05/10/10    kk     Added ^SYSINFO,^HDRCSQ commands. 
11/16/09    ca     Added support for MMGSDI AUTH commands.  
11/21/02    rsl    Fixed merge issues with at$qcchv.
10/15/02    ak     Added exec_qcchs, which is for control/hold.
10/03/02    atp    Fixed minor compilation problem by including .h.
09/24/02    atp    Added support for QOS. (1x Release-A feature).
07/12/02    ak     Extern for dat707_set_mdr_val.
04/03/02    rsl    Initial version of file.

===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"
#include "ds_profile_3gpp2.h"
#include "ds_profile.h"

#ifdef FEATURE_DATA_IS707
#include "dsati.h"

/*===========================================================================

                           Global Data 

===========================================================================*/


/*===========================================================================
                                 DATA STRUCTURES 
===========================================================================*/


/*===========================================================================
                                 EXTERN VARIABLES 
===========================================================================*/

/*===========================================================================
                       EXTERNAL FUNCTION DECLARATIONS
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
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
); /* dsat707_exec_qcprev_cmd */


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
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
); /* dsat707_exec_qcmdr_cmd */

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
); /* dsat707_exec_qcscrm_cmd */

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
); /* dsat707_exec_qctrtl_cmd */

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
);
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
); /* dsat707_exec_qcqnc_cmd */
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
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,    /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *rb_ptr           /*  Place to put response       */
); /* dsat707_exec_qcso_cmd */
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
); /* dsat707_exec_qcvad_cmd */

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
); /* dsat707_exec_qccav_cmd */

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
); /* dsat707_exec_qcchv_cmd */

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
); /* dsat707_exec_qcqospri_cmd */
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
); /* dsat707_exec_hdrcsq_cmd */



/*===========================================================================
  FUNCTION DSAT707_EXEC_RESET_CMD

  DESCRIPTION
  This function takes the result from the command line parser
  and executes it. It executes AT^RESET command.

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
dsat_result_enum_type dsat707_exec_reset_cmd
(
  dsat_mode_enum_type mode,             /*  AT command mode:            */
  const dsati_cmd_type *tab_entry,      /*  Ptr to cmd in parse table   */
  const tokens_struct_type *tok_ptr,    /*  Command tokens from parser  */
  dsm_item_type *res_buff_ptr           /*  Place to put response       */
); /* dsat707_exec_reset_cmd */

#endif /* FEATURE_DATA_IS707 */
#endif /* DSAT707VEND_H      */
