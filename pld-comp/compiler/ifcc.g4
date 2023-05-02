grammar ifcc;

axiom       : prog ;

prog        : (func)? TYPE 'main' '(' ')' '{' code? '}' ;

func        : TYPE VAR '(' args? ')' '{' code? '}' func? ;

args        : TYPE VAR (',' args)? ;

code        : instruction ';'                                #uneInst
            | instruction ';' code                           #mulInst
            | '{' code? '}'                                  #block
            | IF '(' expr ')' code  ( ELSE code )? code?     #ifInst
            | WHILE '(' expr ')' code code?                  #whileInst
            | RETURN expr ';' code?                          #return
            ;

instruction : TYPE vars ('=' expr)?        #declaration
            | vars '=' expr                #affectation
            ;

expr        : expr OPM expr         #muldiv
            | expr OPP expr         #addsub
            | CONST                 #const
            | VAR                   #var
            | '(' expr ')'          #par
            | expr CMPOP expr       #cmp
            | VAR '(' input? ')'    #funcCall
            ;

vars        : VAR(',' vars)?;
input       : expr(',' input)?;
TYPE        : INT|CHAR;
INT         :'int';
CHAR        :'char';

IF: 'if';
ELSE: 'else';
WHILE: 'while';
RETURN      : 'return' ;
CONST       : [0-9]+ ;
OPM : ('*'|'/');
OPP : ('+'|'-');
CMPOP : ('=='|'!='|'>'|'<'|'<='|'>=');
COMMENT     : '/*' .*? '*/' -> skip ;
DIRECTIVE   : '#' .*? '\n' -> skip ;
WS          : [ \t\r\n] -> channel(HIDDEN);

VAR         : [a-zA-Z]+;