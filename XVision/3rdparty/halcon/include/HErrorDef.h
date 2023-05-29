/*****************************************************************************
 * HErrorDef.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Definition of error constants
 *
 * (c) 1996-2019 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 ****************************************************************************/

#ifndef HERRORDEF_H
#define HERRORDEF_H

/****************************************************************************/
/* Return values of HALCON operators in the case of no error (messages)     */
/****************************************************************************/

#define H_MSG_OK          2          /* Normal return value                 */
#define H_MSG_TRUE        H_MSG_OK   /* TRUE                                */
#define H_MSG_FALSE       3          /* FALSE                               */
#define H_MSG_VOID        4          /* Stop processing                     */
#define H_MSG_FAIL        5          /* Call failed                         */


/****************************************************************************/
#define H_ERR_BREAK       20 /* for internal use */
#define H_ERR_HEN_CANCEL  21 /* operator was canceled for hdevengine */
#define H_ERR_CANCEL      22 /* operator was generally cancelled */


/****************************************************************************/
/* Return codes for errors                                                  */
/****************************************************************************/
/* The values of errors range from 1000 to H_ERR_START_EXT                  */
/* Values beyond H_ERR_START_EXT are reserved for user extensions           */
/****************************************************************************/



/*****************************************************************/
/* Groups of error numbers:                                      */
/*****************************************************************/
/*  General error:                                               */
/*    Parameter of HALCON operators                              */
/*      Type input parameter            12xx                     */
/*      Value input parameter           13xx                     */
/*      Number values input parameter   14xx                     */
/*      Number objects input parameter  15xx                     */
/*****************************************************************/
/*  Main part:                                                   */
/*    CORE                              2xxx                     */
/*      CORE0                           20xx                     */
/*      CORE1                           21xx                     */
/*      COREx                           22xx                     */
/*      Licensing                       23xx                     */
/*      Tuple, Vectors, handles         24xx                     */
/*      Extensions (hlibxpi)            25xx                     */
/*      HALCON scheduling               28xx-29xx                */
/*    Image processing                  3xxx                     */
/*      Chords                          30xx                     */
/*      IPxx                            31xx                     */
/*      Contour                         32xx                     */
/*      XLD                             325x                     */
/*      Classification                  33xx                     */
/*      Morphology                      34xx                     */
/*      Runlength encoding              35xx                     */
/*      Bead Inspection                 371x-374x                */
/*      Sheet-of-light                  375x                     */
/*      Texture Inspection              381x                     */
/*      ShapeFrom                       385x                     */
/*      Kalman                          390x                     */
/*      Structured Light                395x-396x                */
/*      Background estimation           82xx                     */
/*      OCR                             83xx                     */
/*      OCV                             835x                     */
/*      Function 1D                     837x                     */
/*      Camera calibration              84xx                     */
/*      Template matching               85xx                     */
/*      1D Bar code                     87xx                     */
/*      2D Bar code (old)               8800                     */
/*      2D Data code (new)              8820-88xx                */
/*      3D Matching                     89xx                     */
/*    Data base                         4xxx                     */
/*    IOxx                              5xxx                     */
/*      General                         50xx                     */
/*      Window                          51xx                     */
/*      File                            52xx                     */
/*      Frame grabber                   53xx                     */
/*      Read picture                    55xx                     */
/*      Socket                          56xx                     */
/*****************************************************************/
/*  Further system components                                    */
/*    Memory management                 60xx                     */
/*    System                            65xx                     */
/*    Interfaces                                                 */
/*      General                         70xx                     */
/*      C                               74xx                     */
/*****************************************************************/
/*  Cxxx (e.g. CIPfeature)                                       */
/*      Cgpx                            80xx                     */
/*      Convol/Rank                     81xx                     */
/*****************************************************************/
/*  Misc                                                         */
/*      Misc                            90xx                     */
/*****************************************************************/

/* Control parameters */
/* Type input parameter 12xx */
#define H_ERR_WIPT1        1201 /* Wrong type of control parameter: 1 */
#define H_ERR_WIPT2        1202 /* Wrong type of control parameter: 2 */
#define H_ERR_WIPT3        1203 /* Wrong type of control parameter: 3 */
#define H_ERR_WIPT4        1204 /* Wrong type of control parameter: 4 */
#define H_ERR_WIPT5        1205 /* Wrong type of control parameter: 5 */
#define H_ERR_WIPT6        1206 /* Wrong type of control parameter: 6 */
#define H_ERR_WIPT7        1207 /* Wrong type of control parameter: 7 */
#define H_ERR_WIPT8        1208 /* Wrong type of control parameter: 8 */
#define H_ERR_WIPT9        1209 /* Wrong type of control parameter: 9 */
#define H_ERR_WIPT10       1210 /* Wrong type of control parameter: 10 */
#define H_ERR_WIPT11       1211 /* Wrong type of control parameter: 11 */
#define H_ERR_WIPT12       1212 /* Wrong type of control parameter: 12 */
#define H_ERR_WIPT13       1213 /* Wrong type of control parameter: 13 */
#define H_ERR_WIPT14       1214 /* Wrong type of control parameter: 14 */
#define H_ERR_WIPT15       1215 /* Wrong type of control parameter: 15 */
#define H_ERR_WIPT16       1216 /* Wrong type of control parameter: 16 */
#define H_ERR_WIPT17       1217 /* Wrong type of control parameter: 17 */
#define H_ERR_WIPT18       1218 /* Wrong type of control parameter: 18 */
#define H_ERR_WIPT19       1219 /* Wrong type of control parameter: 19 */
#define H_ERR_WIPT20       1220 /* Wrong type of control parameter: 20 */
/* Value input parameter 13xx */
#define H_ERR_WIPV1        1301 /* Wrong value of control parameter: 1 */
#define H_ERR_WIPV2        1302 /* Wrong value of control parameter: 2 */
#define H_ERR_WIPV3        1303 /* Wrong value of control parameter: 3 */
#define H_ERR_WIPV4        1304 /* Wrong value of control parameter: 4 */
#define H_ERR_WIPV5        1305 /* Wrong value of control parameter: 5 */
#define H_ERR_WIPV6        1306 /* Wrong value of control parameter: 6 */
#define H_ERR_WIPV7        1307 /* Wrong value of control parameter: 7 */
#define H_ERR_WIPV8        1308 /* Wrong value of control parameter: 8 */
#define H_ERR_WIPV9        1309 /* Wrong value of control parameter: 9 */
#define H_ERR_WIPV10       1310 /* Wrong value of control parameter: 10 */
#define H_ERR_WIPV11       1311 /* Wrong value of control parameter: 11 */
#define H_ERR_WIPV12       1312 /* Wrong value of control parameter: 12 */
#define H_ERR_WIPV13       1313 /* Wrong value of control parameter: 13 */
#define H_ERR_WIPV14       1314 /* Wrong value of control parameter: 14 */
#define H_ERR_WIPV15       1315 /* Wrong value of control parameter: 15 */
#define H_ERR_WIPV16       1316 /* Wrong value of control parameter: 16 */
#define H_ERR_WIPV17       1317 /* Wrong value of control parameter: 17 */
#define H_ERR_WIPV18       1318 /* Wrong value of control parameter: 18 */
#define H_ERR_WIPV19       1319 /* Wrong value of control parameter: 19 */
#define H_ERR_WIPV20       1320 /* Wrong value of control parameter: 20 */
#define H_ERR_WCOMP        1350 /* Wrong value of component */
#define H_ERR_WGCOMP       1351 /* Wrong value of gray value component */
/* Number of values input parameter 14xx */
#define H_ERR_WIPN1        1401 /* Wrong number of values of ctrl.par.: 1 */
#define H_ERR_WIPN2        1402 /* Wrong number of values of ctrl.par.: 2 */
#define H_ERR_WIPN3        1403 /* Wrong number of values of ctrl.par.: 3 */
#define H_ERR_WIPN4        1404 /* Wrong number of values of ctrl.par.: 4 */
#define H_ERR_WIPN5        1405 /* Wrong number of values of ctrl.par.: 5 */
#define H_ERR_WIPN6        1406 /* Wrong number of values of ctrl.par.: 6 */
#define H_ERR_WIPN7        1407 /* Wrong number of values of ctrl.par.: 7 */
#define H_ERR_WIPN8        1408 /* Wrong number of values of ctrl.par.: 8 */
#define H_ERR_WIPN9        1409 /* Wrong number of values of ctrl.par.: 9 */
#define H_ERR_WIPN10       1410 /* Wrong number of values of ctrl.par.: 10 */
#define H_ERR_WIPN11       1411 /* Wrong number of values of ctrl.par.: 11 */
#define H_ERR_WIPN12       1412 /* Wrong number of values of ctrl.par.: 12 */
#define H_ERR_WIPN13       1413 /* Wrong number of values of ctrl.par.: 13 */
#define H_ERR_WIPN14       1414 /* Wrong number of values of ctrl.par.: 14 */
#define H_ERR_WIPN15       1415 /* Wrong number of values of ctrl.par.: 15 */
#define H_ERR_WIPN16       1416 /* Wrong number of values of ctrl.par.: 16 */
#define H_ERR_WIPN17       1417 /* Wrong number of values of ctrl.par.: 17 */
#define H_ERR_WIPN18       1418 /* Wrong number of values of ctrl.par.: 18 */
#define H_ERR_WIPN19       1419 /* Wrong number of values of ctrl.par.: 19 */
#define H_ERR_WIPN20       1420 /* Wrong number of values of ctrl.par.: 20 */
/* Number of input objects 15xx */
#define H_ERR_IONTB        1500 /* Number of input objects too big */
#define H_ERR_WION1        1501 /* Wrong number of values of object par.: 1 */
#define H_ERR_WION2        1502 /* Wrong number of values of object par.: 2 */
#define H_ERR_WION3        1503 /* Wrong number of values of object par.: 3 */
#define H_ERR_WION4        1504 /* Wrong number of values of object par.: 4 */
#define H_ERR_WION5        1505 /* Wrong number of values of object par.: 5 */
#define H_ERR_WION6        1506 /* Wrong number of values of object par.: 6 */
#define H_ERR_WION7        1507 /* Wrong number of values of object par.: 7 */
#define H_ERR_WION8        1508 /* Wrong number of values of object par.: 8 */
#define H_ERR_WION9        1509 /* Wrong number of values of object par.: 9 */
#define H_ERR_OONTB        1510 /* Number of output objects too big */

/* Error codes concerning the HALCON core */
#define H_ERR_WNP          2000 /* Wrong specification of parameter (error in
                                   file: xxx.def) */
#define H_ERR_HONI         2001 /* Initialize Halcon:
                                   reset_obj_db(Width,Height,Components) */
#define H_ERR_WRKNN        2002 /* Used number of symbolic object names
                                   too big */

/* Error codes concerning licensing */
#define H_ERR_LIC_NO_LICENSE      2003 /* No license found */
#define H_ERR_LIC_NO_LS_SERVER    2004 /* Lost connection to license server */
#define H_ERR_LIC_NO_MODULES      2005 /* No modules in license
                                         (no VENDOR_STRING) */
#define H_ERR_LIC_NO_LIC_OPER     2006 /* No license for this operator */
#define H_ERR_LIC_BAD_TZ          2007 /* Time zone offset from GMT is
                                          > 24 hours */
#define H_ERR_LIC_BADPLATFORM     2008 /* Vendor keys do not support this
                                          platform */
#define H_ERR_LIC_BADVENDORKEY    2009 /* Bad vendor keys */
#define H_ERR_LIC_BADVENDORDATA   2010 /* Unknown vendor key type */
#define H_ERR_LIC_CANTMALLOC      2011 /* malloc() call failed */
#define H_ERR_LIC_EXPIREDKEYS     2012 /* Vendor keys have expired */
#define H_ERR_LIC_FUNCNOTAVAIL    2013 /* Second call to lc_inti()
                                          (multiple jobs), and vendorkeys
                                          do not support multiple jobs */
#define H_ERR_LIC_NOKEYDATA       2014 /* Vendor key data not supplied */
#define H_ERR_LIC_LIBRARYMISMATCH 2015 /* lmclient.h/liblmgr.a version
                                          mismatch */
#define H_ERR_LIC_NONETWORK       2016 /* Networking software not available
                                          on this machine */
#define H_ERR_LIC_OLDVENDORDATA   2017 /* Old vendor keys supplied */
#define H_ERR_LIC_BADCODE         2018 /* License key in license file does
                                          not match other data in file */
#define H_ERR_LIC_BADHANDSHAKE    2019 /* Encryption handshake with daemon
                                          failed */
#define H_ERR_LIC_BADPARAM        2020 /* 'key' structure is incorrect
                                          type, or feature == NULL, or
                                          num_licenses == 0 */
#define H_ERR_LIC_BADSYSDATE      2021 /* System clock has been set back */
#define H_ERR_LIC_BAD_VERSION     2022 /* Version argument is invalid
                                          floating point format */
#define H_ERR_LIC_BUSYNEWSERV     2023 /* License server busy starting
                                          another copy of itself */
#define H_ERR_LIC_CANTCONNECT     2024 /* Cannot establish a connection
                                          with a license server */
#define H_ERR_LIC_FEATQUEUE       2025 /* Feature is queued. lc_status will
                                          determine when it is available */
#define H_ERR_LIC_FUNC_NOT_AVAIL  2026 /* Vendor keys do not support this
                                          function */
#define H_ERR_LIC_LOCALFILTER     2027 /* Checkout request filtered by the
                                          vendor-defined filter routine */
#define H_ERR_LIC_MAXLIMIT        2028 /* Checkout exceeds MAX specified
                                          in options file */
#define H_ERR_LIC_MAXUSERS        2029 /* All licenses in use */
#define H_ERR_LIC_NO_SERVER_IN_FILE 2030 /* No license server specified
                                            for counted license */
#define H_ERR_LIC_NOFEATURE       2031 /* Can not find feature in the
                                          license file */
#define H_ERR_LIC_NOSERVSUPP      2032 /* Server has different license
                                          file than client - client's
                                          license has feature, but
                                          server's does not */
#define H_ERR_LIC_OLDVER          2033 /* License file does not support
                                          a version this new */
#define H_ERR_LIC_PLATNOTLIC      2034 /* This platform not authorized by
                                          license - running on platform
                                          not included in PLATFORMS list */
#define H_ERR_LIC_SERVBUSY        2035 /* License server busy */
#define H_ERR_LIC_NOCONFFILE      2036 /* Could not find license.dat */

#define H_ERR_LIC_BADFILE           2037 /* Invalid license file syntax */
#define H_ERR_LIC_NOSERVER          2038 /* Cannot connect to a license
                                            server */
#define H_ERR_LIC_NOSERVICE         2039 /* No TCP "license" service
                                            exists */
#define H_ERR_LIC_NOSOCKET          2040 /* No socket connection to
                                            license manager server */
#define H_ERR_LIC_NOTTHISHOST       2041 /* Invalid host */
#define H_ERR_LIC_LONGGONE          2042 /* Feature has expired */
#define H_ERR_LIC_BADDATE           2043 /* Invalid date format in license
                                            file */
#define H_ERR_LIC_BADCOMM           2044 /* Invalid returned data from
                                            license server */
#define H_ERR_LIC_BADHOST           2045 /* Cannot find SERVER hostname in
                                            network database */
#define H_ERR_LIC_CANTREAD          2046 /* Cannot read data from license
                                            server */
#define H_ERR_LIC_CANTWRITE         2047 /* Cannot write data to license
                                            server */
#define H_ERR_LIC_SELECTERR         2048 /* Error in select system call */
#define H_ERR_LIC_CHECKINBAD        2049 /* Feature checkin failure
                                            detected at license */
#define H_ERR_LIC_USERSQUEUED       2050 /* Users are queued for this
                                            feature */
#define H_ERR_LIC_SERVLONGGONE      2051 /* License server does not support
                                            this version of this feature */
#define H_ERR_LIC_TOOMANY           2052 /* Request for more licenses than
                                            this feature supports */
#define H_ERR_LIC_CANTREADKMEM      2053 /* Cannot read /dev/kmem */
#define H_ERR_LIC_CANTREADVMUNIX    2054 /* Cannot read /vmunix */
#define H_ERR_LIC_CANTFINDETHER     2055 /* Cannot find ethernet device */
#define H_ERR_LIC_NOREADLIC         2056 /* Cannot read license file */
#define H_ERR_LIC_TOOEARLY          2057 /* Feature not yet available */
#define H_ERR_LIC_NOSUCHATTR        2058 /* No such attribute */
#define H_ERR_LIC_CLOCKBAD          2059 /* Clock difference too large
                                            between client and server */
#define H_ERR_LIC_FEATCORRUPT       2060 /* Feature database corrupted in
                                            daemon */
#define H_ERR_LIC_BADFEATPARAM      2061 /* Duplicate selection mismatch
                                            for this feature */
#define H_ERR_LIC_FEATEXCLUDE       2062 /* User/host on EXCLUDE list for
                                            feature */
#define H_ERR_LIC_FEATNOTINCLUDE    2063 /* User/host not on INCLUDE list
                                            for feature */
#define H_ERR_LIC_NEVERCHECKOUT     2064 /* Feature was never checked out */
#define H_ERR_LIC_BADKEYDATA        2065 /* Invalid FLEXlm key data supplied */
#define H_ERR_LIC_NOCLOCKCHECK      2066 /* Clock setting check not
                                            available in daemon */
#define H_ERR_LIC_DATE_TOOBIG       2067 /* Date too late for binary format */
#define H_ERR_LIC_NOFLEXLMINIT      2068 /* FLEXlm not initialized */
#define H_ERR_LIC_NOSERVRESP        2069 /* Server did not respond to message */
#define H_ERR_LIC_CHECKOUTFILTERED  2070 /* Request rejected by vendor
                                            defined filter */
#define H_ERR_LIC_NOFEATSET         2071 /* No FEATURESET line present in
                                            license file */
#define H_ERR_LIC_BADFEATSET        2072 /* Incorrect FEATURESET line in
                                            license file */
#define H_ERR_LIC_CANTCOMPUTEFEATSET 2073 /* Cannot compute FEATURESET
                                             line */
#define H_ERR_LIC_SOCKETFAIL        2074 /* socket() call failed */
#define H_ERR_LIC_SETSOCKFAIL       2075 /* setsockopt() failed */
#define H_ERR_LIC_BADCHECKSUM       2076 /* Message checksum failure */
#define H_ERR_LIC_SERVNOREADLIC     2077 /* Cannot read license file from
                                            server */
#define H_ERR_LIC_NOTLICADMIN       2078 /* Not a license administrator */
#define H_ERR_LIC_REMOVETOOSOON     2079 /* lmremove request too soon */
#define H_ERR_LIC_ENDPATH           2080 /* Attempt to read beyond the end
                                            of LF path */
#define H_ERR_LIC_VMS_SETIMR_FAILED 2081 /* SYS$SETIMR call failed */
#define H_ERR_LIC_INTERNAL_ERROR    2082 /* Internal FLEXlm Erro - Please
                                            report to Globetrotter
                                            Software */
#define H_ERR_LIC_NOADMINAPI        2083 /* FLEXadmin API functions not
                                            avilable */
#define H_ERR_LIC_BADPKG            2084 /* Invalid PACKAGE line in
                                            license file */
#define H_ERR_LIC_SERVOLDVER        2085 /* Server FLEXlm version older
                                            than client's */
#define H_ERR_LIC_USER_BASED        2086 /* Incorrect number of USERS/HOSTS
                                            INCLUDED in options file */
#define H_ERR_LIC_NOSERVCAP         2087 /* Server doesn't support this
                                            request */
#define H_ERR_LIC_OBJECTUSED        2088 /* This license object already in
                                            use */

#define H_ERR_LIC_FUTURE_FILE       2089 /* Future license file format */
#define H_ERR_LIC_SERVER_REMOVED    2090 /* Feature removed during
                                            lmreread */
#define H_ERR_LIC_POOL              2091 /* This feature is available in a
                                            different license pool */
#define H_ERR_LIC_NOT_THIS_HOST     2092 /* Network connect to THIS_HOST
                                            failed */
#define H_ERR_LIC_HOSTDOWN          2093 /* Server node is down or not
                                            responding */
#define H_ERR_LIC_VENDOR_DOWN       2094 /* The desired vendor daemon is
                                            down */
#define H_ERR_LIC_BADDECFILE        2095 /* The decimal format license is
                                            typed incorrectly */
#define H_ERR_LIC_RESVFOROTHERS     2096 /* All licenses are reserved for
                                            others */
#define H_ERR_LIC_TSOK_ERR          2097 /* Terminal Server remote client
                                            not allowed */
#define H_ERR_LIC_BORROW_TOOLONG    2098 /* Cannot borrow that long */
#define H_ERR_LIC_SERVER_MAXED_OUT  2099 /* License server out of network
                                            connections */
#define H_ERR_LIC_NODONGLE          2300 /* Dongle not attached, or can't
                                            read dongle */
#define H_ERR_LIC_NODONGLEDRIVER    2301 /* Missing dongle driver */
#define H_ERR_LIC_FLEXLOCK2CKOUT    2302 /* FLEXlock checkouts attempted */
#define H_ERR_LIC_SIGN_REQ          2303 /* SIGN= attribute required */
#define H_ERR_LIC_NOCROSUPPORT      2304 /* CRO not supported for this
                                            platform */
#define H_ERR_LIC_BORROW_LINGER_ERR 2305 /* BORROW failed */
#define H_ERR_LIC_BORROW_EXPIRED    2306 /* BORROW period has expired */
#define H_ERR_LIC_FLOATOK_ONEHOSTID 2307 /* FLOAT_OK license must have
                                            exactly one dongle hostid */
#define H_ERR_LIC_BORROW_DELETE_ERR 2308 /* Unable to delete local borrow
                                            info" */
#define H_ERR_LIC_BORROW_RETURN_EARLY_ERR    2309 /* Returning borrowed
                                                     license early
                                                     not enabled */
#define H_ERR_LIC_BORROW_RETURN_SERVER_ERR   2310 /* Returning borrowed
                                                     license on server
                                                     failed */
#define H_ERR_LIC_CANT_CHECKOUT_JUST_PACKAGE 2311 /* Checkout just a
                                                     PACKAGE failed*/
#define H_ERR_LIC_COMPOSITEID_INIT_ERR 2312 /* Composite Hostid not
                                               initialized */
#define H_ERR_LIC_COMPOSITEID_ITEM_ERR 2313 /* An item needed for Composite
                                               Hostid missing or invalid */
#define H_ERR_LIC_BORROW_MATCH_ERR   2314 /* Borrowed license doesn't match
                                             any known server license */
#define H_ERR_LIC_EVENTLOG_INIT_ERR  2315 /* Error enabling event log */
#define H_ERR_LIC_EVENTLOG_DISABLED  2316 /* Event logging is disabled */
#define H_ERR_LIC_EVENTLOG_WRITE_ERR 2317 /* Error writing to event log */
#define H_ERR_LIC_TIMEOUT            2318 /* Timeout */
#define H_ERR_LIC_BADCOMMAND         2319 /* Bad message command */
#define H_ERR_LIC_SOCKET_BROKEN_PIPE 2320 /* Error writing to socket */
#define H_ERR_LIC_INVALID_SIGNATURE  2321 /* Failed to generate version
                                             specific license */
#define H_ERR_LIC_UNCOUNTED_NOT_SUPPORTED 2322 /* Vers.-specific signatures
                                                  not supported */
#define H_ERR_LIC_REDUNDANT_SIGNATURES 2323 /* License template contains
                                               redundant signature
                                               specifiers */
#define H_ERR_LIC_BADCODE_V71_LK    2324 /* Invalid V71_LK signature */
#define H_ERR_LIC_BADCODE_V71_SIGN  2325 /* Invalid V71_SIGN signature */
#define H_ERR_LIC_BADCODE_V80_LK    2326 /* Invalid V80_LK signature */
#define H_ERR_LIC_BADCODE_V80_SIGN  2327 /* Invalid V80_SIGN signature */
#define H_ERR_LIC_BADCODE_V81_LK    2328 /* Invalid V81_LK signature */
#define H_ERR_LIC_BADCODE_V81_SIGN  2329 /* Invalid V81_SIGN signature */
#define H_ERR_LIC_BADCODE_V81_SIGN2 2330 /* Invalid V81_SIGN2 signature */
#define H_ERR_LIC_BADCODE_V84_LK    2331 /* Invalid V84_LK signature */
#define H_ERR_LIC_BADCODE_V84_SIGN  2332 /* Invalid V84_SIGN signature */
#define H_ERR_LIC_BADCODE_V84_SIGN2 2333 /* Invalid V84_SIGN2 signature */
#define H_ERR_LIC_LK_REQ            2334 /* License key required but
                                            missing from the certificate */
#define H_ERR_LIC_BADAUTH           2335 /* Bad AUTH={} signature */
#define H_ERR_LIC_REPAIR_NEEDED     2336 /* TS record invalid */
#define H_ERR_LIC_TS_OPEN           2337 /* Cannot open TS */
#define H_ERR_LIC_BAD_FULFILLMENT   2338 /* Invalid Fulfillment record */
#define H_ERR_LIC_BAD_ACTREQ        2339 /* Invalid activation request
                                            received */
#define H_ERR_LIC_TS_NO_FULFILL_MATCH 2340 /* No fulfillment exists in
                                              trusted storage which matches
                                              the request */
#define H_ERR_LIC_BAD_ACT_RESP      2341 /* Invalid activation response
                                            received */
#define H_ERR_LIC_CANTRETURN        2342 /* Can't return the fulfillment */
#define H_ERR_LIC_RETURNEXCEEDSMAX  2343 /* Return would exceed max
                                            count(s) */
#define H_ERR_LIC_NO_REPAIRS_LEFT   2344 /* No repair count left */
#define H_ERR_LIC_NOT_ALLOWED       2345 /* Specified operation is not
                                            allowed */
#define H_ERR_LIC_ENTLEXCLUDE       2346 /* User/host on EXCLUDE list for
                                            entitlement */
#define H_ERR_LIC_ENTLNOTINCLUDE    2347 /* User/host not in INCLUDE list
                                            for entitlement */
#define H_ERR_LIC_ACTIVATION        2348 /* Activation error */
#define H_ERR_LIC_TS_BADDATE        2349 /* Invalid date format in trusted
                                            storage */
#define H_ERR_LIC_ENCRYPTION_FAILED 2350 /* Message encryption failed */
#define H_ERR_LIC_DECRYPTION_FAILED 2351 /* Message decryption failed */
#define H_ERR_LIC_BADCONTEXT        2352 /* Bad filter context */
#define H_ERR_LIC_SUPERSEDE_CONFLICT 2353 /* SUPERSEDE feature conflict */
#define H_ERR_LIC_INVALID_SUPERSEDE_SIGN 2354 /* Invalid SUPERSEDE_SIGN
                                                 syntax */
#define H_ERR_LIC_SUPERSEDE_SIGN_EMPTYSTRING 2355 /* SUPERSEDE_SIGN does
                                                     not contain a feature
                                                     name and license
                                                     signature */
#define H_ERR_LIC_ONE_TSOK_PLATFORM_ERR 2356 /* ONE_TS_OK is not supported
                                                in this Windows Platform */
#define H_ERR_LIC_ONE_TSOK_MTX_ERR  2357 /* Internal error */
#define H_ERR_LIC_ONE_TSOK_ERR      2358 /* Only one terminal server
                                            remote client checkout is
                                            allowed for this feature */
#define H_ERR_LIC_SSIDNULL          2359 /* Internal error */
#define H_ERR_LIC_SMTXNOTREL        2360 /* Internal error */
#define H_ERR_LIC_MTXNOPERM         2361 /* Internal error */
#define H_ERR_LIC_COMPOSITEID_ETHER_ERR 2362 /* More than one ethernet
                                                hostid not supported in
                                                composite hostid
                                                definition */
#define H_ERR_LIC_LIC_FILE_CHAR_EXCEED 2363 /* The number of characters in
                                               the license file paths
                                               exceeds the permissible
                                               limit */
#define H_ERR_LIC_TZ_INVALID_SYNTAX 2364 /* Invalid TZ keyword syntax */
#define H_ERR_LIC_TZ_INVALID_TZONE_SPEC 2365 /* Invalid time zone override
                                                specification in the
                                                client */
#define H_ERR_LIC_TZ_INVALID_TZONE_INFO 2366 /* The time zone information
                                                could not be obtained */
#define H_ERR_LIC_TZ_UNAUTHORIZED   2367 /* License client time zone not
                                            authorized for license
                                            rights */
#define H_ERR_LIC_INVALID_VM_PLATFORMS 2368 /* Invalid syntax for
                                               VM_PLATFORMS keyword */
#define H_ERR_LIC_VM_PHYSICAL_ONLY  2369 /* Feature can be checked out
                                            from physical machine only */
#define H_ERR_LIC_VM_VIRTUAL_ONLY   2370 /* Feature can be checked out
                                            from virtual machine only */
#define H_ERR_LIC_VM_BAD_KEY        2371 /* Vendor keys do not support
                                            Virtualization feature */
#define H_ERR_LIC_MAXLIMIT_EXCEED   2372 /* Checkout request denied as it
                                            exceeds the MAX limit
                                            specified in the options
                                            file */
#define H_ERR_LIC_BA_API_INTERNAL_ERROR 2373 /* Binding agent API -
                                                Internal error */
#define H_ERR_LIC_BA_COMM_ERROR     2374 /* Binding agent communication
                                            error */
#define H_ERR_LIC_INVALID_BA_VERSION 2375 /* Invalid Binding agent
                                             version */
#define H_ERR_LIC_SERVERQUERY_LOAD_REQUEST_FAILED 2376
                                              /* Failed to load ServerQuery
                                                 request */
#define H_ERR_LIC_SERVERQUERY_RESPONSE_FAILED 2377
                                              /* Failed to generate ServerQuery
                                                 response */
#define H_ERR_LIC_INVALID_IPADDRESS 2378  /* Invalid IP address used while
                                             overriding */
#define H_ERR_LIC_NO_CM_RUNTIME      2379 /* No CodeMeter Runtime installed */
#define H_ERR_LIC_CM_RUNTIME_TOO_OLD 2380 /* Installed CodeMeter Runtime is too
                                             old */
#define H_ERR_LIC_WRONG_EDITION      2381 /* License is for wrong HALCON
                                             edition */
#define H_ERR_LIC_UNKNOWN_FLAGS      2382 /* License contains unknown FLAGS */
#define H_ERR_LIC_PREVIEW_EXPIRED    2383 /* HALCON preview version expired */
#define H_ERR_LIC_NEWVER             2384 /* License does not support a HALCON
                                             version this old */

/* Adapt this to be the highest error code concerning licensing */
#define H_ERR_LAST_LIC_ERROR H_ERR_LIC_NEWVER

/* Error codes concerning the HALCON core, 2100..2199 */
#define H_ERR_WOOPI        2100 /* Wrong index for output object parameter */
#define H_ERR_WIOPI        2101 /* Wrong index for input object parameter*/
#define H_ERR_WOI          2102 /* Wrong index for image object */
#define H_ERR_WRCN         2103 /* Wrong number region/image component */
#define H_ERR_WRRN         2104 /* Wrong relation name */
#define H_ERR_AUDI         2105 /* Access to undefined gray value component*/
#define H_ERR_WIWI         2106 /* Wrong image width */
#define H_ERR_WIHE         2107 /* Wrong image height */
#define H_ERR_ICUNDEF      2108 /* Undefined gray value component */

/* Error codes concerning the HALCON core (+ Language interfaces),
   2200..2299 */
#define H_ERR_IDBD         2200 /* Inconsistent data of data base (typing) */
#define H_ERR_WICPI        2201 /* Wrong index for input control parameter */
#define H_ERR_DBDU         2202 /* Data of data base not defined
                                   (internal error) */
#define H_ERR_PNTL         2203 /* legacy: Number of operators too big */
#define H_ERR_UEXTNI       2205 /* User extension not properly installed */
#define H_ERR_NPTL         2206 /* legacy: Number of packages too large */
#define H_ERR_NSP          2207 /* No such package installed */

#define H_ERR_ICHV         2211 /* incompatible HALCON versions */
#define H_ERR_ICOI         2212 /* incompatible operator interface */
#define H_ERR_XPKG_WXID    2220 /* wrong extension package id */
#define H_ERR_XPKG_WOID    2221 /* wrong operator id */
#define H_ERR_XPKG_WOIID   2222 /* wrong operator information id */

/* Error codes concerning the HALCON control tuples, 2400.. */
#define H_ERR_CTPL_WTYP         2400 /* Wrong Hctuple array type */
#define H_ERR_CPAR_WTYP         2401 /* Wrong Hcpar type */
#define H_ERR_CTPL_WIDX         2402 /* Wrong Hctuple index */
#define H_ERR_WFV               2403 /* Wrong version of file */
#define H_ERR_WRONG_HANDLE_TYPE 2404 /* Wrong handle type */

/* Error codes concerning the HALCON vectors, 2410.. */
#define H_ERR_WVTYP         2410 /* wrong vector type */
#define H_ERR_WVDIM         2411 /* wrong vector dimension */

/* Error codes concerning the HALCON handles and ids 2450 ...
 * These error codes are only used internally and no error text is available
 * for these codes, therefore. */
#define H_ERR_WHDL           2450 /* Wrong (unknown) HALCON handle */
#define H_ERR_WID            2451 /* Wrong HALCON id, no data available */
#define H_ERR_IDOOR          2452 /* HALCON id out of range */
#define H_ERR_HANDLE_NULL    2453 /* Handle is NULL */
#define H_ERR_HANDLE_CLEARED 2454 /* Handle was cleared */
#define H_ERR_HANDLE_NOSER   2455 /* Handle type does not serialize */

/* Error codes concerning HALCON extensions, esp. of the
 * HALCON Library Extension Programming Interface (hlibxpi) 2500 ... */
#define H_ERR_XPI_INIT_NOT_CALLED 2500 /* hlibxpi Init function of an extension
                                        * that was build with xpi was not
                                        * called */
#define H_ERR_XPI_NO_INIT_FOUND   2501 /* hlib didn't find the init function
                                        * of the extension it is connecting to
                                        * -> old extension without hlibxpi or
                                        *    the function export failed */
#define H_ERR_XPI_UNRES           2502 /* Unresolved function in hlibxpi */
#define H_ERR_XPI_HLIB_TOO_OLD    2503 /* HALCON extension requires a HALCON
                                        * version that is newer than the
                                        * connected hlib */
#define H_ERR_XPI_XPI_TOO_OLD     2504 /* the (major) version of the hlibxpi
                                        * which is used by the connecting
                                        * extension is too small for hlib */
#define H_ERR_XPI_MAJOR_TOO_SMALL 2505 /* the major version of the hlibxpi
                                        * which is used by the hlib is too
                                        * small */
#define H_ERR_XPI_MINOR_TOO_SMALL 2506 /* the minor version of the hlibxpi
                                        * which is used by the hlib is too
                                        * small */
#define H_ERR_XPI_INT_WRONG_MAJOR 2507 /* Wrong major version in symbol struct
                                        * (internal: should not happen) */
#define H_ERR_XPI_UNKNOW_HLIB_VER 2508 /* HLib version could not be detected */


/* HALCON agents/scheduler (parallel processing HALCON operators),
   2800..2999 */
#define H_ERR_HW_WFF       2800 /* Wrong hardware information file format    */
#define H_ERR_HW_WFV       2801 /* Wrong hardware information file version   */
#define H_ERR_HW_RF        2802 /* Error while reading the hardware knowledge*/
#define H_ERR_HW_WF        2803 /* Error while writing the hardware knowledge*/
#define H_ERR_HW_TF        2804 /* Tag not found                             */
#define H_ERR_HW_CPU       2805 /* No CPU Info  */
#define H_ERR_HW_AOP       2806 /* No AOP Info  */
#define H_ERR_HW_HVAR      2807 /* No AOP Info for this HALCON variant  */
#define H_ERR_HW_HARCH     2808 /* No AOP Info for this HALCON architecture */
#define H_ERR_HW_HOP       2809 /* No AOP Info for specified Operator found */
#define H_ERR_HW_WAOPM     2810 /* undefined AOP model */
#define H_ERR_HW_WTD       2811 /* wrong tag derivate */
#define H_ERR_HW_IE        2812 /* internal error */
#define H_ERR_HW_CANCEL    2813 /* hw check was canceled */

#define H_ERR_GV_WA        2830 /* Wrong access to global variable */
#define H_ERR_GV_NC        2831 /* Used global variable does not exist */
#define H_ERR_GV_NG        2832 /* Used global variable not accessible via
                                   GLOBAL_ID */

#define H_ERR_HM_NT        2835 /* Halcon server to terminate is still
                                   working on a job */

#define H_ERR_HM_NA        2837 /* No such HALCON software agent */
#define H_ERR_AG_CN        2838 /* Hardware check for parallelization not
                                   possible on a single-processor machine */
#define H_ERR_AG_NC        2839 /* (Seq.) HALCON does not support parallel
                                   hardware check (use Parallel HALCON
                                   instead) */
#define H_ERR_AG_IN        2840 /* Initialization of agent failed */
#define H_ERR_AG_NT        2841 /* Termination of agent failed */
#define H_ERR_AG_HW        2842 /* Inconsistent hardware description file */
#define H_ERR_AG_II        2843 /* Inconsistent agent information file */
#define H_ERR_AG_IK        2844 /* Inconsistent agent knowledge file */
#define H_ERR_AG_WV        2845 /* The file with the parallelization
                                   information does not match to the
                                   currently HALCON version/revision */
#define H_ERR_AG_WH        2846 /* The file with the parallelization
                                   information does not match to the
                                   currently used machine */
#define H_ERR_AG_KC        2847 /* Inconsistent knowledge base of HALCON
                                   software agent */
#define H_ERR_AG_CT        2848 /* Unknown communication type */
#define H_ERR_AG_MT        2849 /* Unknown message type for HALCON software
                                   agent */
#define H_ERR_AG_WK        2850 /* Error while saving the parallelization
                                   knowledge */
#define H_ERR_AG_WW        2851 /* Wrong type of work information */
#define H_ERR_AG_WA        2852 /* Wrong type of application information */
#define H_ERR_AG_WE        2853 /* Wrong type of experience information */
#define H_ERR_AG_NU        2854 /* Unknown name of HALCON software agent */
#define H_ERR_AG_NE        2855 /* Unknown name and communication address of
                                   HALCON software agent */
#define H_ERR_AG_RR        2856 /* cpu representative (HALCON software agent)
                                   not reachable */
#define H_ERR_AG_CR        2857 /* cpu refuses work */
#define H_ERR_AG_RN        2858 /* Description of scheduling resource
                                   not found */
#define H_ERR_AG_TILT      2859 /* Not accessible function of HALCON
                                   software agent */

#define H_ERR_WRT          2860 /* Wrong type: HALCON scheduling resource */
#define H_ERR_WRS          2861 /* Wrong state: HALCON scheduling resource */
#define H_ERR_UNKPT        2862 /* Unknown parameter type:
                                   HALCON scheduling resource */
#define H_ERR_UNKPARVAL    2863 /* Unknown parameter value:
                                   HALCON scheduling resource */
#define H_ERR_CTRL_WPP     2864 /* Wrong post processing of
                                   control parameter */

#define H_ERR_GETTI        2867 /* Error while trying to get time */
#define H_ERR_GETCPUNUM    2868 /* Error while trying to get the number
                                   of processors */
#define H_ERR_TMPFNF       2869 /* Error while accessing temporary file */

#define H_ERR_MQCNCL       2890 /* message queue wait operation canceled */
#define H_ERR_MQOVL        2891 /* message queue overflow */
#define H_ERR_MQCLEAR      2892 /* Threads still wait on message queue while
                                 * clearing it. */
#define H_ERR_M_WRFILE     2893 /* Invalid file format for a message */

#define H_ERR_DICT_KEY     2894 /* Dict does not contain requested key */
#define H_ERR_DICT_TUPLE_LENGTH 2895 /* Incorrect tuple length in dict */
#define H_ERR_DICT_TUPLE_TYPE 2896 /* Incorrect tuple type in dict */

#define H_ERR_PTHRD_SCHED  2900 /* Error while forcing a context switch */
#define H_ERR_SCHED_GAFF   2901 /* Error while accessing cpu affinity */
#define H_ERR_SCHED_SAFF   2902 /* Error while setting cpu affinity */

#define H_ERR_CO_WSO       2950 /* wrong synchronization object  */
#define H_ERR_CO_WOCO      2952 /* wrong operator call object   */
#define H_ERR_CO_IOPNI     2953 /* input object not initialized */
#define H_ERR_CO_ICPNI     2954 /* input control not initialized */
#define H_ERR_CO_OOPNI     2955 /* output object not initialized */
#define H_ERR_CO_OCPNI     2956 /* output control not initialized */

#define H_ERR_PTHRD_CR     2970 /* Creation of pthread failed */
#define H_ERR_PTHRD_DT     2971 /* pthread-detach failed */
#define H_ERR_PTHRD_JO     2972 /* pthread-join failed */
#define H_ERR_PTHRD_MI     2973 /* Initialization of mutex variable failed */
#define H_ERR_PTHRD_MD     2974 /* Deletion of mutex variable failed */
#define H_ERR_PTHRD_ML     2975 /* Lock of mutex variable failed */
#define H_ERR_PTHRD_MU     2976 /* Unlock of mutex variable failed */
#define H_ERR_PTHRD_CS     2977 /* Failed to signal pthread condition var. */
#define H_ERR_PTHRD_CW     2978 /* Failed to wait for pthread cond. var. */
#define H_ERR_PTHRD_CI     2979 /* Failed to init pthread condition var. */
#define H_ERR_PTHRD_CD     2980 /* Failed to destroy pthread condition var.*/
#define H_ERR_PTHRD_ES     2981 /* Failed to signal event. */
#define H_ERR_PTHRD_EW     2982 /* Failed to wait for event. */
#define H_ERR_PTHRD_EI     2983 /* Failed to init event. */
#define H_ERR_PTHRD_ED     2984 /* Failed to destroy event.*/
#define H_ERR_PTHRD_TSDC   2985 /* Failed to create a tsd key.*/
#define H_ERR_PTHRD_TSDS   2986 /* Failed to set a thread specific data key.*/
#define H_ERR_PTHRD_TSDG   2987 /* Failed to get a tsd key.*/
#define H_ERR_PTHRD_TSDF   2988 /* Failed to free a tsd key.*/
#define H_ERR_PTHRD_BA     2989 /* Aborted waiting at a barrier*/

#define H_ERR_DCDG_FLE     2990 /* 'Free list' is empty while scheduling */

#define H_ERR_MSG_PNCI     2991 /* Communication partner not checked in */
#define H_ERR_MSG_CSAI     2992 /* The communication system can't be started
                                   while running */
#define H_ERR_MSG_CSNI     2993 /* Communication partner not checked in */

#define H_ERR_PTHRD_BI     2994 /* Initialization of Barrier failed */
#define H_ERR_PTHRD_BW     2995 /* Waiting at a barrier failed */
#define H_ERR_PTHRD_BD     2996 /* Destroying of an barrier failed */


/* Runlength data 3000..3099 */
#define H_ERR_RCOIMA       3010 /* Region completely outside of the
                                   image domain */
#define H_ERR_ROOIMA       3011 /* Region (partially) outside of the
                                   definition range of the image */
#define H_ERR_RIEI         3012 /* Intersected definition range
                                   region/image empty */
#define H_ERR_EDEF         3013 /* Image with empty definition range */
#define H_ERR_IIEI         3014 /* No common image point of two images */
#define H_ERR_FLTS         3015 /* Wrong region for image (first row < 0) */
#define H_ERR_LLTB         3016 /* Wrong region for image
                                   (column in last row >= image width) */
#define H_ERR_UENOI        3017 /* Number of images unequal in input pars. */
#define H_ERR_HTS          3018 /* Image height too small */
#define H_ERR_WTS          3019 /* Image width too small */
#define H_ERR_CHSEG        3020 /* Internal error:
                                   Multiple call of HRLInitSeg() */
#define H_ERR_RLSEG1       3021 /* Internal error:
                                   HRLSeg() not initialized */
#define H_ERR_WGAUSSM      3022 /* Wrong size of filter for Gauss */
#define H_ERR_FSEIS        3033 /* Filter size exceeds image size */
#define H_ERR_FSEVAN       3034 /* Filter size evan */
#define H_ERR_FSTOBIG      3035 /* Filter size to big */
#define H_ERR_EMPTREG      3036 /* Region is empty */
#define H_ERR_DOM_DIFF     3037 /* Domains of the input images differ */


/* Cordinates */
#define H_ERR_ROWTB        3040 /* Row value of a coordinate > 2^15-1
                                   (XL: 2^31 - 1) */
#define H_ERR_ROWTS        3041 /* Row value of a coordinate < -2^15
                                   (XL: -2^31) */
#define H_ERR_COLTB        3042 /* Column value of a coordinate > 2^15-1
                                   (XL: 2^31 - 1) */
#define H_ERR_COLTS        3043 /* Column value of a coordinate < -2^15
                                   (XL: -2^31) */

/* Error codes concerning image processing, 31xx */
#define H_ERR_WRTHR        3100 /* Wrong segmentation threshold */
#define H_ERR_UNKF         3101 /* Unknown feature */
#define H_ERR_UNKG         3102 /* Unknown gray value feature */
#define H_ERR_EINCC        3103 /* Internal error in HContCut */
#define H_ERR_EINCP1       3104 /* Error in HContToPol:
                                   distance of points too big */
#define H_ERR_EINCP2       3105 /* Error in HContToPol: contour too long */
#define H_ERR_TMR          3106 /* Too many rows (IPImageTransform) */
#define H_ERR_SFZ          3107 /* Scaling factor = 0.0 (IPImageScale) */
#define H_ERR_OOR          3108 /* Wrong range in transformation matrix */
#define H_ERR_NEF          3109 /* Internal error in IPvvf: no element free */
#define H_ERR_NOOB         3110 /* Number of input objects is zero */
#define H_ERR_EMPOB        3111 /* At least one input object has an
                                   empty region */
#define H_ERR_NPOT         3112 /* Operation allowed for rectangular
                                   images 2**n only */
#define H_ERR_TMEP         3113 /* Too many relevant points (IPHysterese) */
#define H_ERR_LTB          3114 /* Number of labels in image too big */
#define H_ERR_NNLA         3115 /* No labels with negative values allowed */
#define H_ERR_WFS          3116 /* Wrong filter size (too small ?) */
#define H_ERR_IWDS         3117 /* Images with different image size */
#define H_ERR_IWTL         3118 /* Target image too wide or too far
                                   on the right */
#define H_ERR_IWTS         3119 /* Target image too narrow or too far
                                   on the left */
#define H_ERR_IHTL         3120 /* Target image too high or too far down */
#define H_ERR_IHTS         3121 /* Target image too low or too far up */
#define H_ERR_DNOC         3122 /* Number of channels in the input parameters
                                   are different */
#define H_ERR_WRCFAFLT     3123 /* Wrong color filter array type */
#define H_ERR_WRCFAINT     3124 /* Wrong color filter array interpolation */
#define H_ERR_NO_AFFTRANS  3125 /* Homogeneous matrix does not represent an
                                   affine transformation */
#define H_ERR_INPNOBDRY    3126 /* Inpainting region too close to the image
                                   border */
#define H_ERR_DSIZESD      3127 /* source and destination differ in size*/
#define H_ERR_TMFEAT       3128 /* to many features*/
#define H_ERR_AXIS_UNDEF   3129 /* Reflection axis undefined */

/* Coocurrence */
#define H_ERR_COWTS        3131 /* Coocurrence Matrix:
                                   Too little columns for quantisation */
#define H_ERR_COHTS        3132 /* Coocurrence Matrix:
                                   Too little rows for quantisation */
#define H_ERR_NUM_COLMN    3133 /* Wrong number of columns */
#define H_ERR_NUM_LINES    3134 /* Wrong number of rows */
#define H_ERR_OVL          3135 /* Number has too many digits */
#define H_ERR_NOT_SYM      3136 /* Matrix is not symmetric */
#define H_ERR_NUM_COLS     3137 /* Matrix is too big */
#define H_ERR_SYNTAX       3138 /* Wrong structure of file */
#define H_ERR_MISSING      3139 /* Less than 2 matrices */
#define H_ERR_COOC_MEM     3140 /* Not enough memory */
#define H_ERR_NO_FILE      3141 /* Can not read the file */
#define H_ERR_FILE_WR      3142 /* Can not open file for writing */
#define H_ERR_NUM_LUCOLS   3143 /* Too many lookup table colors */

#define H_ERR_WNOLI        3145 /* Too many Hough points (lines) */
#define H_ERR_DITS         3146 /* Target image has got wrong height
                                   (not big enough) */
#define H_ERR_WINTM        3147 /* Wrong interpolation mode */
#define H_ERR_THICK_NK     3148 /* Region not compact or not connected */


/* Laws */
#define H_ERR_WIND3        3170 /* Wrong filter index for filter size 3 */
#define H_ERR_WIND5        3171 /* Wrong filter index for filter size 5 */
#define H_ERR_WIND7        3172 /* Wrong filter index for filter size 7 */
#define H_ERR_WLAWSS       3173 /* Wrong filter size; only 3/5/7 */

/* Noise estimation */
#define H_ERR_NE_NPTS      3175 /* Number of suitable pixels too small to
                                   reliably estimate the noise */

/* Contour */
#define H_ERR_WNEE         3200 /* Different number of entries/exits
                                   in HContCut */
#define H_ERR_REF          3201 /* Reference to contour is missing */

/* XLD */
#define H_ERR_XLDWT        3250 /* Wrong XLD type */
#define H_ERR_XLD_RPF      3252 /* Border point is set to FG */
#define H_ERR_XLD_MCL      3253 /* Maximum contour length exceeded */
#define H_ERR_XLD_MCN      3254 /* Maximum number of contours exceeded */
#define H_ERR_XLD_CTS      3255 /* Contour too short for fetch_angle_xld */
#define H_ERR_XLD_CRD      3256 /* Regression parameters of contours
                                   already computed */
#define H_ERR_XLD_CRND     3257 /* Regression parameters of contours not
                                   yet entered! */

#define H_ERR_DBXC         3258 /* Data base: XLD object has been deleted */
#define H_ERR_DBWXID       3259 /* Data base: Object has no XLD-ID */

#define H_ERR_XLD_WNP      3260 /* Wrong number of contour points allocated */
#define H_ERR_XLD_CAND     3261 /* Contour attribute not defined */

#define H_ERR_FIT_ELLIPSE  3262 /* Ellipse fitting failed */
#define H_ERR_FIT_CIRCLE   3263 /* Circle fitting failed */
#define H_ERR_FIT_CLIP     3264 /* All points classified as outliers
                                   (ClippingFactor too small or used points
                                   not similar to primitive) */
#define H_ERR_FIT_QUADRANGLE 3265 /* Quadrangle fitting failed */
#define H_ERR_INCOMPL_RECT 3266 /* No points for at least one rectangle side */
#define H_ERR_XLD_COI      3267 /* A contour point lies outside of the image */
#define H_ERR_FIT_NOT_ENOUGH_POINTS  3274 /* Not enough points for model
                                             fitting */


#define H_ERR_NWF          3275 /* No ARC/INFO world file */
#define H_ERR_NAIGF        3276 /* No ARC/INFO generate file */

#define H_ERR_DXF_UEOF     3278 /* Unexpected end of file while
                                   reading DXF file */
#define H_ERR_DXF_CRGC     3279 /* Cannot read DXF-group code from file */
#define H_ERR_DXF_INAPP    3280 /* Inconsistent number of attributes
                                   per point in DXF file */
#define H_ERR_DXF_INAPPN   3281 /* Inconsistent number of attributes and
                                   names in DXF file */
#define H_ERR_DXF_INAPCN   3282 /* Inconsistent number of global attributes
                                   and names in DXF file */
#define H_ERR_DXF_CRAPP    3283 /* Cannot read attributes from DXF file */
#define H_ERR_DXF_CRAPC    3284 /* Cannot read global attributes
                                   from DXF file */
#define H_ERR_DXF_CRAN     3285 /* Cannot read attribute names from DXF file */
#define H_ERR_DXF_WPN      3286 /* Wrong generic parameter name */
#define H_ERR_DXF_IEDT     3289 /* Internal DXF I/O error: Wrong data type */

#define H_ERR_XLD_ISOL_POINT 3290 /* Isolated point while contour merging */

#define H_ERR_NURBS_CCBF   3291  /* Constraints cannot be fulfilled */

#define H_ERR_NSEG         3292  /* No segment in contour */
#define H_ERR_NO_ONE_P     3293  /* Only one or no point in template contour */

/* Classification */
#define H_ERR_SESF         3300 /* Syntax error in file for training */
#define H_ERR_TMFE         3301 /* Maximum number of attributes per example
                                   exceeded */
#define H_ERR_OPSF         3302 /* Not possible to open file for training */
#define H_ERR_TMSS         3303 /* Too many data sets for training */
#define H_ERR_TMSAM        3305 /* Too many examples for one data set for
                                   training */
#define H_ERR_TMCLS        3306 /* Too many classes */
#define H_ERR_TMBOX        3307 /* Maximum number of cuboids exceeded */
#define H_ERR_OPCF         3308 /* Not possible to open classificator's file */
#define H_ERR_SCLA         3309 /* Error while saving the classificator */
#define H_ERR_OPF          3310 /* Not possible to open protocol file */
#define H_ERR_CLEX         3311 /* Classificator with this name is already
                                   existent */
#define H_ERR_TMCLA        3312 /* Maximum number of classificators exceeded */
#define H_ERR_CNTL         3313 /* Name of classificator is too long, >= 20 */
#define H_ERR_CLNNF        3314 /* Classificator with this name is not
                                   existent */
#define H_ERR_NCCLA        3315 /* Current classificator is not defined */
#define H_ERR_CLASS2_ID    3316 /* Wrong id in classification file */
#define H_ERR_CLASS2_VERS  3317 /* The version of the classifier
                                   is not supported */
#define H_ERR_CLASS_NOSITEM 3318 /* Serialized item does not contain
                                    a valid classifier */
#define H_ERR_TM_NO_CL      3319 /* Text model does not contain a classifier
                                    yet (use set_text_model_param) */


#define H_ERR_KNN_CANNOT_ADD       3320  /* Adding new features is not
                                            possible, because the dataset has
                                            been normalized during training.
                                            Please create a new classfier and
                                            add all training data again or
                                            disable normalization during
                                            training.*/

#define H_ERR_GMM_NOTRAINFILE      3330 /* Invalid file format for GMM
                                           training samples */
#define H_ERR_GMM_WRTRAINVERS      3331 /* The version of the GMM training
                                           samples is not supported */
#define H_ERR_GMM_WRSMPFORMAT      3332 /* Wrong training sample file format */
#define H_ERR_GMM_NOCLASSFILE      3333 /* nvalid file format for
                                           Gaussian Mixture Model (GMM) */
#define H_ERR_GMM_WRCLASSVERS      3334 /* The version of the Gaussian Mixture
                                           Model (GMM) is not supported */
#define H_ERR_GMM_TRAIN_UNKERR     3335 /* Unknown error when training GMM */
#define H_ERR_GMM_TRAIN_COLLAPSED  3336 /* Collapsed covariance matrix */
#define H_ERR_GMM_TRAIN_NOSAMPLE   3337 /* No samples for at least one class */
#define H_ERR_GMM_TRAIN_FEWSAMPLES 3338 /* Too few samples for at least one
                                           class */
#define H_ERR_GMM_NOTTRAINED       3340 /* GMM is not trained */
#define H_ERR_GMM_NOTRAINDATA      3341 /* GMM has no training data */
#define H_ERR_GMM_NOSITEM          3342 /* Serialized item does not contain a
                                         valid Gaussian Mixture Model (GMM) */

#define H_ERR_MLP_UNKOUTFUNC  3350 /* Unknown output function */
#define H_ERR_MLP_NOT01ENC    3351 /* Target not in 0-1 encoding */
#define H_ERR_MLP_NOTRAINDATA 3352 /* No training samples stored in the
                                      classifier */
#define H_ERR_MLP_NOTRAINFILE 3353 /* Invalid file format for MLP
                                      training samples */
#define H_ERR_MLP_WRTRAINVERS 3354 /* The version of the MLP training
                                      samples is not supported */
#define H_ERR_MLP_WRSMPFORMAT 3355 /* Wrong training sample format */
#define H_ERR_MLP_NOCLASSIF   3356 /* MLP is not a classifier */
#define H_ERR_MLP_NOCLASSFILE 3357 /* Invalid file format for
                                      multilayer perceptron (MLP) */
#define H_ERR_MLP_WRCLASSVERS 3358 /* The version of the multilayer
                                      perceptron (MLP) is not supported */
#define H_ERR_WRNUMCHAN       3359 /* Wrong number of channels */
#define H_ERR_MLP_WRNUMPARAM  3360 /* Wrong number of MLP parameters */
#define H_ERR_MLP_NOSITEM     3361 /* Serialized item does not contain a
                                      valid multilayer perceptron (MLP) */


#define H_ERR_LUT_WRNUMCHAN   3370 /* The number of image channels and the
                                      number of dimensions of the look-up
                                      table do not match */
#define H_ERR_LUT_NRCHANLARGE 3371 /* A look-up table can be build for 2 or 3
                                      channels only */
#define H_ERR_LUT_CANNOTCREAT 3372 /* Cannot create look-up table. Please
                                      choose a larger 'bit_depth' or select
                                      the 'fast' 'class_selection'. */


#define H_ERR_SVM_NOTRAINDATA  3380 /* No training samples stored in the
                                       classifier */
#define H_ERR_SVM_NOTRAINFILE  3381 /* Invalid file format for SVM
                                       training samples */
#define H_ERR_SVM_WRTRAINVERS  3382 /* The version of the SVM training
                                       samples is not supported */
#define H_ERR_SVM_WRSMPFORMAT  3383 /* Wrong training sample format */
#define H_ERR_SVM_NOCLASSFILE  3384 /* Invalid file format for support
                                       vector machine (SVM) */
#define H_ERR_SVM_WRCLASSVERS  3385 /* The version of the support vector
                                       machine (SVM) is not supported */
#define H_ERR_SVM_WRNRCLASS    3386 /* Wrong number of classes */
#define H_ERR_SVM_NU_TOO_BIG   3387 /* Chosen nu is too big */
#define H_ERR_SVM_TRAIN_FAIL   3388 /* SVM Training failed */
#define H_ERR_SVM_DO_NOT_FIT   3389 /* SVMs do not fit together */
#define H_ERR_SVM_NO_TRAIN_ADD 3390 /* No SV in SVM to add to training */
#define H_ERR_SVM_KERNELNOTRBF 3391 /* Kernel must be RBF */
#define H_ERR_SVM_NO_TRAIND_FOR_CLASS 3392 /* Not all classes contained in
                                              training data */
#define H_ERR_SVM_NOT_TRAINED  3393 /* SVM not trained */
#define H_ERR_NOT_TRAINED      3394 /* Classifier not trained */
#define H_ERR_SVM_NOSITEM      3395 /* Serialized item does not contain a
                                       valid support vector machine (SVM) */

/* Morphology */
#define H_ERR_ROTNR        3401 /* Wrong rotation number */
#define H_ERR_GOL          3402 /* Wrong letter for Golay element */
#define H_ERR_BEZ          3403 /* Wrong reference point */
#define H_ERR_ITER         3404 /* Wrong number of iterations */
#define H_ERR_MOSYS        3405 /* Mophology: system error */
#define H_ERR_ART          3406 /* Wrong type of boundary */
#define H_ERR_OBJI         3407 /* Morphology: Wrong number of input obj. */
#define H_ERR_OBJO         3408 /* Morphology: Wrong number of output obj. */
#define H_ERR_PARI         3409 /* Morphology: Wrong number of input
                                   control parameter */
#define H_ERR_PARO         3410 /* Morphology: Wrong number of output
                                   control parameter */
#define H_ERR_SELC         3411 /* Morphology: Struct. element is infinite */
#define H_ERR_WRNSE        3412 /* Morphology: Wrong name for struct. elem. */

/* Runlength encoding, 35xxx */
#define H_ERR_WRRLN1       3500 /* Wrong number of run length rows (chords):
                                   smaller than 0 */
#define H_ERR_WRRLN2       3501 /* Number of chords too big, increase
                                 * current_runlength_number using set_system*/
#define H_ERR_WRRLL        3502 /* Run length row with negative length */
#define H_ERR_RLLTB        3503 /* Run length row >= image height */
#define H_ERR_RLLTS        3504 /* Run length row < 0 */
#define H_ERR_RLCTB        3505 /* Run length column >= image width */
#define H_ERR_RLCTS        3506 /* Lauflaengenspalte < 0 */
#define H_ERR_CHLTB        3507 /* For CHORD_TYPE: Number of row too big */
#define H_ERR_CHLTS        3508 /* For CHORD_TYPE: Number of row too small */
#define H_ERR_CHCTB        3509 /* For CHORD_TYPE: Number of column too big */
#define H_ERR_MRLE         3510 /* Exceeding the maximum number of run lengths
                                   while automatical expansion */
#define H_ERR_ICCOMPL      3511 /* Region->compl neither TRUE/FALSE */
#define H_ERR_RLEMAX       3512 /* Region->max_num < Region->num */
#define H_ERR_WRRLN3       3513 /* Number of chords too big for num_max */
#define H_ERR_OPNOCOMPL    3514 /* Operator cannot be implemented for
                                   complemented regions */

/* Image format */
#define H_ERR_WIMAW1        3520 /* Image width < 0 */
#define H_ERR_WIMAW2        3521 /* Image width >= MAX_FORMAT */
#define H_ERR_WIMAH1        3522 /* Image height <= 0 */
#define H_ERR_WIMAH2        3523 /* Image height >= MAX_FORMAT */
#define H_ERR_WIMAW3        3524 /* Image width <= 0 */
#define H_ERR_WIMAH3        3525 /* Image height <= 0 */
#define H_ERR_TMS           3550 /* Too many segments */
#define H_ERR_NO_INT8_IMAGE 3551 /* INT8 images are available on 64 bit systems
                                    only */


/* Projective transformations */
#define H_ERR_POINT_AT_INFINITY    3600 /* Point at infinity cannot be
                                           converted to a Euclidean point */
#define H_ERR_ML_NO_COVARIANCE     3601 /* Covariance matrix could not be
                                           determined */
#define H_ERR_RANSAC_PRNG          3602 /* RANSAC algorithm didn't find enough
                                           point correspondences */
#define H_ERR_RANSAC_TOO_DIFFERENT 3603 /* RANSAC algorithm didn't find enough
                                           point correspondences */
#define H_ERR_PTI_FALLBACK         3604 /* Internal diagnosis: fallback method
                                           had to be used */
#define H_ERR_PTI_TRAFO_SING       3605 /* Projective transformation is
                                           singular */
#define H_ERR_PTI_MOSAIC_UNDERDET  3606 /* Mosaic is under-determined */

#define H_ERR_COV_NPD              3607 /* Input covariance matrix
                                           is not positive definite */
#define H_ERR_TOO_MANY_POINTS      3608 /* The number of input points
                                           too large. */

/* Self-calibration */
#define H_ERR_INPC         3620 /* Inconsistent number of point
                                   correspondences. */
#define H_ERR_NOPA         3621 /* No path from reference image to one or
                                   more images. */
#define H_ERR_IINE         3622 /* Image with specified index does not
                                   exist. */
#define H_ERR_NOCM         3623 /* Matrix is not a camera matrix. */
#define H_ERR_SKNZ         3624 /* Skew is not zero. */
#define H_ERR_ILFL         3625 /* Illegal focal length. */
#define H_ERR_KANZ         3626 /* Kappa is not zero. */
#define H_ERR_VARA         3627 /* It is not possible to determine all
                                   parameters for in the variable case. */
#define H_ERR_LVDE         3628 /* No valid implementation selected. */
#define H_ERR_KPAR         3629 /* Kappa can only be determined with the
                                   gold-standard method for fixed camera
                                   parameters. */
#define H_ERR_IMOD         3630 /* Conflicting number of images and projection
                                   mode. */
#define H_ERR_PNIC         3631 /* Error in projection: Point not in any cube
                                   map. */
#define H_ERR_NO_SOL       3632 /* No solution found. */
#define H_ERR_TINZ         3633 /* Tilt is not zero. */

/* Adjust mosaic */
#define H_ERR_ILMD         3640 /* Illegal combination of parameters and
                                   estimation method. */

/* Self-calibration of radial distortions */
#define H_ERR_RDS_NSC      3660 /* No suitable contours found */
#define H_ERR_RDS_NSS      3661 /* No stable solution found */
#define H_ERR_RDS_ISS      3662 /* Instable solution found */
#define H_ERR_RDS_NEC      3663 /* Not enough contours for calibration */


/* FFT */
#define H_ERR_NOFFTOPT       3650 /* Invalid file format for FFT
                                     optimization data */
#define H_ERR_WRFFTOPTVERS   3651 /* The version of the FFT optimization
                                     data is not supported */
#define H_ERR_WRHALCONVERS   3652 /* Optimization data was created with a
                                   different HALCON version
                                   (Standard HALCON / Parallel HALCON) */
#define H_ERR_OPTFAIL        3653 /* Storing of the optimization data failed */
#define H_ERR_FFTOPT_NOSITEM 3654 /* Serialized item does not contain valid
                                     FFT optimization data */

/* binocular_disparity */
#define H_ERR_INVLD_DISP_RANGE 3690 /* Invalid disparity range for
                                       binocular_disparity_ms method */

/* Stereo */
#define H_ERR_EPIINIM      3700 /* Epipoles are situated within the image
                                   domain */
#define H_ERR_EPI_FOV      3701 /* Fields of view of both cameras do not
                                   intersect each other */
#define H_ERR_EPI_RECT     3702 /* Rectification impossible */


/* Bead Inpsection */
#define H_ERR_BI_WT_TARGET         3710 /* Wrong type of target_thickness
                                           parameter */
#define H_ERR_BI_WT_THICKNESS      3711 /* Wrong type of thickness_tolerance
                                           parameter */
#define H_ERR_BI_WT_POSITION       3712 /* Wrong type of position_tolerance
                                           parameter */
#define H_ERR_BI_WT_SIGMA          3713 /* Wrong type of sigma parameter */
#define H_ERR_BI_WV_SIGMA          3714 /* Wrong value of sigma parameter */
#define H_ERR_BI_WT_THRESH         3715 /* Wrong type of threshold
                                           parameter */
#define H_ERR_BI_WV_TARGET         3716 /* Wrong value of target_thickness
                                           parameter */
#define H_ERR_BI_WV_THICKNESS      3717 /* Wrong value of thickness_tolerance
                                           parameter */
#define H_ERR_BI_WV_POSITION       3718 /* Wrong value of position_tolerance
                                           parameter */
#define H_ERR_BI_WV_THRESH         3719 /* Wrong value of threshold
                                           parameter */
#define H_ERR_BI_WT_REFINE         3720 /* Wrong type of refinement
                                           parameter */
#define H_ERR_BI_WV_REFINE         3721 /* Wrong value of refinement
                                           parameter */
#define H_ERR_BI_WT_RESOL          3722 /* Wrong type of resolution
                                           parameter */
#define H_ERR_BI_WV_RESOL          3723 /* Wrong type of resolution
                                           parameter */
#define H_ERR_BI_WT_POLARITY       3724 /* Wrong type of polarity
                                           parameter */
#define H_ERR_BI_WV_POLARITY       3725 /* Wrong type of polarity
                                           parameter */


/* Sheet-of-light */
#define H_ERR_SOL_EMPTY_MODEL_LIST 3751 /* No sheet-of-light model available*/
#define H_ERR_SOL_WNIW             3752 /* Wrong input image size (width) */
#define H_ERR_SOL_WNIH             3753 /* Wrong input image size (height) */
#define H_ERR_SOL_WPROF_REG        3754 /* profile region does not fit the
                                           domain of definition of the input
                                           image */
#define H_ERR_SOL_CAL_NONE         3755 /* Calibration extend not set */
#define H_ERR_SOL_UNDEF_DISPARITY  3756 /* Undefined disparity image */
#define H_ERR_SOL_UNDEF_DISPDOMAIN 3757 /* Undefined domain for disparity
                                           image */
#define H_ERR_SOL_UNDEF_CAMPAR     3758 /* Undefined camera parameter */
#define H_ERR_SOL_UNDEF_LPCS       3759 /* Undefined pose of the lightplane */
#define H_ERR_SOL_UNDEF_CCS        3760 /* Undefined pose of the camera
                                           coordinate system */
#define H_ERR_SOL_UNDEF_CCS_2_LPCS 3761 /* Undefined transformation from the
                                           camera to the lightplane
                                           coordinate system */
#define H_ERR_SOL_UNDEF_MOV_POSE   3762 /* Undefined movement pose for xyz
                                           calibration */
#define H_ERR_SOL_WV_SCALE         3763 /* Wrong value of scale parameter */
#define H_ERR_SOL_WV_PAR_NAME      3764 /* Wrong parameter name */
#define H_ERR_SOL_WT_METHOD        3765 /* Wrong type of parameter method */
#define H_ERR_SOL_WT_AMBIGUITY     3766 /* Wrong type of parameter
                                           ambiguity */
#define H_ERR_SOL_WT_SCORE_TYPE    3767 /* Wrong type of parameter score */
#define H_ERR_SOL_WT_CALIBRATION   3768 /* Wrong type of parameter
                                           calibration */
#define H_ERR_SOL_WT_NUM_PROF      3769 /* Wrong type of parameter
                                           number_profiles */
#define H_ERR_SOL_WT_CAM_PAR       3770 /* Wrong type of element in parameter
                                           camera_parameter */
#define H_ERR_SOL_WT_PAR_POSE      3771 /* Wrong type of element in pose */
#define H_ERR_SOL_WV_METHOD        3772 /* Wrong value of parameter method */
#define H_ERR_SOL_WT_THRES         3773 /* Wrong type of parameter min_gray */
#define H_ERR_SOL_WV_AMBIGUITY     3774 /* Wrong value of parameter
                                           ambiguity */
#define H_ERR_SOL_WV_SCORE_TYPE    3775 /* Wrong value of parameter
                                           score_type */
#define H_ERR_SOL_WV_CALIBRATION   3776 /* Wrong value of parameter
                                           calibration */
#define H_ERR_SOL_WV_NUM_PROF      3777 /* Wrong value of parameter
                                           number_profiles */
#define H_ERR_SOL_WV_CAMERA_TYPE   3778 /* Wrong type of camera */
#define H_ERR_SOL_WN_CAM_PAR       3779 /* Wrong number of values of parameter
                                           camera_parameter */
#define H_ERR_SOL_WN_POSE          3780 /* Wrong number of values of pose */
#define H_ERR_SOL_NO_TARGET_FOUND  3781 /* Calibration target not found */
#define H_ERR_SOL_NO_VALID_SOL     3782 /* The calibration algorithm failed to
                                           find a valid solution. */
#define H_ERR_SOL_WT_CALIB_OBJECT  3783 /* Wrong type of parameter
                                           calibration_object */
#define H_ERR_SOL_INVALID_CALIB_OBJECT 3784 /* Invalid calibration object */
#define H_ERR_SOL_NO_CALIB_OBJECT_SET 3785  /* No calibration object set */
#define H_ERR_SOL_WR_FILE_FORMAT 3786       /* Invalid file format for
                                               sheet-of-light model */
#define H_ERR_SOL_WR_FILE_VERS   3787       /* The version of the
                                               sheet-of-light model is not
                                               supported */
#define H_ERR_SOL_CAMPAR_UNSUPPORTED 3788   /* Camera type not supported by
                                               calibrate_sheet_of_light_model*/
/* 3789 Used to be: Not available with calibration object based calibration */
#define H_ERR_SOL_PAR_CALIB 3790            /* Parameter does not match the
                                               set 'calibration' */
#define H_ERR_SOL_WGV_DISP         3791     /* The gray values of the disparity
                                               image do not fit the height of
                                               the camera */

/* Texture Inspection */
#define H_ERR_TI_WRONGMODEL       3800 /* Wrong texture inspection model type*/
#define H_ERR_TI_NOTTRAINED       3801 /* Texture Model is not trained */
#define H_ERR_TI_NOTRAINDATA      3802 /* Texture Model has no training data */
#define H_ERR_TI_NOTRAINFILE      3803 /* Invalid file format for Texture
                                          inspection model */
#define H_ERR_TI_WRTRAINVERS      3804 /* The version of the Texture inspection
                                          model is not supported */
#define H_ERR_TI_WRSMPFORMAT      3805 /* Wrong training sample file format */
#define H_ERR_TI_WRSMPVERS        3806 /* The version of the training sample
                                          file is not supported */
#define H_ERR_TI_WRIMGSIZE        3807 /* At least one of the images is too
                                          small */
#define H_ERR_TI_WRSMPTEXMODEL    3808 /* The samples do not match the current
                                          texture model */
#define H_ERR_NOT_ENOUGH_IMAGES   3809 /* No images within the texture model */

/* Shape-From */
#define H_ERR_SING         3850 /* The light source positions are linearly
                                   dependent */
#define H_ERR_FEWIM        3851 /* No sufficient image indication */
#define H_ERR_ZBR_NOS      3852 /* Internal error: Function has equal signs
                                   in HZBrent */


/* Kalman filter */
#define H_ERR_DIMK         3900 /* Kalman: Dimension n,m or p has got a
                                   undefined value */
#define H_ERR_NOFILE       3901 /* Kalman: File does not exist */
#define H_ERR_FF1          3902 /* Kalman: Error in file (row of dimension) */
#define H_ERR_FF2          3903 /* Kalman: Error in file (row of marking) */
#define H_ERR_FF3          3904 /* Error in file (value is no float) */
#define H_ERR_NO_A         3905 /* Kalman: Matrix A is missing in file */
#define H_ERR_NO_C         3906 /* Kalman: In Datei fehlt Matrix C */
#define H_ERR_NO_Q         3907 /* Kalman: Matrix Q is missing in file */
#define H_ERR_NO_R         3908 /* Kalman: Matrix R is missing in file */
#define H_ERR_NO_GU        3909 /* Kalman: G or u is missing in file */
#define H_ERR_NOTSYMM      3910 /* Kalman: Covariant matrix is not symmetric */
#define H_ERR_SINGU        3911 /* Kalman: Equation system is singular */

/* Structured Light */
#define H_ERR_SLM_NOT_PERSISTENT 3950 /* structured light model is not in
                                         persistent mode */
#define H_ERR_SLM_MSW_TOO_LARGE  3951 /* the min_stripe_width is too large for
                                         the chosen pattern_width or
                                         pattern_height */
#define H_ERR_SLM_SSW_TOO_LARGE  3952 /* the single_stripe_width is too large
                                         for the chosen pattern_width or
                                         pattern_height */
#define H_ERR_SLM_MSW_GT_SSW     3953 /* min_stripe_width has to be smaller
                                         than single_stripe_width. */
#define H_ERR_SLM_SSW_LT_MSW     3954 /* single_stripe_width is too small
                                         for min_stripe_width. */
#define H_ERR_SLM_NOT_PREP       3955 /* The SLM is not prepared for
                                         decoding. */
#define H_ERR_SLM_NO_OBJS        3956 /* The SLM does not contain the queried
                                         object. */
#define H_ERR_SLM_WRVERS         3957 /* The version of the structured light
                                         model is not supported */
#define H_ERR_SLM_WRFILE         3958 /* Invalid file format for a structured light
                                         model */
#define H_ERR_SLM_WRONGPATTERN   3959 /* Wrong pattern type*/
#define H_ERR_SLM_NOT_DECODED    3960 /* The SLM is not decoded. */
#define H_ERR_SLM_WRONGMODEL     3961 /* Wrong model type*/

/* Data Base and Image data management */
#define H_ERR_DBOIT        4050 /* Object is a object tupel */
#define H_ERR_DBOC         4051 /* Object has been deleted already */
#define H_ERR_DBWOID       4052 /* Wrong object-ID */
#define H_ERR_DBTC         4053 /* Object tupel has been deleted already */
#define H_ERR_DBWTID       4054 /* Wrong object tupel-ID */
#define H_ERR_DBTIO        4055 /* Object tupel is a object */
#define H_ERR_DBIDNULL     4056 /* Object-ID is NULL (0) */
#define H_ERR_WDBID        4057 /* Object-ID outside the valid range */
#define H_ERR_DBIC         4058 /* Access to deleted image */
#define H_ERR_DBWIID       4059 /* Access to image with wrong key */
#define H_ERR_DBRC         4060 /* Access to deleted region */
#define H_ERR_DBWRID       4061 /* Access to region with wrong key */
#define H_ERR_WCHAN        4062 /* Wrong value for image channel */
#define H_ERR_DBITL        4063 /* Index too big */
#define H_ERR_DBIUNDEF     4064 /* Index not defined */


/* OpenCL related error messages */
#define H_ERR_NO_OPENCL           4100 /* No OpenCL available */
#define H_ERR_OPENCL_ERROR        4101 /* OpenCL Error occured */
#define H_ERR_NO_COMPUTE_DEVICES  4102 /* No compute devices available */
#define H_ERR_NO_DEVICE_IMPL      4103 /* No device implementation for this
                                          parameter */
#define H_ERR_OUT_OF_DEVICE_MEM   4104 /* Out of device memory */
#define H_ERR_INVALID_SHAPE       4105 /* Invalid work group shape */
#define H_ERR_INVALID_DEVICE      4106 /* Invalid compute device */

/* CUDA/cuDNN releated error messages */
#define H_ERR_CUDA_ERROR                  4200 /* CUDA Error occured */
#define H_ERR_CUDNN_ERROR                 4201 /* cuDNN Error occured */
#define H_ERR_CUBLAS_ERROR                4202 /* cuBLAS Error occured */
#define H_ERR_BATCH_SIZE_NOT_SUPPORTED    4203 /* Set batch_size not
                                                  supported */
#define H_ERR_CUDA_NOT_AVAILABLE          4204 /* CUDA implementations not
                                                  available */
#define H_ERR_CUDNN_UNSUPPORTED_VERSION   4205 /* Unsupported version of cuDNN */
#define H_ERR_CUDNN_FEATURE_NOT_SUPPORTED 4206 /* Requested feature not supported by
                                                  cuDNN */
#define H_ERR_CUDA_DRIVER_VERSION         4207 /* CUDA driver is out-of-date */

/* MKL related error messages */
#define H_ERR_TRAINING_UNSUPPORTED        4301 /* Training is unsupported with
                                                  the selected runtime. Please switch to
                                                  'gpu' runtime. */
#define H_ERR_CPU_INFERENCE_NOT_AVAILABLE 4302 /* CPU based inference is not
                                                  supported on this platform */

#define H_ERR_DNNL_ERROR                4303 /* Error occured in DNNL library */

/* ACL (Arm Compute Library) related error messages */
#define H_ERR_ACL_ERROR                   4400 /* ACL error ocurred */

/* Visualization errors */
#define H_ERR_VISUALIZATION               4500 /* Internal visualization error */
#define H_ERR_COLOR_TYPE_UNEXP            4501 /* Unexpected color type */
#define H_ERR_NUM_COLOR_EXCEEDED          4502 /* Number of color settings exceeded */

/* I/O and window management, 51xx */
#define H_ERR_WSCN         5100 /* Wrong (logical) window number */
#define H_ERR_DSCO         5101 /* Error while opening the window */
#define H_ERR_WWC          5102 /* Wrong window coordinates */
#define H_ERR_NWA          5103 /* It is not possible to open another window */
#define H_ERR_DNA          5104 /* Device resp. operator not available */
#define H_ERR_UCOL         5105 /* Unknown color */
#define H_ERR_NWO          5106 /* No window has been opened for
                                   desired action */
#define H_ERR_WFM          5107 /* Wrong filling mode for regions */
#define H_ERR_WGV          5108 /* Wrong gray value (0..255) */
#define H_ERR_WPV          5109 /* Wrong pixel value */
#define H_ERR_WLW          5110 /* Wrong line width */
#define H_ERR_WCUR         5111 /* Wrong name of cursor */
#define H_ERR_WLUT         5112 /* Wrong color table */
#define H_ERR_WDM          5113 /* Wrong representation mode */
#define H_ERR_WRCO         5114 /* Wrong representation color */
#define H_ERR_WRDM         5115 /* Wrong dither matrix */
#define H_ERR_WRIT         5116 /* Wrong image transformation */
#define H_ERR_IPIT         5117 /* Unsuitable image type for image trafo. */
#define H_ERR_WRZS         5118 /* Wrong zooming factor for image trafo. */
#define H_ERR_WRDS         5119 /* Wrong representation mode */
#define H_ERR_WRDV         5120 /* Wrong code of device */
#define H_ERR_WWINF        5121 /* Wrong number for father window */
#define H_ERR_WDEXT        5122 /* Wrong window size */
#define H_ERR_WWT          5123 /* Wrong window type */
#define H_ERR_WND          5124 /* No current window has been set */
#define H_ERR_WRGB         5125 /* Wrong color combination or range (RGB) */
#define H_ERR_WPNS         5126 /* Wrong number of pixels set */
#define H_ERR_WCM          5127 /* Wrong value for comprise */
#define H_ERR_FNA          5128 /* set_fix with 1/4 image levels and
                                   static not valid */
#define H_ERR_LNFS         5129 /* set_lut not valid in child windows */
#define H_ERR_LOFL         5130 /* Number of concurrent used color tables
                                   is too big */
#define H_ERR_WIDT         5131 /* Wrong device for window dump */
#define H_ERR_WWDS         5132 /* Wrong window size for window dump */
#define H_ERR_NDVS         5133 /* System variable DISPLAY not defined */
#define H_ERR_WBW          5134 /* Wrong thickness for window margin */
#define H_ERR_WDVS         5135 /* System variable DISPLAY has been set
                                   wrong (<host>:0.0) */
#define H_ERR_TMF          5136 /* Too many fonts loaded */
#define H_ERR_WFN          5137 /* Wrong font name */
#define H_ERR_WCP          5138 /* No valid cursor position */
#define H_ERR_NTW          5139 /* Window is not a textual window */
#define H_ERR_NPW          5140 /* Window is not a image window */
#define H_ERR_STL          5141 /* String too long or too high */
#define H_ERR_NSS          5142 /* Too little space in the window rightw. */
#define H_ERR_NMS          5143 /* Window is not suitable for the mouse */
#define H_ERR_DWNA         5144 /* Here Windows on a equal machine is
                                   permitted only */
#define H_ERR_WOM          5145 /* Wrong mode while opening a window */
#define H_ERR_WWM          5146 /* Wrong window mode for operation */
#define H_ERR_LUTF         5147 /* Operation not possible with fixed pixel */
#define H_ERR_LUTN8        5148 /* Color tables for 8 image levels only */
/* pseudo true-color */
#define H_ERR_WTCM         5149 /* Wrong mode for pseudo real colors */
#define H_ERR_WIFTL        5150 /* Wrong pixel value for LUT */
#define H_ERR_WSOI         5151 /* Wrong image size for pseudo real colors */
#define H_ERR_HRLUT        5152 /* Error in procedure HRLUT */
#define H_ERR_WPFSL        5153 /* Wrong number of entries in color table
                                   for set_lut */

#define H_ERR_WPVS         5154 /* Wrong values for image area */
#define H_ERR_WLPN         5155 /* Wrong line pattern */
#define H_ERR_WLPL         5156 /* Wrong number of parameters for
                                   line pattern */
#define H_ERR_WNOC         5157 /* Wrong number of colors */
#define H_ERR_WPST         5158 /* Wrong value for mode of area creation */

#define H_ERR_SWNA         5159 /* Spy window is not set (set_spy) */
#define H_ERR_NSFO         5160 /* No file for spy has been set (set_spy) */
#define H_ERR_WSPN         5161 /* Wrong parameter output depth (set_spy) */

#define H_ERR_WIFFD        5162 /* Wrong window size for window dump */
#define H_ERR_WLUTF        5163 /* Wrong color table:
                                   Wrong file name or query_lut() */
#define H_ERR_WLUTE        5164 /* Wrong color table:
                                   Empty string ? */
#define H_ERR_WLUTD        5165 /* Using this hardware set_lut('default')
                                   is allowed only */

#define H_ERR_CNDP         5166 /* Error while calling online help */

#define H_ERR_LNPR         5167 /* Row can not be projected */
#define H_ERR_NFSC         5168 /* Operation is unsuitable using a computer
                                   with fixed color table */
#define H_ERR_NACD         5169 /* Computer represents gray scales only */

#define H_ERR_LUTO         5170 /* LUT of this display is full */
#define H_ERR_WCC          5171 /* Internal error: wrong color code */
#define H_ERR_WWATTRT      5172 /* Wrong type for window attribute */
#define H_ERR_WWATTRN      5173 /* Wrong name for window attribute */
#define H_ERR_WRSPART      5174 /* negativ height of area (or 0) */
#define H_ERR_WCSPART      5175 /* negativ width of area (or 0) */

/* Window dump */
#define H_ERR_WNCV         5176 /* Window not completely visible */

/* Fonts */
#define H_ERR_FONT_NA      5177 /* Font not allowed for this operation */

/* Threads */
#define H_ERR_WDIFFTH      5178 /* Window was created in different thread */

#define H_ERR_OBJ_ATTACHED 5194 /* Drawing object already attached to another
                                   window */

/* Image windows */
#define H_ERR_CHA3         5180 /* Internal error: only RGB-Mode */
#define H_ERR_NMWA         5181 /* No more (image-)windows available */

/* OpenGL support */
#define H_ERR_DEPTH_NOT_STORED 5179 /* Depth was not stored with window */
#define H_ERR_INDEX_NOT_STORED 5182 /* Object index was not stored with
                                       window */
#define H_ERR_PRIM_NO_POINTS 5183 /* Operator does not support primitives
                                     without point coordinates */
#define H_ERR_REMOTE_DESKTOP_SIZE 5184 /* Maximum image size for Windows Remote
                                          Desktop exceeded */
#define H_ERR_NOGL         5185 /* No OpenGL support available */
#define H_ERR_NODEPTH      5186 /* No depth information available */
#define H_ERR_OGL_ERROR    5187 /* OpenGL error */
#define H_ERR_UNSUPPORTED_FBO 5188 /* Required framebuffer object is
                                      unsupported */
#define H_ERR_OGL_HSR_NOT_SUPPORTED 5189 /* OpenGL accelerated hidden
                                            surface removal not supported on
                                            this machine */

/* window parameters */
#define H_ERR_WP_IWP       5190 /* Invalid window parameter */
#define H_ERR_WP_IWPV      5191 /* Invalid value for window parameter */
#define H_ERR_UMOD         5192 /* Unknown mode */
#define H_ERR_ATTIMG       5193 /* No image attached */

/* 3d navigation */
#define H_ERR_NVG_WM       5195 /* invalid navigation mode */

/* File I/O, 52xx */
#define H_ERR_FINTERN      5196 /* Internal file error */
#define H_ERR_FS           5197 /* Error while file synchronisation */
#define H_ERR_FISR         5198 /* insufficient rights */
#define H_ERR_BFD          5199 /* Bad file descriptor */
#define H_ERR_FNF          5200 /* File not found */
#define H_ERR_DWI          5201 /* Error while writing image data
                                   (sufficient memory ?) */
#define H_ERR_DWID         5202 /* Error while writing image descriptor
                                   (sufficient memory ?) */
#define H_ERR_DRI1         5203 /* Error while reading image data
                                   (format of image too small ?) */
#define H_ERR_DRI2         5204 /* Error while reading image data
                                   (format of image too big ?) */
#define H_ERR_DRID1        5205 /* Error while reading image descriptor:
                                   File too small */
#define H_ERR_DIMMAT       5206 /* Image matrices are different */
#define H_ERR_HNF          5207 /* Help file not found (setenv HALCONROOT) */
#define H_ERR_XNF          5208 /* Help index not found (setenv HALCONROOT) */
#define H_ERR_CNCSI        5209 /* File <standard_input> can not be closed */
#define H_ERR_CNCSO        5210 /* <standard_output/error> can not be closed */
#define H_ERR_CNCF         5211 /* File can not be closed */
#define H_ERR_EDWF         5212 /* Error while writing to file */
#define H_ERR_NFA          5213 /* Exceeding of maximum number of files */
#define H_ERR_WFIN         5214 /* Wrong file name */
#define H_ERR_CNOF         5215 /* Error while opening the file */
#define H_ERR_WFMO         5216 /* Wrong file mode */
#define H_ERR_WPTY         5217 /* Wrong type for pixel (e.g. byte) */
#define H_ERR_WIW          5218 /* Wrong image width (too big ?) */
#define H_ERR_WIH          5219 /* Wrong image height (too big ?) */
#define H_ERR_FTS1         5220 /* File already exhausted before reading
                                   an image */
#define H_ERR_FTS2         5221 /* File exhausted before terminating
                                   the image */
#define H_ERR_WDPI         5222 /* Wrong value for resolution (dpi) */
#define H_ERR_WNOW         5223 /* Wrong output image size (width) */
#define H_ERR_WNOH         5224 /* Wrong output image size (height) */
#define H_ERR_WNFP         5225 /* Wrong number of parameter values:
                                   Format description */
#define H_ERR_WPNA         5226 /* Wrong parameter name for operator */
#define H_ERR_WSNA         5227 /* Wrong slot name for parameter */
#define H_ERR_NPCF         5228 /* Operator class is missing in help file */
#define H_ERR_WHIF         5229 /* Wrong or inconsistent help/ *.idx
                                   or help/ *.sta */
#define H_ERR_HINF         5230 /* File help/ *.idx not found */
#define H_ERR_HSNF         5231 /* File help/ *.sta not found */
#define H_ERR_ICSF         5232 /* Inconsistent file help/ *.sta */
#define H_ERR_EFNF         5233 /* No explication file (.exp) found */
#define H_ERR_NFWKEF       5234 /* No file found in known graphic format */
#define H_ERR_WIFT         5235 /* Wrong graphic format */
#define H_ERR_ICNF         5236 /* Inconsistent file halcon.num */
#define H_ERR_WTIFF        5237 /* File with extension 'tiff' is no
                                   Tiff-file */
#define H_ERR_WFF          5238 /* Wrong file format */
#define H_ERR_NOGPPROC     5239 /* gnuplot could not be started */
#define H_ERR_NOGPFILE     5240 /* Output file for gnuplot could not be
                                   opened */
#define H_ERR_NOGPOUT      5241 /* Not a valid gnuplot output stream */
#define H_ERR_NOPNM        5242 /* No PNM format */
#define H_ERR_ICODB        5243 /* Inconsistent or old help file */
#define H_ERR_INVAL_FILE_ENC 5244 /* Invalid file encoding */

#define H_ERR_FNO          5245 /* File not open */
#define H_ERR_NO_FILES     5246 /* No files in use so far (none opened) */
#define H_ERR_NORFILE      5247 /* Invalid file format for regions */
#define H_ERR_RDTB         5248 /* Error while reading region data:
                                   Format of region too big. */
#define H_ERR_BINFILE_ENC  5249 /* Encoding for binary files not allowed */
#define H_ERR_EDRF         5250 /* Error reading file */

/* Serial interface */
#define H_ERR_SNO          5251 /* Serial port not open */
#define H_ERR_NSA          5252 /* No serial port available */
#define H_ERR_CNOS         5253 /* Could not open serial port */
#define H_ERR_CNCS         5254 /* Could not close serial port */
#define H_ERR_CNGSA        5255 /* Could not get serial port attributes */
#define H_ERR_CNSSA        5256 /* Could not set serial port attributes */
#define H_ERR_WRSBR        5257 /* Wrong baud rate for serial connection */
#define H_ERR_WRSDB        5258 /* Wrong number of data bits for
                                   serial connection */
#define H_ERR_WRSFC        5259 /* Wrong flow control for serial connection */
#define H_ERR_CNFS         5260 /* Could not flush serial port */
#define H_ERR_EDWS         5261 /* Error during write to serial port */
#define H_ERR_EDRS         5262 /* Error during read from serial port */

#define H_ERR_REG_NOSITEM  5270 /* Serialized item does not contain
                                   valid regions. */
#define H_ERR_REG_WRVERS   5271 /* The version of the regions is
                                   not supported. */
#define H_ERR_IMG_NOSITEM  5272 /* Serialized item does not contain
                                   valid images. */
#define H_ERR_IMG_WRVERS   5273 /* The version of the images is
                                   not supported. */
#define H_ERR_XLD_NOSITEM  5274 /* Serialized item does not contain
                                   valid XLD objects. */
#define H_ERR_XLD_WRVERS   5275 /* The version of the XLD objects is
                                   not supported. */
#define H_ERR_OBJ_NOSITEM  5276 /* Serialized item does not contain
                                   valid objects. */
#define H_ERR_OBJ_WRVERS   5277 /* The version of the objects is
                                   not supported. */
#define H_ERR_XLD_DATA_TOO_LARGE   5678 /* XLD object data can only be read by
                                           HALCON XL */
#define H_ERR_OBJ_UNEXPECTED   5279 /* Unexpected object detected */


/* File I/O, 52xx (continue) */
#define H_ERR_FNOTF        5280 /* File has not been opened in text format */
#define H_ERR_FNOBF        5281 /* File has not been opened in binary file
                                   format */
#define H_ERR_DIRCR        5282 /* Cannot create directory */
#define H_ERR_DIRRM        5283 /* Cannot remove directory */
#define H_ERR_GETCWD       5284 /* Cannot get current directory */
#define H_ERR_SETCWD       5285 /* Cannot set current directory */

#define H_ERR_XINIT        5286 /* Need to call XInitThreads() */

/* Frame grabber / Image acquisition devices */
#define H_ERR_NFS          5300 /* No image acquisition device opened */
#define H_ERR_FGWC         5301 /* IA: wrong color depth */
#define H_ERR_FGWD         5302 /* IA: wrong device */
#define H_ERR_FGVF         5303 /* IA: determination of video format
                                   not possible */
#define H_ERR_FGNV         5304 /* IA: no video signal */
#define H_ERR_UFG          5305 /* Unknown image acquisition device */
#define H_ERR_FGF          5306 /* IA: failed grabbing of an image */
#define H_ERR_FGWR         5307 /* IA: wrong resolution chosen */
#define H_ERR_FGWP         5308 /* IA: wrong image part chosen */
#define H_ERR_FGWPR        5309 /* IA: wrong pixel ratio chosen */
#define H_ERR_FGWH         5310 /* IA: handle not valid */
#define H_ERR_FGCL         5311 /* IA: instance not valid (already closed?) */
#define H_ERR_FGNI         5312 /* Image acquisition device could not be
                                   initialized */
#define H_ERR_FGET         5313 /* IA: external triggering not supported */
#define H_ERR_FGLI         5314 /* IA: wrong camera input line (multiplex) */
#define H_ERR_FGCS         5315 /* IA: wrong color space */
#define H_ERR_FGPT         5316 /* IA: wrong port */
#define H_ERR_FGCT         5317 /* IA: wrong camera type */
#define H_ERR_FGTM         5318 /* IA: maximum number of acquisition device
                                   classes exceeded */
#define H_ERR_FGDV         5319 /* IA: device busy */
#define H_ERR_FGASYNC      5320 /* IA: asynchronous grab not supported */
#define H_ERR_FGPARAM      5321 /* IA: unsupported parameter */
#define H_ERR_FGTIMEOUT    5322 /* IA: timeout */
#define H_ERR_FGGAIN       5323 /* IA: invalid gain  */
#define H_ERR_FGFIELD      5324 /* IA: invalid field */
#define H_ERR_FGPART       5325 /* IA: invalid parameter type */
#define H_ERR_FGPARV       5326 /* IA: invalid parameter value */
#define H_ERR_FGFNS        5327 /* IA: function not supported */
#define H_ERR_FGIVERS      5328 /* IA: incompatible interface version */
#define H_ERR_FGSETPAR     5329 /* IA: could not set parameter value */
#define H_ERR_FGGETPAR     5330 /* IA: could not query parameter setting */
#define H_ERR_FGPARNA      5331 /* IA: parameter not available in current
                                   configuration */
#define H_ERR_FGCLOSE      5332 /* IA: device could not be closed properly */
#define H_ERR_FGCAMFILE    5333 /* IA: camera configuration file could not be
                                   opened */
#define H_ERR_FGCALLBACK   5334 /* IA: unsupported callback type */
#define H_ERR_FGDEVLOST    5335 /* IA: device lost */
#define H_ERR_FGABORTED    5336 /* IA: grab aborted */

/* digital io devices */
#define H_ERR_IOTIMEOUT    5350 /* IO: timeout */
#define H_ERR_IOIVERS      5351 /* IO: incompatible interface version */
#define H_ERR_IOWH         5352 /* IO: handle not valid */
#define H_ERR_IODBUSY      5353 /* IO: device busy */
#define H_ERR_IOIAR        5354 /* IO: insufficient user rights */
#define H_ERR_IONF         5355 /* IO: device or channel not found */
#define H_ERR_IOPART       5356 /* IO: invalid parameter type */
#define H_ERR_IOPARV       5357 /* IO: invalid parameter value */
#define H_ERR_IOPARNUM     5358 /* IO: invalid parameter number */
#define H_ERR_IOPARAM      5359 /* IO: unsupported parameter */
#define H_ERR_IOPARNA      5360 /* IO: parameter not available in curr
                                       config.*/
#define H_ERR_IOFNS        5361 /* IO: function not supported */
#define H_ERR_IOME         5362 /* IO: maximum number of dio classes exceeded*/
#define H_ERR_IODNA        5363 /* IO: driver of io device not available */
#define H_ERR_IOABORTED    5364 /* IO: operation aborted */
#define H_ERR_IODATT       5365 /* IO: invalid data type */
#define H_ERR_IODEVLOST    5366 /* IO: device lost */
#define H_ERR_IOSETPAR     5367 /* IO: could not set parameter value */
#define H_ERR_IOGETPAR     5368 /* IO: could not query parameter setting */
#define H_ERR_IOCLOSE      5369 /* IO: device could not be closed properly */

/* Images from file */

/* JpegXR files */
#define H_ERR_JXR_UNSUPPORTED_FORMAT         5400 /* Image type is not
                                                     supported */
#define H_ERR_JXR_INVALID_PIXEL_FORMAT       5401 /* Invalid pixel format
                                                     passed to filter
                                                     function */
#define H_ERR_JXR_INTERNAL_ERROR             5402 /* Internal JpegXR error. */
#define H_ERR_JXR_FORMAT_SYNTAX_ERROR        5403 /* Syntax error in output
                                                     format string */
#define H_ERR_JXR_TOO_MANY_CHANNELS          5404 /* Maximum number of channels
                                                     exceeded */
#define H_ERR_JXR_EC_ERROR                   5405 /* Unspecified error in JXR
                                                     library */
#define H_ERR_JXR_EC_BADMAGIC                5406 /* Bad magic number in JXR
                                                     library */
#define H_ERR_JXR_EC_FEATURE_NOT_IMPLEMENTED 5407 /* Feature not implemented in
                                                     JXR library */
#define H_ERR_JXR_EC_IO                      5408 /* File read/write error in
                                                     JXR library */
#define H_ERR_JXR_EC_BADFORMAT               5409 /* Bad file format in JXR
                                                     library */

/* General */
#define H_ERR_LIB_FILE_CLOSE          5500 /* Error while closing the
                                              image file */
#define H_ERR_LIB_FILE_OPEN           5501 /* Error while opening the
                                              image file */
#define H_ERR_LIB_UNEXPECTED_EOF      5502 /* Premature end of the
                                              image file */
#define H_ERR_IDTL                    5503 /* Image dimensions too large for
                                              this file format */
#define H_ERR_ITLHV                   5504 /* Image too large for this HALCON
                                              version */
#define H_ERR_TMIO                    5505 /* Too many iconic objects for
                                              this file format */
#define H_ERR_FILE_FORMAT_UNSUPPORTED 5506 /* File format is unsupported */

/* PCX files */
#define H_ERR_PCX_NO_PCX_FILE         5510 /* File is no PCX-File */
#define H_ERR_PCX_UNKNOWN_ENCODING    5511 /* Unknown encoding */
#define H_ERR_PCX_MORE_THAN_4_PLANES  5512 /* More than 4 image plains */
#define H_ERR_PCX_COLORMAP_SIGNATURE  5513 /* Wrong magic in color table */
#define H_ERR_PCX_REPEAT_COUNT_SPANS  5514 /* Wrong number of bytes in span */
#define H_ERR_PCX_TOO_MUCH_BITS_PIXEL 5515 /* Wrong number of bits/pixels */
#define H_ERR_PCX_PACKED_PIXELS       5516 /* Wrong number of plains */

/* GIF files */
#define H_ERR_GIF_NO_GIF_PICTURE      5520 /* File is no GIF-File */
#define H_ERR_GIF_BAD_VERSION         5521 /* GIF: Wrong version */
#define H_ERR_GIF_SCREEN_DESCRIPTOR   5522 /* GIF: Wrong descriptor */
#define H_ERR_GIF_COLORMAP            5523 /* GIF: Wrong color table */
#define H_ERR_GIF_READ_ERROR_EOF      5524 /* GIF: Premature end of file */
#define H_ERR_GIF_NOT_ENOUGH_IMAGES   5525 /* GIF: Wrong number of images */
#define H_ERR_GIF_ERROR_ON_EXTENSION  5526 /* GIF: Wrong image extension */
#define H_ERR_GIF_LEFT_TOP_WIDTH      5527 /* GIF: Wrong left top width */
#define H_ERR_GIF_CIRCULAR_TABL_ENTRY 5528 /* GIF: Cyclic index of table */
#define H_ERR_GIF_BAD_IMAGE_DATA      5529 /* GIF: Wrong image data */

/* SUN-Raster files  */
#define H_ERR_SUN_RASTERFILE_TYPE     5530 /* File is no Sun-Raster-File */
#define H_ERR_SUN_RASTERFILE_HEADER   5531 /* Wrong header */
#define H_ERR_SUN_COLS                5532 /* Wrong image width */
#define H_ERR_SUN_ROWS                5533 /* Wrong image height */
#define H_ERR_SUN_COLORMAP            5534 /* Wrong color map */
#define H_ERR_SUN_RASTERFILE_IMAGE    5535 /* Wrong image data */
#define H_ERR_SUN_IMPOSSIBLE_DATA     5536 /* Wrong type of pixel */

/* XWD files */
#define H_ERR_XWD_IMPOSSIBLE_DATA     5540  /* Wrong type of pixel */
#define H_ERR_XWD_VISUAL_CLASS        5541  /* Wrong visual class */
#define H_ERR_XWD_X10_HEADER          5542  /* Wrong X10 header */
#define H_ERR_XWD_X11_HEADER          5543  /* Wrong X11 header */
#define H_ERR_XWD_X10_COLORMAP        5544  /* Wrong X10 colormap */
#define H_ERR_XWD_X11_COLORMAP        5545  /* Wrong X11 colormap */
#define H_ERR_XWD_X11_PIXMAP          5546  /* Wrong pixmap */
#define H_ERR_XWD_UNKNOWN_VERSION     5547  /* Unknown version */
#define H_ERR_XWD_READING_IMAGE       5548  /* Error while reading an image */

/* TIFF files */
#define H_ERR_TIF_BAD_INPUTDATA      5550 /* Error while reading a file */
#define H_ERR_TIF_COLORMAP           5551 /* Wrong colormap */
#define H_ERR_TIF_TOO_MANY_COLORS    5552 /* Too many colors */
#define H_ERR_TIF_BAD_PHOTOMETRIC    5553 /* Wrong photometric interpretation*/
#define H_ERR_TIF_PHOTOMETRIC_DEPTH  5554 /* Wrong photometric depth */
#define H_ERR_TIF_NO_REGION          5555 /* Image is no binary file */
#define H_ERR_TIF_UNSUPPORTED_FORMAT 5556 /* Unsupported TIFF format */
#define H_ERR_TIF_BAD_SPECIFICATION  5557 /* Wrong file format specification */
#define H_ERR_TIF_FILE_CORRUPT       5558 /* TIFF file is corrupt */
#define H_ERR_TIF_TAG_UNDEFINED      5559 /* Required TIFF tag is missing */

/* BMP files */
#define H_ERR_BMP_NO_BMP_PICTURE      5560  /* File is no BMP-File */
#define H_ERR_BMP_READ_ERROR_EOF      5561  /* Premature end of file */
#define H_ERR_BMP_INCOMPLETE_HEADER   5562  /* Incomplete header */
#define H_ERR_BMP_UNKNOWN_FORMAT      5563  /* Unknown bitmap format */
#define H_ERR_BMP_UNKNOWN_COMPRESSION 5564  /* Unknown compression format */
#define H_ERR_BMP_COLORMAP            5565  /* Wrong color table */
#define H_ERR_BMP_WRITE_ERROR         5566  /* Write error on output */
#define H_ERR_BMP_NO_REGION           5567  /* File does not contain a
                                               binary image */

/* Jpeg files */
#define H_ERR_JPG_COMP_NUM     5570 /* Wrong number of components in image */
#define H_ERR_JPGLIB_UNKNOWN   5571 /* Unknown error from libjpeg */
#define H_ERR_JPGLIB_NOTIMPL   5572 /* Not implemented feature in libjpeg */
#define H_ERR_JPGLIB_FILE      5573 /* File access error in libjpeg */
#define H_ERR_JPGLIB_TMPFILE   5574 /* Tmp file access error in libjpeg */
#define H_ERR_JPGLIB_MEMORY    5575 /* Memory error in libjpeg */
#define H_ERR_JPGLIB_INFORMAT  5576 /* Error in input image */

/* PNG files */
#define H_ERR_PNG_NO_PNG_FILE            5580  /* File is not a PNG file */
#define H_ERR_PNG_UNKNOWN_INTERLACE_TYPE 5581  /* Unknown interlace type */
#define H_ERR_PNG_UNSUPPORTED_COLOR_TYPE 5582  /* Unsupported color type */
#define H_ERR_PNG_NO_REGION              5583  /* Image is no binary file */
#define H_ERR_PNG_SIZE_TOO_BIG           5584  /* Image size too big */

/* TIFF files extension: no more code availables after 5559 */
#define H_ERR_TIF_TAG_ACCESS 5587      /* Error accessing TIFF tag */
#define H_ERR_TIF_TAG_DATATYPE 5588    /* Invalid TIFF tag value datatype */
#define H_ERR_TIF_TAG_UNSUPPORTED 5589 /* Unsupported TIFF tag requested */

/* Jpeg-2000 files */
#define H_ERR_JP2_CORRUPT        5590 /* File corrupt */
#define H_ERR_JP2_PREC_TOO_HIGH  5591 /* Image precision too high */
#define H_ERR_JP2_ENCODING_ERROR 5592 /* Error while encoding */
#define H_ERR_JP2_SIZE_TOO_BIG   5593 /* Image size too big */

/* HOBJ files */
#define H_ERR_HOBJ_NOT_ONLY_IMAGES 5599 /* File does not contain only images */


/* Socket communication and virtual links */
#define H_ERR_SOCKET_BLOCK                5600 /* Socket can not be set to
                                                  block */
#define H_ERR_SOCKET_UNBLOCK              5601 /* Socket can not be set to
                                                  unblock */
#define H_ERR_SOCKET_NO_CPAR              5602 /* Received data is no tuple */
#define H_ERR_SOCKET_NO_IMAGE             5603 /* Received data is no image */
#define H_ERR_SOCKET_NO_RL                5604 /* Received data is no region */
#define H_ERR_SOCKET_NO_XLD               5605 /* Received data is no
                                                  xld object */
#define H_ERR_SOCKET_READ_DATA_FAILED     5606 /* Error while reading
                                                  from socket */
#define H_ERR_SOCKET_WRITE_DATA_FAILED    5607 /* Error while writing
                                                  to socket */
#define H_ERR_SOCKET_WRONG_BYTE_NUMBER    5608 /* Illegal number of bytes
                                                  with get_rl */
#define H_ERR_SOCKET_BUFFER_OVERFLOW      5609 /* Buffer overflow in
                                                  read_data */
#define H_ERR_SOCKET_CANT_ASSIGN_FD       5610 /* Socket can not be created */
#define H_ERR_SOCKET_CANT_BIND            5611 /* Bind on socket failed */
#define H_ERR_SOCKET_CANT_GET_PORTNUMBER  5612 /* Socket information is not
                                                  available */
#define H_ERR_SOCKET_CANT_LISTEN          5613 /* Socket cannot listen for
                                                  incoming connections */
#define H_ERR_SOCKET_CANT_ACCEPT          5614 /* Connection could not be
                                                  accepted */
#define H_ERR_SOCKET_CANT_CONNECT         5615 /* Connection request failed */
#define H_ERR_SOCKET_GETHOSTBYNAME        5616 /* Hostname could not be
                                                  resolved */
#define H_ERR_SOCKET_ILLEGAL_TUPLE_TYPE   5618 /* Unknown tuple type on
                                                  socket */
#define H_ERR_SOCKET_TIMEOUT              5619 /* Timeout occured on socket */
#define H_ERR_SOCKET_NA                   5620 /* No more sockets available */
#define H_ERR_SOCKET_NI                   5621 /* Socket is not initialized */
#define H_ERR_SOCKET_OOR                  5622 /* Invalid socket */
#define H_ERR_SOCKET_IS                   5623 /* Socket is NULL */
#define H_ERR_SOCKET_DATA_TOO_LARGE       5624 /* Received data type is too
                                                  large */
#define H_ERR_SOCKET_WRONG_TYPE           5625 /* Wrong socket type. */
#define H_ERR_SOCKET_NO_PACKED_DATA       5626 /* Received data is not packed.
                                                  */
#define H_ERR_SOCKET_PARAM_FAILED         5627 /* Socket parameter operation
                                                  failed. */
#define H_ERR_SOCKET_FORMAT_MISMATCH      5628 /* The data does not match the
                                                  format specification. */
#define H_ERR_SOCKET_INVALID_FORMAT       5629 /* Invalid format
                                                  specification. */
#define H_ERR_SOCKET_NO_SERIALIZED_ITEM   5630 /* Received data is no
                                                  serialized item */

#define H_ERR_ARCINFO_TOO_MANY_XLDS       5700 /* Too many contours/polygons
                                                  for this file format */

/* Serialize/Deserialize */
#define H_ERR_QUAT_WRONG_VERSION      5750 /* The version of the quaternion
                                              is not supported */
#define H_ERR_QUAT_NOSITEM            5751 /* Serialized item does not contain
                                              a valid quaternion*/
#define H_ERR_HOM_MAT2D_WRONG_VERSION 5752 /* The version of the homogeneous
                                              matrix is not supported */
#define H_ERR_HOM_MAT2D_NOSITEM       5753 /* Serialized item does not contain
                                              a valid homogeneous matrix */
#define H_ERR_HOM_MAT3D_WRONG_VERSION 5754 /* The version of the homogeneous
                                              3D matrix is not supported */
#define H_ERR_HOM_MAT3D_NOSITEM       5755 /* Serialized item does not contain
                                              a valid homogeneous 3D matrix */
#define H_ERR_TUPLE_WRONG_VERSION     5756 /* The version of the tuple
                                              is not supported */
#define H_ERR_TUPLE_NOSITEM           5757 /* Serialized item does not
                                              contain a valid tuple */
#define H_ERR_TUPLE_DTLFTHV           5758 /* Tuple data can only be read on
                                              64-bit systems */
#define H_ERR_POSE_WRONG_VERSION      5759 /* The version of the camera
                                              parameters (pose) is not
                                              supported */
#define H_ERR_POSE_NOSITEM            5760 /* Serialized item does not contain
                                              valid camera parameters (pose) */
#define H_ERR_CAM_PAR_WRONG_VERSION   5761 /* The version of the internal
                                              camera parameters is not
                                              supported */
#define H_ERR_CAM_PAR_NOSITEM         5762 /* Serialized item does not contain
                                              valid internal camera parameters
                                              */
#define H_ERR_DUAL_QUAT_WRONG_VERSION 5763 /* The version of the dual
                                              quaternion is not supported */
#define H_ERR_DUAL_QUAT_NOSITEM       5764 /* Serialized item does not contain
                                              a valid dual quaternion*/

/* Memory management */
#define H_ERR_NP           6000 /* Access to undefined memory area */
#define H_ERR_MEM          6001 /* Not enough memory available */
#define H_ERR_ICM          6002 /* Memory partition on heap has been
                                   overwritten */
#define H_ERR_WMS          6003 /* HAlloc: 0 bytes requested */
#define H_ERR_NOTMP        6004 /* Tmp-memory management:
                                   Call freeing memory although nothing had
                                   been allocated */
#define H_ERR_TMPNULL      6005 /* Tmp-memory management:
                                   Null pointer while freeing */
#define H_ERR_CNFMEM       6006 /* Tmp-memory management:
                                   Could not find memory element */
#define H_ERR_WMT          6007 /* memory management: wrong memory type */

#define H_ERR_MEM_VID      6021 /* Not enough video memory available */

#define H_ERR_NRA          6041 /* No memory block allocated at last */
#define H_ERR_IAD          6040 /* System parameter for memory-allocation
                                   inconsistent */

#define H_ERR_INVALID_ALIGN 6042 /* Invalid alignement */


/* System */
#define H_ERR_CP_FAILED    6500 /* Process creation failed */

/* Language interfaces */
/* General  */
#define H_ERR_WOCPI        7000 /* Wrong index for output control par. */
#define H_ERR_WOCPVN       7001 /* Wrong number of values:
                                   Output control parameter */
#define H_ERR_WOCPT        7002 /* Wrong type: Output control parameter */
#define H_ERR_WKT          7003 /* Wrong data type for object key
                                   (input objects) */
#define H_ERR_IOOR         7004 /* Range for integer had been passed */
#define H_ERR_IHV          7005 /* Inconsistent Halcon version */
#define H_ERR_NISS         7006 /* Not enough memory for strings allocated */
#define H_ERR_PROC_NULL    7007 /* Internal error: Proc is NULL */
#define H_ERR_UNKN         7105 /* Unknown symbolic object key (input obj.) */
#define H_ERR_WOON         7200 /* Wrong number of output object parameter */

/* C */
#define H_ERR_OTSE         7400 /* Output type <string> expected */
#define H_ERR_OTLE         7401 /* Output type <long> expected */
#define H_ERR_OTFE         7402 /* Output type <float> expected */
#define H_ERR_OPINP        7403 /* Object parameter is a zero pointer */
#define H_ERR_TWC          7404 /* Tupel had been deleted; values are not
                                   valid any more */
/* CNNs */
#define H_ERR_CNN_DATA               7701 /* CNN: Internal data error */
#define H_ERR_CNN_MEM                7702 /* CNN: Invalid memory type */
#define H_ERR_CNN_IO_INVALID         7703 /* CNN: Invalid data
                                             serialization */
#define H_ERR_CNN_IMPL_NOT_AVAILABLE 7704 /* CNN: Implementation not
                                             available */
#define H_ERR_CNN_NUM_INPUTS_INVALID 7705 /* CNN: Wrong number of input data */

#define H_ERR_CNN_IMPL_INVALID       7706 /* CNN: Invalid implementation type
                                           */
#define H_ERR_CNN_TRAINING_NOT_SUP   7707 /* CNN: Training is not supported in
                                             the current environment. */

#define H_ERR_CNN_GPU_REQUIRED       7708 /* For this operation a GPU with
                                             certain minimal requirements is
                                             required. See installation guide
                                             for details. */
#define H_ERR_CNN_CUDA_LIBS_MISSING  7709 /* For this operation the CUDA
                                             library needs to be available.
                                             (See installation guide for
                                             details.) */
#define H_ERR_OCR_CNN_RE             7710 /* OCR File: Error while reading
                                             classifier */
#define H_ERR_OCR_CNN_WGPN           7711 /* Wrong generic parameter name */
#define H_ERR_OCR_CNN_EXCLUSIV_PARAM 7712 /* One of the parameters returns
                                             several values and has to be used
                                             exclusively */
#define H_ERR_CNN_WGPN               7713 /* Wrong generic parameter name */

#define H_ERR_CNN_INVALID_LABELS     7714 /* Invalid labels. */
#define H_ERR_OCR_CNN_FILE_WRONG_VERSION  7715 /*OCR File: Wrong file version*/
#define H_ERR_CNN_MULTIPLE_CLASSES   7716 /* Invalid classes: At least one
                                             class apears twice */
#define H_ERR_CNN_CUBLAS_LIBS_MISSING 7717 /* For this operation the cuBLAS
                                             library needs to be available.
                                             (See installation guide for
                                             details.) */
#define H_ERR_CNN_CUDNN_LIBS_MISSING  7718  /* For this operation the CUDNN
                                             library needs to be available.
                                             (See installation guide for
                                             details.) */
#define H_ERR_OCR_FNF_FIND_TEXT_SUPPORT  7719 /* File 'find_text_support.hotc'
                                                 not found (please place this
                                                 file in the ocr subdirectory
                                                 of the root directory of your
                                                 HALCON installation or in the
                                                 current working directory) */
#define H_ERR_CNN_TRAINING_FAILED     7720 /* Training step failed. This
                                              might be caused by unsuitable
                                              training parameters */
#define H_ERR_CNN_NO_PRETRAINED_WEIGHTS   7721 /* Weights in Graph have been
                                                  overwritten previously
                                                  and are lost. */
#define H_ERR_CNN_INVALID_INPUT_SIZE     7722 /* New input size is too small
                                                 to produce meaningful
                                                 features */
#define H_ERR_CNN_RESULT_NOT_AVAILABLE   7723 /* Result is not available. */
#define H_ERR_CNN_INVALID_INPUT_DEPTH    7724 /* New number of channels must be
                                                 either 1 or 3. */
#define H_ERR_CNN_DEPTH_NOT_AVAILABLE    7725 /* New input number of channels
                                                 can't be set to 3 if network
                                                 is specified for number of
                                                 channels 1 */
#define H_ERR_CNN_INVALID_BATCH_SIZE     7726 /* Device batch size larger than
                                                 batch size. */
#define H_ERR_CNN_INVALID_PARAM_SPEC     7727 /* Invalid specification of a
                                                 parameter. */
#define H_ERR_CNN_EXCEEDS_MAX_MEM        7728 /* Memory size exceeds maximal
                                                 allowed value. */
#define H_ERR_CNN_BATCH_SIZE_OVERFLOW    7729 /* New batch size causes integer
                                                 overflow */
#define H_ERR_CNN_INVALID_IMAGE_SIZE     7730 /* Invalid input image size for
                                                 detection model */
#define H_ERR_CNN_INVALID_LAYER_PARAM_VALUE 7731 /* Invalid parameter value
                                                    for current layer */
#define H_ERR_CNN_INVALID_LAYER_PARAM_NUM   7732 /* Invalid parameter num
                                                    for current layer */
#define H_ERR_CNN_INVALID_LAYER_PARAM_TYPE  7733 /* Invalid parameter type
                                                    for current layer */
#define H_ERR_CNN_NUM_OUTPUTS_INVALID 7734 /* CNN: Wrong number of output data
                                            */
#define H_ERR_CNN_INVALID_SHAPE       7735 /* CNN: Invalid input shape */
#define H_ERR_CNN_IO_INVALID_LAYER_TYPE 7740 /* CNN: Invalid layer type
                                                serialization */
#define H_ERR_CNN_INFERENCE_FAILED 7741 /* CNN: Inference failed */

/* Graphs */
#define H_ERR_GRAPH_INTERNAL         7751 /* Graph: Internal error */
#define H_ERR_GRAPH_IO_INVALID       7752 /* Graph: Invalid data serialization
                                           */
#define H_ERR_GRAPH_INVALID_INDEX    7753 /* Graph: Invalid index */

/* CNN graphs */
#define H_ERR_CNNGRAPH_INTERNAL       7760 /* HCNNGraph: Internal error */
#define H_ERR_CNNGRAPH_IO_INVALID     7761 /* HCNNGraph: Invalid data
                                              serialization */
#define H_ERR_CNNGRAPH_LAYER_INVALID  7762 /* HCNNGraph: Invalid layer
                                              specification */
#define H_ERR_CNNGRAPH_NOINIT         7763 /* HCNNGraph: Graph not properly
                                              initialized */
#define H_ERR_CNNGRAPH_INVALID_MEM    7764 /* CNN-Graph: Invalid memory type */
#define H_ERR_CNNGRAPH_INVALID_NUML   7765 /* CNN-Graph: Invalid number of
                                              layers */
#define H_ERR_CNNGRAPH_INVALID_IDX    7766 /* CNN-Graph: Invalid index */
#define H_ERR_CNNGRAPH_SPEC_STATUS    7767 /* CNN-Graph: Invalid specification
                                              status */
#define H_ERR_CNNGRAPH_NOCHANGE       7768 /* CNN-Graph: Graph is not allowed
                                              to be changed after
                                              initialization */
#define H_ERR_CNNGRAPH_PREPROC        7769 /* CNN-Graph: Missing preprocessing
                                            */
#define H_ERR_CNNGRAPH_DEGREE         7770 /* CNN-Graph: Invalid vertex degree
                                            */
#define H_ERR_CNNGRAPH_OUTSHAPE       7771 /* CNN-Graph: Invalid output shape
                                            */
#define H_ERR_CNNGRAPH_SPEC           7772 /* CNN-Graph: Invalid specification
                                            */
#define H_ERR_CNNGRAPH_DEF            7773 /* CNN-Graph: Invalid graph
                                              definition */

#define H_ERR_CNNGRAPH_NO_CLASS_CHANGE  7774 /* CNN-Graph: Architecture not
                                                suitable for the adaption of
                                                the number of output classes */

#define H_ERR_CNNGRAPH_NO_IMAGE_RESIZE  7775 /* CNN-Graph: Architecture not
                                                suitable for the adaption of
                                                the image size" */
#define H_ERR_CNNGRAPH_AUX_INDEX_OOB  7776 /* CNN-Graph: Aux index out of
                                              bounds.
                                              */
#define H_ERR_CNNGRAPH_AUX_SPEC       7777 /* CNN-Graph: Invalid graph
                                              definition. Probably the
                                              auxiliary outputs of a layer have
                                              not been connected with
                                              corresponding aux selection
                                              layers (SelectAux) or at least
                                              one aux output has not been
                                              specified during model creation
                                              (create_dl_model call).
                                              */

#define H_ERR_DL_FILE_READ            7780 /* DL: Error reading file */
#define H_ERR_DL_FILE_WRITE           7781 /* DL: Error writing file */
#define H_ERR_DL_FILE_WRONG_VERSION   7782 /* DL: Wrong file version */

#define H_ERR_DL_INPUTS_MISSING       7783 /* DL: Inputs missing in input dict */
#define H_ERR_DL_INPUT_WRONG_BS       7784 /* DL: Inputs have incorrect batch
                                                  size */
#define H_ERR_DL_INVALID_NAME         7785 /* DL: Invalid layer name */
#define H_ERR_DL_DUPLICATE_NAME       7786 /* DL: Duplicate layer name */
#define H_ERR_DL_INVALID_OUTPUT       7787 /* DL: Invalid output layer */
#define H_ERR_DL_PARAM_NOT_AVAILABLE  7788 /* DL: Parameter is not available */
#define H_ERR_DL_INPUT_WRONG_LENGTH   7789 /* DL: Tuple inputs have incorrect length */
#define H_ERR_DL_INPUT_WRONG_TYPE     7790 /* DL: Tuple inputs have incorrect type */
#define H_ERR_DL_INPUT_WRONG_VALUES   7791 /* DL: Some inputs have incorrect values */
#define H_ERR_DL_CLASS_IDS_NOT_UNIQUE 7792 /* DL: Some class ids are not unique */
#define H_ERR_DL_CLASS_IDS_INVALID    7793 /* DL: Some class ids are invalid */
#define H_ERR_DL_CLASS_IDS_INVALID_CONV    7794 /* DL: Input data of class id
                                                   conversion is invalid. */
#define H_ERR_DL_TYPE_ALREADY_DEFINED 7795 /* DL: Type already defined */
#define H_ERR_DL_NO_INFERENCE_INPUTS  7796 /* DL: Cannot identify inference
                                              inputs. */
#define H_ERR_DL_CLASS_IDS_INVALID_OVERLAP 7797 /* DL: Some class ids overlap
                                                   with ignore class ids. */
#define H_ERR_DL_WRONG_OUTPUT_LAYER_NUM   7798 /* DL: Wrong number of output layer */
#define H_ERR_DL_WRONG_BS_MULTIPLIER      7799 /* DL: Batch size multiplier needs to be greater than 0 */
#define H_ERR_DL_INPUT_WRONG_BS_WITH_MULTIPLIER    7800 /* DL: Inputs have incorrect batch
                                                  size. The number of needed inputs is defined
                                                  by batch_size * batch_size_multiplier */

#define H_ERR_DL_READ_ONNX 7801 /* Error occured while reading an ONNX model */
#define H_ERR_DL_CLASS_IDS_MISSING 7802 /* DL: Model does not have class ids */

/* DL Detector */
#define H_ERR_DL_FPN_SCALES           7810 /* DL: Wrong scales during FPN creation */
#define H_ERR_DL_FPN_INVALID_BACKBONE 7811 /* DL: Backbone unusable for FPN creation */
#define H_ERR_DL_FPN_INVALID_FEATURE_MAP_SIZE 7812 /* DL: Backbone feature maps not divisible by 2 */
#define H_ERR_DL_FPN_INVALID_LEVELS 7813 /* Invalid FPN levels given */
#define H_ERR_DL_ANCHOR                 7820 /* DL: Internal error using anchors */
#define H_ERR_DL_DETECTOR_INVALID_PARAM  7821 /* DL: Invalid detector parameter */
#define H_ERR_DL_DETECTOR_INVALID_PARAM_VALUE  7822 /* DL: Invalid detector parameter value */
#define H_ERR_DL_DETECTOR_INVALID_DOCKING_LAYER  7823 /* DL: Invalid docking layer */
#define H_ERR_DL_DETECTOR_INVALID_INSTANCE_TYPE  7824 /* DL: Invalid instance type */

/* DL Nodes */
#define H_ERR_DL_NODE_MISSING_PARAM_NAME  7830 /* DL-Node: Missing generic
                                                  parameter 'name'. Please
                                                  specify a layer name. */

#define H_ERR_DL_NODE_GENPARAM_NAME_NOT_ALLOWED  7831 /* DL-Node: No generic parameter
                                                  'name' allowed for this node. */

#define H_ERR_DL_NODE_INVALID_SPEC  7832 /* DL-Node: Invalid layer specification. */

/* DL Heatmap */
#define H_ERR_DL_HEATMAP_UNSUPPORTED_RUNTIME    7850 /* DL: Heatmap is unsupported with
                                                        the selected runtime. Please switch to
                                                        'gpu' runtime. */
#define H_ERR_DL_HEATMAP_UNSUPPORTED_MODEL_TYPE 7851 /* DL: Unsupported heatmap model type. 
                                                        The heatmap is only applicable for 
                                                        model type 'classification'. */
#define H_ERR_DL_HEATMAP_UNSUPPORTED_METHOD     7852 /* DL: Unsupported heatmap method */
#define H_ERR_DL_HEATMAP_WRONG_TARGET_CLASS_ID  7853 /* DL: Wrong target class id for heatmap */

/* DL Anomaly */
#define H_ERR_DL_ANOMALY_MODEL_INTERNAL  7880 /* DL: Internal error occurred in anomaly model */
#define H_ERR_DL_ANOMALY_MODEL_UNTRAINED  7881 /* DL: Untrained anomaly model */
#define H_ERR_DL_ANOMALY_MODEL_TRAINING_FAILED  7882 /* DL: Anomaly model training failed */
#define H_ERR_DL_ANOMALY_MODEL_PARAM_TRAINED 7883 /* DL: Unable to set parameter on a trained
                                                     anomaly detection model */
#define H_ERR_DL_ANOMALY_MODEL_RESIZE  7884 /* DL: Input image size cannot be changed */
#define H_ERR_DL_ANOMALY_MODEL_DEPTH  7885 /* DL: Input depth is not supported */
#define H_ERR_DL_ANOMALY_MODEL_INPUT_DOMAIN 7886 /* DL: Input domain must not be empty */

/* DL Model */
#define H_ERR_DL_MODEL_APPLY_NO_DEF_OUTPUTS 7910 /* apply_dl_model: no default
                                                    outputs allowed */
#define H_ERR_DL_MODEL_UNSUPPORTED_GENPARAM  7911 /* DL: Unsupported generic parameter */

/* DL Module */
#define H_ERR_DL_MODULE_NOT_LOADED 7990 /* DLModule is not loaded */

/* Cgpx */
#define H_ERR_WPRN         8000 /* Unknown operator name */
#define H_ERR_RCNA         8001 /* register_comp_used is not activated */
#define H_ERR_WPC          8002 /* Unknown operator class */

/* Convolution and rank */
/* Error codes concerning getMask() (RMF = Read Mask-File) */
#define H_ERR_ORMF        8101  /* convol/mask: Error while opening file */
#define H_ERR_EOFRMF      8102  /* convol/mask: Premature end of file */
#define H_ERR_CVTRMF      8103  /* convol/mask: Conversion error */
#define H_ERR_LCNRMF      8104  /* convol/mask: Wrong row-/column number */
#define H_ERR_WCOVRMF     8105  /* convol/mask: Mask size overflow */
#define H_ERR_NEOFRMF     8106  /* convol/mask: Too many elements entered */
/* IPconvol() and IPRank()                             */
#define H_ERR_WRRA        8107  /* convol: Wrong margin type */
#define H_ERR_MCN0        8108  /* convol: No mask object has got
                                   empty region */
#define H_ERR_WF0         8110  /* convol: Weight factor is 0 */
#define H_ERR_NWC         8111  /* convol: Inconsistent number of weights */
#define H_ERR_WRRV        8112  /* rank: Wrong rank value */
/* Border treatment */
#define H_ERR_ROVFL       8113  /* convol/rank: Error while handling margin */
#define H_ERR_EWPMF       8114  /* Error while parsing filter mask file */

#define H_ERR_WNUMM       8120  /* Wrong number of coefficients for
                                   convolution (sigma too big?) */

/* Background estimation (Kalman) */
#define H_ERR_WBEDN       8200  /* No valid ID for data set */
#define H_ERR_NBEDA       8201  /* No data set active (set_bg_esti) */
#define H_ERR_BEDNAU      8202  /* ID already used for data set */
#define H_ERR_NBEDC       8204  /* No data set created (create_bg_esti) */
#define H_ERR_NTM         8205  /* Not possible to pass an object list */
#define H_ERR_WISBE       8206  /* Image has other size than the background
                                   image in data set */
#define H_ERR_UDNSSBE     8207  /* Up-date-region is bigger than
                                   background image */
#define H_ERR_SNBETS      8208  /* Number of statistic data sets is
                                   too small */
#define H_ERR_WAMBE       8209  /* Wrong value for adapt mode */
#define H_ERR_WFMBE       8210  /* Wrong value for frame mode */


/* Pose estimation */
#define H_ERR_PE_NPCTS    8250  /* Number of point corresponcences too small */
#define H_ERR_PE_INVMET   8251  /* Invalid method */

/* OCR */
#define H_ERR_OCR_MEM1    8300  /* Maximum number of fonts exceeded */
#define H_ERR_OCR_WID     8301  /* Wrong ID (Number) for font */
#define H_ERR_OCR1        8302  /* OCR internal error: wrong ID */
#define H_ERR_OCR_NNI     8303  /* OCR not initialised: no font was read in */
#define H_ERR_OCR_NAI     8304  /* No font activated */
#define H_ERR_OCR_WTP     8305  /* OCR internal error: Wrong threshold in
                                   angle determination */
#define H_ERR_OCR_WF      8306  /* OCR internal error: Wrong attribute */
#define H_ERR_OCR_READ    8307  /* The version of the OCR classifier
                                   is not supported */
#define H_ERR_OCR_NODES   8308  /* OCR File: Inconsistent number of nodes */
#define H_ERR_OCR_EOF     8309  /* OCR File: File too short */
#define H_ERR_OCR_INC1    8310  /* OCR: Internal error 1 */
#define H_ERR_OCR_INC2    8311  /* OCR: Internal error 2 */
#define H_ERR_WOCRTYPE    8312  /* Wrong type of OCR tool
                                   (no 'box' or 'net') */
#define H_ERR_OCR_TRF     8313  /* The version of the OCR training characters
                                   is not supported */
#define H_ERR_TRF_ITL     8314  /* Image too large for training file */
#define H_ERR_TRF_RTL     8315  /* Region too large for training file */
#define H_ERR_TRF_PT      8316  /* Protected OCR training file */
#define H_ERR_TRF_WPW     8317  /* Protected OCR training file: wrong passw. */
#define H_ERR_OCR_NOSITEM 8318  /* Serialized item does not contain a valid
                                   OCR classifier */
#define H_ERR_TRF_CON_EIO 8319  /* OCR training file concatenation failed:
                                   identical input and output files */

#define H_ERR_OCR_MLP_NOCLASSFILE 8320 /* Invalid file format for
                                          MLP classifier */
#define H_ERR_OCR_MLP_WRCLASSVERS 8321 /* The version of the MLP classifier
                                          is not supported */
#define H_ERR_OCR_MLP_NOSITEM     8322 /* Serialized item does not contain
                                          a valid MLP classifier */

#define H_ERR_OCR_SVM_NOCLASSFILE 8330 /* Invalid file format for
                                          SVM classifier */
#define H_ERR_OCR_SVM_WRCLASSVERS 8331 /* The version of the SVM
                                          classifier is not supported*/
#define H_ERR_OCR_SVM_NOSITEM     8332 /* Serialized item does not contain
                                          a valid SVM classifier */

#define H_ERR_OCR_KNN_NOCLASSFILE 8333 /* Invalid file format for
                                          k-NN classifier */
#define H_ERR_OCR_KNN_NOSITEM     8334 /* Serialized item does not contain
                                          a valid k-NN classifier */

#define H_ERR_OCR_CNN_NOCLASSFILE 8335 /* Invalid file format for CNN
                                          classifier */
#define H_ERR_OCR_CNN_WRCLASSVERS 8336 /* The version of the CNN classifier
                                          is not supported */
#define H_ERR_OCR_CNN_NOSITEM     8337 /* Serialized item does not contain
                                          a valid CNN classifier */
#define H_ERR_OCR_RESULT_NOT_AVAILABLE 8338 /* Result name is not available
                                               for this mode */

/* OCV */
#define H_ERR_OCV_NI            8350  /* OCV system not initialized */
#define H_ERR_WOCVTYPE          8351  /* The version of the OCV tool
                                         is not supported */
#define H_ERR_OCV_WNAME         8353  /* Wrong name for an OCV object */
#define H_ERR_OCV_II            8354  /* Training has already been applied */
#define H_ERR_OCV_NOTTR         8355  /* No training has been applied */
#define H_ERR_OCV_NOSITEM       8356  /* Serialized item does not
                                         contain a valid OCV tool */

/* Function 1D */
#define H_ERR_WLENGTH       8370 /* Wrong number of function points */
#define H_ERR_NO_FUNCTION   8371 /* List of values is not a function */
#define H_ERR_NOT_ASCENDING 8372 /* Wrong ordering of values (not ascending)*/
#define H_ERR_ILLEGAL_DIST  8373 /* Illegal distance of function points */
#define H_ERR_NOT_MONOTONIC 8374 /* Function is not monotonic. */
#define H_ERR_WFUNCTION     8375 /* Wrong function type. */

/* Grid rectification */
#define H_ERR_GRID_CONNECT_POINTS 8390 /* The input points could not be
                                          arranged in a regular grid */
#define H_ERR_GRID_GEN_MAP        8391 /* Error while creating the output
                                          map */
#define H_ERR_GRID_AUTO_ROT       8392 /* Auto rotation failed */

/* Camera calibration */
#define H_ERR_CAL_IDENTICAL_FP    8395 /* Same finder pattern found
                                          multiple times */
#define H_ERR_CAL_LSCPNA    8396 /* Function not available for line scan
                                    cameras with perspective lenses */
#define H_ERR_CAL_MARK_SEGM 8397 /* Mark segmentation failed */
#define H_ERR_CAL_CONT_EXT  8398 /* Contour extraction failed */
#define H_ERR_CAL_NO_FP     8399 /* No finder pattern found */
#define H_ERR_CAL_LCALP     8400 /* At least 3 calibration points have to be
                                    indicated */
#define H_ERR_CAL_INCONSISTENT_FP  8401 /* Inconsistent finder pattern
                                           positions */
#define H_ERR_CAL_NCPF      8402 /* No calibration table found */
#define H_ERR_CAL_RECPF     8403 /* Error while reading calibration table
                                    description file */
#define H_ERR_CAL_LTMTH     8404 /* Minimum threshold while searching for
                                    ellipses */
#define H_ERR_CAL_FRCP      8405 /* Read error / format error in calibration
                                    table description file */
#define H_ERR_CAL_PROJ      8406 /* Error in projection:
                                    s_x = 0 or s_y = 0 or z = 0 */
#define H_ERR_CAL_UNPRO     8407 /* Error in inverse projection */
#define H_ERR_CAL_RICPF     8408 /* Not possible to open camera parameter
                                    file */
#define H_ERR_CAL_FICP1     8409 /* Format error in file: No colon */
#define H_ERR_CAL_FICP2     8410 /* Format error in file:
                                    2. colon is missing */
#define H_ERR_CAL_FICP3     8411 /* Format error in file:
                                    Semicolon is missing */
#define H_ERR_CAL_REPOS     8412 /* Not possible to open camera parameter
                                    (pose) file */
#define H_ERR_CAL_FOPOS     8413 /* Format error in camera parameter
                                    (pose) file */
#define H_ERR_CAL_OCPDF     8414 /* Not possible to open calibration target
                                    description file */
#define H_ERR_CAL_OCPPS     8415 /* Not possible to open postscript file of
                                    calibration target */
#define H_ERR_CAL_EVECN     8416 /* Error while norming the vector */
#define H_ERR_CAL_NPLAN     8417 /* Fitting of calibration target failed */
#define H_ERR_CAL_NNMAR     8418 /* No next mark found */
#define H_ERR_CAL_NNEQU     8419 /* Normal equation system is not solvable */
#define H_ERR_CAL_QETHM     8420 /* Average quadratic error is too big for
                                    3D position of mark */
#define H_ERR_CAL_NOELL     8421 /* Non elliptic contour */
#define H_ERR_CAL_WPARV     8422 /* Wrong parameter value slvand() */
#define H_ERR_CAL_WFRES     8423 /* Wrong function results slvand() */
#define H_ERR_CAL_ECPDI     8424 /* Distance of marks in calibration target
                                    description file is not possible */
#define H_ERR_CAL_WEFLA     8425 /* Specified flag for degree of freedom
                                    not valid */
#define H_ERR_CAL_NOMER     8426 /* Minimum error did not fall below */
#define H_ERR_CAL_WPTYP     8427 /* Wrong type in Pose
                                    (rotation / translation) */
#define H_ERR_CAL_WIMSZ     8428 /* Image size does not match the measurement
                                    in camera parameters */
#define H_ERR_CAL_NPILS     8429 /* Point could not be projected into
                                    linescan image */
#define H_ERR_CAL_DIACM     8430 /* Diameter of calibration marks could
                                    not be determined */
#define H_ERR_CAL_ORICP     8431 /* Orientation of calibration plate could
                                    not be determined */
#define H_ERR_CAL_CPNII     8432 /* Calibration plate does not lie completely
                                    inside the image */
#define H_ERR_CAL_WNCME     8433 /* Wrong number of calibration marks
                                    extracted */
#define H_ERR_CAL_UNKPG     8434 /* Unknown name of parameter group */
#define H_ERR_CAL_NEGFL     8435 /* Focal length must be non-negative */
#define H_ERR_CAL_TELNA     8436 /* Function not available for cameras
                                    with telecentric lenses */
#define H_ERR_CAL_LSCNA     8437 /* Function not available for line scan
                                    cameras */
#define H_ERR_CAL_ELLDP     8438 /* Ellipse is degenerated to a point */
#define H_ERR_CAL_NOMF      8439 /* No orientation mark found */
#define H_ERR_CAL_NCONV     8440 /* Camera calibration did not converge */
#define H_ERR_CAL_HYPNA     8441 /* Function not available for cameras with
                                    hypercentric lenses */
#define H_ERR_CAL_DISTORT   8442 /* Point cannot be distorted. */
#define H_ERR_CAL_WREDGFILT 8443 /* Wrong edge filter. */
#define H_ERR_CAL_NEGPS     8444 /* Pixel size must be non-negative or zero */
#define H_ERR_CAL_NEGTS     8445 /* Tilt is in the wrong range */
#define H_ERR_CAL_NEGRS     8446 /* Rot is in the wrong range */
#define H_ERR_CAL_INVCAMPAR 8447 /* Camera parameters are invalid */
#define H_ERR_CAL_ILLFL     8448 /* Focal length must be positive */
#define H_ERR_CAL_ILLMAG    8449 /* Magnification must be positive */
#define H_ERR_CAL_ILLIPD    8450 /* Illegal image plane distance */

/* Calib Data Model (CM) and Camera Setup Model (CSM) errors */
#define H_ERR_CM_NOT_OPTIMIZED  8451 /* model not optimized yet - no res's*/
#define H_ERR_CM_NOT_POSTPROCC  8452 /* auxilary model results not available */
#define H_ERR_CM_NOT_INTERCONN  8453 /* setup not 'visibly' interconnected */
#define H_ERR_CM_CAMPAR_MISMCH  8454 /* camera parameter mismatch */
#define H_ERR_CM_CAMTYP_MISMCH  8455 /* camera type mismatch */
#define H_ERR_CM_CAMTYP_UNSUPD  8456 /* camera type not supported */
#define H_ERR_CM_INVALD_CAMIDX  8457 /* invalid camera ID */
#define H_ERR_CM_INVALD_DESCID  8458 /* invalid cal.obj. ID */
#define H_ERR_CM_INVALD_COBJID  8459 /* invalid cal.obj. instance ID */
#define H_ERR_CM_UNDEFINED_CAM  8460 /* undefined camera  */
#define H_ERR_CM_REPEATD_INDEX  8461 /* repeated observ. index */
#define H_ERR_CM_UNDEFI_CADESC  8462 /* undefined calib. object description */
#define H_ERR_CM_NO_DESCR_FILE  8463 /* Invalid file format for calibration
                                        data model */
#define H_ERR_CM_WR_DESCR_VERS  8464 /* The version of the calibration data
                                        model is not supported */
#define H_ERR_CM_ZERO_MOTION    8465 /* zero-motion in linear scan camera */
#define H_ERR_CM_MULTICAM_UNSP  8466 /* multi-camera and -calibobj not
                                        supported for all camera types */
#define H_ERR_CM_INCMPLTE_DATA  8467 /* incomplete data, required for legacy
                                        calibration */
#define H_ERR_CSM_NO_DESCR_FIL  8468 /* Invalid file format for camera setup
                                        model */
#define H_ERR_CSM_WR_DESCR_VER  8469 /* The version of the camera setup model
                                        is not supported */
#define H_ERR_CM_CALTAB_NOT_AV  8470 /* full HALCON-caltab descr'n required */
#define H_ERR_CM_INVAL_OBSERID  8471 /* invalid observation ID */
#define H_ERR_CSM_NOSITEM       8472 /* Serialized item does not contain a
                                        valid camera setup model */

#define H_ERR_CM_NOSITEM        8473 /* Serialized item does not contain a
                                        valid calibration data model */
#define H_ERR_CM_INV_TOOLPOSID  8474 /* Invalid tool pose id */
#define H_ERR_CM_UNDEFINED_TOO  8475 /* Undefined tool pose */
#define H_ERR_CM_INVLD_MODL_TY  8476 /* Invalid calib data model type */
#define H_ERR_CSM_UNINIT_CAM    8477 /* The camera setup model contains an
                                        uninitialized camera */
#define H_ERR_CM_NO_VALID_SOL   8478 /* The hand-eye algorithm failed
                                        to find a solution. */
#define H_ERR_CM_INVAL_OBS_POSE 8479 /* invalid observation pose */
#define H_ERR_CM_TOO_FEW_POSES  8480 /* Not enough calibration object poses */
#define H_ERR_CM_UNDEF_CAM_TYP  8481 /* undefined camera type */

/* Stereo Model (SM) Errors */
#define H_ERR_SM_NO_IM_PAIR     8484 /* No camera pair set by
                                        set_stereo_model_image_pairs */
#define H_ERR_SM_NO_VIS_COLOR   8485 /* No reconstructed point is visible for
                                        coloring */
#define H_ERR_SM_NO_RECONSTRUCT 8486 /* No camera pair yields
                                        reconstructed points (please check
                                        parameters of disparity method or
                                        bounding box) */
#define H_ERR_SM_INVLD_BB_PARTITION 8487 /* Partitioning of bounding box is too
                                            fine (please adapt the parameter
                                            'resolution' or the bounding box)*/
#define H_ERR_SM_INVLD_DISP_RANGE 8488 /* Invalid disparity range for
                                          binocular_disparity_ms method */
#define H_ERR_SM_INVLD_BIN_PAR  8489 /* Invalid param for binoculuar method */
#define H_ERR_SM_INVLD_MODL_TY  8490 /* invalid stereo model type */
#define H_ERR_SM_NOT_PERSISTEN  8491 /* stereo model is not in persistent
                                        mode */
#define H_ERR_SM_INVLD_BOU_BOX  8492 /* invalid bounding box */
#define H_ERR_SR_INVLD_IMG_SIZ  8493 /* stereo reconstruction: image sizes
                                        must correspond to camera setup */
#define H_ERR_SR_BBOX_BHND_CAM  8494 /* bounding box is behind basis line */
#define H_ERR_CAL_AMBIGIOUS     8495 /* Ambigious calibration: Please,
                                        recalibrate with improved input data!*/
#define H_ERR_CAL_PCPND         8496 /* Pose of calibration plate not
                                        determined */
#define H_ERR_CAL_FAILED        8497 /* Calibration failed: Please check your
                                        input data and calibrate again! */
#define H_ERR_CAL_MISSING_DATA  8498 /* No observation data supplied! */
#define H_ERR_CAL_FEWER_FOUR    8499 /* The calibration object has to be
                                        seen at least once by every camera,
                                        if less than four cameras are used. */

/* Matching */
/* Gray-value-based matching */
#define H_ERR_NOAP          8500 /* Invalid file format for template */
#define H_ERR_WPFV          8501 /* The version of the template is not
                                    supported */
#define H_ERR_MATCH_MODE    8502 /* Error during changing the file mode */
#define H_ERR_MATCH_OOR     8503 /* Inconsistent match file:
                                    Coordinates out of range */
#define H_ERR_NOTAP         8505 /* The image(s) is not a pyramid */
#define H_ERR_NGTPTS        8506 /* Number of template points too small */
#define H_ERR_PDTL          8507 /* Template data can only be read by
                                    HALCON XL */
#define H_ERR_NCC_NOSITEM   8508 /* Serialized item does not contain
                                    a valid NCC model */
#define H_ERR_MATCH_NOSITEM 8509 /* Serialized item does not contain
                                    a valid template */

/* Shape-based matching */
#define H_ERR_NTPTS         8510 /* Number of shape model points too small */
#define H_ERR_CGSMM         8511 /* Gray and color shape models mixed */
#define H_ERR_SMTL          8512 /* Shape model data can only be read by
                                    HALCON XL */
#define H_ERR_SMNXLD        8513 /* Shape model was not created from XLDs */
#define H_ERR_SM_NOSITEM    8514 /* Serialized item does not contain a valid
                                    shape model */
#define H_ERR_SM_CL_CONT    8515 /* Shape model contour too near to clutter
                                    region */
#define H_ERR_SM_NO_CLUT    8516 /* Shape model does not contain clutter
                                    parameters */
#define H_ERR_SM_SAME_CL    8517 /* Shape models are not of the same clutter type */
#define H_ERR_SM_WRONG_CLCO 8518 /* Shape model has an invalid clutter
                                    contrast */
                                    
/* Surface-based matching */
#define H_ERR_FIND_BOX_UNSUP_GENPARAM 8520 /* Box finder: Unsupported
                                              generic parameter */

/* Component-based matching */
#define H_ERR_COMP_DRT      8530 /* Initial components have different
                                    region types */
#define H_ERR_COMP_SAMF     8531 /* Solution of ambiguous matches failed */
#define H_ERR_IGF_NC        8532 /* Computation of the incomplete gamma
                                    function not converged */
#define H_ERR_MSA_TMN       8533 /* Too many nodes while computing the minimum
                                    spanning arborescence */
#define H_ERR_CTTL          8534 /* Component training data can only be read
                                    by HALCON XL */
#define H_ERR_CMTL          8535 /* Component model data can only be read by
                                    HALCON XL */
#define H_ERR_COMP_NOSITEM  8536 /* Serialized item does not contain a valid
                                    component model */
#define H_ERR_TRAIN_COMP_NOSITEM        8537 /* Serialized item does not
                                                contain a valid component
                                                training result */
/* Image comparison */
#define H_ERR_VARIATION_WS    8540 /* Size of the training image and the
                                      variation model differ */
#define H_ERR_VARIATION_PREP  8541 /* Variation model has not been prepared
                                      for segmentation */
#define H_ERR_VARIATION_WRMD  8542 /* Invalid variation model training mode */
#define H_ERR_VARIATION_NOVF  8543 /* Invalid file format for variation
                                      model */
#define H_ERR_VARIATION_WVFV  8544 /* The version of the variation model is
                                      not supported */
#define H_ERR_VARIATION_TRDC  8545 /* Training data has been cleared */
#define H_ERR_VARIATION_NOSITEM 8546 /* Serialized item does not contain a
                                        valid variation model */

/* Measure */
#define H_ERR_MEASURE_NA    8550 /* No more measure objects available */
#define H_ERR_MEASURE_NI    8551 /* Measure object is not initialized */
#define H_ERR_MEASURE_OOR   8552 /* Invalid measure object */
#define H_ERR_MEASURE_IS    8553 /* Measure object is NULL */
#define H_ERR_MEASURE_WS    8554 /* Measure object has wrong image size */
#define H_ERR_MEASURE_NO_MODEL_FILE 8555 /* Invalid file format for measure
                                            object */
#define H_ERR_MEASURE_WRONG_VERSION 8556 /* The version of the measure object
                                            is not supported */
#define H_ERR_MEASURE_TL            8557 /* Measure object data can only be
                                            read by HALCON XL */
#define H_ERR_MEASURE_NOSITEM       8558 /* Serialized item does not contain
                                            a valid measure object */

/* Metrology */
#define H_ERR_METROLOGY_MODEL_NI       8570 /* Metrology model is not
                                               initialized */
#define H_ERR_METROLOGY_OBJECT_INVALID 8572 /* Invalid metrology object */
#define H_ERR_METROLOGY_FIT_NOT_ENOUGH_MEASURES  8573 /* Not enough valid
                                               measures for fitting the
                                               metrology object */
#define H_ERR_METROLOGY_NO_MODEL_FILE  8575 /* Invalid file format for
                                               metrology model */
#define H_ERR_METROLOGY_WRONG_VERSION  8576 /* The version of the metrology
                                               model is not supported */
#define H_ERR_METROLOGY_NO_FUZZY_FUNC  8577 /* Fuzzy function is not set */
#define H_ERR_METROLOGY_NOSITEM        8578 /* Serialized item does not
                                               contain a valid metrology
                                               model */
#define H_ERR_METROLOGY_UNDEF_CAMPAR   8579 /* Camera parameters are not
                                               set */
#define H_ERR_METROLOGY_UNDEF_POSE     8580 /* Pose of the measurement plane
                                               is not set */
#define H_ERR_METROLOGY_SET_MODE       8581 /* Mode of metrology model cannot
                                               be set since an object has
                                               already been added */
#define H_ERR_METROLOGY_OP_NOT_ALLOWED 8582 /* If the pose of the metrology
                                               object has been set several
                                               times, the operator is not
                                               longer allowed */
#define H_ERR_METROLOGY_MULTI_POSE_CAM_PAR 8583 /* All objects of a metrology
                                               model must have the same world
                                               pose and camera parameters. */
#define H_ERR_METROLOGY_WRONG_INPUT_MODE   8584 /* Input type of metrology
                                                   model does not correspond
                                                   with the current input
                                                   type */

/* Dynamic libraries */
#define H_ERR_DLOPEN        8600 /* Dynamic library could not be opened */
#define H_ERR_DLCLOSE       8601 /* Dynamic library could not be closed */
#define H_ERR_DLLOOKUP      8602 /* Symbol not found in dynamic library */

#define H_ERR_COMPONENT_NOT_INSTALLED 8603 /* Interface library not
                                            * available */

/* Radiometric calibration */
#define H_ERR_EAD_CAL_NII   8650 /* Not enough information for rad. calib. */

/* Barcode */
#define H_ERR_BAR_WNOM       8701 /* Wrong number of modules */
#define H_ERR_BAR_WNOE       8702 /* Wrong number of elements */
#define H_ERR_BAR_UNCHAR     8703 /* Unknown character (for this code) */
#define H_ERR_BAR_WRONGDESCR 8705 /* Wrong name for attribute in barcode
                                     descriptor */
#define H_ERR_BAR_EL_LENGTH  8706 /* Wrong thickness of element */
#define H_ERR_BAR_NO_REG     8707 /* No region found */
#define H_ERR_BAR_WRONGCODE  8708 /* Wrong type of bar code */
#define H_ERR_BAR_INTERNAL   8709  /* Internal error in bar code reader */
#define H_ERR_BAR_NO_DECODED_SCANLINE   8710  /* Candidate does not contain a
                                                 decoded scanline */
#define H_ERR_BC_EMPTY_MODEL_LIST   8721 /* Empty model list */
#define H_ERR_BC_TRAIN_ONLY_SINGLE  8722 /* Training cannot be done for
                                            multiple bar code types */
#define H_ERR_BC_GET_SPECIFIC       8723 /* Cannot get bar code type specific
                                            parameter with get_bar_code_param.
                                            Use get_bar_code_param_specific */
#define H_ERR_BC_GET_OBJ_MULTI      8724 /* Cannot get this object for multiple
                                            bar code types. Try again with
                                            single bar code type */
#define H_ERR_BC_WR_FILE_FORMAT     8725 /* Wrong binary (file) format */
#define H_ERR_BC_WR_FILE_VERS       8726 /* Wrong version of binary file */
#define H_ERR_BC_NOT_PERSISTANT     8727 /* The model must be in persistency
                                            mode to deliver the required
                                            object/result */
#define H_ERR_BC_GRAY_OUT_OF_RANGE  8728 /* Incorrect index of scanline's gray
                                            values*/

#define H_ERR_NO_PERSISTENT_OP_CALL 8729 /* Neither find_bar_code nor
                                            decode_bar_code_rectanlge2 has
                                            been called in 'persistent' mode on
                                            this model */

#define H_ERR_SRB_ABORTED           8730  /* The super-resolution algorithm has
                                             been aborted */

#define H_ERR_SRB_INVALID_INPUT     8731  /* SRB: Invalid input data. */

#define H_ERR_BC_XCORR_INVALID_INPUT     8740 /* Invalid input detected for
                                                 barcode normalized cross
                                                 correlation */
#define H_ERR_BC_XCORR_TOO_MANY_BAD_ROWS 8741 /* Too many bad rows found during
                                                 barcode normalized cross
                                                 correlation */
#define H_ERR_BC_XCORR_NO_CORRELATION    8742 /* No correlation found during
                                                 barcode normalized cross
                                                 correlation */

/* 2D Barcode */
#define H_ERR_BAR2D_UNKNOWN_TYPE     8800 /* Specified code type is not
                                             supported */
#define H_ERR_BAR2D_WRONG_FOREGROUND 8801 /* Wrong foreground specified */
#define H_ERR_BAR2D_WRONG_SIZE       8802 /* Wrong matrix size specified */
#define H_ERR_BAR2D_WRONG_SHAPE      8803 /* Wrong symbol shape specified */
#define H_ERR_BAR2D_WRONG_PARAM_NAME 8804 /* Wrong generic parameter name */
#define H_ERR_BAR2D_WRONG_PARAM_VAL  8805 /* Wrong generic parameter value */
#define H_ERR_BAR2D_WRONG_MODE       8806 /* Wrong symbol printing mode */
#define H_ERR_BAR2D_SYMBOL_ON_BORDER 8807 /* Symbol region too near to image
                                             border */
#define H_ERR_BAR2D_MODULE_CONT_NUM  8808 /* No rectangular modul boundings
                                             found */
#define H_ERR_BAR2D_SYMBOL_FINDER    8809 /* Couldn't identify symbol
                                             finder */
#define H_ERR_BAR2D_SYMBOL_DIMENSION 8810 /* Symbol region with wrong
                                             dimension */
#define H_ERR_BAR2D_CLASSIF_FAILED   8811 /* Classification failed */
#define H_ERR_BAR2D_DECODING_FAILED  8812 /* Decoding failed */
#define H_ERR_BAR2D_DECODING_READER  8813 /* Reader programing not
                                             supported */

/* Error codes for errors on all types 2d data codes */
#define H_ERR_DC2D_GENERAL             8820 /* General 2d data code error */
#define H_ERR_DC2D_BROKEN_SIGN         8821 /* Corrupt signature of 2d data
                                               code handle */
#define H_ERR_DC2D_INVALID_HANDLE      8822 /* Invalid 2d data code handle */
#define H_ERR_DC2D_EMPTY_MODEL_LIST    8823 /* List of 2d data code models is
                                               empty */
#define H_ERR_DC2D_NOT_INITIALIZED     8824 /* Access to uninitialized (or not
                                               persistent) internal data */
#define H_ERR_DC2D_INVALID_CANDIDATE   8825 /* Invalid 'Candidate' parameter */
#define H_ERR_DC2D_INDEX_PARNUM        8826 /* It's not possible to return more
                                               than one parameter for several
                                               candidates */
#define H_ERR_DC2D_EXCLUSIV_PARAM      8827 /* One of the parameters returns
                                               several values and has to be
                                               used exclucively for a single
                                               candidate */
#define H_ERR_DC2D_DEF_SET_NOT_FIRST   8828 /* Parameter for default settings
                                               must be the first in the
                                               parameter list */
#define H_ERR_DC2D_INTERNAL_UNEXPECTED 8829 /* Unexpected 2d data code error */
#define H_ERR_DC2D_WRONG_PARAM_VALUE   8830 /* Invalid parameter value */
#define H_ERR_DC2D_WRONG_PARAM_NAME    8831 /* Unknown parameter name */
#define H_ERR_DC2D_WRONG_POLARITY      8832 /* Invalid 'polarity' */
#define H_ERR_DC2D_WRONG_SYMBOL_SHAPE  8833 /* Invalid 'symbol_shape' */
#define H_ERR_DC2D_WRONG_SYMBOL_SIZE   8834 /* Invalid symbol size */
#define H_ERR_DC2D_WRONG_MODULE_SIZE   8835 /* Invalid module size */
#define H_ERR_DC2D_WRONG_MODULE_SHAPE  8836 /* Invalid 'module_shape' */
#define H_ERR_DC2D_WRONG_ORIENTATION   8837 /* Invalid 'orientation' */
#define H_ERR_DC2D_WRONG_CONTRAST      8838 /* Invalid 'contrast_min' */
#define H_ERR_DC2D_WRONG_MEAS_THRESH   8839 /* Invalid 'measure_thresh' */
#define H_ERR_DC2D_WRONG_ALT_MEAS_RED  8840 /* Invalid 'alt_measure_red' */
#define H_ERR_DC2D_WRONG_SLANT         8841 /* Invalid 'slant_max' */
#define H_ERR_DC2D_WRONG_L_DIST        8842 /* Invalid 'L_dist_max' */
#define H_ERR_DC2D_WRONG_L_LENGTH      8843 /* Invalid 'L_length_min' */
#define H_ERR_DC2D_WRONG_GAP           8844 /* Invalid module gap */
#define H_ERR_DC2D_WRONG_DEF_SET       8845 /* Invalid 'default_parameters' */
#define H_ERR_DC2D_WRONG_TEXTURED      8846 /* Invalid 'back_texture' */
#define H_ERR_DC2D_WRONG_MIRRORED      8847 /* Invalid 'mirrored' */
#define H_ERR_DC2D_WRONG_CLASSIFICATOR 8848 /* Invalid 'classificator' */
#define H_ERR_DC2D_WRONG_PERSISTENCE   8849 /* Invalid 'persistence' */
#define H_ERR_DC2D_WRONG_MODEL_TYPE    8850 /* Invalid model type */
#define H_ERR_DC2D_WRONG_MOD_ROI_PART  8851 /* Invalid 'module_roi_part' */
#define H_ERR_DC2D_WRONG_FP_TOLERANCE  8852 /* Invalid
                                               'finder_pattern_tolerance' */
#define H_ERR_DC2D_WRONG_MOD_ASPECT    8853 /* Invalid 'mod_aspect_max' */
#define H_ERR_DC2D_WRONG_SM_ROBUSTNESS 8854 /* Invalid
                                               'small_modules_robustness' */
#define H_ERR_DC2D_WRONG_CONTRAST_TOL  8855 /* Invalid 'contrast_tolerance' */
#define H_ERR_DC2D_READ_HEAD_FORMAT    8860 /* Invalid header in 2d data code
                                               model file */
#define H_ERR_DC2D_READ_HEAD_SIGN      8861 /* Invalid code signature in 2d
                                               data code model file */
#define H_ERR_DC2D_READ_LINE_FORMAT    8862 /* Corrupted line in 2d data code
                                               model file */
#define H_ERR_DC2D_WRONG_MODULE_ASPECT 8863 /* Invalid module aspect ratio */
#define H_ERR_DC2D_WRONG_LAYER_NUM     8864 /* wrong number of layers */
#define H_ERR_DCD_READ_WRONG_VERSION   8865 /* wrong data code model version */
#define H_ERR_DC2D_NOSITEM             8866 /* Serialized item does not contain
                                               a valid 2D data code model */
#define H_ERR_DC2D_WR_FILE_FORMAT      8867 /* Wrong binary (file) format */

/* 3D Matching */
#define H_ERR_SM3D_WRONG_PARAM_NAME      8900  /* Invalid parameter value */
#define H_ERR_SM3D_WRONG_NUM_LEVELS      8901  /* Invalid 'num_levels' */
#define H_ERR_SM3D_WRONG_OPTIMIZATION    8902  /* Invalid 'optimization' */
#define H_ERR_SM3D_WRONG_METRIC          8903  /* Invalid 'metric' */
#define H_ERR_SM3D_WRONG_MIN_FACE_ANGLE  8904  /* Invalid 'min_face_angle' */
#define H_ERR_SM3D_WRONG_MIN_SIZE        8905  /* Invalid 'min_size' */
#define H_ERR_SM3D_WRONG_MODEL_TOLERANCE 8906  /* Invalid 'model_tolerance' */
#define H_ERR_SM3D_WRONG_FAST_POSE_REF   8907  /* Invalid
                                                 'fast_pose_refinment'*/
#define H_ERR_SM3D_WRONG_LOWEST_MODEL_LEVEL 8908 /* Invalid
                                                  'lowest_model_level'*/
#define H_ERR_SM3D_WRONG_PART_SIZE       8909  /* Invalid 'part_size'*/
#define H_ERR_SM3D_PROJECTION_TOO_LARGE  8910  /* The projected model is too
                                                  large (increase the value
                                                  for DistMin or the image
                                                  size in CamParam) */
#define H_ERR_SM3D_WRONG_OPENGL_ACCURACY 8911  /* Invalid
                                                 'opengl_accuracy'*/
#define H_ERR_SM3D_WRONG_RECOMPUTE_SCORE 8913  /* Invalid
                                                 'recompute_score'*/
#define H_ERR_SM3D_WRONG_LON_MIN         8920 /* Invalid 'longitude_min' */
#define H_ERR_SM3D_WRONG_LON_MAX         8921 /* Invalid 'longitude_max' */
#define H_ERR_SM3D_WRONG_LAT_MIN         8922 /* Invalid 'latitude_min */
#define H_ERR_SM3D_WRONG_LAT_MAX         8923 /* Invalid 'latitude_max' */
#define H_ERR_SM3D_WRONG_ROL_MIN         8924 /* Invalid 'cam_roll_min' */
#define H_ERR_SM3D_WRONG_ROL_MAX         8925 /* Invalid 'cam_roll_max' */
#define H_ERR_SM3D_WRONG_DIST_MIN        8926 /* Invalid 'dist_min' */
#define H_ERR_SM3D_WRONG_DIST_MAX        8927 /* Invalid 'dist_max' */
#define H_ERR_SM3D_WRONG_NUM_MATCHES     8928 /* Invalid 'num_matches' */
#define H_ERR_SM3D_WRONG_MAX_OVERLAP     8929 /* Invalid 'max_overlap' */
#define H_ERR_SM3D_WRONG_POSE_REFINEMENT 8930 /* Invalid 'pose_refinement' */
#define H_ERR_SM3D_WRONG_COV_POSE_MODE   8931 /* Invalid 'cov_pose_mode' */
#define H_ERR_SM3D_WRONG_OUTLIER_SUP     8932 /* In. 'outlier_suppression' */
#define H_ERR_SM3D_WRONG_BORDER_MODEL    8933 /* Invalid 'border_model' */
#define H_ERR_SM3D_UNDEFINED_POSE        8940 /* Pose is not well-defined */
#define H_ERR_SM3D_NO_SM3D_FILE          8941 /* Invalid file format for 3D
                                                 shape model */
#define H_ERR_SM3D_WRONG_FILE_VERSION    8942 /* The version of the 3D shape
                                                 model is not supported */
#define H_ERR_SM3D_MTL                   8943 /* 3D shape model can only be
                                                 read by HALCON XL */
#define H_ERR_SM3D_NO_OM3D_FACES         8944 /* 3D object model does not
                                                 contain any faces */
#define H_ERR_SM3D_NOSITEM               8945 /* Serialized item does not
                                                 contain a valid 3D shape
                                                 model */
#define H_ERR_SM3D_WRONG_UNION_ADJACENT_CONTOURS 8946 /* Invalid
                                                 'union_adjacent_contours' */

/* Descriptor-based matching */
#define H_ERR_DESCR_NODESCRFILE            8960 /* Invalid file format for
                                                   descriptor model */
#define H_ERR_DESCR_WRDESCRVERS            8961 /* The version of the
                                                   descriptor model is not
                                                   supported */
#define H_ERR_DM_WRONG_NUM_CIRC_RADIUS     8962 /* Invalid 'radius' */
#define H_ERR_DM_WRONG_NUM_CHECK_NEIGH     8963 /* Invalid 'check_neighbor' */
#define H_ERR_DM_WRONG_NUM_MIN_CHECK_NEIGH 8964 /* Invalid
                                                   'min_check_neighbor_diff' */
#define H_ERR_DM_WRONG_NUM_MIN_SCORE       8965 /* Invalid 'min_score' */
#define H_ERR_DM_WRONG_NUM_SIGMAGRAD       8966 /* Invalid 'sigma_grad' */
#define H_ERR_DM_WRONG_NUM_SIGMAINT        8967 /* Invalid 'sigma_smooth' */
#define H_ERR_DM_WRONG_NUM_ALPHA           8968 /* Invalid 'alpha' */
#define H_ERR_DM_WRONG_NUM_THRESHOLD       8969 /* Invalid 'threshold' */
#define H_ERR_DM_WRONG_NUM_DEPTH           8970 /* Invalid 'depth' */
#define H_ERR_DM_WRONG_NUM_TREES           8971 /* Invalid 'number_trees' */
#define H_ERR_DM_WRONG_NUM_MIN_SCORE_DESCR 8972 /* Invalid 'min_score_descr' */
#define H_ERR_DM_WRONG_NUM_PATCH_SIZE      8973 /* Invalid 'patch_size' */
#define H_ERR_DM_WRONG_TILT                8974 /* Invalid 'tilt' */
#define H_ERR_DM_WRONG_PAR_GUIDE           8975 /* Invalid 'guided_matching' */
#define H_ERR_DM_WRONG_PAR_SUBPIX          8976 /* Invalid 'subpix' */
#define H_ERR_DM_TOO_FEW_POINTS            8977 /* Too few feature points
                                                   can be found */
#define H_ERR_DM_WRONG_NUM_MINROT          8978 /* Invalid 'min_rot' */
#define H_ERR_DM_WRONG_NUM_MAXROT          8979 /* Invalid 'max_rot' */
#define H_ERR_DM_WRONG_NUM_MINSCALE        8980 /* Invalid 'min_scale' */
#define H_ERR_DM_WRONG_NUM_MAXSCALE        8981 /* Invalid 'max_scale' */
#define H_ERR_DM_WRONG_NUM_MASKSIZEGRD     8982 /* Invalid 'mask_size_grd' */
#define H_ERR_DM_WRONG_NUM_MASKSIZESMOOTH  8983 /* Invalid
                                                   'mask_size_smooth' */
#define H_ERR_BROKEN_MODEL                 8984 /* Model broken */
#define H_ERR_DM_WRONG_DESCR_TYPE          8985 /* Invalid 'descriptor_type' */
#define H_ERR_DM_WRONG_PAR_MATCHER         8986 /* Invalid 'matcher' */
#define H_ERR_DM_TOO_MANY_CLASSES          8987 /* Too many point classes -
                                                   cannot be written to file */
#define H_ERR_DESCR_NOSITEM                8988 /* Serialized item does not
                                                   contain a valid descriptor
                                                   model */

/* Misc */
#define H_ERR_NOT_IMPL     9000 /* Function not implemented on this machine */
#define H_ERR_WIT          9001 /* Image to process has wrong gray
                                   value type */
#define H_ERR_WIC          9002 /* Wrong image component */
#define H_ERR_UNDI         9003 /* Undefined gray values */
#define H_ERR_WIS          9004 /* Wrong image format for operation
                                   (too big or too small) */
#define H_ERR_WCN          9005 /* Wrong number of image components for
                                   image output */
#define H_ERR_STRTL        9006 /* String is too long
                                   (max. 1024 characters) */
#define H_ERR_WITFO        9007 /* Wrong pixel type for this operation */
#define H_ERR_NIIT         9008 /* Operation not realized yet for this
                                   pixel type */
#define H_ERR_NOCIMA       9009 /* Image is no color image with three
                                   channels */

#define H_ERR_DEMO_NOFG    9010 /* Image acquisition devices are not supported
                                   in the demo version */
#define H_ERR_DEMO_NOPA    9011 /* Packages are not supported in the
                                   demo version */
#define H_ERR_IEUNKV       9020 /* Internal Error: Unknown value*/
#define H_ERR_WPFO         9021 /* Wrong paramter for this operation */
#define H_ERR_IDTS         9022 /* Image domain too small */
#define H_ERR_CNCLDRW      9023 /* Draw operator has been canceled */
#define H_ERR_REGEX_MATCH  9024 /* Error during matching of regular
                                 * expression */

#define H_ERR_STUD_OPNA    9050 /* Operator is not available in the
                                   student version of HALCON */
#define H_ERR_STUD_PANA    9051 /* Packages are not available in the
                                   student version of HALCON */
#define H_ERR_STUD_FGNA    9052 /* The selected image acquisition device is not
                                   available in the student version of HALCON*/
#define H_ERR_NDPA         9053 /* No data points available */
#define H_ERR_WR_OBJ_TYPE  9054 /* Object type is not supported. */

#define H_ERR_OP_DISABLED  9055 /* Operator is disabled. */

/* Linear equations */
#define H_ERR_TMU          9100 /* Too many unknown variables in
                                   linear equation */
#define H_ERR_NUS          9101 /* No (unique) solution for the
                                   linear equation */
#define H_ERR_NEE          9102 /* Too little equations in linear equation */

/* Geometric configurations */
#define H_ERR_PDDL         9150 /* Points do not define a line */

/* Matrix operations */
#define H_ERR_MNI          9200 /* Matrix is not invertible */
#define H_ERR_SVD_CNVRG    9201 /* Singular value decomposition did not
                                   converge */
#define H_ERR_SVD_FEWROW   9202 /* Matrix has too few rows for singular
                                   value partition */
#define H_ERR_TQLI_CNVRG   9203 /* Eigenvalue computation did not converge */
#define H_ERR_JACOBI_CNVRG 9204 /* Eigenvalue computation did not converge */
#define H_ERR_MATRIX_SING  9205 /* Matrix is singular */
#define H_ERR_MATCH_CNVRG  9206 /* Function matching did not converge */

#define H_ERR_MAT_UNDEF    9207 /* Input matrix undefined */
#define H_ERR_MAT_WDIM     9208 /* Input matrix with wrong dimension */
#define H_ERR_MAT_NSQR     9209 /* Input matrix is not quadratic */
#define H_ERR_MAT_FAIL     9210 /* Matrix operation failed */
#define H_ERR_MAT_NPD      9211 /* Matrix is not positive definite */
#define H_ERR_MAT_DBZ      9212 /* Matrix element division by 0 */
#define H_ERR_MAT_NUT      9213 /* Matrix is not an upper triangular matrix */
#define H_ERR_MAT_NLT      9214 /* Matrix is not a lower triangular matrix */
#define H_ERR_MAT_NEG      9215 /* Matrix element is negative */
#define H_ERR_MAT_UNCHAR   9216 /* Matrix file: Invalid character */
#define H_ERR_MAT_NOT_COMPLETE 9217 /* Matrix file: matrix incomplete */
#define H_ERR_MAT_READ     9218 /* Invalid file format for matrix */
#define H_ERR_MAT_COMPLEX  9219 /* Resulting matrix has complex values */
#define H_ERR_WMATEXP      9220 /* Wrong value in matrix of exponents */
#define H_ERR_MAT_WRONG_VERSION 9221 /* The version of the matrix is not
                                        supported */
#define H_ERR_MAT_NOSITEM  9222 /* Serialized item does not contain a valid
                                   matrix */

/* Tree */
#define H_ERR_WNODE            9230 /* Internal Error: Wrong Node */
#define H_ERR_CMP_INCONSISTENT 9231 /* Inconsistent red black tree */

#define H_ERR_LAPACK_PAR   9250 /* Internal error */

/* Stripack */
#define H_ERR_STRI_NPNT    9260 /* Number of points too small */
#define H_ERR_STRI_COLL    9261 /* First 3 points are collinear */
#define H_ERR_STRI_IDPNT   9262 /* Identical points in triangulation */
#define H_ERR_STRI_NALLOC  9263 /* Array not allocated large enough */
#define H_ERR_STRI_DEGEN   9264 /* Triangle is degenerate */
#define H_ERR_STRI_ITRI    9265 /* Inconsistent triangulation */
#define H_ERR_STRI_SELFINT 9266 /* Self-intersecting polygon */
#define H_ERR_STRI_INCONS  9267 /* Inconsistent polygon data */
#define H_ERR_STRI_AMBINT  9268 /* Ambiguous great circle arc intersection */
#define H_ERR_STRI_AMBARC  9269 /* Ambiguous great circle arc */
#define H_ERR_STRI_ILLPAR  9270 /* Illegal parameter */

/* Tripack */
#define H_ERR_TRI_NPNT     9280 /* Not enough points for planar triangular
                                   meshing */
#define H_ERR_TRI_COLL     9281 /* The first three points of the triangular
                                   meshing are collinear */
#define H_ERR_TRI_IDPNT    9282 /* Planar triangular meshing contains
                                   identical input points */
#define H_ERR_TRI_IDPNTIN  9283 /* Invalid points for planar triangular
                                   meshing */
#define H_ERR_TRI_NALLOC   9284 /* Internal error: allocated array too small
                                   for planar triangular meshing */
#define H_ERR_TRI_ITRI     9285 /* Internal error: planar triangular meshing
                                   inconsistent */
#define H_ERR_TRI_OUTR     9286 /* Node index outside triangulation range */

/* Triangulation */
#define H_ERR_TRI_LOCINC   9290 /* Local inconsistencies for all points with
                                   valid neighbors (parameters only allow few
                                   valid neighborhoods or point cloud not
                                   subsampled) */

/* Orthogonal Projection */
#define H_ERR_WSPVP        9300 /* Eye point and reference point coincide */

/* Dual Quaternions */
#define H_ERR_DQ_ZERO_NORM 9310 /* Real part of the dual quaternion has
                                   length 0 */

/* Timeout */
#define H_ERR_TIMEOUT                  9400 /* Timeout occurred */
#define H_ERR_WRONG_TIMEOUT            9401 /* Invalid 'timeout' */
#define H_ERR_TIMEOUT_AFTER_SBM_CLEAR  9402 /* Timeout occured after cached
                                               transformations have been freed
                                               (internal error) */

/* Deformable matching */
#define H_ERR_DEFORM_WRONG_NUM_CLUSTER    9450 /* Invalid 'sub_object_size' */
#define H_ERR_DEFORM_WRONG_NUM_MIN_SIZE   9451 /* Invalid 'min_size' */
#define H_ERR_DEFORM_WRONG_NUM_LSQ        9452 /* Invalid number of
                                                  least-squares iterations */
#define H_ERR_DEFORM_WRONG_ANGLE_STEP     9453 /* Invalid 'angle_step' */
#define H_ERR_DEFORM_WRONG_SCALE_R_STEP   9454 /* Invalid 'scale_r_step' */
#define H_ERR_DEFORM_WRONG_SCALE_C_STEP   9455 /* Invalid 'scale_c_step' */
#define H_ERR_DEFORM_WRONG_MAX_ANGLE      9456 /* Invalid
                                                  'max_angle_distortion' */
#define H_ERR_DEFORM_WRONG_MAX_ANISO      9457 /* Invalid
                                                'max_aniso_scale_distortion' */
#define H_ERR_DEFORM_WRONG_MIN_SIZE       9458 /* Invalid 'min_size' */
#define H_ERR_DEFORM_WRONG_COV_POSE_MODE  9459 /* Invalid 'cov_pose_mode' */
#define H_ERR_DEFORM_NO_CALIBRATION_INFO  9460 /* Model contains no
                                                  calibration information */
#define H_ERR_DEFORM_WRONG_PARAM_NAME     9461 /* Generic parameter name
                                                  does not exist */
#define H_ERR_DEFORM_IMAGE_TO_CAMERA_DIFF 9462 /* camera has different
                                                  resolution than image */
#define H_ERR_DEFORM_NO_MODEL_IN_FILE     9463 /* Invalid file format for
                                                  deformable model */
#define H_ERR_DEFORM_WRONG_VERSION        9464 /* The version of the
                                                  deformable model is not
                                                  supported */
#define H_ERR_DEFORM_WRONG_SMOOTH_DEFORM     9465 /* Invalid
                                                     'deformation_smoothness'*/
#define H_ERR_DEFORM_WRONG_EXPAND_BORDER     9466 /* Invalid 'expand_border' */
#define H_ERR_DEFORM_ORIGIN_OUTSIDE_TEMPLATE 9467 /* Model origin outside of
                                                     axis-aligned bounding
                                                     rectangle of template
                                                     region */
#define H_ERR_DEFORM_NOSITEM              9468 /* Serialized item does not
                                                  contain a valid deformable
                                                  model */

/* Surface Based Matching */
#define H_ERR_SFM_NO_POINTS          9500 /* Object model has no points */
#define H_ERR_SFM_NO_FACES           9501 /* Object model has no faces */
#define H_ERR_SFM_NO_NORMALS         9502 /* Object model has no normals */
#define H_ERR_SFM_NO_VISIBILITY      9503 /* 3D surface model not trained for
                                             calculating view-based score */
#define H_ERR_SFM_NO_3D_EDGES        9504 /* 3D surface model not trained for
                                             edge-supported matching */
#define H_ERR_SFM_NO_SFM_FILE        9506 /* Invalid file format for 3D
                                             surface model */
#define H_ERR_SFM_WRONG_FILE_VERSION 9507 /* The version of the 3D surface
                                             model is not supported */
#define H_ERR_SFM_NOSITEM            9508 /* Serialized item does not contain
                                             a valid 3D surface model */
#define H_ERR_SFM_TOO_MANY_SYMMS     9509 /* Poses generate too many
                                             symmetries */

/* Object Model 3D */
#define H_ERR_OM3D_INVALID_FILE       9510 /* Invalid 3D file */
#define H_ERR_OM3D_INVALID_MODEL      9511 /* Invalid 3D Object Model */
#define H_ERR_OM3D_UNKNOWN_FILE_TYPE  9512 /* Unknown 3D file type */
#define H_ERR_OM3D_WRONG_FILE_VERSION 9513 /* The version of the 3D object
                                              model is not supported */
#define H_ERR_OM3D_MISSING_ATTRIB     9514 /* Required attribute is missing */
/* Object Model 3D Errors for special attributes */
#define H_ERR_OM3D_MISSING_ATTRIB_V_COORD         9515 /* Required attribute
                                                          point_coord is
                                                          missing */
#define H_ERR_OM3D_MISSING_ATTRIB_V_NORMALS       9516 /* Required attribute
                                                          point_normal is
                                                          missing */
#define H_ERR_OM3D_MISSING_ATTRIB_F_TRIANGLES     9517 /* Required attribute
                                                          face_triangle is
                                                          missing  */
#define H_ERR_OM3D_MISSING_ATTRIB_F_LINES         9518 /* Required attribute
                                                          line_array is
                                                          missing */
#define H_ERR_OM3D_MISSING_ATTRIB_F_TRINEIGB      9519 /* Required attribute
                                                          f_trineighb is
                                                          missing  */
#define H_ERR_OM3D_MISSING_ATTRIB_F_POLYGONS      9520 /* Required attribute
                                                          face_polygon is
                                                          missing  */
#define H_ERR_OM3D_MISSING_ATTRIB_V_2DMAP         9521 /* Required attribute
                                                          xyz_mapping is
                                                          missing  */
#define H_ERR_OM3D_MISSING_ATTRIB_O_PRIMITIVE     9522 /* Required attribute
                                                          o_primitive is
                                                          missing  */
#define H_ERR_OM3D_MISSING_ATTRIB_SHAPE_MODEL     9523 /* Required attribute
                                                          shape_model
                                                          is missing  */
#define H_ERR_OM3D_MISSING_ATTRIB_EXTENDED        9524 /* Required extended
                                                          attribute missing in
                                                          3D object model */
#define H_ERR_OM3D_NOSITEM            9525 /* Serialized item does not contain
                                              a valid 3D object model */
#define H_ERR_OM3D_MISSING_O_PRIMITIVE_EXTENSION  9526 /* Primitive in 3D
                                                          object model has no
                                                          extended data */
#define H_ERR_OM3D_CONTAIN_ATTRIB_F_TRIANGLES 9527 /* Operation invalid, 3D
                                                      object model already
                                                      contains triangles */
#define H_ERR_OM3D_CONTAIN_ATTRIB_F_LINES     9528 /* Operation invalid, 3D
                                                      object model already
                                                      contains lines */
#define H_ERR_OM3D_CONTAIN_ATTRIB_F_POLYGONS  9529 /* Operation invalid, 3D
                                                      object model already
                                                      contains faces or
                                                      polygons */
#define H_ERR_OM3D_ISOLATED_OBJECT       9530  /* In a global registration an
                                                  input object has no
                                                  neighbors */
#define H_ERR_OM3D_SET_ALL_COORD         9531  /* All components of points
                                                  must be set at once */
#define H_ERR_OM3D_SET_ALL_NORMALS       9532  /* All components of normals
                                                  must be set at once */
#define H_ERR_OM3D_NUM_NOT_FIT_COORD     9533  /* Number of values doesn't
                                                  correspond to number of
                                                  already existing points */
#define H_ERR_OM3D_NUM_NOT_FIT_NORMALS   9534  /* Number of values doesn't
                                                  correspond to number of
                                                  already existing normals */
#define H_ERR_OM3D_NUM_NOT_FIT_TRIANGLES 9535  /* Number of values doesn't
                                                  correspond to already
                                                  existing triangulation */
#define H_ERR_OM3D_NUM_NOT_FIT_POLYGONS  9536  /* Number of values doesn't
                                                  correspond to length of
                                                  already existing polygons */
#define H_ERR_OM3D_NUM_NOT_FIT_LINES     9537  /* Number of values doesn't
                                                  correspond to length of
                                                  already existing polylines */
#define H_ERR_OM3D_NUM_NOT_FIT_2DMAP     9538  /* Number of values doesn't
                                                  correspond already existing
                                                  2D mapping */
#define H_ERR_OM3D_NUM_NOT_FIT_EXTENDED  9539  /* Number of values doesn't
                                                  correspond to already
                                                  existing extended
                                                  attribute */
#define H_ERR_OM3D_FACE_INTENSITY_WITH_POINTS 9540 /* Per-face intensity
                                                  is used with point
                                                  attribute */
#define H_ERR_OM3D_ATTRIBUTE_NOT_SUPPORTED    9541 /* Attribute is not (yet)
                                                      supported */
#define H_ERR_OM3D_NOT_IN_BB             9542  /* No point within bounding
                                                  box */
#define H_ERR_DIF_TOO_SMALL              9543  /* distance_in_front
                                                  is smaller than the
                                                  resolution */
#define H_ERR_MINTH_TOO_SMALL            9544  /* The minimum thickness is
                                                  smaller than the surface
                                                  tolerance */

/* 3D segmentation and fitting */
#define H_ERR_SF_OM3D_TRIANGLES_NOT_SUITABLE  9550 /* Triangles of the 3D
                                                      object model are not
                                                      suitable for this
                                                      operator */
#define H_ERR_SF_OM3D_FEW_POINTS      9551 /* Too few suitable 3D points in
                                              the 3D object model */

/* Serialized item */
#define H_ERR_NO_SERIALIZED_ITEM      9580 /* Not a valid serialized item
                                              file */
#define H_ERR_END_OF_FILE             9581 /* Serialized item: premature end
                                              of file */

/* Sample-based identification */
#define H_ERR_SID_WRONG_RESIZE_METHOD 9600 /* Invalid 'image_resize_method' */
#define H_ERR_SID_WRONG_RESIZE_VALUE  9601 /* Invalid 'image_resize_value' */
#define H_ERR_SID_WRONG_RATING_METHOD 9602 /* Invalid 'rating_method' */
#define H_ERR_SID_NO_IMAGE_INFO_TYPE  9603 /* At least one type of image
                                              information must be used */
#define H_ERR_SID_MODEL_NO_COLOR      9604 /* Sample identifier does not
                                              contain color information */
#define H_ERR_SID_MODEL_NO_TEXTURE    9605 /* Sample identifier does not
                                              contain texture information */
#define H_ERR_SID_NO_IMAGE_INFO       9606 /* Sample image does not contain
                                              enough information */
#define H_ERR_SID_NO_UNPREPARED_DATA  9607 /* Sample identifier does not
                                              contain unprepared data
                                              (use
                                     add_sample_identifier_preparation_data) */
#define H_ERR_SID_MODEL_NOT_PREPARED  9608 /* Sample identifier has not been
                                              prepared yet (use
                                              prepare_sample_identifier) */
#define H_ERR_SID_NO_UNTRAINED_DATA   9609 /* Sample identifier does not
                                              contain untrained data (use
                                        add_sample_identifier_training_data) */
#define H_ERR_SID_MODEL_NOT_TRAINED   9610 /* Sample identifier has not been
                                              trained yet (use
                                              train_sample_identifier) */
#define H_ERR_SID_NO_RESULT_DATA      9611 /* Sample identifier does not
                                              contain result data */
#define H_ERR_SID_NUM_TRAIN_OBJ       9612 /* Sample identifier must contain
                                              at least two training objects
                                              (use
                                        add_sample_identifier_training_data) */

#define H_ERR_FINI_USR_THREADS        9700 /* More than one user thread still uses HALCON
                                            * resources during finalization */

/************************************************************************/


#define H_ERR_START_EXT      10000 /* User defined error codes must be
                                      larger than this value */

/************************************************************************/
/* Legacy error codes                                                   */
/************************************************************************/

/* Error codes concerning licensing */
#define H_ERR_NO_LICENSE   2003 /* No license found */
#define H_ERR_NO_LS_SERVER 2004 /* Lost connection to license server */
#define H_ERR_NO_MODULES   2005 /* No modules in license (no VENDOR_STRING) */
#define H_ERR_NO_LIC_OPER  2006 /* No license for this operator */
#define H_ERR_FLEX_LM_BAD_TZ          2007 /* Time zone offset from GMT is
                                              > 24 hours */
#define H_ERR_FLEX_LM_BADPLATFORM     2008 /* Vendor keys do not support this
                                              platform */
#define H_ERR_LM_BADKEYDATA           2009 /* Bad vendor keys */
#define H_ERR_FLEX_LM_BADVENDORDATA   2010 /* Unknown vendor key type */
#define H_ERR_FLEX_LM_CANTMALLOC      2011 /* malloc() call failed */
#define H_ERR_FLEX_LM_EXPIREDKEYS     2012 /* Vendor keys have expired */
#define H_ERR_FLEX_LM_FUNCNOTAVAIL    2013 /* Second call to lc_inti()
                                              (multiple jobs), and vendore
                                              keys do not support multiple
                                              jobs */
#define H_ERR_FLEX_LM_NOKEYDATA       2014 /* Vendor key data not supplied */
#define H_ERR_FLEX_LM_LIBRARYMISMATCH 2015 /* lmclient.h/liblmgr.a version
                                              mismatch */
#define H_ERR_FLEX_LM_NONETWORK       2016 /* Networking software not
                                              available on this machine */
#define H_ERR_FLEX_LM_OLDVENDORDATA   2017 /* Old vendor keys supplied */
#define H_ERR_FLEX_LM_BADCODE         2018 /* License key in license file does
                                              not match other data in file */
#define H_ERR_FLEX_LM_BADHANDSHAKE    2019 /* Encryption handshake with daemon
                                              failed */
#define H_ERR_FLEX_LM_BADPARAM        2020 /* 'key' structure is incorrect
                                              type, or feature == NULL,
                                              or num_licenses == 0 */
#define H_ERR_FLEX_LM_BADSYSDATE      2021 /* System clock has been set back */
#define H_ERR_FLEX_LM_BAD_VERSION     2022 /* Version argument is invalid
                                              floating point format */
#define H_ERR_FLEX_LM_BUSYNEWSERV     2023 /* License server busy starting
                                              another copy of itself */
#define H_ERR_FLEX_LM_CANTCONNECT     2024 /* Cannot establish a connection
                                              with a license server */
#define H_ERR_FLEX_LM_FEATQUEUE       2025 /* Feature is queued. lc_status
                                              will determine when it is
                                              available */
#define H_ERR_FLEX_LM_FUNC_NOT_AVAIL  2026 /* Vendor keys do not support this
                                              function */
#define H_ERR_FLEX_LM_LOCALFILTER     2027 /* Checkout request filtered by the
                                              vendor-defined filter routine */
#define H_ERR_FLEX_LM_MAXLIMIT        2028 /* Checkout exceeds MAX specified
                                              in options file */
#define H_ERR_FLEX_LM_MAXUSERS        2029 /* All licenses in use */
#define H_ERR_FLEX_LM_NO_SERVER_IN_FILE 2030 /* No license server specified
                                                for counted license */
#define H_ERR_FLEX_LM_NOFEATURE       2031 /* Can not find feature in the
                                              license file */
#define H_ERR_FLEX_LM_NOSERVSUPP      2032 /* Server has different license
                                              file than client - client's
                                              license has feature, but
                                              server's does not */
#define H_ERR_FLEX_LM_OLDVER          2033 /* License file does not support
                                              a version this new */
#define H_ERR_FLEX_LM_PLATNOTLIC      2034 /* This platform not authorized by
                                              license - running on platform
                                              not included in PLATFORMS list */
#define H_ERR_FLEX_LM_SERVBUSY        2035 /* License server busy */
#define H_ERR_FLEX_LM_NOCONFFILE      2036 /* Could not find license.dat */

#define H_ERR_FLEX_LM_BADFILE           2037 /* Invalid license file syntax */
#define H_ERR_FLEX_LM_NOSERVER          2038 /* Cannot connect to a license
                                                server */
#define H_ERR_FLEX_LM_NOSERVICE         2039 /* No TCP "license" service
                                                exists */
#define H_ERR_FLEX_LM_NOSOCKET          2040 /* No socket connection to
                                                license manager server */
#define H_ERR_FLEX_LM_NOTTHISHOST       2041 /* Invalid host */
#define H_ERR_FLEX_LM_LONGGONE          2042 /* Feature has expired */
#define H_ERR_FLEX_LM_BADDATE           2043 /* Invalid date format in license
                                                file */
#define H_ERR_FLEX_LM_BADCOMM           2044 /* Invalid returned data from
                                                license server */
#define H_ERR_FLEX_LM_BADHOST           2045 /* Cannot find SERVER hostname in
                                                network database */
#define H_ERR_FLEX_LM_CANTREAD          2046 /* Cannot read data from license
                                                server */
#define H_ERR_FLEX_LM_CANTWRITE         2047 /* Cannot write data to license
                                                server */
#define H_ERR_FLEX_LM_SELECTERR         2048 /* Error in select system call */
#define H_ERR_FLEX_LM_CHECKINBAD        2049 /* Feature checkin failure
                                                detected at license */
#define H_ERR_FLEX_LM_USERSQUEUED       2050 /* Users are queued for this
                                                feature */
#define H_ERR_FLEX_LM_SERVLONGGONE      2051 /* License server does not
                                                support this version of this
                                                feature */
#define H_ERR_FLEX_LM_TOOMANY           2052 /* Request for more licenses than
                                                this feature supports */
#define H_ERR_FLEX_LM_CANTREADKMEM      2053 /* Cannot read /dev/kmem */
#define H_ERR_FLEX_LM_CANTREADVMUNIX    2054 /* Cannot read /vmunix */
#define H_ERR_FLEX_LM_CANTFINDETHER     2055 /* Cannot find ethernet device */
#define H_ERR_FLEX_LM_NOREADLIC         2056 /* Cannot read license file */
#define H_ERR_FLEX_LM_TOOEARLY          2057 /* Feature not yet available */
#define H_ERR_FLEX_LM_NOSUCHATTR        2058 /* No such attribute */
#define H_ERR_FLEX_LM_CLOCKBAD          2059 /* Clock difference too large
                                                between client and server */
#define H_ERR_FLEX_LM_FEATCORRUPT       2060 /* Feature database corrupted in
                                                daemon */
#define H_ERR_FLEX_LM_BADFEATPARAM      2061 /* Duplicate selection mismatch
                                                for this feature */
#define H_ERR_FLEX_LM_FEATEXCLUDE       2062 /* User/host on EXCLUDE list for
                                                feature */
#define H_ERR_FLEX_LM_FEATNOTINCLUDE    2063 /* User/host not on INCLUDE list
                                                for feature */
#define H_ERR_FLEX_LM_NEVERCHECKOUT     2064 /* Feature was never checked
                                                out */
#define H_ERR_FLEX_LM_BADKEYDATA        2065 /* Invalid FLEXlm key data
                                                supplied */
#define H_ERR_FLEX_LM_NOCLOCKCHECK      2066 /* Clock setting check not
                                                available in daemon */
#define H_ERR_FLEX_LM_DATE_TOOBIG       2067 /* Date too late for binary
                                                format */
#define H_ERR_FLEX_LM_NOFLEXLMINIT      2068 /* FLEXlm not initialized */
#define H_ERR_FLEX_LM_NOSERVRESP        2069 /* Server did not respond to
                                                message */
#define H_ERR_FLEX_LM_CHECKOUTFILTERED  2070 /* Request rejected by vendor
                                                defined filter */
#define H_ERR_FLEX_LM_NOFEATSET         2071 /* No FEATURESET line present in
                                                license file */
#define H_ERR_FLEX_LM_BADFEATSET        2072 /* Incorrect FEATURESET line in
                                                license file */
#define H_ERR_FLEX_LM_CANTCOMPUTEFEATSET 2073 /* Cannot compute FEATURESET
                                                 line */
#define H_ERR_FLEX_LM_SOCKETFAIL        2074 /* socket() call failed */
#define H_ERR_FLEX_LM_SETSOCKFAIL       2075 /* setsockopt() failed */
#define H_ERR_FLEX_LM_BADCHECKSUM       2076 /* Message checksum failure */
#define H_ERR_FLEX_LM_SERVNOREADLIC     2077 /* Cannot read license file from
                                                server */
#define H_ERR_FLEX_LM_NOTLICADMIN       2078 /* Not a license administrator */
#define H_ERR_FLEX_LM_REMOVETOOSOON     2079 /* lmremove request too soon */
#define H_ERR_FLEX_LM_ENDPATH           2080 /* Attempt to read beyond the end
                                                of LF path */
#define H_ERR_FLEX_LM_VMS_SETIMR_FAILED 2081 /* SYS$SETIMR call failed */
#define H_ERR_FLEX_LM_INTERNAL_ERROR    2082 /* Internal FLEXlm Erro - Please
                                                report to Globetrotter
                                                Software */
#define H_ERR_FLEX_LM_NOADMINAPI        2083 /* FLEXadmin API functions not
                                                avilable */
#define H_ERR_FLEX_LM_BADPKG            2084 /* Invalid PACKAGE line in
                                                license file */
#define H_ERR_FLEX_LM_SERVOLDVER        2085 /* Server FLEXlm version older
                                                than client's */
#define H_ERR_FLEX_LM_USER_BASED        2086 /* Incorrect number of USERS/HOSTS
                                                INCLUDED in options file */
#define H_ERR_FLEX_LM_NOSERVCAP         2087 /* Server doesn't support this
                                                request */
#define H_ERR_FLEX_LM_OBJECTUSED        2088 /* This license object already in
                                                use */

#define H_ERR_FLEX_LM_FUTURE_FILE       2089 /* Future license file format */
#define H_ERR_FLEX_LM_SERVER_REMOVED    2090 /* Feature removed during
                                                lmreread */
#define H_ERR_FLEX_LM_POOL              2091 /* This feature is available in a
                                                different license pool */
#define H_ERR_FLEX_LM_NOT_THIS_HOST     2092 /* Network connect to THIS_HOST
                                                failed */
#define H_ERR_FLEX_LM_HOSTDOWN          2093 /* Server node is down or not
                                                responding */
#define H_ERR_FLEX_LM_VENDOR_DOWN       2094 /* The desired vendor daemon is
                                                down */
#define H_ERR_FLEX_LM_BADDECFILE        2095 /* The decimal format license is
                                                typed incorrectly */
#define H_ERR_FLEX_LM_RESVFOROTHERS     2096 /* All licenses are reserved for
                                                others */
#define H_ERR_FLEX_LM_TSOK_ERR          2097 /* Terminal Server remote client
                                                not allowed */
#define H_ERR_FLEX_LM_BORROW_TOOLONG    2098 /* Cannot borrow that long */
#define H_ERR_FLEX_LM_SERVER_MAXED_OUT  2099 /* License server out of network
                                                connections */
#define H_ERR_FLEX_LM_NODONGLE          2300 /* Dongle not attached, or can't
                                                read dongle */
#define H_ERR_FLEX_LM_NODONGLEDRIVER    2301 /* Missing dongle driver */
#define H_ERR_FLEX_LM_FLEXLOCK2CKOUT    2302 /* FLEXlock checkouts attempted */
#define H_ERR_FLEX_LM_SIGN_REQ          2303 /* SIGN= attribute required */
#define H_ERR_FLEX_LM_NOCROSUPPORT      2304 /* CRO not supported for this
                                                platform */
#define H_ERR_FLEX_LM_BORROW_LINGER_ERR 2305 /* BORROW failed */
#define H_ERR_FLEX_LM_BORROW_EXPIRED    2306 /* BORROW period has expired */
#define H_ERR_FLEX_LM_FLOATOK_ONEHOSTID 2307 /* FLOAT_OK license must have
                                                exactly one dongle hostid */
#define H_ERR_FLEX_LM_BORROW_DELETE_ERR 2308 /* Unable to delete local borrow
                                                info" */
#define H_ERR_FLEX_LM_BORROW_RETURN_EARLY_ERR    2309 /* Returning borrowed
                                                         license early
                                                         not enabled */
#define H_ERR_FLEX_LM_BORROW_RETURN_SERVER_ERR   2310 /* Returning borrowed
                                                         license on server
                                                         failed */
#define H_ERR_FLEX_LM_CANT_CHECKOUT_JUST_PACKAGE 2311 /* Checkout just a
                                                         PACKAGE failed*/
#define H_ERR_FLEX_LM_COMPOSITEID_INIT_ERR 2312 /* Composite Hostid not
                                                   initialized */
#define H_ERR_FLEX_LM_COMPOSITEID_ITEM_ERR 2313 /* An item needed for Composite
                                                   Hostid missing or invalid */
#define H_ERR_FLEX_LM_BORROW_MATCH_ERR   2314 /* Borrowed license doesn't match
                                                 any known server license */
#define H_ERR_FLEX_LM_EVENTLOG_INIT_ERR  2315 /* Error enabling event log */
#define H_ERR_FLEX_LM_EVENTLOG_DISABLED  2316 /* Event logging is disabled */
#define H_ERR_FLEX_LM_EVENTLOG_WRITE_ERR 2317 /* Error writing to event log */
#define H_ERR_FLEX_LM_TIMEOUT            2318 /* Timeout */
#define H_ERR_FLEX_LM_BADCOMMAND         2319 /* Bad message command */
#define H_ERR_FLEX_LM_SOCKET_BROKEN_PIPE 2320 /* Error writing to socket */
#define H_ERR_FLEX_LM_INVALID_SIGNATURE  2321 /* Failed to generate version
                                                 specific license */
#define H_ERR_FLEX_LM_UNCOUNTED_NOT_SUPPORTED 2322 /* Vers.-specific signatures
                                                      not supported */
#define H_ERR_FLEX_LM_REDUNDANT_SIGNATURES 2323 /* License template contains
                                                   redundant signature
                                                   specifiers */
#define H_ERR_FLEX_LM_BADCODE_V71_LK    2324 /* Invalid V71_LK signature */
#define H_ERR_FLEX_LM_BADCODE_V71_SIGN  2325 /* Invalid V71_SIGN signature */
#define H_ERR_FLEX_LM_BADCODE_V80_LK    2326 /* Invalid V80_LK signature */
#define H_ERR_FLEX_LM_BADCODE_V80_SIGN  2327 /* Invalid V80_SIGN signature */
#define H_ERR_FLEX_LM_BADCODE_V81_LK    2328 /* Invalid V81_LK signature */
#define H_ERR_FLEX_LM_BADCODE_V81_SIGN  2329 /* Invalid V81_SIGN signature */
#define H_ERR_FLEX_LM_BADCODE_V81_SIGN2 2330 /* Invalid V81_SIGN2 signature */
#define H_ERR_FLEX_LM_BADCODE_V84_LK    2331 /* Invalid V84_LK signature */
#define H_ERR_FLEX_LM_BADCODE_V84_SIGN  2332 /* Invalid V84_SIGN signature */
#define H_ERR_FLEX_LM_BADCODE_V84_SIGN2 2333 /* Invalid V84_SIGN2 signature */
#define H_ERR_FLEX_LM_LK_REQ            2334 /* License key required but
                                                missing from the certificate */
#define H_ERR_FLEX_LM_BADAUTH           2335 /* Bad AUTH={} signature */
#define H_ERR_FLEX_LM_REPAIR_NEEDED     2336 /* TS record invalid */
#define H_ERR_FLEX_LM_TS_OPEN           2337 /* Cannot open TS */
#define H_ERR_FLEX_LM_BAD_FULFILLMENT   2338 /* Invalid Fulfillment record */
#define H_ERR_FLEX_LM_BAD_ACTREQ        2339 /* Invalid activation request
                                                received */
#define H_ERR_FLEX_LM_TS_NO_FULFILL_MATCH 2340 /* No fulfillment exists in
                                                  trusted storage which matches
                                                  the request */
#define H_ERR_FLEX_LM_BAD_ACT_RESP      2341 /* Invalid activation response
                                                received */
#define H_ERR_FLEX_LM_CANTRETURN        2342 /* Can't return the fulfillment */
#define H_ERR_FLEX_LM_RETURNEXCEEDSMAX  2343 /* Return would exceed max
                                                count(s) */
#define H_ERR_FLEX_LM_NO_REPAIRS_LEFT   2344 /* No repair count left */
#define H_ERR_FLEX_LM_NOT_ALLOWED       2345 /* Specified operation is not
                                                allowed */
#define H_ERR_FLEX_LM_ENTLEXCLUDE       2346 /* User/host on EXCLUDE list for
                                                entitlement */
#define H_ERR_FLEX_LM_ENTLNOTINCLUDE    2347 /* User/host not in INCLUDE list
                                                for entitlement */
#define H_ERR_FLEX_LM_ACTIVATION        2348 /* Activation error */
#define H_ERR_FLEX_LM_TS_BADDATE        2349 /* Invalid date format in trusted
                                                storage */
#define H_ERR_FLEX_LM_ENCRYPTION_FAILED 2350 /* Message encryption failed */
#define H_ERR_FLEX_LM_DECRYPTION_FAILED 2351 /* Message decryption failed */
#define H_ERR_FLEX_LM_BADCONTEXT        2352 /* Bad filter context */
#define H_ERR_FLEX_LM_SUPERSEDE_CONFLICT 2353 /* SUPERSEDE feature conflict */
#define H_ERR_FLEX_LM_INVALID_SUPERSEDE_SIGN 2354 /* Invalid SUPERSEDE_SIGN
                                                     syntax */
#define H_ERR_FLEX_LM_SUPERSEDE_SIGN_EMPTYSTRING 2355 /* SUPERSEDE_SIGN does
                                                         not contain a feature
                                                         name and license
                                                         signature */
#define H_ERR_FLEX_LM_ONE_TSOK_PLATFORM_ERR 2356 /* ONE_TS_OK is not supported
                                                    in this Windows Platform */
#define H_ERR_FLEX_LM_ONE_TSOK_MTX_ERR  2357 /* Internal error */
#define H_ERR_FLEX_LM_ONE_TSOK_ERR      2358 /* Only one terminal server
                                                remote client checkout is
                                                allowed for this feature */
#define H_ERR_FLEX_LM_SSIDNULL          2359 /* Internal error */
#define H_ERR_FLEX_LM_SMTXNOTREL        2360 /* Internal error */
#define H_ERR_FLEX_LM_MTXNOPERM         2361 /* Internal error */
#define H_ERR_FLEX_LM_COMPOSITEID_ETHER_ERR 2362 /* More than one ethernet
                                                    hostid not supported in
                                                    composite hostid
                                                    definition */
#define H_ERR_FLEX_LM_LIC_FILE_CHAR_EXCEED 2363 /* The number of characters in
                                                   the license file paths
                                                   exceeds the permissible
                                                   limit */
#define H_ERR_FLEX_LM_TZ_INVALID_SYNTAX 2364 /* Invalid TZ keyword syntax */
#define H_ERR_FLEX_LM_TZ_INVALID_TZONE_SPEC 2365 /* Invalid time zone override
                                                    specification in the
                                                    client */
#define H_ERR_FLEX_LM_TZ_INVALID_TZONE_INFO 2366 /* The time zone information
                                                    could not be obtained */
#define H_ERR_FLEX_LM_TZ_UNAUTHORIZED   2367 /* License client time zone not
                                                authorized for license
                                                rights */
#define H_ERR_FLEX_LM_INVALID_VM_PLATFORMS 2368 /* Invalid syntax for
                                                   VM_PLATFORMS keyword */
#define H_ERR_FLEX_LM_VM_PHYSICAL_ONLY  2369 /* Feature can be checked out
                                                from physical machine only */
#define H_ERR_FLEX_LM_VM_VIRTUAL_ONLY   2370 /* Feature can be checked out
                                                from virtual machine only */
#define H_ERR_FLEX_LM_VM_BAD_KEY        2371 /* Vendor keys do not support
                                                Virtualization feature */
#define H_ERR_FLEX_LM_MAXLIMIT_EXCEED   2372 /* Checkout request denied as it
                                                exceeds the MAX limit
                                                specified in the options
                                                file */
#define H_ERR_FLEX_LM_BA_API_INTERNAL_ERROR 2373 /* Binding agent API -
                                                    Internal error */
#define H_ERR_FLEX_LM_BA_COMM_ERROR     2374 /* Binding agent communication
                                                error */
#define H_ERR_FLEX_LM_INVALID_BA_VERSION 2375 /* Invalid Binding agent
                                                 version */
#define H_ERR_FLEX_LM_SERVERQUERY_LOAD_REQUEST_FAILED 2376
                                              /* Failed to load ServerQuery
                                                 request */
#define H_ERR_FLEX_LM_SERVERQUERY_RESPONSE_FAILED 2377
                                              /* Failed to generate ServerQuery
                                                 response */
#define H_ERR_FLEX_LM_INVALID_IPADDRESS 2378  /* Invalid IP address used while
                                                 overriding */

/* Adapt this to be the highest error code concerning FlexLM */
#define H_ERR_LAST_FLEX_LM_ERROR H_ERR_FLEX_LM_INVALID_IPADDRESS

#endif



