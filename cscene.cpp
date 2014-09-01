#include <QStack>
#include <QKeyEvent>
#include "cscene.h"
#include "expr_dialog.h"



cscene::cscene(QObject *parent): QGraphicsScene(parent)
{
    menu = new QMenu();
    mode=0;
    //menu.
    connect(this,SIGNAL(selectionChanged()),this,SLOT(performselection()));
}



void cscene::arrange_tables()
{

QList<QList<calink * > > p1;
QList<QList<calink * > > p2;
QList<int> linkcounts;
QList<catable * > tables;
QList<int> ptables;
QList<calink * > links;
QList<catable *> p1t;
QList<catable *> p2t;


foreach(QGraphicsItem * item,items())
  {

   if( (item->type() & TTYPE_LINK)  == TTYPE_LINK   )
     {
   calink * link = static_cast<calink * >(item);
   if( !(( p1t.indexOf( link->p1) >= 0 && p2t.indexOf( link->p2) >= 0 )
           || ( p1t.indexOf( link->p2) >= 0 && p2t.indexOf( link->p1) >= 0 )  )  )
 {
       links.append(link);
  p1t.append(link->p1);
  p2t.append(link->p2);
   }
   }
   if( (item->type() & TTYPE_ABSTRACT)  == TTYPE_ABSTRACT   )
     {

  tables.append(static_cast<catable * >(item));
   }

}

int maxcount = 0;
catable *  maxtable=0;
foreach (catable * table, tables) {
    QList<calink * > p1l;
    QList<calink * > p2l;
int lcount = 0;
foreach(calink * link,links)
 {
if(link->p1 == table)
  {
  p1l.append(link);
  lcount++;
   }
if(link->p2 == table)
  {
  p2l.append(link);
  lcount++;
   }
}

if(maxcount < lcount)
  {
  maxcount =lcount;
  maxtable = table;
}
//linkcounts.append(lcount);
p1.append(p1l);
p2.append(p2l);

}

enum vert_colors
{
WHITE,
GRAY,
BLACK

};



if(maxtable)
 {
QList<int> tcolors;
for(int i = 0;i<tables.count();i++)
{
tcolors.append(WHITE);
linkcounts.append(100000);
ptables.append(i);
}

int tind = tables.indexOf(maxtable);
tcolors[tind] = GRAY;
linkcounts[tind] = 0;
QStack<int> tstack;
tstack.push(tind);
while(tstack.isEmpty())
 {
 tind = tstack.pop();
 QList<calink * >  p1c = p1[tind];
 for(int i=0;i<p1c.count();i++  )
 {
 int rind = tables.indexOf( p1c[i]->p2);
 if(tcolors[rind] == WHITE)
  {
  tcolors[rind] = GRAY;
  linkcounts[rind] = linkcounts[tind] + 1;
    ptables[rind] = tind;
    tstack.push(rind);
 }
 }
    p1c = p2[tind];
 for(int i=0;i<p1c.count();i++  )
 {
 int rind = tables.indexOf( p1c[i]->p1);
 if(tcolors[rind] == WHITE)
  {
  tcolors[rind] = GRAY;
  linkcounts[rind] = linkcounts[tind] + 1;
    ptables[rind] = tind;
    tstack.push(rind);
 }
 }

 tcolors[tind]=BLACK;


 }
}






}



QString cscene::export_allt_to_graphml()
{
    QString xmlstr = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?> "
                             "   <graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" "
                             "   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
                             "   xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns "
                             "   http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\"> "
                             "  <graph id=\"G\" edgedefault=\"undirected\">");
    QString linklist;

    for(int i=0;i<alltables->count();i++)
    {
    xmlstr += QString("<node id=\"n%1\"/>\n").arg(i);
    for(int j=0;j<alltables->at(i)->fkeytables.count();j++)
      {
        ctable * ftable =  alltables->at(i)->fkeytables[j];
       // int f_ind = alltables->indexOf(ftable)
        linklist += QString(" <edge source=\"n%1\" target=\"n%2\"/>\n")
                .arg(i)
                .arg(alltables->indexOf(ftable));
    }

    }
  return xmlstr + linklist +  QString("</graph></graphml>");

}




void cscene::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
 if(mode)
    {

  int argcount = 2;
  QString name("Expr");
  QString expr("\%1 + \%2 ");
int rez =  expr_dialog::get_expr_params(&name, &argcount,&expr );
 if(rez)
 {
  QStringList colnames;
  colnames.append(name);
  for(int i=1;i<=argcount;i++)
      colnames.append(QString("ARGUMENT %1").arg(i));

 cexpritem *  expritem = new cexpritem(expr,colnames);



 QTransform transf;
 transf.translate( event->pos().x(),event->pos().y() );
  expritem->setTransform(transf);

  addItem(expritem);
mode = 0;

 }




 }
else
   QGraphicsScene::mousePressEvent(event) ;

}


void cscene::keyPressEvent ( QKeyEvent * keyEvent )
{

  if(keyEvent->key()==Qt::Key_Delete)
  {

      QList<catable *> seltables;

      foreach(QGraphicsItem * item,selectedItems())
        {

         if( (item->type() & TTYPE_ABSTRACT)  == TTYPE_ABSTRACT   )
           {
            seltables.append( static_cast<catable *>(item));

         }


      }

      foreach (QGraphicsItem * item, items()) {


      if((item->type() & TTYPE_LINK) == TTYPE_LINK )
      {
          calink * link = static_cast<calink * >(item);
          if(link->isSelected()
                  || seltables.indexOf( link->p1) >=0
                  || seltables.indexOf( link->p2) >=0   )
       {
              removeItem(link);
          delete link;
      }
      }
      }

      foreach(catable * table,seltables)
      {
          removeItem(table);
          delete table;

      }

   }

}


crtableitem *  cscene::addtable(ctable * atable, QString talias)
{

     QString alias=atable->alias;

    if(talias.isEmpty())
   {
     int aliascount=0;
   foreach (QGraphicsItem *  item, items()) {
       if((item->type() & TTYPE_TABLE) == TTYPE_TABLE )
        {
           crtableitem *  table = static_cast< crtableitem *>(item);
           if(table->tablestring.startsWith(alias))aliascount++;

       }
   }





    if(aliascount>0)alias+=QString::number(aliascount );



    }else alias = talias;







    crtableitem * titem =  new crtableitem(atable,alias);



   addItem( titem);

return titem;

}



bool cscene::add_selected_link()
{
int firstcol,secondcol;
catable * first = 0;
catable * second =0;

foreach (QGraphicsItem * item , this->items()) {
 int ttype = item->type();
 if( (ttype & TTYPE_ABSTRACT)  == TTYPE_ABSTRACT   )
 {

  if(!first)
  {
    first = static_cast<catable *> (item);
    int custind = first->coltypes.indexOf(CTYPE_CUSTOM_SELECTED);
   if(custind >0 )
      firstcol = custind;
   else first = 0;
  }
  else
  {
   second =  static_cast<catable *> (item);
    int custind = second->coltypes.indexOf(CTYPE_CUSTOM_SELECTED);
   if(custind >0 )
   {
     secondcol = custind;
     break;
   }
   else second = 0;
  }


 }

}

if(first != 0 && second !=0   )
  {
  add_link(first,second,firstcol,secondcol,TTYPE_CUSTOM_LINK);
return true;
}

return false;


}


void cscene::add_link(catable * first, catable * second,
                      int firstcol, int secondcol, int type, bool directed)
{

 calink * link = new calink(first,second,firstcol,secondcol,type,directed);

 QPointF p1,p2,p1m,p2m;

 p1 = QPointF(0,(0.5 + (qreal) firstcol)   * first->defaultrowhight );
 p2 = QPointF(0,(0.5 +  (qreal)secondcol) * second->defaultrowhight);

 qreal fdist = abs(  second->mapToScene(0,0).x() -   first->mapToScene(0,0).x() - first->defaultwidth);
 qreal sdist =  abs(second->mapToScene(0,0).x() + second->defaultwidth - first->mapToScene(0,0).x());


 if(fdist <  sdist )
     p1.setX( first->defaultwidth);

    else
      p2.setX( second->defaultwidth);




  p1m = first->mapToScene(p1) ;
 p2m = second->mapToScene(p2);


 link->setLine(QLineF(p1m,p2m) );


 addItem(link);

}







void cscene::performselection()
{




    foreach (QGraphicsItem *  item, items())
    {
        if((item->type() & TTYPE_ABSTRACT) == TTYPE_ABSTRACT)
         {
           catable * table = static_cast<catable *>(item);
          if(table->isSelected())
              table->set_column_type(0,CTYPE_HEADER_SELECTED);
          else
              table->set_column_type(0,CTYPE_HEADER);
        }
    }




}


crtableitem * cscene::getselectedtable()
{

crtableitem * table;


foreach (QGraphicsItem *  item, selectedItems()) {
    if((item->type() & TTYPE_TABLE) == TTYPE_TABLE )
     {
        table = static_cast< crtableitem *>(item);
        return table;

    }
}


return 0;

}



/*

void  cscene::removeat(ctableitem * ritem)
{
int i;
for(i=0;i<usedtables.count();i++)if(usedtables[i]==ritem)break;
if(i<usedtables.count())usedtables.removeAt(i);

}

*/
QString cscene::make_query()
{
 int maxrowwidth = 80;

 int wherwidth = 0;
 int selwidth = 0;
 int fromwidth = 0;
  QString wherstr;
QString selstr;
 QString fromstr;
 QMap<catable*,QString> exprmap;

    foreach (QGraphicsItem *  item, items()) {
        if((item->type() & TTYPE_TABLE) == TTYPE_TABLE )
         {
            crtableitem *  table = static_cast< crtableitem *>(item);
        QString addfrom = QString(",%1 %2").arg(table->colnames[0]).arg(table->tablestring);
            if(fromwidth + addfrom.length() > maxrowwidth)
           {
                fromwidth = addfrom.length();
               fromstr += "\n" +  addfrom.toLower();
           }
            else
            {
                fromstr += addfrom.toLower();
                fromwidth += addfrom.length();
            }

         for(int i=1;i<table->colcount;i++ )
           {
          if(table->coltypes[i] == CTYPE_OUTPUTFIELD )
           {
           QString addsel;
           if(table->colstrings[i].isEmpty())
           {
            addsel = QString(",%1.%2").arg(table->tablestring).arg(table->colnames[i]).toLower();

           }
           else
            {
            addsel = "," +  table->colstrings[i].replace("?",QString("%1.%2").arg(table->tablestring).arg(table->colnames[i]).toLower());
           }

           if(selwidth + addsel.count() > maxrowwidth )
              {

               selwidth = addsel.length();
               selstr += "\n" + addsel;
           }
           else
           {
            selwidth +=  addsel.length();
               selstr +=  addsel;
           }



          }


          if(table->coltypes[i] == CTYPE_WHERE_FIELD )
           {

              QString addwhere;
              if(table->colstrings[i].isEmpty())
              {
               addwhere = QString(" AND ") + QString("%1.%2").arg(table->tablestring).arg(table->colnames[i]).toLower();

              }
              else
               {
               addwhere = " AND " +  table->colstrings[i].replace(QRegExp("\\?[0-9]*"),QString("%1.%2").arg(table->tablestring).arg(table->colnames[i]).toLower());
              }

              if(wherwidth + addwhere.count() > maxrowwidth )
                 {

                  wherwidth = addwhere.length();
                  wherstr += "\n" + addwhere;
              }
              else
              {
               wherwidth +=  addwhere.length();
                  wherstr +=  addwhere;
              }


          }


         }




        }





        if((item->type() & TTYPE_LINK) == TTYPE_LINK )
         {

         calink * link = static_cast<calink *>(item);





         if((link->type() == TTYPE_CUSTOM_LINK && link->p1->type() != TTYPE_EXPRESSION && link->p2->type() != TTYPE_EXPRESSION   )   || link->type() == TTYPE_FOREIGN_LINK   )
           {


             QString addwhere = QString(" AND ")  + QString("%1.%2 = %3.%4")
                .arg(link->p1->tablestring)
                .arg(link->p1->colnames[link->cols1])
                .arg(link->p2->tablestring)
                .arg(link->p2->colnames[link->cols2]).toLower();

        if(wherwidth + addwhere.count() > maxrowwidth )
           {

            wherwidth = addwhere.length();
            wherstr += "\n" + addwhere;
        }
        else
        {
         wherwidth +=  addwhere.length();
            wherstr +=  addwhere;
        }




         }
         else
         {
         if(link->p1->type() == TTYPE_EXPRESSION || link->p2->type() == TTYPE_EXPRESSION )
          {
           catable * expr;
           crtableitem * table;
           int tabcol,exprcol;
           int exprtype;
             if(link->p1->type() == TTYPE_EXPRESSION )
           {
              expr = link->p1;
        exprtype = link->p1->type();
              table = static_cast< crtableitem * >(link->p2);
          exprcol = link->cols1;
          tabcol = link->cols2;
             }
           else
          {
                  exprtype = link->p2->type();
                 expr = link->p2;
                 table = static_cast< crtableitem * >(link->p1);
             exprcol = link->cols2;
             tabcol = link->cols1;

             }
       if(exprmap.keys().indexOf(expr) < 0)
           exprmap.insert(expr,expr->tablestring);

        exprmap[expr] = exprmap[expr].replace("?" + QString::number(exprcol),table->tablestring + "." + table->colnames[tabcol]  );
        if(exprmap[expr].indexOf("?")<0)
        {
            if( (exprtype  & TTYPE_EXPRESSION_WHERE)  == TTYPE_EXPRESSION_WHERE   )
         {
        QString addwhere = QString(" AND ")  + exprmap[expr];

        if(wherwidth + addwhere.count() > maxrowwidth )
           {

            wherwidth = addwhere.length();
            wherstr += "\n" + addwhere;
        }
        else
        {
         wherwidth +=  addwhere.length();
            wherstr +=  addwhere;
        }

        }
       else
            {
           QString addwhere = QString(",")  + exprmap[expr];

           if(selwidth + addwhere.count() > maxrowwidth )
              {

               selwidth = addwhere.length();
               selstr += "\n" + addwhere;
           }
           else
           {
            selwidth +=  addwhere.length();
               selstr +=  addwhere;
           }

           }



        }



         }




         }



        }





}


    QRegExp wherexp("^[\\r\\n\\s]*AND ");
     QRegExp selexpr("^[\\r\\n]*,");

  wherstr.replace(wherexp,"");
  selstr.replace(selexpr,"");
  fromstr.replace(selexpr,"");

  if (selstr.isEmpty() )selstr=QString("*");
  if (fromstr.isEmpty() ) fromstr = QString("DUAL");
  QString retstr = QString("SELECT %1\nFROM %2").arg(selstr).arg(fromstr);
  if(!wherstr.isEmpty())retstr += QString("\nWHERE ") + wherstr;
  return retstr;


}

void cscene::savel_to_stream(QDataStream * stream, QList<catable *> tlist)
{

   QList<calink * > llist;
    foreach (QGraphicsItem *  item, items()) {
        if((item->type() & TTYPE_LINK) == TTYPE_LINK )
         {
           llist.append(static_cast<calink *>(item ));
        }
    }
*stream << llist.count();
    foreach (calink * link,llist) {

        *stream <<  link->ltype;
       if(link->directedt)
        *stream << tlist.indexOf(link->directedt);
       else *stream << -1;

       *stream <<  tlist.indexOf(link->p1);
       *stream << tlist.indexOf(link->p2);
       *stream << link->cols1;
       *stream << link->cols2;
    }

}

void cscene::loadl_from_stream(QDataStream * stream,QList<catable *> tlist)
{
    //ltype << directedt<< p1 << p2 << cols1 << cols2 <<  << ;
 int lcount;
*stream >> lcount;
 for(int i=0;i<lcount;i++)
 {
 int ltype;
 *stream >> ltype;
 int directedt;
*stream >> directedt;
/*
 catable * tdirectedt;

if(directedt >= 0)
  tdirectedt = tlist[directedt];
*/
 int p1;
*stream >> p1;
catable * tp1 = tlist[p1];
        int p2;
       *stream >> p2;
       catable * tp2 = tlist[p2];
 int cols1,cols2;
 *stream >> cols1 >> cols2;

if(directedt == p1 )
    add_link(tp2,tp1,cols2,cols1,ltype,true);
else
 add_link(tp1,tp2,cols1,cols2,ltype,(directedt >= 0));


 }

}

QList<catable *> cscene::save_to_stream(QDataStream * stream)
{

    QList<catable *> tlist;

    foreach (QGraphicsItem *  item, items()) {
        if((item->type() & TTYPE_ABSTRACT) == TTYPE_ABSTRACT )
         {
           tlist.append(static_cast<catable *>(item) );
        }
}
 *stream << tlist.count();
        foreach (catable * table, tlist) {

            *stream << table->type();
            if((table->type() & TTYPE_TABLE) == TTYPE_TABLE )
            *stream << alltables->indexOf(static_cast<crtableitem * >(table)->table );
            else
              *stream << 0;
           *stream << table->tablestring;
            *stream << table->colnames;
            *stream << table->coltypes;
            *stream << table->colstrings;
            *stream << table->scenePos();

        }
 return tlist;
}



QList<catable *> cscene::load_from_stream(QDataStream *stream)
{
//stream ttype << tindex <<  tablestring
  //   colnames      << coltypes << colstrings << position  ;
    QList<catable *> tlist;
 int tcount;
 *stream >> tcount;
 for(int i=0;i<tcount;i++)
 {
 int ttype;
  *stream >> ttype;
  int tindex;
  QString tablestring;
  QStringList colnames;
  *stream >> tindex;
  *stream >> tablestring;
  *stream >> colnames;
   QList<int> coltypes;
 catable * atable;

   if((ttype & TTYPE_TABLE) == TTYPE_TABLE   )
    {

    crtableitem * table = new crtableitem(alltables->at(tindex),tablestring);
  atable = table;
   }
  else
   {
    atable = new catable(colnames,tablestring);
       atable->set_type(ttype);

   }
 *stream >> coltypes;
 atable->set_column_types(coltypes);
 QStringList colstrings;
 *stream >> colstrings;
 atable->colstrings = colstrings;
 QPointF position;
*stream >> position;
//table.
 QTransform transform;
 transform.translate(position.x(),position.y());


 atable->setTransform(transform);
//atable->setPos(position);
 tlist.append(atable);
 addItem(atable);
 }

 return tlist;
}

void  cscene::publicate_keys()
{
//----------------------Add custom links


    if(add_selected_link())
        return;

   // ----------------------------------




    foreach (QGraphicsItem *  item, items())
       {
        if((item->type() & TTYPE_TABLE) == TTYPE_TABLE )
         {
            crtableitem *  table = static_cast< crtableitem *>(item);

            for(int i= 0;i<table->table->fkeys.count();i++)
            {
                crtableitem * prim_item =   find_primary_table(table->table->fkeytables[i]);
                if(prim_item && (prim_item != table) )
                    add_link(table,prim_item,table->table->fkeys[i]+1,
                             prim_item->table->primary+1,TTYPE_FOREIGN_LINK,true);

            }


         }

        }




}

crtableitem * cscene::find_primary_table(ctable * table)
{

    foreach (QGraphicsItem *  item, items()) {
        if((item->type() & TTYPE_TABLE) == TTYPE_TABLE )
         {
            crtableitem *  prim_item = static_cast< crtableitem *>(item);
            if(prim_item->table == table) // vai atrastajai tabulas vienibai prototips sakrit
              {
                bool found = false;
                foreach (QGraphicsItem *  item, items()) {
                    if((item->type() & TTYPE_FOREIGN_LINK) == TTYPE_FOREIGN_LINK )
                     {
                        calink * link = static_cast<calink *>(item);
                        if(link->directedt == prim_item)
                           {
                        found = true;
                            break;
                    }  }
                }

                if(!found) // primara atslega briva
                    return prim_item;
              }
      }

}

return 0;
 }

/*
void cscene::addforeign(crtableitem * ftable,crtableitem * idtable)
{

//    add_link(table,prim_item,table->table->fkeys[i]+1,
  //           prim_item->table->primary+1,TTYPE_FOREIGN_LINK,true);

 add_link(ftable,idtable,ftable->table->fkeys);


}

*/
