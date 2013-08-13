#include "cscene.h"

cscene::cscene(QObject *parent): QGraphicsScene(parent)
{
    menu = new QMenu();
    //menu.
    connect(this,SIGNAL(selectionChanged()),this,SLOT(performselection()));
}





void cscene::keyPressEvent ( QKeyEvent * keyEvent )
{

  if(keyEvent->key()==Qt::Key_Delete)
  {



      int delcnt=0;

   for(int i= usedtables.count()-1;i>=0;i--)
       if(usedtables[i]->isSelected())
       {
       ctableitem * table = usedtables[i];
       table->removelinksp();
       removeItem(table);
       delete table;
       usedtables.removeAt(i);
      delcnt++;
       }
   if(!delcnt)
   {
 //findforeignl
   //    QGraphicsScene::keyPressEvent(keyEvent);
QList<QGraphicsItem *> selines = selectedItems();
for(int i=selines.count()-1;i>=0;i--)
{

    for(int j=0;j<usedtables.count();j++)
   {
      int fkind =  usedtables[j]->findforeignl(selines[i]);
      if(fkind >=0 )usedtables[j]->removeforeign(fkind);
}

}


   }



   }

}


void cscene::addtable(ctable * atable, QString talias)
{
    ctableitem * titem =  new ctableitem(atable);
    if(talias.isEmpty())
   {
        QString alias = titem->table->alias;
    if(alias.isEmpty())alias=titem->table->name;
   int aliascount=0;
    for(int i=0;i<usedtables.count();i++)
        if(usedtables[i]->alias.startsWith(alias))aliascount++;
    if(aliascount>0)alias+=QString::number(aliascount );
      titem->alias = alias;
    }else titem->alias = talias;

   usedtables.append( titem );
   addItem( titem);



}

void cscene::place_tables(QList < csertable * > sertables, QList<ctable * > alltables)
{

    foreach(csertable * sertable  ,sertables)
 {
        addtable(alltables[sertable->tindex],sertable->alias);


        QTransform transf;
        transf.translate( sertable->position.x(),sertable->position.y() );

        usedtables.last()->setTransform(transf);
//usedtables.last()->setPos(sertable->position);
usedtables.last()->outputfields =  sertable->outputfields;

if(sertable->outputfields.count() > 0)
for(int i=0;i<sertable->outputfields.count();i++)
{
    QGraphicsRectItem  * outrect = new QGraphicsRectItem(QRectF(0,(sertable->outputfields[i]+1)*usedtables.last()->defaultrowhight,usedtables.last()->defaultwidth,usedtables.last()->defaultrowhight),usedtables.last());
//outrect->stackBefore (this);
outrect->setFlag( QGraphicsItem::ItemStacksBehindParent,  true );
outrect->setBrush(usedtables.last()->outcolor);
usedtables.last()->outputrects.append(outrect);
usedtables.last()->addToGroup(outrect);
}

usedtables.last()->keyfields =  sertable->keyfields ;


    }

    /*
     *
     *

    int primary;




  *
     sertable.alias = alias;
 sertable.primary = usedtables.indexOf(primary);
 sertable.position = scenePos();
 sertable.iindex = usedtables.indexOf(this);
 sertable.outputfields = outputfields;
 sertable.keyfields = keyfields;
 foreach(ctableitem * titem,usedkeys)
  sertable.usedkeys.append(usedtables.indexOf(titem));
 sertable.tindex = alltables.indexOf(table);

 QGraphicsLineItem * primline;
 QList<QGraphicsLineItem *> keylines;

**/


   foreach(csertable * sertable  ,sertables)
   {
 ctableitem *    ftable =  usedtables[sertables.indexOf(sertable)];

            if(sertable->primary >=0)   ftable->primary = usedtables[sertable->primary];

 foreach(int kindex,sertable->usedkeys)
       {
            ftable->usedkeys.append(usedtables[kindex]);

        addforeign(ftable,ftable->usedkeys.last());
         }
  /*
     for(int i=0;i<sertable->keyfields.count();i++)
    addforeign(usedtables[i],idtable);
*/
   }



}


void cscene::addforeign(ctableitem * ftable,ctableitem * idtable)
{
int findex = ftable->table->fkeys[
        ftable->table->fkeytables.indexOf(idtable->table)
        ];

QPointF p1,p2,p1m,p2m;

p1 = QPointF(0,(0.5 + (qreal)( findex  +1) )  * ftable->defaultrowhight );
p2 = QPointF(0,(0.5 +  (qreal)(idtable->table->primary  +1) ) * idtable->defaultrowhight);

if(idtable->mapToScene(0,0).x() > ftable->mapToScene(0,0).x() )
   p1.setX( ftable->defaultwidth);
else p2.setX( idtable->defaultwidth);


 p1m = ftable->mapToScene(p1) ;
p2m = idtable->mapToScene(p2);
QGraphicsLineItem * keyline = new QGraphicsLineItem(QLineF(p1m,p2m));
 keyline->setFlag (QGraphicsItem::ItemIsSelectable,  true );

idtable->primline=keyline;
ftable->keylines.append(keyline);

addItem(keyline);

}



void cscene::performselection()
{
    foreach(ctableitem * stable,  usedtables)
  {
      QBrush selbrush;
      QBrush headb = stable->namerect->brush();

      if(stable->isSelected())selbrush = QBrush(stable->scolor);
      else selbrush = QBrush(stable->hcolor);
      if(headb != selbrush )stable->namerect->setBrush(selbrush);



    }


}


ctableitem * cscene::getselectedtable()
{


    if(selectedItems().count()>0)
   {
QGraphicsItem *  seltable =  selectedItems()[0];
int i;
for(i=0;i<usedtables.count();i++)
    if(usedtables[i] == seltable)break;
if(usedtables[i] == seltable)
    return usedtables[i];

}
return 0;

}





void  cscene::removeat(ctableitem * ritem)
{
int i;
for(i=0;i<usedtables.count();i++)if(usedtables[i]==ritem)break;
if(i<usedtables.count())usedtables.removeAt(i);

}


QString cscene::make_query()
{
    QString  whereq,fromq,selq;



 for(int i=0;i<usedtables.count();i++)
 {
     ctableitem * table = usedtables[i];
     for(int j=0;j<table->outputfields.count();j++)
       {
         selq += QString(",%1.%2").arg(table->alias).arg(table->table->fields[table->outputfields[j]]);
     }
     fromq += QString(",%1 %2").arg(table->table->name).arg(table->alias);


     for(int j=0;j<table->keyfields.count();j++)
      {
         ctableitem *  rtable = table->usedkeys[j];
         whereq += QString(" and %1.%2 = %3.%4").arg(table->alias).arg(table->table->fields[table->table->fkeys[table->keyfields[j]]]).arg(rtable->alias).arg(rtable->table->fields[rtable->table->primary]);
     }

     //QList<ctableitem *  > usedkeys;
     //QList<int> keyfields;


 }

  whereq.remove(0,4);
  selq.remove(0,1);
  fromq.remove(0,1);

  if (selq.isEmpty() )selq=QString("*");
  if (fromq.isEmpty() ) fromq = QString("dual");
  QString retstr = QString("select %1 from %2").arg(selq).arg(fromq);
  if(!whereq.isEmpty())retstr += QString(" where ") + whereq;
  return retstr.toLower();


}




void  cscene::publicate_keys()
{
    for(int i=0;i<usedtables.count();i++)
    {
        ctable * curtable = usedtables[i]->table;

        for(int j=0;j<curtable->fkeys.count();j++)
     {
int f;
for( f=0;f<usedtables.count();f++)
 {
    if(f!=i && usedtables[f]->table == curtable->fkeytables[j]
&& !(usedtables[f]->primline) &&  usedtables[i]->findforeign(usedtables[f]) < 0  &&  usedtables[i]->findforeignind(j)<0  )break;
}



if(f<usedtables.count()){

  /*
    QPointF p1,p2,p1m,p2m;

p1 = QPointF(0,(0.5 + (qreal)(curtable->fkeys[j]+1) )  * usedtables[i]->defaultrowhight );
p2 = QPointF(0,(0.5 +  (qreal)(usedtables[f]->table->primary  +1) ) * usedtables[f]->defaultrowhight);

if(usedtables[f]->mapToScene(0,0).x() > usedtables[i]->mapToScene(0,0).x() )
   p1.setX( usedtables[i]->defaultwidth);
else p2.setX( usedtables[f]->defaultwidth);


 p1m =  usedtables[i]->mapToScene(p1) ;
p2m = usedtables[f]->mapToScene(p2);
QGraphicsLineItem * keyline = new QGraphicsLineItem(QLineF(p1m,p2m));
 keyline->setFlag (QGraphicsItem::ItemIsSelectable,  true );

usedtables[f]->primline=keyline;
usedtables[i]->keylines.append(keyline);
usedtables[f]->primary=usedtables[i];
usedtables[i]->keyfields.append(j);
usedtables[i]->usedkeys.append(usedtables[f]);


idtable->primline=keyline;
ftable->keylines.append(keyline);

this->addItem(keyline);
*/

addforeign(usedtables[i],usedtables[f]);
usedtables[f]->primary=usedtables[i];
usedtables[i]->keyfields.append(j);
usedtables[i]->usedkeys.append(usedtables[f]);

}
        }


    }



}
