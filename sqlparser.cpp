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

QList<QStringList> sel_tables;
QList<QStringList> sel_columns;
QStringList sel_expressions;
QStringList sel_aliases;
QStringList wh_expressions;
QStringList current_sel_tables;
QStringList current_sel_columns;
QString current_sel_expression;

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

QString current_expression;

QList<int> wh_optypes;

int current_optype;


int tablenamecnt;
//int sel_col_count;
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
     current_expression.append(QString(" ?%1").arg(current_wh_tables.count()));

    }




}



void save_sel_cols(QString * table,QString * column)
{
if( is_sel){
int colind=-1;
int tabind=-1;
    if(!column->isEmpty())
        colind = current_sel_columns.indexOf(column->toUpper());



    if(!table->isEmpty())
      {
        if(colind>=0  )
          {
            if(current_sel_tables[colind] == table->toUpper()  )
                tabind = colind;
        }
        else
        tabind = current_sel_tables.indexOf(table->toUpper());
    }
    else
    {
        if(colind >= 0)
            tabind = colind;
     }

    if(column->isEmpty() && tabind >= 0  )
        colind = tabind;




      if( tabind >=0 &&  tabind == colind  )
           current_sel_expression.append(QString(" ?%1").arg(tabind+1));
      else{
    current_sel_tables.append( table->toUpper());
    current_sel_columns.append( column->toUpper());
    current_sel_expression.append(QString(" ?%1").arg(current_sel_tables.count()));
      }
}

else save_wh_cols( table, column);

}

void append_expression(QString * exp)
{
 current_expression.append(*exp);

}

void reset_saved_columns()
{
wh_tables.append(current_wh_tables);
wh_columns.append(current_wh_columns);
wh_expressions.append(current_expression);
current_wh_tables.clear();
current_wh_columns.clear();
current_expression.clear();
}

void reset_saved_sel_columns(QString * alias)
{
sel_columns.append(current_sel_columns);
sel_tables.append(current_sel_tables);
sel_expressions.append(current_sel_expression);
sel_aliases.append(* alias);
current_sel_columns.clear();
current_sel_tables.clear();
current_sel_expression.clear();

}

void save_comparison(QString * operation)
{
    if(is_where)
current_expression.append(operation->prepend(" "));
    else
     current_sel_expression.append(operation->prepend(" "));
}




void save_comparison_number(int num)
{
  QString  apstr(QString::number(num));
  current_expression.append(apstr.prepend(" "));

}



void start_save(void)
{

    is_where = 0;
    is_sel = 1;
    wh_tables.clear();
    wh_columns.clear();
    wh_expressions.clear();
    tbl_aliases.clear();
    sel_columns.clear();
  tablenames.clear();
  sel_tables.clear();
  sel_expressions.clear();
  current_sel_columns.clear();
  current_sel_tables.clear();
  current_sel_expression.clear();
sel_aliases.clear();

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


void  findcrtables(  QList< crtableitem * > crtlist,QString tablename,QString colname,int * tabindex,int * colindex )
 {
int i = 0;
* tabindex = -1;

    foreach (crtableitem * crtable , crtlist) {



 if(crtable->tablestring == tablename  || crtable->colnames[0] == tablename  )
   {
     int fieldind = crtlist[i]->table->fields.indexOf(colname);
     if( fieldind >= 0 )
     {
     * tabindex = i;
     * colindex =fieldind;
         return;
     }
 }





i++;
   }


 }


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
    QList<cexpritem * > expreslist;
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

 if(sel_tables.count() > 0 )
 {

     for(int i=0;i<sel_tables.count();i++ )
 {
         int tab_ind = -1;
         if(sel_tables[i].count() == 1)
        {
          int col_ind;
             findcrtables(tlist,sel_tables[i][0],sel_columns[i][0],&tab_ind,&col_ind);
             if( tab_ind >=0 )
             {
                 tlist[tab_ind]->set_column_type(col_ind+1,CTYPE_OUTPUTFIELD);
                 if(sel_expressions[i].trimmed() != "?1" || !sel_aliases[i].isEmpty() )
             {
                  QString expr =  sel_expressions[i];
                  if(!sel_aliases[i].isEmpty())
                      expr += " " + sel_aliases[i];
                 tlist[tab_ind]->colstrings[col_ind+1] = expr;
                 tlist[tab_ind]->set_column_tooltip(col_ind+1,expr);
             }

             }



         }

         if(tab_ind < 0 )
        {




             QStringList colnames =  sel_columns[i];
             QString expression = sel_expressions[i];
             if(sel_aliases[i].isEmpty())
             colnames.prepend(QString("Out%1").arg(expreslist.count()+1));
             else
                {
               colnames.prepend(sel_aliases[i]);
               expression += " " + sel_aliases[i];
             }

             cexpritem * expritem  = new  cexpritem(expression , colnames);
                     expritem->set_type( TTYPE_EXPRESSION_SELECT);
                     expritem->typecolors[CTYPE_HEADER] = Qt::yellow;
                   expreslist.append(expritem);
                  scene->addItem(expritem);

                  for(int j=0;j<sel_tables[i].count();j++)
                  {
                 int tab_ind,col_ind;
                 findcrtables(tlist,sel_tables[i][j],sel_columns[i][j],&tab_ind,&col_ind);
                 if(tab_ind >=0)
                   {
                     scene->add_link(expritem,tlist[tab_ind],j+1,col_ind+1,TTYPE_CUSTOM_LINK);

                 }
                 else
                 {
                     expritem->expression = expritem->expression.replace(QString("?%1").arg(j),sel_columns[i][j]);

                 }


                  }



         }





  }

 }



 if(wh_tables.count() > 0)
   {



     for(int i=0;i<wh_tables.count();i++ )
 {
     QString expression =  wh_expressions[i];

         if( wh_tables[i].count() >=0  &&  wh_tables[i].count() < 3    )
     {
            QString secondtable;
            QString secondcol;
       QString firsttable = wh_tables[i][0];
    QString firstcol = wh_columns[i][0];

int first_field,second_field,first_tab_ind,second_tab_ind;
 findcrtables(tlist,firsttable,firstcol,&first_tab_ind,&first_field);

  if( wh_tables[i].count() == 1)
  {
      tlist[first_tab_ind]->set_column_type(first_field+1,CTYPE_WHERE_FIELD);

      tlist[first_tab_ind]->colstrings[first_field+1] = expression;
        tlist[first_tab_ind]->set_column_tooltip(first_field+1,expression);


  }




      if( wh_tables[i].count() == 2 )
     {


          secondtable = wh_tables[i][1];
        secondcol = wh_columns[i][1];

 findcrtables(tlist,secondtable,secondcol,&second_tab_ind,&second_field);

 if( first_tab_ind >= 0 && second_tab_ind >= 0 )

  {


     if(expression.trimmed() == QString("?1 = ?2"))
     {
     if(tlist[first_tab_ind]->table->primary == first_field   )
     {
       int foreign_ind = tlist[second_tab_ind]->table->get_foreign_by_prim_table(tlist[first_tab_ind]->table);
               if(foreign_ind == second_field )
                  scene->add_link(tlist[first_tab_ind],tlist[second_tab_ind],first_field+1,second_field+1,TTYPE_FOREIGN_LINK,true);

     }
     else
       {
         if(tlist[second_tab_ind]->table->primary == second_field   )
         {
           int foreign_ind = tlist[first_tab_ind]->table->get_foreign_by_prim_table(tlist[second_tab_ind]->table);
                   if(foreign_ind == first_field )
                      scene->add_link(tlist[second_tab_ind],tlist[first_tab_ind],second_field+1 ,first_field+1,TTYPE_FOREIGN_LINK,true);

         }
     else
         {
         scene->add_link(tlist[first_tab_ind],tlist[second_tab_ind],first_field+1,second_field+1,TTYPE_CUSTOM_LINK);

         }


     }
     }


 }



}



     }else
         {



QStringList colnames =  wh_columns[i];

colnames.prepend(QString("Expr%1").arg(expreslist.count()+1));

          cexpritem * expritem  = new  cexpritem(expression, colnames);
         expritem->set_type( TTYPE_EXPRESSION_WHERE);
              expritem->typecolors[CTYPE_HEADER] = Qt::magenta;
          expreslist.append(expritem);
     scene->addItem(expritem);

     for(int j=0;j<wh_tables[i].count();j++)
     {
    int tab_ind,col_ind;
    findcrtables(tlist,wh_tables[i][j],wh_columns[i][j],&tab_ind,&col_ind);
    if(tab_ind >=0)
      {
        scene->add_link(expritem,tlist[tab_ind],j+1,col_ind+1,TTYPE_CUSTOM_LINK);

    }
    else
    {
        expritem->expression = expritem->expression.replace(QString("?%1").arg(j),wh_columns[i][j]);

    }


     }

 }






 }









 }

scene->arrange_tables();

/*
 for(int i=0;i<sel_tables.count();i++ )
{
int table_ind,field_ind;

findcrtables(tlist,sel_tables[i],sel_columns[i],&table_ind,&field_ind);

if(table_ind  >= 0 )
  tlist.at(table_ind)->set_column_type(field_ind+1,CTYPE_OUTPUTFIELD);

 }

*/

return 0;
}

