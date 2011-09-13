/*
 * Copyright 2011 Tresys Technology, LLC. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 * 
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY TRESYS TECHNOLOGY, LLC ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL TRESYS TECHNOLOGY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of Tresys Technology, LLC.
 */

#ifndef CIL_H_
#define CIL_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

#include "cil_symtab.h"
#include "cil_mem.h"

#define CIL_MAX_NAME_LENGTH 2048

/*
	Tree/list node types
*/
#define CIL_MIN_DECLARATIVE	500

enum cil_flavor {
	CIL_ROOT = 0,
	CIL_DB,
	CIL_AST_NODE,
	CIL_PARSE_NODE,
	CIL_AST_STR,
	CIL_LIST,
	CIL_LIST_ITEM,
	CIL_INT,
	CIL_FILES,
	CIL_AVRULE,
	CIL_SENS_DOM,
	CIL_BLOCKINHERIT,
	CIL_IN,
	CIL_FILECON,
	CIL_PORTCON,
	CIL_NODECON,
	CIL_GENFSCON,
	CIL_NETIFCON,
	CIL_PIRQCON,
	CIL_IOMEMCON,
	CIL_IOPORTCON,
	CIL_PCIDEVICECON,
	CIL_FSUSE,
	CIL_CONSTRAIN,
	CIL_MLSCONSTRAIN,
	CIL_PERM,
	CIL_CLASSMAPPERM,
	CIL_CLASSMAPPING,
	CIL_USERROLE,
	CIL_USERLEVEL,
	CIL_USERRANGE,
	CIL_USERBOUNDS,
	CIL_TYPEATTRIBUTETYPES,
	CIL_TYPE_RULE,
	CIL_TYPEBOUNDS,
	CIL_FILETRANSITION,
	CIL_RANGETRANSITION,
	CIL_TYPEPERMISSIVE,
	CIL_ROLETRANSITION,
	CIL_ROLEALLOW,
	CIL_ROLETYPE,
	CIL_ROLEDOMINANCE,
	CIL_ROLEBOUNDS,
	CIL_CATORDER,
	CIL_DOMINANCE,
	CIL_SENSCAT,
	CIL_CLASSCOMMON,
	CIL_SIDCONTEXT,
	CIL_CALL,
	CIL_ARGS,
	CIL_BOOLEANIF,
	CIL_TUNABLEIF,
	CIL_CONDTRUE,
	CIL_CONDFALSE,
	CIL_TUNABLEIFDEF,
	CIL_TUNABLEIFNDEF,

	CIL_AND,
	CIL_OR,
	CIL_XOR,
	CIL_NOT,
	CIL_EQ,
	CIL_NEQ,
	CIL_COND,
	CIL_PARAM,
	CIL_CONS_DOM,
	CIL_CONS_DOMBY,
	CIL_CONS_INCOMP,
	CIL_CONS_U1,
	CIL_CONS_U2,
	CIL_CONS_T1,
	CIL_CONS_T2,
	CIL_CONS_R1,
	CIL_CONS_R2,
	CIL_CONS_L1,
	CIL_CONS_L2,
	CIL_CONS_H1,
	CIL_CONS_H2,

	CIL_BLOCK = CIL_MIN_DECLARATIVE,
	CIL_CLASS,
	CIL_CLASSMAP,
	CIL_COMMON,
	CIL_SID,
	CIL_USER,
	CIL_ROLE,
	CIL_TYPE,
	CIL_TYPEATTRIBUTE,
	CIL_BOOL,
	CIL_PERMSET,
	CIL_CLASSPERMSET,
	CIL_TUNABLE,
	CIL_TYPEALIAS,
	CIL_CONTEXT,
	CIL_LEVEL,
	CIL_LEVELRANGE,
	CIL_SENS,
	CIL_CAT,
	CIL_SENSALIAS,
	CIL_CATALIAS,
	CIL_CATRANGE,
	CIL_CATSET,
	CIL_MACRO,
	CIL_OPTIONAL,
	CIL_POLICYCAP,
	CIL_IPADDR
};

/*
	Keywords
*/
#define CIL_KEY_BLOCK 		"block"
#define CIL_KEY_BLOCKINHERIT	"blockinherit"
#define CIL_KEY_CLASS		"class"
#define CIL_KEY_PERM		"perm"
#define CIL_KEY_PERMSET		"permissionset"
#define CIL_KEY_CLASSPERMSET	"classpermissionset"
#define CIL_KEY_CLASSMAP	"classmap"
#define CIL_KEY_CLASSMAPPING	"classmapping"
#define CIL_KEY_COMMON		"common"
#define CIL_KEY_CLASSCOMMON	"classcommon"
#define CIL_KEY_SID		"sid"
#define CIL_KEY_SIDCONTEXT	"sidcontext"
#define CIL_KEY_USER		"user"
#define CIL_KEY_USERBOUNDS	"userbounds"
#define CIL_KEY_ROLE 		"role"
#define CIL_KEY_USERROLE	"userrole"
#define CIL_KEY_USERLEVEL	"userlevel"
#define CIL_KEY_USERRANGE	"userrange"
#define CIL_KEY_ROLETYPE	"roletype"
#define CIL_KEY_ROLETRANSITION	"roletransition"
#define CIL_KEY_ROLEALLOW	"roleallow"
#define CIL_KEY_ROLEDOMINANCE	"roledominance"
#define CIL_KEY_ROLEBOUNDS	"rolebounds"
#define CIL_KEY_TYPE 		"type"
#define CIL_KEY_SELF		"self"
#define CIL_KEY_TYPEATTRIBUTE	"typeattribute"
#define CIL_KEY_BOOL		"boolean"
#define CIL_KEY_ALLOW		"allow"
#define CIL_KEY_AUDITALLOW	"auditallow"
#define CIL_KEY_DONTAUDIT	"dontaudit"
#define CIL_KEY_NEVERALLOW	"neverallow"
#define CIL_KEY_TYPETRANS	"typetransition"
#define CIL_KEY_RANGETRANSITION	"rangetransition"
#define CIL_KEY_FILETRANSITION	"filetransition"
#define CIL_KEY_TYPECHANGE	"typechange"
#define CIL_KEY_TYPEMEMBER	"typemember"
#define CIL_KEY_TYPEATTRIBUTETYPES	"typeattributetypes"
#define CIL_KEY_TYPEALIAS	"typealias"
#define CIL_KEY_TYPEBOUNDS	"typebounds"
#define CIL_KEY_TYPEPERMISSIVE	"typepermissive"
#define CIL_KEY_MACRO		"macro"
#define CIL_KEY_CALL		"call"
#define CIL_KEY_POLICYCAP	"policycap"
#define CIL_KEY_CONTEXT		"context"
#define CIL_KEY_FILECON		"filecon"
#define CIL_KEY_PORTCON		"portcon"
#define CIL_KEY_NODECON		"nodecon"
#define CIL_KEY_GENFSCON	"genfscon"
#define CIL_KEY_NETIFCON	"netifcon"
#define CIL_KEY_PIRQCON		"pirqcon"
#define CIL_KEY_IOMEMCON	"iomemcon"
#define CIL_KEY_IOPORTCON	"ioportcon"
#define CIL_KEY_PCIDEVICECON	"pcidevicecon"
#define CIL_KEY_FSUSE		"fsuse"
#define CIL_KEY_SENSITIVITY	"sensitivity"
#define CIL_KEY_SENSALIAS	"sensitivityalias"
#define CIL_KEY_CATEGORY	"category"
#define CIL_KEY_CATALIAS	"categoryalias"
#define CIL_KEY_CATRANGE	"categoryrange"
#define CIL_KEY_CATSET		"categoryset"
#define CIL_KEY_CATORDER	"categoryorder"
#define CIL_KEY_DOMINANCE	"dominance"
#define CIL_KEY_SENSCAT		"sensitivitycategory"
#define CIL_KEY_LEVEL		"level"
#define CIL_KEY_LEVELRANGE	"levelrange"
#define CIL_KEY_MLSCONSTRAIN	"mlsconstrain"
#define CIL_KEY_CONSTRAIN	"constrain"
#define CIL_KEY_BOOLEANIF	"booleanif"
#define CIL_KEY_TUNABLE		"tunable"
#define CIL_KEY_TUNABLEIF	"tunableif"
#define CIL_KEY_CONDTRUE	"true"
#define CIL_KEY_CONDFALSE	"false"
#define CIL_KEY_TUNABLEIFDEF	"tunableifdef"
#define CIL_KEY_TUNABLEIFNDEF	"tunableifndef"
#define CIL_KEY_AND		"and"
#define CIL_KEY_OR		"or"
#define CIL_KEY_XOR		"xor"
#define CIL_KEY_NOT		"not"
#define CIL_KEY_EQ		"eq"
#define CIL_KEY_NEQ		"neq"
#define CIL_KEY_OPTIONAL	"optional"
#define CIL_KEY_IPADDR		"ipaddr"
#define CIL_KEY_UDP		"udp"
#define CIL_KEY_TCP		"tcp"

#define CIL_KEY_CONS_DOM	"dom"
#define CIL_KEY_CONS_DOMBY	"domby"
#define CIL_KEY_CONS_INCOMP	"incomp"
#define CIL_KEY_CONS_U1		"u1"
#define CIL_KEY_CONS_U2		"u2"
#define CIL_KEY_CONS_T1		"t1"
#define CIL_KEY_CONS_T2		"t2"
#define CIL_KEY_CONS_R1		"r1"
#define CIL_KEY_CONS_R2		"r2"
#define CIL_KEY_CONS_L1		"l1"
#define CIL_KEY_CONS_L2		"l2"
#define CIL_KEY_CONS_H1		"h1"
#define CIL_KEY_CONS_H2		"h2"

/*
	Symbol Table Array Indices
*/
enum cil_sym_index {
	CIL_SYM_FILENAMES = 0,
	CIL_SYM_BLOCKS,
	CIL_SYM_USERS,
	CIL_SYM_ROLES,
	CIL_SYM_TYPES,
	CIL_SYM_COMMONS,
	CIL_SYM_CLASSES,
	CIL_SYM_PERMSETS,
	CIL_SYM_CLASSPERMSETS,
	CIL_SYM_BOOLS,
	CIL_SYM_TUNABLES,
	CIL_SYM_SENS,
	CIL_SYM_CATS,
	CIL_SYM_SIDS,
	CIL_SYM_FILECONS,
	CIL_SYM_PORTCONS,
	CIL_SYM_NETIFCONS,
	CIL_SYM_MACROS,
	CIL_SYM_CONTEXTS,
	CIL_SYM_LEVELS,
	CIL_SYM_LEVELRANGES,
	CIL_SYM_POLICYCAPS,
	CIL_SYM_OPTIONALS,
	CIL_SYM_IPADDRS,
	CIL_SYM_NUM,
	CIL_SYM_UNKNOWN,
};

#define CIL_SYM_SIZE		256

struct cil_db {
	struct cil_tree *ast;
	symtab_t symtab[CIL_SYM_NUM];
	struct cil_type *selftype;
	struct cil_list *catorder;
	struct cil_list *dominance;
	struct cil_sort *netifcon;
	struct cil_sort *genfscon;
	struct cil_sort *filecon;
	struct cil_sort *nodecon;
	struct cil_sort *portcon;
	struct cil_sort *pirqcon;
	struct cil_sort *iomemcon;
	struct cil_sort *ioportcon;
	struct cil_sort *pcidevicecon;
	struct cil_sort *fsuse;
};

struct cil_sort {
	enum cil_flavor flavor;
	uint32_t count;
	uint32_t index;
	void **array;
};

struct cil_block {
	struct cil_symtab_datum datum;
	symtab_t symtab[CIL_SYM_NUM];
	/* TODO CDS eventually, these should probably become a flags bit vector */
	uint16_t is_abstract;
	/* TODO CDS we need to figure out how to handle conditionals */
	char *condition;
};

struct cil_blockinherit {
	char *block_str;
};

struct cil_optional {
	struct cil_symtab_datum datum;
};

struct cil_class {
	struct cil_symtab_datum datum;
	symtab_t perms;
	struct cil_common *common;
};

struct cil_perm {
	struct cil_symtab_datum datum;
};

struct cil_permset {
	struct cil_symtab_datum datum;
	struct cil_list *perms_list_str;
};

struct cil_classpermset {
	struct cil_symtab_datum datum;
	char *class_str;
	void *class;
	enum cil_flavor flavor;
	char *permset_str;
	struct cil_permset *permset;
	struct cil_list *perms;
};

struct cil_classmap_perm {
	struct cil_symtab_datum datum;
	struct cil_list *classperms;
};

struct cil_classmap {
	struct cil_symtab_datum datum;
	symtab_t perms;
};

struct cil_classmapping {
	char *classmap_str;
	char *classmap_perm_str;
	struct cil_list *classpermsets_str;
};

struct cil_common {
	struct cil_symtab_datum datum;
	symtab_t perms;
};

struct cil_classcommon {
	char *class_str;
	char *common_str;
};

struct cil_sid {
	struct cil_symtab_datum datum;
	struct cil_context *context;
};

struct cil_sidcontext {
	char *sid_str;
	char *context_str;
	struct cil_context *context;
};

struct cil_user {
	struct cil_symtab_datum datum;
	struct cil_user *bounds;
	struct cil_list *roles;
	struct cil_level *dftlevel;
	struct cil_levelrange *range;
};

struct cil_userrole {
	char *user_str;
	struct cil_user *user;
	char *role_str;
	struct cil_role *role;
};

struct cil_userlevel {
	char *user_str;
	char *level_str;
	struct cil_level *level;
};

struct cil_userrange {
	char *user_str;
	char *range_str;
	struct cil_levelrange *range;
};

struct cil_userbounds {
	char *user_str;
	char *bounds_str;
};

struct cil_role {
	struct cil_symtab_datum datum;
	struct cil_list *types;
	struct cil_role *bounds;
};

/* TODO Waiting on design */
struct cil_roledominance {
	char *role_str;
	struct cil_role *role;
	char *domed_str;
	struct cil_role *domed;
};

struct cil_roletype {
	char *role_str;
	struct cil_role *role;
	char *type_str;
	void *type; /* type, alias, or attribute */
};

struct cil_rolebounds {
	char *role_str;
	char *bounds_str;
};

struct cil_type	{
	struct cil_symtab_datum datum;
	void *bounds; /* type or alias */
};

struct cil_typeattribute {
	struct cil_symtab_datum datum;
	struct cil_list *types_list;
	struct cil_list *neg_list;
};

struct cil_typeattributetypes {
	char *attr_str;
	struct cil_list *types_list_str; /* list of types, aliases, and attributes */
	struct cil_list *neg_list_str; /* list of types, aliases, and attributes */
};

struct cil_typealias {
	struct cil_symtab_datum datum;
	char *type_str;
	void *type; /* type or alias */
};

struct cil_typebounds {
	char *type_str;
	char *bounds_str;
};

struct cil_typepermissive {
	char *type_str;
	void *type; /* type or alias */
};

struct cil_filetransition {
	char *src_str;
	void *src; /* type, alias, or attribute */
	char *exec_str;
	void *exec; /* type, alias, or attribute */
	char *proc_str;
	struct cil_class *proc;
	char *dest_str;
	void *dest; /* type or alias */
	char *path_str;
};

struct cil_rangetransition {
	char *src_str;
	void *src; /* type, alias, or attribute */
	char *exec_str;
	void *exec; /* type, alias, or attribute */
	char *obj_str;
	struct cil_class *obj;
	char *range_str;
	struct cil_levelrange *range;
};

struct cil_bool {
	struct cil_symtab_datum datum;
	uint16_t value;
};

#define CIL_AVRULE_ALLOWED     1
#define CIL_AVRULE_AUDITALLOW  2
#define CIL_AVRULE_DONTAUDIT   8
#define CIL_AVRULE_NEVERALLOW 128
#define CIL_AVRULE_AV         (AVRULE_ALLOWED | AVRULE_AUDITALLOW | AVRULE_DONTAUDIT | AVRULE_NEVERALLOW)
struct cil_avrule {
	uint32_t rule_kind;
	char *src_str;
	void *src; /* type, alias, or attribute */
	char *tgt_str;	
	void *tgt; /* type, alias, or attribute */
	char *classpermset_str;
	struct cil_classpermset *classpermset;
};

#define CIL_TYPE_TRANSITION 16
#define CIL_TYPE_MEMBER     32
#define CIL_TYPE_CHANGE     64
#define CIL_AVRULE_TYPE       (AVRULE_TRANSITION | AVRULE_MEMBER | AVRULE_CHANGE)
struct cil_type_rule {
	uint32_t rule_kind;
	char *src_str;
	void *src; /* type, alias, or attribute */
	char *tgt_str;
	void *tgt; /* type, alias, or attribute */
	char *obj_str;
	struct cil_class *obj;
	char *result_str;
	void *result; /* type or alias */
};

struct cil_roletransition {
	char *src_str;
	struct cil_role *src;
	char *tgt_str;	
	void *tgt; /* type, alias, or attribute */
	char *obj_str;
	struct cil_class *obj;
	char *result_str;
	struct cil_role *result;
};

struct cil_roleallow {
	char *src_str;
	struct cil_role *src;
	char *tgt_str;
	struct cil_role *tgt;
};

struct cil_sens {
	struct cil_symtab_datum datum;
	struct cil_list *catsets;
};

struct cil_sensalias {
	struct cil_symtab_datum datum;
	char *sens_str;
	struct cil_sens *sens;
};

struct cil_sens_dominates {
	struct cil_list *sens_list_str;
};

struct cil_cat {
	struct cil_symtab_datum datum;
};

struct cil_catalias {
	struct cil_symtab_datum datum;
	char *cat_str;
	struct cil_cat *cat;
};

struct cil_catrange {
	struct cil_symtab_datum datum;
	char *cat_low_str;
	struct cil_cat *cat_low;
	char *cat_high_str;
	struct cil_cat *cat_high;
};

struct cil_catset {
	struct cil_symtab_datum datum;
	struct cil_list *cat_list_str;
	struct cil_list *cat_list;
};

struct cil_catorder {
	struct cil_list *cat_list_str;
};

struct cil_senscat {
	char *sens_str;
	char *catset_str;
	struct cil_catset *catset;
};

struct cil_level {
	struct cil_symtab_datum datum;
	char *sens_str;
	struct cil_sens *sens;
	char *catset_str;
	struct cil_catset *catset;
};

struct cil_levelrange {
	struct cil_symtab_datum datum;
	char *low_str;
	struct cil_level *low;
	char *high_str;
	struct cil_level *high;
};

struct cil_context {
	struct cil_symtab_datum datum;
	char *user_str;
	struct cil_user *user;
	char *role_str;
	struct cil_role *role;
	char *type_str;
	void *type; /* type or alias */
	char *range_str;
	struct cil_levelrange *range;
};

enum cil_filecon_types {
	CIL_FILECON_FILE = 1,
	CIL_FILECON_DIR,
	CIL_FILECON_CHAR,
	CIL_FILECON_BLOCK,
	CIL_FILECON_SOCKET,
	CIL_FILECON_PIPE,
	CIL_FILECON_SYMLINK,
	CIL_FILECON_ANY
};

struct cil_filecon {
	char *root_str;
	char *path_str;
	enum cil_filecon_types type;
	char *context_str;
	struct cil_context *context;
};

enum cil_protocol {
	CIL_PROTOCOL_UDP = 1,
	CIL_PROTOCOL_TCP	
};

struct cil_portcon {
	enum cil_protocol proto;
	uint32_t port_low;
	uint32_t port_high;
	char *context_str;
	struct cil_context *context;
};

struct cil_nodecon {
	char *addr_str;
	struct cil_ipaddr *addr;
	char *mask_str;
	struct cil_ipaddr *mask;
	char *context_str;
	struct cil_context *context;
};

struct cil_ipaddr {
	struct cil_symtab_datum datum;
	int family;
	union {
		struct in_addr v4;
		struct in6_addr v6;
	} ip;
};

struct cil_genfscon {
	char *fs_str;
	char *path_str;
	char *context_str;
	struct cil_context *context;
};

struct cil_netifcon {
	char *interface_str;
	char *if_context_str;
	struct cil_context *if_context;
	char *packet_context_str;
	struct cil_context *packet_context;
	char *context_str;
};

struct cil_pirqcon {
	uint32_t pirq;
	char *context_str;
	struct cil_context *context;
};

struct cil_iomemcon {
	uint32_t iomem_low;
	uint32_t iomem_high;
	char *context_str;
	struct cil_context *context;
};

struct cil_ioportcon {
	uint32_t ioport_low;
	uint32_t ioport_high;
	char *context_str;
	struct cil_context *context;
};

struct cil_pcidevicecon {
	uint32_t dev;
	char *context_str;
	struct cil_context *context;
};

enum cil_fsuse_types {
	CIL_FSUSE_XATTR = 1,
	CIL_FSUSE_TASK,
	CIL_FSUSE_TRANS
};

struct cil_fsuse {
	enum cil_fsuse_types type;
	char *fs_str;
	char *context_str;
	struct cil_context *context;
};

#define CIL_MLS_LEVELS "l1 l2 h1 h2" 
#define CIL_CONSTRAIN_KEYS "t1 t2 r1 r2 u1 u2"
#define CIL_MLSCONSTRAIN_KEYS CIL_MLS_LEVELS CIL_CONSTRAIN_KEYS
#define CIL_CONSTRAIN_OPER "== != eq dom domby incomp not and or"
struct cil_constrain {
	struct cil_list *class_list_str;
	struct cil_list *class_list;
	struct cil_list *perm_list_str;
	struct cil_list *perm_list;
	struct cil_list *expr;
};

struct cil_param {
	char *str;
	enum cil_flavor flavor;
};

struct cil_macro {
	struct cil_symtab_datum datum;
	symtab_t symtab[CIL_SYM_NUM];
	struct cil_list *params;
};

struct cil_args {
	char *arg_str;
	struct cil_tree_node *arg;
	char *param_str;
	enum cil_flavor flavor;
};

struct cil_call {
	char *macro_str;
	struct cil_macro *macro;
	struct cil_tree *args_tree;
	struct cil_list *args;
};

#define CIL_TRUE	1
#define CIL_FALSE	0

struct cil_booleanif {
	struct cil_list *expr_stack;
	struct cil_tree_node *condtrue;
	struct cil_tree_node *condfalse;
};

struct cil_tunableif {
	symtab_t symtab[CIL_SYM_NUM];
	struct cil_list *expr_stack;
	struct cil_tree_node *condtrue;
	struct cil_tree_node *condfalse;
};

struct cil_conditional {
	char *str;
	void *data;
	enum cil_flavor flavor;
};

struct cil_policycap {
	struct cil_symtab_datum datum;
};

void cil_db_init(struct cil_db **db);
void cil_db_destroy(struct cil_db **db);

void cil_destroy_data(void **data, enum cil_flavor flavor);

int cil_flavor_to_symtab_index(enum cil_flavor flavor, enum cil_sym_index *index);

void cil_symtab_array_init(symtab_t symtab[], uint32_t symtab_num);
void cil_symtab_array_destroy(symtab_t symtab[]);
int cil_destroy_ast_symtabs(struct cil_tree_node *root);
int cil_get_symtab(struct cil_db *db, struct cil_tree_node *ast_node, symtab_t **symtab, enum cil_sym_index sym_index);

void cil_sort_init(struct cil_sort **sort);
void cil_sort_destroy(struct cil_sort **sort);
void cil_netifcon_init(struct cil_netifcon **netifcon);
void cil_context_init(struct cil_context **context);
void cil_level_init(struct cil_level **level);
void cil_levelrange_init(struct cil_levelrange **lvlrange);
void cil_sens_init(struct cil_sens **sens);
void cil_block_init(struct cil_block **block);
void cil_blockinherit_init(struct cil_blockinherit **inherit);
void cil_class_init(struct cil_class **class);
void cil_common_init(struct cil_common **common);
void cil_classcommon_init(struct cil_classcommon **classcommon);
void cil_sid_init(struct cil_sid **sid);
void cil_sidcontext_init(struct cil_sidcontext **sidcontext);
void cil_userrole_init(struct cil_userrole **userrole);
void cil_userbounds_init(struct cil_userbounds **userbounds);
void cil_roledominance_init(struct cil_roledominance **roledominance);
void cil_rolebounds_init(struct cil_rolebounds **rolebounds);
void cil_roletype_init(struct cil_roletype **roletype);
void cil_typeattribute_init(struct cil_typeattribute **attribute);
void cil_typeattributetypes_init(struct cil_typeattributetypes **attrtypes);
void cil_typealias_init(struct cil_typealias **typealias);
void cil_typebounds_init(struct cil_typebounds **typebnds);
void cil_typepermissive_init(struct cil_typepermissive **typeperm);
void cil_filetransition_init(struct cil_filetransition **filetrans);
void cil_rangetransition_init(struct cil_rangetransition **rangetrans);
void cil_bool_init(struct cil_bool **cilbool);
void cil_boolif_init(struct cil_booleanif **bif);
void cil_conditional_init(struct cil_conditional **cond);
void cil_tunif_init(struct cil_tunableif **tif);
void cil_avrule_init(struct cil_avrule **avrule);
void cil_type_rule_init(struct cil_type_rule **type_rule);
void cil_roletransition_init(struct cil_roletransition **roletrans);
void cil_roleallow_init(struct cil_roleallow **role_allow);
void cil_sensalias_init(struct cil_sensalias **sensalias);
void cil_catalias_init(struct cil_catalias **catalias);
void cil_catrange_init(struct cil_catrange **catrange);
void cil_catset_init(struct cil_catset **catset);
void cil_senscat_init(struct cil_senscat **senscat);
void cil_filecon_init(struct cil_filecon **filecon);
void cil_portcon_init(struct cil_portcon **portcon);
void cil_nodecon_init(struct cil_nodecon **nodecon);
void cil_genfscon_init(struct cil_genfscon **genfscon);
void cil_pirqcon_init(struct cil_pirqcon **pirqcon);
void cil_iomemcon_init(struct cil_iomemcon **iomemcon);
void cil_ioportcon_init(struct cil_ioportcon **ioportcon);
void cil_pcidevicecon_init(struct cil_pcidevicecon **pcidevicecon);
void cil_fsuse_init(struct cil_fsuse **fsuse);
void cil_constrain_init(struct cil_constrain **constrain);
void cil_ipaddr_init(struct cil_ipaddr **ipaddr);
void cil_perm_init(struct cil_perm **perm);
void cil_permset_init(struct cil_permset **permset);
void cil_classpermset_init(struct cil_classpermset **cps);
void cil_classmap_perm_init(struct cil_classmap_perm **cmp);
void cil_classmap_init(struct cil_classmap **map);
void cil_classmapping_init(struct cil_classmapping **mapping);
void cil_user_init(struct cil_user **user);
void cil_userlevel_init(struct cil_userlevel **usrlvl);
void cil_userrange_init(struct cil_userrange **userrange);
void cil_role_init(struct cil_role **role);
void cil_type_init(struct cil_type **type);
void cil_cat_init(struct cil_cat **cat);
void cil_catorder_init(struct cil_catorder **catorder);
void cil_sens_dominates_init(struct cil_sens_dominates **sens_dominates);
void cil_args_init(struct cil_args **args);
void cil_call_init(struct cil_call **call);
void cil_optional_init(struct cil_optional **optional);
void cil_param_init(struct cil_param **param);
void cil_macro_init(struct cil_macro **macro);
void cil_policycap_init(struct cil_policycap **policycap);

#endif
