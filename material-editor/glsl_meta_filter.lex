%{

#include <stdio.h>
#include <string.h>

char *metalval;

%}

%x COMMENT
%x META
%x META_COMMENT

%%

<INITIAL>@ BEGIN(META);
<META>@ BEGIN(INITIAL);
<META>"/*" BEGIN(META_COMMENT);
<META_COMMENT>"*/" BEGIN(META);
<META_COMMENT>[^*\n]+ { }
<META>[^@\n]+ { }

<INITIAL>"/*" { metalval = "/*"; BEGIN(COMMENT); return 1; }
<COMMENT>"*/"  { metalval = "*/"; BEGIN(INITIAL); return 1; }
<COMMENT>[^*\n]+ { metalval = yytext; return 1;}

[^@\n] {metalval = yytext; return 1;}

\n {metalval = "\n"; return 1;}

%%

int metawrap()
{
	return 1;
}

void metaerror(const char *s)
{
	fprintf(stderr, "error: %s\n", s);
}
