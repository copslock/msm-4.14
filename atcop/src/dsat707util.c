/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        D A T A   S E R V I C E S
                A T   C O M M A N D   P R O C E S S O R

               I S - 7 0 7   C O M M A N D   T A B L E S

GENERAL DESCRIPTION
  This module contains generic function definitions used by the IS707
  AT command processor.
  
EXTERNALIZED FUNCTIONS
  None
    
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

  $PVCSPath: L:/src/asw/MM_DATA/vcs/dsat707util.c_v   1.11   18 Feb 2003 10:39:58   sramacha  $
  $Header: //commercial/MPSS.HI.1.0.c8/Main/modem_proc/datamodem_r/interface/atcop/src/dsat707util.c#1 $ $DateTime: 2019/10/12 17:41:50 $ $Author: mplcsds1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/27/14   tk      Added support for Dynamic ATCoP.
03/11/14   tk      Optimized debug macros usage in ATCoP.
05/18/12   tk      Migrated to MSG 2.0 macros
03/13/12   dvk     Merged enabling mdr val update always during powerup.
01/19/12   sk      Feature cleanup.
07/22/11   dvk     Global Variable Cleanup
03/30/11   ms      Global variable cleanup.
03/15/11   mg      Global variable cleanup.
01/11/11   ad      Fixed security vulnerabilities in 1X.
01/11/11   ad      Remove extern usage.used get/set API for command associated  
                   value pointers.
05/10/10   kk      Added functions to read and parse MIN and IMSI NV items.
09/09/09   bs      Fixed Klocwork criticals.
07/01/09   vg      Replacing deprecated MSG_XXX macro with MSG_SPRINTFX_ macro.
06/15/09   vg	   Fixed Lint medium.
03/03/09   ms      Update the HAT timer value with the value read from 
                   NV or RUIM card entry.
03/04/09   sa      AU level CMI modifications.
12/12/08   ua      Fixed Off target lint errors.
09/02/08   mga     Removed return in some cases in dsat707_nv_sync() and changed
                   accordingly. Changed ERR_FATAL to MSG_ERROR in some cases.
08/11/08   bs      Fixed Klocwork criticals.
06/24/08   mga     Made changes to support CTA timer NV item
06/18/08   nc      Fixed the memory leak caused by item_ptr in 
                   dsat707_unrec_func_ptr().
06/10/08   mga     Made changes to support CTA timer NV item
04/29/08   mga     Added return in some cases after error checking
04/09/08   bs      Fixed Klocwork errors.
01/15/08   mga     Merged changes to change ERR_FATAL to MSG_ERROR
10/26/07   ua      Correcting sending of unrecognized commands to IWF only 
                   when +CXT value is set to 1. 
05/10/07   ac      Lint fix
04/11/07   ua      Modifications as per KDDI requirements. 
10/30/06   spn     Changed Featurization from DS_AT_TEST_ONLY to 
                   HDR_AT_TEST_ONLY
04/05/05   gr      Integrated EPZID functionality onto the main line
08/11/04   jd      Fix buffer overrun check in dsat707_strip_quotes
06/29/04   sy      Added bound check for the pzid hysteresis NV items.
05/16/04   vr      Moved uint32_to_str and str_to_uint32 from dsat707mip.c
                   Added mcast_str_to_uint32()
04/08/04   gr      Added support for force cdma dial str nv item
09/17/03   sy      Added support for nv items for pzid hysteresis under
                   FEATURE_DS_EPZID_HYSTERESIS.
01/28/03   rsl     Don't append 'T' to dial string because of ATCOP changes.
01/20/03   ar      Added dialstr_modifiers to ds707_async_dial_str_cb 
                   interface.
10/15/02   ak      Updated FEATURE_JCDMA_DS to FEATURE_JCDMA_DS_1X
09/30/02   ar      Accomodate changed interface to proc_dial_string
07/13/02   atp     Changed signature of dsat707_send_config() to make param
                   passed in a ptr to const byte.
07/13/02   atp     In dsat707_send_config() functions, calls 
                   ds707_async_ps_tcp_enqueue() to queue data.
4/3/01     rsl     Initial release.

===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include "datamodem_variation.h"
#include "comdef.h"
#include "customer.h"

#ifdef FEATURE_DATA_IS707
#include "amssassert.h"
#include "dsati.h"
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

/*-------------------------------------------------------------------------
    Definition of strings used for verbose result codes:

    Assignment to the pointer arrays "xxx_codes" must match
    the definition of "ds_atcop_result_enum_type" in dsatcop.h
-------------------------------------------------------------------------*/
const byte res_code_string_ok []        = "OK";         /*  0  */
const byte res_code_string_con []       = "CONNECT";    /*  1  */
const byte res_code_string_ring []      = "RING";       /*  2  */
const byte res_code_string_no_car []    = "NO CARRIER"; /*  3  */
const byte res_code_string_error []     = "ERROR";      /*  4  */
const byte res_code_string_nu []        = "(not used)"; /*  5  */
const byte res_code_string_no_dial []   = "NO DIALTONE";/*  6  */
const byte res_code_string_busy []      = "BUSY";       /*  7  */
const byte res_code_string_no_ans []    = "NO ANSWER";  /*  8  */
const byte res_code_string_delayed []   = "DELAYED";    /*  9  */

const byte res_code_string_rng_amps  [] = "RING AMPS";  /* 10  */
const byte res_code_string_rng_async [] = "RING ASYNC"; /* 11  */
const byte res_code_string_rng_fax []   = "RING FAX";   /* 12  */
const byte res_code_string_rng_pkt   [] = "RING PACKET";/* 13  */

/*20*/
const byte res_code_string_no_amps[]    = "NO AMPS SERVICE";
/*21*/
const byte res_code_string_no_srv []    = "NO SERVICE";
/*22 */
const byte res_code_string_no_async []  = "NO ASYNC SERVICE";
/*23*/
const byte res_code_string_no_fax []    = "NO FAX SERVICE";
/*24*/
const byte res_code_string_no_pkt []    = "NO PACKET SERVICE";
/*25*/
const byte res_code_string_no_intr[]    = "BAD REQUEST";
/*26*/
const byte res_code_string_paged []     = "PAGED";
const byte res_code_string_reoder []    = "RETRY";      /* 27 */
const byte res_code_string_page_fail [] = "PAGE FAIL";  /* 28 */
const byte res_code_string_link_fail [] = "LINK FAIL";  /* 29 */

const byte res_code_string_released []  = "RELEASE";    /* 30 */

/*  Stand alone */
const byte res_code_string_cerror []    = "+CERROR: ";

const byte *const res_codes [] =
      { res_code_string_ok,
        res_code_string_con,
        res_code_string_ring,
        res_code_string_no_car,
        res_code_string_error,
        res_code_string_nu,
        res_code_string_no_dial,
        res_code_string_busy,
        res_code_string_no_ans,
        res_code_string_delayed
      };

const byte *const cell_res_codes [] =
      { res_code_string_rng_amps,
        res_code_string_rng_async,
        res_code_string_rng_fax,
        res_code_string_rng_pkt
      };

const byte *const cell_error_res_codes [] =
      { res_code_string_no_amps,
        res_code_string_no_srv,
        res_code_string_no_async,
        res_code_string_no_fax,
        res_code_string_no_pkt,
        res_code_string_no_intr,
        res_code_string_paged,
        res_code_string_reoder,
        res_code_string_page_fail,
        res_code_string_link_fail,
        res_code_string_released
      };

boolean unrec_cmd_rcvd = FALSE;

/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

  This section contains local definitions for constants, macros, types,
  variables and other items needed by this module.

===========================================================================*/
#define DSAT707_IS_ASSERT(expression) \
         dsat707_is_assert_wrapper(__LINE__, expression)
		 
		 
/*===========================================================================

FUNCTION DSAT707_IS_ASSERT_WRAPPER()

DESCRIPTION
  Wrapper function for DSAT707_IS ASSERT
 
DEPENDENCIES 
  None

RETURN VALUE
  None
 
SIDE EFFECTS

===========================================================================*/
static void dsat707_is_assert_wrapper
(
  unsigned int     line_num,
  int              expression
)
{
  if ( !expression )
  {
    ERR_FATAL("DSAT707_IS_FATAL at line:%d ",  
                                   line_num,0,0);  
  }
}/* dsat707_is_assert_wrapper */

/*===========================================================================

FUNCTION DSAT707_IS_STATUS

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

boolean dsat707_is_status
(
  byte *a_ptr,
  dsat_result_enum_type result
)
{
  byte c;
  const byte *c_ptr;

  DSAT707_IS_ASSERT(((a_ptr != NULL) == TRUE) );
  
  if (*a_ptr == '0' + (byte) result)
  {
    return TRUE;
  }

  if((result >= DSAT_MAX_BASIC)||(result < DSAT_OK))
  {
    /* Applicable till 9 only! */
    return FALSE;
  }

  c_ptr = res_codes [result];

  while ( (c = *c_ptr++) != '\0')
  {
    if (c != *a_ptr++)
    {
      return FALSE;
    }
  }
  return TRUE;
} /* dsat707_is_status */


/*===========================================================================
  FUNCTION DSAT707_IP_STR_TO_UINT32

  DESCRIPTION
    This function takes an IP address in string format (which includes
    "." as delimiters. e.g. 123.23.123.231) and convert the string into
    a uint32 value.

  DEPENDENCIES
    None

  RETURN VALUE
    status ( success or error)

  SIDE EFFECTS
    None
===========================================================================*/
boolean dsat707_ip_str_to_uint32
(
  char   *ip_string,
  uint32 *ip_uint32
)
{
  byte                   buff[4];
  dsat_num_item_type     ip_val[4];
  uint8 buff_index     = 0;
  uint8 ip_index       = 0;
  uint8 n_dots         = 0;
  boolean loop         = TRUE;
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  ip_val[0] = ip_val[1] = ip_val[2] = ip_val[3] = 0;
  /*-------------------------------------------------------------------------
    The following loop processes the string representing the IP address. Each
    one of the four-tuples is converted into decimal integer and stored in a
    temporary array. If the value is greater than 255, we return an error,
    because each tuple in the IP cannot be greater than 255.
  -------------------------------------------------------------------------*/
  while(loop != FALSE)
  {
    if( (*ip_string != '.') &&
        (*ip_string != '\0') )
    {
      /* check to see if > 3 digits specified on for this tuple */
      if(buff_index >= 3)
      {
       DS_ATCOP_ERROR_LOG_0("Too many digits");
        return FALSE;
      }
      buff[buff_index] = (byte) *ip_string;
      buff_index++;
    }
    else
    {
      n_dots++;
      buff[buff_index]= '\0';  /* null terminate the string */

      /* check to see if > 3 digits */
      if(ip_index >= 4)
      {
       DS_ATCOP_ERROR_LOG_0("Too many digits");
        return FALSE;
      }
      
      /*---------------------------------------------------------------------
        Convert ascii to integer and return error if an invalid ip address
        is entered. eg A.12.14.45
      ---------------------------------------------------------------------*/
      if( ATOI_OK != dsatutil_atoi( (ip_val + ip_index),buff,10 ) )
      {
       DS_ATCOP_ERROR_LOG_0("Error while converting from atoi");
        return FALSE;
      }
      else if(ip_val[ip_index] > 255)
      {
       DS_ATCOP_ERROR_LOG_0("IP address tuple greater than 255");
        return FALSE;
      }
      buff_index = 0;
      ip_index++;
      if(*ip_string == '\0')
      {
        loop=FALSE;

        /*-------------------------------------------------------------------
          If the ip address has more than 3 dots it is an invalid 
          ip address eg: 129.23.34  , 129.34.45.65.78 etc.
        -------------------------------------------------------------------*/
        if(n_dots != 4)
        {
         DS_ATCOP_ERROR_LOG_0("Invalid IP address");
          return FALSE;
        }
      }
    }/* else */
    ip_string++;
  } /* while */

  /*-------------------------------------------------------------------------
    Store the converted IP address into a uint32
  --------------------------------------------------------------------------*/
  *ip_uint32 = (((uint32) ip_val[0]) << 24) |
               (((uint32) ip_val[1]) << 16) |
               (((uint32) ip_val[2]) << 8)  |
               (uint32) ip_val[3];

  DS_AT_MSG1_LOW("ip_uint32 is %ld", *ip_uint32);
  return TRUE;
} /* dsat707_ip_str_to_uint32 () */

/*===========================================================================
FUNCTION DSAT707_MCAST_IP_STR_TO_UINT32

DESCRIPTION
  This function takes an IP address in string format (which includes
  "." as delimiters. e.g. 123.23.123.231) and convert the string into
  a uint32 value. It checks to make sure that the IP address is in the
  multicast range or is 0.0.0.0

  The string may have more information than the IP address and this 
  function will stop processing once it has found or failed to find a valid
  IP address. The number of bytes processed by the function is returned in
  len_curr_ip.

DEPENDENCIES
  None

RETURN VALUE
  OK if the IP address is a valid multicast IPv4 address or 0.0.0.0,
  ERROR otherwise. The number of bytes processed is returned in 
  len_curr_ip independent of success or failure.

SIDE EFFECTS
  None
===========================================================================*/
boolean dsat707_mcast_ip_str_to_uint32
(
  char   *ip_string,
  uint32 *ip_uint32,
  uint32 *len_curr_ip
)
{
  byte                   buff[4];
  dsat_num_item_type     ip_val[4];
  atoi_enum_type         atoi_result;
  uint8 buff_index     = 0;
  uint8 ip_index       = 0;
  uint8 n_dots         = 0;
  boolean loop         = TRUE;
  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /*lint -save -e572 suppressing error 572*/
  ip_val[0] = ip_val[1] = ip_val[2] = ip_val[3] = 0;
  /*-------------------------------------------------------------------------
    The following loop processes the string representing the IP address. Each
    one of the four-tuples is converted into decimal integer and stored in a
    temporary array. If the value is greater than 255, we return an error,
    because each tuple in the IP cannot be greater than 255.
  -------------------------------------------------------------------------*/
  if(len_curr_ip != NULL)
  {
    (*len_curr_ip) = 0;
  }

  while(loop != FALSE)
  {
    if( (*ip_string != '.') &&
        (*ip_string != '\0') &&
        (*ip_string != ' ' ))
    {
      /* check to see if > 3 digits specified on for this tuple */
      if(buff_index >= 3)
      {
       DS_ATCOP_ERROR_LOG_0("Too many digits");
        return FALSE;
      }
      buff[buff_index] = *ip_string;
      buff_index++;
    }
    else
    {
      n_dots++;
      buff[buff_index]= '\0';  /* null terminate the string */

      /* check to see if > 3 digits */
      if(ip_index >= 4)
      {
       DS_ATCOP_ERROR_LOG_0("Too many digits");
        return FALSE;
      }

      /*---------------------------------------------------------------------
        Convert ascii to integer and return error if an invalid ip address
        is entered. eg A.12.14.45
      ---------------------------------------------------------------------*/
      atoi_result = dsatutil_atoi( (ip_val + ip_index),buff,10 );
      if(atoi_result != ATOI_OK)
      {
       DS_ATCOP_ERROR_LOG_0("Error while converting from atoi");
        return FALSE;
      }
      else if(ip_val[ip_index] > 255)
      {
       DS_ATCOP_ERROR_LOG_0("IP address tuple greater than 255");
        return FALSE;
      }
      buff_index = 0;
      ip_index++;
      if(*ip_string == '\0' || *ip_string == ' ')
      {
        loop=FALSE;

        /*-------------------------------------------------------------------
        If the ip address has more than 3 dots it is an invalid 
        ip address eg: 129.23.34  , 129.34.45.65.78 etc.
        -------------------------------------------------------------------*/
        if(n_dots != 4)
        {
       DS_ATCOP_ERROR_LOG_0("Invalid IP address");
        return FALSE;
        }
      }
    }/* else */
    ip_string++;
    if(len_curr_ip != NULL)
    {
      (*len_curr_ip) += 1;
    }
  } /* while */

  /*-------------------------------------------------------------------------
    Store the converted IP address into a uint32
  --------------------------------------------------------------------------*/
  *ip_uint32 = (((uint32) ip_val[0]) << 24) |
         (((uint32) ip_val[1]) << 16) |
         (((uint32) ip_val[2]) << 8)  |
         (uint32) ip_val[3];

  /*-------------------------------------------------------------------------
    Validate the IP address for multicast range or 0.0.0.0
  --------------------------------------------------------------------------*/
  if(!PS_IN_IS_ADDR_MULTICAST((dss_htonl(*ip_uint32))) && (*ip_uint32 != 0))
  {
   DS_ATCOP_ERROR_LOG_0("IP not in mcast range");
    return FALSE;
  }

  DS_AT_MSG1_LOW("ip_uint32 is %ld", *ip_uint32);
  return TRUE;
  /*lint -restore Restore lint error 572*/
} /* dsat707_mcast_ip_str_to_uint32 */


/*===========================================================================
FUNCTION DSAT707_STRIP_QUOTES

DESCRIPTION
  This fuction 
  - takes an input quoted string,
  - puts a copy of the string in "parsed_string" with the quotes stripped off
  - NULL-terminates the parsed_string by placing \0 at the end.
  - Validates that the output string length falls within the range specified
    in the ? 
returning  an ERROR if out 
  The function also checks for the range of the AT command and throws out an
  error if the range is exceeded.

  For examples,
    "123.12.23.21"           ---> 123.12.23.21\0
    "nobody,one@nowhere.com" ---> nobody,one@nowhere.com\0

DEPENDENCIES
  None

PARAMETERS
   raw_string - Returned by the standard ATCoP parser, ds_atcop_parse_ex().
   parsed_string - Buffer where the parsed argument shall be returned.
   table_entry  -  To find out the size of the argument defined in the table.

RETURN VALUE
  FALSE  if - null input or output string pointers are provided
            - output string length is out of range

  TRUE   if conversion goes well

SIDE EFFECTS
  None
===========================================================================*/
#define STRIP_QUOTES_MAX_LEN  (128)

boolean dsat707_strip_quotes
(
  char *  in_s,                   /* input string (to be stripped)         */
  char *  parsed_s,               /* null-term output string placed here   */
  uint16  max_parsed_len          /* size of provided output buffer        */
)
{
  char     temp_s[STRIP_QUOTES_MAX_LEN];     /* temporary output storage   */
  char *   out_s;                 /* working pointer for stripped output   */
  char *   max_out_s;             /* limit for output pointer              */
  boolean  escape;                /* state flag - escape next character    */
  boolean  quote;                 /* state flag - currently in quotes      */
  boolean  copy;                  /* state flag - copy current character   */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /*-------------------------------------------------------------------------
    Make sure there are no NULL de-reference and that at least one 
    character (+ null terminator) can be placed in output buffer.
  -------------------------------------------------------------------------*/
  if( parsed_s == NULL || max_parsed_len < 2 )
  {
   DS_ATCOP_ERROR_LOG_0("No output buffer provided!");
    return FALSE;
  }

  /*-------------------------------------------------------------------------
    Parse the input string
    " xxx " - whitespace enclosed between quotes will be preserved
            - quotes need not be matched
      \     - escape character, next character is 
  -------------------------------------------------------------------------*/
  out_s      = &temp_s[0];
  max_out_s  = &temp_s[MIN(max_parsed_len, STRIP_QUOTES_MAX_LEN) - 1];  /* leave room for \0 */
  if (in_s)
  {
    escape = FALSE;
    quote  = FALSE;
    copy   = FALSE;
    while( *in_s )   /* terminate if NULL in input string is reached */
    {
      if (escape)    /* if last byte was escape, don't interpret this byte */
      {
        copy   = TRUE;
        escape = FALSE;
      }
      else
      {
        switch(*in_s)
        {
          case '"':
          {
            quote = !quote;
          }
          break;

          case '\\':   /* allow escape character - note escaping req'd here! */
          { 
            escape = TRUE;
          }
          break;

          case ' ':   /* space is included only if currently quoting */
          case '\t': //0x9:   /* tab is included only if currently quoting */
          case '\n':  /* newline */
          case '\r':  /* linefeed */
          case '\f':  /* formfeed */
          case '\b':  /* backspace */
          case '\v':  /* vertical tab */
          {
            if (!quote)
            {
              break;
            }
            /* else fall through */
          } /*lint -save -e616 */

          default: /*lint -restore */
          {
            copy = TRUE;
          }
          break;
        }
      }

      if (copy)
      {
        if (out_s == max_out_s)
        {
          DS_ATCOP_ERROR_LOG_1("Unquoted value length exceeds maximum =(d)!",
                     max_parsed_len);
          return FALSE;
        }
        *out_s++ = *in_s;  /* copy current character to output string */
        copy = FALSE;
      }

      in_s++;        /* done with current character, go to next */

    }/* while */
  }

  /* Terminate the string */
  *out_s++ = '\0';

  /* copy output to user's buffer */
  (void) strlcpy (parsed_s, temp_s, max_parsed_len);

  return TRUE;

} /* dsat707_strip_quotes() */

#endif /* FEATURE_DATA_IS707 */
