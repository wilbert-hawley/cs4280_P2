#include "parser.h"
using namespace std;

void parse_error(token tok) {
    cout << "Error when processing " << tok.instance << endl;
    exit(1);
}

void parser(fstream& file) {
    int lineNumber = 0;
    char nextChar;
    file.get(nextChar);
    token tok = scanner(file, lineNumber, nextChar);
    //program_(tok);
    tok = scanner(file, lineNumber, nextChar);
    if(tok.tk == EOF_tk)
        cout << "End of file reached\n";
    else
        parse_error(tok);
    return;
}

/*<program> -> <vars> main <block>
void program_(token tok){
	if()
}

<block> -> { <vars> <stats> }
void block_()

<vars> -> empty | declare Identifier :=  whole ; <vars>

<expr> -> <N> - <expr> | <N>

<N> -> <N> / <A> | <N> + <A> | <A>

<A> -> <M> * <A> | <M>

<M> -> % <M> |  <R>

<R> -> ( <expr> ) | Identifier | Integer

<stats> -> <stat>  <mStat>

<mStat> -> empty |  <stat>  <mStat>

<stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop1> ; | <loop2> ; | <assign> ; | <goto> ; | <label> ;

<in> -> listen  Identifier

<out> -> yell <expr>

<if> -> if [ <expr> <RO> <expr> ] then <stat>

<loop1> -> repeat  [ <expr> <RO> <expr> ]  <stat>

<loop2> -> repeat <stat> until [ <expr> <RO> <expr> ]

<assign> -> assign Identifier  = <expr>

<RO> -> >=  | <= |  ==  |   ... (three tokens here) |  !=

<label> -> label Identifier

<goto> ->  portal Identifier*/