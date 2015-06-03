#ifndef GLSL_COMMON
#define GLSL_COMMON

struct generic {
	int code;
};

struct declaration {
	struct generic gen;
	const char *name;
	struct declaration *next;
	struct type *type;
};

struct block_declaration {
	struct declaration decl;
	struct struct_declaration_list *struct_declaration;
	struct generic_list *qualifiers;
	const char *block_name;
	struct array_specifier *array_specifier;
};

struct type {
	struct type_specifier *specifier;
	struct generic_list *qualifiers;
};

struct array_specifier {
	int placeholder;
};

struct type_specifier {
	struct generic *nonarray;
	struct array_specifier *array;
};

struct parameter_declarator {
	const char *name;
	struct type_specifier *type_specifier;
	struct array_specifier *array_specifier;
};

struct parameter_declaration {
	struct generic_list *qualifiers;
	struct parameter_declarator *declarator;
};

struct parameter_list {
	struct parameter_declaration *decl;
	struct parameter_list *next;
};

struct generic_list {
	struct generic *ent;
	struct generic_list *next;
};

struct function {
	struct declaration decl;
	struct parameter_list *plist;
};

struct translation_unit {
	struct declaration *decl;
};

struct binary_operator {
	struct generic gen;
	struct generic *left;
	struct generic *right;
};

struct identifier {
	struct generic gen;
	const char *name;
};

union rvalue {
	int ival;
	unsigned int uval;
	float fval;
	bool bval;
	double dval;
};

struct constant_value {
	struct generic gen;
	union rvalue val;
};

extern struct declaration *g_decls;

#endif
