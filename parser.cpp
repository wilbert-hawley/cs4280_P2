#include "parser.h"
using namespace std;

token tok;
char nextChar;
int lineNumber = 0;

void parse_error() {
    cout << "Error when processing " << tok.instance << endl;
    exit(1);
}

void parser(fstream& file) {

    //char nextChar;
    file.get(nextChar);
    tok = scanner(file, lineNumber, nextChar);
    program_(file);
    //tok = scanner(file, lineNumber, nextChar);
    if(tok.tk == EOF_tk)
        cout << "End of file reached\n";
    else
        parse_error();
    return;
}

/*enum tokenID {
    ID_tk, KEY_tk, NUM_tk,
    EOF_tk, ERR_tk, START_tk, STOP_tk, REPEAT_tk, UNTIL_tk, WHOLE_tk, LABEL_tk, QUIT_tk, LISTEN_tk,
    YELL_tk, MAIN_tk, PORTAL_tk, IF_tk, THEN_tk, PICK_tk, DECLARE_tk, ASSIGN_tk, PROC_tk, EQUAL_tk,
    DUBEQUAL_tk, LESS_tk, GREAT_tk, NOTEQU_tk, COL_tk, COLEQU_tk, PLUS_tk, SUB_tk, MULT_tk, SLASH_tk,
    MOD_tk, DOT_tk, LPARA_tk, RPARA_tk, COMMA_tk, LCURLY_tk, RCURLY_tk, SEMI_tk, LBRAK_tk, RBRAK_tk
};*/

//<program> -> <vars> main <block>
void program_(fstream &file){
    cout << "Entering program_()\n";
    vars_(file);
	if(tok.tk == MAIN_tk) {
	    cout << "Found MAIN_tk\n";
        tok = scanner(file, lineNumber, nextChar);
        //block_(file);
	    return;
	}
	cout << "Made it back to program_()\n";
}

// <block> -> { <vars> <stats> }
void block_(fstream& file) {

    return;
}

//<vars> -> empty | declare Identifier :=  whole ; <vars>
void vars_(fstream& file) {
    if(tok.tk == DECLARE_tk) {
        cout << "Found declare\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found Identifier\n";
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == COLEQU_tk) {
                cout << "Found colon equal\n";
                tok = scanner(file, lineNumber, nextChar);
                if(tok.tk == WHOLE_tk) {
                    cout << "Found whole\n";
                    tok = scanner(file, lineNumber, nextChar);
                    if(tok.tk == SEMI_tk) {
                        cout << "Found semicolon\n";
                        tok = scanner(file, lineNumber, nextChar);
                        vars_(file);
                        return;
                    } else parse_error();
                } else parse_error();
            } else parse_error();
        } else parse_error();
    }
    else {
        cout << "Returning empty <vars>\n";
        return;
    }

}

// <expr> -> <N> - <expr> | <N>
void expr_(fstream& file) {
    N_(file);
    return;
}

// <N> -> <N> / <A> | <N> + <A> | <A>
void N_(fstream& file) {

    return;
}

// <A> -> <M> * <A> | <M>
void A_(fstream& file) {

    return;
}

// <M> -> % <M> |  <R>
void M_(fstream& file) {

    return;
}

// <R> -> ( <expr> ) | Identifier | Integer
void R_(fstream& file) {

    return;
}

// <stats> -> <stat>  <mStat>
void stats_(fstream& file) {

    return;
}

// <mStat> -> empty |  <stat>  <mStat>
void mStat_(fstream& file) {

    return;
}

// <stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop1> ; | <loop2> ; | <assign> ; | <goto> ; | <label> ;
void stat_(fstream& file) {

    return;
}

// <in> -> listen  Identifier
void in_(fstream& file) {

    return;
}

// <out> -> yell <expr>
void out_(fstream& file) {

    return;
}

// <if> -> if [ <expr> <RO> <expr> ] then <stat>
void if_(fstream& file) {

    return;
}

// <loop1> -> repeat  [ <expr> <RO> <expr> ]  <stat>
void loop1_(fstream& file) {

    return;
}

// <loop2> -> repeat <stat> until [ <expr> <RO> <expr> ]
void loop2_(fstream& file) {

    return;
}

// <assign> -> assign Identifier  = <expr>
void assign_(fstream& file) {

    return;
}

// <RO> -> >=  | <= |  ==  |   ... (three tokens here) |  !=
void R0_(fstream& file) {

    return;
}

// <label> -> label Identifier
void label_(fstream& file) {

    return;
}

// <goto> ->  portal Identifier*/
void goto_(fstream& file) {

    return;
}
