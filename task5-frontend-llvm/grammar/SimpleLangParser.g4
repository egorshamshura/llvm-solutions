parser grammar SimpleLangParser;

options { tokenVocab=SimpleLangLexer; }

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.
@parser::header {/* parser/listener/visitor header section */}

// Appears before any #include in h + cpp files.
@parser::preinclude {/* parser precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@parser::postinclude {
/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
}

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}

main: funcDecl+;


/* Function declaration */
funcDecl: FUNC funcName LPAREN funcArgs RPAREN ARROW return_type LCBRACE 
  funcBody 
  RETURN ID SEMICOLON 
RCBRACE;

funcName: ID;
funcArgs: ID*;
return_type: ID;

/* Function body and expression */
funcBody: expr;
expr: expr_line*;
expr_line: varDecl SEMICOLON
		| ID EQ primary_expr SEMICOLON
		| funcCall SEMICOLON
		| RETURN ID SEMICOLON 
		| WHILE LPAREN cond_expr RPAREN LCBRACE expr RCBRACE
		| IF LPAREN cond_expr RPAREN LCBRACE expr RCBRACE
		; 

/* Variable declaration and function call */
varDecl: VAR ID EQ primary_expr;
funcCall: ID LPAREN funcArgs RPAREN;

/* Math expression */
primary_expr:
	SUB primary_expr
	| primary_expr (MUL | DIV) primary_expr
	| primary_expr (ADD | SUB) primary_expr
	| LPAREN primary_expr RPAREN
	| INT
	| ID
	| funcCall
	;

/* Conditional expression */
cond_expr: 
	ID LESS ID
	| ID NOTGREATER ID
	| ID GREATER ID
	| ID NOTLESS ID
	| ID EQUALS ID
	| ID NOTEQUALS ID
	;


