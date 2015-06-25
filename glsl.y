%{
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glsl.tab.h"

#include "glsl_common.h"

#include "lex.glsl.h"
void glslerror(const char *s);
int glsllex (void);

int8_t *buffer = NULL;
int8_t *buffer_end = NULL;
int remaining = 0;

static int8_t *myalloc(size_t size, int align)
{
	int8_t *ret;

	if (size + align > (buffer_end - buffer)) {
		buffer = (int8_t *)malloc(1024*1024);
		buffer_end = buffer + 1024*1024;
	}

	ret = buffer;

	int8_t *trunc = (int8_t *)((~((intptr_t)align - 1)) & ((intptr_t)ret));
	if (trunc != ret) {
		ret = trunc + align;
	}
	buffer = ret + size;
	return ret;
}

static char *mystrdup(const char *c)
{
	int len = strlen(c);
	char *ret = (char *)myalloc(len + 1, 1);
	strcpy(ret, c);
	return ret;
}

#define NEW_STRUCT(TYPE) ((struct TYPE *)myalloc(sizeof(struct TYPE), sizeof(intptr_t)))

static struct generic *new_generic_list(struct generic *first)
{
	struct generic_list *gl = NEW_STRUCT(generic_list);
	gl->gen.code = GENERIC_LIST_NODE;
	gl->ent = first;
	gl->next = NULL;
	return &(gl->gen);
}

static struct generic *generic_list_add(struct generic *gl, struct generic *ent)
{
	struct generic_list *nl = (struct generic_list *)new_generic_list(ent);
	nl->next = (struct generic_list *)gl;
	return &(nl->gen);
}

static struct generic *new_generic(int code)
{
	struct generic *g = NEW_STRUCT(generic);
	g->code = code;
	return g;
}

static void init_declaration(struct declaration *d, const char *name, struct type *type)
{
	d->gen.code = DECLARATION_NODE;
	d->next = NULL;
	d->name = name;
	d->type = type;
	d->tag = NULL;
}

static struct generic *new_declaration(const char *name, struct type *type)
{
	struct declaration *d = NEW_STRUCT(declaration);
	init_declaration(d, name, type);
	return &(d->gen);
}

static struct generic *new_function(const char *name, struct type *rtype, struct parameter_list *plist)
{
	struct function *f = NEW_STRUCT(function);
	init_declaration(&f->decl, name, rtype);
	f->decl.gen.code = FUNCTION_NODE;
	f->plist = plist;
	return &f->decl.gen;
}

static struct generic *new_binary_operator(int code, struct generic *left, struct generic *right)
{
	struct binary_operator *b = NEW_STRUCT(binary_operator);
	b->gen.code = code;
	b->left = left;
	b->right = right;
	return &b->gen;
}

static struct generic *new_identifier(const char *name)
{
	struct identifier *id = NEW_STRUCT(identifier);
	id->gen.code = IDENTIFIER;
	id->name = name;
	return &id->gen;
}

static struct generic *new_constant_value(int code, union rvalue *r)
{
	struct constant_value *v = NEW_STRUCT(constant_value);
	v->gen.code = code;
	v->val = *r;
	return &v->gen;
}

static struct type *new_type(struct generic *specifier, struct generic *qualifiers)
{
	struct type *type = NEW_STRUCT(type);
	type->specifier = specifier;
	type->qualifiers = qualifiers;
	return type;
}

static struct generic *new_type_specifier(struct generic *nonarray, struct array_specifier *array)
{
	struct type_specifier *t = NEW_STRUCT(type_specifier);
	t->gen.code = TYPE_SPECIFIER_NODE;
	t->nonarray = nonarray;
	t->array = array;
	return &(t->gen);
}

static struct parameter_declarator *new_parameter_declarator(
	struct generic *specifier,
	const char *name,
	struct array_specifier *array)
{
	struct parameter_declarator *p = NEW_STRUCT(parameter_declarator);
	p->type_specifier = (struct type_specifier *)specifier;
	p->name = name;
	p->array_specifier = array;
	return p;
}

static struct parameter_declaration *new_parameter_declaration(
	struct generic *qualifiers,
	struct parameter_declarator *declarator)
{
	struct parameter_declaration *pd = NEW_STRUCT(parameter_declaration);
	pd->qualifiers = qualifiers;
	pd->declarator = declarator;
	return pd;
}

static struct parameter_list *new_parameter_list(
	struct parameter_declaration *decl,
	struct parameter_list *next)
{
	struct parameter_list *pl = NEW_STRUCT(parameter_list);
	pl->decl = decl;
	pl->next = next;
	return pl;
}

static struct declaration_tag *new_declaration_tag(
	const char *name,
	struct generic *value)
{
	struct declaration_tag *tag = NEW_STRUCT(declaration_tag);
	tag->name = name;
	tag->value = value;
	tag->next = NULL;
	return tag;
}

static struct function_call *new_function_call(struct generic *function_identifier)
{
	struct function_call *call = NEW_STRUCT(function_call);
	call->gen.code = FUNCTION_CALL_NODE;
	call->function_identifier = function_identifier;
	call->params = NULL;
	return call;
}

struct declaration *g_decls = NULL;

%}

%defines

%define api.value.type union
%define api.prefix glsl

%type <struct generic *> function_declarator
%type <struct generic *> function_header_with_parameters
%type <struct generic *> function_prototype
%type <struct generic *> function_definition
%type <struct generic *> function_header
%type <struct generic *>       external_declaration
%type <struct generic *>       single_declaration
%type <struct generic *>       init_declarator_list
%type <struct generic *>       declaration
%type <struct type *>              fully_specified_type
%type <struct generic *>      type_qualifier
%type <struct generic *>           single_type_qualifier
%type <struct generic *>           storage_qualifier
%type <struct generic *>    type_specifier
%type <struct generic *>           type_specifier_nonarray
%type <struct generic *>           precision_qualifier
%type <struct generic *>           interpolation_qualifier
%type <struct generic *>           invariant_qualifier
%type <struct generic *>           precise_qualifier
%type <struct generic *>           expression
%type <struct generic *>           assignment_expression
%type <struct generic *>           constant_expression
%type <struct generic *>           conditional_expression
%type <struct generic *>           logical_or_expression
%type <struct generic *>           logical_xor_expression
%type <struct generic *>           logical_and_expression
%type <struct generic *>           inclusive_or_expression
%type <struct generic *>           exclusive_or_expression
%type <struct generic *>           and_expression
%type <struct generic *>           equality_expression
%type <struct generic *>           relational_expression
%type <struct generic *>           shift_expression
%type <struct generic *>           additive_expression
%type <struct generic *>           multiplicative_expression
%type <struct generic *>           integer_expression
%type <struct generic *>           unary_expression
%type <struct generic *>           postfix_expression
%type <struct generic *>           primary_expression
%type <struct function_call *>	   function_call
%type <struct function_call *>	   function_call_or_method
%type <struct function_call *>	   function_call_generic
%type <struct function_call *>	   function_call_header
%type <struct generic *>	   function_identifier
%type <struct function_call *>	   function_call_header_no_parameters
%type <struct function_call *>	   function_call_header_with_parameters
%type <struct generic *>	   initializer
%type <struct generic *>	   initializer_list
%type <struct generic *>	   expression_statement
%type <struct generic *>	   statement
%type <struct generic *>	   simple_statement
%type <struct generic *>	   compound_statement
%type <struct generic *>	   declaration_statement
%type <struct generic *>	   selection_statement
%type <struct generic *>	   statement_no_new_scope
%type <struct generic *>	   for_init_statement
%type <struct generic *>	   switch_statement
%type <struct generic *>	   case_label
%type <struct generic *>	   for_rest_statement
%type <struct generic *>	   iteration_statement
%type <struct generic *>	   jump_statement
%type <struct generic *>	   compound_statement_no_new_scope
%type <struct generic *>	   statement_list
%type <int>                        unary_operator
%type <int>                        assignment_operator
%type <char *>                     variable_identifier
%type <char *>                     decl_identifier
%type <char *>                     block_identifier
%type <char *>                     struct_name
%type <char *>                     type_name
%type <char *>                     param_name
%type <char *>                     function_name
%type <struct generic *>        field_selection
%type <struct declaration_tag *>   end_declaration
%type <struct generic *>    parameter_type_specifier
%type <struct array_specifier *>   array_specifier
%type <struct parameter_declaration *> parameter_declaration
%type <struct parameter_declarator *> parameter_declarator
%type <struct declaration_tag*> declaration_tag
%type <struct declaration_tag*> declaration_tag_list

%token CONST
%token BOOL
%token FLOAT
%token DOUBLE
%token INT
%token UINT
%token BREAK
%token CONTINUE
%token DO
%token ELSE
%token FOR
%token IF
%token DISCARD
%token RETURN
%token SWITCH
%token CASE
%token DEFAULT
%token SUBROUTINE
%token BVEC2
%token BVEC3
%token BVEC4
%token IVEC2
%token IVEC3
%token IVEC4
%token UVEC2
%token UVEC3
%token UVEC4
%token VEC2
%token VEC3
%token VEC4
%token MAT2
%token MAT3
%token MAT4
%token CENTROID
%token IN
%token OUT
%token INOUT
%token UNIFORM
%token PATCH
%token SAMPLE
%token BUFFER
%token SHARED
%token COHERENT
%token VOLATILE
%token RESTRICT
%token READONLY
%token WRITEONLY
%token DVEC2
%token DVEC3
%token DVEC4
%token DMAT2
%token DMAT3
%token DMAT4
%token NOPERSPECTIVE
%token FLAT
%token SMOOTH
%token LAYOUT
%token MAT2X2
%token MAT2X3
%token MAT2X4
%token MAT3X2
%token MAT3X3
%token MAT3X4
%token MAT4X2
%token MAT4X3
%token MAT4X4
%token DMAT2X2
%token DMAT2X3
%token DMAT2X4
%token DMAT3X2
%token DMAT3X3
%token DMAT3X4
%token DMAT4X2
%token DMAT4X3
%token DMAT4X4
%token ATOMIC_UINT
%token SAMPLER1D
%token SAMPLER2D
%token SAMPLER3D
%token SAMPLERCUBE
%token SAMPLER1DSHADOW
%token SAMPLER2DSHADOW
%token SAMPLERCUBESHADOW
%token SAMPLER1DARRAY
%token SAMPLER2DARRAY
%token SAMPLER1DARRAYSHADOW
%token SAMPLER2DARRAYSHADOW
%token ISAMPLER1D
%token ISAMPLER2D
%token ISAMPLER3D
%token ISAMPLERCUBE
%token ISAMPLER1DARRAY
%token ISAMPLER2DARRAY
%token USAMPLER1D
%token USAMPLER2D
%token USAMPLER3D
%token USAMPLERCUBE
%token USAMPLER1DARRAY
%token USAMPLER2DARRAY
%token SAMPLER2DRECT
%token SAMPLER2DRECTSHADOW
%token ISAMPLER2DRECT
%token USAMPLER2DRECT
%token SAMPLERBUFFER
%token ISAMPLERBUFFER
%token USAMPLERBUFFER
%token SAMPLERCUBEARRAY
%token SAMPLERCUBEARRAYSHADOW
%token ISAMPLERCUBEARRAY
%token USAMPLERCUBEARRAY
%token SAMPLER2DMS
%token ISAMPLER2DMS
%token USAMPLER2DMS
%token SAMPLER2DMSARRAY
%token ISAMPLER2DMSARRAY
%token USAMPLER2DMSARRAY
%token IMAGE1D
%token IIMAGE1D
%token UIMAGE1D
%token IMAGE2D
%token IIMAGE2D
%token UIMAGE2D
%token IMAGE3D
%token IIMAGE3D
%token UIMAGE3D
%token IMAGE2DRECT
%token IIMAGE2DRECT
%token UIMAGE2DRECT
%token IMAGECUBE
%token IIMAGECUBE
%token UIMAGECUBE
%token IMAGEBUFFER
%token IIMAGEBUFFER
%token UIMAGEBUFFER
%token IMAGE1DARRAY
%token IIMAGE1DARRAY
%token UIMAGE1DARRAY
%token IMAGE2DARRAY
%token IIMAGE2DARRAY
%token UIMAGE2DARRAY
%token IMAGECUBEARRAY
%token IIMAGECUBEARRAY
%token UIMAGECUBEARRAY
%token IMAGE2DMS
%token IIMAGE2DMS
%token UIMAGE2DMS
%token IMAGE2DMSARRAY
%token IIMAGE2DMSARRAY
%token UIMAGE2DMSARRAY
%token STRUCT
%token VOID
%token WHILE
%token <char *> IDENTIFIER
%token <float> FLOATCONSTANT
%token <double> DOUBLECONSTANT
%token <int> INTCONSTANT
%token <unsigned int> UINTCONSTANT
%token <bool> BOOLCONSTANT
%token LEFT_OP
%token RIGHT_OP
%token INC_OP
%token DEC_OP
%token LE_OP
%token GE_OP
%token EQ_OP
%token NE_OP
%token AND_OP
%token OR_OP
%token XOR_OP
%token MUL_ASSIGN
%token DIV_ASSIGN
%token ADD_ASSIGN
%token MOD_ASSIGN
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token AND_ASSIGN
%token XOR_ASSIGN
%token OR_ASSIGN
%token SUB_ASSIGN
%token LEFT_PAREN
%token RIGHT_PAREN
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_BRACE
%token RIGHT_BRACE
%token DOT
%token COMMA
%token COLON
%token EQUAL
%token SEMICOLON
%token BANG
%token DASH
%token TILDE
%token PLUS
%token STAR
%token SLASH
%token PERCENT
%token LEFT_ANGLE
%token RIGHT_ANGLE
%token VERTICAL_BAR
%token CARET
%token AMPERSAND
%token QUESTION
%token INVARIANT
%token PRECISE
%token HIGHP
%token MEDIUMP
%token LOWP
%token PRECISION
%token FUNCTION_NODE
%token DECLARATION_NODE
%token FUNCTION_CALL_NODE
%token TYPE_SPECIFIER_NODE
%token GENERIC_LIST_NODE
%token AT

%%

translation_unit	: external_declaration { if ($1) { ((struct declaration *)$1)->next = g_decls; g_decls = (struct declaration *)$1; } }
			| translation_unit external_declaration { if ($2) { ((struct declaration *)$2)->next = g_decls; g_decls = (struct declaration *)$2; } }
			;

block_identifier	: IDENTIFIER { $$ = $1; }
			;

decl_identifier		: IDENTIFIER { $$ = $1; }
			;

struct_name		: IDENTIFIER { $$ = $1; }
			;

type_name		: IDENTIFIER { $$ = $1; }
			;

param_name		: IDENTIFIER { $$ = $1; }
			;

function_name		: IDENTIFIER { $$ = $1; }
			;

field_selection		: IDENTIFIER { $$ = new_identifier($1); }
			;

variable_identifier	: IDENTIFIER { $$ = $1; }
			;

external_declaration	: function_definition { $$ = $1; }
			| declaration { $$ = $1; }
			;

function_definition	: function_prototype compound_statement_no_new_scope { $$ = $1; }
			| function_prototype { $$ = $1; }
			;

compound_statement_no_new_scope : LEFT_BRACE RIGHT_BRACE { $$ = NULL; }
			| LEFT_BRACE statement_list RIGHT_BRACE { $$ = $2; }
			;

statement		: compound_statement { $$ = $1; }
			| simple_statement { $$ = $1; }
			;

statement_list		: statement { $$ = new_generic_list($1); }
			| statement_list statement { $$ = generic_list_add($$, $2); }
			;

compound_statement	: LEFT_BRACE RIGHT_BRACE { $$ = NULL; }
			| LEFT_BRACE statement_list RIGHT_BRACE { $$ = $2; }
			;

simple_statement	: declaration_statement { $$ = $1; }
			| expression_statement { $$ = $1; }
			| selection_statement { $$ = $1; }
			| switch_statement { $$ = $1; }
			| case_label { $$ = $1; }
			| iteration_statement { $$ = $1; }
			| jump_statement { $$ = $1; }
			;

declaration_statement	: declaration { $$ = $1; }
			;

declaration_tag		: IDENTIFIER { $$ = new_declaration_tag($1, NULL); }
			| IDENTIFIER EQUAL primary_expression { $$ = new_declaration_tag($1, $3); }
			;

declaration_tag_list	: declaration_tag { $$ = $1; }
			| declaration_tag_list COMMA declaration_tag { $$ = $1; $$->next = $3; }
			;

end_declaration		: AT declaration_tag_list AT SEMICOLON { $$ = $2; }
			| SEMICOLON { $$ = NULL; }
			;

declaration		: function_prototype SEMICOLON { $$ = NULL; }
			| init_declarator_list end_declaration { $$ = $1; if ($1) ((struct declaration *)$1)->tag = $2; }
			| PRECISION precision_qualifier type_specifier SEMICOLON { $$ = NULL; }
			| type_qualifier block_identifier LEFT_BRACE struct_declaration_list RIGHT_BRACE SEMICOLON { $$ = NULL; }
			| type_qualifier block_identifier LEFT_BRACE struct_declaration_list RIGHT_BRACE decl_identifier SEMICOLON { $$ = NULL; }
			| type_qualifier block_identifier LEFT_BRACE struct_declaration_list RIGHT_BRACE decl_identifier array_specifier SEMICOLON { $$ = NULL; }
			| type_qualifier SEMICOLON { $$ = NULL; }
			| type_qualifier type_name SEMICOLON { $$ = NULL; }
			| type_qualifier type_name identifier_list SEMICOLON { $$ = NULL; }
			;

identifier_list		: COMMA decl_identifier
			| identifier_list COMMA decl_identifier
			;

init_declarator_list	: single_declaration { $$ = $1; }
			| init_declarator_list COMMA decl_identifier { $$ = NULL; }
			| init_declarator_list COMMA decl_identifier array_specifier { $$ = NULL; }
			| init_declarator_list COMMA decl_identifier array_specifier EQUAL initializer { $$ = NULL; }
			| init_declarator_list COMMA decl_identifier EQUAL initializer { $$ = NULL; }
			;

single_declaration	: fully_specified_type { $$ = NULL; }
			| fully_specified_type decl_identifier { $$ = new_declaration($2, $1);}
			| fully_specified_type decl_identifier array_specifier { $$ = NULL; }
			| fully_specified_type decl_identifier array_specifier EQUAL initializer { $$ = NULL; }
			| fully_specified_type decl_identifier EQUAL initializer { $$ = NULL; }
			;

initializer		: assignment_expression { $$ = $1; }
			| LEFT_BRACE initializer_list RIGHT_BRACE { $$ = $2; }
			| LEFT_BRACE initializer_list COMMA RIGHT_BRACE { $$ = $2; }
			;

initializer_list	: initializer { $$ = new_generic_list($1); }
			| initializer_list COMMA initializer { $$ = generic_list_add($$, $3); }
			;

expression_statement	: SEMICOLON { $$ = NULL; }
			| expression SEMICOLON { $$ = $1; }
			;

selection_statement	: IF LEFT_PAREN expression RIGHT_PAREN statement { $$ = NULL; }
			| IF LEFT_PAREN expression RIGHT_PAREN statement ELSE statement { $$ = NULL; }
			;

switch_statement	: SWITCH LEFT_PAREN expression RIGHT_PAREN LEFT_BRACE switch_statement_list RIGHT_BRACE { $$ = NULL; }
			;

switch_statement_list	:
			| statement_list
			;

case_label		: CASE expression COLON { $$ = NULL; }
			| DEFAULT COLON { $$ = NULL; }
			;

iteration_statement	: WHILE LEFT_PAREN condition RIGHT_PAREN statement_no_new_scope { $$ = NULL; }
			| DO statement WHILE LEFT_PAREN expression RIGHT_PAREN SEMICOLON { $$ = NULL; }
			| FOR LEFT_PAREN for_init_statement for_rest_statement RIGHT_PAREN statement_no_new_scope { $$ = NULL; }
			;

statement_no_new_scope	: compound_statement_no_new_scope { $$ = NULL; }
			| simple_statement { $$ = NULL; }
			;

for_init_statement	: expression_statement { $$ = NULL; }
			| declaration_statement { $$ = NULL; }
			;

conditionopt		: condition
			|
			;

condition		: expression
			| fully_specified_type variable_identifier EQUAL initializer
			;

for_rest_statement	: conditionopt SEMICOLON { $$ = NULL; }
			| conditionopt SEMICOLON expression { $$ = NULL; }
			;

jump_statement		: CONTINUE SEMICOLON { $$ = NULL; }
			| BREAK SEMICOLON { $$ = NULL; }
			| RETURN SEMICOLON { $$ = NULL; }
			| RETURN expression SEMICOLON { $$ = NULL; }
			| DISCARD SEMICOLON { $$ = NULL; }
			;

function_prototype	: function_declarator RIGHT_PAREN { $$ = $1; }
			;

function_declarator	: function_header { $$ = $1; }
			| function_header_with_parameters { $$ = $1; }
			;

function_header_with_parameters : function_header parameter_declaration { $$ = $1; ((struct function *)$1)->plist = new_parameter_list($2, NULL);}
			| function_header_with_parameters COMMA parameter_declaration { $$ = $1; ((struct function *)$1)->plist = new_parameter_list($3, ((struct function *)$1)->plist); }
			;

parameter_declaration	: type_qualifier parameter_declarator { $$ = new_parameter_declaration($1, $2); }
			| parameter_declarator { $$ = new_parameter_declaration(NULL, $1); }
			| type_qualifier parameter_type_specifier { $$ = new_parameter_declaration($1, new_parameter_declarator($2, NULL, NULL)); }
			| parameter_type_specifier { $$ = new_parameter_declaration(NULL, new_parameter_declarator($1, NULL, NULL)); }
			;

parameter_declarator	: type_specifier param_name { $$ = new_parameter_declarator($1, $2, NULL); }
			| type_specifier param_name array_specifier { $$ = new_parameter_declarator($1, $2, $3); }
			;

function_header		: fully_specified_type function_name LEFT_PAREN { $$ = new_function($2, $1, NULL); }
			;

fully_specified_type	: type_specifier { $$ = new_type($1, NULL); }
			| type_qualifier type_specifier { $$ = new_type($2, $1); }
			;

parameter_type_specifier : type_specifier { $$ = $1; }
			;

type_specifier		: type_specifier_nonarray { $$ = new_type_specifier($1, NULL); }
			| type_specifier_nonarray array_specifier { $$ = new_type_specifier($1, $2); }
			;

array_specifier		: LEFT_BRACKET RIGHT_BRACKET { $$ = NULL; }
			| LEFT_BRACKET constant_expression RIGHT_BRACKET { $$ = NULL; }
			| array_specifier LEFT_BRACKET RIGHT_BRACKET { $$ = NULL; }
			| array_specifier LEFT_BRACKET constant_expression RIGHT_BRACKET { $$ = NULL; }
			;

type_specifier_nonarray : VOID { $$ = new_generic(VOID); }
			| FLOAT { $$ = new_generic(FLOAT); }
			| DOUBLE { $$ = new_generic(DOUBLE); }
			| INT { $$ = new_generic(INT); }
			| UINT { $$ = new_generic(UINT); }
			| BOOL { $$ = new_generic(BOOL); }
			| VEC2 { $$ = new_generic(VEC2); }
			| VEC3 { $$ = new_generic(VEC3); }
			| VEC4 { $$ = new_generic(VEC4); }
			| DVEC2 { $$ = new_generic(DVEC2); }
			| DVEC3 { $$ = new_generic(DVEC3); }
			| DVEC4 { $$ = new_generic(DVEC4); }
			| BVEC2 { $$ = new_generic(BVEC2); }
			| BVEC3 { $$ = new_generic(BVEC3); }
			| BVEC4 { $$ = new_generic(BVEC4); }
			| IVEC2 { $$ = new_generic(IVEC2); }
			| IVEC3 { $$ = new_generic(IVEC3); }
			| IVEC4 { $$ = new_generic(IVEC4); }
			| UVEC2 { $$ = new_generic(UVEC2); }
			| UVEC3 { $$ = new_generic(UVEC3); }
			| UVEC4 { $$ = new_generic(UVEC4); }
			| MAT2 { $$ = new_generic(MAT2); }
			| MAT3 { $$ = new_generic(MAT3); }
			| MAT4 { $$ = new_generic(MAT4); }
			| MAT2X2 { $$ = new_generic(MAT2X2); }
			| MAT2X3 { $$ = new_generic(MAT2X3); }
			| MAT2X4 { $$ = new_generic(MAT2X4); }
			| MAT3X2 { $$ = new_generic(MAT3X2); }
			| MAT3X3 { $$ = new_generic(MAT3X3); }
			| MAT3X4 { $$ = new_generic(MAT3X4); }
			| MAT4X2 { $$ = new_generic(MAT4X2); }
			| MAT4X3 { $$ = new_generic(MAT4X3); }
			| MAT4X4 { $$ = new_generic(MAT4X4); }
			| DMAT2 { $$ = new_generic(DMAT2); }
			| DMAT3 { $$ = new_generic(DMAT3); }
			| DMAT4 { $$ = new_generic(DMAT4); }
			| DMAT2X2 { $$ = new_generic(DMAT2X2); }
			| DMAT2X3 { $$ = new_generic(DMAT2X3); }
			| DMAT2X4 { $$ = new_generic(DMAT2X4); }
			| DMAT3X2 { $$ = new_generic(DMAT3X2); }
			| DMAT3X3 { $$ = new_generic(DMAT3X3); }
			| DMAT3X4 { $$ = new_generic(DMAT3X4); }
			| DMAT4X2 { $$ = new_generic(DMAT4X2); }
			| DMAT4X3 { $$ = new_generic(DMAT4X3); }
			| DMAT4X4 { $$ = new_generic(DMAT4X4); }
			| ATOMIC_UINT { $$ = new_generic(UINT); }
			| SAMPLER1D { $$ = new_generic(SAMPLER1D); }
			| SAMPLER2D { $$ = new_generic(SAMPLER2D); }
			| SAMPLER3D { $$ = new_generic(SAMPLER3D); }
			| SAMPLERCUBE { $$ = new_generic(SAMPLERCUBE); }
			| SAMPLER1DSHADOW { $$ = new_generic(SAMPLER1DSHADOW); }
			| SAMPLER2DSHADOW { $$ = new_generic(SAMPLER2DSHADOW); }
			| SAMPLERCUBESHADOW { $$ = new_generic(SAMPLERCUBESHADOW); }
			| SAMPLER1DARRAY { $$ = new_generic(SAMPLER1DARRAY); }
			| SAMPLER2DARRAY { $$ = new_generic(SAMPLER2DARRAY); }
			| SAMPLER1DARRAYSHADOW { $$ = new_generic(SAMPLER1DARRAYSHADOW); }
			| SAMPLER2DARRAYSHADOW { $$ = new_generic(SAMPLER2DARRAYSHADOW); }
			| SAMPLERCUBEARRAY { $$ = new_generic(SAMPLERCUBEARRAY); }
			| SAMPLERCUBEARRAYSHADOW { $$ = new_generic(SAMPLERCUBEARRAYSHADOW); }
			| ISAMPLER1D { $$ = new_generic(ISAMPLER1D); }
			| ISAMPLER2D { $$ = new_generic(ISAMPLER2D); }
			| ISAMPLER3D { $$ = new_generic(ISAMPLER3D); }
			| ISAMPLERCUBE { $$ = new_generic(ISAMPLERCUBE); }
			| ISAMPLER1DARRAY { $$ = new_generic(ISAMPLER1DARRAY); }
			| ISAMPLER2DARRAY { $$ = new_generic(ISAMPLER2DARRAY); }
			| ISAMPLERCUBEARRAY { $$ = new_generic(ISAMPLERCUBEARRAY); }
			| USAMPLER1D { $$ = new_generic(USAMPLER1D); }
			| USAMPLER2D { $$ = new_generic(USAMPLER2D); }
			| USAMPLER3D { $$ = new_generic(USAMPLER3D); }
			| USAMPLERCUBE { $$ = new_generic(USAMPLERCUBE); }
			| USAMPLER1DARRAY { $$ = new_generic(USAMPLER1DARRAY); }
			| USAMPLER2DARRAY { $$ = new_generic(USAMPLER2DARRAY); }
			| USAMPLERCUBEARRAY { $$ = new_generic(USAMPLERCUBEARRAY); }
			| SAMPLER2DRECT { $$ = new_generic(SAMPLER2DRECT); }
			| SAMPLER2DRECTSHADOW { $$ = new_generic(SAMPLER2DRECTSHADOW); }
			| ISAMPLER2DRECT { $$ = new_generic(ISAMPLER2DRECT); }
			| USAMPLER2DRECT { $$ = new_generic(USAMPLER2DRECT); }
			| SAMPLERBUFFER { $$ = new_generic(SAMPLERBUFFER); }
			| ISAMPLERBUFFER { $$ = new_generic(ISAMPLERBUFFER); }
			| USAMPLERBUFFER { $$ = new_generic(USAMPLERBUFFER); }
			| SAMPLER2DMS { $$ = new_generic(SAMPLER2DMS); }
			| ISAMPLER2DMS { $$ = new_generic(ISAMPLER2DMS); }
			| USAMPLER2DMS { $$ = new_generic(USAMPLER2DMS); }
			| SAMPLER2DMSARRAY { $$ = new_generic(SAMPLER2DMSARRAY); }
			| ISAMPLER2DMSARRAY { $$ = new_generic(ISAMPLER2DMSARRAY); }
			| USAMPLER2DMSARRAY { $$ = new_generic(USAMPLER2DMSARRAY); }
			| IMAGE1D { $$ = new_generic(IMAGE1D); }
			| IIMAGE1D { $$ = new_generic(IIMAGE1D); }
			| UIMAGE1D { $$ = new_generic(UIMAGE1D); }
			| IMAGE2D { $$ = new_generic(IMAGE2D); }
			| IIMAGE2D { $$ = new_generic(IIMAGE2D); }
			| UIMAGE2D { $$ = new_generic(UIMAGE2D); }
			| IMAGE3D { $$ = new_generic(IMAGE3D); }
			| IIMAGE3D { $$ = new_generic(IIMAGE3D); }
			| UIMAGE3D { $$ = new_generic(UIMAGE3D); }
			| IMAGE2DRECT { $$ = new_generic(IMAGE2DRECT); }
			| IIMAGE2DRECT { $$ = new_generic(IIMAGE2DRECT); }
			| UIMAGE2DRECT { $$ = new_generic(UIMAGE2DRECT); }
			| IMAGECUBE { $$ = new_generic(IMAGECUBE); }
			| IIMAGECUBE { $$ = new_generic(IIMAGECUBE); }
			| UIMAGECUBE { $$ = new_generic(UIMAGECUBE); }
			| IMAGEBUFFER { $$ = new_generic(IMAGEBUFFER); }
			| IIMAGEBUFFER { $$ = new_generic(IIMAGEBUFFER); }
			| UIMAGEBUFFER { $$ = new_generic(UIMAGEBUFFER); }
			| IMAGE1DARRAY { $$ = new_generic(IMAGE1DARRAY); }
			| IIMAGE1DARRAY { $$ = new_generic(IIMAGE1DARRAY); }
			| UIMAGE1DARRAY { $$ = new_generic(UIMAGE1DARRAY); }
			| IMAGE2DARRAY { $$ = new_generic(IMAGE2DARRAY); }
			| IIMAGE2DARRAY { $$ = new_generic(IIMAGE2DARRAY); }
			| UIMAGE2DARRAY { $$ = new_generic(UIMAGE2DARRAY); }
			| IMAGECUBEARRAY { $$ = new_generic(IMAGECUBEARRAY); }
			| IIMAGECUBEARRAY { $$ = new_generic(IIMAGECUBEARRAY); }
			| UIMAGECUBEARRAY { $$ = new_generic(UIMAGECUBEARRAY); }
			| IMAGE2DMS { $$ = new_generic(IMAGE2DMS); }
			| IIMAGE2DMS { $$ = new_generic(IIMAGE2DMS); }
			| UIMAGE2DMS { $$ = new_generic(UIMAGE2DMS); }
			| IMAGE2DMSARRAY { $$ = new_generic(IMAGE2DMSARRAY); }
			| IIMAGE2DMSARRAY { $$ = new_generic(IIMAGE2DMSARRAY); }
			| UIMAGE2DMSARRAY { $$ = new_generic(UIMAGE2DMSARRAY); }
			| struct_specifier { $$ = NULL; }
			| IDENTIFIER { $$ = new_generic(VOID); }
			;

struct_specifier	: STRUCT struct_name LEFT_BRACE struct_declaration_list RIGHT_BRACE
			| STRUCT LEFT_BRACE struct_declaration_list RIGHT_BRACE
			;

struct_declaration_list : struct_declaration
			| struct_declaration_list struct_declaration
			;

struct_declaration	: type_specifier struct_declarator_list SEMICOLON
			| type_qualifier type_specifier struct_declarator_list SEMICOLON
			;

struct_declarator_list	: struct_declarator
			| struct_declarator_list COMMA struct_declarator
			;

struct_declarator	: decl_identifier
			| decl_identifier array_specifier
			;

type_qualifier		: single_type_qualifier { if ($1) $$ = new_generic_list($1); else $$ = NULL;}
			| type_qualifier single_type_qualifier { if ($2) $$ = generic_list_add($1, $2); else $$ = $1; }
			;

single_type_qualifier	: storage_qualifier { $$ = $1; }
			| layout_qualifier { $$ = NULL; }
			| precision_qualifier { $$ = $1; }
			| interpolation_qualifier { $$ = $1; }
			| invariant_qualifier { $$ = $1; }
			| precise_qualifier { $$ = $1; }
			;

layout_qualifier	: LAYOUT LEFT_PAREN layout_qualifier_id_list RIGHT_PAREN
			;

layout_qualifier_id_list: layout_qualifier_id
			| layout_qualifier_id_list COMMA layout_qualifier_id
			;

layout_qualifier_id	: IDENTIFIER
			| IDENTIFIER EQUAL constant_expression
			| SHARED
			;

precision_qualifier	: HIGHP { $$ = new_generic(HIGHP); }
			| MEDIUMP { $$ = new_generic(MEDIUMP); }
			| LOWP { $$ = new_generic(LOWP); }
			;

interpolation_qualifier : SMOOTH { $$ = new_generic(SMOOTH); }
			| FLAT { $$ = new_generic(FLAT); }
			| NOPERSPECTIVE { $$ = new_generic(NOPERSPECTIVE); }
			;

invariant_qualifier	: INVARIANT { $$ = new_generic(INVARIANT); }
			;

precise_qualifier 	: PRECISE { $$ = new_generic(PRECISE); }
			;

storage_qualifier	: CONST { $$ = new_generic(CONST); }
			| INOUT { $$ = new_generic(INOUT); }
			| IN { $$ = new_generic(IN); }
			| OUT { $$ = new_generic(OUT); }
			| CENTROID { $$ = new_generic(CENTROID); }
			| PATCH { $$ = new_generic(PATCH); }
			| SAMPLE { $$ = new_generic(SAMPLE); }
			| UNIFORM { $$ = new_generic(UNIFORM); }
			| BUFFER { $$ = new_generic(BUFFER); }
			| SHARED { $$ = new_generic(SHARED); }
			| COHERENT { $$ = new_generic(COHERENT); }
			| VOLATILE { $$ = new_generic(VOLATILE); }
			| RESTRICT { $$ = new_generic(RESTRICT); }
			| READONLY { $$ = new_generic(READONLY); }
			| WRITEONLY { $$ = new_generic(WRITEONLY); }
			| SUBROUTINE { $$ = new_generic(SUBROUTINE); }
			| SUBROUTINE LEFT_PAREN type_name_list RIGHT_PAREN { $$ = NULL; }
			;

type_name_list		: type_name
			| type_name_list COMMA type_name
			;

expression		: assignment_expression { $$ = $1; }
			| expression COMMA assignment_expression { $$ = new_binary_operator(COMMA, $1, $3); }
			;

assignment_expression	: conditional_expression { $$ = $1; }
			| unary_expression assignment_operator assignment_expression { $$ = new_binary_operator($2, $1, $3); }
			;

assignment_operator	: EQUAL { $$ = EQUAL;}
			| MUL_ASSIGN { $$ = MUL_ASSIGN;}
			| DIV_ASSIGN { $$ = DIV_ASSIGN;}
			| MOD_ASSIGN { $$ = MOD_ASSIGN;}
			| ADD_ASSIGN { $$ = ADD_ASSIGN;}
			| SUB_ASSIGN { $$ = SUB_ASSIGN;}
			| LEFT_ASSIGN { $$ = LEFT_ASSIGN;}
			| RIGHT_ASSIGN { $$ = RIGHT_ASSIGN;}
			| AND_ASSIGN { $$ = AND_ASSIGN;}
			| XOR_ASSIGN { $$ = XOR_ASSIGN;}
			| OR_ASSIGN { $$ = OR_ASSIGN;}
			;

constant_expression	: conditional_expression { $$ = $1; }
			;

conditional_expression	: logical_or_expression { $$ = $1; }
			| logical_or_expression QUESTION expression COLON assignment_expression { $$ = NULL; }
			;

logical_or_expression	: logical_xor_expression { $$ = $1; }
			| logical_or_expression OR_OP logical_xor_expression { $$ = new_binary_operator(OR_OP, $1, $3); }
			;

logical_xor_expression	: logical_and_expression { $$ = $1; }
			| logical_xor_expression XOR_OP logical_and_expression { $$ = new_binary_operator(XOR_OP, $1, $3); }
			;

logical_and_expression	: inclusive_or_expression { $$ = $1; }
			| logical_and_expression AND_OP inclusive_or_expression { $$ = new_binary_operator(AND_OP, $1, $3); }
			;

inclusive_or_expression : exclusive_or_expression { $$ = $1; }
			| inclusive_or_expression VERTICAL_BAR exclusive_or_expression { $$ = new_binary_operator(VERTICAL_BAR, $1, $3); }
			;

exclusive_or_expression	: and_expression { $$ = $1; }
			| exclusive_or_expression CARET and_expression { $$ = new_binary_operator(CARET, $1, $3); }
			;

and_expression		: equality_expression { $$ = $1; }
			| and_expression AMPERSAND equality_expression { $$ = new_binary_operator(AMPERSAND, $1, $3); }
			;

equality_expression	: relational_expression { $$ = $1; }
			| equality_expression EQ_OP relational_expression { $$ = new_binary_operator(EQ_OP, $1, $3); }
			| equality_expression NE_OP relational_expression { $$ = new_binary_operator(NE_OP, $1, $3); }
			;

relational_expression	: shift_expression { $$ = $1; }
			| relational_expression LEFT_ANGLE shift_expression { $$ = new_binary_operator(LEFT_ANGLE, $1, $3); }
			| relational_expression RIGHT_ANGLE shift_expression { $$ = new_binary_operator(RIGHT_ANGLE, $1, $3); }
			| relational_expression LE_OP shift_expression { $$ = new_binary_operator(LE_OP, $1, $3); }
			| relational_expression GE_OP shift_expression { $$ = new_binary_operator(GE_OP, $1, $3); }
			;

shift_expression	: additive_expression { $$ = $1; }
			| shift_expression LEFT_OP additive_expression { $$ = new_binary_operator(LEFT_OP, $1, $3); }
			| shift_expression RIGHT_OP additive_expression { $$ = new_binary_operator(RIGHT_OP, $1, $3); }
			;

additive_expression	: multiplicative_expression { $$ = $1; }
			| additive_expression PLUS multiplicative_expression { $$ = new_binary_operator(PLUS, $1, $3); }
			| additive_expression DASH multiplicative_expression { $$ = new_binary_operator(DASH, $1, $3); }
			;

multiplicative_expression : unary_expression { $$ = $1; }
			| multiplicative_expression STAR unary_expression { $$ = new_binary_operator(STAR, $1, $3); }
			| multiplicative_expression SLASH unary_expression { $$ = new_binary_operator(SLASH, $1, $3); }
			| multiplicative_expression PERCENT unary_expression { $$ = new_binary_operator(PERCENT, $1, $3); }
			;

unary_expression	: postfix_expression { $$ = $1; }
			| INC_OP unary_expression { $$ = new_binary_operator(INC_OP, NULL, $2); }
			| DEC_OP unary_expression { $$ = new_binary_operator(DEC_OP, NULL, $2); }
			| unary_operator unary_expression { $$ = new_binary_operator($1, NULL, $2); }
			;

unary_operator		: PLUS { $$ = PLUS; }
			| DASH { $$ = DASH; }
			| BANG { $$ = BANG; }
			| TILDE { $$ = TILDE; }
			;

postfix_expression	: primary_expression { $$ = $1; }
			| postfix_expression LEFT_BRACKET integer_expression RIGHT_BRACKET { $$ = NULL; }
			| function_call { $$ = NULL; }
			| postfix_expression DOT field_selection { $$ = new_binary_operator(DOT, $1, $3); }
			| postfix_expression INC_OP { $$ = new_binary_operator(INC_OP, $1, NULL); }
			| postfix_expression DEC_OP { $$ = new_binary_operator(DEC_OP, $1, NULL); }
			;

integer_expression	: expression { $$ = $1; }
			;

function_call		: function_call_or_method { $$ = $1; }
			;

function_call_or_method	: function_call_generic { $$ = $1; }
			;

function_call_generic	: function_call_header_with_parameters RIGHT_PAREN { $$ = $1; }
			| function_call_header_no_parameters RIGHT_PAREN { $$ = $1; }
			;

function_call_header_no_parameters: function_call_header VOID { $$ = $1; }
			| function_call_header { $$ = $1; }
			;

function_call_header_with_parameters: function_call_header assignment_expression { $$ = $1; $$->params = new_generic_list($2); }
			| function_call_header_with_parameters COMMA assignment_expression { $$ = $1; $1->params = generic_list_add($1->params, $3); }
			;

function_call_header	: function_identifier LEFT_PAREN { $$ = new_function_call($1); }
			;

function_identifier	: type_specifier { $$ = $1; }
			| postfix_expression { $$ = $1; }
			;

primary_expression	: variable_identifier { $$ = new_identifier($1); }
			| INTCONSTANT { union rvalue v; v.ival = $1; $$ = new_constant_value(INTCONSTANT, &v); }
			| UINTCONSTANT { union rvalue v; v.uval = $1; $$ = new_constant_value(UINTCONSTANT, &v);  }
			| FLOATCONSTANT { union rvalue v; v.fval = $1; $$ = new_constant_value(FLOATCONSTANT, &v);  }
			| BOOLCONSTANT  { union rvalue v; v.bval = $1; $$ = new_constant_value(BOOLCONSTANT, &v);  }
			| DOUBLECONSTANT { union rvalue v; v.dval = $1; $$ = new_constant_value(DOUBLECONSTANT, &v);  }
			| LEFT_PAREN expression RIGHT_PAREN { $$ = $2; }
			;

%%
