
%{
// In this section we can add all needed headers, from Qt or another libraries.

#include <QString>
// Also, we must add the parser's header where are defined the tokens.
#include "sql2.h"

#define YY_DECL extern "C" int yylex(void)
int lineno = 1;

#define TOK(name) { return name; }
extern void yyerror(const char *s);
extern QString * save_str(char *s);
extern void start_save();
//extern void save_comparison(QString * operation);



%}

%s SQL
%%

EXEC[ \t]+SQL	{ BEGIN SQL; start_save(); }


	/* literal keyword tokens */
<SQL>(?i:ALL)		TOK(ALL)
<SQL>(?i:AND)		TOK(AND)
<SQL>(?i:AVG)		TOK(AMMSC)
<SQL>(?i:MIN)		TOK(AMMSC)
<SQL>(?i:MAX)		TOK(AMMSC)
<SQL>(?i:SUM)		TOK(AMMSC)
<SQL>(?i:COUNT)		TOK(AMMSC)
<SQL>(?i:ABS) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ACOS) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ADD_MONTHS) { yylval.strval = save_str(yytext); return ADD_MONTHS; }
<SQL>(?i:APPENDCHILDXML) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ASCII) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ASCIISTR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ASIN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ATAN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ATAN2) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:BIN_TO_NUM) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:BITAND) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CARDINALITY) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CAST) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CEIL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CHARTOROWID) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CHR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CLUSTER_ID) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CLUSTER_PROBABILITY) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CLUSTER_SET) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:COALESCE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:COLLECT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:COMPOSE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CONCAT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CONVERT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:COS) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:COSH) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CURRENT_DATE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:CURRENT_TIMESTAMP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:DBTIMEZONE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:DECODE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:DECOMPOSE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:DELETEXML) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:DEPTH) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:DUMP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:EXISTSNODE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:EXP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:EXTRACT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:EXTRACTVALUE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:FEATURE_ID) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:FEATURE_SET) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:FEATURE_VALUE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:FLOOR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:FROM_TZ) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:GREATEST) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:HEXTORAW) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:INITCAP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:INSERTCHILDXML) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:INSERTXMLBEFORE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:INSTR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LAST_DAY) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LEAST) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LENGTH) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LNNVL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LOCALTIMESTAMP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LOG) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LOWER) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LPAD) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:LTRIM) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:MOD) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:MONTHS_BETWEEN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NANVL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NEW_TIME) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NEXT_DAY) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NLS_CHARSET_DECL_LEN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NLS_CHARSET_ID) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NLS_CHARSET_NAME) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NLS_INITCAP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NLS_LOWER) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NLS_UPPER) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NLSSORT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NULLIF) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NUMTODSINTERVAL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NUMTOYMINTERVAL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NVL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:NVL2) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ORA_HASH) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:PATH) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:POWER) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:POWERMULTISET) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:POWERMULTISET_BY_CARDINALITY) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:PREDICTION) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:PREDICTION_COST) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:PREDICTION_DETAILS) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:PREDICTION_PROBABILITY) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:PREDICTION_SET) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:RAWTOHEX) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:RAWTONHEX) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:REGEXP_INSTR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:REGEXP_REPLACE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:REGEXP_SUBSTR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:REMAINDER) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:REPLACE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ROUND) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ROWIDTOCHAR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ROWIDTONCHAR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:RPAD) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:RTRIM) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SCN_TO_TIMESTAMP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SESSIONTIMEZONE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SET) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SIGN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SIN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SINH) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SOUNDEX) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SQRT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SUBSTR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SYS_DBURIGEN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SYS_EXTRACT_UTC) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SYS_XMLAGG) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SYS_XMLGEN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SYSDATE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:SYSTIMESTAMP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TAN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TANH) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TIMESTAMP_TO_SCN) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_BINARY_DOUBLE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_BINARY_FLOAT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_CHAR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_CLOB) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_DATE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_DSINTERVAL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_LOB) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_MULTI_BYTE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_NCHAR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_NCLOB) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_NUMBER) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_SINGLE_BYTE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_TIMESTAMP) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_TIMESTAMP_TZ) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TO_YMINTERVAL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TRANSLATE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TREAT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TRIM) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TRUNC) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:TZ_OFFSET) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:UNISTR) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:UPDATEXML) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:UPPER) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:VSIZE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:WIDTH_BUCKET) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLAGG) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLCDATA) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLCOLATTVAL) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLCOMMENT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLCONCAT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLFOREST) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLPARSE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLPI) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLQUERY) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLROOT) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLSEQUENCE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLSERIALIZE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLTABLE) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:XMLTRANSFORM) { yylval.strval = save_str(yytext); return AMMSCF; }
<SQL>(?i:ANY)		TOK(ANY)
<SQL>(?i:AS)			TOK(AS)
<SQL>(?i:ASC)		TOK(ASC)
<SQL>(?i:AUTHORIZATION)	TOK(AUTHORIZATION)
<SQL>(?i:BETWEEN)		TOK(BETWEEN)
<SQL>(?i:BY)			TOK(BY)
<SQL>(?i:CHAR(ACTER)?)	TOK(CHARACTER)
<SQL>(?i:CHECK)		TOK(CHECK)
<SQL>(?i:CLOSE)		TOK(CLOSE)
<SQL>(?i:COMMIT)		TOK(COMMIT)
<SQL>(?i:CONTINUE)		TOK(CONTINUE)
<SQL>(?i:CREATE)		TOK(CREATE)
<SQL>(?i:CURRENT)		TOK(CURRENT)
<SQL>(?i:CURSOR)		TOK(CURSOR)
<SQL>(?i:DECIMAL)		TOK(DECIMAL)
<SQL>(?i:DECLARE)		TOK(DECLARE)
<SQL>(?i:DEFAULT)		TOK(DEFAULT)
<SQL>(?i:DELETE)		TOK(DELETE)
<SQL>(?i:DESC)		TOK(DESC)
<SQL>(?i:DISTINCT)		TOK(DISTINCT)
<SQL>(?i:DOUBLE)		TOK(DOUBLE)
<SQL>(?i:ESCAPE)		TOK(ESCAPE)
<SQL>(?i:EXISTS)		TOK(EXISTS)
<SQL>(?i:FETCH)		TOK(FETCH)
<SQL>(?i:FLOAT)		TOK(FLOAT)
<SQL>(?i:FOR)		TOK(FOR)
<SQL>(?i:FOREIGN)		TOK(FOREIGN)
<SQL>(?i:FOUND)		TOK(FOUND)
<SQL>(?i:FROM)		{  return  FROM;  }
<SQL>(?i:GO[ \t]*TO)		TOK(GOTO)
<SQL>(?i:GRANT)		TOK(GRANT)
<SQL>(?i:GROUP)		TOK(GROUP)
<SQL>(?i:HAVING)		TOK(HAVING)
<SQL>(?i:IN)			TOK(IN)
<SQL>(?i:INDICATOR)		TOK(INDICATOR)
<SQL>(?i:INSERT)		TOK(INSERT)
<SQL>(?i:INT(EGER)?)		TOK(INTEGER)
<SQL>(?i:INTO)		TOK(INTO)
<SQL>(?i:IS)			TOK(IS)
<SQL>(?i:KEY)		TOK(KEY)
<SQL>(?i:LANGUAGE)		TOK(LANGUAGE)
<SQL>(?i:LIKE)		TOK(LIKE)
<SQL>(?i:NOT)		TOK(NOT)
<SQL>(?i:NULL)		TOK(NULLX)
<SQL>(?i:NUMERIC)		TOK(NUMERIC)
<SQL>(?i:OF)			TOK(OF)
<SQL>(?i:ON)			TOK(ON)
<SQL>(?i:OPEN)		TOK(OPEN)
<SQL>(?i:OPTION)		TOK(OPTION)
<SQL>(?i:OR)			TOK(OR)
<SQL>(?i:ORDER)		TOK(ORDER)
<SQL>(?i:PRECISION)		TOK(PRECISION)
<SQL>(?i:PRIMARY)		TOK(PRIMARY)
<SQL>(?i:PRIVILEGES)		TOK(PRIVILEGES)
<SQL>(?i:PROCEDURE)		TOK(PROCEDURE)
<SQL>(?i:PUBLIC)		TOK(PUBLIC)
<SQL>(?i:REAL)		TOK(REAL)
<SQL>(?i:REFERENCES)		TOK(REFERENCES)
<SQL>(?i:ROLLBACK)		TOK(ROLLBACK)
<SQL>(?i:SCHEMA)		TOK(SCHEMA)
<SQL>(?i:SELECT)	TOK(SELECT)
<SQL>(?i:SET)		TOK(SET)
<SQL>(?i:SMALLINT)		TOK(SMALLINT)
<SQL>(?i:SOME)		TOK(SOME)
<SQL>(?i:SQLCODE)		TOK(SQLCODE)
<SQL>(?i:TABLE)		TOK(TABLE)
<SQL>(?i:TO)			TOK(TO)
<SQL>(?i:UNION)		TOK(UNION)
<SQL>(?i:UNIQUE)		TOK(UNIQUE)
<SQL>(?i:UPDATE)		TOK(UPDATE)
<SQL>(?i:USER)		TOK(USER)
<SQL>(?i:VALUES)		TOK(VALUES)
<SQL>(?i:VIEW)		TOK(VIEW)
<SQL>(?i:WHENEVER)		TOK(WHENEVER)
<SQL>(?i:WHERE)		TOK(WHERE)
<SQL>(?i:WITH)		TOK(WITH)
<SQL>(?i:WORK)		TOK(WORK)

	/* punctuation */

<SQL>"="	|
<SQL>"<>" 	|
<SQL>"<"	|
<SQL>">"	|
<SQL>"<="	|
<SQL>">="	    {  yylval.strval = save_str(yytext); return COMPARISON;}


<SQL>"=>" { yylval.strval =  save_str(yytext);  return ARG_REF;}




<SQL>[-+*/(),.;]	{ yylval.strval =  save_str(yytext);    return yytext[0]; }

<SQL>"\|\|"   {  yylval.strval =  save_str(yytext);  return CONCATE;}


	/* names */
<SQL>[A-Za-z][A-Za-z0-9_]*	{ yylval.strval = save_str(yytext); return NAME; }

	/* parameters */
<SQL>":"[A-Za-z][A-Za-z0-9_]*	{
yylval.strval = save_str(yytext);
			return PARAMETER;
		}

	/* numbers */





<SQL>-?[0-9]+ {
    // yyval is a variable created by Flex, which we can return the parsed
    // value.
    // yytext is another variable created by Flex that contains the text to
    // parse.
    //yylval.QVariant_t = new QVariant();
  //  *yylval.QVariant_t = QString(yytext).toInt();
 yylval.strval =  save_str(yytext);
  return INTNUM;
}




<SQL>[0-9]+[eE][+-]?[0-9]+	|
<SQL>[0-9]+"."[0-9]*[eE][+-]?[0-9]+ |
<SQL>"."[0-9]*[eE][+-]?[0-9]+	TOK(APPROXNUM)

	/* strings */

<SQL>'[^'\n]*'	{yylval.strval = save_str(yytext);

                        return STRING;

	}



		
<SQL>'[^'\n]*$	{	yyerror("Unterminated string"); }

<SQL>\n		{ lineno++; }
\n		{ lineno++; ECHO; }

<SQL>[ \t\r]+	;

<SQL>"--".*	;	/* comment */

<SQL>"/*"			{   char c, c1;

loop:
    while ((c = yyinput()) != '*' && c != 0)
        putchar(c);

    if ((c1 = yyinput()) != '/' && c != 0)
    {
        unput(c1);
        goto loop;
    }

    if (c != 0)
        putchar(c1); }

.		ECHO;	/* random non-SQL text */
%%




/* leave SQL lexing mode */
void un_sql()
{
	BEGIN INITIAL;
} /* un_sql */
