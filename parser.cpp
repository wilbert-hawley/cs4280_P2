#include "parser.h"
using namespace std;

string tokenNames[] ={ "Identifier", "Keyword", "Number", "EOF", "Error", "Start", "Stop",
                       "Repeat", "Until", "Whole", "Label", "Quit", "Listen", "Yell", "Main", "Portal",
                       "If", "Then", "Pick", "Declare", "Assign", "Proc", "Equal Sign", "Double Equal",
                       "Less Than", "Greater Than", "Not Equal To", "Colon", "Colon Equals", "Plus Sign",
                       "Minus Sign", "Multiplication Sign", "Slash", "Modulus", "Period", "Left Parenthesis",
                       "Right Parenthesis", "Comma", "Left Curly Brace", "Right Curly Brace", "Semicolon",
                       "Left Bracket", "Right Bracket" };

token tok;
char nextChar;
int lineNumber = 0;

void parse_error() {
    cout << "Error when processing " << "TokenID: " << tokenNames[tok.tk] << "     TokenInstance: "
         << tok.instance << "     LineNumber: " << tok.line << endl;
    exit(1);
}

Node* parser(fstream& file) {
    Node* root = new Node;

    file.get(nextChar);
    tok = scanner(file, lineNumber, nextChar);
    root = program_(file);
    if(tok.tk == EOF_tk)
        cout << "End of file reached\n";
    else
        parse_error();
    return root;
}



//<program> -> <vars> main <block>
Node* program_(fstream &file){
    cout << "Entering program_()\n";
    Node* newNode = getNode("<program>");
    newNode->child1 = vars_(file);
	if(tok.tk == MAIN_tk) {
	    cout << "Found MAIN_tk\n";
	    newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        newNode->child2 = block_(file);
        return newNode;
	} else parse_error();
	cout << "Made it back to program_()\n";
	return NULL;

}

// <block> -> { <vars> <stats> }
Node* block_(fstream& file) {
    cout << "Entering block_()\n";
    if(tok.tk == LCURLY_tk) {
        cout << "Found LCURLY_tk in block_()\n";
        Node* newNode = getNode("<block>");
        tok = scanner(file, lineNumber, nextChar);
        newNode->child1 = vars_(file);
        newNode->child2 = stats_(file);
        if(tok.tk == RCURLY_tk) {
            cout << "Found RCURLY_tk in block_()\n";
            tok = scanner(file, lineNumber, nextChar);
            return newNode;
        } else parse_error();
    } else parse_error();
    return getNode("ERROR: block_()");
}

//<vars> -> empty | declare Identifier :=  whole ; <vars>
Node* vars_(fstream& file) {
    cout << "Entering vars()\n";
    Node* newNode = getNode("<vars>");
    if(tok.tk == DECLARE_tk) {
        cout << "Found declare in vars()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found Identifier in vars()\n";
            newNode->tok2 = tok;
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == COLEQU_tk) {
                cout << "Found colon equal in vars()\n";
                newNode->tok3 = tok;
                tok = scanner(file, lineNumber, nextChar);
                if(tok.tk == WHOLE_tk) {
                    cout << "Found whole in vars()\n";
                    newNode->tok4 = tok;
                    tok = scanner(file, lineNumber, nextChar);
                    if(tok.tk == SEMI_tk) {
                        cout << "Found semicolon in vars()\n";
                        newNode->tok5 = tok;
                        tok = scanner(file, lineNumber, nextChar);
                        newNode->child1 = vars_(file);
                        return newNode;
                    } else parse_error();
                } else parse_error();
            } else parse_error();
        } else parse_error();
    }
    else {
        cout << "Returning empty <vars>\n";
        return newNode;
    }
    return getNode("ERROR vars_");
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
Node* expr_(fstream& file) {
    Node* newNode = getNode("<expr>");
    cout << "Entering expr_()\n";
    newNode->child1 = N_(file);

    if(tok.tk == SUB_tk){
        cout << "Found minus in expr_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        newNode->child2 = expr_(file);
    }
    return newNode;
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
Node* N_(fstream& file) {
    cout << "Entering N_()\n";
    Node* newNode = getNode("<N>");
    newNode->child1 = A_(file);
    if(tok.tk == SLASH_tk) {
        cout << "Found SLAHS_tk in N()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        newNode->child1 = N_(file);
        return newNode;
    }
    else if (tok.tk == PLUS_tk) {
        cout << "Found PLUS_tk in N()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        newNode->child1 = N_(file);
        return newNode;
    } else
        return newNode;
}

// <A> -> <M> * <A> | <M>
Node* A_(fstream& file) {
    cout << "Entering A_()\n";
    Node* newNode = getNode("<A>");
    newNode->child1 = M_(file);
    if(tok.tk == MULT_tk) {
        cout << "Found MULT_tk in A_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        newNode->child2 = A_(file);
    }
    return newNode;
}

// <M> -> % <M> |  <R>
Node* M_(fstream& file) {
    cout << "Entering M_()\n";
    Node* newNode = getNode("<M>");
    if(tok.tk == MOD_tk) {
        cout << "Found MOD_tk in M_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        newNode->child1 = M_(file);
        return newNode;
    } else {
        newNode->child1 = R_(file);
        return newNode;
    }
}

// <R> -> ( <expr> ) | Identifier | Integer
Node* R_(fstream& file) {
    cout << "Entering R_()\n";
    Node* newNode = getNode("<R>");
    if(tok.tk == LPARA_tk) {
        cout << "Found LPARA_tk in R_()\n";
        tok = scanner(file, lineNumber, nextChar);
        newNode->child1 = expr_(file);
        if(tok.tk == RPARA_tk) {
            cout << "Found RPARA_tk in R_()\n";
            tok = scanner(file, lineNumber, nextChar);
            return NULL;
        } else parse_error();
    } else if(tok.tk == ID_tk) {
        cout << "Found ID_tk in R_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        return newNode;
    } else if(tok.tk == NUM_tk) {
        cout << "Found NUM_tk in R_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        return newNode;
    } else parse_error();

    return getNode("ERROR R_()");
}

// <stats> -> <stat>  <mStat>
Node* stats_(fstream& file) {
    cout << "Entering stats_()\n";
    Node* newNode = getNode("<stats>");
    newNode->child1 = stat_(file);
    newNode->child2 = mStat_(file);
    return newNode;
}

// <mStat> -> empty |  <stat>  <mStat>
Node* mStat_(fstream& file) {
    cout << "Entering mStat()\n";
    Node* newNode = getNode("<mStat>");
    switch(tok.tk) {
        case LISTEN_tk: // in
            break;
        case YELL_tk: // out
            break;
        case LCURLY_tk: // block
            break;
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
            return newNode;
    }
    newNode->child1 = stat_(file);
    newNode->child2 = mStat_(file);
    return newNode;
}

// <stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop1> ; | <loop2> ; | <assign> ; | <goto> ; | <label> ;
Node* stat_(fstream& file) {
    cout << "Entering stat_()\n";
    Node* newNode = getNode("<stat>");
    switch(tok.tk) {
        case LISTEN_tk: // in
            newNode->child1 = in_(file);
            break;
        case YELL_tk: // out
            newNode->child1 = out_(file);
            break;
        case LCURLY_tk: // block
            newNode->child1 = block_(file);
            return NULL;
        case IF_tk: // if
            newNode->child1 = if_(file);
            break;
        case REPEAT_tk:
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == LBRAK_tk) {
                newNode->child1 = loop1_(file);
            }
            else
                newNode->child1 = loop2_(file);
            break;
        case ASSIGN_tk:
            newNode->child1 = assign_(file);
            break;
        case PORTAL_tk:
            newNode->child1 = goto_(file);
            break;
        case LABEL_tk:
            newNode->child1 = label_(file);
            break;
        default:
            cout << "Messed up in stat_()\n";
            parse_error();
    }

    if (tok.tk == SEMI_tk) {
        cout << "Found SEMI_tk in stat_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        return newNode;
    } else parse_error();

    return getNode("ERROR stat_()\n");
}

// <in> -> listen  Identifier
Node* in_(fstream& file) {
    cout << "Entering in_()\n";
    Node* newNode = getNode("<in>");
    if(tok.tk == LISTEN_tk) {
        cout << "Found LISTEN_tk in in_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in in_()\n";
            newNode->tok2 = tok;
            tok = scanner(file, lineNumber, nextChar);
            return newNode;
        } else parse_error();
    } else parse_error();
    return getNode("ERROR in_()\n");
}

// <out> -> yell <expr>
Node* out_(fstream& file) {
    cout << "Entering out_()\n";
    Node* newNode = getNode("<out>");
    if(tok.tk == YELL_tk) {
        cout << "Found YELL_tk in out_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        newNode->child1 = expr_(file);
        return newNode;
    } else parse_error();
    return getNode("ERROR out_()\n");
}

// <if> -> if [ <expr> <RO> <expr> ] then <stat>
Node* if_(fstream& file) {
    cout << "Entering if_()\n";
    Node* newNode = getNode("<if>");
    if(tok.tk == IF_tk) {
        cout << "Found IN_tk in if_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == LBRAK_tk) {
            cout << "Found LBRAK_tk in if_()\n";
            tok = scanner(file, lineNumber, nextChar);
            newNode->child1 = expr_(file);
            newNode->child2 = R0_(file);
            newNode->child3 = expr_(file);
            if(tok.tk == RBRAK_tk) {
                cout << "Found RBRAK_tk in if_()\n";
                tok = scanner(file, lineNumber, nextChar);
                if(tok.tk == THEN_tk) {
                    cout << "Found THEN_tk in if_()\n";
                    newNode->tok2 = tok;
                    tok = scanner(file, lineNumber, nextChar);
                    newNode->child4 = stat_(file);
                    return newNode;
                } else parse_error();
            } else parse_error();
        } else parse_error();
    } else parse_error();
    return getNode("ERROR if_()\n");
}

// <loop1> -> repeat  [ <expr> <RO> <expr> ]  <stat>
Node* loop1_(fstream& file) {
    cout << "Entering loop1_()\n";
    Node* newNode = getNode("<loop1>");
    newNode->tok1.tk = REPEAT_tk;
    newNode->tok1.instance = "repeat";
    newNode->tok1.line = lineNumber;
    cout << "Found REAPEAT_tk in loop1_()\n";
    if(tok.tk == LBRAK_tk) {
        cout << "Found LBRAK_tk in loop1_()\n";
        tok = scanner(file, lineNumber, nextChar);
        newNode->child1 = expr_(file);
        newNode->child2 = R0_(file);
        newNode->child3 = expr_(file);
        if(tok.tk == RBRAK_tk) {
            cout << "Found RBRAK_tk in loop1_()\n";
            tok = scanner(file, lineNumber, nextChar);
            newNode->child4 = stat_(file);
            return newNode;
        } else parse_error();
    } else parse_error();
    return getNode("ERROR loop1_()");
}

// <loop2> -> repeat <stat> until [ <expr> <RO> <expr> ]
Node* loop2_(fstream& file) {
    cout << "Entering loop2_()\n";
    cout << "Found REAPEAT_tk in loop2_()\n";
    Node* newNode = getNode("<loop2>");
    newNode->tok1.tk = REPEAT_tk;
    newNode->tok1.instance = "repeat";
    newNode->tok1.line = lineNumber;
    newNode->child1 = stat_(file);
    if(tok.tk == UNTIL_tk) {
        cout << "Found UNTIL_tk in loop2_()\n";
        newNode->tok2 = tok;
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == LBRAK_tk) {
            cout << "Found LBRAK_tk in loop2_()\n";
            tok = scanner(file, lineNumber, nextChar);
            newNode->child2 = expr_(file);
            newNode->child3 = R0_(file);
            newNode->child4 = expr_(file);
            if(tok.tk == RBRAK_tk) {
                cout << "Found RBRAK_tk in loop2()\n";
                tok = scanner(file, lineNumber, nextChar);
                return newNode;
            } else parse_error();
        } else parse_error();
    } else parse_error();
    return getNode("ERROR loop2_()\n");
}

// <assign> -> assign Identifier  = <expr>
Node* assign_(fstream& file) {
    cout << "Entering assign_()\n";
    Node* newNode = getNode("<assign>");
    if(tok.tk == ASSIGN_tk) {
        cout << "Found ASSIGN_tk in assign_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in assign_()\n";
            newNode->tok2 = tok;
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == EQUAL_tk) {
                cout << "Found EQUAL_tk in assign_()\n";
                newNode->tok3 = tok;
                tok = scanner(file, lineNumber, nextChar);
                newNode->child1 = expr_(file);
                return newNode;
            } else parse_error();
        } else parse_error();
    } else parse_error();

    return getNode("ERROR assign_()\n");
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
Node* R0_(fstream& file) {
    cout << "Entering R0_()\n";
    Node* newNode = getNode("<R0>");
    switch(tok.tk) {
        case GREAT_tk:
            cout << "Found GREAT_tk in R0_()\n";
            newNode->tok1 = tok;
            tok = scanner(file, lineNumber, nextChar);
            break;
        case LESS_tk:
            cout << "Found LESS_tk in R0()\n";
            newNode->tok1 = tok;
            tok = scanner(file, lineNumber, nextChar);
            break;
        case DUBEQUAL_tk:
            cout << "Found DUBEQUAL_tk in R0()\n";
            newNode->tok1 = tok;
            tok = scanner(file, lineNumber, nextChar);
            break;
        case NOTEQU_tk:
            cout << "Found NOTEQU_tk in R0()\n";
            newNode->tok1 = tok;
            tok = scanner(file, lineNumber, nextChar);
            break;
        case DOT_tk:
            cout << "Found DOT_tk in R0()\n";
            newNode->tok1 = tok;
            tok = scanner(file, lineNumber, nextChar);
            if(tok.tk == DOT_tk) {
                cout << "Found DOT_tk in R0()\n";
                newNode->tok2 = tok;
                tok = scanner(file, lineNumber, nextChar);
                if(tok.tk == DOT_tk) {
                    cout << "Found DOT_tk in R0()\n";
                    newNode->tok3 = tok;
                    tok = scanner(file, lineNumber, nextChar);
                    break;
                } else parse_error();
            } else parse_error();
        default:
            parse_error();
    }

    return newNode;
}

// <label> -> label Identifier
Node* label_(fstream& file) {
    cout << "Entering label_()\n";
    Node* newNode = getNode("<label>");
    if(tok.tk == LABEL_tk) {
        cout << "Found LABEL_tk in label_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in label_()\n";
            newNode->tok2 = tok;
            tok = scanner(file, lineNumber, nextChar);
            return newNode;
        } else parse_error();
    } else parse_error();
    return getNode("ERROR label_()\n");
}

// <goto> ->  portal Identifier*/
Node* goto_(fstream& file) {
    cout << "Entering goto_()\n";
    Node* newNode = getNode("<goto>");
    if(tok.tk == PORTAL_tk) {
        cout << "Found PORTAL_tk in goto_()\n";
        newNode->tok1 = tok;
        tok = scanner(file, lineNumber, nextChar);
        if(tok.tk == ID_tk) {
            cout << "Found ID_tk in goto_()\n";
            newNode->tok2 = tok;
            tok = scanner(file, lineNumber, nextChar);
            return newNode;
        } else parse_error();
    } else parse_error();
    return getNode("ERROR goto_()\n");
}
