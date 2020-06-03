#ifndef DSATASKEYTAB_H
#define DSATASKEYTAB_H
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                A S K EY P R O P R I E T A RY

                A T   C O M M A N D   
                
                T A B L E

GENERAL DESCRIPTION
   This module executes the AT commands. It mainly executes the ASKEY common commands.

EXTERNALIZED FUNCTIONS

EXTERNALIZED FUNCTIONS INTERNAL TO DSAT UNIT
  dsat_askey_lab_test_cfg_cmd

INITIALIZATION AND SEQUENCING REQUIREMENTS

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/


/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/30/18   philip  Created file. ASKEY_PROPRIETARY_ATCMD

===========================================================================*/

/*--------------------------------------------------------------------------
                    Common Command Tables and Table Sizes 
--------------------------------------------------------------------------*/

extern const dsati_cmd_type dsat_askey_ext_table[ ];
extern const dsati_cmd_type dsat_askey_vendor_table[ ];

extern const unsigned int dsat_askey_ext_table_size;
extern const unsigned int dsat_askey_vendor_table_size;




typedef enum
{

  DSAT_ASKEY_ACT_START_IDX               = 50000
  ,DSAT_ASKEY_ACT_LAB_TEST_CFG_IDX        = DSAT_ASKEY_ACT_START_IDX

  // philip, 20180810, [Generic][TMO] Set preferred band
#ifdef ASKEY_SET_PREFERRED_BAND
  ,DSAT_ASKEY_ACT_SET_PERFERRED_BAND_IDX
#endif

  // jelly, 20180830, [Generic][TMO] Set PCI lock
#ifdef ASKEY_PCI_LOCK
  ,DSAT_ASKEY_ACT_SET_PCI_LOCK_IDX
#endif
#ifdef ASKEY_AT_TEST
  ,DSAT_ASKEY_ACT_TEST_IDX
#endif
#ifdef ASKEY_PREF_NET
  ,DSAT_ASKEY_ACT_PREFNET_IDX
#endif
  ,DSAT_ASKEY_ACT_MAKE_CALL_IDX
  ,DSAT_ASKEY_ACT_FWD_TEST_IDX
}dsataskey_ext_index_enum_type;

// philip, 20190313, Add askey extended and vendor types of AT cmd table
#if defined(ASKEY_PROPRIETARY_ATCMD) || defined(ASKEY_EXT_VENDOR_ATCMD)

typedef enum
{
  DSAT_ASKEY_EXT_TEST_IDX  = DSAT_ASKEY_ACT_START_IDX + 100

}dsat_askey_ext_index_enum_type;

typedef enum
{
  DSAT_ASKEY_VENDOR_TEST_IDX  = DSAT_ASKEY_ACT_START_IDX + 200
  ,DSAT_ASKEY_VENDOR_DISABLECA_IDX

}dsat_askey_vendor_index_enum_type;


#endif /* ASKEY_PROPRIETARY_ATCMD || ASKEY_EXT_VENDOR_ATCMD */


#endif /* DSATASKEYTAB_H */
