#include "glsl_ast.h"
#include "glsl_parser.h"

#include <stdio.h>

static const char *code_to_str[4096] = {
	[CONST] = "CONST",
	[BOOL] = "BOOL",
	[FLOAT] = "FLOAT",
	[DOUBLE] = "DOUBLE",
	[INT] = "INT",
	[UINT] = "UINT",
	[BREAK] = "BREAK",
	[CONTINUE] = "CONTINUE",
	[DO] = "DO",
	[ELSE] = "ELSE",
	[FOR] = "FOR",
	[IF] = "IF",
	[DISCARD] = "DISCARD",
	[RETURN] = "RETURN",
	[RETURN_VALUE] = "RETURN_VALUE",
	[SWITCH] = "SWITCH",
	[CASE] = "CASE",
	[DEFAULT] = "DEFAULT",
	[SUBROUTINE] = "SUBROUTINE",
	[BVEC2] = "BVEC2",
	[BVEC3] = "BVEC3",
	[BVEC4] = "BVEC4",
	[IVEC2] = "IVEC2",
	[IVEC3] = "IVEC3",
	[IVEC4] = "IVEC4",
	[UVEC2] = "UVEC2",
	[UVEC3] = "UVEC3",
	[UVEC4] = "UVEC4",
	[VEC2] = "VEC2",
	[VEC3] = "VEC3",
	[VEC4] = "VEC4",
	[MAT2] = "MAT2",
	[MAT3] = "MAT3",
	[MAT4] = "MAT4",
	[CENTROID] = "CENTROID",
	[IN] = "IN",
	[OUT] = "OUT",
	[INOUT] = "INOUT",
	[UNIFORM] = "UNIFORM",
	[PATCH] = "PATCH",
	[SAMPLE] = "SAMPLE",
	[BUFFER] = "BUFFER",
	[SHARED] = "SHARED",
	[COHERENT] = "COHERENT",
	[VOLATILE] = "VOLATILE",
	[RESTRICT] = "RESTRICT",
	[READONLY] = "READONLY",
	[WRITEONLY] = "WRITEONLY",
	[DVEC2] = "DVEC2",
	[DVEC3] = "DVEC3",
	[DVEC4] = "DVEC4",
	[DMAT2] = "DMAT2",
	[DMAT3] = "DMAT3",
	[DMAT4] = "DMAT4",
	[NOPERSPECTIVE] = "NOPERSPECTIVE",
	[FLAT] = "FLAT",
	[SMOOTH] = "SMOOTH",
	[LAYOUT] = "LAYOUT",
	[MAT2X2] = "MAT2X2",
	[MAT2X3] = "MAT2X3",
	[MAT2X4] = "MAT2X4",
	[MAT3X2] = "MAT3X2",
	[MAT3X3] = "MAT3X3",
	[MAT3X4] = "MAT3X4",
	[MAT4X2] = "MAT4X2",
	[MAT4X3] = "MAT4X3",
	[MAT4X4] = "MAT4X4",
	[DMAT2X2] = "DMAT2X2",
	[DMAT2X3] = "DMAT2X3",
	[DMAT2X4] = "DMAT2X4",
	[DMAT3X2] = "DMAT3X2",
	[DMAT3X3] = "DMAT3X3",
	[DMAT3X4] = "DMAT3X4",
	[DMAT4X2] = "DMAT4X2",
	[DMAT4X3] = "DMAT4X3",
	[DMAT4X4] = "DMAT4X4",
	[ATOMIC_UINT] = "ATOMIC_UINT",
	[SAMPLER1D] = "SAMPLER1D",
	[SAMPLER2D] = "SAMPLER2D",
	[SAMPLER3D] = "SAMPLER3D",
	[SAMPLERCUBE] = "SAMPLERCUBE",
	[SAMPLER1DSHADOW] = "SAMPLER1DSHADOW",
	[SAMPLER2DSHADOW] = "SAMPLER2DSHADOW",
	[SAMPLERCUBESHADOW] = "SAMPLERCUBESHADOW",
	[SAMPLER1DARRAY] = "SAMPLER1DARRAY",
	[SAMPLER2DARRAY] = "SAMPLER2DARRAY",
	[SAMPLER1DARRAYSHADOW] = "SAMPLER1DARRAYSHADOW",
	[SAMPLER2DARRAYSHADOW] = "SAMPLER2DARRAYSHADOW",
	[ISAMPLER1D] = "ISAMPLER1D",
	[ISAMPLER2D] = "ISAMPLER2D",
	[ISAMPLER3D] = "ISAMPLER3D",
	[ISAMPLERCUBE] = "ISAMPLERCUBE",
	[ISAMPLER1DARRAY] = "ISAMPLER1DARRAY",
	[ISAMPLER2DARRAY] = "ISAMPLER2DARRAY",
	[USAMPLER1D] = "USAMPLER1D",
	[USAMPLER2D] = "USAMPLER2D",
	[USAMPLER3D] = "USAMPLER3D",
	[USAMPLERCUBE] = "USAMPLERCUBE",
	[USAMPLER1DARRAY] = "USAMPLER1DARRAY",
	[USAMPLER2DARRAY] = "USAMPLER2DARRAY",
	[SAMPLER2DRECT] = "SAMPLER2DRECT",
	[SAMPLER2DRECTSHADOW] = "SAMPLER2DRECTSHADOW",
	[ISAMPLER2DRECT] = "ISAMPLER2DRECT",
	[USAMPLER2DRECT] = "USAMPLER2DRECT",
	[SAMPLERBUFFER] = "SAMPLERBUFFER",
	[ISAMPLERBUFFER] = "ISAMPLERBUFFER",
	[USAMPLERBUFFER] = "USAMPLERBUFFER",
	[SAMPLERCUBEARRAY] = "SAMPLERCUBEARRAY",
	[SAMPLERCUBEARRAYSHADOW] = "SAMPLERCUBEARRAYSHADOW",
	[ISAMPLERCUBEARRAY] = "ISAMPLERCUBEARRAY",
	[USAMPLERCUBEARRAY] = "USAMPLERCUBEARRAY",
	[SAMPLER2DMS] = "SAMPLER2DMS",
	[ISAMPLER2DMS] = "ISAMPLER2DMS",
	[USAMPLER2DMS] = "USAMPLER2DMS",
	[SAMPLER2DMSARRAY] = "SAMPLER2DMSARRAY",
	[ISAMPLER2DMSARRAY] = "ISAMPLER2DMSARRAY",
	[USAMPLER2DMSARRAY] = "USAMPLER2DMSARRAY",
	[IMAGE1D] = "IMAGE1D",
	[IIMAGE1D] = "IIMAGE1D",
	[UIMAGE1D] = "UIMAGE1D",
	[IMAGE2D] = "IMAGE2D",
	[IIMAGE2D] = "IIMAGE2D",
	[UIMAGE2D] = "UIMAGE2D",
	[IMAGE3D] = "IMAGE3D",
	[IIMAGE3D] = "IIMAGE3D",
	[UIMAGE3D] = "UIMAGE3D",
	[IMAGE2DRECT] = "IMAGE2DRECT",
	[IIMAGE2DRECT] = "IIMAGE2DRECT",
	[UIMAGE2DRECT] = "UIMAGE2DRECT",
	[IMAGECUBE] = "IMAGECUBE",
	[IIMAGECUBE] = "IIMAGECUBE",
	[UIMAGECUBE] = "UIMAGECUBE",
	[IMAGEBUFFER] = "IMAGEBUFFER",
	[IIMAGEBUFFER] = "IIMAGEBUFFER",
	[UIMAGEBUFFER] = "UIMAGEBUFFER",
	[IMAGE1DARRAY] = "IMAGE1DARRAY",
	[IIMAGE1DARRAY] = "IIMAGE1DARRAY",
	[UIMAGE1DARRAY] = "UIMAGE1DARRAY",
	[IMAGE2DARRAY] = "IMAGE2DARRAY",
	[IIMAGE2DARRAY] = "IIMAGE2DARRAY",
	[UIMAGE2DARRAY] = "UIMAGE2DARRAY",
	[IMAGECUBEARRAY] = "IMAGECUBEARRAY",
	[IIMAGECUBEARRAY] = "IIMAGECUBEARRAY",
	[UIMAGECUBEARRAY] = "UIMAGECUBEARRAY",
	[IMAGE2DMS] = "IMAGE2DMS",
	[IIMAGE2DMS] = "IIMAGE2DMS",
	[UIMAGE2DMS] = "UIMAGE2DMS",
	[IMAGE2DMSARRAY] = "IMAGE2DMSARRAY",
	[IIMAGE2DMSARRAY] = "IIMAGE2DMSARRAY",
	[UIMAGE2DMSARRAY] = "UIMAGE2DMSARRAY",
	[STRUCT] = "STRUCT",
	[VOID] = "VOID",
	[WHILE] = "WHILE",
	[TRUE_VALUE] = "TRUE_VALUE",
	[FALSE_VALUE] = "FALSE_VALUE",
	[LEFT_OP] = "LEFT_OP",
	[RIGHT_OP] = "RIGHT_OP",
	[INC_OP] = "INC_OP",
	[DEC_OP] = "DEC_OP",
	[LE_OP] = "LE_OP",
	[GE_OP] = "GE_OP",
	[EQ_OP] = "EQ_OP",
	[NE_OP] = "NE_OP",
	[AND_OP] = "AND_OP",
	[OR_OP] = "OR_OP",
	[XOR_OP] = "XOR_OP",
	[MUL_ASSIGN] = "MUL_ASSIGN",
	[DIV_ASSIGN] = "DIV_ASSIGN",
	[ADD_ASSIGN] = "ADD_ASSIGN",
	[MOD_ASSIGN] = "MOD_ASSIGN",
	[LEFT_ASSIGN] = "LEFT_ASSIGN",
	[RIGHT_ASSIGN] = "RIGHT_ASSIGN",
	[AND_ASSIGN] = "AND_ASSIGN",
	[XOR_ASSIGN] = "XOR_ASSIGN",
	[OR_ASSIGN] = "OR_ASSIGN",
	[SUB_ASSIGN] = "SUB_ASSIGN",
	[LEFT_PAREN] = "LEFT_PAREN",
	[RIGHT_PAREN] = "RIGHT_PAREN",
	[LEFT_BRACKET] = "LEFT_BRACKET",
	[RIGHT_BRACKET] = "RIGHT_BRACKET",
	[LEFT_BRACE] = "LEFT_BRACE",
	[RIGHT_BRACE] = "RIGHT_BRACE",
	[DOT] = "DOT",
	[COMMA] = "COMMA",
	[COLON] = "COLON",
	[EQUAL] = "EQUAL",
	[SEMICOLON] = "SEMICOLON",
	[BANG] = "BANG",
	[DASH] = "DASH",
	[TILDE] = "TILDE",
	[PLUS] = "PLUS",
	[STAR] = "STAR",
	[SLASH] = "SLASH",
	[PERCENT] = "PERCENT",
	[LEFT_ANGLE] = "LEFT_ANGLE",
	[RIGHT_ANGLE] = "RIGHT_ANGLE",
	[VERTICAL_BAR] = "VERTICAL_BAR",
	[CARET] = "CARET",
	[AMPERSAND] = "AMPERSAND",
	[QUESTION] = "QUESTION",
	[INVARIANT] = "INVARIANT",
	[PRECISE] = "PRECISE",
	[HIGHP] = "HIGHP",
	[MEDIUMP] = "MEDIUMP",
	[LOWP] = "LOWP",
	[PRECISION] = "PRECISION",

	[UNARY_PLUS] = "UNARY_PLUS",
	[UNARY_DASH] = "UNARY_DASH",
	[PRE_INC_OP] = "PRE_INC_OP",
	[PRE_DEC_OP] = "PRE_DEC_OP",
	[POST_DEC_OP] = "POST_DEC_OP",
	[POST_INC_OP] = "POST_INC_OP",
	[ARRAY_REF_OP] = "ARRAY_REF_OP",
	[FUNCTION_CALL] = "FUNCTION_CALL",
	[TYPE_NAME_LIST] = "TYPE_NAME_LIST",
	[TYPE_SPECIFIER] = "TYPE_SPECIFIER",
	[POSTFIX_EXPRESSION] = "POSTFIX_EXPRESSION",
	[TYPE_QUALIFIER_LIST] = "TYPE_QUALIFIER_LIST",
	[STRUCT_DECLARATION] = "STRUCT_DECLARATION",
	[STRUCT_DECLARATOR] = "STRUCT_DECLARATOR",
	[STRUCT_SPECIFIER] = "STRUCT_SPECIFIER",
	[FUNCTION_DEFINITION] = "FUNCTION_DEFINITION",
	[DECLARATION] = "DECLARATION",
	[STATEMENT_LIST] = "STATEMENT_LIST",
	[TRANSLATION_UNIT] = "TRANSLATION_UNIT",
	[PRECISION_DECLARATION] = "PRECISION_DECLARATION",
	[BLOCK_DECLARATION] = "BLOCK_DECLARATION",
	[TYPE_QUALIFIER_DECLARATION] = "TYPE_QUALIFIER_DECLARATION",
	[IDENTIFIER_LIST] = "IDENTIFIER_LIST",
	[INIT_DECLARATOR_LIST] = "INIT_DECLARATOR_LIST",
	[FULLY_SPECIFIED_TYPE] = "FULLY_SPECIFIED_TYPE",
	[SINGLE_DECLARATION] = "SINGLE_DECLARATION",
	[SINGLE_INIT_DECLARATION] = "SINGLE_INIT_DECLARATION",
	[INITIALIZER_LIST] = "INITIALIZER_LIST",
	[EXPRESSION_STATEMENT] = "EXPRESSION_STATEMENT",
	[SELECTION_STATEMENT] = "SELECTION_STATEMENT",
	[SELECTION_STATEMENT_ELSE] = "SELECTION_STATEMENT_ELSE",
	[SWITCH_STATEMENT] = "SWITCH_STATEMENT",
	[FOR_REST_STATEMENT] = "FOR_REST_STATEMENT",
	[WHILE_STATEMENT] = "WHILE_STATEMENT",
	[DO_STATEMENT] = "DO_STATEMENT",
	[FOR_STATEMENT] = "FOR_STATEMENT",
	[CASE_LABEL] = "CASE_LABEL",
	[CONDITION_OPT] = "CONDITION_OPT",
	[ASSIGNMENT_CONDITION] = "ASSIGNMENT_CONDITION",
	[EXPRESSION_CONDITION] = "EXPRESSION_CONDITION",
	[FUNCTION_HEADER] = "FUNCTION_HEADER",
	[FUNCTION_DECLARATION] = "FUNCTION_DECLARATION",
	[FUNCTION_PARAMETER_LIST] = "FUNCTION_PARAMETER_LIST",
	[PARAMETER_DECLARATION] = "PARAMETER_DECLARATION",
	[PARAMETER_DECLARATOR] = "PARAMETER_DECLARATOR",
	[UNINITIALIZED_DECLARATION] = "UNINITIALIZED_DECLARATION",
	[ARRAY_SPECIFIER] = "ARRAY_SPECIFIER",
	[ARRAY_SPECIFIER_LIST] = "ARRAY_SPECIFIER_LIST",
	[STRUCT_DECLARATOR_LIST] = "STRUCT_DECLARATOR_LIST",
	[FUNCTION_CALL_PARAMETER_LIST] = "FUNCTION_CALL_PARAMETER_LIST",
	[STRUCT_DECLARATION_LIST] = "STRUCT_DECLARATION_LIST",
	[LAYOUT_QUALIFIER_ID] = "LAYOUT_QUALIFIER_ID",
	[LAYOUT_QUALIFIER_ID_LIST] = "LAYOUT_QUALIFIER_ID_LIST",
	[SUBROUTINE_TYPE] = "SUBROUTINE_TYPE",
	[PAREN_EXPRESSION] = "PAREN_EXPRESSION",
	[DECLARATION_STATEMENT] = "DECLARATION_STATEMENT",
	[SECTION] = "SECTION",
	[DECLARATION_STATEMENT_LIST] = "DECLARATION_STATEMENT_LIST",
	[SECTION_STATEMENT] = "SECTION_STATEMENT",
	[NUM_GLSL_TOKEN] = ""
};

bool glsl_is_list_node(struct glsl_node *n)
{
	switch(n->code) {
	case TYPE_NAME_LIST:
	case TYPE_QUALIFIER_LIST:
	case STATEMENT_LIST:
	case IDENTIFIER_LIST:
	case INIT_DECLARATOR_LIST:
	case INITIALIZER_LIST:
	case FUNCTION_PARAMETER_LIST:
	case ARRAY_SPECIFIER_LIST:
	case STRUCT_DECLARATOR_LIST:
	case STRUCT_DECLARATION_LIST:
	case TRANSLATION_UNIT:
	case FUNCTION_CALL_PARAMETER_LIST:
	case DECLARATION_STATEMENT_LIST:
		return true;
	default:
		return false;
	}
}

void glsl_print_ast_tree(struct glsl_node *n, int depth)
{
	int i;

	for (i = 0; i < depth; i++) {
		printf("\t");
	}

	if (code_to_str[n->code])
		printf("%s", code_to_str[n->code]);

	switch(n->code) {
	case IDENTIFIER:
		if (n->data.str) {
			if (code_to_str[n->code])
				printf(": ");
			printf("%s", n->data.str);
		}
		break;
	case FLOATCONSTANT:
		if (code_to_str[n->code])
			printf(": ");
		printf("%f", n->data.f);
		break;
	case DOUBLECONSTANT:
		if (code_to_str[n->code])
			printf(": ");
		printf("%f", n->data.d);
		break;
	case INTCONSTANT:
		if (code_to_str[n->code])
			printf(": ");
		printf("%d", n->data.i);
		break;
	case UINTCONSTANT:
		if (code_to_str[n->code])
			printf(": ");
		printf("%u", n->data.ui);
		break;
	}
	printf("\n");

	for (i = 0; i < n->child_count; i++) {
		glsl_print_ast_tree((struct glsl_node *)n->children[i], depth + 1);
	}
}
