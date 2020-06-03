/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                D A T A   S E R V I C E S

                A T   C O M M A N D   
                
                ( E T S I  C A L L  M A N A G E R  I N T E R F A C E )
                
                P R O C E S S I N G

GENERAL DESCRIPTION
  This software unit contains functions for interfacing to Call Manager.

EXTERNALIZED FUNCTIONS

EXTERNALIZED FUNCTIONS INTERNAL TO DSAT UNIT
  dsatetsicmif_init_cmif
    CM Interface initialization function
    
  dsatetsicmif_initiate_voice_call
    This function requests CM to start a voice call.

  dsatetsicmif_sups_class_action
    This function intiates the action in Call Manager to perform supplemental
    service commands for classes.

  dsatetsicmif_sups_change_password
    This function intiates the change of supplementary services facility
    password.
    
  dsatetsicmif_sups_process_ussd
    This function intiates the action in Call Manager to perform supplemental
    service commands for Unstructured Supplementary Service Data (USSD).

  dsatetsicmif_cm_sups_cmd_handler
    This function is the handler function for the CM supplementary service
    commands.
    
  dsatetsicmif_cm_sups_event_handler
    This function is the handler function for the CM supplementary service
    related events

  dsatetsicmif_report_ccwa_result 
    This function handles the +CCWA unsolicited result triggered by incoming 
    call event

  dsatetsicmif_attach_ps
    Wrapper function to inform CM to attach to a PS domain. Called from CGATT
    command

  dsatetsicmif_detach_ps
    Wrapper function to inform CM to detach from the PS domain. Called from 
    CGATT command

 dsatetsicmif_init_pdp_connect_state
    This function intializes the PDP context profile connection state
    information.

  dsatetsicmif_deactivate_all_contexts
    This function initiates PDP context deactivation for all contexts.

  dsatetsicmif_query_networks
    This function invokes the CM API to get either the list of
    available networks from the access stratum or the preferred
    network list from the SIM/USIM.

  dsatetsicmif_change_network_registration
    This function invokes the CM API to change the network registration
    preference.


INITIALIZATION AND SEQUENCING REQUIREMENTS

   Copyright (c) 2002 - 2019 by Qualcomm Technologies Incorporated.
   All Rights Reserved.
   Qualcomm Confidential and Proprietary.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsatetsicmif.c#2 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/31/19   ks      Added support for MMODE NR5G while querying networks.
03/19/18   skc     Added SMS service class support for CCFC cmd.
02/23/18   skc     Added support for +CCFCU.
02/07/18   rg      Return error on +CUSD with invalid dcs 
01/23/18   skc     Added support for dial prefix *31# and #31#.
12/22/17   skc     Added enhancement on supplementary service for IP Call sub-phase 2.
12/15/17   skc     Added enhancement on supplementary service for IP Call.
09/13/17   skc     Added support for VT Call.
08/17/17   skc     Fixed api related issue in DSDS mode.
04/11/17   skc     Changes made to display local time instead of universal time.
06/17/16   skc     Fixed issue with time for dst adjustment.
06/06/16   skc     Fixed issue with USSD Notification and CMGS
04/17/15   tk      Fixed issue with unsupported SUPS error codes.
04/16/15   tk      Enhanced support for +CTZR command.
08/26/14   tk      Fixed issues in SUPS events handling.
08/12/14   pg      Modified DS Profile APIs to per subs.
07/29/14   sc      Added support for NV Refresh.
08/01/14   sc      Added support for linked MO and MT USSD sessions.
06/27/14   sc      Added support for Dynamic ATCoP.
06/11/14   sc      Fixed PLMN name issue having '@'.
02/15/14   pg      Added support for SGLTE+G.
04/17/14   sc      Fixed ATCoP KW errors.
03/14/14   tk      Optimized debug macros usage in ATCoP.
11/27/13   ab      Allowed NO_REPLY timer for all & conditional call forwarding.
11/14/13   tk      Fixed issues in online command state.
11/13/13   sc      Added support for $QCCSGCOPS command.
09/13/13   tk      ATCoP changes for LTE and DSDS concurrency solution.
07/23/13   tk      Fixed issue with default voice bearer capability.
06/05/13   tk      ATCoP changes for SGLTE support on Dime Plus.
05/16/13   sk      $QCCOPS command for Extension of network search.
04/02/13   tk      Fixed issues in single SIM device mode.
03/28/13   tk      Mainlined FEATURE_THIN_UI using new NV-EFS item.
02/22/13   tk      ATCoP - CM interface changes for Triton DSDA.
01/23/13   sk      DS command buffer memory reduction.
01/17/13   tk      Fixed KW errors.
01/04/13   tk      Fixed +CPAS and +CEER issues.
01/04/13   tk      ATCoP changes for DSDX C/G+G with True World Mode Support.
12/03/12   tk      Mainlined the PMIC RTC features.
11/30/12   tk      ATCoP changes for Triton DSDA.
10/12/12   sk      Support to add "No Change" when  value is not given in +COPS.
08/22/12   sk      Mainlining Nikel Changes.
07/16/12   nc      New interface changes for Manual PLMN selection.
06/15/12   sk      Fixed CEER issue.
05/18/12   tk      Migrated to MSG 2.0 macros
03/07/12   sk      Made CLCC common for all modes.
02/17/12   sk      Migrating Data related AT commands interface to unified MH.
01/27/12   sk      Fixed +CLCC in CDMA mode.
12/26/11   ad      Added Support the New Call Control Interface in Call Manager.
01/19/12   sk      Feature cleanup.
12/19/11   sk      QCDGEN case handled in CM_CALL_EVENT_END
09/27/11   ht      Included dsut header to support offtarget stubs.
06/24/11   bs      Added support for EF CFIS/CFF.
04/29/11   bs      Fixed $QCDGEN command to use COMPTASK.
04/07/10   ad      Fix to ignore unexpected password indication from CM.
03/03/11   nc      Fixed CLCC for Fusion.
03/03/11   bs      Added +CCFC support for allteleservices.
02/24/11   bs      Fixed Klocwork errors.
01/11/11   ad      Removed pending variable .
01/11/11   ad      Remove extern usage.used get/set API for command associated  
                   value pointers.
11/02/10   bs      Fixed +COPS query issue.
09/20/10   bs      Fixed +CGATT issue.
09/30/10   ad      Fixed Compilation warnings. 
09/01/10   ad      Fixed CCLK issue.
07/20/10   ad      Fixed compiler warning.
07/02/10   ad      Exclude obsolete clkrtc.h header file.
06/10/10   bs      Fixed +COPS query networks issue.
05/10/10   kk      Mainlining pending GOBI changes.
01/15/10   ua      Using new send_response_to_te API.
01/08/10   bs      Fixed +CGACT issue.
01/04/10   vk      Removing certain macros from PDP reg API header file
                   that cause problems with autogenerated RPC stub code
12/15/09   nc      Featurisation changes for LTE.
11/30/09   bs      Added +COPS support for LTE.
10/12/09   vk      PDP profile changes for IPv4v6 support
10/06/09   sa      Fixed unsolicited response handling.
09/10/09   nc      Fixed Klocwork errors. 
09/18/09   ss      DataCommon CMI SU level impacts.
05/20/09   bs      Fixed USSD issue.
06/14/09   nc      Fixed the border case of PDP activation for cid equals 16.
04/20/09   ua      Fixed issues related with call commands followed by +CIND query.
06/25/09   vk      Removing use of certain deprecated macros in pdp reg api
05/19/09   vk      Defeaturization of PDP registry for CMI
04/29/09   ua      Fixed compiler warnings. 
03/25/09   ua      Fixing CGEV for non-sock orig embedded calls. 
03/11/09   ua      Correcting an ASSERT statement.
01/30/09   ua      Added support of CGEV for DUN calls.
02/26/09   nc      Fixed Compiler Warnings.
01/19/09   bs      Added support for $qcctm.
12/23/08   sa      Replaced q_init with dsm_queue_init for watermark initialization.
12/18/08   bs      Fixed data class mapping in bsg conversion table.
12/12/08   ua      Fixed Off target lint errors.
11/28/08   ss      Off target Lint fix.
11/28/08   bs      Changed DSM LARGE item to SMALL.
10/23/08   bs      Added support for 1X AT Phonebook commands.
09/25/08   nc      Fixed number plan discrepancy for +CLCC between 1x+GSM and 
                   UMTS builds. 
06/25/08   nc      Fixed USSD broken charecter set problems
05/12/08   ua      Changes incorporated for GERAN WB AMR development.
03/24/08   bs      Fixed Klocwork criticals.
12/18/07   sa      Fixed data crash during downlink data transfer using the RAB
                   established by $QCDGEN command.
11/04/07   pp      Lint low - fixes.
09/07/07   ua      Work around for +CUSD abort for NW initated USSD operations.
06/22/07   sa      Added dsat_bsg_extra_conversion_table for conversion of basic service 
                   codes to class parameter which are not present in bsg_conversion_table.
05/18/07   sa      Corrected abort handler to send response to TE only when
                   it is not in the NOT_ABORTABLE state.
05/16/07   ua      Filtering off events which are not processed in ATCOP 
                   from the event call back function dsatetsicmif_sups_event_cb_func.
05/02/07   ua      Fixed lint medium errors. 
04/17/07   ua      COPS command should not wait for SS events when there is no change
                   in PLMN+AcT
04/05/07   ua      Added support for COPS DEREGISTRATION;
04/04/07   sa      Correcting COPS error handling due to CM cmd_buff unavailibity.
03/21/07   sa      Add support for BS code not being sent in case of class 255 
                   to map to All tele and bearerservices of MMI code.
03/08/07   ua      Corrected ss_oper value to processUnstructuredSS_Request 
                   for CUSD=2.
03/02/07   sa      Added outgoing voice call support when there is an active call  
                   for ATD command.
01/29/06   ua      Added support for GSM 7bit '@' character (0x00).
02/15/07   ss      Fixed lint high errors
02/13/07   pkp     Fixed RVCT compiler warnings.
01/30/07   ss      Replaced banned string API calls.
12/22/06   ua      Remove possibilty for duplicate ACK to USSD
12/14/06   sa      Fixed +CLIP <CLI validity>.
12/07/06   ua      Correcting etsicmif_report_sups_error to support for 
                   URC and final result code
11/17/06   sa      Added support for AllSynchronousServices.
11/06/06   ua      Sending CCFC's time parameter only for CFNRy. 
11/03/06   snb     Dual processor changes.
10/03/06   sa      Add support for bearer service code AllAsynchronousService 
09/14/06   snb     Correct etsicmif_default_bearer_capability octet 3.
08/01/06   snb     Clear query_mode on failure.
07/11/06   ua      aoc_set_acmmax and aoc_reset_acm modified according to new 
                   CM API's.
05/24/06   ua      Fixed critical Lint errors and corrected build issues concerned with 
                   mmgsdilib.h.
05/08/06   sa      Correct USSD report result handling for special characters.
03/01/06   snb     Correct USSD handling: CM expects ASCII input in 
                   cm_sups_cmd_process_uss() case only.
02/21/06   sa      Merged changes from Sirius Branch
                   -Removed activate & deactivate SS service functions.
                   -Buffering CLIP information is added during call setup 
01/26/06   snb     Correct size of and indexing into datagen_info array.
12/08/05   snb     Add IPV6 support
11/30/05   snb     Add support for +CGCMOD command.
11/29/05   ar      Do not ignore USSD events for ThinUI builds.
11/11/05   ar      Return immediately to command mode for voice calls.
11/09/05   snb     Lint errors.
09/20/05   snb     Clear "call was connected" boolean after all processing of 
                   end event completed, don't send basic service info on Supp
                   service query, correct +CCWA response.
08/15/05   snb     Allow secondary contexts for $QCDGEN.
08/11/05   snb     CM API change.
07/29/05   ar      Migrate CM SS events to watermark queue. 
07/25/05   snb     Changes to initialization of PDP state info and event 
                   handling to support WCDMA-mode $QCDGEN, clear +COPS command
                   state at end of processing. 
06/27/05   snb     Clear query mode after action complete, lint corrections.
05/03/05   tkk     Added initialization of context ID info.
04/29/05   ar      Add support for capturing call end status.
04/28/05   snb     Fix 6550 GSM-CDMA build issues.
04/22/05   snb     Changes to track call sequence number as described in 3GPP 
                   TS 22.030 section 6.5.5.1 and required by +CHLD command.
04/12/05   ar      Add support for +COPS access technology selection.
04/05/05   iv      Modified +CLCC to support CS data calls.
04/04/05   ar      Added support for +CIND command.
04/04/05   snb     Perform verification of "1 context without TFT" rule 
                   immediately before context is activated.
04/01/05   tkk     Few extern variables are pulled out of (WCDMA_PS | GSM_GPRS)
03/29/05   ar      Add CTM bit to speech bearer cap when TTY supported.
                   Add test for AUTO net preference when it matches current.  
03/15/05   tkk     Fix GPRS commands repository update issues.
03/15/05   sb      Fixes from testing the serializer changes.
03/03/05   snb     Redo Corrections to +CTZR/+CTZU event handling.
03/02/05   snb     Additional processing on call connect and end events for 
                   $QCDGEN command, lint corrections.
02/10/05   sb      Accessories related changes.
02/07/05   tkk     Added support for +CLIR command.
01/27/05   sb      Removed dsbyte.h header file. Not used anymore.
01/27/05   pdv     Merge from Sirius-ATCoP development.
01/27/05   pdv     Rebase from Mainline.
01/17/05   tkk     Added support for +CGEREP command.
01/10/05   tkk     Added support for +CGPADDR command.
01/05/05   iv      Added support for +CLCC command
12/30/04   tkk     Added support for CLIP, COLP commands.
12/29/04   snb     Changes for new character sets.
12/13/04   snb     Init primary_pdp boolean even when only primaries supported.
12/10/04   snb     Fix issue when FEATURE_SECONDARY_PDP not defined.
12/07/04   ar      Add support for +COPS command.
11/22/04   rr      Set higher order byte of profile number to DS_UMTS_PDP_
                   ATCOP_PROFILE_FAMILY to access profiles from 
                   "pdp_profile/atcop_profiles" directory
11/18/04   snb     Add +CSCS character set support.
11/09/04   snb     Use TFT info from EFS in packet originations via +CGACT
                   and lint corrections.
10/27/04   tkk     Added support for +CTZR,+CRZU commands.
10/15/04   ar      Add Advice of Charge support.
10/04/04   snb     Fix +CGACT activation problem.
09/10/04   sb      Secondary PDP changes
09/03/04   snb     Init number plan and type.
08/23/04   snb     Add new PRL preference parameter to CM function call.
05/12/04   snb     Fix +CGACT response when deactivating contexts activated via
                   embedded sockets and use local buffer for +CCWA unsolicited
                   response number.
03/19/04   snb     Added support for +CCWA command and correction to CM service
                   type in ETSI PD context activation.
12/04/03   ar      Accomodate CM API call info list query change to async.
12/03/03   ar      Fix context deactivation unmatched call ID problem.
11/18/03   ar      Use dsumtsps_call_orig_param_setup() instead of local 
                   routines for Call Manager parameter setup.
11/07/03   snb     Fix out of order responses due to local formatted response
                   buffers.
10/22/03   ar      Move Call Manager PH & SS API calls from ETSI to COMMON.
10/07/03   ar      Add +CREG and +CGREG support
09/23/03   snb     Add support for PS attach timeout failure
09/05/03   ar      Use local buffer for large SupS CM event payload.
08/06/03   ar      Add support for seeding minimum QoS on context activation.
07/16/03   snb     Remove mode equal DSAT_CMD assertions.
05/16/03   snb     Add featurized octet 3d & 3e to bearer capability struct.
04/18/03   vsk     Pass dns address to dsumtsps_gen_ipcp_req_pkt()
04/03/03   ar      Accomodate restructuring of SupS event info.
03/31/03   ar      Added command write_mode to context activation tracking.
03/12/03   ar      Generalize PDP context event handler for all packet calls.
03/07/03   ar      Remove FEATURE_DATA_ETSI_SUPSERV wrappers
02/21/03   ar      Add support for PDP context activation.
02/17/03   sb      New API for PS ATTACH and DETACH
02/06/03   ar      Fix abort behavior for +CLCK command.  Adjust error 
                   reporting for +CUSD event responses.  Lint corrections.
01/16/03   wx      Add clir and ccug support for voice call
01/16/03   ar      Renamed dsatetsicmif_send_respose_to_te(). Improved 
                   response generation in supserv class loop.
01/10/03   sb      Event handler support for +CGATT command
01/03/03   wx      modify default bearer capability as per mn_cm_exp.h#28
                   of msmshared umts.
12/10/02   ar      Added support for +CUSD command
11/21/02   ar      Added support for +CLCK and +CPWD commands
10/31/02   ar      Added support for +CCFC command
10/28/02   sb      Opened Voice call related handlers (moved to a common file)
10/12/02   npr     Feature wrapped relevent code with FEATURE_GSM_GPRS
04/08/02   ar      Created module.


===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"
#include "mcfg_nv_api.h"

#include <stringl/stringl.h>
#include "ps_utils.h"


#if defined(T_WINNT) || defined(T_UNIX)
#ifdef TEST_FRAMEWORK
#error code not present
#endif /* TEST_FRAMEWORK */
#endif /* WINNT || UNIX */



#ifdef FEATURE_DSAT_ETSI_MODE
/* this file should be included only in GSM or WCDMA mode */

#include <stdio.h>
#include <string.h>
#include "dsati.h"
#include "dsatetsime.h"
#include "dsatetsicmif.h"
#include "dsatetsictab.h"
#include "dsatetsicall.h"
#include "dsatcmif.h"
#include "dsatparm.h"
#include "dsatact.h"
#include "dsatvoice.h"
#include "cm.h"
#include "cmutil.h"
#include "amssassert.h"
#include "msg.h"
#include "err.h"

#include "mn_cm_exp.h"

#ifdef FEATURE_DSAT_ETSI_DATA
#include "ps_ppp_ipcp.h"
#include "dsumtsps.h"
#include "dsatetsipkt.h"
#include "sm.h"
#include "sm_common.h"
#include "dsatvend.h"
#endif /* FEATURE_DSAT_ETSI_DATA */


#include "time_jul.h"
#include "time_svc.h"

/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

  This section contains local definitions for constants, macros, types,
  variables and other items needed by this module.

===========================================================================*/

/*-------------------------------------------------------------------------
    Local definitions:
-------------------------------------------------------------------------*/

#define DSATETSICMIF_ASSERT(expression) \
         dsatetsicmif_assert_wrapper(__LINE__, expression)

#ifdef FEATURE_DSAT_ETSI_DATA

/*-------------------------------------------------------------------------
  These macros used to be in dsumtspdpreg.h but had to removed from there 
  due to compilation issues seen with pdp reg rpc stub code.
-------------------------------------------------------------------------*/
#define pdp_addr_ipv4 pdp_addr.pdp_addr_ipv4
#define pdp_addr_ipv6 pdp_addr.pdp_addr_ipv6

#define DSAT_MAX_CALLS_ENDED  1
extern cgatt_write_e_type dsatcmif_attach_write;
#endif /* FEATURE_DSAT_ETSI_DATA */
extern boolean                    dsat_clip_pending[DSAT_SYS_MODEM_AS_ID_MAX];
extern boolean                    dsat_colp_pending[DSAT_SYS_MODEM_AS_ID_MAX];
/*---------------------------------------------------------------------------
   Definitions for Supplementary Services support
---------------------------------------------------------------------------*/
#define DEFAULT_ALPHABET             0x00
#define ALPHABET_MASK                0xF0
  
/*----------------------------------------------------
  Table for conversion between reason parameter and
  network supplementary service codes.
  See ss_operation_code_T in mn_cm_exp.h
----------------------------------------------------*/
LOCAL const struct sc_conversion_s
{
  ss_operation_e_type operation;
  uint8   code; 
  byte    net_sc;           /* Network SC */
} sc_conversion_table[] =
{
  { DSAT_SSOP_CALL_FWD, (uint8)DSAT_CCFC_REASON_UNCOND,  (byte)cfu },
  { DSAT_SSOP_CALL_FWD, (uint8)DSAT_CCFC_REASON_BUSY  ,  (byte)cfb },
  { DSAT_SSOP_CALL_FWD, (uint8)DSAT_CCFC_REASON_NOREPLY, (byte)cfnry },
  { DSAT_SSOP_CALL_FWD, (uint8)DSAT_CCFC_REASON_NOTREACH,(byte)cfnrc },
  { DSAT_SSOP_CALL_FWD, (uint8)DSAT_CCFC_REASON_ALLCALL, (byte)allForwardingSS },
  { DSAT_SSOP_CALL_FWD, (uint8)DSAT_CCFC_REASON_ALLCOND, (byte)allCondForwardingSS },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_ALLB,         (byte)allCallRestrictionSS },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_AINB,         (byte)barringOfIncomingCalls },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_AOTB,         (byte)barringOfOutgoingCalls },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_BAIC,         (byte)baic },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_BAOC,         (byte)baoc },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_BICR,         (byte)bicRoam },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_BOIC,         (byte)boic },
  { DSAT_SSOP_FACILITY, (uint8)DSAT_SS_FAC_BOICHC,       (byte)boicExHC },
  { DSAT_SSOP_CALL_WT,  0,                               (byte)cw },
  { DSAT_SSOP_MAX,      0,           0 },
};
  
/*----------------------------------------------------
  Table for conversion between class parameter and
  basic service codes.  See mn_cm_exp.h
  Supplemental Service versus class restrictions are
  documented in 3GPP TS 22.004 Annex A
  Aggregate class values are specified in 3GPP TS 
  22.030 Annex C

  Note: Table must be organized: class aggregates first, ordered by 
  DSAT_SS_CLASS_ values(largest to smallest), then single class values
  ordered smallest to largest to avoid un-necessary multiple
  calls to Call Manager.
----------------------------------------------------*/
const bsg_conversion_s_type dsat_bsg_conversion_table[] =
{
  {DSAT_SS_CLASS_ALL,        NO_CODE,   0},
  {(ss_class_e_type)((uint16)DSAT_SS_CLASS_DATA_SYNC |
   (uint16)DSAT_SS_CLASS_DATA_ASYNC |
   (uint16)DSAT_SS_CLASS_DATA_PKT |
   (uint16)DSAT_SS_CLASS_DATA_PAD),   BS_CODE,   allBearerServices},
  {(ss_class_e_type)((uint16)DSAT_SS_CLASS_DATA_ASYNC | 
   (uint16)DSAT_SS_CLASS_DATA_PAD),   BS_CODE,   allAsynchronousServices },
  {(ss_class_e_type)((uint16)DSAT_SS_CLASS_DATA_SYNC |
   (uint16)DSAT_SS_CLASS_DATA_PKT),   BS_CODE,   allSynchronousServices },
  {(ss_class_e_type)((uint16)DSAT_SS_CLASS_VOICE |
   (uint16)DSAT_SS_CLASS_DATA  |
   (uint16)DSAT_SS_CLASS_FAX  |
   (uint16)DSAT_SS_CLASS_SMS),        TS_CODE,  allTeleservices},
  {(ss_class_e_type)((uint16)DSAT_SS_CLASS_VOICE |
   (uint16)DSAT_SS_CLASS_FAX  |
   (uint16)DSAT_SS_CLASS_SMS),        TS_CODE,  allTeleservices},
  {(ss_class_e_type)((uint16)DSAT_SS_CLASS_VOICE |
   (uint16)DSAT_SS_CLASS_DATA  |
   (uint16)DSAT_SS_CLASS_FAX),        TS_CODE,  allTeleservices_ExeptSMS},
  {DSAT_SS_CLASS_VOICE,      TS_CODE,   allSpeechTransmissionservices},
  {DSAT_SS_CLASS_DATA,       BS_CODE,   allBearerServices},
  {DSAT_SS_CLASS_FAX,        TS_CODE,   allFacsimileTransmissionServices},
  {DSAT_SS_CLASS_SMS,        TS_CODE,   allShortMessageServices},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   allDataCircuitSynchronous},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   allDataCircuitAsynchronous},
  {DSAT_SS_CLASS_DATA_PKT,   BS_CODE,   allDataPDS_Services},
  {DSAT_SS_CLASS_DATA_PAD,   BS_CODE,   allPadAccessCA_Services},
  {DSAT_SS_CLASS_MAX,        MAX_CODE,  0xFF},
};

/*----------------------------------------------------------------------------
  Table for conversion between class parameter and basic code services
  that can be returned by network and not present in dsat_bsg_conversion_table.
  This table is used by etsicmif_lookup_class function. It is possible 
  for the network to send a non-mappable basic code services value if UI 
  is used to setup the facility lock and then ATCOP is used to query it.
  See Spec 3GPP 29.002,Section 17.7.10.
------------------------------------------------------------------------------*/
const bsg_conversion_s_type dsat_bsg_extra_conversion_table[] =
{
  {DSAT_SS_CLASS_VOICE,      TS_CODE,   allTeleservices},
  {DSAT_SS_CLASS_VOICE,      TS_CODE,   telephony},
  {DSAT_SS_CLASS_VOICE,      TS_CODE,   emergencyCalls},
  {DSAT_SS_CLASS_DATA,       TS_CODE,   allDataTeleservices},
  {DSAT_SS_CLASS_FAX,        TS_CODE,   facsimileGroup3AndAlterSpeech},
  {DSAT_SS_CLASS_FAX,        TS_CODE,   automaticFacsimileGroup3},
  {DSAT_SS_CLASS_FAX,        TS_CODE,   facsimileGroup4},
  {DSAT_SS_CLASS_SMS,        TS_CODE,   shortMessageMT_PP},
  {DSAT_SS_CLASS_SMS,        TS_CODE,   shortMessageMO_PP},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   allDataCDS_Services},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   dataCDS_1200bps},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   dataCDS_2400bps},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   dataCDS_4800bps},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   dataCDS_9600bps},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   allAlternateSpeech_DataCDS},
  {DSAT_SS_CLASS_DATA_SYNC,  BS_CODE,   allSpeechFollowedByDataCDS},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   allDataCDA_Services},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   dataCDA_300bps},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   dataCDA_1200bps},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   dataCDA_1200_75bps},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   dataCDA_2400bps},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   dataCDA_4800bps},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   dataCDA_9600bps},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   allAlternateSpeech_DataCDA},
  {DSAT_SS_CLASS_DATA_ASYNC, BS_CODE,   allSpeechFollowedByDataCDA},
  {DSAT_SS_CLASS_DATA_PKT,   BS_CODE,   dataPDS_2400bps},
  {DSAT_SS_CLASS_DATA_PKT,   BS_CODE,   dataPDS_4800bps},
  {DSAT_SS_CLASS_DATA_PKT,   BS_CODE,   dataPDS_9600bps},
  {DSAT_SS_CLASS_DATA_PAD,   BS_CODE,   padAccessCA_300bps},
  {DSAT_SS_CLASS_DATA_PAD,   BS_CODE,   padAccessCA_1200bps},
  {DSAT_SS_CLASS_DATA_PAD,   BS_CODE,   padAccessCA_1200_75bps},
  {DSAT_SS_CLASS_DATA_PAD,   BS_CODE,   padAccessCA_2400bps},
  {DSAT_SS_CLASS_DATA_PAD,   BS_CODE,   padAccessCA_4800bps},
  {DSAT_SS_CLASS_DATA_PAD,   BS_CODE,   padAccessCA_9600bps},
  {DSAT_SS_CLASS_MAX,        MAX_CODE,  0xFF},
};
/* Constant to quickly identify all classes in ccfc_bsg_conversion_table[] */
/* which are applicable to specific commands.  Change to the table need    */
/*    to be reflected here                                                 */
const uint32 dsat_ccfc_allowed_classes = (uint16)DSAT_SS_CLASS_VOICE |
                                         (uint16)DSAT_SS_CLASS_DATA | 
                                         (uint16)DSAT_SS_CLASS_FAX | 
                                         (uint16)DSAT_SS_CLASS_SMS |
                                         (uint16)DSAT_SS_CLASS_DATA_SYNC | 
                                         (uint16)DSAT_SS_CLASS_DATA_PAD |
                                         (uint16)DSAT_SS_CLASS_DATA_ASYNC|
                                         (uint16)DSAT_SS_CLASS_DATA_PKT;
const uint32 dsat_clck_allowed_classes = (uint32)DSAT_SS_CLASS_ALL;
                                   
/* Per 22.004 Table A.1 the incoming, waiting call can be of any kind */
const uint32 dsat_ccwa_allowed_classes = (uint32)DSAT_SS_CLASS_ALL;

/*-------------------------------------------------------------------------
    Local Function declarations:
-------------------------------------------------------------------------*/

LOCAL void etsicmif_sups_exten_cmd_cb_func 
(
  void                        *data_block_ptr,
    /**< Pointer to the client-provided data block. */
  cm_sups_cmd_e_type           sups_cmd,
    /**< Indicate which SUPS command this error status is for. */
  cm_sups_cmd_err_e_type       sups_cmd_err,
    /**< SUPS command error code, indicating whether the command
         is rejected and, if so, the reason for the rejection. */
  cm_sups_cmd_err_cause_e_type err_cause,
  /**< Cause of Error to be used when sups_cmd_err is other than
       CM_SUPS_CMD_ERR_NOERR, currently it is supported only for
       CC_REJECT error. */
  cm_alpha_s_type              alpha
  /**< Modified alpha to be used only if alpha.len > 0. */  
);

LOCAL uint16 etsicmif_lookup_class
(
  bsg_code_type    bsg_type,        /* BSG type */
  uint8  bsg_code                   /* BSG code */
);

LOCAL dsat_result_enum_type etsicmif_format_class_response
(
  dsm_item_type * res_buff_ptr,             /* Result buffer */
  const byte * name,                        /* Command name  */
  const uint16 class,                       /* Class value   */
  const uint8 status,                       /* Status value  */
  const byte * tail                         /* Tail info buffer  */
);

LOCAL boolean etsicmif_sups_lookup_netsc ( void );

LOCAL dsat_result_enum_type etsicmif_sups_send_ussd_cmd ( void );

LOCAL dsat_result_enum_type etsicmif_sups_send_release( void );

LOCAL dsat_result_enum_type etsicmif_sups_send_ussd_request_response
(
  boolean                 error_present,         /* Error present */
  byte                    error_code,             /* Error code    */
  sys_modem_as_id_e_type  subs_id
);

LOCAL dsat_result_enum_type etsicmif_sups_send_password 
(
  const ds_at_sups_event_info_s_type *einfo_ptr,       /* Event info */
  sys_modem_as_id_e_type              subs_id
);

LOCAL dsat_result_enum_type etsicmif_sups_convert_alphabet
(
  boolean                 to_default,     /* Conversion flat    */
  uss_data_s_type *       uss_data_ptr,   /* USSD structure     */
  byte *                  string_ptr,     /* USSD string        */
  byte                    coding_scheme,  /* Data coding scheme */
  cm_uss_data_e_type      data_type       /* USSD data type  */
);

LOCAL void set_call_param_by_ccug
(
  cm_forward_cug_info_s_type    * cug_info_ptr,
  const dsat_num_item_type      * ccug_val
);

/*-------------------------------------------------------------------------
            Extern Function Declaration
-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
            Function Definitions:
-------------------------------------------------------------------------*/

/*===========================================================================

FUNCTION DSATETSICMIF_ASSERT_WRAPPER()

DESCRIPTION
  Wrapper function for DSATETSICMIF ASSERT
 
DEPENDENCIES 
  None

RETURN VALUE
  None
 
SIDE EFFECTS

===========================================================================*/
static void dsatetsicmif_assert_wrapper
(
  unsigned int     line_num,
  int              expression
)
{
  if ( !expression )
  {
    ERR_FATAL("DSATETSICMIF_FATAL at line:%d ",  
                                   line_num,0,0);  
  }
}/* dsatetsicmif_assert_wrapper */

/*===========================================================================

FUNCTION  DSATETSICMIF_INITIATE_VOICE_CALL

DESCRIPTION
  This function requests CM to start a voice call.

DEPENDENCIES
  None

RETURN VALUE
  returns an enum that describes the result of the command execution.
  possible values:
    FALSE :    if there was any problem in executing the command
    TRUE  :    if it succeeds.

SIDE EFFECTS
  None

===========================================================================*/
boolean dsatetsicmif_initiate_voice_call
(
  /* contains the dialing number and its attributes */
  const dsati_dial_str_type     * dial_ptr,

  /* returns the call id which is returned by cm */
  uint8 * call_id_ptr
)
{
  boolean                     call_status;
  cm_num_s_type               dial_num;
  cm_num_s_type               calling_number;
  cm_gw_cs_orig_params_s_type call_orig_params;
  cm_ip_orig_params_s_type    ip_orig_params;
  cm_orig_alpha_s_type        alpha_buf;
  sys_modem_as_id_e_type      subs_id = dsat_get_current_subs_id(FALSE);
  dsatetsicall_call_state_da_info  *call_da_val = NULL;
  cm_call_type_e_type         call_type = CM_CALL_TYPE_VOICE;
  uint8                       call_attr;

  DSATETSICMIF_ASSERT(dial_ptr->attrib & DIAL_ATTRIB_SEMICOLON);

  call_da_val = dsat_get_base_addr_per_subs(DSAT_CALL_DA_VALS, subs_id, FALSE);

  if(NULL == call_da_val)
  {
    return FALSE;
  }

  /* check number length */
  if (dial_ptr->len > CM_MAX_NUMBER_CHARS)
  {
    DS_AT_MSG1_HIGH("dial number is too long, %d", 
             dial_ptr->len);
    return FALSE;
  }
  if ( call_da_val->etsicall_num_active_calls > 0 )
  {
    /* Set the flag to filter CM_CALL_EVENT_MNG_CALLS_CONF event */
    call_da_val->etsicall_was_call_active = TRUE;
  }
  
  /* set dial num */
  memset(&dial_num, 0, sizeof(cm_num_s_type));
  cm_num_init( &dial_num );

  /* dial_ptr->len is <= CM_MAX_NUMBER_CHARS (64), the cast is safe */
  cm_num_fill( &dial_num,
               (dial_ptr->valid_dial_prefix) ? (dial_ptr->num + dial_ptr->len_dial_prefix) : dial_ptr->num,
               (dial_ptr->valid_dial_prefix) ? (byte)(dial_ptr->len - dial_ptr->len_dial_prefix):(byte) dial_ptr->len,
               CM_DIGIT_MODE_4BIT_DTMF);

  /* We don't have calling number or alpha, 
     just init calling number and alpha */
  memset(&calling_number, 0, sizeof(cm_num_s_type));
  cm_num_init(&calling_number);
  
  memset(&alpha_buf, 0, sizeof(cm_orig_alpha_s_type));

  /* set mode specific parameters */
  memset(&call_orig_params,CM_CALL_CMD_PARAM_DEFAULT_VALUE,sizeof(call_orig_params));
  memset(&ip_orig_params, 0, sizeof(cm_ip_orig_params_s_type));

  /* Fill up call setup parameter with default voice bearer capabilities
   */
  call_orig_params.bc_repeat_indicator.repeat_indication = 0;
#ifdef FEATURE_DUAL_SIM 
  cm_util_set_default_voice_bearer_cap_per_sub(
                     &call_orig_params.bearer_capability_1,subs_id);
#else
  cm_util_set_default_voice_bearer_cap( &call_orig_params.bearer_capability_1 );
#endif
#ifdef FEATURE_TTY
  if((dsat_num_item_type)dsatutil_get_val(
                         DSAT_VENDOR_QCCTM_IDX,0,0,NUM_TYPE) == 1)
  {
    call_orig_params.bearer_capability_1.ctm = CTM_SUPPORTED;
  }
#endif /* FEATURE_TTY */
  
  /* fill out clir fields */
  if(dial_ptr->attrib & DIAL_ATTRIB_UP_I)
  {
    call_orig_params.cm_clir = CM_CLIR_INVOCATION;
    calling_number.pi = DSAT_PI_RESTRICTED;
    ip_orig_params.call_attrib.is_ip_pi_valid = TRUE;
  }
  else if(dial_ptr->attrib & DIAL_ATTRIB_DN_I)
  {
    call_orig_params.cm_clir = CM_CLIR_SUPPRESSION;
    calling_number.pi = DSAT_PI_ALLOWED;
    ip_orig_params.call_attrib.is_ip_pi_valid = TRUE;
  }
  else
  {
    call_orig_params.cm_clir = CM_CLIR_DEFAULT;
    ip_orig_params.call_attrib.is_ip_pi_valid = FALSE;
  }

  /* fill up forward_cug_info */
  if(dial_ptr->attrib & DIAL_ATTRIB_UP_G)
  {
    /* enable CUG temporary mode */
    call_orig_params.forward_cug_info.present = TRUE;
    set_call_param_by_ccug(&call_orig_params.forward_cug_info, 
      (const dsat_num_item_type *)dsatutil_get_val(DSATETSI_EXT_ACT_CCUG_ETSI_IDX,0,0,STR_TYPE));
  }
  else if(dial_ptr->attrib & DIAL_ATTRIB_DN_G)
  {
    /* disable CUG temporary mode */
    call_orig_params.forward_cug_info.present = FALSE;
  }
  else
  {
    /* use the parameters specified by +CCUG */
    if((dsat_num_item_type)dsatutil_get_val(DSATETSI_EXT_ACT_CCUG_ETSI_IDX,0,0,NUM_TYPE) == 0)
    {
      call_orig_params.forward_cug_info.present = FALSE;
    }
    else
    {
      call_orig_params.forward_cug_info.present = TRUE;
      set_call_param_by_ccug(&call_orig_params.forward_cug_info, 
        (const dsat_num_item_type *)dsatutil_get_val(DSATETSI_EXT_ACT_CCUG_ETSI_IDX,0,0,STR_TYPE));
    }
  }

  if ((*dial_ptr->num == '+') ||
      (dial_ptr->attrib & DIAL_ATTRIB_START_PLUS_AFTER_VALID_DIAL_PREFIX))
  {
    dial_num.number_type = (uint8) CM_NUM_TYPE_INTERNATIONAL;
  }
  else
  {
    dial_num.number_type = (uint8) CM_NUM_TYPE_UNKNOWN;
  }
  
  dial_num.number_plan = (uint8) CM_NUM_PLAN_ISDN;
  calling_number.number_plan = (uint8) CM_NUM_PLAN_ISDN;

  /* Check if call is initiated for Video call */
  if ( (dsat_num_item_type)dsatutil_get_val(DSAT_VENDOR_QCCALLATTR_IDX,0,0,NUM_TYPE) == DSAT_QCCALLATTR_CALL_TYPE_VT )
  {
    call_type = CM_CALL_TYPE_VT;
    call_attr = (dsat_num_item_type)dsatutil_get_val(DSAT_VENDOR_QCCALLATTR_IDX,0,1,NUM_TYPE);
    ip_orig_params.call_attrib.audio_attrib = CM_CALL_ATTRIB_TX_RX;
    /* Set video attributes based on AT$QCCALLATTR setting */
    if(call_attr == DSAT_QCCALLATTR_CALL_ATTR_RX)
    {
      ip_orig_params.call_attrib.video_attrib = CM_CALL_ATTRIB_RX_ONLY;
    }
    else if(call_attr == DSAT_QCCALLATTR_CALL_ATTR_TX)
    {
      ip_orig_params.call_attrib.video_attrib = CM_CALL_ATTRIB_TX_ONLY;
    }
    else
    {
     ip_orig_params.call_attrib.video_attrib = CM_CALL_ATTRIB_TX_RX;
    }
  }

  call_status = cm_mm_call_cmd_orig_cc_per_subs_exten(dsatcmif_call_cmd_cb_exten_func,
  	                             NULL,
  	                             dsatcm_client_id,
  	                             call_type,
  	                             CM_SRV_TYPE_AUTOMATIC,
  	                             &calling_number,
  	                             &dial_num,
/* No alpha tag we don't support a search in ph book we can add it as a enhancement */
  	                             &alpha_buf,
  	                             NULL, /* CDMA parameters */
  	                             &call_orig_params, /* GW CS mode specific data*/
  	                             NULL, /* PS parameters */
  	                             &ip_orig_params,   /* Data related to IP Call */
  	                             CM_CALL_ID_INVALID,
                                     CM_ORIG_CLIENT_CATEG_USER,
                                     dsat_get_current_subs_id(FALSE),
                                     call_id_ptr);

  return call_status;
} /* dsatetsicmif_initiate_call */


#ifdef FEATURE_ETSI_ATTACH

/*===========================================================================

FUNCTION  DSATETSICMIF_ATTACH_PS

DESCRIPTION
  Wrapper function to inform CM to attach to a PS domain. Called from CGATT
  command

DEPENDENCIES
  None

RETURN VALUE
  returns an enum that describes the result of the command execution.
  possible values:
    DSAT_ERROR :    if there was any problem in executing the command
    DSAT_OK :       if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_attach_ps ( void )
{
  
  boolean                cm_result;
  cm_pref_chg_req_s_type        user_pref;
  (void ) cm_pref_change_req_init( &user_pref );

#ifdef FEATURE_DUAL_SIM
  sys_modem_as_id_e_type subs_id = dsat_get_current_subs_id(FALSE);

    /* When the device mode is Dual SIM Dual Standby, allow the CGATT command only on
       Default Data Subscription. */
    if((SYS_MODEM_DEVICE_MODE_DUAL_SIM_DUAL_STANDBY == dsatcmif_get_device_mode()) &&
       (dsat_subs_info[subs_id].is_default_data == FALSE))
    {
     DS_ATCOP_ERROR_LOG_0("Pkt Attach not valid on this subscription");
      return DSAT_ERROR;
    }
#endif /* FEATURE_DUAL_SIM */

  user_pref.cmd_cb_func = dsatcmif_ph_cmd_cb_func;
  user_pref.data_block_ptr= NULL;
  user_pref.client_id = dsatcm_client_id;
  user_pref.asubs_id = subs_id;
  user_pref.pref_term = CM_PREF_TERM_PWR_CYCLE;
  user_pref.misc_pref.pref_duration = 0;
  user_pref.misc_pref.acq_order_pref = CM_GW_ACQ_ORDER_PREF_NO_CHANGE;
  user_pref.mode_band.bands.band = SD_SS_BAND_PREF_NO_CHANGE;
  user_pref.misc_pref.prl_pref = CM_PRL_PREF_NO_CHANGE;
  user_pref.misc_pref.roam_pref = CM_ROAM_PREF_NO_CHANGE;
  user_pref.hybr_pref = CM_HYBR_PREF_NO_CHANGE;
  user_pref.srv_domain_pref = CM_SRV_DOMAIN_PREF_PS_ATTACH;
  user_pref.network_sel_mode_pref = CM_NETWORK_SEL_MODE_PREF_NO_CHANGE;
  user_pref.plmn_ptr = NULL;
  cm_result = cm_ph_cmd_pref_change_req(&user_pref);

  if (!cm_result)
  {
    /* ERROR tell user about it */
    return DSAT_ERROR;
  }
  else
  {
    /* We are in WRITE mode set the flag */
    /* Will ge used to when we get the service changed event */
    dsatcmif_attach_write = DSAT_CGATT_ACTIVATE;
    return DSAT_ASYNC_CMD;
  }

} /* dsatetsicmif_attach_ps */



/*===========================================================================

FUNCTION  DSATETSICMIF_DETACH_PS

DESCRIPTION
  Wrapper function to inform CM to detach from the PS domain. Called from 
  CGATT command

DEPENDENCIES
  None

RETURN VALUE
  returns an enum that describes the result of the command execution.
  possible values:
    DSAT_ERROR :    if there was any problem in executing the command
    DSAT_OK :       if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_detach_ps ( void )
{
  boolean                cm_result;
  cm_pref_chg_req_s_type        user_pref;
  (void) cm_pref_change_req_init( &user_pref );

#ifdef FEATURE_DUAL_SIM
  sys_modem_as_id_e_type subs_id = dsat_get_current_subs_id(FALSE);
  if (!IS_VALID_SUBS_ID(subs_id))
  {
    return DSAT_ERROR;
  }
#endif /* FEATURE_DUAL_SIM */

  dsatcmif_attach_write = DSAT_CGATT_DEACTIVATE;

#ifdef FEATURE_DUAL_SIM
    /* When the device mode is Dual SIM Dual Standby, allow the CGATT command only on
       Default Data Subscription. */
    if((SYS_MODEM_DEVICE_MODE_DUAL_SIM_DUAL_STANDBY == dsatcmif_get_device_mode()) &&
       (dsat_subs_info[subs_id].is_default_data == FALSE))
    {
     DS_ATCOP_ERROR_LOG_0("Pkt Dettach not valid on this subscription");
      dsatcmif_attach_write = DSAT_CGATT_MAX;
      return DSAT_ERROR;
    }
#endif /* FEATURE_DUAL_SIM */

  user_pref.cmd_cb_func = dsatcmif_ph_cmd_cb_func;
  user_pref.data_block_ptr= NULL;
  user_pref.client_id = dsatcm_client_id;
  user_pref.asubs_id = subs_id;
  user_pref.pref_term = CM_PREF_TERM_PWR_CYCLE;
  user_pref.misc_pref.pref_duration = 0;
  user_pref.misc_pref.acq_order_pref = CM_GW_ACQ_ORDER_PREF_NO_CHANGE;
  user_pref.mode_band.bands.band = SD_SS_BAND_PREF_NO_CHANGE;
  user_pref.misc_pref.prl_pref = CM_PRL_PREF_NO_CHANGE;
  user_pref.misc_pref.roam_pref = CM_ROAM_PREF_NO_CHANGE;
  user_pref.hybr_pref = CM_HYBR_PREF_NO_CHANGE;
  user_pref.srv_domain_pref = CM_SRV_DOMAIN_PREF_PS_DETACH;
  user_pref.network_sel_mode_pref = CM_NETWORK_SEL_MODE_PREF_NO_CHANGE;
  user_pref.plmn_ptr = NULL;
  cm_result = cm_ph_cmd_pref_change_req(&user_pref);

  if (!cm_result)
  {
    /* ERROR tell user about it */
    dsatcmif_attach_write = DSAT_CGATT_MAX;
    return DSAT_ERROR;
  }
  else
  {
    /* We are in WRITE mode set the flag */
    return DSAT_ASYNC_CMD;
  }
} /* dsatetsicmif_detach_ps */

#endif /* FEATURE_ETSI_ATTACH */

#ifdef FEATURE_DSAT_ETSI_DATA

/*===========================================================================

FUNCTION DSATETSICMIF_INIT_PDP_CONNECT_STATE

DESCRIPTION
  This function intializes the PDP context profile connection state
  information.
  
DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None
  
===========================================================================*/
void dsatetsicmif_init_pdp_connect_state ( void )
{
  memset ((void*)&dsat_pdp_state, 0x0,
          sizeof(dsat_pdp_connect_s_type));
  return;
} /* dsatetsicmif_init_pdp_connect_state */

#endif /* FEATURE_DSAT_ETSI_DATA */



/*===========================================================================

FUNCTION DSATETSICMIF_SUPS_CLASS_ACTION

DESCRIPTION
  This function intiates the action in Call Manager to perform supplemental
  service commands for classes.  The user parameters stored in regional variable
  dsat_ss_cm_data are expected to be validated. This routine populates
  the Call Manager API structures.
  
DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  Command is sent to Call Manager
  
===========================================================================*/
dsat_result_enum_type dsatetsicmif_sups_class_action
(
  boolean                    first_call,       /* Flag for recursive loop   */
  sys_modem_as_id_e_type     subs_id
)
{
  uint8 index = 0;
  uint8 bsg_code = 0;
  bsg_code_type bsg_type = MAX_CODE;
  boolean cm_result = TRUE;
  mcs_sups_params_s_type dsat_ss_params;
  char                        dsat_mmi_buf[DSAT_MAX_MMI_STRING_LEN];
  cm_num_s_type               dsat_dialed_digits;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;

  memset(&dsat_mmi_buf[0],0,DSAT_MAX_MMI_STRING_LEN);
  memset(&dsat_ss_params,CM_CALL_CMD_PARAM_DEFAULT_VALUE,sizeof(mcs_sups_params_s_type));
  memset(&dsat_dialed_digits,CM_CALL_CMD_PARAM_DEFAULT_VALUE,sizeof(cm_num_s_type));

  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);

  if(NULL == sups_ms_val)
  {
    return DSAT_ERROR;
  }

  /* Check to see if this is the initial call in possible series */
  if (first_call)
  {
    /* No classes yet processed, nothing currently pending */
    sups_ms_val->dsat_ss_cm_data.done_class = 0;
    sups_ms_val->dsat_ss_cm_data.pending_msg = FALSE;
    sups_ms_val->dsat_ss_cm_data.pending_rsp = FALSE;

    /* Lookup Network Service Code */
    if (!etsicmif_sups_lookup_netsc())
    {
      DS_ATCOP_ERROR_LOG_0("Could not determine net SC");
      return DSAT_ERROR;
    }
  }
  
  /* See if we have checked all classes specified on AT command line */
  if (sups_ms_val->dsat_ss_cm_data.user_data.class == sups_ms_val->dsat_ss_cm_data.done_class) 
  {
    dsm_item_type * res_buff_ptr;
      
    /* Clear password if FACILITY operation */
    if (DSAT_SSOP_FACILITY == sups_ms_val->dsat_ss_cm_data.user_data.operation)
    {
      dsatutil_reset_password (
        sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.passwd,
        sizeof(sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.passwd));
    }

    /* Send a line terminator at end of response series (if any) */
    if (TRUE == sups_ms_val->dsat_ss_cm_data.pending_rsp)
    {
      res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, FALSE);
      res_buff_ptr->data_ptr[res_buff_ptr->used++] = '\n';

      /* format response, send the response to the user as information text, */
      /* Clear the regional block indications flag, & free raw_rsp_ptr */
      dsatcmdp_handle_async_cmd_rsp(res_buff_ptr, DSAT_INTERMEDIATE_RSP);  

      sups_ms_val->dsat_ss_cm_data.pending_rsp = FALSE;
    }

    /* Terminate series of calls */
    SET_PENDING(DSATETSI_EXT_ACT_CCFC_ETSI_IDX, 0, DSAT_PENDING_FALSE)
    return DSAT_OK;
  }

  /* Current class is all classes specified in argument to AT command and 
     not yet processed */
  sups_ms_val->dsat_ss_cm_data.curr_class = 
    sups_ms_val->dsat_ss_cm_data.user_data.class ^ sups_ms_val->dsat_ss_cm_data.done_class;
  
  /* Check for out of control loop (should not happen) */
  if (((uint16)DSAT_SS_CLASS_ALL < sups_ms_val->dsat_ss_cm_data.curr_class) ||
      ((uint16)DSAT_SS_CLASS_MIN == sups_ms_val->dsat_ss_cm_data.curr_class))
  {
    DS_AT_MSG1_HIGH("Class loop exceeds bounds: %d",
             sups_ms_val->dsat_ss_cm_data.curr_class);
    SET_PENDING(DSATETSI_EXT_ACT_CCFC_ETSI_IDX, 0, DSAT_PENDING_FALSE)
    return DSAT_ERROR;
  }
  
  /* Find largest aggregate class contained within current class,
     failing to find an aggregate class choose smallest single class -
     this requires correct organization of dsat_bsg_conversion_table,
     it must start with aggregate classes, largest to smallest then single
     classes smallest to largest */
  index = 0;
  while ( DSAT_SS_CLASS_MAX != dsat_bsg_conversion_table[index].class )
  {
    /* This same comparison will handle aggregate or single class */
    if ( ( sups_ms_val->dsat_ss_cm_data.curr_class & 
           (uint16)dsat_bsg_conversion_table[index].class ) ==
         (uint16)dsat_bsg_conversion_table[index].class )
    {
      /* Use its bsg type and code and possibly restrict current class to class 
         value found */
      bsg_type = dsat_bsg_conversion_table[index].bsg_type;
      bsg_code = dsat_bsg_conversion_table[index].net_bsg_code;
      sups_ms_val->dsat_ss_cm_data.curr_class = (uint16)dsat_bsg_conversion_table[index].class;
      break;
    }
    index++;
    if(index >= ARR_SIZE(dsat_bsg_conversion_table))
    {
      DS_ATCOP_ERROR_LOG_0("Invalid Access into dsat_bsg_conversion_table");
      SET_PENDING(DSATETSI_EXT_ACT_CCFC_ETSI_IDX, 0, DSAT_PENDING_FALSE)
      return DSAT_ERROR;
    }
  }
  DSATETSICMIF_ASSERT( bsg_type != MAX_CODE);

  /* Invoke the correct Call Manager API */  
  DS_AT_MSG1_MED("Sending message to CM for class: %d",
           dsat_bsg_conversion_table[index].class);

  switch (sups_ms_val->dsat_ss_cm_data.user_data.operation)
  {
    /* Call forwarding class action */
    case DSAT_SSOP_CALL_FWD:
  /* Call appropriate API based on Mode */
      switch (sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.mode)
      {
        case DSAT_CCFC_MODE_DISABLE:
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.present =
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.code_type = bsg_type;
          
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_DISABLE;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);
#ifdef FEATURE_DUAL_SIM
          cm_result = cm_sups_cmd_deactivate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func, 
                                             &sups_ms_val->dsat_ss_cm_data,
                                             dsatcm_client_id,
                                             &sups_ms_val->dsat_ss_cm_data.cm_parms.deact,
                                             &dsat_dialed_digits,
                                             CM_ORIG_CLIENT_CATEG_USER,
                                             TRUE,
                                             subs_id);
#else
          cm_result = cm_sups_cmd_deactivate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                             &sups_ms_val->dsat_ss_cm_data,
                                             dsatcm_client_id,
                                             &sups_ms_val->dsat_ss_cm_data.cm_parms.deact,
                                             &dsat_dialed_digits,
                                             CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
      
        case DSAT_CCFC_MODE_ENABLE:
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.present = 
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_ENABLE;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM
          cm_result = cm_sups_cmd_activate_cc_exten_per_subs (etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.act,
                                           &dsat_dialed_digits,
                                           CM_ORIG_CLIENT_CATEG_USER,
                                             TRUE,
                                             subs_id);
#else
          cm_result = cm_sups_cmd_activate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.act,
                                           &dsat_dialed_digits,
                                            CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
      
        case DSAT_CCFC_MODE_QUERY:
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          /* set the basic_service present flag if GCF testing is enabled */
          if ( TRUE == mcfg_gcf_nv_get_status() )
            {
              sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.present = 
              (NO_CODE == bsg_type)? FALSE: TRUE;
            }
            else
            {
              sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.present =  FALSE;
            }
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_QUERY;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));

          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM      
          cm_result = cm_sups_cmd_interrogate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func, 
                                              &sups_ms_val->dsat_ss_cm_data,
                                              dsatcm_client_id,
                                              &sups_ms_val->dsat_ss_cm_data.cm_parms.interr,
                                              &dsat_dialed_digits,
                                              CM_ORIG_CLIENT_CATEG_USER,
                                              TRUE,
                                              subs_id);
#else
          cm_result = cm_sups_cmd_interrogate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                              &sups_ms_val->dsat_ss_cm_data,
                                              dsatcm_client_id,
                                              &sups_ms_val->dsat_ss_cm_data.cm_parms.interr,
                                              &dsat_dialed_digits,
                                               CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
      
        case DSAT_CCFC_MODE_REG:
          sups_ms_val->dsat_ss_cm_data.cm_parms.reg.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.reg.basic_service.present = 
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.reg.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.reg.basic_service.code_type = bsg_type;

          /* Load address structure */
          if (CM_FORWARD_TO_NUMBER == sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.fwd_type &&
              0 < sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.alength )
          {
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_num.present = TRUE;
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_num.length =
            sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.alength;
            (void) dsatutil_memscpy((void*)sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_num.data,
                  CM_CALLED_PARTY_BCD_NO_LENGTH,
                  (void*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.addr,
                  CM_CALLED_PARTY_BCD_NO_LENGTH);
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_type = CM_FORWARD_TO_NUMBER;
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_uri = NULL;
          }
          else if (CM_FORWARD_TO_URI == sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.fwd_type &&
                   NULL != sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.fwd_to_uri &&
                   0 < sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.fwd_to_uri->fwd_to_uri_length)
          {
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_type = 
                   sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.fwd_type;
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_uri = 
                   sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.fwd_to_uri;
          }
          else
          {
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_num.present = FALSE;
          }
      
          /* Load subaddress structure (length in first byte) */
          if (0 < sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.subaddr[0])
          {
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_subaddr.present = TRUE;
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_subaddr.length =
              (byte)strlen((char*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.subaddr);
            (void) dsatutil_memscpy((void*)sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_subaddr.data,
                  CM_CALLED_PARTY_SUBADDRESS_LENGTH,
                  (void*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.subaddr,
                   CM_CALLED_PARTY_SUBADDRESS_LENGTH);
          }
          else
          {
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_subaddr.present = FALSE;
          }

          if ( (sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.reason 
                == DSAT_CCFC_REASON_NOREPLY) || 
               (sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.reason 
                == DSAT_CCFC_REASON_ALLCALL) ||
               (sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.reason 
                == DSAT_CCFC_REASON_ALLCOND))
          {
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.nr_timer.present = TRUE;
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.nr_timer.timer_value =
            sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.time;
          }
          else
          {
            sups_ms_val->dsat_ss_cm_data.cm_parms.reg.nr_timer.present = FALSE;
          }
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_REG;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          if(sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_num.present ||
             (NULL != sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_uri &&
              sups_ms_val->dsat_ss_cm_data.cm_parms.reg.fwd_to_uri->fwd_to_uri_length > 0))
          {
            dsat_ss_params.cmd.reg.number =(char *)dsatetsicmif_return_ccfc_reg_num();
          }
          
          if(sups_ms_val->dsat_ss_cm_data.cm_parms.reg.nr_timer.present)
          {
            dsat_ss_params.cmd.reg.nr_timer = sups_ms_val->dsat_ss_cm_data.cm_parms.reg.nr_timer.timer_value;
          }
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
            DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));         
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

          if(sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.sups_time_info.time_present)
          {
            memset(&sups_ms_val->dsat_ss_cm_data.cm_parms.reg.sups_time_info, 0, 
                   sizeof(cm_ip_sups_time_info_s_type));
            (void) dsatutil_memscpy((void*)&sups_ms_val->dsat_ss_cm_data.cm_parms.reg.sups_time_info, 
                                sizeof(cm_ip_sups_time_info_s_type),
                                (void*)&sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.sups_time_info,
                                sizeof(cm_ip_sups_time_info_s_type));
          }

#ifdef FEATURE_DUAL_SIM         
          cm_result = cm_sups_cmd_register_cc_exten_per_subs (etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.reg,
                                           &dsat_dialed_digits,
                                            CM_ORIG_CLIENT_CATEG_USER,
                                           TRUE,
                                           subs_id);
#else
          cm_result = cm_sups_cmd_register_exten(etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.reg,
                                           &dsat_dialed_digits,
                                            CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;

        case DSAT_CCFC_MODE_ERASURE:
          sups_ms_val->dsat_ss_cm_data.cm_parms.erase.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.erase.basic_service.present = 
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.erase.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.erase.basic_service.code_type = bsg_type;
          
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_ERASURE;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM
         cm_result = cm_sups_cmd_erase_cc_exten_per_subs (etsicmif_sups_exten_cmd_cb_func, 
                                                     &sups_ms_val->dsat_ss_cm_data,
                                                     dsatcm_client_id,
                                                     &sups_ms_val->dsat_ss_cm_data.cm_parms.erase,
                                                     &dsat_dialed_digits,
                                                     CM_ORIG_CLIENT_CATEG_USER,
                                                     TRUE,
                                                     subs_id);

#else
          cm_result = cm_sups_cmd_erase_exten(etsicmif_sups_exten_cmd_cb_func, 
                                        &sups_ms_val->dsat_ss_cm_data,
                                        dsatcm_client_id,
                                        &sups_ms_val->dsat_ss_cm_data.cm_parms.erase,
                                        &dsat_dialed_digits,
                                         CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */

          break;
    
        default:
          DS_ATCOP_ERROR_LOG_1("Unrecognized mode value: =d",
                    sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.mode);
          return DSAT_ERROR;
      }
      break;

    /* Facility class action */
    case DSAT_SSOP_FACILITY:
      /* Call appropriate API based on Mode */
      switch (sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.mode)
      {
        case DSAT_CLCK_MODE_UNLOCK:
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.present = 
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_DISABLE;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM
          cm_result = cm_sups_cmd_deactivate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func, 
                                             &sups_ms_val->dsat_ss_cm_data,
                                             dsatcm_client_id,
                                             &sups_ms_val->dsat_ss_cm_data.cm_parms.deact,
                                             &dsat_dialed_digits,
                                             CM_ORIG_CLIENT_CATEG_USER,
                                             TRUE,
                                             subs_id);
#else
          cm_result = cm_sups_cmd_deactivate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                             &sups_ms_val->dsat_ss_cm_data,
                                             dsatcm_client_id,
                                             &sups_ms_val->dsat_ss_cm_data.cm_parms.deact,
                                             &dsat_dialed_digits,
                                             CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
      
        case DSAT_CLCK_MODE_LOCK:
          /* Password is not sent in initial message.  If network */
          /* requires password, if will send subsequent request */
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.present = 
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_ENABLE;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM
          cm_result = cm_sups_cmd_activate_cc_exten_per_subs (etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.act,
                                           &dsat_dialed_digits,
                                           CM_ORIG_CLIENT_CATEG_USER,
                                           TRUE,
                                           subs_id);
#else
          cm_result = cm_sups_cmd_activate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.act,
                                           &dsat_dialed_digits,
                                            CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
      
        case DSAT_CLCK_MODE_QUERY:
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.present = FALSE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_QUERY;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM      
          cm_result = cm_sups_cmd_interrogate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func, 
                                              &sups_ms_val->dsat_ss_cm_data,
                                              dsatcm_client_id,
                                              &sups_ms_val->dsat_ss_cm_data.cm_parms.interr,
                                              &dsat_dialed_digits,
                                               CM_ORIG_CLIENT_CATEG_USER,
                                              TRUE,
                                              subs_id);
#else
          cm_result = cm_sups_cmd_interrogate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                              &sups_ms_val->dsat_ss_cm_data,
                                              dsatcm_client_id,
                                              &sups_ms_val->dsat_ss_cm_data.cm_parms.interr,
                                              &dsat_dialed_digits,
                                               CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
    
        default:
          DS_ATCOP_ERROR_LOG_1("Unrecognized mode value: =d",
                    sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.mode);
          return DSAT_ERROR;
      }
      if (cm_result)
      {
        DS_AT_MSG0_HIGH("Setting +CLCK pending  True");
        sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind = TRUE;
      }
      break;

    /* Call waiting class action */
    case DSAT_SSOP_CALL_WT:
    /* Call appropriate API based on Mode */
      switch (sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_wt.mode)
      {
        case DSAT_CCWA_MODE_DISABLE:
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.present =
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.deact.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_DISABLE;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM     
          cm_result = cm_sups_cmd_deactivate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func, 
                                             &sups_ms_val->dsat_ss_cm_data,
                                             dsatcm_client_id,
                                             &sups_ms_val->dsat_ss_cm_data.cm_parms.deact,
                                             &dsat_dialed_digits,
                                              CM_ORIG_CLIENT_CATEG_USER,
                                             TRUE,
                                             subs_id);
#else
          cm_result = cm_sups_cmd_deactivate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                             &sups_ms_val->dsat_ss_cm_data,
                                             dsatcm_client_id,
                                             &sups_ms_val->dsat_ss_cm_data.cm_parms.deact,
                                             &dsat_dialed_digits,
                                            CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
      
        case DSAT_CCWA_MODE_ENABLE:
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.present = 
            (NO_CODE == bsg_type)? FALSE: TRUE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.act.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_ENABLE;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM           
          cm_result = cm_sups_cmd_activate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.act,
                                           &dsat_dialed_digits,
                                            CM_ORIG_CLIENT_CATEG_USER,
                                           TRUE,
                                           subs_id);
 #else     
          cm_result = cm_sups_cmd_activate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                           &sups_ms_val->dsat_ss_cm_data,
                                           dsatcm_client_id,
                                           &sups_ms_val->dsat_ss_cm_data.cm_parms.act,
                                           &dsat_dialed_digits,
                                            CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;
      
        case DSAT_CCWA_MODE_QUERY:
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.present = FALSE;
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.bs_code = bsg_code;
          sups_ms_val->dsat_ss_cm_data.cm_parms.interr.basic_service.code_type = bsg_type;
          /*Building MMI string */
          dsat_ss_params.mode = MCS_SUPS_MODE_QUERY;
          dsat_ss_params.code = sups_ms_val->dsat_ss_cm_data.sc_code;
          dsat_ss_params.service_class = sups_ms_val->dsat_ss_cm_data.user_data.class;
          
          cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
                   
          if (cm_result != E_SUCCESS)
          {
           DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
            return DSAT_ERROR;
           
          }
          dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
          dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
          
          (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
                  CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
                  MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
          
          DS_AT_MSG_SPRINTF_2_HIGH(
                          "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM           
          cm_result = cm_sups_cmd_interrogate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func, 
                                              &sups_ms_val->dsat_ss_cm_data,
                                              dsatcm_client_id,
                                              &sups_ms_val->dsat_ss_cm_data.cm_parms.interr,
                                              &dsat_dialed_digits,
                                               CM_ORIG_CLIENT_CATEG_USER,
                                              TRUE,
                                              subs_id);
#else
          cm_result = cm_sups_cmd_interrogate_exten(etsicmif_sups_exten_cmd_cb_func, 
                                              &sups_ms_val->dsat_ss_cm_data,
                                              dsatcm_client_id,
                                              &sups_ms_val->dsat_ss_cm_data.cm_parms.interr,
                                              &dsat_dialed_digits,
                                               CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
          break;

        default:
          DS_ATCOP_ERROR_LOG_1("Unrecognized mode value: =d",
                    sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_wt.mode);
          return DSAT_ERROR;
      }
      break;

    default:
      DS_ATCOP_ERROR_LOG_1("Unrecognized operation value: =d",
               sups_ms_val->dsat_ss_cm_data.user_data.operation);
      return DSAT_ERROR;
  }

  if (!cm_result)
  {
   DS_ATCOP_ERROR_LOG_0("Problem invoking CM API");
    return DSAT_ERROR;
  }

  return DSAT_ASYNC_CMD;
} /* dsatetsicmif_sups_class_action */



/*===========================================================================

FUNCTION DSATETSICMIF_SUPS_CHANGE_PASSWORD

DESCRIPTION
  This function intiates the change of supplementary services facility
  password. The user parameters stored in regional variable
  dsat_ss_cm_data are expected to be validated. This routine populates
  the Call Manager API structures.
  
DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  Command is sent to Call Manager
  
===========================================================================*/
dsat_result_enum_type dsatetsicmif_sups_change_password (void)
{
  cm_reg_pwd_params_s_type       reg_pwd_cmd_parms;
  boolean cm_result = TRUE;
  mcs_sups_params_s_type dsat_ss_params;
  char                       dsat_mmi_buf[DSAT_MAX_MMI_STRING_LEN];
  cm_num_s_type               dsat_dialed_digits;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;

  sups_ms_val = dsat_get_base_addr_current_subs(DSAT_SUPS_MS_VALS);

  /* Lookup Network Service Code */
  if (!etsicmif_sups_lookup_netsc())
  {
   DS_ATCOP_ERROR_LOG_0("Could not determine net SC");
    return DSAT_ERROR;
  }

  /* Clear CM structure */
  memset( &reg_pwd_cmd_parms,
          CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof( cm_reg_pwd_params_s_type ) );
  memset(&dsat_mmi_buf[0],0,DSAT_MAX_MMI_STRING_LEN);
  memset(&dsat_ss_params,CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof(mcs_sups_params_s_type));
  memset(&dsat_dialed_digits,CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof(cm_num_s_type));
  /* set all the fields of the request */
  reg_pwd_cmd_parms.ss_ref = 0;

  /* SS code */
  reg_pwd_cmd_parms.ss_code.present = TRUE;
  reg_pwd_cmd_parms.ss_code.ss_code = sups_ms_val->dsat_ss_cm_data.sc_code;
    /*Building MMI string */
  dsat_ss_params.mode = MCS_SUPS_MODE_REG_PASSWD;
  dsat_ss_params.code = reg_pwd_cmd_parms.ss_code.ss_code;
  
  /* Old Password */
  (void) dsatutil_memscpy((void*)reg_pwd_cmd_parms.ss_old_pwd.ss_password,MAX_PWD_CHAR,
          (void*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.passwd,
          MAX_PWD_CHAR );
  reg_pwd_cmd_parms.ss_old_pwd.present = TRUE;
  dsat_ss_params.cmd.passwd.old_passwd = (char *)&sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.passwd[0];

  /* New Password */
  (void) dsatutil_memscpy((void*)reg_pwd_cmd_parms.ss_new_pwd.ss_password,MAX_PWD_CHAR,
          (void*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.new_passwd,
          MAX_PWD_CHAR );
  reg_pwd_cmd_parms.ss_new_pwd.present = TRUE;
  dsat_ss_params.cmd.passwd.new_passwd =(char *) &sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.new_passwd[0];

  /* New Password Again*/
  (void) dsatutil_memscpy((void*)reg_pwd_cmd_parms.ss_new_pwd_again.ss_password,MAX_PWD_CHAR,
          (void*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.new_passwd,
          MAX_PWD_CHAR );
  reg_pwd_cmd_parms.ss_new_pwd_again.present = TRUE;
  dsat_ss_params.cmd.passwd.new_passwd_again = (char *)&sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.new_passwd[0];
  
  cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);
  if (cm_result != E_SUCCESS)
  {
   DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
    return DSAT_ERROR;
   
  }
  dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
  dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
  
  (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
          CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
          MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
  
  DS_AT_MSG_SPRINTF_2_HIGH(
                  "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

  /* send the command to the CM command queue */
#ifdef FEATURE_DUAL_SIM
  cm_result = cm_sups_cmd_reg_password_cc_exten_per_subs ( etsicmif_sups_exten_cmd_cb_func,
                                        &sups_ms_val->dsat_ss_cm_data,
                                        dsatcm_client_id,
                                        &reg_pwd_cmd_parms,
                                        &dsat_dialed_digits,
                                         CM_ORIG_CLIENT_CATEG_USER,
                                        TRUE,
                                        dsat_get_current_subs_id(FALSE));
#else
  cm_result = cm_sups_cmd_reg_password_exten( etsicmif_sups_exten_cmd_cb_func,
                                        &sups_ms_val->dsat_ss_cm_data,
                                        dsatcm_client_id,
                                        &reg_pwd_cmd_parms,
                                        &dsat_dialed_digits,
                                         CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
  if (!cm_result)
  {
   DS_ATCOP_ERROR_LOG_0("Problem invoking CM API");
    return DSAT_ERROR;
  }

  return DSAT_ASYNC_CMD;
} /* dsatetsicmif_sups_change_password */


/*===========================================================================

FUNCTION DSATETSICMIF_SUPS_PROCESS_USSD

DESCRIPTION
  This function intiates the action in Call Manager to perform supplemental
  service commands for Unstructured Supplementary Service Data (USSD). It acts
  as a state machine for MS originated USSD messages. 
  
DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  Command is sent to Call Manager
  
===========================================================================*/
dsat_result_enum_type dsatetsicmif_sups_process_ussd (void)
{
  dsat_result_enum_type result = DSAT_ASYNC_CMD;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;

  sups_ms_val = dsat_get_base_addr_current_subs(DSAT_SUPS_MS_VALS);

  /* Perform operation based on mode */
  switch (sups_ms_val->dsat_ss_cm_data.ussd_state)
  {
    /* Send mobile-originated USSD command */
    case DSAT_CUSD_STATE_MS_SEND:
      result = etsicmif_sups_send_ussd_cmd();
      break;
      
    /* Send release to abort USSD command */
    case DSAT_CUSD_STATE_MS_ABORT:
      result = etsicmif_sups_send_release();
      break;

    /* Send response to network request indication */
    case DSAT_CUSD_STATE_SS_REQUEST:
      result = etsicmif_sups_send_ussd_request_response( FALSE, 0 ,dsat_get_current_subs_id(FALSE));
      break;
      
    default:
      DS_ATCOP_ERROR_LOG_1("Unsupported USSD state: =d",
                sups_ms_val->dsat_ss_cm_data.ussd_state);
      result = DSAT_ERROR;
  }
  
  return result;
} /* dsatetsicmif_sups_process_ussd */



/*===========================================================================

FUNCTION  DSATETSICMIF_CM_SUPS_CMD_HANDLER

DESCRIPTION
  This function is the handler function for the CM supplementary service
  commands.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the command execution.
  Possible values:
    DSAT_ERROR :      if there was any problem in execution.
    DSAT_ASYNC_CMD :  if it is a success and asynch cmd continues.
    DSAT_OK :         if it is a success and asynch cmd done. 

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsatetsicmif_cm_sups_cmd_handler
(
  ds_at_cm_sups_cmd_type *sups_cmd, /* SUPS command pointer */
  dsat_result_enum_type   result,
  sys_modem_as_id_e_type  subs_id
)
{
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;

  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);

  if(NULL == sups_ms_val)
  {
    return DSAT_ERROR;
  }

  switch (sups_cmd->cmd)
  {
    case CM_SUPS_CMD_INTERROGATE:
    case CM_SUPS_CMD_REGISTER:
    case CM_SUPS_CMD_ERASE:
    case CM_SUPS_CMD_ACTIVATE:
    case CM_SUPS_CMD_DEACTIVATE:
    case CM_SUPS_CMD_REG_PASSWORD:
    case CM_SUPS_CMD_GET_PASSWORD_RES:
    case CM_SUPS_CMD_RELEASE:
    case CM_SUPS_CMD_PROCESS_USS:
    case CM_SUPS_CMD_USS_NOTIFY_RES:
    case CM_SUPS_CMD_USS_RES:
      switch (sups_cmd->cmd_err)
      {
        case CM_SUPS_CMD_ERR_NOERR:
          /* Do nothing */
          break;

        case CM_SUPS_CMD_ERR_SRV_STATE_S:
        case CM_SUPS_CMD_ERR_OFFLINE_S:
          if(sups_ms_val->dsat_interr_ss_service == clip || 
             sups_ms_val->dsat_interr_ss_service == colp ||
             sups_ms_val->dsat_interr_ss_service == allLineIdentificationSS ||
             sups_ms_val->dsat_interr_ss_service == clir )
          {
            result = dsatetsicall_report_ss_lineid_status(
                     &sups_ms_val->dsat_interr_ss_service, NULL, FALSE);
          }
          else
          {
            result = dsat_send_cme_error(DSAT_CME_NO_NETWORK_SERVICE);
          }
          break;

        case CM_SUPS_CMD_ERR_NO_BUF_L:
        case CM_SUPS_CMD_ERR_OTHER:
          if(sups_ms_val->dsat_interr_ss_service == clip || 
             sups_ms_val->dsat_interr_ss_service == colp ||
             sups_ms_val->dsat_interr_ss_service == allLineIdentificationSS ||
             sups_ms_val->dsat_interr_ss_service == clir )
          {
            sups_ms_val->dsat_interr_ss_service = (ss_operation_code_T)DSAT_INVALID_OP_CODE;
          }
          result = dsat_send_cme_error(DSAT_CME_PHONE_FAILURE);
          break;
          
        default:
          DS_AT_MSG1_HIGH("Unsupported CM SupS command error: %d", sups_cmd->cmd_err);
          result = DSAT_ERROR;
      }

      if ((sups_ms_val->dsat_ss_cm_data.user_data.operation == DSAT_SSOP_FACILITY)&&
                 (sups_cmd->cmd_err != CM_SUPS_CMD_ERR_NOERR))
      {
        sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind = FALSE;
      }
      break;

    case CM_SUPS_CMD_ABORT:
      /* ABORT cmd raised by +CLCK abort handler only */
      switch (sups_cmd->cmd_err)
      {
        case CM_SUPS_CMD_ERR_NOERR:
          /* Return to normal command processing */
          result = DSAT_OK;
          break;

        default:
          DS_AT_MSG1_HIGH("Unsupported CM SupS command error: %d", sups_cmd->cmd_err);
          result = DSAT_ERROR;
      }
      if (sups_ms_val->dsat_ss_cm_data.user_data.operation == DSAT_SSOP_FACILITY)
      {
        sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind = FALSE;
        DS_AT_MSG1_HIGH("Clearing Panding variable status %d",
                    sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind);
      }
      if(dsatcmdp_abortable_state == NOT_ABORTABLE)
      {
        result = DSAT_ASYNC_EVENT;
      }
      break;
  
    default:
      DS_AT_MSG1_HIGH("Unsupport CM SupS command: %d",sups_cmd->cmd);
      result = DSAT_ERROR;
      break;
  }

  return result;
} /* dsatetsicmif_cm_sups_cmd_handler */

/*===========================================================================

FUNCTION  DSATETSICMIF_CM_SUPS_EVENT_HANDLER

DESCRIPTION
  This function is the handler function for the CM supplementary service
  related events

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR :       if there was any problem in execution
    DSAT_ASYNC_EVENT : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_cm_sups_event_handler
(
  ds_at_cm_sups_event_type *sups_event, /* SUPS event pointer */
  dsat_result_enum_type     result,
  sys_modem_as_id_e_type    subs_id
)
{
  ds_at_sups_event_info_s_type * einfo_ptr         = NULL;
  /* control loop over all +CCFC/+CCFCU/$QCCCFC/+CLCK/+CCWA class parameter values */
  boolean                               class_loop = FALSE;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val    = NULL;

  einfo_ptr = &sups_event->event_info;

  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, TRUE);
  if (NULL == sups_ms_val)
  {
    return DSAT_ASYNC_EVENT;
  }

  switch (sups_event->event)
  {
    /* Do nothing for command invocation events */
    case CM_SUPS_EVENT_REGISTER:
    case CM_SUPS_EVENT_ERASE:
    case CM_SUPS_EVENT_ACTIVATE:
    case CM_SUPS_EVENT_DEACTIVATE:
    case CM_SUPS_EVENT_INTERROGATE:
    case CM_SUPS_EVENT_REG_PASSWORD:
    /* Unsupported events for now */
    case CM_SUPS_EVENT_ABORT:
    case CM_SUPS_EVENT_FWD_CHECK_IND:
    case CM_SUPS_EVENT_GET_PASSWORD_RES:
      break;

    case CM_SUPS_EVENT_REGISTER_CONF:
    case CM_SUPS_EVENT_ERASE_CONF:
    case CM_SUPS_EVENT_ACTIVATE_CONF:
    case CM_SUPS_EVENT_DEACTIVATE_CONF:
    case CM_SUPS_EVENT_REG_PASSWORD_CONF:
      /* Process message */
      if (einfo_ptr->ss_success)
      {
        /* Check network response anomaly */
        switch(einfo_ptr->conf_type)
        {
          /* Success cases */
          case FWD_INFO:
          case SS_DATA_INFO:
          case CUG_INFO:
          case CALL_BARRING_INFO:
          case NO_INFO:  /* special case with no parameter info */
            class_loop = TRUE;   
            
            /* Password change not dependent on Class */
            /* Terminate async event with success */
            if (CM_SUPS_EVENT_REG_PASSWORD_CONF == sups_event->event)
            {
              class_loop = FALSE;
              result = DSAT_OK;
            }
            break;
          case NEW_PWD_INFO:
            /* Password change not dependent on Class */
            /* Terminate async event with success */
            result = DSAT_OK;
            DS_AT_MSG1_HIGH("SupS confirmation successful: %d",
                     einfo_ptr->conf_type);
            break;

          case CC_CAUSE_INFO:
            /* Network rejected request */
            DS_AT_MSG0_HIGH("Network rejected SupS request");
            result = dsat_send_cme_error(DSAT_CME_SUPS_NETWORK_REJECTED);
            break;

          default:
            break;
        }
      }
      else
      {
        /* Operation not succesful */
        result = DSAT_CMD_ERR_RSP;
        if(sups_ms_val->dsat_ss_abort_status == TRUE)
        {  
          /* We don't have to do anything */
           sups_ms_val->dsat_ss_abort_status = FALSE;
        }
      }
      if (sups_ms_val->dsat_ss_cm_data.user_data.operation == DSAT_SSOP_FACILITY)
      {
        DS_AT_MSG1_HIGH("Checking Panding variable status %d",
                    sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind); 
        sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind = FALSE;
      }
      break;  

    case CM_SUPS_EVENT_INTERROGATE_CONF:
      /* Process message */
      if (einfo_ptr->ss_success)
      {
        /* Check network response anomaly */
        switch(einfo_ptr->conf_type)
        {
          /* Success cases */
          case FWD_INFO:
          case FWD_TO_NUM_INFO:
          case CALLED_PARTY_NUM_INFO:
          case NO_INFO:            /* special case: no parameter info */
            class_loop = TRUE;
            DS_AT_MSG1_HIGH("SupS confirmation successful: %d",
                     einfo_ptr->conf_type);
            break;
            
          case FWD_FEATURE_LIST_INFO:
            /* Report query information */
            result =  dsatetsicmif_report_ccfc (sups_event, subs_id);
            class_loop = TRUE;
            break;

          case BSG_LIST_INFO:
            /* Report query information */
            DS_AT_MSG1_HIGH("SupS confirmation successful: %d",
                     einfo_ptr->conf_type);
            switch (sups_ms_val->dsat_ss_cm_data.user_data.operation)
            {
              case DSAT_SSOP_FACILITY:
                result =  dsatetsicmif_report_clck (sups_event, NULL, subs_id);
                break;

              case DSAT_SSOP_CALL_WT:
                result = dsatetsicmif_report_ccwa (sups_event, NULL, subs_id);
                break;
                  
              default:
                DS_ATCOP_ERROR_LOG_1("Unsupported operation: =d",
                          sups_ms_val->dsat_ss_cm_data.user_data.operation);
            }
            class_loop = TRUE;
            break;

          case CALL_BARRING_INFO:
            /* Report query information */
            DS_AT_MSG1_HIGH("SupS confirmation successful: %d",
                     einfo_ptr->conf_type);
            result =  dsatetsicmif_report_clck (sups_event, NULL, subs_id);
            class_loop = TRUE;
            break;

          case SS_STATUS_INFO:
            if(sups_ms_val->dsat_interr_ss_service == colp || 
               sups_ms_val->dsat_interr_ss_service == clip ||
               sups_ms_val->dsat_interr_ss_service == allLineIdentificationSS ||
               sups_ms_val->dsat_interr_ss_service == clir )
            {
              result = dsatetsicall_report_ss_lineid_status(
                         &sups_ms_val->dsat_interr_ss_service, &einfo_ptr->ss_status, TRUE);
            }
            else if(sups_ms_val->dsat_ss_abort_status == TRUE)
            {
              /* Do nothing, ignore the status message as the CLIP abort has 
                 been issued */
              sups_ms_val->dsat_ss_abort_status = FALSE;
            }
            else 
            {/* Diagnostic report */
              if( einfo_ptr->ss_status.present )
              {
                /* Report status information */
                if (einfo_ptr->ss_status.cm_ss_registered)
                {
                  DS_AT_MSG0_MED("SupS status: Registered");
                }
                if (einfo_ptr->ss_status.cm_ss_active)
                {
                  DS_AT_MSG0_MED("SupS status: Active");
                }
                if (einfo_ptr->ss_status.cm_ss_provisioned)
                {
                  DS_AT_MSG0_MED("SupS status: Provisioned");
                }
                if (einfo_ptr->ss_status.cm_ss_operative)
                {
                  DS_AT_MSG0_MED("SupS status: Operative");
                }
              
                class_loop = TRUE;
                switch (sups_ms_val->dsat_ss_cm_data.user_data.operation)
                {
                  case DSAT_SSOP_CALL_FWD:
                    result = dsatetsicmif_report_ccfc (sups_event, subs_id);
                    break;
                  
                  case DSAT_SSOP_FACILITY:
                    result = dsatetsicmif_report_clck (sups_event, NULL, subs_id);
                    break;
                  
                  case DSAT_SSOP_CALL_WT:
                    result = dsatetsicmif_report_ccwa (sups_event, NULL, subs_id);
                    break;
                  
                  default:
                    DS_ATCOP_ERROR_LOG_1("Unsupported operation: =d",
                            sups_ms_val->dsat_ss_cm_data.user_data.operation);
                }
              }
              else
              { 
                /* Generate +CME error */
                result = dsat_send_cme_error(DSAT_CME_SERV_OP_TEMP_OUT_OF_ORDER);
              }
            }
            break;
            
          case SS_ERROR_INFO:
            /* Decode error info */
            if(sups_ms_val->dsat_interr_ss_service == colp ||
               sups_ms_val->dsat_interr_ss_service == clip  ||
               sups_ms_val->dsat_interr_ss_service == allLineIdentificationSS ||
               sups_ms_val->dsat_interr_ss_service == clir )
            {
              sups_ms_val->dsat_interr_ss_service = (ss_operation_code_T)DSAT_INVALID_OP_CODE;
            }
            break;
            
          case CC_CAUSE_INFO:
                   /* Network rejected request */
            DS_AT_MSG0_HIGH("Network rejected SupS request");
            if(sups_ms_val->dsat_interr_ss_service == colp || 
               sups_ms_val->dsat_interr_ss_service == clip  ||
               sups_ms_val->dsat_interr_ss_service == allLineIdentificationSS ||
               sups_ms_val->dsat_interr_ss_service == clir )
            {
              sups_ms_val->dsat_interr_ss_service = (ss_operation_code_T)DSAT_INVALID_OP_CODE;
            }
            if(sups_ms_val->dsat_ss_abort_status == FALSE)
            {
              result = dsat_send_cme_error(DSAT_CME_SUPS_NETWORK_REJECTED);
            }
            else
            {
              sups_ms_val->dsat_ss_abort_status = FALSE;
            }
            
            break;
            
          case CLI_RESTRICTION_INFO:
            /* Introduced for +CLIR */
            if(sups_ms_val->dsat_interr_ss_service == clir)
            {
              result = dsatetsicall_report_clir_status(sups_event, subs_id);
            }
            else if(sups_ms_val->dsat_ss_abort_status == TRUE)
            {
              /* We don't have to do anything */
              sups_ms_val->dsat_ss_abort_status = FALSE;
            }
            break;

          default:
            DS_AT_MSG1_HIGH("Unsupported DYNAMIC CM SupS confirmation type: %d",
                     einfo_ptr->conf_type);
            break;
        }
      }
      else
      {
        /* Operation not succesful */
        if ( sups_ms_val->dsat_interr_ss_service == colp || 
             sups_ms_val->dsat_interr_ss_service == clip || 
             sups_ms_val->dsat_interr_ss_service == allLineIdentificationSS ||
             sups_ms_val->dsat_interr_ss_service == clir )
        {
          sups_ms_val->dsat_interr_ss_service = (ss_operation_code_T)DSAT_INVALID_OP_CODE;
        }
      }

    if (sups_ms_val->dsat_ss_cm_data.user_data.operation == DSAT_SSOP_FACILITY)
      {
        DS_AT_MSG1_HIGH("Checking Panding variable status %d",
                    sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind);
        sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind = FALSE;
      }
      break;

    case CM_SUPS_EVENT_GET_PASSWORD_IND:
      /* Network is requesting a password */
      result = etsicmif_sups_send_password(einfo_ptr, subs_id); 
      sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind = FALSE;
      break;

    case CM_SUPS_EVENT_PROCESS_USS:
      /* Outgoing messages (to NW) */
      /* Return to cmd prompt while network message pending */
      /* and before final result code.                      */
      /* See note under 3GPP TS 27.007 section 7.15         */
      result = DSAT_OK;
      break;
      
    case CM_SUPS_EVENT_PROCESS_USS_CONF:
      if(!einfo_ptr->ss_success)
      {
        /* Generate +CME error */
        DS_AT_MSG0_HIGH("Unknown USSD process conf msg");
        /* Check to see if result codes are enabled */
        if (1 == (dsat_num_item_type)dsatutil_get_val(
                               DSATETSI_EXT_ACT_CUSD_ETSI_IDX,0,0,MIX_NUM_TYPE))
        {
          result = dsatetsicmif_gen_cmee_error (DSAT_CME_SUPS_UNKNOWN_NETMSG,subs_id);
        }
      }

      /* Cleanup USSD transaction */
      dsatetsicmif_set_cusd_state(&(sups_ms_val->dsat_ss_cm_data), DSAT_CUSD_STATE_NULL, 0);
      break;
    default:
      break;
  }

  /* Loop for next class if applicable */
  if ((DSAT_ASYNC_EVENT == result) &&
      (TRUE == class_loop) &&
      (FALSE == sups_ms_val->dsat_ss_cm_data.abort_cmd))
  {
    /* Generate next CM message (possible) */
    sups_ms_val->dsat_ss_cm_data.done_class |= sups_ms_val->dsat_ss_cm_data.curr_class;
    result = dsatetsicmif_sups_class_action (FALSE , subs_id);
  }
  
  return result;

} /* dsatetsicmif_cm_sups_event_handler */


/*===========================================================================

FUNCTION DSATETSICMIF_SUPS_ABORT_HANDLER

DESCRIPTION
  This function generates an abort command to terminate asynchronous 
  processing for supplementary services commands.  It should be
  installed in the command table as the abort handler function for
  abortable supplementary service commands.

DEPENDENCIES
  None

RETURN VALUE
  Value indicating whether or not call should be aborted:
      TRUE if call should be aborted, FALSE otherwise.

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
boolean dsatetsicmif_sups_abort_handler
(
  const dsati_cmd_type *cmd_table_entry_ptr  /* Ptr to cmd entry in table. */
)
{
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;
  
  sups_ms_val = dsat_get_base_addr_current_subs(DSAT_SUPS_MS_VALS);

  /* Flag supserv handlers to abort */
  sups_ms_val->dsat_ss_cm_data.abort_cmd = TRUE;

  /* Raise abort cmd to return to normal command processing */
  etsicmif_sups_cmd_cb_func ( NULL, CM_SUPS_CMD_ABORT, CM_SUPS_CMD_ERR_NOERR );
  
  /* Signal command processor */
  return TRUE;
} /* dsatetsicmif_sups_abort_handler */



/*===========================================================================
FUNCTION  DSATETSICMIF_REPORT_CCWA_RESULT

DESCRIPTION
  This function generates the unsolicited result code for +CCWA command.
  The +CCWA command <n> parameter controls whether results are presented
  or suppressed.

  If TE indications are blocked, the result code is not sent to TE.
  
DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_EVENT : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_report_ccwa_result 
(
  sys_modem_as_id_e_type         subs_id,       /* Subscription ID */
  const ds_at_call_info_s_type  *call_info_ptr  /* Incoming call information */
)
{
  dsat_result_enum_type result = DSAT_ASYNC_EVENT;

  /* Only display if unsolicited result codes are enabled and 
     indications are not blocked */
  if ( (1 == (dsat_num_item_type)dsatutil_get_val(
       DSATETSI_EXT_ACT_CCWA_ETSI_IDX,0,0,NUM_TYPE)) &&
       FALSE == dsatcmdp_block_indications() )
  {
    dsm_item_type *res_buff_ptr = NULL;
    uint8 type;    
    uint8 svc_class;

    /* Get a result buffer */
    res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, TRUE);
    if (NULL != res_buff_ptr)
    {
      /* Type bits - bit7 = 1, bits 6-4 = number type, bits 3-0 = number plan */
      type = 0x80;
      type |= ((call_info_ptr->num.number_type & 0x07) << 4);
      type |= (call_info_ptr->num.number_plan & 0x0F); 

      svc_class = (call_info_ptr->call_type == CM_CALL_TYPE_VOICE ||
                   call_info_ptr->call_type == CM_CALL_TYPE_VT) ? 1 : 2;

      /* Construct result code: "+CCWA: <number>,<type of number>,<class>" */
      (void) dsatutil_memscpy((void*)res_buff_ptr->data_ptr,
              res_buff_ptr->size,(void*)"+CCWA: \"",8);


      res_buff_ptr->used += 8;
      if(res_buff_ptr->size > (call_info_ptr->num.len + res_buff_ptr->used ))
      {
      /* dsat_incom_call_num.buf is not null terminated */
        (void) dsatutil_memscpy((void*)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                       DSAT_BUF_SIZE(res_buff_ptr->size,res_buff_ptr->used),
                (void*)call_info_ptr->num.buf,
                       call_info_ptr->num.len);    
        res_buff_ptr->used += call_info_ptr->num.len;
      }

      res_buff_ptr->used +=
          (word) snprintf( 
                          (char*)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                          res_buff_ptr->size - res_buff_ptr->used,
                          "\",%d,%d",
                          type,
                          svc_class );

      /* Send response to TE */
      dsatcmdp_send_urc_per_subs(subs_id, res_buff_ptr, DSAT_COMPLETE_RSP);
    }
  }
  else
  {
    DS_AT_MSG0_LOW("Suppressing +CCWA result code");
  }
  
  return result;
} /* dsatetsicmif_report_ccwa_result */



/*===========================================================================
FUNCTION  DSATETSICMIF_AOC_SET_ACMMAX

DESCRIPTION
  Submit command to Call Manager to set the Advice of Charge (AoC)
  call meter maximum.  Note a value of zero will disable AoC.

DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
    DSAT_ASYNC_CMD :   if command sent to Call Manager
    DSAT_ERROR     :   if error occurred  

SIDE EFFECTS
  Sends command to Call Manager

===========================================================================*/
dsat_result_enum_type dsatetsicmif_aoc_set_acmmax
(
  uint32 acmmax
)
{
  dsat_result_enum_type result = DSAT_ASYNC_CMD;;
  
  /* Command CM to reset ACM value */
#ifdef FEATURE_DUAL_SIM
  if ( FALSE ==
       cm_ph_cmd_aoc_set_acmmax_per_subs(dsatcmif_ph_cmd_cb_func,
                                                   NULL,
                                                   dsatcm_client_id,
                                                   dsat_get_current_subs_id(FALSE),
                                                   acmmax) )
  {
   DS_ATCOP_ERROR_LOG_0("Problem setting ACM maximum via CM");
    result = DSAT_ERROR;
  }
#else
  if ( FALSE ==
       cm_ph_cmd_aoc_set_acmmax(dsatcmif_ph_cmd_cb_func,
                                NULL,
                                dsatcm_client_id,
                                acmmax) )
  {
   DS_ATCOP_ERROR_LOG_0("Problem setting ACM maximum via CM");
    result = DSAT_ERROR;
  }
#endif /* FEATURE_DUAL_SIM */
  return result;
} /* dsatetsicmif_aoc_set_acmmax */



/*===========================================================================
FUNCTION  DSATETSICMIF_AOC_RESET_ACM

DESCRIPTION
  Submit command to Call Manager to reset the Advice of Charge (AoC)
  call meter.

DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
    DSAT_ASYNC_CMD :   if command sent to Call Manager
    DSAT_ERROR     :   if error occurred  

SIDE EFFECTS
  Sends command to Call Manager

===========================================================================*/
dsat_result_enum_type dsatetsicmif_aoc_reset_acm ( void )
{
  dsat_result_enum_type result = DSAT_ASYNC_CMD;;
  
  /* Command CM to reset ACM value */
#ifdef FEATURE_DUAL_SIM 
  if ( FALSE == cm_ph_cmd_aoc_reset_acm_per_subs (dsatcmif_ph_cmd_cb_func,
                                                    NULL,
                                                    dsatcm_client_id,
                                                    dsat_get_current_subs_id(FALSE)) )
   {
    DS_ATCOP_ERROR_LOG_0("Problem resetting ACM via CM");
     result = DSAT_ERROR;
   }
#else
  if ( FALSE ==
       cm_ph_cmd_aoc_reset_acm (dsatcmif_ph_cmd_cb_func,
                                NULL,
                                dsatcm_client_id) )
  {
   DS_ATCOP_ERROR_LOG_0("Problem resetting ACM via CM");
    result = DSAT_ERROR;
  }
#endif /* FEATURE_DUAL_SIM */
  return result;
} /* dsatetsicmif_aoc_reset_acm */



/*===========================================================================
FUNCTION  DSATETSICMIF_GEN_CMEE_ERROR

DESCRIPTION
  Generate the passed +CME error response.  One DSM item is allocated for
  response buffer.

DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
    DSAT_ASYNC_EVENT :   if +CME error respose was generated

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_gen_cmee_error 
(
  dsat_cme_error_e_type   error_code,                      /* Error ID      */
  sys_modem_as_id_e_type  subs_id
)
{
  /* Generate +CME error */
  dsm_item_type * res_buff_ptr;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;

  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);

  if(NULL == sups_ms_val)
  {
    return  DSAT_ASYNC_EVENT;
  }

  res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, TRUE);
  if (NULL != res_buff_ptr)
  {
    /* For +CCFC/$QCCCFC/+CCFCU/+CLCK, there may be a pending response */
    /* so add a newline to terminate.                   */
    if (TRUE == sups_ms_val->dsat_ss_cm_data.pending_rsp)
    {
      res_buff_ptr->data_ptr[res_buff_ptr->used++] = '\n';
    }
  
    dsatme_set_cme_error(error_code,
                             res_buff_ptr);

    (void)dsatcmdp_send_respose_to_te (res_buff_ptr, DSAT_COMPLETE_RSP);
  }

  sups_ms_val->dsat_ss_cm_data.pending_rsp = FALSE;

  return DSAT_ASYNC_EVENT;
} /* dsatetsicmif_gen_cmee_error */



/*===========================================================================

FUNCTION  DSATETSICMIF_GET_CM_CALL_STATE

DESCRIPTION
  This function queries Call Manager to get the current call state
  information.  The results of the query are returned asynchronously.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  CM is sent a async command

===========================================================================*/
dsat_result_enum_type dsatetsicmif_get_cm_call_state ( void )
{
  boolean cm_result;
  
  /* Query Call Manager for current active calls */
#ifdef FEATURE_DUAL_SIM
  cm_result =
    cm_mm_call_cmd_get_call_info_list_per_subs(dsatcmif_call_cmd_cb_func,
                                               NULL,
                                               dsatcm_client_id,
                                               dsat_get_current_subs_id(FALSE));
#else
  cm_result =
    cm_mm_call_cmd_get_call_info_list( dsatcmif_call_cmd_cb_func,
                                       NULL,
                                       dsatcm_client_id );
#endif /* FEATURE_DUAL_SIM */
  if (!cm_result)
  {
   DS_ATCOP_ERROR_LOG_0("Failed to query CM call info list");
    return DSAT_ERROR;
  }
  
  return DSAT_ASYNC_CMD;
} /* dsatetsicmif_get_cm_call_state */


/*===========================================================================

FUNCTION  DSATETSICMIF_DEACTIVATE_ALL_CONTEXTS

DESCRIPTION
  This function initiates PDP context deactivation for all contexts.
  This should be called when network domain changes to PS detach, which
  must result in all active contexts becoming deactivated according
  to 3GPP TS 27.007 section 10.1.9

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_deactivate_all_contexts 
( 
  sys_modem_as_id_e_type subs_id
)
{
  dsat_result_enum_type  result = DSAT_ASYNC_CMD;
  uint8     total_profiles = 0;
  /* Force all contexts to be deactivated */

  if (DSAT_ERROR == etsipkt_get_profile_list( DS_PROFILE_TECH_3GPP,(uint8*) &dsat_pdp_cid[0],
                                              DSAT_MAX_ALLOWED_PROFILES, &total_profiles,dsat_get_ds_profile_subs_id(subs_id)) )
  {  
   DS_ATCOP_ERROR_LOG_0("Error getting 3GPP profile list!");
  }


  dsat_pdp_state.valid_profile_count = total_profiles;
  dsat_pdp_state.demand_state = DSAT_PDP_CONNECT_DEACTIVATED;
  dsat_pdp_state.change_index = 0;
  result = dsatetsipkt_cgact_proc_cmd();
  return result;
} /* dsatetsicmif_deactivate_all_contexts */



/*===========================================================================

FUNCTION  DSATETSICMIF_QUERY_NETWORKS

DESCRIPTION
  This function invokes the CM API to get either the list of available
  networks from the access stratum or the preferred network list from
  the SIM/USIM.  Handling of the results is done asynchronously in the
  Phone command event handler for the CM_PH_EVENT_AVAILABLE_NETWORKS_CONF event.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_query_networks
(
  cm_network_list_type_e_type net_type
)
{
  dsat_result_enum_type  result = DSAT_ASYNC_CMD;

  DS_AT_MSG0_HIGH("COPS query networks requested");

  cm_cmd_get_net_req_s_type get_net_info;
  (void) cm_get_net_req_init(&get_net_info);
  get_net_info.cmd_cb_func = dsatcmif_ph_cmd_cb_func;
  get_net_info.data_block_ptr = NULL;
  get_net_info.client_id = dsatcm_client_id;
  get_net_info.scan_type = net_type;
 #ifdef FEATURE_TDSCDMA
  get_net_info.network_type = MMODE_RAT_MASK_TDS | MMODE_RAT_MASK_GSM | MMODE_RAT_MASK_WCDMA | MMODE_RAT_MASK_LTE | MMODE_RAT_MASK_NR5G;
 #else
  get_net_info.network_type = MMODE_RAT_MASK_GSM | MMODE_RAT_MASK_WCDMA | MMODE_RAT_MASK_LTE | MMODE_RAT_MASK_NR5G;
 #endif /* FEATURE_TDSCDMA */
  get_net_info.asubs_id = dsat_get_current_subs_id(FALSE);
	
  if (FALSE == cm_ph_cmd_get_net_req(&get_net_info))
  {
    result = DSAT_ERROR;
  }

  return result;
} /* dsatetsicmif_query_networks */

/*===========================================================================

FUNCTION DSATETSICMIF_CLCC_ABORT_EVENT_HANDLER

DESCRIPTION
  This function handles the +CLCC abort event handling. Most of the
  processing is done in the abort command handler.  This routine just
  ensures the AT command processor returns to normal processing.

DEPENDENCIES
  None

RETURN VALUE
  DSAT_ERROR : As command is aborted

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsatetsicmif_clcc_abort_event_handler
(
  ds_at_cmd_status_type *cmd_info_ptr
)
{
  if( dsatcmdp_abortable_state != NOT_ABORTABLE )
  {
    return DSAT_ERROR;
  }
  else
  {
    return DSAT_ASYNC_EVENT;
  }
} /* dsatetsicmif_clcc_abort_event_handler */



/*=========================   LOCAL FUNCTIONS   ============================*/

/*===========================================================================
FUNCTION  ETSICMIF_SUPS_EXTEN_CMD_CB_FUNC

DESCRIPTION
  Call control CM supplementary services command callback function

DEPENDENCIES
  None

RETURNS
  None

SIDE EFFECTS
  Adds command in DS command buffer

===========================================================================*/
LOCAL void etsicmif_sups_exten_cmd_cb_func 
(
  void                         *data_ptr, /* Data block pointer    */
  cm_sups_cmd_e_type            cmd,      /* Command ID            */
  cm_sups_cmd_err_e_type        cmd_err,  /* Command error code    */
  cm_sups_cmd_err_cause_e_type  err_cause, /* Cause of Error  */
  cm_alpha_s_type               alpha     /* alpha to be used only */
)
{
  ds_cmd_type * cmd_buf;
  ds_at_cm_sups_cmd_type *sups_cmd = NULL;

  cmd_buf = dsat_get_cmd_buf(sizeof(ds_at_cm_sups_cmd_type), FALSE);

  /* send the message to ATCOP */
  cmd_buf->hdr.cmd_id = DS_CMD_ATCOP_CM_SUPS_CMD;
  sups_cmd = cmd_buf->cmd_payload_ptr;
  sups_cmd->cmd = cmd;
  sups_cmd->cmd_err = cmd_err;
  sups_cmd->data_ptr = data_ptr;
  /*As of now we are not using err_cause and alpha fields and it can be used for
  extracting Cause of Error .Cause of Error to be used when cmd_err is other than CM_SUPS_CMD_ERR_NOERR*/
  sups_cmd->err_cause = err_cause;
  sups_cmd->alpha.len= alpha.len;
  if(alpha.len > 0)
  {
    (void)dsatutil_memscpy((void*)&sups_cmd->alpha.buf[0],
          CM_MAX_ALPHA_TAG_CHARS,(void*)&alpha.buf[0],MIN(alpha.len,CM_MAX_ALPHA_TAG_CHARS));
    
  }
  ds_put_cmd(cmd_buf);

  return;
} /* etsicmif_sups_exten_cmd_cb_func */

/*===========================================================================
FUNCTION  ETSICMIF_SUPS_LOOKUP_NETSC

DESCRIPTION
  This function does a lookup of the network sercive code for the given
  +CCFC/$QCCCFC/+CCFCU reason or +CLCK/+CPWD facility code.  All data is in regional
  variable dsat_ss_cm_data.

DEPENDENCIES
  None

RETURNS
  TRUE if lookup was successful, FALSE otherwise

SIDE EFFECTS
  None

===========================================================================*/
LOCAL boolean etsicmif_sups_lookup_netsc ()
{
  boolean result = FALSE;
  uint8 index = 0;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;
  
  sups_ms_val = dsat_get_base_addr_current_subs(DSAT_SUPS_MS_VALS);

  while (DSAT_SSOP_MAX != sc_conversion_table[index].operation )
  {
    if (sc_conversion_table[index].operation ==
        sups_ms_val->dsat_ss_cm_data.user_data.operation)
    {
      if (((DSAT_SSOP_CALL_FWD == sups_ms_val->dsat_ss_cm_data.user_data.operation) &&
           (sc_conversion_table[index].code ==
            (uint8)sups_ms_val->dsat_ss_cm_data.user_data.opdata.call_fwd.reason)) ||

          ((DSAT_SSOP_FACILITY == sups_ms_val->dsat_ss_cm_data.user_data.operation) &&
           (sc_conversion_table[index].code ==
             (uint8)sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.facility)) ||

           (DSAT_SSOP_CALL_WT == sups_ms_val->dsat_ss_cm_data.user_data.operation) )
      {
        sups_ms_val->dsat_ss_cm_data.sc_code = sc_conversion_table[index].net_sc;
        result = TRUE;
        break;
      }
    }
    index++;
    
    if(index >= ARR_SIZE(sc_conversion_table))
    {
     DS_ATCOP_ERROR_LOG_0("Invalid Access into sc_conversion_table");
      return FALSE;
    }
  }
  DSATETSICMIF_ASSERT( sups_ms_val->dsat_ss_cm_data.sc_code > 0 );

  return result;
} /* etsicmif_sups_lookup_netsc */

/*===========================================================================
FUNCTION  ETSICMIF_SEND_SUPS_ERROR

DESCRIPTION
  Function to send sups error.
  
DEPENDENCIES
  None

RETURNS
  None

SIDE EFFECTS
  None

===========================================================================*/
LOCAL dsat_result_enum_type etsicmif_send_sups_error
(
  dsat_cme_error_e_type    error_code,
  sys_modem_as_id_e_type   subs_id
)
{
  dsat_result_enum_type    result = DSAT_ASYNC_EVENT;
  if( dsatcmdp_block_indications() == FALSE ) 
  { 
    result= dsatetsicmif_gen_cmee_error(error_code,subs_id); 
  } 
  else 
  { 
    result= dsat_send_cme_error (error_code); 
  }
  return result;
}/* etsicmif_send_sups_error */


/*===========================================================================
FUNCTION  ETSICMIF_SUPS_SEND_PASSWORD

DESCRIPTION
  This function sends the required password to Call Manager in response 
  to request from network.  The required password is indicated by the
  guidance_info field.
  
DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  Send command to Call Manager

===========================================================================*/
LOCAL dsat_result_enum_type etsicmif_sups_send_password 
(
  const ds_at_sups_event_info_s_type *einfo_ptr,       /* Event info */
  sys_modem_as_id_e_type              subs_id
)
{
  cm_get_pwd_res_params_s_type       get_pwd_res;
  boolean cm_result = TRUE;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;
  
  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);
  
  if(NULL == sups_ms_val)
  {
    return DSAT_ASYNC_CMD;
  }
  
  if (sups_ms_val->dsat_ss_cm_data.pending_clck_pwd_ind != TRUE)
  {
    DS_AT_MSG0_MED("Ignoring unexpected GET_PWD_IND");
    return DSAT_OK;
  }
  memset( &get_pwd_res,
          CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof( cm_get_pwd_res_params_s_type ));

  /* Preserve network invoke ID */
  get_pwd_res.invoke_id = einfo_ptr->invoke_id;
  get_pwd_res.ss_pwd.present = TRUE;
  
  /* Determine which password required */
  switch (einfo_ptr->guidance_info)
  {
    case enterPW:                   /* enter password */
      (void) dsatutil_memscpy((void*)get_pwd_res.ss_pwd.ss_password,
              MAX_PWD_CHAR,
              (void*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.passwd,
              MAX_PWD_CHAR );
      break;

    case enterNewPW:                /* enter new password */
    case enterNewPW_Again:          /* confirm new password */
      (void) dsatutil_memscpy((void*)get_pwd_res.ss_pwd.ss_password,
              MAX_PWD_CHAR,
              (void*)sups_ms_val->dsat_ss_cm_data.user_data.opdata.fac_lock.new_passwd,
              MAX_PWD_CHAR );
      break;

    default:
      DS_ATCOP_ERROR_LOG_1("Unknown password indication: =d",
                 einfo_ptr->guidance_info);
      break;
  }

  /* Send the command to the CM command queue */
#ifdef FEATURE_DUAL_SIM
  cm_result = cm_sups_cmd_get_password_res_per_subs( etsicmif_sups_cmd_cb_func,
                                                     &sups_ms_val->dsat_ss_cm_data,
                                                     dsatcm_client_id,
                                                     &get_pwd_res,
                                                     subs_id);
#else
  cm_result = cm_sups_cmd_get_password_res( etsicmif_sups_cmd_cb_func,
                                            &sups_ms_val->dsat_ss_cm_data,
                                            dsatcm_client_id,
                                            &get_pwd_res);
#endif

  if (!cm_result)
  {
   DS_ATCOP_ERROR_LOG_0("Problem invoking CM API");
    return DSAT_ERROR;
  }

  return DSAT_ASYNC_CMD;
} /* etsicmif_sups_send_password */


/*===========================================================================
FUNCTION  ETSICMIF_SUPS_SEND_USSD_CMD

DESCRIPTION
  This function requests Call Manager to send the mobile originated USSD
  command to the network.  
  
DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  Send command to Call Manager

===========================================================================*/
LOCAL dsat_result_enum_type etsicmif_sups_send_ussd_cmd ( void )
{
  dsat_result_enum_type result = DSAT_ASYNC_CMD;
  ss_us_user_s_type *               ssus_ptr = NULL;
  cm_uss_params_s_type    uss_cmd_parms;
  boolean cm_result = TRUE;
  cm_num_s_type           dsat_dialed_digits;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;
  
  sups_ms_val = dsat_get_base_addr_current_subs(DSAT_SUPS_MS_VALS);

  /* Send USSD string to network */

  ssus_ptr = &sups_ms_val->dsat_ss_cm_data.user_data.opdata.ussd;
  memset( &uss_cmd_parms,
          CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof( cm_uss_params_s_type ));
  memset(&dsat_dialed_digits,
          CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof(cm_num_s_type));

  /* Setup USS Data structure */
  uss_cmd_parms.ss_ref = 0;
  uss_cmd_parms.uss_data.present = TRUE;
  (void) dsatutil_memscpy((void*)uss_cmd_parms.uss_data.ussData,
          MAX_USS_CHAR_ASCII + 1,(void*)ssus_ptr->string,MAX_USS_CHAR_ASCII);

  /* Don't call etsicmif_sups_convert_alphabet():
     in this one case CM expects ASCII string instead of packed GSM 7bit
     for USSD data. */
  uss_cmd_parms.uss_data.size = (byte)strlen( (char *)ssus_ptr->string );
  
  if(uss_cmd_parms.uss_data.size < CM_MAX_NUMBER_CHARS+1)
  {
    dsat_dialed_digits.len = uss_cmd_parms.uss_data.size;
    dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
    /* MMI string also expact data is in ASCII format */
  (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
          CM_MAX_NUMBER_CHARS,(void*)&uss_cmd_parms.uss_data.ussData[0],
          MIN(dsat_dialed_digits.len,MAX_USS_CHAR_ASCII + 1));   
  }
  
  if (DEFAULT_ALPHABET == ( ssus_ptr->dcs & ALPHABET_MASK ))
  {
    uss_cmd_parms.uss_data.uss_data_coding_scheme = ssus_ptr->dcs;
  }
  else
  {
    DS_AT_MSG1_HIGH("Unsupported alphabet for USSD msg: %d",
             ssus_ptr->dcs);     
    result = DSAT_ERROR;
    return result;
  }
  uss_cmd_parms.uss_data.present = TRUE;
  
  /* send the command to the CM command queue */
#ifdef FEATURE_DUAL_SIM
  cm_result = cm_sups_cmd_process_uss_exten_per_subs( etsicmif_sups_exten_cmd_cb_func,
                                       &sups_ms_val->dsat_ss_cm_data,
                                       dsatcm_client_id,
                                       &uss_cmd_parms,
                                       &dsat_dialed_digits,
                                        CM_ORIG_CLIENT_CATEG_USER,
                                       TRUE,
                                       dsat_get_current_subs_id(FALSE));
#else
  cm_result = cm_sups_cmd_process_uss_exten( etsicmif_sups_exten_cmd_cb_func,
                                       &sups_ms_val->dsat_ss_cm_data,
                                       dsatcm_client_id,
                                       &uss_cmd_parms,
                                       &dsat_dialed_digits,
                                        CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
  if (!cm_result)
  {
   DS_ATCOP_ERROR_LOG_0("Problem invoking CM API");
    result = DSAT_ERROR;
  }
  return result;
} /* etsicmif_sups_send_ussd_cmd */



/*===========================================================================
FUNCTION  ETSICMIF_SUPS_SEND_USSD_REQUEST_RESPONSE

DESCRIPTION
  This function requests Call Manager to send the mobile originated USSD
  response to the network.  This response message is sent by the MS after
  an USSD indication message has been received.
  If the error present flag is FALSE, no error code is specified in
  the message payload.
  
DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  Send command to Call Manager

===========================================================================*/
LOCAL dsat_result_enum_type etsicmif_sups_send_ussd_request_response
(
  boolean                 error_present,         /* Error present */
  byte                    error_code ,             /* Error code    */
  sys_modem_as_id_e_type  subs_id
)
{
  dsat_result_enum_type result = DSAT_ASYNC_CMD;
  ss_us_user_s_type * ssus_ptr = NULL;
  cm_uss_res_params_s_type    uss_res_parms;
  boolean cm_result = TRUE;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;

  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);

  if(NULL == sups_ms_val)
  {
    return result;
  }

  ssus_ptr = &sups_ms_val->dsat_ss_cm_data.user_data.opdata.ussd;
  /* Initialize CM structure */
  memset( &uss_res_parms,
          CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof( cm_uss_res_params_s_type ));

  /* Setup USS Data structure */
  etsicmif_get_cusd_info(&(sups_ms_val->dsat_ss_cm_data), &uss_res_parms.invoke_id, NULL);

  if( TRUE == error_present )
  {
    ie_cm_ss_error_T * uss_error_ptr =
      &uss_res_parms.uss_res_data.data.cm_ss_error;

    uss_res_parms.uss_res_data.data_type = (cm_ss_conf_e_type)CM_USS_RES_SS_ERROR;
    
    uss_error_ptr->present = error_present;
    uss_error_ptr->error_code_tag = ERROR_CODE_TAG;
    uss_error_ptr->error_code = error_code;
  }
  else
  {
    uss_data_s_type *  uss_data_ptr =
      &uss_res_parms.uss_res_data.data.uss_data;
    
    uss_res_parms.uss_res_data.data_type = (cm_ss_conf_e_type)CM_USS_RES_SS_DATA;

    uss_data_ptr->present = TRUE;
    uss_data_ptr->uss_data_coding_scheme = ssus_ptr->dcs;
  
    if (DSAT_ERROR ==
        etsicmif_sups_convert_alphabet(TRUE,
                                       (uss_data_s_type *)uss_data_ptr,
                                       ssus_ptr->string,
                                       ssus_ptr->dcs,
                                       CM_USS_PHASE2_TYPE))
    {
      DS_ATCOP_ERROR_LOG_1("Cannot convert to OTA alphabet for DCS=d",ssus_ptr->dcs);
      return DSAT_ERROR;
    }
  }

  /* Set indicator for pending messages */
  sups_ms_val->dsat_ss_cm_data.pending_msg = TRUE;
      
  DS_AT_MSG3_HIGH("Sending USSD request response: dtype=%d  err present=%d code=%d",
            uss_res_parms.uss_res_data.data_type, error_present, error_code );
      
  /* send the command to the CM command queue */
#ifdef FEATURE_DUAL_SIM
  cm_result = cm_sups_cmd_uss_res_per_subs ( etsicmif_sups_cmd_cb_func,
                                    &sups_ms_val->dsat_ss_cm_data,
                                    dsatcm_client_id,
                                    &uss_res_parms,
                                    subs_id);
#else
  cm_result = cm_sups_cmd_uss_res ( etsicmif_sups_cmd_cb_func,
                                    &sups_ms_val->dsat_ss_cm_data,
                                    dsatcm_client_id,
                                    &uss_res_parms);
#endif /* FEATURE_DUAL_SIM */
  if (!cm_result)
  {
   DS_ATCOP_ERROR_LOG_0("Problem invoking CM API");
    result = DSAT_ERROR;
  }
  return result;
} /* etsicmif_sups_send_ussd_request_response */



/*===========================================================================
FUNCTION  ETSICMIF_SUPS_SEND_RELEASE

DESCRIPTION
  This function requests Call Manager to send the release message to the
  network.  
  
DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_CMD : if it is a success.

SIDE EFFECTS
  Send command to Call Manager

===========================================================================*/
LOCAL dsat_result_enum_type etsicmif_sups_send_release( void )
{
  cm_release_ss_params_s_type  release_cmd_parms;
  boolean cm_result = TRUE;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;

  sups_ms_val = dsat_get_base_addr_current_subs(DSAT_SUPS_MS_VALS);

  memset( &release_cmd_parms,
          CM_CALL_CMD_PARAM_DEFAULT_VALUE,
          sizeof(cm_release_ss_params_s_type));

  etsicmif_get_cusd_info(&(sups_ms_val->dsat_ss_cm_data), &release_cmd_parms.ss_ref, &release_cmd_parms.ss_oper);

  /* Send the command to the CM */
#ifdef FEATURE_DUAL_SIM
  cm_result = cm_sups_cmd_release_cc_per_subs( etsicmif_sups_cmd_cb_func,
                                   &sups_ms_val->dsat_ss_cm_data,
                                   dsatcm_client_id,
                                   &release_cmd_parms,
                                   NULL,
                                   TRUE,
                                   dsat_get_current_subs_id(FALSE));
#else
  cm_result = cm_sups_cmd_release( etsicmif_sups_cmd_cb_func,
                                   &sups_ms_val->dsat_ss_cm_data,
                                   dsatcm_client_id,
                                   &release_cmd_parms);
#endif /* FEATURE_DUAL_SIM */

  if (!cm_result)
  {
   DS_ATCOP_ERROR_LOG_0("Problem invoking CM API");
    return DSAT_ERROR;
  }

  return DSAT_ASYNC_CMD;
} /* etsicmif_sups_send_release */



/*===========================================================================
FUNCTION  ETSICMIF_REPORT_USSD_RESULT

DESCRIPTION
  This function generates the unsolicited result code for USSD commands.
  The +CUSD command <n> paramater controls whether results are presented
  or suppressed.

  If TE indications are blocked, the network is sent a busy response. 
  If the data coding scheme is not supported, the network is sent an 
  unknown alphabet response.
  
DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_ASYNC_EVENT : if it is a success.

SIDE EFFECTS
  Send command to Call Manager

===========================================================================*/
dsat_result_enum_type etsicmif_report_ussd_result
(
  const ds_at_cm_sups_event_type *sups_event_ptr, /* SUPS event pointer */
  const cusd_result_e_type        result_code,    /* Result code */
  sys_modem_as_id_e_type          subs_id,
  boolean                        *send_ack
)
{

  #define MAX_USSD_BUF_SIZE ((MAX_DISPLAY_TEXT_LEN << 1) + 1)
  /* maximum number of characters after USSD data:
     includes '+CUSD: <n>,\"\",<dcs>\0' */
  #define CHARS_RESERVED  14
  #define SEND_RESPONSE( error, code ) \
  if( DSAT_CUSD_STATE_SS_NOTIFY == sups_ms_val->dsat_ss_cm_data.ussd_state ) \
  { \
    (void)etsicmif_sups_send_ussd_notify_response( error, code,subs_id ); \
  } \
  else \
  { \
    (void)etsicmif_sups_send_ussd_request_response( error, code ,subs_id); \
  }
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;
  dsat_num_item_type cscs_val ;
  dsat_result_enum_type result = DSAT_ASYNC_EVENT;

  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);

  if(NULL == sups_ms_val)
  {
    return DSAT_ASYNC_EVENT;
  }

  /* Check to see if result codes are enabled */
  if (1 == (dsat_num_item_type)dsatutil_get_val(
                               DSATETSI_EXT_ACT_CUSD_ETSI_IDX,0,0,MIX_NUM_TYPE))
  {
    dsm_item_type * res_buff_ptr = NULL;
    
    /* Report busy to network if indications to the TE are blocked. */
    if ( TRUE ==  dsatcmdp_block_indications() )
    {
      /* Send error response back to network */
      DS_AT_MSG0_HIGH("Sending USSD busy to network");
      SEND_RESPONSE( TRUE, ussd_Busy );
      *send_ack = FALSE;
      return result;
    }

    DS_AT_MSG5_MED("Generating CUSD result code: %d, "
                   "present = %d, dcs = %d, size = %d, type = %d",
                   result_code,
                   sups_event_ptr->event_info.uss_data.present,
                   sups_event_ptr->event_info.uss_data.uss_data_coding_scheme,
                   sups_event_ptr->event_info.uss_data.size,
                   sups_event_ptr->event_info.uss_data_type);

    /* Get a result buffer */
    res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, TRUE);
    if (NULL != res_buff_ptr)
    {
      /* Check for valid USSD information */
      if (sups_event_ptr->event_info.uss_data.present)
      {
        /* Convert from default alphabet (incoming messages) */
        if (DEFAULT_ALPHABET ==
            ( sups_event_ptr->event_info.uss_data.uss_data_coding_scheme & ALPHABET_MASK ))
        {
          char * buff_ptr;
          byte * buffer2_ptr;
          uint16 size;
          uint16  num_bytes = 0;
          /* Generate result code and USSD string */
          byte * buffer_ptr;
          buffer2_ptr = (byte *)dsat_alloc_memory(MAX_USSD_BUF_SIZE, FALSE);
          buffer_ptr = (byte *)dsat_alloc_memory(MAX_USSD_BUF_SIZE, FALSE);

          /* Clear output buffer */
          num_bytes = sups_event_ptr->event_info.uss_data.size ;
          /* Making sure no overflow occurs */
          if (num_bytes >= MAX_USSD_BUF_SIZE )
          {
            num_bytes = (MAX_USSD_BUF_SIZE - 1);
          }
          /* Check USSD data type */
          if (CM_USS_PHASE1_TYPE != sups_event_ptr->event_info.uss_data_type)
          {
            /* Unpack network message into GSM7b alphabet */
#ifdef CM_API_UTIL_USSD_FUNCTIONS
            num_bytes = cm_util_ussd_unpack(buffer_ptr, (byte*)sups_event_ptr->event_info.uss_data.ussData,(byte)num_bytes);
#else
            cm_util_unpack((byte*)sups_event_ptr->event_info.uss_data.ussData,num_bytes,buffer_ptr);
#endif


            /* Data is comming from N/W in GSM character set;
               This should be converted to replace GSM @ characters if any */
            if (! dsatutil_convert_alpha_gsm_with_at_to_alpha_gsm ( 
                                   (char *)buffer_ptr ,
                                   (char *)buffer2_ptr, 
                                   MIN( num_bytes, (MAX_USSD_BUF_SIZE - 1) ) ) )
            {
             DS_ATCOP_ERROR_LOG_0(" Invalid string received from GSDI");
              /* Report CME error */
              dsatme_set_cme_error ( DSAT_CME_INVALID_CHAR_IN_TEXT,
                                         res_buff_ptr );
              result = DSAT_CMD_ERR_RSP;
            }
            else
            {
              /* copying back to buffer */
              (void) dsatutil_memscpy((void*)buffer_ptr, MAX_USSD_BUF_SIZE,
                                      (void*)buffer2_ptr, MAX_USSD_BUF_SIZE);
            }
            /* Convert buffer[] from GSM to TE's character set, writing
             * into res_buff_ptr_data_ptr[] and dropping inconvertible
             * characters (there shouldn't be any). MAX_CHARS_AFTER_USSD
             * makes certain there'll be room for "\",<dcs>" in result
             * buffer. */
            cscs_val =(dsat_num_item_type)dsatutil_get_val(
                                               DSATETSI_EXT_CSCS_IDX,0,0,NUM_TYPE);
            buff_ptr = dsatutil_convert_chset( 
                             (const char *)&buffer_ptr[0], 
                             ALPHA_GSM, 
                             (char *)&buffer2_ptr[0],
                             (dsati_chset_type)cscs_val,
                             (MAX_USSD_BUF_SIZE - (uint32)CHARS_RESERVED),
                             TRUE );
          }
          else
          {
            /* PHASE 1 is in ASCII */
            /* Convert buffer[] from IRA to TE's character set, writing
             * into res_buff_ptr_data_ptr[] and dropping inconvertible
             * characters (there shouldn't be any). MAX_CHARS_AFTER_USSD
             * makes certain there'll be room for "\",<dcs>" in result
             * buffer. */
            (void) dsatutil_memscpy((void*)buffer_ptr, MAX_USSD_BUF_SIZE,
                                    (void*)sups_event_ptr->event_info.uss_data.ussData,MAX_USS_CHAR_ASCII);     
            cscs_val =(dsat_num_item_type)dsatutil_get_val(
                                               DSATETSI_EXT_CSCS_IDX,0,0,NUM_TYPE);
            buff_ptr = dsatutil_convert_chset( 
                             (const char *)&buffer_ptr[0], 
                             ALPHA_IRA, 
                             (char *)&buffer2_ptr[0],
                             (dsati_chset_type)cscs_val,
                             (MAX_USSD_BUF_SIZE - (uint32)CHARS_RESERVED),
                             TRUE );
          }

          if( NULL == buff_ptr )
          {
           DS_ATCOP_ERROR_LOG_0("Cannot convert USSD data string");
            buffer2_ptr[0] = '\0';
          }

          size = (uint16)snprintf((char*)buffer_ptr,
                          (MAX_USSD_BUF_SIZE - 1),
                          "+CUSD: %d,\"%s\",%d",
                          result_code,
                          buffer2_ptr,
                          sups_event_ptr->event_info.uss_data.
                              uss_data_coding_scheme );
  
          dsat_dsm_pushdown_tail(&res_buff_ptr, buffer_ptr, size,
                                 DSM_ITEM_POOL(res_buff_ptr), FALSE);
          dsatutil_free_memory((void *)buffer2_ptr);
          dsatutil_free_memory((void *)buffer_ptr);
        }
        else
        {
          /* Return response buffer */
          (void) dsm_free_buffer( res_buff_ptr );
          res_buff_ptr = NULL;

          /* Send error response back to network */
          DS_AT_MSG0_HIGH("Sending USSD unknown alphabet to network");
          SEND_RESPONSE( TRUE, unknownAlphabet );
          *send_ack = FALSE;
          result = DSAT_ERROR;
        }
      }
      else
      {
        /* Generate result code only */
        res_buff_ptr->used = (word) snprintf((char*)res_buff_ptr->data_ptr,
                                                    res_buff_ptr->size,
                                                    "+CUSD: %d",
                                                    result_code);
      }

      /* Ensure a response was generated */
      if (NULL != res_buff_ptr)
      {
        /* Send response to TE */
        result = dsatcmdp_send_respose_to_te (res_buff_ptr, DSAT_COMPLETE_RSP);
      }
    }
  }
  else
  {
    DS_AT_MSG1_HIGH("Suppressing CUSD result code: %d",result_code);
  }
  
  
  return result;
} /* etsicmif_report_ussd_result */



/*===========================================================================
FUNCTION  ETSICMIF_SUPS_CONVERT_ALPHABET

DESCRIPTION
  This function converts to and from the default alphabet based on data
  character set.  Only the GSM 7BIT character set is supported at this time.
  Refernce: 3GPP TS 23.038 
  
DEPENDENCIES
  None

RETURNS
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_OK : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
LOCAL dsat_result_enum_type etsicmif_sups_convert_alphabet
(
  boolean                 to_default,     /* Conversion mode flag  */
  uss_data_s_type *       uss_data_ptr,   /* USSD structure        */
  byte *                  string_ptr,     /* USSD string           */
  byte                    coding_scheme,  /* Data coding scheme    */
  cm_uss_data_e_type      data_type       /* USSD data type        */
)
{
  dsat_result_enum_type result = DSAT_OK;
  uint32  num_bytes = 0;
  uint32  num_bits = 0;
  uint32  num_chars = 0;

  if (to_default)
  {
    if (DEFAULT_ALPHABET == ( coding_scheme & ALPHABET_MASK ))
    {
      num_chars = strlen( (char *)(string_ptr) );
      
      /* Check USSD data type */
      if (CM_USS_PHASE1_TYPE == data_type)
      {
        /* PHASE 1 already in ASCII */
        (void) dsatutil_memscpy((void*)uss_data_ptr->ussData,
                MAX_USS_CHAR_ASCII + 1,(void*)string_ptr,MAX_USS_CHAR_ASCII);        
        uss_data_ptr->size = (byte)num_chars;
      }
      else
      {
        /* Convert to default alphabet (outgoing messages) */
        num_bits = ( num_chars * 7 );
        num_bytes = num_bits / 8;
   
        if(0 != ( num_bits % 8 ))
        {
          num_bytes ++;  /* round up */
        }
    
        /* Convert ASCII to default alphabet */
#ifdef CM_API_UTIL_USSD_FUNCTIONS
        (void)cm_util_ascii_to_gsm_alphabet( (byte *)uss_data_ptr->ussData,
                                       string_ptr,
                                       (byte)num_chars );
#else
        cm_util_ascii_to_def_alphabet( (byte *)uss_data_ptr->ussData,
                                       (byte)num_chars,
                                       string_ptr );
#endif
    
        uss_data_ptr->size = (uint8) num_bytes;
      }
      
      uss_data_ptr->uss_data_coding_scheme = coding_scheme;
      uss_data_ptr->present = TRUE;
    }
    else
    {
      /* Unsupported alphabet */
      DS_AT_MSG1_HIGH("Unsupported alphabet for USSD msg: %d",
               coding_scheme);
      
      result = DSAT_ERROR;
    }
  }
  else
  {
    /* Convert from default alphabet (incoming messages) */
    if (DEFAULT_ALPHABET ==
        ( uss_data_ptr->uss_data_coding_scheme & ALPHABET_MASK ))
    {
      /* Check USSD data type */
      if (CM_USS_PHASE1_TYPE == data_type)
      {
        /* PHASE 1 already in ASCII */
        (void) dsatutil_memscpy((void*)string_ptr,
                MAX_USS_CHAR_ASCII + 1,(void*)uss_data_ptr->ussData,MAX_USS_CHAR_ASCII);       
        num_bytes = uss_data_ptr->size;
      }
      else
      {
        /* Convert default GSM7b alphabet to ASCII */
#ifdef CM_API_UTIL_USSD_FUNCTIONS
        (void)cm_util_gsm_alphabet_to_ascii( string_ptr,          
                                             (byte *)uss_data_ptr->ussData,
                                             uss_data_ptr->size );
#else
        cm_util_def_alphabet_to_ascii( (byte *)uss_data_ptr->ussData,
                                       uss_data_ptr->size,
                                       string_ptr );
#endif
      }
    }
    else
    {
      /* Unsupported alphabet */
      DS_AT_MSG1_HIGH("Unsupported alphabet in USSD msg: %d",
               uss_data_ptr->uss_data_coding_scheme);
      
      result = DSAT_ERROR;
    }
  }

  return result;
} /* etsicmif_sups_convert_alphabet */



/*===========================================================================

FUNCTION  SET_CALL_PARAM_BY_CCUG

DESCRIPTION
  This function fill out the struct pointed by cug_info_ptr according
  to <index> and <info> of +CCGU command.

DEPENDENCIES
  cug_info_ptr->present is TRUE

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
LOCAL void set_call_param_by_ccug
(
  /* output: contains ccug info */
  cm_forward_cug_info_s_type    * cug_info_ptr,

  /* input: dsat_ccug_val array      */
  const dsat_num_item_type      * ccug_val
)
{
  /* check <index> of +CCGU */
  if (ccug_val[1] != 10)
  {
    cug_info_ptr->cm_cug_index.present = TRUE;
    cug_info_ptr->cm_cug_index.msb = 0;
    cug_info_ptr->cm_cug_index.lsb = 
      (byte) ccug_val[1];
  }
  else
  {
    cug_info_ptr->cm_cug_index.present = FALSE;
  }

  /* fill out fields related to <info> of +CCGU */
  switch(ccug_val[2])
  {
    case 0:
      cug_info_ptr->cm_suppress_pref_cug = FALSE;
      cug_info_ptr->cm_suppress_outgoing_access = FALSE;
      break;

    case 1:
      /* +CCUG cmd <info>: suppress OA */
      cug_info_ptr->cm_suppress_pref_cug = FALSE;
      cug_info_ptr->cm_suppress_outgoing_access = TRUE;
      break;

    case 2:
      /* +CCUG cmd <info>: suppress preferential CUG */
      cug_info_ptr->cm_suppress_pref_cug = TRUE;
      cug_info_ptr->cm_suppress_outgoing_access = FALSE;
      break;
      
    case 3:
      /* +CCUG cmd <info>: suppress OA and preferential CUG */
      cug_info_ptr->cm_suppress_outgoing_access = TRUE;
      cug_info_ptr->cm_suppress_pref_cug = TRUE;
      break;

    default:
      DS_ATCOP_ERROR_LOG_1("incorrect ccug_val[2]: =d", ccug_val[2]);
      cug_info_ptr->cm_suppress_pref_cug = FALSE;
      cug_info_ptr->cm_suppress_outgoing_access = FALSE;
      break;
  }

} /* set_call_param_by_ccug */

#ifdef FEATURE_DSAT_UMTS_DATA
/*===========================================================================

FUNCTION  DSATETSICMIF_CONTEXT_ACTIVATION_ATZ_CB

DESCRIPTION
  This function intiates PDP context deactivation in response to ATZ command.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void dsatetsicmif_context_activation_atz_cb ( void )
{
  dsatetsicmif_deactivate_all_contexts(dsat_get_current_subs_id(FALSE));
} /* dsatetsicmif_context_activation_atz_cb */
          

#endif /* FEATURE_DSAT_ETSI_DATA */

/*===========================================================================

FUNCTION  DSATETSICMIF_PROCESS_CM_MM_INFO_DATA

DESCRIPTION
  This function processes the Call Manager MM information data to display 
  the timezone status to TE

DEPENDENCIES
  None

RETURN VALUE
  returns an enum that describes the result of the command execution.
  possible values:
    DSAT_ERROR :    if there was any problem in executing the command
    DSAT_OK :       if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_process_cm_mm_info_data
(
  ds_at_ss_info_s_type   *event_info,
  sys_modem_as_id_e_type  subs_id
)
{

  dsat_result_enum_type         result = DSAT_ASYNC_EVENT;
  dsat_num_item_type            ctzr_reporting;
  dsatcmif_servs_state_ms_info *ph_ss_ms_val = NULL;
  char                          tz_str[6];
  sys_time_and_time_zone_s_type date_time;
  boolean                       add_day_month = FALSE;
  int                           hour = 0, minute = 0;

  /* ME doesn't know which time zone it powered up in */
  if (FALSE == IS_VALID_SUBS_ID(subs_id) ||
      ((ph_ss_ms_val = dsat_get_base_addr_per_subs(DSAT_SS_PH_MS_VALS, subs_id, FALSE)) &&
       (NULL == ph_ss_ms_val)))
  {
    DS_ATCOP_ERROR_LOG_1("Invalid Arg: subs_id =%d or NULL ph_ss_ms_val", subs_id);
    return result;
  }

  /* Report timezone change to TE if reporting enabled and timezone has 
     changed from last reported value. Per 27.007, section 8.40 this is
     not effected by +CTZU setting. */
  ctzr_reporting = (dsat_num_item_type)dsatutil_get_val(
                      DSATETSI_EXT_ACT_CTZR_ETSI_IDX, 0, 0, NUM_TYPE);

  if (((ctzr_reporting != 0) && (event_info->last_reported_tz_changed == TRUE)) ||
      ((ctzr_reporting == 2) && (event_info->last_reported_dst_adj_changed == TRUE)))
  {
    dsm_item_type *res_buff_ptr;

    res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_SMALL_ITEM_POOL, TRUE);
    if (NULL != res_buff_ptr)
    {
      if (ph_ss_ms_val->last_reported_tz >= 0)
      {
        (void)snprintf(tz_str,
                       sizeof(tz_str),
                       "\"+%02d\"",
                       ph_ss_ms_val->last_reported_tz);
      }
      else
      {
        (void)snprintf(tz_str,
                       sizeof(tz_str),
                       "\"%02d\"",
                       ph_ss_ms_val->last_reported_tz);
      }

      if (ctzr_reporting == 2)
      {
        res_buff_ptr->used = (word)snprintf((char *) res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "+CTZE: %s,%d",
                                            tz_str,
                                            ph_ss_ms_val->last_reported_dst_adj);

        if (TRUE == event_info->mm_info.univ_time_and_time_zone_avail)
        {
          //Converting Universal time to local time
          hour = event_info->mm_info.univ_time_and_time_zone.hour +
                 (ph_ss_ms_val->last_reported_tz / 4);
          minute = event_info->mm_info.univ_time_and_time_zone.minute;
          
          //Handling both + and - timezone
          if(ph_ss_ms_val->last_reported_tz > 0)
          {
            minute = minute + (ph_ss_ms_val->last_reported_tz % 4) * 15;
            //For + time zone, minute can go beyond 60 minutes, so ajust minute and hour
            if(minute >= 60)
            {
              minute = minute - 60;
              hour = hour + 1;
            }
          }
          else if(ph_ss_ms_val->last_reported_tz % 4 != 0)
          {
            minute = minute + (ph_ss_ms_val->last_reported_tz % 4) * 15;
            //For - time zone, minute can be negative, so adjust minute and hour
            if(minute < 0)
            {
              hour = hour - 1;
              minute = 60 + minute;
            }
          }

          date_time.minute = minute;
          date_time.second = event_info->mm_info.univ_time_and_time_zone.second;
          date_time.year = event_info->mm_info.univ_time_and_time_zone.year;
          date_time.month = event_info->mm_info.univ_time_and_time_zone.month;
          date_time.day = event_info->mm_info.univ_time_and_time_zone.day;
          date_time.time_zone = event_info->mm_info.univ_time_and_time_zone.time_zone;

          //If hour after adjustment become greater than 23
          if(hour >= 24)
          {
            date_time.day = date_time.day + 1;
            date_time.hour = hour - 24;
            //Check for months having number of days 31
            //January to July, odd month is having 31 days
            //August to December, even moth is having 31 days
            if((date_time.month % 2 != 0 && date_time.month <= 7) || 
               (date_time.month % 2 == 0 && date_time.month > 7))
            {
              add_day_month = (date_time.day > 31)? TRUE : FALSE;
            }
            else
            {
              //For month February 
              if(date_time.month == 2)
              {
                //For leap year
                boolean is_leap_year = FALSE;
                if(date_time.year % 4 != 0)
                {
                  is_leap_year = FALSE;
                }
                else if(date_time.year % 100 != 0)
                {
                  is_leap_year = TRUE;
                }
                else if(date_time.year % 400 != 0)
                {
                  is_leap_year = FALSE;
                }
                else
                {
                  is_leap_year = TRUE;
                }
                add_day_month = ((is_leap_year  && date_time.day > 29) ||
                                 (!is_leap_year && date_time.day > 28)) ? TRUE : FALSE;
              }
              else
              {
                //Month having number of days 30
                add_day_month = (date_time.day > 30) ? TRUE : FALSE;
              }
            }
            if( add_day_month == TRUE )
            {
              date_time.day = 1;
              date_time.month = date_time.month + 1;
              if( date_time.month > 12)
              {
                date_time.month = 1;
                date_time.year = date_time.year + 1;
              }
            }
          }
          else if(hour < 0)
          {
            date_time.day = date_time.day - 1;
            date_time.hour = 24 + hour;
            if( date_time.day == 0 )
            {
              //Check for months having number of days 31
              //January to July, odd month is having 31 days
              //August to December, even moth is having 31 days
              if((date_time.month % 2 != 0 && date_time.month <= 7) ||
                 (date_time.month % 2 == 0 && date_time.month > 7))
              {
                date_time.day = 30;
                //If earlier month was March
                //Checking for leap year
                if(date_time.month == 3)
                {
                  if(date_time.year % 4 != 0)
                  {
                    date_time.day = 28;
                  }
                  else if(date_time.year % 100 != 0)
                  {
                    date_time.day = 29;
                  }
                  else if(date_time.year % 400 != 0)
                  {
                    date_time.day = 28;
                  }
                  else
                  {
                    date_time.day = 29;
                  }
                }
                //If the universal month is January, adjust day and year
                else if(date_time.month == 1)
                {
                  date_time.day = 31;
                  date_time.year = date_time.year - 1;
                }
              }
              else
              {
                date_time.day = 31;
              }
              date_time.month = ((date_time.month - 1) > 0) ? (date_time.month - 1): 12;
            }
          }
          else
          {
            date_time.hour = hour;
          }
		  
          res_buff_ptr->used += 
            (word)snprintf((char *) res_buff_ptr->data_ptr + res_buff_ptr->used,
                           res_buff_ptr->size - res_buff_ptr->used,
                           ",\"%04d/%02d/%02d,%02d:%02d:%02d\"",
                           DSAT_YEAR_BASE_2000 + \
                           date_time.year,
                           date_time.month,
                           date_time.day,
                           date_time.hour,
                           date_time.minute,
                           date_time.second);
        }
      }
      else
      {
        res_buff_ptr->used = (word)snprintf((char *) res_buff_ptr->data_ptr,
                                            res_buff_ptr->size,
                                            "+CTZV: %s",
                                            tz_str);
      }

      /* Report DTE the unsolicited result/response code */
      (void)dsatcmdp_send_respose_to_te(res_buff_ptr, DSAT_COMPLETE_RSP);
    }
  }
  
  return result;
} /* dsatetsicmif_process_cm_mm_info_data */

/*==========================================================================
FUNCTION  dsatetsicmif_cm_sups_cmd_interrogate

DESCRIPTION
  This function interrogates the n/w for a particular SS service.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
True- Success
FALSE - failure
SIDE EFFECTS
  None

===========================================================================*/
boolean
dsatetsicmif_cm_sups_cmd_interrogate
(
  void                         *data_block_ptr,
  cm_client_id_type             dsatcm_client_id_lcl,
  const cm_interr_ss_params_s_type   *interr_clip_params
)
{
  mcs_sups_params_s_type dsat_ss_params;
  char                       dsat_mmi_buf[DSAT_MAX_MMI_STRING_LEN];
  cm_num_s_type               dsat_dialed_digits;
  boolean cm_result = TRUE;
  
  memset(&dsat_mmi_buf[0],0,DSAT_MAX_MMI_STRING_LEN);
  memset(&dsat_ss_params,CM_CALL_CMD_PARAM_DEFAULT_VALUE,sizeof(mcs_sups_params_s_type));
  memset(&dsat_dialed_digits,CM_CALL_CMD_PARAM_DEFAULT_VALUE,sizeof(cm_num_s_type));
  if(allLineIdentificationSS != interr_clip_params->ss_code)
  {
 
    dsat_ss_params.mode = MCS_SUPS_MODE_QUERY;
    dsat_ss_params.code = interr_clip_params->ss_code;
    cm_result = mcs_sups_build_string ( &dsat_ss_params, &dsat_mmi_buf[0], DSAT_MAX_MMI_STRING_LEN);

    if (cm_result != E_SUCCESS)
    {
     DS_ATCOP_ERROR_LOG_0("MMI string genration failed ");
      return DSAT_ERROR;
    }
    dsat_dialed_digits.len = strlen((const char *)dsat_mmi_buf);
    dsat_dialed_digits.digit_mode = CM_DIGIT_MODE_8BIT_ASCII;
   
   (void) dsatutil_memscpy((void*)&dsat_dialed_digits.buf[0],
           CM_MAX_NUMBER_CHARS,(void*)&dsat_mmi_buf[0],
           MIN(dsat_dialed_digits.len,DSAT_MAX_MMI_STRING_LEN));
   
    DS_AT_MSG_SPRINTF_2_HIGH(
                   "MMI string length %d String  %s",dsat_dialed_digits.len,dsat_mmi_buf);

#ifdef FEATURE_DUAL_SIM

  return cm_sups_cmd_interrogate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func,
                                     data_block_ptr,
                                     dsatcm_client_id_lcl,
                                     interr_clip_params,
                                     &dsat_dialed_digits,
                                     CM_ORIG_CLIENT_CATEG_USER,
                                     TRUE,
                                     dsat_get_current_subs_id(FALSE));
#else
  return cm_sups_cmd_interrogate_exten(etsicmif_sups_exten_cmd_cb_func,
                                   data_block_ptr,
                                   dsatcm_client_id_lcl, 
                                   interr_clip_params,
                                   &dsat_dialed_digits,
                                    CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */
  }
  else
  {
   /*Spec 22.030 doesn't mention any MMI string for CDIP command*/
    DS_AT_MSG0_HIGH("CDIP command doesn't require DIALED DIGIT ");
#ifdef FEATURE_DUAL_SIM

     return cm_sups_cmd_interrogate_cc_exten_per_subs(etsicmif_sups_exten_cmd_cb_func,
                                        data_block_ptr,
                                        dsatcm_client_id_lcl,
                                        interr_clip_params,
                                   NULL,
                                        CM_ORIG_CLIENT_CATEG_USER,
                                   TRUE,
                                   dsat_get_current_subs_id(FALSE));
#else
     return cm_sups_cmd_interrogate_exten(etsicmif_sups_exten_cmd_cb_func,
                                      data_block_ptr,
                                      dsatcm_client_id_lcl, 
                                      interr_clip_params,
                                      NULL,
                                      CM_ORIG_CLIENT_CATEG_USER);
#endif /* FEATURE_DUAL_SIM */

  }

} /* dsatetsicmif_cm_sups_cmd_interrogate */


/*===========================================================================

FUNCTION  dsatetsicmif_get_colp_info_or_report_result

DESCRIPTION
  This function report connected number to the TE if CLIP reporting is enabled.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_OK : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsatetsicmif_get_colp_info_or_report_result
(
  sys_modem_as_id_e_type        subs_id,        /* Subscription ID */
  const ds_at_call_info_s_type *call_info_ptr   /* Incoming call information */
)
{
  dsat_result_enum_type result = DSAT_ASYNC_EVENT;

  if(cm_mm_call_cmd_get_call_info(dsatcmif_call_cmd_cb_func,
                                  NULL,
                                  dsatcm_client_id,
                                  call_info_ptr->call_id) == TRUE)
  {
    dsat_colp_pending[subs_id] = TRUE;
  }
  else
  {
    return dsat_send_cme_error(DSAT_CME_PHONE_FAILURE);
  }

  return result;
} /* dsatetsicmif_get_colp_info_or_report_result */



/*==========================================================================
FUNCTION  DSATETSICMIF_GET_CLIP_INFO_OR_REPORT_RESULT

DESCRIPTION
  This function report Caller ID to the TE if CLIP reporting is enabled.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_OK : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_get_clip_info_or_report_result
(
  sys_modem_as_id_e_type          subs_id,
  ds_at_cm_call_event_type *call_event_ptr /* Call event pointer */
)
{
  dsatetsicall_call_state_da_info  *call_da_val = NULL;
  
  call_da_val = dsat_get_base_addr_per_subs(DSAT_CALL_DA_VALS, subs_id, FALSE);

  if((dsat_num_item_type)dsatutil_get_val(
      DSATETSI_EXT_ACT_CLIP_ETSI_IDX,0,0,NUM_TYPE) == DSAT_CLIP_ENABLED)
  {
    if(call_event_ptr->event_info.dsat_mode_info.info_type == CM_CALL_MODE_INFO_GW_CS &&
       call_event_ptr->event_info.dsat_mode_info.info.gw_cs_call.calling_party_bcd_number.present == TRUE)
    {
      
      if(cm_mm_call_cmd_get_call_info(dsatcmif_call_cmd_cb_func,
                                      NULL,
                                      dsatcm_client_id,
                                      call_event_ptr->event_info.call_id) == FALSE)
      {
        return dsat_send_cme_error(DSAT_CME_PHONE_FAILURE);
      }
      dsat_clip_pending[subs_id] = TRUE;
    }
    else if(call_event_ptr->event_info.dsat_mode_info.info_type == CM_CALL_MODE_INFO_IP &&
            call_event_ptr->event_info.num.pi == 0 && call_event_ptr->event_info.num.len > 0)
    {
      /* Report CLIP for IP Call */
      dsatetsicall_report_clip_result(call_event_ptr, subs_id);
    }
    else
    {
      byte         dsat_cli_presence = DSAT_CLI_NOT_AVAILABLE;
     
      if( (call_event_ptr->event_info.dsat_mode_info.info_type == CM_CALL_MODE_INFO_GW_CS) &&
          (call_event_ptr->event_info.dsat_mode_info.info.gw_cs_call.cause_of_no_cli.present) && 
          (call_event_ptr->event_info.dsat_mode_info.info.gw_cs_call.cause_of_no_cli.cause_value == DSAT_CLI_RESTRICTED) )
      {
        dsat_cli_presence = DSAT_CLI_RESTRICTED;
      }
     
      /* No CLI available (cases 1 & 2) setting # to empty and type to 128 */
      /* Remember the CLIP info to relay TE during alerting/ringing phase */
      call_da_val->dsat_lineid_buf_length = (word)snprintf((char*)&call_da_val->dsat_lineid_buf[0],
                                            DSAT_MAX_LINEID_BUF,
                                           "+CLIP: \"\",%d,,,,%d",
                                           DSAT_CLIP_NUMBER_TYPE_UNKNOWN,
                                           dsat_cli_presence);
    }
  }
  return DSAT_ASYNC_EVENT;
} /* dsatetsicmif_get_clip_info_or_report_result */


/*==========================================================================
FUNCTION  DSATETSICMIF_GET_CDIP_INFO_OR_REPORT_RESULT

DESCRIPTION
  This function report Caller ID to the TE if CDIP reporting is enabled.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR : if there was any problem in executing the command
    DSAT_OK : if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
dsat_result_enum_type dsatetsicmif_get_cdip_info_or_report_result
(
  sys_modem_as_id_e_type          subs_id,
  const ds_at_cm_call_event_type *call_event_ptr /* Call event pointer */
)
{
  dsatetsicall_call_state_da_info  *call_da_val = NULL;
  call_da_val = dsat_get_base_addr_per_subs(DSAT_CALL_DA_VALS, subs_id, FALSE);

  if(NULL == call_da_val)
  {
    return DSAT_ASYNC_EVENT;
  }

  if ( (dsat_num_item_type)dsatutil_get_val(
            DSATETSI_EXT_ACT_CDIP_ETSI_IDX,0,0,NUM_TYPE) == DSAT_CDIP_ENABLED )
  {
    if ( call_event_ptr->event_info.dsat_mode_info.info.gw_cs_call.called_party_bcd_number.present
                                                                   == TRUE )
    {
      
      if ( cm_mm_call_cmd_get_call_info(dsatcmif_call_cmd_cb_func,
                                      NULL,
                                      dsatcm_client_id,
                                      call_event_ptr->event_info.call_id) == FALSE )
      {
        return dsat_send_cme_error(DSAT_CME_PHONE_FAILURE);
      }
      dsat_cdip_pending[subs_id] = TRUE;
    }
    else
    {
      dsm_item_type           *res_buff_ptr;

      res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, TRUE);
      if (NULL != res_buff_ptr)
      {
        /* No CDI available (cases 1 & 2) setting # to empty and type to 128 */
        res_buff_ptr->used += (word)snprintf(
           (char*)res_buff_ptr->data_ptr, res_buff_ptr->size, "+CDIP: \"\",%d",
           DSAT_CDIP_NUMBER_TYPE_UNKNOWN);

        /* Remember the CDIP info to relay TE during alerting/ringing phase */

        if (res_buff_ptr->used <= CM_CALLED_PARTY_BCD_NO_LENGTH)
        {
          (void) dsatutil_memscpy((void*)&call_da_val->dsat_called_lineid_buf[0],
                  DSAT_MAX_CALLED_LINEID_BUF,(void*)res_buff_ptr->data_ptr,
                  MIN(res_buff_ptr->size,res_buff_ptr->used));

          call_da_val->dsat_called_lineid_buf_length = MIN(res_buff_ptr->size,res_buff_ptr->used);
        }
        else
        {
         DS_ATCOP_ERROR_LOG_0("CDIP: Buffer Over Flow");
          return DSAT_ERROR;
        }

        (void)dsatcmdp_send_urc_per_subs(subs_id, res_buff_ptr, DSAT_COMPLETE_RSP);
      }
    }
  }
  return DSAT_ASYNC_EVENT;
} /* dsatetsicmif_get_cdip_info_or_report_result */
/*===========================================================================

FUNCTION: ETSICMIF_LOOKUP_CLASS

DESCRIPTION

  This funciton perforces a lookup for class values based on basic service
  group code and type.

  There is an issue in that the basic service group set is larger than
  the ATCOP class set.  It is possible for the network to have a non-
  mappable value if the UI is used to setup the facility lock and then
  ATCOP is used to query it. In those cases dsat_bsg_extra_conversion_table 
  is used to map those values.

DEPENDENCIES
  None

RETURN VALUE
  Returns element form the class enum
    DSAT_SS_CLASS_MAX :  if BSG parameters wer not mapped successfully
    other :              mapped class value

SIDE EFFECTS
  None

===========================================================================*/

LOCAL uint16 etsicmif_lookup_class
(
  bsg_code_type    bsg_type,        /* BSG type */
  uint8  bsg_code                   /* BSG code */
)
{
  uint16 class = (uint16)DSAT_SS_CLASS_MAX;
  uint8 index = 0;

  /* Lookup BSG for Class parameter */
  while ( DSAT_SS_CLASS_MAX != dsat_bsg_conversion_table[index].class )
  {
    if ((dsat_bsg_conversion_table[index].net_bsg_code == bsg_code) &&
        (dsat_bsg_conversion_table[index].bsg_type == bsg_type))
    {
      class = (uint16)dsat_bsg_conversion_table[index].class;
      break;
    }
    index++;
  }
  if ((uint16)DSAT_SS_CLASS_MAX == class)
  {
    index = 0;
    /* Lookup BSG extra conversion table for Class parameter */
    while ( DSAT_SS_CLASS_MAX != dsat_bsg_extra_conversion_table[index].class )
    {
      if ((dsat_bsg_extra_conversion_table[index].net_bsg_code == bsg_code) &&
          (dsat_bsg_extra_conversion_table[index].bsg_type == bsg_type))
      {
        class = (uint16)dsat_bsg_extra_conversion_table[index].class;
        break;
      }
      index++;
    }
  }
  if ((uint16)DSAT_SS_CLASS_MAX == class)
  {
    DS_AT_MSG2_ERROR("Could not decode BSG type,code: %d,%d",
               bsg_type, bsg_code);
  }
  else
  {
    DS_AT_MSG3_HIGH("BSG type,code and class: %d,%d, %d",
               bsg_type, bsg_code, class);
  }

  return class;
}
/*===========================================================================

FUNCTION  ETSICMIF_FORMAT_CLASS_RESPONSE

DESCRIPTION
  This function formats the response for various class based
  supplementary services comamnds.  The class parameter is
  validated in this routine as well.  If class is zero, no
  class value to displayed in the response.  A tail buffer
  may be passed for all data appearing after the class value.
  
DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_CMD_ERR_RSP : if +CME error respose was generated
    DSAT_ASYNC_EVENT : if aynchronous command continues successfully

SIDE EFFECTS
  None

===========================================================================*/
LOCAL dsat_result_enum_type etsicmif_format_class_response
(
  dsm_item_type * res_buff_ptr,             /* Result buffer */
  const byte * name,                        /* Command name  */
  const uint16 class,                       /* Class value   */
  const uint8 status,                       /* Status value  */
  const byte * tail                         /* Tail info buffer  */
)
{
  /* Verify the class was successfully mapped from BSG */
  if ( (uint16)DSAT_SS_CLASS_MAX == class)
  {
    /* Set error for indeterminant class */
    res_buff_ptr->used = 0;  /* clear response buffer */
    dsatme_set_cme_error (DSAT_CME_SUPS_UNKNOWN_CLASS,
                              res_buff_ptr);
    return DSAT_CMD_ERR_RSP;
  }
          
  /* Generate response */
  res_buff_ptr->data_ptr[res_buff_ptr->used] = '\0';
  res_buff_ptr->used = (word) snprintf ((char*)res_buff_ptr->data_ptr,
                                       res_buff_ptr->size,
                                       "%s%s: %d,%d%s",
                                       res_buff_ptr->data_ptr,
                                       name, 
                                       status,
                                       class,
                                       (NULL == tail)? (byte*)"" : tail);

  return DSAT_ASYNC_EVENT;
}


/*===========================================================================

FUNCTION  DSATETSICMIF_REPORT_CCFC

DESCRIPTION
  This function reports the call forwarding supplementary service status
  received from Call Manager.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR :    if there was any problem in execution.
    DSAT_OK :       if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsatetsicmif_report_ccfc
(
  ds_at_cm_sups_event_type *sups_event,       /* SUPS Event pointer         */
  sys_modem_as_id_e_type    subs_id
)
{
#define ALL_CLASSES     255
#define STATUS_INACTIVE 0
  
  dsat_result_enum_type result = DSAT_ASYNC_EVENT;
  dsm_item_type * res_buff_ptr = NULL;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val = NULL;
  uint8                               num_active_classes = 0;
  uint8                               i = 0;
  uint8                               status = 0;
  uint16                              class = 0;
  const ds_at_sups_event_info_s_type *einfo_ptr = &sups_event->event_info;
  boolean is_ext_cmd = FALSE;
  boolean is_ccfcu = FALSE;


  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);

  if(NULL == sups_ms_val)
  {
    return result;
  }

  res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, FALSE);
  /* Initialize result buffer */
  res_buff_ptr->data_ptr[0] = '\0';

  if(CHECK_PENDING(DSATETSI_EXT_ACT_CCFC_ETSI_IDX, 0, DSAT_PENDING_CCFC_EXTENDED ))
  {
    is_ext_cmd = TRUE;
  }

  if(CHECK_PENDING(DSATETSI_EXT_ACT_CCFCU_ETSI_IDX, 0, DSAT_PENDING_CCFCU ))
  {
    is_ccfcu = TRUE;
  }
  
  switch (einfo_ptr->conf_type)
  {
    case FWD_FEATURE_LIST_INFO:
      if (!einfo_ptr->fwd_feature_list.present)
      {
       DS_ATCOP_ERROR_LOG_0("Fowarding feature list info missing");
        break;
      }

      /* Report for each forwarding registration */
      while (einfo_ptr->fwd_feature_list.forwarding_feature_list_length > i)
      {
        const forwarding_feature_T * fflist_ptr =
          &einfo_ptr->fwd_feature_list.forwarding_feature[i];
        uint8 type = 0;
        uint8 satype = 0;
        uint8 j = 0;
        boolean hit = FALSE;
        /* Size temp buffer for address, subaddress, and various other characters */
        #define MAX_CCFC_ADDRESS_SIZE (2 * CM_CALLED_PARTY_BCD_NO_LENGTH * \
                                           (2*MAXNO_FORWARD_TO_NUMBER))
        byte address[MAX_CCFC_ADDRESS_SIZE]; 
        byte * a_ptr = &address[1];
        uint8 a_length = 0;
        #define MAX_CCFC_RSP_SIZE (CM_CALLED_PARTY_SUBADDRESS_LENGTH + \
                                   MAX_CCFC_ADDRESS_SIZE + 20)
        byte buffer[MAX_CCFC_RSP_SIZE];
        byte * s_ptr = buffer;

        status = (fflist_ptr->ss_status.present &&
                  fflist_ptr->ss_status.cm_ss_active)? 1 : 0;

        /* Per 3GPP TS 27.007 section Do not print an info text response line
           for an inactive class */
        if ( status == 0 )
        {
          i++;
          continue;
        }
        else
        {
          num_active_classes++;
        }

        res_buff_ptr->data_ptr[res_buff_ptr->used] = '\0';
        memset((void*)buffer, 0, sizeof(buffer));
        memset((void*)address, 0, sizeof(address));

        /* Decode BSG into Class */
        class = (!fflist_ptr->basic_service.present)? 0 :
                   etsicmif_lookup_class(fflist_ptr->basic_service.code_type,
                                         fflist_ptr->basic_service.bs_code);

        /* Initialize buffer */
        *s_ptr++ = ',';

        if(is_ccfcu)
        {
           *s_ptr++ = 49;   /* numbertype: 1 */
           *s_ptr++ = ',';
           *s_ptr++ = 48;   /* ton: 0 */
           *s_ptr++ = ',';
           *s_ptr++ = '"';
          if(NULL != fflist_ptr->forwarded_to_uri &&
             fflist_ptr->forwarded_to_uri->fwd_to_uri_length > 0)
          {
            dsatutil_memscpy(s_ptr, (MAX_CCFC_RSP_SIZE - (s_ptr - buffer) ),
                             fflist_ptr->forwarded_to_uri->fwd_to_uri,
                             fflist_ptr->forwarded_to_uri->fwd_to_uri_length);
            s_ptr += fflist_ptr->forwarded_to_uri->fwd_to_uri_length;
            hit = TRUE;
          }
        }

        if(!is_ccfcu || !hit)
        {
          /* Decode dialed number */
          /* Multiple cm_called_party_bcd_no_T structures used for */
          /* long numbers.  Need to append then decode from BCD.   */
          *s_ptr++ = '"';
          /* Loop over forwarded to number segments */
          while ( j < (2*MAXNO_FORWARD_TO_NUMBER) )
          {
            /* Check for availability */
            if (fflist_ptr->forwarded_to_number[j].present)
            {
              /* Append number segment to existing buffer */
              uint8 k;
              for (k=0; k < fflist_ptr->forwarded_to_number[j].length; k++)
              {
                *a_ptr++ = fflist_ptr->forwarded_to_number[j].data[k];
              }
              a_length += fflist_ptr->forwarded_to_number[j].length;
            }
            j++;
          }
          address[0] = a_length;

        
          /* Convert from BCD to ASCII string */
          if (a_ptr != address)
          {
            cm_util_bcd_num_to_ascii_num(address,s_ptr,
                          (MAX_CCFC_RSP_SIZE - (s_ptr - buffer) ));

            /* Set Type based on '+' prefix */
            type = (DSAT_TA_INTER_PREFIX == *s_ptr) ?
                    DSAT_TA_INTERNATIONAL : DSAT_TA_UNKNOWN;
           
            s_ptr += strlen((char*)s_ptr);
            hit = TRUE;
          }
        }

        if(fflist_ptr->forwarded_to_uri != NULL)
        {
          ref_cnt_obj_release(fflist_ptr->forwarded_to_uri);
        }
        *s_ptr++ = '"';
        *s_ptr++ = ',';

        if (0 != type)
           s_ptr = psutil_itoa (type, s_ptr, 10);
        *s_ptr++ = ',';

        /* Decode subaddress */
        if (fflist_ptr->forwarded_to_subaddress.present)
        {
          *s_ptr++ = '"';
          /* Subaddress has following structure */
          /* data[0] - type                     */
          /* data[1] - AFI                      */
          /* data[2...] - string                */
          (void)strlcpy((char*)s_ptr,
                        (char*)&fflist_ptr->forwarded_to_subaddress.data[2],
                        MAX_CCFC_RSP_SIZE);
          s_ptr += (fflist_ptr->forwarded_to_subaddress.length-2);
          *s_ptr++ = '"';
          *s_ptr++ = ',';
      
          /*  Subaddress type in first data array element */
          satype = fflist_ptr->forwarded_to_subaddress.data[0];
          s_ptr = psutil_itoa (satype, s_ptr, 10);
          hit = TRUE;
        }
        else
        {
          *s_ptr++ = ',';
        }
        *s_ptr++ = ',';

        /* Decode timer */
        if (fflist_ptr->no_reply_condition_timer.present)
        {
          s_ptr = psutil_itoa (
                    fflist_ptr->no_reply_condition_timer.timer_value,
                    s_ptr, 10);
          hit = TRUE;
        }
        *s_ptr++ = '\0';

        /* Format response */
        if (0 < i++)
        {
          /* Add new line */
          res_buff_ptr->data_ptr[res_buff_ptr->used++] = '\n';
        }
        result = etsicmif_format_class_response(res_buff_ptr,
                                                (is_ccfcu)?(const byte *)"+CCFCU":
                                                (is_ext_cmd)?(const byte *)"$QCCCFC":(const byte *)"+CCFC",
                                                class,
                                                status,
                                                (hit)? buffer : NULL);

        /* Display call forwarding start and end time if AT Command is AT$QCCCFC and time is present */
        if(einfo_ptr->sups_time_info.time_present && is_ext_cmd)
        {
          /* Format response */
          /* hh:mm:ss#hh:mm:ss format */
          res_buff_ptr->used = (word) snprintf((char*)(res_buff_ptr->data_ptr ),
		  	        res_buff_ptr->size,
                    "%s,\"%2.2d:%2.2d:%2.2d#%2.2d:%2.2d:%2.2d\"",
                    res_buff_ptr->data_ptr,
                    einfo_ptr->sups_time_info.call_fwd_start_time.hour,
                    einfo_ptr->sups_time_info.call_fwd_start_time.minute,
                    einfo_ptr->sups_time_info.call_fwd_start_time.second,
                    einfo_ptr->sups_time_info.call_fwd_end_time.hour,
                    einfo_ptr->sups_time_info.call_fwd_end_time.minute,
                    einfo_ptr->sups_time_info.call_fwd_end_time.second);
        }
        if (DSAT_ASYNC_EVENT != result)
        {
          break;
        }
      }

      /* If there were no active classes then no info text response has been
         given so create one indicating all classes inactive */
      if ( num_active_classes == 0 )
      {
        result = etsicmif_format_class_response(res_buff_ptr,
                                                (is_ccfcu)?(const byte *)"+CCFCU":
                                                (is_ext_cmd)?(const byte *)"$QCCCFC":(const byte *)"+CCFC",
                                                ALL_CLASSES,
                                                STATUS_INACTIVE,
                                                NULL);
      }
      break;

    case SS_STATUS_INFO:
      /* Report active only if active flag set */
      status = (einfo_ptr->ss_status.present &&
                einfo_ptr->ss_status.cm_ss_active)? 1 : 0;

      /* Report all classes if basic service group info absent */
      class = (!einfo_ptr->basic_service.present)?
                (uint16)DSAT_SS_CLASS_ALL :
                etsicmif_lookup_class(einfo_ptr->basic_service.code_type,
                                      einfo_ptr->basic_service.bs_code);

      /* Format response */
      result = etsicmif_format_class_response(res_buff_ptr,
                                              (is_ccfcu)?(const byte *)"+CCFCU":
                                              (is_ext_cmd)?(const byte *)"$QCCCFC":(const byte *)"+CCFC",
                                              class,
                                              status,
                                              NULL);
      break;

    default:
      DS_ATCOP_ERROR_LOG_1("Unrecognized confirmation type: =d",
                 einfo_ptr->conf_type);
      result = DSAT_ERROR;
      break;
  }
  
  sups_ms_val->dsat_ss_cm_data.pending_rsp = TRUE;
  /* format response, send the response to the user as information text, */
  /* Clear the regional block indications flag, & free res_buff_ptr */
  dsatcmdp_handle_async_cmd_rsp( res_buff_ptr, 
                                 ( (result == DSAT_ASYNC_EVENT) ?  
                                          DSAT_START_OF_RSP :
                                          DSAT_COMPLETE_RSP));

  res_buff_ptr = NULL;

  return result;
}  /* dsatetsicmif_report_ccfc */

/*===========================================================================

FUNCTION  DSATETSICMIF_RETURN_CCFC_REG_NUM

DESCRIPTION
  This function return a pointer to the number
DEPENDENCIES
  None

RETURN VALUE
   Returns a pointer to number .

SIDE EFFECTS
  None

===========================================================================*/
byte* dsatetsicmif_return_ccfc_reg_num(void)
{
  dsatetsicmif_sups_state_ss_info  *sups_ss_val = NULL;
  
  sups_ss_val = dsat_get_base_addr(DSAT_SUPS_SS_VALS, FALSE);
  return (byte*)sups_ss_val->dsat_reg_number;
}/*dsatetsicmif_return_ccfc_reg_num*/

/*===========================================================================

FUNCTION  DSATETSICMIF_REPORT_CLCK

DESCRIPTION
  This function reports the facility lock supplementary service status
  received from Call Manager.

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR :    if there was any problem in execution.
    DSAT_OK :       if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsatetsicmif_report_clck
(
  const ds_at_cm_sups_event_type *sups_event, /* Sups event pointer */
  const ds_at_cmd_status_type    *status_ptr,  /* DS Status pointer          */
  sys_modem_as_id_e_type          subs_id
)
{
  dsat_result_enum_type                result          = DSAT_ASYNC_EVENT;
  dsm_item_type                       *res_buff_ptr    = NULL;
  dsatetsicmif_sups_state_ms_info     *sups_ms_val     = NULL;
  const ds_at_sups_event_info_s_type  *einfo_ptr = NULL;

  res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, FALSE);
  /* Initialize result buffer */
  res_buff_ptr->data_ptr[0] = '\0';

  /* Process network information */
  if (NULL != sups_event)
  {
    uint8 i = 0;
    uint8 status = 0;
    uint16 class = 0;

    sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);
    if(NULL == sups_ms_val)
    {
      return result;
    }
    
    einfo_ptr  = &sups_event->event_info;
  
    switch (einfo_ptr->conf_type)
    {
      case CALL_BARRING_INFO:
        /* Report for each subscription */
        while (einfo_ptr->call_barring_info.call_barring_info_length > i)
        {
          const call_barring_feature_T * cblist_ptr =
            &einfo_ptr->call_barring_info.call_barring_feature_list[i];

          /* Report active only if active flag set */
          status = (cblist_ptr->cm_ss_status.present &&
                    cblist_ptr->cm_ss_status.cm_ss_active)? 1 : 0;
     
          class = (!cblist_ptr->basic_service.present)? 0 :
            etsicmif_lookup_class(cblist_ptr->basic_service.code_type,
                                  cblist_ptr->basic_service.bs_code);

          /* Format response */
          if (0 < i++)
          {
            /* Add new line */
            res_buff_ptr->data_ptr[res_buff_ptr->used++] = '\n';
          }
          result = etsicmif_format_class_response
            (res_buff_ptr, (const byte *)dsat_curr_cmd_var.parse_table->name,
             class, status, NULL);
          if (DSAT_ASYNC_EVENT != result)
          {
            break;
          }
        }
        break;

      case BSG_LIST_INFO:
        /* Report for each subscription */
        while (einfo_ptr->bsg_list.list_length  > i)
        {
          const basic_service_T *bsglist_ptr = &einfo_ptr->bsg_list.list[i];

          /* Report active by default */
          status = 1;
     
          class = (!bsglist_ptr->present)? 0 :
            etsicmif_lookup_class(bsglist_ptr->code_type,
                                  bsglist_ptr->bs_code);

          /* Format response */
          if (0 < i++)
          {
            /* Add new line */
            res_buff_ptr->data_ptr[res_buff_ptr->used++] = '\n';
          }
          result = etsicmif_format_class_response(res_buff_ptr,
                                                  (const byte *)
                                                  dsat_curr_cmd_var.parse_table->name,
                                                  class,
                                                  status,
                                                  NULL);
          if (DSAT_ASYNC_EVENT != result)
          {
            break;
          }
        }
        break;

      case SS_STATUS_INFO:
        /* Report active only if active flag set */
        status = (einfo_ptr->ss_status.present &&
                  einfo_ptr->ss_status.cm_ss_active)? 1 : 0;
     
        /* Report all classes if basic service group info absent */
        class = (!einfo_ptr->basic_service.present)?
                  (uint16)DSAT_SS_CLASS_ALL :
                  etsicmif_lookup_class(einfo_ptr->basic_service.code_type,
                                        einfo_ptr->basic_service.bs_code);

        /* Format response */
        result = etsicmif_format_class_response(res_buff_ptr,
                                                (const byte *)
                                                  dsat_curr_cmd_var.parse_table->name,
                                                class,
                                                status,
                                                NULL);
        break;
      
      default:
        DS_ATCOP_ERROR_LOG_1("Unrecognized confirmation type: =d",
                   einfo_ptr->conf_type);
        result = DSAT_ERROR;
        break;
    }
    
    /* send the response to the user */
    sups_ms_val->dsat_ss_cm_data.pending_rsp = TRUE;

    /* format response, send the response to the user as information text, */
    /* Clear the regional block indications flag, & free res_buff_ptr */
    dsatcmdp_handle_async_cmd_rsp( res_buff_ptr, 
                                 ( (result == DSAT_ASYNC_EVENT) ?  
                                            DSAT_START_OF_RSP :
                                            DSAT_COMPLETE_RSP));
  }
#ifdef FEATURE_DATA_ETSI_PIN
  /* Process MMGSDI information */
  else if (NULL != status_ptr)
  {
    uint8 status = 0;

    /* Map MMGSDI PIN status to response */
    switch (status_ptr->cmd_data)
    {
      case MMGSDI_PIN_DISABLED:
      case MMGSDI_PIN_STATUS_NOT_INITIALIZED:
        /* Assume no pin; equivalent to disabled */
        status = 0;
        break;

      case MMGSDI_PIN_ENABLED_VERIFIED:
      case MMGSDI_PIN_ENABLED_NOT_VERIFIED:
      case MMGSDI_PIN_BLOCKED:
      case MMGSDI_PIN_PERM_BLOCKED:
        status = 1;
        break;

      default:
        DS_AT_MSG1_MED("Unsupported MMGSDI PIN state: %d",status_ptr->cmd_data);
        result = DSAT_ERROR;
        break;
    }
    
    /* Generate response */
    res_buff_ptr->used = (word) snprintf ((char*)res_buff_ptr->data_ptr,
                                         res_buff_ptr->size,
                                         "%s: %d",
                                         dsat_curr_cmd_var.parse_table->name,
                                         status);

    /* format response, send the response to the user as information text, */
    /* Clear the regional block indications flag, & free res_buff_ptr */
    dsatcmdp_handle_async_cmd_rsp( res_buff_ptr, DSAT_COMPLETE_RSP );  

    result = DSAT_OK;
  }
#endif /*  FEATURE_DATA_ETSI_PIN */
  /* Error if neither parameter provided */
  else
  {
    dsm_free_packet(&res_buff_ptr);
   DS_ATCOP_ERROR_LOG_0("Unsupport call to function");
    result = DSAT_ERROR;
  }
  
  return result;
}  /* dsatetsicmif_report_clck */

/*===========================================================================

FUNCTION  DSATETSICMIF_REPORT_CCWA

DESCRIPTION
  This function reports the call waiting supplementary service status
  received from Call Manager. 

DEPENDENCIES
  None

RETURN VALUE
  Returns an enum that describes the result of the execution.
  Possible values:
    DSAT_ERROR :    if there was any problem in execution.
    DSAT_OK :       if it is a success.

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
dsat_result_enum_type dsatetsicmif_report_ccwa
(
  const ds_at_cm_sups_event_type  *sups_event, /* Sups event pointer */
  const ds_at_cmd_status_type  * status_ptr,  /* DS Status pointer          */
  sys_modem_as_id_e_type            subs_id
)
{
  dsat_result_enum_type             result       = DSAT_ASYNC_EVENT;
  dsm_item_type                    *res_buff_ptr = NULL;
  dsatetsicmif_sups_state_ms_info  *sups_ms_val  = NULL;

  sups_ms_val = dsat_get_base_addr_per_subs(DSAT_SUPS_MS_VALS, subs_id, FALSE);

  if(NULL == sups_ms_val)
  {
    return result;
  }

  /* Process network information */
  if (NULL != sups_event)
  {
    uint8 i = 0;
    uint8 status = 0;
    uint16 class = 0;
    const ds_at_sups_event_info_s_type * einfo_ptr = NULL;
        
    res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, FALSE);
    /* Initialize result buffer */
    res_buff_ptr->data_ptr[0] = '\0';
    einfo_ptr  = &sups_event->event_info;
  
    switch (einfo_ptr->conf_type)
    {
      case BSG_LIST_INFO:
        /* Report for each subscription */
        while (einfo_ptr->bsg_list.list_length  > i)
        {
          const basic_service_T *bsglist_ptr = &einfo_ptr->bsg_list.list[i];

          /* Report active by default */
          status = 1;
     
          class = (!bsglist_ptr->present)? 0 :
            etsicmif_lookup_class(bsglist_ptr->code_type,
                                  bsglist_ptr->bs_code);

          /* Format response */
          if (0 < i++)
          {
            /* Add new line */
            res_buff_ptr->data_ptr[res_buff_ptr->used++] = '\n';
          }
          result = etsicmif_format_class_response(res_buff_ptr,
                                                  (const byte *)"+CCWA",
                                                  class,
                                                  status,
                                                  NULL);
          if (DSAT_ASYNC_EVENT != result)
          {
            break;
          }
        }
        break;

      case SS_STATUS_INFO:
        /* Report active only if active flag set */
        status = (einfo_ptr->ss_status.present &&
                  einfo_ptr->ss_status.cm_ss_active)? 1 : 0;
     
        /* Report all classes if basic service group info absent */
        class = (!einfo_ptr->basic_service.present)?
                  (uint16)DSAT_SS_CLASS_ALL :
                  etsicmif_lookup_class(einfo_ptr->basic_service.code_type,
                                        einfo_ptr->basic_service.bs_code);

        /* Format response */
        result = etsicmif_format_class_response(res_buff_ptr,
                                                (const byte *)"+CCWA",
                                                class,
                                                status,
                                                NULL);
        break;
      
      default:
        DS_ATCOP_ERROR_LOG_1("Unrecognized confirmation type: =d",
                   einfo_ptr->conf_type);
        result = DSAT_ERROR;
        break;
    }
    
    /* send the response to the user */
    sups_ms_val->dsat_ss_cm_data.pending_rsp = TRUE;

    /* format response, send the response to the user as information text, */
    /* Clear the regional block indications flag, & free res_buff_ptr */
    dsatcmdp_handle_async_cmd_rsp( res_buff_ptr, 
                                 ( (result == DSAT_ASYNC_EVENT) ?  
                                            DSAT_START_OF_RSP :
                                            DSAT_COMPLETE_RSP));
  }
  /* Error if neither parameter provided */
  else
  {
   DS_ATCOP_ERROR_LOG_0("Unsupported call to function");
    result = DSAT_ERROR;
  }

  return result;
}  /* dsatetsicmif_report_ccwa */

/*===========================================================================

FUNCTION  DSATETSICMIF_CMCCS_GET_CCSTATUS

DESCRIPTION
  This function gets call status based on voice call state and other parameters.

DEPENDENCIES
  None

RETURN VALUE
  Return call status.
  Default:
         DSAT_CMCCS_IDLE

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
uint8 dsatetsicmif_cmccs_get_ccstatus
(
  voice_state_e_type    voice_call_state,
  boolean               etsicall_was_waiting
)
{
  /* Call status based on voice state */
  if(voice_call_state == DSAT_VOICE_STATE_CONNECTING)
  {
    return DSAT_CMCCS_CONNECTING;
  }
  else if(voice_call_state == DSAT_VOICE_STATE_ACTIVE)
  {
    return DSAT_CMCCS_ACTIVE;
  }
  else if(voice_call_state == DSAT_VOICE_STATE_WAITING)
  {
    return (etsicall_was_waiting)? DSAT_CMCCS_CALL_WAITING_MT :DSAT_CMCCS_ALERTING_MT;
  }
  return DSAT_CMCCS_IDLE;
}

/*===========================================================================

FUNCTION  DSATETSICMIF_REPORT_CMCCS

DESCRIPTION
  This function reports the call status.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
void dsatetsicmif_report_cmccs
(
  sys_modem_as_id_e_type           subs_id,
  ds_at_cm_call_event_type        *call_event
)
{
  #define DSAT_SDP_MD_SIZE 8

  dsm_item_type                    *res_buff_ptr = NULL;
  dsat_num_item_type                cmccs_val    = (dsat_num_item_type)dsatutil_get_val(
  	                                            DSATETSI_EXT_ACT_CMCCS_ETSI_IDX,0,0,NUM_TYPE);
  uint8 ccidx;
  uint8 ccstatus;
  uint8 numbertype = DSAT_CMCCSI_NUMBERTYPE_NOT_VALID;
  dsat_string_item_type *sdp_md = NULL;
  const dsat_string_item_type sdp_md1[DSAT_SDP_MD_SIZE] = "m=audio";
  const dsat_string_item_type sdp_md2[DSAT_SDP_MD_SIZE] = "m=video";
  boolean neg_status_present = FALSE;
  dsat_neg_status_e_type neg_status =  DSAT_NEG_STATUS_NONE;

  dsatetsicall_call_state_da_info  *call_da_val = NULL;
  
  call_da_val = dsat_get_base_addr_per_subs(DSAT_CALL_DA_VALS, subs_id, TRUE);
  
  if(call_event == NULL ||
     call_da_val == NULL ||
     (DSAT_CMCCS_VAL_ENABLED_BASIC != cmccs_val && 
      DSAT_CMCCS_VAL_ENABLED_BASIC_SUPS != cmccs_val))
  {
    return;
  }
  /* Sequence number */
  ccidx = dsatact_callid_to_seqnum(subs_id, call_event->event_info.call_id);

  /* Get sdp_md based on call type */
  if(call_event->event_info.call_type == CM_CALL_TYPE_VT)
  {
    sdp_md = (dsat_string_item_type*)sdp_md2;
  }
  else if(call_event->event_info.call_type == CM_CALL_TYPE_VOICE)
  {
    sdp_md = (dsat_string_item_type*)sdp_md1;
  }

  /* Get call status based on voice state and other parameters */
  ccstatus = dsatetsicmif_cmccs_get_ccstatus(voice_state[subs_id][call_event->event_info.call_id].state,
                                             call_da_val->etsicall_was_waiting);
  /* Set ccstatus, neg_status, neg_status_present based on different CM Events */
  switch(call_event->event)
  {
    case CM_CALL_EVENT_ORIG:
      /* If AT+CHLD=3 is given VoLTE call, new call will be originated */
      if(call_event->event_info.dsat_mode_info.info_type == CM_CALL_MODE_INFO_IP &&
         ((etsicall_cmd_pending[subs_id] & (CMD_CHLD3 | CMD_CONF)) == (CMD_CHLD3 | CMD_CONF)))
      {
        ccstatus = DSAT_CMCCS_CALLING;
      }
      else
      {
        ccstatus = (call_da_val->etsicall_was_call_active) ?
                    DSAT_CMCCS_CALL_WAITING_MO:DSAT_CMCCS_CALLING;
      }
      break;
    case CM_CALL_EVENT_ANSWER:
    case CM_CALL_EVENT_PROGRESS_INFO_IND:
      ccstatus = DSAT_CMCCS_CONNECTING;
      break;
    case CM_CALL_EVENT_INCOM:
      ccstatus = (call_da_val->etsicall_was_waiting) ?
                  DSAT_CMCCS_CALL_WAITING_MT : DSAT_CMCCS_ALERTING_MT;
      neg_status_present = TRUE;
      neg_status = DSAT_NEG_STATUS_PROPOSED;
      break;
    case CM_CALL_EVENT_ABRV_ALERT:
      ccstatus = DSAT_CMCCS_ALERTING_MO;
      break;
    case CM_CALL_EVENT_CONNECT:
    case CM_CALL_EVENT_CALL_RETRIEVED:
      ccstatus = DSAT_CMCCS_ACTIVE;
      break;
    case CM_CALL_EVENT_END:	  
      ccstatus = (call_event->event_info.call_direction == CM_CALL_DIRECTION_MO) ?
                   DSAT_CMCCS_RELEASED_MO : DSAT_CMCCS_RELEASED_MT;
      ccidx = call_da_val->last_seq_num + 1;
      break;
    case CM_CALL_EVENT_CALL_ON_HOLD:
      ccstatus = (call_event->event_info.call_direction == CM_CALL_DIRECTION_MO) ?
                   DSAT_CMCCS_CALL_HOLD_MO : DSAT_CMCCS_CALL_HOLD_MT;
      break;
    case CM_CALL_EVENT_MODIFY_REQ:
      neg_status_present = TRUE;
      neg_status = DSAT_NEG_STATUS_DESIRED;
      break;
    case CM_CALL_EVENT_MODIFY_COMPLETE_CONF:
      neg_status_present = TRUE;
      neg_status =(CM_CALL_END_UPGRADE_DOWNGRADE_REJ ==
                    call_event->event_info.dsat_mode_info.info.ip_call.modify_error_code) ?
                    DSAT_NEG_STATUS_REJECT : DSAT_NEG_STATUS_ACCEPT;
      break;
    case CM_CALL_EVENT_MODIFY_IND:
      neg_status_present = TRUE;
      neg_status = DSAT_NEG_STATUS_PROPOSED;
      break;
    case CM_CALL_EVENT_MODIFY_RES:
      neg_status_present = TRUE;
      neg_status =(call_da_val->call_modify_param.modify_response) ? 
                    DSAT_NEG_STATUS_ACCEPT : DSAT_NEG_STATUS_REJECT;
     break;
    default:
      /* Don't handle for other CM Events */
      return;
  }

  res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, FALSE);
  /* Initialize result buffer */
  res_buff_ptr->data_ptr[0] = '\0';

  /* Generate response */
  /* +CMCCSI: <ccidx>,<dir>,<neg_status_present>,<neg_status>,<SDP_md>,<cs_mode>,
               <ccstatus>,<mpty>,<numbertype>,<ton>,<number>,<exittype>,<exitcause>	*/
  res_buff_ptr->used = (word) snprintf ((char*)res_buff_ptr->data_ptr,
                                       res_buff_ptr->size,
                                       "+CMCCSI: %d,%d,%d,%d,\"",
                                       ccidx, call_event->event_info.call_direction,
                                       neg_status_present, neg_status);
  /* <SDP_md> */
  if(sdp_md != NULL)
  {
    res_buff_ptr->used += (word)snprintf(
                        (char*)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                        res_buff_ptr->size - res_buff_ptr->used, "%s",
                        sdp_md);
  }

  if(call_event->event_info.num.len > 0)
  {
    /* Currently we are not supporting 1 i.e. URI format */
    numbertype = DSAT_CMCCSI_NUMBERTYPE_GENERIC_FORMAT;
  }
  /* <cs_mode>, <ccstatus>,<mpty>,<numbertype>,<ton> */
  res_buff_ptr->used += (word)snprintf(
                        (char*)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                        res_buff_ptr->size - res_buff_ptr->used, "\",0,%d,%d,%d,%d,\"",
                        ccstatus,
                        call_da_val->dsat_seqnum_callid[call_event->event_info.call_id].is_conf_participant,
                        numbertype, call_event->event_info.num.number_type);
  

  /* <number>; call_info_ptr->num.buf is not null terminated */
  (void) dsatutil_memscpy((void*)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                                  DSAT_BUF_SIZE(res_buff_ptr->size,res_buff_ptr->used),
                           (void*)call_event->event_info.num.buf, call_event->event_info.num.len);

  res_buff_ptr->used += call_event->event_info.num.len;
  /* Exittype and exitcause */
  res_buff_ptr->used += (word)snprintf(
                        (char*)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                        res_buff_ptr->size - res_buff_ptr->used, "\",0,0");

  /* Send response to TE */
  dsatcmdp_send_urc_per_subs(subs_id, res_buff_ptr, DSAT_COMPLETE_RSP);
  
}  /* dsatetsicmif_report_cmccs */


/*===========================================================================

FUNCTION  DSATETSICMIF_REPORT_CMCCS_CONF

DESCRIPTION
  This function reports the call status for conference call

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
/* ARGSUSED */
void dsatetsicmif_report_cmccs_conf
(
  sys_modem_as_id_e_type            subs_id,
  dsat_conference_participant_info *conf_participant_info
)
{
  dsm_item_type                    *res_buff_ptr = NULL;
  dsat_num_item_type                cmccs_val    = (dsat_num_item_type)dsatutil_get_val(
  	                                            DSATETSI_EXT_ACT_CMCCS_ETSI_IDX,0,0,NUM_TYPE);
  uint8 ccstatus;
  uint8 j;
  
  if(conf_participant_info == NULL ||
     (DSAT_CMCCS_VAL_ENABLED_BASIC != cmccs_val && 
      DSAT_CMCCS_VAL_ENABLED_BASIC_SUPS != cmccs_val))
  {
    return;
  }

  /* Get call status based on voice state and other parameters */
  if(conf_participant_info->status == MMODE_QMI_CALL_STATUS_ON_HOLD)
  {
    /* As direction is not available to ATCoP, this hold can be MO or MT */
    ccstatus = DSAT_CMCCS_CALL_HOLD_MO;
  }
  else if(conf_participant_info->status == MMODE_QMI_CALL_STATUS_DISCONNECTED)
  {
    /* As direction is not available to ATCoP, this release can be MO or MT */
    ccstatus = DSAT_CMCCS_RELEASED_MO;
  }
  else if(conf_participant_info->status == MMODE_QMI_CALL_STATUS_CONNECTED)
  {
    ccstatus = DSAT_CMCCS_ACTIVE;
  }
  else
  {
    /* No need to report these */
    return;
  }
  
  /* Allocate buffer for response */
  res_buff_ptr = dsat_dsm_new_buffer(DSM_DS_LARGE_ITEM_POOL, FALSE);
  /* Initialize result buffer */
  res_buff_ptr->data_ptr[0] = '\0';

  /* Generate response */
  /* +CMCCSI: <ccidx>,<dir>,<neg_status_present>,<neg_status>,<SDP_md>,<cs_mode>,
               <ccstatus>,<mpty>,<numbertype>,<ton>,<number>,<exittype>,<exitcause>	*/
  /* <ccidx>,<dir>,<neg_status_present>,<neg_status> <cs_mode>, <ccstatus>,<mpty>,<numbertype>,<ton> */
  res_buff_ptr->used = (word) snprintf ((char*)res_buff_ptr->data_ptr,
                                       res_buff_ptr->size,
                                       "+CMCCSI: %d,,0,0,\"\",0,%d,1,%d,0,\"",
                                       conf_participant_info->seq_number,
                                       ccstatus,
                                       DSAT_CMCCSI_NUMBERTYPE_URI_FORMAT);

  /* <number> */
  for(j = 0; j < conf_participant_info->user_uri_len; j++)
  {
    res_buff_ptr->data_ptr[res_buff_ptr->used + j] = (uint8)conf_participant_info->user_uri[j];
  }

  res_buff_ptr->used += conf_participant_info->user_uri_len;
  
  /* Exittype and exitcause */
  res_buff_ptr->used += (word)snprintf(
                        (char*)&res_buff_ptr->data_ptr[res_buff_ptr->used],
                        res_buff_ptr->size - res_buff_ptr->used, "\",0,0");

  /* Send response to TE */
  dsatcmdp_send_urc_per_subs(subs_id, res_buff_ptr, DSAT_COMPLETE_RSP);
  
}  /* dsatetsicmif_report_cmccs_conf */

#endif /* FEATURE_DSAT_ETSI_MODE */


