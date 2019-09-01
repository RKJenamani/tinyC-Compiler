%{
	#include <stdio.h>
	#include <string.h>
%}

%{
	#define AUTO				1
	#define BREAK	 			2
	#define CASE				3
	#define CHAR 				4
	#define CONST 				5
	#define CONTINUE 			6
	#define DEFAULT 			7
	#define DO 					8
	#define DOUBLE 				9
	#define ELSE 				10
	#define ENUM 				11
	#define EXTERN 				12
	#define FLOAT 				13
	#define FOR 				14
	#define GOTO 				15
	#define IF 					16
	#define INLINE 				17
	#define INT					18
	#define LONG 				19
	#define REGISTER 			20
	#define RESTRICT 			21
	#define RETURN 				22	
	#define SHORT 				23
	#define SIGNED				24
	#define SIZEOF 				25
	#define STATIC				26
	#define STRUCT 				27
	#define SWITCH 				28
	#define TYPEDEF 			29
	#define UNION 				30
	#define UNSIGNED 			31
	#define VOID 				32
	#define VOLATILE			33
	#define WHILE 				34
	#define _BOOL				35
	#define _COMPLEX 			36
	#define _IMAGINARY 			37

	#define SINGLE_LINE_COMMENT		38
	#define MULTI_LINE_COMMENT	 	39

	#define IDENTIFIER 			40
	#define INTEGER_CONSTANT 	41
	#define FLOATING_CONSTANT 	42
	#define CHARACTER_CONSTANT 	43
	#define STRING_LITERAL 		44

	#define SQUARE_BRACKET_OPEN 			45
	#define SQUARE_BRACKET_CLOSE 			46
	#define ROUND_BRACKET_OPEN 				47
	#define ROUND_BRACKET_CLOSE 			48
	#define CURLY_BRACKET_OPEN 				49
	#define CURLY_BRACKET_CLOSE 			50

	#define DOT 				51
	#define IMPLIES 			52
	#define INC 				53
	#define DEC 				54
	#define BITWISE_AND			55
	#define MUL 				56
	#define ADD 				57
	#define SUB 				58
	#define BITWISE_NOT			59
	#define EXCLAIM 			60
	#define DIV 				61
	#define MOD 				62
	#define SHIFT_LEFT 			63
	#define SHIFT_RIGHT 		64
	#define BIT_SL 	 			65
	#define BIT_SR 				66
	#define LTE 				67
	#define GTE 				68
	#define EQ 					69
	#define NEQ 				70
	#define BITWISE_XOR 		71
	#define BITWISE_OR 			72
	#define AND 				73
	#define OR 					74
	#define QUESTION 			75
	#define COLON 				76
	#define SEMICOLON 			77
	#define DOTS 				78
	#define ASSIGN 				79
	#define STAR_EQ 			80
	#define DIV_EQ 				81
	#define MOD_EQ 				82
	#define ADD_EQ 				83
	#define SUB_EQ 				84
	#define SL_EQ 				85
	#define SR_EQ 				86
	#define BITWISE_AND_EQ 		87
	#define BITWISE_XOR_EQ 		88
	#define BITWISE_OR_EQ 		89
	#define COMMA 				90
	#define HASH 				91
%}

/* REGEX DEFINITION */

/*KEYWORDS*/

KEYWORD 					"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"inline"|"int"|"long"|"register"|"restrict"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"|"_Bool"|"_Complex"|"_Imaginary"
	
/*IDENTIFIER*/

DIGIT						[0-9]
IDENTIFIER_NONDIGIT 		[a-zA-Z]|"_"
IDENTIFIER 					{IDENTIFIER_NONDIGIT}({IDENTIFIER_NONDIGIT}|{DIGIT})*

/*CONSTANTS*/

INTEGER_CONSTANT			{NONZERO_INTEGER_CONSTANT}|"0"
NONZERO_INTEGER_CONSTANT	{NONZERO_DIGIT}({NONZERO_DIGIT}|{DIGIT})*
NONZERO_DIGIT				[1-9]

CONSTANT					{INTEGER_CONSTANT}|{FLOATING_CONSTANT}|{ENUMERATION_CONSTANT}|{CHARACTER_CONSTANT}

FLOATING_CONSTANT			({FRACTIONAL_CONSTANT}{EXPONENT_PART}?)|({DIGIT_SEQUENCE}{EXPONENT_PART})
FRACTIONAL_CONSTANT			({DIGIT_SEQUENCE}?"."{DIGIT_SEQUENCE})|({DIGIT_SEQUENCE}".")
EXPONENT_PART				("e"{SIGN}?{DIGIT_SEQUENCE})|("E"{SIGN}?{DIGIT_SEQUENCE})
SIGN 						"+"|"-"
DIGIT_SEQUENCE				{DIGIT}({DIGIT})*


ENUMERATION_CONSTANT		{IDENTIFIER}

ESCAPE_SEQUENCE				"\'"|"\""|"\?"|"\\"|"\a"|"\b"|"\f"|"\n"|"\r"|"\t"|"\v"
C_CHAR 						{ESCAPE_SEQUENCE}|[^("\'"|"\\"|"\n")]
C_CHAR_SEQUENCE				{C_CHAR}+
CHARACTER_CONSTANT			"\'"{C_CHAR_SEQUENCE}"\'"


/*STRING_LITERALS*/
S_CHAR  					{ESCAPE_SEQUENCE}|[^("\""|"\\"|"\n")]
S_CHAR_SEQUENCE				{S_CHAR}+
STRING_LITERAL 				"\""{S_CHAR_SEQUENCE}?"\""


/*PUNCTUATORS*/
PUNCTUATOR 					"["|"]"|"("|")"|"{"|"}"|"."|"->"|"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"|"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"|"?"|":"|";"|"..."|"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="|","|"#"
				


/*COMMENTS*/
MULTI_LINE_COMMENT			"/*"[^"*"]*"*"("*"|([^"/*"]*[^"*"]*"*"))*"/"
SINGLE_LINE_COMMENT			"//"[^("\n")]*
COMMENT 					{SINGLE_LINE_COMMENT}|{MULTI_LINE_COMMENT}

%%

{KEYWORD}		{
if(strcmp(yytext,"auto")==0)			{ return AUTO; }
if(strcmp(yytext,"break")==0)			{ return BREAK; }
if(strcmp(yytext,"case")==0)			{ return CASE; }
if(strcmp(yytext,"char")==0)		  	{ return CHAR; }
if(strcmp(yytext,"const")==0)			{ return CONST; }
if(strcmp(yytext,"continue")==0)		{ return CONTINUE; }
if(strcmp(yytext,"default")==0)			{ return DEFAULT; }
if(strcmp(yytext,"do")==0)				{ return DO; }
if(strcmp(yytext,"double")==0)			{ return DOUBLE; }
if(strcmp(yytext,"else")==0)			{ return ELSE; }
if(strcmp(yytext,"enum")==0)			{ return ENUM; }
if(strcmp(yytext,"extern")==0)			{ return EXTERN; }
if(strcmp(yytext,"float")==0)			{ return FLOAT; }
if(strcmp(yytext,"for")==0)				{ return FOR; }
if(strcmp(yytext,"goto")==0)			{ return GOTO; }
if(strcmp(yytext,"signed")==0)		  	{ return SIGNED; }
if(strcmp(yytext,"struct")==0)			{ return STRUCT; }
if(strcmp(yytext,"_Imaginary")==0)		{ return _IMAGINARY; }
if(strcmp(yytext,"short")==0)			{ return SHORT; }
if(strcmp(yytext,"_Complex")==0)		{ return _COMPLEX; }
if(strcmp(yytext,"register")==0)		{ return REGISTER; }
if(strcmp(yytext,"void")==0)			{ return VOID; }
if(strcmp(yytext,"restrict")==0)		{ return RESTRICT; } 
if(strcmp(yytext,"unsigned")==0)		{ return UNSIGNED; }
if(strcmp(yytext,"return")==0)			{ return RETURN; }
if(strcmp(yytext,"volatile")==0)		{ return VOLATILE; }
if(strcmp(yytext,"while")==0)			{ return WHILE; }
if(strcmp(yytext,"sizeof")==0)			{ return SIZEOF; }
if(strcmp(yytext,"_Bool")==0)			{ return _BOOL; }
if(strcmp(yytext,"if")==0)				{ return IF; }
if(strcmp(yytext,"static")==0)			{ return STATIC; }
if(strcmp(yytext,"inline")==0)			{ return INLINE; }
if(strcmp(yytext,"int")==0)				{ return INT; }
if(strcmp(yytext,"switch")==0)			{ return SWITCH; }
if(strcmp(yytext,"long")==0)			{ return LONG; }
if(strcmp(yytext,"typedef")==0)			{ return TYPEDEF; }
if(strcmp(yytext,"union")==0)			{ return UNION; }
}


{IDENTIFIER}	{
	return IDENTIFIER;
}

{INTEGER_CONSTANT}	{
	return INTEGER_CONSTANT;
}

{FLOATING_CONSTANT}	{
	return FLOATING_CONSTANT;
}

{CHARACTER_CONSTANT} {
	return CHARACTER_CONSTANT;
}

{STRING_LITERAL} {
	return STRING_LITERAL;
}

{PUNCTUATOR}	{
	if(strcmp(yytext,"[") == 0) return SQUARE_BRACKET_OPEN;
	if(strcmp(yytext,"]") == 0) return SQUARE_BRACKET_CLOSE;
	if(strcmp(yytext,"(") == 0) return ROUND_BRACKET_OPEN;
	if(strcmp(yytext,")") == 0) return ROUND_BRACKET_CLOSE;
	if(strcmp(yytext,"{") == 0) return CURLY_BRACKET_OPEN;
	if(strcmp(yytext,"}") == 0) return CURLY_BRACKET_CLOSE;
	if(strcmp(yytext,".") == 0) return DOT;
	if(strcmp(yytext,"->") == 0) return IMPLIES;
	if(strcmp(yytext,"++") == 0) return INC;
	if(strcmp(yytext,"--") == 0) return DEC;
	if(strcmp(yytext,"&") == 0) return BITWISE_AND;
	if(strcmp(yytext,"*") == 0) return MUL;
	if(strcmp(yytext,"+") == 0) return ADD;
	if(strcmp(yytext,"-") == 0) return SUB;
	if(strcmp(yytext,"~") == 0) return BITWISE_NOT;
	if(strcmp(yytext,"!") == 0) return EXCLAIM;
	if(strcmp(yytext,"/") == 0) return DIV;
	if(strcmp(yytext,"%") == 0) return MOD;
	if(strcmp(yytext,"<<") == 0) return SHIFT_LEFT;
	if(strcmp(yytext,">>") == 0) return SHIFT_RIGHT;
	if(strcmp(yytext,"<") == 0) return BIT_SL;
	if(strcmp(yytext,">") == 0) return BIT_SR;
	if(strcmp(yytext,"<=") == 0) return LTE;
	if(strcmp(yytext,">=") == 0) return GTE;
	if(strcmp(yytext,"==") == 0) return EQ;
	if(strcmp(yytext,"!=") == 0) return NEQ;
	if(strcmp(yytext,"^") == 0) return BITWISE_XOR;
	if(strcmp(yytext,"|") == 0) return BITWISE_OR;
	if(strcmp(yytext,"&&") == 0) return AND;
	if(strcmp(yytext,"||") == 0) return OR;
	if(strcmp(yytext,"?") == 0) return QUESTION;
	if(strcmp(yytext,":") == 0) return COLON;
	if(strcmp(yytext,";") == 0) return SEMICOLON;
	if(strcmp(yytext,"...") == 0) return DOTS;
	if(strcmp(yytext,"=") == 0) return ASSIGN;
	if(strcmp(yytext,"*=") == 0) return STAR_EQ;
	if(strcmp(yytext,"/=") == 0) return DIV_EQ;
	if(strcmp(yytext,"%=") == 0) return MOD_EQ;
	if(strcmp(yytext,"+=") == 0) return ADD_EQ;
	if(strcmp(yytext,"-=") == 0) return SUB_EQ;
	if(strcmp(yytext,"<<=") == 0) return SL_EQ;
	if(strcmp(yytext,">>=") == 0) return SR_EQ;
	if(strcmp(yytext,"&=") == 0) return BITWISE_AND_EQ;
	if(strcmp(yytext,"^=") == 0) return BITWISE_XOR_EQ;
	if(strcmp(yytext,"|=") == 0) return BITWISE_OR_EQ;
	if(strcmp(yytext,",") == 0) return COMMA;
	if(strcmp(yytext,"#") == 0) return HASH;
}

"\n"|" "|"\t"	{

}
{SINGLE_LINE_COMMENT}					{return SINGLE_LINE_COMMENT;}
{MULTI_LINE_COMMENT} 					{return MULTI_LINE_COMMENT;}

%%
