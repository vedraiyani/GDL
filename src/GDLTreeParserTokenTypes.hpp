#ifndef INC_GDLTreeParserTokenTypes_hpp_
#define INC_GDLTreeParserTokenTypes_hpp_

/* $ANTLR 2.7.7 (20110618): "gdlc.tree.g" -> "GDLTreeParserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API GDLTreeParserTokenTypes {
#endif
	enum {
		EOF_ = 1,
		ALL = 4,
		ASSIGN = 5,
		ASSIGN_INPLACE = 6,
		ASSIGN_REPLACE = 7,
		ASSIGN_ARRAYEXPR_MFCALL = 8,
		ARRAYDEF = 9,
		ARRAYDEF_CONST = 10,
		ARRAYIX = 11,
		ARRAYIX_ALL = 12,
		ARRAYIX_ORANGE = 13,
		ARRAYIX_RANGE = 14,
		ARRAYIX_ORANGE_S = 15,
		ARRAYIX_RANGE_S = 16,
		ARRAYEXPR = 17,
		ARRAYEXPR_FN = 18,
		ARRAYEXPR_MFCALL = 19,
		BLOCK = 20,
		BREAK = 21,
		CSBLOCK = 22,
		CONTINUE = 23,
		COMMONDECL = 24,
		COMMONDEF = 25,
		CONSTANT = 26,
		DEREF = 27,
		ELSEBLK = 28,
		EXPR = 29,
		FOR = 30,
		FOR_STEP = 31,
		FOREACH = 32,
		FOREACH_INDEX = 33,
		FOR_LOOP = 34,
		FOR_STEP_LOOP = 35,
		FOREACH_LOOP = 36,
		FOREACH_INDEX_LOOP = 37,
		FCALL = 38,
		FCALL_LIB = 39,
		FCALL_LIB_DIRECT = 40,
		FCALL_LIB_N_ELEMENTS = 41,
		FCALL_LIB_RETNEW = 42,
		GDLNULL = 43,
		IF_ELSE = 44,
		KEYDECL = 45,
		KEYDEF = 46,
		KEYDEF_REF = 47,
		KEYDEF_REF_CHECK = 48,
		KEYDEF_REF_EXPR = 49,
		LABEL = 50,
		MPCALL = 51,
		MPCALL_PARENT = 52,
		MFCALL = 53,
		MFCALL_LIB = 54,
		MFCALL_LIB_RETNEW = 55,
		MFCALL_PARENT = 56,
		MFCALL_PARENT_LIB = 57,
		MFCALL_PARENT_LIB_RETNEW = 58,
		NOP = 59,
		NSTRUC = 60,
		NSTRUC_REF = 61,
		ON_IOERROR_NULL = 62,
		PCALL = 63,
		PCALL_LIB = 64,
		PARADECL = 65,
		PARAEXPR = 66,
		PARAEXPR_VN = 67,
		POSTDEC = 68,
		POSTINC = 69,
		DECSTATEMENT = 70,
		INCSTATEMENT = 71,
		REF = 72,
		REF_VN = 73,
		REF_CHECK = 74,
		REF_CHECK_VN = 75,
		REF_EXPR = 76,
		REF_EXPR_VN = 77,
		REPEAT = 78,
		REPEAT_LOOP = 79,
		RETURN = 80,
		RETF = 81,
		RETP = 82,
		STRUC = 83,
		SYSVAR = 84,
		UMINUS = 85,
		VAR = 86,
		VARPTR = 87,
		WHILE = 88,
		IDENTIFIER = 89,
		AND_OP = 90,
		BEGIN = 91,
		CASE = 92,
		COMMON = 93,
		COMPILE_OPT = 94,
		DO = 95,
		ELSE = 96,
		END = 97,
		ENDCASE = 98,
		ENDELSE = 99,
		ENDFOR = 100,
		ENDFOREACH = 101,
		ENDIF = 102,
		ENDREP = 103,
		ENDSWITCH = 104,
		ENDWHILE = 105,
		EQ_OP = 106,
		FORWARD = 107,
		FUNCTION = 108,
		GE_OP = 109,
		GOTO = 110,
		GT_OP = 111,
		IF = 112,
		INHERITS = 113,
		LE_OP = 114,
		LT_OP = 115,
		MOD_OP = 116,
		NE_OP = 117,
		NOT_OP = 118,
		OF = 119,
		ON_IOERROR = 120,
		OR_OP = 121,
		PRO = 122,
		SWITCH = 123,
		THEN = 124,
		UNTIL = 125,
		XOR_OP = 126,
		METHOD = 127,
		COMMA = 128,
		COLON = 129,
		END_U = 130,
		EQUAL = 131,
		DEC = 132,
		INC = 133,
		AND_OP_EQ = 134,
		ASTERIX_EQ = 135,
		EQ_OP_EQ = 136,
		GE_OP_EQ = 137,
		GTMARK_EQ = 138,
		GT_OP_EQ = 139,
		LE_OP_EQ = 140,
		LTMARK_EQ = 141,
		LT_OP_EQ = 142,
		MATRIX_OP1_EQ = 143,
		MATRIX_OP2_EQ = 144,
		MINUS_EQ = 145,
		MOD_OP_EQ = 146,
		NE_OP_EQ = 147,
		OR_OP_EQ = 148,
		PLUS_EQ = 149,
		POW_EQ = 150,
		SLASH_EQ = 151,
		XOR_OP_EQ = 152,
		MEMBER = 153,
		LBRACE = 154,
		RBRACE = 155,
		SLASH = 156,
		LSQUARE = 157,
		RSQUARE = 158,
		SYSVARNAME = 159,
		EXCLAMATION = 160,
		LCURLY = 161,
		RCURLY = 162,
		CONSTANT_HEX_BYTE = 163,
		CONSTANT_HEX_LONG = 164,
		CONSTANT_HEX_LONG64 = 165,
		CONSTANT_HEX_INT = 166,
		CONSTANT_HEX_I = 167,
		CONSTANT_HEX_ULONG = 168,
		CONSTANT_HEX_ULONG64 = 169,
		CONSTANT_HEX_UI = 170,
		CONSTANT_HEX_UINT = 171,
		CONSTANT_BYTE = 172,
		CONSTANT_LONG = 173,
		CONSTANT_LONG64 = 174,
		CONSTANT_INT = 175,
		CONSTANT_I = 176,
		CONSTANT_ULONG = 177,
		CONSTANT_ULONG64 = 178,
		CONSTANT_UI = 179,
		CONSTANT_UINT = 180,
		CONSTANT_OCT_BYTE = 181,
		CONSTANT_OCT_LONG = 182,
		CONSTANT_OCT_LONG64 = 183,
		CONSTANT_OCT_INT = 184,
		CONSTANT_OCT_I = 185,
		CONSTANT_OCT_ULONG = 186,
		CONSTANT_OCT_ULONG64 = 187,
		CONSTANT_OCT_UI = 188,
		CONSTANT_OCT_UINT = 189,
		CONSTANT_FLOAT = 190,
		CONSTANT_DOUBLE = 191,
		CONSTANT_BIN_BYTE = 192,
		CONSTANT_BIN_LONG = 193,
		CONSTANT_BIN_LONG64 = 194,
		CONSTANT_BIN_INT = 195,
		CONSTANT_BIN_I = 196,
		CONSTANT_BIN_ULONG = 197,
		CONSTANT_BIN_ULONG64 = 198,
		CONSTANT_BIN_UI = 199,
		CONSTANT_BIN_UINT = 200,
		ASTERIX = 201,
		DOT = 202,
		STRING_LITERAL = 203,
		POW = 204,
		MATRIX_OP1 = 205,
		MATRIX_OP2 = 206,
		PLUS = 207,
		MINUS = 208,
		LTMARK = 209,
		GTMARK = 210,
		LOG_NEG = 211,
		LOG_AND = 212,
		LOG_OR = 213,
		QUESTION = 214,
		STRING = 215,
		INCLUDE = 216,
		EOL = 217,
		W = 218,
		D = 219,
		L = 220,
		H = 221,
		O = 222,
		B = 223,
		EXP = 224,
		DBL_E = 225,
		DBL = 226,
		CONSTANT_OR_STRING_LITERAL = 227,
		COMMENT = 228,
		END_MARKER = 229,
		WHITESPACE = 230,
		SKIP_LINES = 231,
		CONT_STATEMENT = 232,
		END_OF_LINE = 233,
		MAX_TOKEN_NUMBER = 234,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_GDLTreeParserTokenTypes_hpp_*/
