#include <QBuffer>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include "cscene.h"
//#include "ctableitem.h"

#ifdef __cplusplus
extern "C"{
#endif

#include "scn2.h"
#include "sql2.h"

extern void yyerror(const  char *  errstr);

extern char * errorstr;


/*
 *	Text handling routines for simple embedded SQL
 */



char save_buf[2000];	/* buffer for SQL command */
char *savebp;		/* current buffer pointer */
char * nameref[200];
int namecnt;
char * tablenames[200];
char * tbl_aliases[200];

char * sel_tables[200];
char * sel_columns[200];


char * wh_columns_l[200];
char * wh_columns_r[200];

char * wh_tables_l[200];
char * wh_tables_r[200];

int wh_optypes[200];

int current_optype;


int tablenamecnt;
int sel_col_count;
int wh_col_count;
int is_sel;
int is_where;
int saved_columns;

#define NPARAM	20	/* max params per function */
char *varnames[NPARAM];	/* parameter names */

/* start an embedded command after EXEC SQL */

void save_table(char * table,char * alias)
{
 tablenames[tablenamecnt] =  table;
 tbl_aliases[tablenamecnt] = alias;
 tablenamecnt++;
}



void save_wh_cols_r(char * table,char * column)

{


     wh_tables_r[wh_col_count] = table;
     wh_columns_r[wh_col_count] = column;
wh_optypes[wh_col_count] =  current_optype;
    wh_col_count++;





}


void save_wh_cols_l(char * table,char * column)

{

    if(is_where)
    {
        if(!saved_columns)
       {
        wh_tables_l[wh_col_count] = table;
        wh_columns_l[wh_col_count] = column;
       }
        else
        {
           if(saved_columns == 1)
            save_wh_cols_r( table, column);
        }
        saved_columns++;

    }




}



void save_sel_cols(char * table,char * column)
{
if( is_sel){
    sel_tables[sel_col_count] = table;
    sel_columns[sel_col_count]= column;

 sel_col_count++;
}
else save_wh_cols_l(table,column);

}



void reset_saved_columns()
{

saved_columns = 0;

}


void save_comparison(char * operation)
{

current_optype = 6;

if(strcmp(operation,"="))
{
    current_optype = 0;
return;
}
if(strcmp(operation,"<>"))
 {
    current_optype = 1;
return;
}
if(strcmp(operation,"<"))
 {
    current_optype = 2;
return;
}
if(strcmp(operation,">"))
 {
    current_optype = 3;
return;
}
if(strcmp(operation,"<="))
 {
    current_optype = 4;
return;
}
if(strcmp(operation,">="))

    current_optype = 5;





}






void start_save(void)
{

    savebp = save_buf;
    namecnt=0;
    tablenamecnt=0;
    sel_col_count = 0;
    is_sel = 0;
    wh_col_count=0;
} /* start_save */

/* save a SQL token */

void enable_where(int where)
{
if(where)
     saved_columns =0;
 is_where = where;

}




void enable_sel(int sel)
{

 is_sel = sel;

}

char * save_str(char *s)
{
    char * retch;

retch = savebp;
    strcpy(savebp, s);
    savebp += strlen(s)+1;
return retch;
} /* save_str */

/* save a parameter reference */
void save_param(char *n)
{
    int i;
    char pbuf[10];

    /* look up the variable name in the table */

    for(i = 1; i < NPARAM; i++) {
        if(!varnames[i]) {

            /* not there, enter it */
            varnames[i] = strdup(n);
            break;
        }

        if(!strcmp(varnames[i],n))
            break;	/* already present */
    }

    if(i >= NPARAM) {
        yyerror("Too many parameter references");
        exit(1);
    }

    /* save #n referece by variable number */
    sprintf(pbuf, " #%d", i);
    save_str(pbuf);

} /* save_param */

/* end of SQL command, now write it out */





#ifdef __cplusplus
}
#endif



extern "C" int  yyparse();

QStringList load_list_from_arr(char * arr[],int count )
{
    QStringList list;
    for(int i=0;i<count;i++)
    {
        list.append(QString(arr[i]).toUpper());

    }
return list;
}

extern int yydebug;





int do_parse(QString inputstr, cscene * scene,   QList<ctable * > * tables )
{

  //  yyFlexLexer fllex;

   // QByteArray * myarr = new QByteArray(inputstr.toUtf8());

  //  std::istringstream  mystr(inputstr.toStdString());
//std::istream * mistr = dynamic_cast<std::istream *>(mystr);

      //  QBuffer mybuf(myarr);

 // YY_BUFFER_STATE bufferState =    fllex.yy_create_buffer(&mystr, inputstr.toUtf8().size() );

   //  scene.addtable(alltables[index.row()]);
yydebug = 1;
 YY_BUFFER_STATE bufferState = yy_scan_string(inputstr.toUtf8().data());
int prez = yyparse();
   yy_delete_buffer(bufferState);

 if(prez)
   return prez;
 QList<int> tableindexes;
  QList< crtableitem * > tlist;
tlist.clear();

 int tableind;
 if(tablenamecnt>0)
 for(int i=0;i<tablenamecnt;i++)
 {
tableind = ctable::findtablebyname(QString(tablenames[i]).toUpper(),tables);
 if(tableind<0)
     break;
 tableindexes.append(tableind);
tlist.append( scene->addtable(tables->at(tableind)  ));
  }
 if(tableind<0)
     return 2;

 QStringList tablesl = load_list_from_arr(tablenames,tablenamecnt);
QStringList tab_aliases = load_list_from_arr(tbl_aliases,tablenamecnt);


 if(wh_col_count > 0)
   {
     QStringList left_cols_tables
             = load_list_from_arr(wh_tables_l,wh_col_count);
     QStringList left_cols
             = load_list_from_arr(wh_columns_l,wh_col_count);
     QStringList right_cols_tables
             = load_list_from_arr(wh_tables_r,wh_col_count);
     QStringList right_cols
             = load_list_from_arr(wh_columns_r,wh_col_count);


     for(int i=0;i<wh_col_count;i++ )
 {
         if(wh_optypes[i] == 1)
     {
  ctable * left_ctable = 0;
  int left_cfield;
  ctable * right_ctable = 0;
  int right_cfield;
  int left_item_ind;
  int right_item_ind;


      left_item_ind = tablesl.indexOf(left_cols_tables[i]);

             if( left_item_ind >= 0 )

                left_ctable  = tables->at(tableindexes[left_item_ind]);
             else
             {
                left_item_ind = tab_aliases.indexOf(left_cols_tables[i]);
               if(left_item_ind >= 0)
                  left_ctable  = tables->at(tableindexes[left_item_ind]);
             }
   if(left_ctable)
         left_cfield = left_ctable->fields.indexOf(left_cols.at(i));

   right_item_ind = tablesl.indexOf(right_cols_tables[i]);

                if( right_item_ind >= 0 )

                   right_ctable  = tables->at(tableindexes[right_item_ind]);
                else
                {
                 right_item_ind = tab_aliases.indexOf(right_cols_tables[i]);
                  if(right_item_ind >= 0)
                     right_ctable  = tables->at(tableindexes[right_item_ind]);
                }
      if(right_ctable)
            right_cfield = right_ctable->fields.indexOf(right_cols.at(i));

      if(right_ctable != 0 && left_ctable != 0 && right_cfield >= 0 && left_cfield >=0  )
       {

         // get_foreign_by_prim_table
       int leftfkey = left_ctable->get_foreign_by_prim_table(right_ctable);
          if(leftfkey >=0 && leftfkey == left_cfield )
                 scene->add_link(tlist.at(left_item_ind),
                                   tlist.at(right_item_ind),left_cfield,right_cfield,TTYPE_FOREIGN_LINK,true);
      else{
           int rightfkey =   right_ctable->get_foreign_by_prim_table(left_ctable);
           if(rightfkey >=0 && rightfkey == right_cfield )
                  scene->add_link(tlist.at(right_item_ind),
                                    tlist.at(left_item_ind),right_cfield,left_cfield,TTYPE_FOREIGN_LINK,true);


          }



      }





     }


 }









 }




 for(int i=0;i<sel_col_count;i++ )
{

     ctable * left_ctable = 0;
     int left_cfield;

       int left_item_ind;

     left_item_ind = tablesl.indexOf(QString(sel_tables[i]));

            if( left_item_ind >= 0 )

               left_ctable  = tables->at(tableindexes[left_item_ind]);
            else
            {
               left_item_ind = tab_aliases.indexOf(QString(sel_tables[i]).toUpper());
              if(left_item_ind >= 0)
                 left_ctable  = tables->at(tableindexes[left_item_ind]);
            }
  if(left_ctable)

        left_cfield = left_ctable->fields.indexOf(QString(sel_columns[i]).toUpper());
if(left_cfield >= 0 )
  tlist.at(left_item_ind)->set_column_type(left_cfield+1,CTYPE_OUTPUTFIELD);

 }



return 0;
}

