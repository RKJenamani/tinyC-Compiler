%{ /* C Declarations and Definitions */
	#include <string.h>
	#include <stdio.h>

	extern int yylex();
	void yyerror(char *s);
%}

%union {
int intval;
}

%token AUTO BREAK CASE CHAR CONST CONTINUE DEFAULT DO DOUBLE ELSE ENUM EXTERN FLOAT FOR GOTO IF INLINE INT LONG REGISTER RESTRICT RETURN SHORT SIGNED SIZEOF STATIC STRUCT SWITCH TYPEDEF UNION UNSIGNED VOID VOLATILE WHILE _BOOL _COMPLEX _IMAGINARY 

%token IDENTIFIER INTEGER_CONSTANT FLOATING_CONSTANT CHARACTER_CONSTANT STRING_LITERAL ENUMERATION_CONSTANT

%token SQUARE_BRACKET_OPEN SQUARE_BRACKET_CLOSE
%token ROUND_BRACKET_OPEN ROUND_BRACKET_CLOSE
%token CURLY_BRACKET_OPEN CURLY_BRACKET_CLOSE

%token DOT IMPLIES INC DEC BITWISE_AND MUL ADD SUB BITWISE_NOT EXCLAIM DIV MOD SHIFT_LEFT SHIFT_RIGHT BIT_SL BIT_SR 
%token LTE GTE EQ NEQ BITWISE_XOR BITWISE_OR AND OR
%token QUESTION COLON SEMICOLON DOTS ASSIGN 
%token STAR_EQ DIV_EQ MOD_EQ ADD_EQ SUB_EQ SL_EQ SR_EQ BITWISE_AND_EQ BITWISE_XOR_EQ BITWISE_OR_EQ 
%token COMMA HASH 
%start translation_unit

%%

primary_expression
	: IDENTIFIER
	| constant
	| STRING_LITERAL
	| ROUND_BRACKET_OPEN expression ROUND_BRACKET_CLOSE
	{printf("| Rule: primary_expression |\n");}
	;

constant
	: INTEGER_CONSTANT 
	| FLOATING_CONSTANT 
	| CHARACTER_CONSTANT
	;

postfix_expression
	: primary_expression
	| postfix_expression SQUARE_BRACKET_OPEN expression SQUARE_BRACKET_CLOSE
	| postfix_expression ROUND_BRACKET_OPEN argument_expression_list_opt ROUND_BRACKET_CLOSE
	| postfix_expression DOT IDENTIFIER
	| postfix_expression IMPLIES IDENTIFIER
	| postfix_expression INC
	| postfix_expression DEC
	| ROUND_BRACKET_OPEN type_name ROUND_BRACKET_CLOSE CURLY_BRACKET_OPEN initializer_list CURLY_BRACKET_CLOSE
	| ROUND_BRACKET_OPEN type_name ROUND_BRACKET_CLOSE CURLY_BRACKET_OPEN initializer_list COMMA CURLY_BRACKET_CLOSE
	{printf("| Rule: postfix_expression |\n");}
	;

argument_expression_list_opt
	: argument_expression_list
	| %empty
    ;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA assignment_expression
	{printf("| Rule: argument_expression_list |\n");}
	;

unary_expression
	: postfix_expression
	| INC unary_expression
	| DEC unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF ROUND_BRACKET_OPEN type_name ROUND_BRACKET_CLOSE
	{printf("| Rule: unary_expression |\n");}
	;

unary_operator
	: BITWISE_AND
	| MUL
	| ADD
	| SUB
	| BITWISE_NOT
	| EXCLAIM
	{printf("| Rule: unary_operator |\n");}
	;

cast_expression
	: unary_expression
	| ROUND_BRACKET_OPEN type_name ROUND_BRACKET_CLOSE cast_expression
	{printf("| Rule: cast_expression |\n");}
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression MUL cast_expression
	| multiplicative_expression DIV cast_expression
	| multiplicative_expression MOD cast_expression
	{printf("| Rule: multiplicative_expression |\n");}
	;

additive_expression
	: multiplicative_expression
	| additive_expression ADD multiplicative_expression
	| additive_expression SUB multiplicative_expression
	{printf("| Rule: additive_expression |\n");}
	;

shift_expression
	: additive_expression
	| shift_expression SHIFT_LEFT additive_expression
	| shift_expression SHIFT_RIGHT additive_expression
	{printf("| Rule: shift_expression |\n");}
	;

relational_expression
	: shift_expression
	| relational_expression BIT_SL shift_expression
	| relational_expression BIT_SR shift_expression
	| relational_expression LTE shift_expression
	| relational_expression GTE shift_expression
	{printf("| Rule: relational_expression |\n");}
	;

equality_expression
	: relational_expression
	| equality_expression EQ relational_expression
	| equality_expression NEQ relational_expression
	{printf("| Rule: equality_expression |\n");}
	;

and_expression
	: equality_expression
	| and_expression BITWISE_AND equality_expression
	{printf("| Rule: and_expression |\n");}
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression BITWISE_XOR and_expression
	{printf("| Rule: exclusive_or_expression |\n");}
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression BITWISE_OR exclusive_or_expression
	{printf("| Rule: inclusive_or_expression |\n");}
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND inclusive_or_expression
	{printf("| Rule: logical_and_expression |\n");}
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR logical_and_expression
	{printf("| Rule: logical_or_expression |\n");}
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression QUESTION expression COLON conditional_expression
	{printf("| Rule: conditional_expression |\n");}
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	{printf("| Rule: assignment_expression |\n");}
	;

assignment_operator
	: ASSIGN
	| STAR_EQ
	| DIV_EQ
	| MOD_EQ
	| ADD_EQ
	| SUB_EQ
	| SL_EQ
	| SR_EQ
	| BITWISE_AND_EQ
	| BITWISE_XOR_EQ
	| BITWISE_OR_EQ
	{printf("| Rule: assignment_operator |\n");}
	;

expression
	: assignment_expression
	| expression COMMA assignment_expression
	{printf("| Rule: expression |\n");}
	;

constant_expression
	: conditional_expression
	{printf("| Rule: constant_expression |\n");}
	;

declaration
	: declaration_specifiers init_declarator_list_opt SEMICOLON
	{printf("| Rule: declaration |\n");}
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers_opt
	| type_specifier declaration_specifiers_opt
	| type_qualifier declaration_specifiers_opt
	| function_specifier declaration_specifiers_opt
	{printf("| Rule: declaration_specifiers |\n");}
	;

declaration_specifiers_opt
	: declaration_specifiers
	| %empty
	;

init_declarator_list
	: init_declarator
	| init_declarator_list COMMA init_declarator
	{printf("| Rule: init_declarator_list |\n");}
	;

init_declarator_list_opt
	: init_declarator_list
	| %empty
	;

init_declarator
	: declarator
	| declarator ASSIGN initializer
	{printf("| Rule: init_declarator |\n");}
	;

storage_class_specifier
	: EXTERN
	| STATIC
	| AUTO
	| REGISTER
	{printf("| Rule: storage_class_specifier |\n");}
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| _BOOL
	| _COMPLEX
	| _IMAGINARY
	| enum_specifier
	{printf("| Rule: type_specifier |\n");}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list_opt
	| type_qualifier specifier_qualifier_list_opt
	{printf("| Rule: specifier_qualifier_list |\n");}
	;

specifier_qualifier_list_opt
	: specifier_qualifier_list
	| %empty
	;


enum_specifier
	: ENUM identifier_opt CURLY_BRACKET_OPEN enumerator_list CURLY_BRACKET_CLOSE
	| ENUM identifier_opt CURLY_BRACKET_OPEN enumerator_list COMMA CURLY_BRACKET_CLOSE
	| ENUM IDENTIFIER
	{printf("| Rule: enum_specifier |\n");}
	;

identifier_opt
	: IDENTIFIER
	| %empty
	;

enumerator_list
	: enumerator
	| enumerator_list COMMA enumerator
	{printf("| Rule: enumerator_list |\n");}
	;

enumerator
	: ENUMERATION_CONSTANT
	| ENUMERATION_CONSTANT ASSIGN constant_expression
	{printf("| Rule: enumerator |\n");}
	;

type_qualifier
	: CONST
	| VOLATILE
	| RESTRICT
	{printf("| Rule: type_qualifier |\n");}
	;

function_specifier
	: INLINE
	{printf("| Rule: function_specifier |\n");}
	;

declarator
	: pointer_opt direct_declarator
	{printf("| Rule: declarator |\n");}
	;

direct_declarator
	: IDENTIFIER
	| ROUND_BRACKET_OPEN declarator ROUND_BRACKET_CLOSE
	| direct_declarator SQUARE_BRACKET_OPEN  type_qualifier_list_opt assignment_expression_opt SQUARE_BRACKET_CLOSE
	| direct_declarator SQUARE_BRACKET_OPEN STATIC type_qualifier_list_opt assignment_expression SQUARE_BRACKET_CLOSE
	| direct_declarator SQUARE_BRACKET_OPEN type_qualifier_list STATIC assignment_expression SQUARE_BRACKET_CLOSE
	| direct_declarator SQUARE_BRACKET_OPEN type_qualifier_list_opt MUL SQUARE_BRACKET_CLOSE
	| direct_declarator ROUND_BRACKET_OPEN parameter_type_list ROUND_BRACKET_CLOSE
	| direct_declarator ROUND_BRACKET_OPEN identifier_list_opt ROUND_BRACKET_CLOSE
	{printf("| Rule: direct_declarator |\n");}
	;

type_qualifier_list_opt
	: type_qualifier_list
	| %empty
	;

pointer_opt
	: pointer
	| %empty
	;

assignment_expression_opt
	: assignment_expression
	| %empty
	;

identifier_list_opt
	: identifier_list
	| %empty
	;

pointer
	: MUL type_qualifier_list_opt
	| MUL type_qualifier_list_opt pointer
	{printf("| Rule: pointer |\n");}
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	{printf("| Rule: type_qualifier_list |\n");}
	;


parameter_type_list
	: parameter_list
	| parameter_list COMMA DOTS
	{printf("| Rule: parameter_type_list |\n");}
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMA parameter_declaration
	{printf("| Rule: parameter_list |\n");}
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers
	{printf("| Rule: parameter_declaration |\n");}
	;

identifier_list
	: IDENTIFIER
	| identifier_list COMMA IDENTIFIER
	{printf("| Rule: identifier_list |\n");}
	;

type_name
	: specifier_qualifier_list
	{printf("| Rule: type_name |\n");}
	;

initializer
	: assignment_expression
	| CURLY_BRACKET_OPEN initializer_list CURLY_BRACKET_CLOSE
	| CURLY_BRACKET_OPEN initializer_list COMMA CURLY_BRACKET_CLOSE
	{printf("| Rule: initializer |\n");}
	;

initializer_list
	: designation_opt initializer
	| initializer_list COMMA designation_opt initializer
	{printf("| Rule: initializer_list |\n");}
	;

designation_opt
	: designation
	| %empty
	;

designation
	: designator_list ASSIGN
	{printf("| Rule: designation |\n");}
	;

designator_list
	: designator
	| designator_list designator
	{printf("| Rule: designator_list |\n");}
	;

designator
	: SQUARE_BRACKET_OPEN constant_expression SQUARE_BRACKET_CLOSE
	| DOT IDENTIFIER
	{printf("| Rule: designator |\n");}
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	{printf("| Rule: statement |\n");}
	;

labeled_statement
	: IDENTIFIER COLON statement
	| CASE constant_expression COLON statement
	| DEFAULT COLON statement
	{printf("| Rule: labeled_statement |\n");}
	;

compound_statement
	: CURLY_BRACKET_OPEN block_item_list_opt CURLY_BRACKET_CLOSE
	{printf("| Rule: compound_statement |\n");}
	;

block_item_list_opt
	: block_item_list
	| %empty
	;

block_item_list
	: block_item
	| block_item_list block_item
	{printf("| Rule: block_item_list |\n");}
	;

block_item
	: declaration
	| statement
	{printf("| Rule: block_item |\n");}
	;

expression_statement
	: expression_opt SEMICOLON
	{printf("| Rule: expression_statement |\n");}
	;

expression_opt
	: expression
	| %empty
	;

selection_statement
	: IF ROUND_BRACKET_OPEN expression ROUND_BRACKET_CLOSE statement
	| IF ROUND_BRACKET_OPEN expression ROUND_BRACKET_CLOSE statement ELSE statement
	| SWITCH ROUND_BRACKET_OPEN expression ROUND_BRACKET_CLOSE statement
	{printf("| Rule: selection_statement |\n");}
	;

iteration_statement
	: WHILE ROUND_BRACKET_OPEN expression ROUND_BRACKET_CLOSE statement
	| DO statement WHILE ROUND_BRACKET_OPEN expression ROUND_BRACKET_CLOSE SEMICOLON
	| FOR ROUND_BRACKET_OPEN expression_opt SEMICOLON expression_opt SEMICOLON expression_opt ROUND_BRACKET_CLOSE statement
	| FOR ROUND_BRACKET_OPEN declaration expression_opt SEMICOLON expression_opt ROUND_BRACKET_CLOSE statement
	{printf("| Rule: iteration_statement |\n");}
	;

jump_statement
	: GOTO IDENTIFIER SEMICOLON
	| CONTINUE SEMICOLON
	| BREAK SEMICOLON
	| RETURN expression_opt SEMICOLON
	{printf("| Rule: jump_statement |\n");}
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	{printf("| Rule: translation_unit |\n");}
	;

external_declaration
	: function_definition
	| declaration
	{printf("| Rule: external_declaration |\n");}
	;

function_definition
	: declaration_specifiers declarator declaration_list_opt compound_statement
	{printf("| Rule: function_definition |\n");}
	;

declaration_list_opt
	: declaration_list
	| %empty
	;

declaration_list
	: declaration
	| declaration_list declaration
	{printf("| Rule: declaration_list |\n");}
	;

%%
void yyerror(char *s) {
	printf("The error is: %s\n", s);
}
