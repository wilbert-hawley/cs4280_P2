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

    file.get(nextChar);
    tok = scanner(file, lineNumber, nextChar);
    program_(file);
    if(tok.tk == EOF_tk)
        cout << "End of file reached\n";
    else
        parse_error();
    return;
}



//<program> -> <vars> main <block>
void program_(fstream &file){
    cout << "Entering program_()\n";
    vars_(file);
	if(tok.tk == MAIN_tk) {
	    cout << "Found MAIN_tk\n";
        tok = scanner(file, lineNumber, nextChar);
        block_(file);
	    return;
	} else parse_error();
	cout << "Made it back to program_()\n";
}

// <block> -> { <vars> <stats> }
void block_(fstream& file) {
    cout << "Entering block_()\n";
    if(tok.tk == LCURLY_tk) {
        cout << "Found LCURLY_tk in block_()\n";
        tok = scanner(file, lineNumber, nextChar);
        vars_(file);
        stats_(file);
        if(tok.tk == RCURLY_tk) {
            cout << "Found RCURLY_tk in block_()\n";
            tok = scanner(file, lineNumber, nextChar);
            return;
        } else parse_error();
    } else parse_error();
    return;
}

//<vars> -> empty | declare Identifier :=  whole ; <vars>
void vars_(fstream& file) {
    cout << "Entering vars()\n";
    if(tok.tk == DECLARE_tk) {
        cout << "Found declare in vars()\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found Identifier in vars()\n";
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == COLEQU_tk) {
                cout << "Found colon equal in vars()\n";
                tok = scanner(file, lineNumber, nextChar);
                if(tok.tk == WHOLE_tk) {
                    cout << "Found whole in vars()\n";
                    tok = scanner(file, lineNumber, nextChar);
                    if(tok.tk == SEMI_tk) {
                        cout << "Found semicolon in vars()\n";
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

/*enum tokenID {
    ID_tk, KEY_tk, NUM_tk,
    EOF_tk, ERR_tk, START_tk, STOP_tk, REPEAT_tk, UNTIL_tk, WHOLE_tk, LABEL_tk, QUIT_tk, LISTEN_tk,
    YELL_tk, MAIN_tk, PORTAL_tk, IF_tk, THEN_tk, PICK_tk, DECLARE_tk, ASSIGN_tk, PROC_tk, EQUAL_tk,
    DUBEQUAL_tk, LESS_tk, GREAT_tk, NOTEQU_tk, COL_tk, COLEQU_tk, PLUS_tk, SUB_tk, MULT_tk, SLASH_tk,
    MOD_tk, DOT_tk, LPARA_tk, RPARA_tk, COMMA_tk, LCURLY_tk, RCURLY_tk, SEMI_tk, LBRAK_tk, RBRAK_tk
};*/

//tok = scanner(file, lineNumber, nextChar);

// <expr> -> <N> - <expr> | <N>
void expr_(fstream& file) {
    cout << "Entering expr_()\n";
    N_(file);

    if(tok.tk == SUB_tk){
        cout << "Found minus in expr_()\n";
        tok = scanner(file, lineNumber, nextChar);
        expr_(file);
        return;
    }
    else
        return;
}

/* // <N> -> <A> <N1>
void N_(fstream& file) {
    cout << "Entering N_()\n";
    A_(file);
    N1_(file);
    return;
}

// <N1> -> / <A> | + A | empty
void N1_(fstream& file) {
    cout << "Entering N1_()\n";
    if(tok.tk == SLASH_tk) {
        cout << "Found SLAHS_tk in N1\n";
        tok = scanner(file, lineNumber, nextChar);
        A_(file);
        return;
    }
    else if (tok.tk == PLUS_tk) {
        cout << "Found PLUS_tk in N1\n";
        tok = scanner(file, lineNumber, nextChar);
        A_(file);
        return;
    } else
        return;
} */

// N -> <A> / <N> | <A> + <N> | <A>
void N_(fstream& file) {
    cout << "Entering N_()\n";
    A_(file);
    if(tok.tk == SLASH_tk) {
        cout << "Found SLAHS_tk in N()\n";
        tok = scanner(file, lineNumber, nextChar);
        N_(file);
        return;
    }
    else if (tok.tk == PLUS_tk) {
        cout << "Found PLUS_tk in N()\n";
        tok = scanner(file, lineNumber, nextChar);
        N_(file);
        return;
    } else
        return;
}

// <A> -> <M> * <A> | <M>
void A_(fstream& file) {
    cout << "Entering A_()\n";
    M_(file);
    if(tok.tk == MULT_tk) {
        cout << "Found MULT_tk in A_()\n";
        tok = scanner(file, lineNumber, nextChar);
        A_(file);
        return;
    } else
        return;
}

// <M> -> % <M> |  <R>
void M_(fstream& file) {
    cout << "Entering M_()\n";
    if(tok.tk == MOD_tk) {
        cout << "Found MOD_tk in M_()\n";
        tok = scanner(file, lineNumber, nextChar);
        M_(file);
        return;
    } else {
        R_(file);
        return;
    }

    return;
}

// <R> -> ( <expr> ) | Identifier | Integer
void R_(fstream& file) {
    cout << "Entering R_()\n";
    if(tok.tk == LPARA_tk) {
        cout << "Found LPARA_tk in R_()\n";
        tok = scanner(file, lineNumber, nextChar);
        expr_(file);
        if(tok.tk == RPARA_tk) {
            cout << "Found RPARA_tk in R_()\n";
            tok = scanner(file, lineNumber, nextChar);
            return;
        } else parse_error();
    } else if(tok.tk == ID_tk) {
        cout << "Found ID_tk in R_()\n";
        tok = scanner(file, lineNumber, nextChar);
        return;
    } else if(tok.tk == NUM_tk) {
        cout << "Found NUM_tk in R_()\n";
        tok = scanner(file, lineNumber, nextChar);
        return;
    } else parse_error();

    return;
}

// <stats> -> <stat>  <mStat>
void stats_(fstream& file) {
    cout << "Entering stats_()\n";
    stat_(file);
    mStat_(file);
    return;
}

// <mStat> -> empty |  <stat>  <mStat>
void mStat_(fstream& file) {
    cout << "Entering mStat()\n";
    switch(tok.tk) {
        case LISTEN_tk: // in
            break;
        case YELL_tk: // out
            break;
        case LCURLY_tk: // block
            return;
        case IF_tk: // if
            break;
        case REPEAT_tk:
            break;
        case ASSIGN_tk:
            break;
        case PORTAL_tk:
            break;
        case LABEL_tk:
            break;
        default:
            return;
    }
    stat_(file);
    mStat_(file);
    return;
}

// <stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop1> ; | <loop2> ; | <assign> ; | <goto> ; | <label> ;
void stat_(fstream& file) {
    cout << "Entering stat_()\n";
    switch(tok.tk) {
        case LISTEN_tk: // in
            in_(file);
            break;
        case YELL_tk: // out
            out_(file);
            break;
        case LCURLY_tk: // block
            block_(file);
            return;
        case IF_tk: // if
            if_(file);
            break;
        case REPEAT_tk:
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == LBRAK_tk) {
                loop1_(file);
            }
            else
                loop2_(file);
            break;
        case ASSIGN_tk:
            assign_(file);
            break;
        case PORTAL_tk:
            goto_(file);
            break;
        case LABEL_tk:
            label_(file);
            break;
        default:
            cout << "Messed up in stat_()\n";
            parse_error();
    }

    if (tok.tk == SEMI_tk) {
        cout << "Found SEMI_tk in stat_()\n";
        tok = scanner(file, lineNumber, nextChar);
        return;
    } else parse_error();

    return;
}

// <in> -> listen  Identifier
void in_(fstream& file) {
    cout << "Entering in_()\n";
    if(tok.tk == LISTEN_tk) {
        cout << "Found LISTEN_tk in in_()\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in in_()\n";
            tok = scanner(file, lineNumber, nextChar);
            return;
        } else parse_error();
    } else parse_error();
    return;
}

// <out> -> yell <expr>
void out_(fstream& file) {
    cout << "Entering out_()\n";
    if(tok.tk == YELL_tk) {
        cout << "Found YELL_tk in out_()\n";
        tok = scanner(file, lineNumber, nextChar);
        expr_(file);
        return;
    } else parse_error();
    return;
}

// <if> -> if [ <expr> <RO> <expr> ] then <stat>
void if_(fstream& file) {
    cout << "Entering if_()\n";
    if(tok.tk == IF_tk) {
        cout << "Found IN_tk in if_()\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == LBRAK_tk) {
            cout << "Found LBRAK_tk in if_()\n";
            tok = scanner(file, lineNumber, nextChar);
            expr_(file);
            R0_(file);
            expr_(file);
            if(tok.tk == RBRAK_tk) {
                cout << "Found RBRAK_tk in if_()\n";
                tok = scanner(file, lineNumber, nextChar);
                if(tok.tk == THEN_tk) {
                    cout << "Found THEN_tk in if_()\n";
                    tok = scanner(file, lineNumber, nextChar);
                    stat_(file);
                    return;
                } else parse_error();
            } else parse_error();
        } else parse_error();
    } else parse_error();
    return;
}

// <loop1> -> repeat  [ <expr> <RO> <expr> ]  <stat>
void loop1_(fstream& file) {
    cout << "Entering loop1_()\n";
    cout << "Found REAPEAT_tk in loop1_()\n";
    if(tok.tk == LBRAK_tk) {
        cout << "Found LBRAK_tk in loop1_()\n";
        tok = scanner(file, lineNumber, nextChar);
        expr_(file);
        R0_(file);
        expr_(file);
        if(tok.tk == RBRAK_tk) {
            cout << "Found RBRAK_tk in loop1_()\n";
            tok = scanner(file, lineNumber, nextChar);
            stat_(file);
            return;
        } else parse_error();
    } else parse_error();
    return;
}

// <loop2> -> repeat <stat> until [ <expr> <RO> <expr> ]
void loop2_(fstream& file) {
    cout << "Entering loop2_()\n";
    cout << "Found REAPEAT_tk in loop2_()\n";
    stat_(file);
    if(tok.tk == UNTIL_tk) {
        cout << "Found UNTIL_tk in loop2_()\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == LBRAK_tk) {
            cout << "Found LBRAK_tk in loop2_()\n";
            tok = scanner(file, lineNumber, nextChar);
            expr_(file);
            R0_(file);
            expr_(file);
            if(tok.tk == RBRAK_tk) {
                cout << "Found RBRAK_tk in loop2()\n";
                tok = scanner(file, lineNumber, nextChar);
                return;
            } else parse_error();
        } else parse_error();
    } else parse_error();
    return;
}

// <assign> -> assign Identifier  = <expr>
void assign_(fstream& file) {
    cout << "Entering assign_()\n";
    if(tok.tk == ASSIGN_tk) {
        cout << "Found ASSIGN_tk in assign_()\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in assign_()\n";
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == EQUAL_tk) {
                cout << "Found EQUAL_tk in assign_()\n";
                tok = scanner(file, lineNumber, nextChar);
                expr_(file);
                return;
            } else parse_error();
        } else parse_error();
    } else parse_error();

    return;
}

/*enum tokenID {
    ID_tk, KEY_tk, NUM_tk,
    EOF_tk, ERR_tk, START_tk, STOP_tk, REPEAT_tk, UNTIL_tk, WHOLE_tk, LABEL_tk, QUIT_tk, LISTEN_tk,
    YELL_tk, MAIN_tk, PORTAL_tk, IF_tk, THEN_tk, PICK_tk, DECLARE_tk, ASSIGN_tk, PROC_tk, EQUAL_tk,
    DUBEQUAL_tk, LESS_tk, GREAT_tk, NOTEQU_tk, COL_tk, COLEQU_tk, PLUS_tk, SUB_tk, MULT_tk, SLASH_tk,
    MOD_tk, DOT_tk, LPARA_tk, RPARA_tk, COMMA_tk, LCURLY_tk, RCURLY_tk, SEMI_tk, LBRAK_tk, RBRAK_tk
};*/

//tok = scanner(file, lineNumber, nextChar);

// <RO> -> >=  | <= |  ==  |   ... (three tokens here) |  !=
void R0_(fstream& file) {
    cout << "Entering R0_()\n";
    switch(tok.tk) {
        case GREAT_tk:
            cout << "Found GREAT_tk in R0_()\n";
            tok = scanner(file, lineNumber, nextChar);
            break;
        case LESS_tk:
            cout << "Found LESS_tk in R0()\n";
            tok = scanner(file, lineNumber, nextChar);
            break;
        case DUBEQUAL_tk:
            cout << "Found DUBEQUAL_tk in R0()\n";
            tok = scanner(file, lineNumber, nextChar);
            break;
        case NOTEQU_tk:
            cout << "Found NOTEQU_tk in R0()\n";
            tok = scanner(file, lineNumber, nextChar);
            break;
        case DOT_tk:
            cout << "Found DOT_tk in R0()\n";
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == DOT_tk) {
                cout << "Found DOT_tk in R0()\n";
                tok = scanner(file, lineNumber, nextChar);
                if(tok.tk == DOT_tk) {
                    cout << "Found DOT_tk in R0()\n";
                    tok = scanner(file, lineNumber, nextChar);
                    break;
                } else parse_error();
            } else parse_error();
        default:
            parse_error();
    }

    return;
}

// <label> -> label Identifier
void label_(fstream& file) {
    cout << "Entering label_()\n";
    if(tok.tk == LABEL_tk) {
        cout << "Found LABEL_tk in label_()\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in label_()\n";
            tok = scanner(file, lineNumber, nextChar);
            return;
        } else parse_error();
    } else parse_error();
    return;
}

// <goto> ->  portal Identifier*/
void goto_(fstream& file) {
    cout << "Entering goto_()\n";
    if(tok.tk == PORTAL_tk) {
        cout << "Found PORTAL_tk in goto_()\n";
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in goto_()\n";
            tok = scanner(file, lineNumber, nextChar);
            return;
        } else parse_error();
    } else parse_error();
    return;
}
