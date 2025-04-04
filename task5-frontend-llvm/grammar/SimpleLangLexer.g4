lexer grammar SimpleLangLexer;

// These are all supported lexer sections:

// Lexer file header. Appears at the top of h + cpp files. Use e.g. for copyrights.
@lexer::header {/* lexer header section */}

// Appears before any #include in h + cpp files.
@lexer::preinclude {/* lexer precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@lexer::postinclude {
/* lexer postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceds the lexer class declaration in the h file (e.g. for additional types etc.).
@lexer::context {/* lexer context section */}

// Appears in the public part of the lexer in the h file.
@lexer::members {/* public lexer declarations section */
}

// Appears in the private part of the lexer in the h file.
@lexer::declarations {/* private lexer declarations/members section */}

// Appears in line with the other class member definitions in the cpp file.
@lexer::definitions {/* lexer definitions section */}


ARROW: '->';
FUNC: 'func';
LCBRACE: '{';
RCBRACE: '}';
LPAREN: '(';
RPAREN: ')';
LBRACKET: '[';
RBRACKET: ']';

NOTEQUALS: '!=';
LESS: '<';
NOTGREATER: '<=';
GREATER: '>';
NOTLESS: '>=';
EQUALS: '==';

WHILE: 'while';
IF: 'if';
ALLOC: 'alloc';

SUB: '-';
MUL: '*';
ADD: '+';
DIV: '/';
AND: '&';
EQ: '=';


VAR: 'var';
SEMICOLON: ';';
RETURN: 'return';

ID: [a-zA-Z_]+;
INT: [0-9]+;
WS: [ \r\n\t]+ -> skip;



