#include <QBuffer>
#include <sstream>
#include <stdio.h>
#include <string.h>

#include "cscene.h"
//#include "ctableitem.h"


#include "scn2.h"
#include "sql2.h"

extern void yyerror(const  char *  errstr);

extern char * errorstr;


/*
 *	Text handling routines for simple embedded SQL
 */



//char save_buf[2000];	/* buffer for SQL command */
//char *savebp;		/* current buffer pointer */
//char * nameref[200];
//int namecnt;
QStringList tablenames;
QStringList tbl_aliases;

QStringList sel_tables;
QStringList sel_columns;
QStringList wh_expressions;
/*
QStringList wh_columns_l;
QStringList wh_columns_r;

QStringList wh_tables_l;
QStringList wh_tables_r;
*/

QList<QStringList> wh_tables;
QList<QStringList> wh_columns;

QStringList current_wh_tables;
QStringList current_wh_columns;


QList<int> wh_optypes;

int current_optype;


int tablenamecnt;
int sel_col_count;
//int wh_col_count;
int is_sel;
int is_where;


#define NPARAM	20	/* max params per function */
char *varnames[NPARAM];	/* parameter names */

/* start an embedded command after EXEC SQL */

void save_table(QString * table,QString * alias)
{
 tablenames.append(table->toUpper());  ;
 tbl_aliases.append(alias->toUpper());

}


/*
void save_wh_cols_r(QString * table,QString * column)

{


     wh_tables_r.append( table->toUpper());
     wh_columns_r.append( column->toUpper());
wh_optypes.append( current_optype);






}
*/


void save_wh_cols(QString * table,QString * column)

{


  if(!table)
      table = new QString();
  if(!column)
      column = new QString();

    if(is_where)
    {
     current_wh_tables.append(table->toUpper());
     current_wh_columns.append(column->toUpper());


    }




}



void save_sel_cols(QString * table,QString * column)
{
if( is_sel){
    sel_tables.append( table->toUpper());
    sel_columns.append( column->toUpper());
}

else save_wh_cols( table, column);

}



void reset_saved_columns()
{
wh_tables.append(current_wh_tables);
wh_columns.append(current_wh_columns);
current_wh_tables.clear();
current_wh_columns.clear();
}


void save_comparison(QString * operation)
{

current_optype = 6;

if( * operation ==  "=")
{
    current_optype = 0;
return;
}
if( * operation ==  "<>")
 {
    current_optype = 1;
return;
}
if( * operation ==  "<")
 {
    current_optype = 2;
return;
}
if( * operation ==  ">")
 {
    current_optype = 3;
return;
}
if( * operation ==  "<=")
 {
    current_optype = 4;
return;
}
if( * operation ==  ">=")

    current_optype = 5;





}






void start_save(void)
{


    is_sel = 0;
    wh_tables.clear();
    wh_columns.clear();
    wh_expressions.clear();

} /* start_save */

/* save a SQL token */

void enable_where(int where)
{
if(where)
 {
    current_wh_tables.clear();
    current_wh_columns.clear();

}

 is_where = where;

}




void enable_sel(int sel)
{

 is_sel = sel;

}

QString * save_str(char *s)
{
    QString * retstr = new QString(s);
    return retstr;
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








extern  int  yyparse();

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
/*

void  findcrtables(  QList< crtableitem * > crtlist,QList<int> * tabindexes,QList<int> * colindexes )
 {


 int ctableind = tbl_aliases.indexOf(tablename);
 if(ctableind >=0)
   {
  QString rtablename = tablenames[ctableind];
 int rtableind = ctable::findtablebyname(rtablename,tables);
  if(rtableind < 0)
      return 0;
 return new  crtableitem(tables->at(rtableind),tbl_aliases[ctableind]);

 }




 }
*/

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
 if(tablenames.count()>0)
 for(int i=0;i<tablenames.count();i++)
 {
tableind = ctable::findtablebyname(QString(tablenames[i]).toUpper(),tables);
 if(tableind<0)
     break;
 tableindexes.append(tableind);
tlist.append( scene->addtable(tables->at(tableind),tbl_aliases[i]));
  }
 if(tableind<0)
     return 2;




 if(wh_tables.count() > 0)
   {



     for(int i=0;i<wh_tables.count();i++ )
 {
     QString expression =  wh_expressions[i];

         if( wh_tables[i].count() < 3 )
     {
            QString secondtable;
            QString secondcol;
       QString firsttable = wh_tables[i][0];
    QString firstcol = wh_columns[i][0];




      if( wh_tables[i].count() == 2 )
     {


          secondtable = wh_tables[i][1];
        secondcol = wh_columns[i][1];


  ctable * left_ctable = 0;
  int left_cfield;
  ctable * right_ctable = 0;
  int right_cfield;
  int left_item_ind;
  int right_item_ind;
/*

      left_item_ind = tablenames.indexOf(wh_tables_l[i]);

             if( left_item_ind >= 0 )

                left_ctable  = tables->at(tableindexes[left_item_ind]);
             else
             {
                left_item_ind = tbl_aliases.indexOf(wh_tables_l[i]);
               if(left_item_ind >= 0)
                  left_ctable  = tables->at(tableindexes[left_item_ind]);
             }
   if(left_ctable)
         left_cfield = left_ctable->fields.indexOf(wh_columns_l[i]);

   right_item_ind = tablenames.indexOf(wh_tables_r[i]);

                if( right_item_ind >= 0 )

                   right_ctable  = tables->at(tableindexes[right_item_ind]);
                else
                {
                 right_item_ind = tbl_aliases.indexOf(wh_tables_r[i]);
                  if(right_item_ind >= 0)
                     right_ctable  = tables->at(tableindexes[right_item_ind]);
                }
      if(right_ctable)
            right_cfield = right_ctable->fields.indexOf(wh_columns_r[i]);

      */


      if(right_ctable != 0 && left_ctable != 0 && right_cfield >= 0 && left_cfield >=0  )
       {

         // get_foreign_by_prim_table
       int leftfkey = left_ctable->get_foreign_by_prim_table(right_ctable);
          if(leftfkey >=0 && leftfkey == left_cfield )
                 scene->add_link(tlist.at(left_item_ind),
                                   tlist.at(right_item_ind),left_cfield+1,right_cfield+1,TTYPE_FOREIGN_LINK,true);
      else{
           int rightfkey =   right_ctable->get_foreign_by_prim_table(left_ctable);
           if(rightfkey >=0 && rightfkey == right_cfield )
                  scene->add_link(tlist.at(right_item_ind),
                                    tlist.at(left_item_ind),right_cfield+1,left_cfield+1,TTYPE_FOREIGN_LINK,true);


          }



      }

}



     }


 }









 }




 for(int i=0;i<sel_tables.count();i++ )
{

     ctable * left_ctable = 0;
     int left_cfield;

       int left_item_ind;

     left_item_ind = tablenames.indexOf(QString(sel_tables[i]));

            if( left_item_ind >= 0 )

               left_ctable  = tables->at(tableindexes[left_item_ind]);
            else
            {
               left_item_ind = tbl_aliases.indexOf(QString(sel_tables[i]).toUpper());
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

