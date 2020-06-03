/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

               C O M M O N   C O M M A N D   T A B L E S

GENERAL DESCRIPTION
  This module contains the command tables and data definitions required
  to define the ASKEY proprietary AT modem commands..

EXTERNALIZED FUNCTIONS

    
INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
07/30/18   philip  Created file. ASKEY_PROPRIETARY_ATCMD


===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/

#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"


#include "target.h"
#include "dsati.h"
#include "msg.h"
#include "dsatparm.h"
#include "dsatact.h"
#include "dsatctab.h"
#include "dsatme.h"
#include "dsatvend.h"
#include "dstaski.h"
#include "nv.h"

#ifdef FEATURE_DSAT_ETSI_DATA
#include "dsatetsipkt.h"
#endif /* FEATURE_DSAT_ETSI_DATA */

#ifdef FEATURE_DSAT_ETSI_MODE
#include "dsatetsictab.h"
#ifdef FEATURE_DSAT_DEV_CMDS
#include "dsatetsicall.h"
#endif /* FEATURE_DSAT_DEV_CMDS */
#include "dsatme.h"
#include "dsatcmif.h"
#ifdef FEATURE_ETSI_SMS
#include "dsatetsisms.h"
#endif /* FEATURE_ETSI_SMS */
#ifdef FEATURE_DATA_ETSI_PIN
#include "dsatetsime.h"
#endif /* FEATURE_DATA_ETSI_PIN */
#endif /* FEATURE_DSAT_ETSI_MODE */
#include "ds_rmnet_defs.h"

#include "dsataskeyat.h"
#include "dsataskeytab.h"

#ifndef ARR_SIZE
#define ARR_SIZE(a) ( sizeof(a) / sizeof(a[0]) )
#endif

/*===========================================================================

                    REGIONAL DEFINITIONS AND DECLARATIONS

===========================================================================*/

/*---------------------------------------------------------------------------
  NV interface data 
---------------------------------------------------------------------------*/
nv_item_type         ds_nv_item;                  /* actual data item     */

/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

  This section contains local definitions for constants, macros, types,
  variables and other items needed by this module.

===========================================================================*/


/*--------------------------------------------------------------------------
                          Common Command Tables 
--------------------------------------------------------------------------*/

/* Basic common AT command table. */
const dsati_cmd_type dsat_askey_basic_at_table [] =
{
  { "@ASKEY_LAB_TEST_CFG",
      RESTRICTED | COMMON_CMD,
      SPECIAL_NONE,
      0,
      DSAT_ASKEY_ACT_LAB_TEST_CFG_IDX,
      NULL},

// philip, 20180810, [Generic][TMO] Set preferred band
#ifdef ASKEY_SET_PREFERRED_BAND
	{ "@ASKEY_PREFBAND",
		RESTRICTED | COMMON_CMD,
		SPECIAL_NONE,
		0,
		DSAT_ASKEY_ACT_SET_PERFERRED_BAND_IDX,
		NULL},
#endif /* ASKEY_SET_PREFERRED_BAND */

#ifdef ASKEY_PCI_LOCK
  { "@ASKEY_PCILOCK",
      RESTRICTED | COMMON_CMD,
      SPECIAL_NONE,
      0,
      DSAT_ASKEY_ACT_SET_PCI_LOCK_IDX,
      NULL},
#endif

#ifdef ASKEY_AT_TEST
  { "@ASKEY_TEST",
      RESTRICTED | COMMON_CMD,
      SPECIAL_NONE,
      0,
      DSAT_ASKEY_ACT_TEST_IDX,
      NULL},
#endif 

#ifdef ASKEY_PREF_NET
  { "@ASKEY_PREFNET",
	  RESTRICTED | COMMON_CMD,
	  SPECIAL_NONE,
	  0,
	  DSAT_ASKEY_ACT_PREFNET_IDX,
	  NULL},
#endif 

  { "@ASKEY_MAKE_CALL",
      RESTRICTED | COMMON_CMD | AT_FWD_CMDS,
      SPECIAL_NONE,
      0,
      DSAT_ASKEY_ACT_MAKE_CALL_IDX,
      NULL},
  { "@ASKEY_FWD_TEST",
      RESTRICTED | COMMON_CMD | AT_FWD_CMDS,
      SPECIAL_NONE,
      0,
      DSAT_ASKEY_ACT_FWD_TEST_IDX,
      NULL}

} ;

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)

/* For '+' beginningg of AT command */
const dsati_cmd_type dsat_askey_ext_table [] =
{
	{ "+ASKEY_TEST_EXT",
	  RESTRICTED | EXTENDED | COMMON_CMD,
	  SPECIAL_NONE,
	  0,
	  DSAT_ASKEY_EXT_TEST_IDX,
	  NULL }

};

/* For '$' beginningg of AT command */
const dsati_cmd_type dsat_askey_vendor_table [] =
{
	{ "$ASKEY_TEST_VENDOR",
	  RESTRICTED | EXTENDED | COMMON_CMD,
	  SPECIAL_NONE, 
	  0,
	  DSAT_ASKEY_VENDOR_TEST_IDX,
	  NULL }, 
	  
	{ "$DISABLECA",
	  RESTRICTED | EXTENDED | COMMON_CMD,
	  SPECIAL_NONE, 
	  0,
	  DSAT_ASKEY_VENDOR_DISABLECA_IDX,
	  NULL }

};
#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */

/* Command table sizes. */
const unsigned int dsat_askey_basic_at_table_size = ARR_SIZE( dsat_askey_basic_at_table );

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)
const unsigned int dsat_askey_ext_table_size = ARR_SIZE( dsat_askey_ext_table );
const unsigned int dsat_askey_vendor_table_size = ARR_SIZE( dsat_askey_vendor_table );
#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */

/* Basic common action command table. */
const dsati_cmd_ex_type dsat_askey_basic_at_table_ex [] =
{ 
  { DSAT_ASKEY_ACT_LAB_TEST_CFG_IDX,       dsataskey_exec_lab_test_cfg_cmd }

// philip, 20180810, [Generic][TMO] Set preferred band
#ifdef ASKEY_SET_PREFERRED_BAND
  ,{ DSAT_ASKEY_ACT_SET_PERFERRED_BAND_IDX,       dsataskey_exec_prefband_cmd }
#endif /* ASKEY_SET_PREFERRED_BAND */

#ifdef ASKEY_PCI_LOCK
  ,{ DSAT_ASKEY_ACT_SET_PCI_LOCK_IDX,       dsataskey_exec_pcilock_cmd }
#endif /* ASKEY_PCI_LOCK */

#ifdef ASKEY_AT_TEST
  ,{ DSAT_ASKEY_ACT_TEST_IDX,       dsataskey_exec_test_cmd }
#endif /* ASKEY_AT_TEST */

#ifdef ASKEY_PREF_NET
  ,{ DSAT_ASKEY_ACT_PREFNET_IDX,	   dsataskey_exec_prefnet_cmd }
#endif /* ASKEY_PREF_NET */

  ,{ DSAT_ASKEY_ACT_MAKE_CALL_IDX,	   dsataskey_exec_makecall_cmd }
  ,{ DSAT_ASKEY_ACT_FWD_TEST_IDX,       dsataskey_exec_fwd_test_cmd }
  
};

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)

// + command table
const dsati_cmd_ex_type dsat_askey_ext_table_ex [] =
{ 
  { DSAT_ASKEY_EXT_TEST_IDX,   dsataskey_exec_test_ext_cmd }

};

// $ command table
const dsati_cmd_ex_type dsat_askey_vendor_table_ex [] =
{ 
  { DSAT_ASKEY_VENDOR_TEST_IDX,	 dsataskey_exec_test_vendor_cmd }
  ,{ DSAT_ASKEY_VENDOR_DISABLECA_IDX, dsataskey_exec_disableca_vendor_cmd }

};

#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */


