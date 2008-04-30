/*
 * Copyright (c) 2004-2008 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2006 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

/** @file:
 *
 * Populates global structure with system-specific information.
 *
 * Notes: add limits.h, compute size of integer and other types via sizeof(type)*CHAR_BIT
 *
 */

#ifndef _ORTE_NAME_FNS_H_
#define _ORTE_NAME_FNS_H_

#include "orte_config.h"
#include "orte/types.h"

#include "opal/class/opal_list.h"

BEGIN_C_DECLS

typedef uint8_t  orte_ns_cmp_bitmask_t;  /**< Bit mask for comparing process names */
#define ORTE_NS_CMP_NONE       0x00
#define ORTE_NS_CMP_JOBID      0x02
#define ORTE_NS_CMP_VPID       0x04
#define ORTE_NS_CMP_ALL        0Xff

/* useful define to print name args in output messages */
ORTE_DECLSPEC char* orte_util_print_name_args(const orte_process_name_t *name);
#define ORTE_NAME_PRINT(n) \
    orte_util_print_name_args(n)

ORTE_DECLSPEC char* orte_util_print_jobids(const orte_jobid_t job);
#define ORTE_JOBID_PRINT(n) \
    orte_util_print_jobids(n)

ORTE_DECLSPEC char* orte_util_print_vpids(const orte_vpid_t vpid);
#define ORTE_VPID_PRINT(n) \
    orte_util_print_vpids(n)


/* a macro for identifying the job family - i.e., for
 * extracting the mpirun-specific id field of the jobid
 */
#define ORTE_JOB_FAMILY(n) \
    (((n) >> 16) & 0x0000ffff)


/* List of names for general use */
struct orte_namelist_t {
    opal_list_item_t item;      /**< Allows this item to be placed on a list */
    orte_process_name_t name;   /**< Name of a process */
};
typedef struct orte_namelist_t orte_namelist_t;

ORTE_DECLSPEC OBJ_CLASS_DECLARATION(orte_namelist_t);

ORTE_DECLSPEC int orte_util_convert_jobid_to_string(char **jobid_string, const orte_jobid_t jobid);
ORTE_DECLSPEC int orte_util_convert_string_to_jobid(orte_jobid_t *jobid, const char* jobidstring);
ORTE_DECLSPEC int orte_util_convert_vpid_to_string(char **vpid_string, const orte_vpid_t vpid);
ORTE_DECLSPEC int orte_util_convert_string_to_vpid(orte_vpid_t *vpid, const char* vpidstring);
ORTE_DECLSPEC int orte_util_convert_string_to_process_name(orte_process_name_t *name,
                                             const char* name_string);
ORTE_DECLSPEC int orte_util_convert_process_name_to_string(char** name_string,
                                             const orte_process_name_t *name);
ORTE_DECLSPEC int orte_util_create_process_name(orte_process_name_t **name,
                                  orte_jobid_t job,
                                  orte_vpid_t vpid);
ORTE_DECLSPEC int orte_util_compare_name_fields(orte_ns_cmp_bitmask_t fields,
                                  const orte_process_name_t* name1,
                                  const orte_process_name_t* name2);
/** This funtion returns a guaranteed unique hash value for the passed process name */
ORTE_DECLSPEC uint64_t orte_util_hash_name(const orte_process_name_t * name);

END_C_DECLS
#endif
