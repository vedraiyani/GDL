#ifndef INC_GDLTokenTypes_hpp_
#define INC_GDLTokenTypes_hpp_

/* $ANTLR 2.7.7 (20120518): "gdlc.g" -> "GDLTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API GDLTokenTypes {
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
		ARRAYEXPR_FCALL = 18,
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
		DEC_REF_CHECK = 68,
		INC_REF_CHECK = 69,
		POSTDEC = 70,
		POSTINC = 71,
		DECSTATEMENT = 72,
		INCSTATEMENT = 73,
		REF = 74,
		REF_VN = 75,
		REF_CHECK = 76,
		REF_CHECK_VN = 77,
		REF_EXPR = 78,
		REF_EXPR_VN = 79,
		REPEAT = 80,
		REPEAT_LOOP = 81,
		RETURN = 82,
		RETF = 83,
		RETP = 84,
		STRUC = 85,
		SYSVAR = 86,
		UMINUS = 87,
		VAR = 88,
		VARPTR = 89,
		WHILE = 90,
		IDENTIFIER = 91,
		AND_OP = 92,
		BEGIN = 93,
		CASE = 94,
		COMMON = 95,
		COMPILE_OPT = 96,
		DO = 97,
		ELSE = 98,
		END = 99,
		ENDCASE = 100,
		ENDELSE = 101,
		ENDFOR = 102,
		ENDFOREACH = 103,
		ENDIF = 104,
		ENDREP = 105,
		ENDSWITCH = 106,
		ENDWHILE = 107,
		EQ_OP = 108,
		FORWARD = 109,
		FUNCTION = 110,
		GE_OP = 111,
		GOTO = 112,
		GT_OP = 113,
		IF = 114,
		INHERITS = 115,
		LE_OP = 116,
		LT_OP = 117,
		MOD_OP = 118,
		NE_OP = 119,
		NOT_OP = 120,
		OF = 121,
		ON_IOERROR = 122,
		OR_OP = 123,
		PRO = 124,
		SWITCH = 125,
		THEN = 126,
		UNTIL = 127,
		XOR_OP = 128,
		METHOD = 129,
		COMMA = 130,
		COLON = 131,
		END_U = 132,
		EQUAL = 133,
		DEC = 134,
		INC = 135,
		AND_OP_EQ = 136,
		ASTERIX_EQ = 137,
		EQ_OP_EQ = 138,
		GE_OP_EQ = 139,
		GTMARK_EQ = 140,
		GT_OP_EQ = 141,
		LE_OP_EQ = 142,
		LTMARK_EQ = 143,
		LT_OP_EQ = 144,
		MATRIX_OP1_EQ = 145,
		MATRIX_OP2_EQ = 146,
		MINUS_EQ = 147,
		MOD_OP_EQ = 148,
		NE_OP_EQ = 149,
		OR_OP_EQ = 150,
		PLUS_EQ = 151,
		POW_EQ = 152,
		SLASH_EQ = 153,
		XOR_OP_EQ = 154,
		MEMBER = 155,
		LBRACE = 156,
		RBRACE = 157,
		SLASH = 158,
		LSQUARE = 159,
		RSQUARE = 160,
		SYSVARNAME = 161,
		EXCLAMATION = 162,
		LCURLY = 163,
		RCURLY = 164,
		CONSTANT_HEX_BYTE = 165,
		CONSTANT_HEX_LONG = 166,
		CONSTANT_HEX_LONG64 = 167,
		CONSTANT_HEX_INT = 168,
		CONSTANT_HEX_I = 169,
		CONSTANT_HEX_ULONG = 170,
		CONSTANT_HEX_ULONG64 = 171,
		CONSTANT_HEX_UI = 172,
		CONSTANT_HEX_UINT = 173,
		CONSTANT_BYTE = 174,
		CONSTANT_LONG = 175,
		CONSTANT_LONG64 = 176,
		CONSTANT_INT = 177,
		CONSTANT_I = 178,
		CONSTANT_ULONG = 179,
		CONSTANT_ULONG64 = 180,
		CONSTANT_UI = 181,
		CONSTANT_UINT = 182,
		CONSTANT_OCT_BYTE = 183,
		CONSTANT_OCT_LONG = 184,
		CONSTANT_OCT_LONG64 = 185,
		CONSTANT_OCT_INT = 186,
		CONSTANT_OCT_I = 187,
		CONSTANT_OCT_ULONG = 188,
		CONSTANT_OCT_ULONG64 = 189,
		CONSTANT_OCT_UI = 190,
		CONSTANT_OCT_UINT = 191,
		CONSTANT_FLOAT = 192,
		CONSTANT_DOUBLE = 193,
		CONSTANT_BIN_BYTE = 194,
		CONSTANT_BIN_LONG = 195,
		CONSTANT_BIN_LONG64 = 196,
		CONSTANT_BIN_INT = 197,
		CONSTANT_BIN_I = 198,
		CONSTANT_BIN_ULONG = 199,
		CONSTANT_BIN_ULONG64 = 200,
		CONSTANT_BIN_UI = 201,
		CONSTANT_BIN_UINT = 202,
		ASTERIX = 203,
		DOT = 204,
		STRING_LITERAL = 205,
		POW = 206,
		MATRIX_OP1 = 207,
		MATRIX_OP2 = 208,
		PLUS = 209,
		MINUS = 210,
		LTMARK = 211,
		GTMARK = 212,
		LOG_NEG = 213,
		LOG_AND = 214,
		LOG_OR = 215,
		QUESTION = 216,
		STRING = 217,
		INCLUDE = 218,
		EOL = 219,
		W = 220,
		D = 221,
		L = 222,
		H = 223,
		O = 224,
		B = 225,
		EXP = 226,
		DBL_E = 227,
		DBL = 228,
		CONSTANT_OR_STRING_LITERAL = 229,
		COMMENT = 230,
		END_MARKER = 231,
		WHITESPACE = 232,
		SKIP_LINES = 233,
		CONT_STATEMENT = 234,
		END_OF_LINE = 235,
		MAX_TOKEN_NUMBER = 236,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_GDLTokenTypes_hpp_*/
