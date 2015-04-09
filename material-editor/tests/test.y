%defines
%define api.value.type union
%token TEST
%type <int> fake
%%
fake : TEST { yylval.fake = 1; }
%%
