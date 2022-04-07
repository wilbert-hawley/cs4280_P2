#include "scanner.h"
using namespace std;

void parse_error();

void parser(fstream&);
void program_(fstream&);
void vars_(fstream&);

void expr_(fstream&);
void N_(fstream&);
void A_(fstream&);
void M_(fstream&);
void R_(fstream&);
void stats_(fstream&);
void mStat_(fstream&);
void stat_(fstream&);
void in_(fstream&);
void out_(fstream&);
void if_(fstream&);
void loop1_(fstream&);
void loop2_(fstream&);
void assign_(fstream&);
void R0_(fstream&);
void label_(fstream&);
void goto_(fstream&);
