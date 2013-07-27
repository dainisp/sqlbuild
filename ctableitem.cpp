#include <QBrush>
#include "ctableitem.h"
#include "cscene.h"



void  ctable::setkeyfield(QString fname)
{
    int kindex = fields.indexOf(fname );
    if(kindex >=0)primary =  kindex;

}


void ctable::setrkeyfield(QString fname,ctable * rtable )
{

    int kindex = fields.indexOf(fname );
    if(kindex >=0)
    {
        fkeys.append( kindex);
        fkeytables.append(rtable);

    }
}


  int  ctable::findtablebyname(QString  tname,QList<ctable * > * alltables )
{
    //   QList<ctable * > alltables;
    int i=0;
    for(i=0;i<alltables->count();i++)
    {
        if((*alltables)[i]->name == tname)break;
    }
    if(i==alltables->count())i=-1;
return i;
}

QList<ctable * > ctable::findftables(QList<ctable * > * alltables )


{
QList<ctable * > ftables;

for(int i=0;i<alltables->count();i++)
{
    ctable *  ftable = (*alltables)[i];
    if(ftable != this  )
  {
    int j;

   j = ftable->fkeytables.indexOf(this);

    if(j>=0)ftables.append(ftable);
}

}

return ftables;
}


void ctableitem::initdefault()
{
    defaultwidth = 50;
    defaultrowhight = 20;
    hcolor = Qt::green;
     scolor= Qt::red;
    outcolor = Qt::yellow;
    primline = 0;
    primary =0;
    setFlag (QGraphicsItem::ItemIsSelectable,  true );
}


ctableitem::ctableitem(QGraphicsItem *parent):QGraphicsItemGroup(  parent )
{
initdefault();
}

 ctableitem::ctableitem(ctable * itable,QGraphicsItem * parent):QGraphicsItemGroup(  parent )
 {

initdefault();
int maxwidth=0;
 table = itable;

 if(table)
 {
QGraphicsTextItem * tnameit = new QGraphicsTextItem(table->name,this);

   this->addToGroup(tnameit);
     if(this->boundingRect().width() >  maxwidth )  maxwidth =  this->boundingRect().width();
     int cnt=0;
     foreach(QString fname,table->fields)
     {
int relativhig = (cnt+1)  * defaultrowhight;
       QGraphicsTextItem *  tline = new QGraphicsTextItem(fname,this);
        tline->setPos(0, relativhig);
       this->addToGroup(tline);
        if(maxwidth < tline->boundingRect().width())maxwidth = tline->boundingRect().width();
cnt++;
     }
     if(maxwidth > defaultwidth ) defaultwidth = maxwidth;

     this->addToGroup(new QGraphicsRectItem(QRectF(0,0,defaultwidth, defaultrowhight +  defaultrowhight * table->fields.count()),this));
 namerect = new QGraphicsRectItem(QRectF(0,0,defaultwidth,defaultrowhight),this) ;
  namerect->setFlag( QGraphicsItem::ItemStacksBehindParent,  true );
  namerect->setBrush(QBrush(hcolor));
         this->addToGroup(namerect);


     cnt=0;
     foreach(QString fname,table->fields)
     {
int relativhig = (cnt+1)  * defaultrowhight;
     //  QGraphicsTextItem *  tline = new QGraphicsTextItem(fname,this);
      //  tline->setPos(0, relativhig);
         this->addToGroup(new QGraphicsLineItem(0,relativhig,defaultwidth,relativhig ,this));
     //  this->addToGroup(tline);

cnt++;
     }

 }
// this->setAcceptDrops(true);

 }


    csertable ctableitem::gensertable(QList<ctableitem *> usedtables, QList<ctable *> alltables)
{
 csertable sertable;
 sertable.alias = alias;
 sertable.primary = usedtables.indexOf(primary);
 sertable.position = scenePos();
 sertable.iindex = usedtables.indexOf(this);
 sertable.outputfields = outputfields;
 sertable.keyfields = keyfields;
 foreach(ctableitem * titem,usedkeys)
  sertable.usedkeys.append(usedtables.indexOf(titem));
 sertable.tindex = alltables.indexOf(table);
 return sertable;

    }



 int ctableitem::findforeign(ctableitem * ftable)
{

 return usedkeys.indexOf(ftable);
 }


   int ctableitem::findforeignl(QGraphicsItem *fline)
   {
       int i;
       for(i=0;i<keylines.count();i++)if(keylines[i]==fline)break;
       if(i==keylines.count())i=-1;
       return i;

   }



int ctableitem::findforeignind(int index)

  {

    int i;
    for(i=0;i<keyfields.count();i++)if(keyfields[i]==index)break;
    if(i==keyfields.count())i=-1;
    return i;


  }




 void ctableitem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
 {
     QPointF point =  event->pos()+dpressed;
  //   this->translate(point.x(),point.y());
//     setPos(point.x(),point.y());
      setTransform(QTransform::fromTranslate(point.x(), point.y()), true);

     for(int i=0;i<this->keylines.count();i++)
  {
       qreal pbefore = usedkeys[i]->scenePos().x()-ppressed.x();
       qreal pnow =  usedkeys[i]->scenePos().x()-this->scenePos().x();
qreal xdiff = 0;
qreal xdifo =0;

       if(pbefore > 0 && pnow < 0 )
       {
           xdiff = -defaultwidth;
       xdifo = usedkeys[i]->defaultwidth;

       }

           if(pbefore < 0 && pnow > 0 )
           {
           xdiff = defaultwidth;
 xdifo = -usedkeys[i]->defaultwidth;
           }

     QLineF line =  keylines[i]->line();
     QPointF p1 = line.p1();
     if(xdiff!=0 )
 {

         line.setP2(line.p2()+QPointF( xdifo,0));

         p1.setX(p1.x()+xdiff);

     ppressed = this->scenePos();

     }

     p1 += point;
     line.setP1(p1);
keylines[i]->setLine(line);

     }

     if(primline)
   {

         qreal pbefore = primary->scenePos().x()-ppressed.x();
         qreal pnow =  primary->scenePos().x()-this->scenePos().x();
  qreal xdiff = 0;
  qreal xdifo =0;

         if(pbefore > 0 && pnow < 0 )
         {
             xdiff = -defaultwidth;
         xdifo = primary->defaultwidth;

         }

             if(pbefore < 0 && pnow > 0 )
             {
             xdiff = defaultwidth;
   xdifo = -primary->defaultwidth;
             }






         QLineF line =  primline->line();
          QPointF p2 = line.p2();

         if(xdiff!=0 )
     {

             line.setP1(line.p1()+QPointF( xdifo,0));

             p2.setX(p2.x()+xdiff);

         ppressed = this->scenePos();

         }




    p2 += point;
         line.setP2(p2);
    primline->setLine(line);



     }


 }


 void ctableitem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
 {
  event->accept();
dpressed = this->pos() - event->pos();
ppressed = this->scenePos();

//if(ppressed.x() !=0)
  //  printf("asdfasdf");

 QGraphicsItem::mousePressEvent(event );
 /*
 if(this->isSelected())this->namerect->setBrush(QBrush(scolor));
 else this->namerect->setBrush(QBrush(hcolor));
*/
 }


 void ctableitem::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event )
 {

   qreal rfieldpos =  event->pos().y()/this->defaultrowhight ;
 int fieldpos = (int)rfieldpos-1;
 if(fieldpos >=0)
    {
 int  i;
 for(i=0;i<outputfields.count();i++)
     if(outputfields[i]==fieldpos)break;
 if(i==outputfields.count())
  {
   //  QGraphicsRectItem  * outrect = new QGraphicsRectItem(QRectF(0,(fieldpos+1)*defaultrowhight,defaultwidth,(fieldpos+2)*defaultrowhight),this);

     QGraphicsRectItem  * outrect = new QGraphicsRectItem(QRectF(0,(fieldpos+1)*defaultrowhight,defaultwidth,defaultrowhight),this);
//outrect->stackBefore (this);
outrect->setFlag( QGraphicsItem::ItemStacksBehindParent,  true );
     outputfields.append(fieldpos);
   outrect->setBrush(outcolor);
    outputrects.append(outrect);
    this->addToGroup(outrect);
//QList<QGraphicsRectItem * > outputrects;
//this->stackBefore(outrect);
  //  outrect->stackBefore (this);
 }
 else
 {
  outputfields.removeAt(i);
  QGraphicsRectItem  * outrect = outputrects[i];
  outputrects.removeAt(i);
  this->removeFromGroup(outrect);
  delete outrect;
 }

 }

 }


 void ctableitem::removeprimary()
 {
     if(primary)
     {
 int find = primary->findforeign(this);
 primary->removeforeign(find);
  }


 }
 void ctableitem::removeforeign(int keyind)
 {
     ctableitem * pitem = usedkeys[keyind];
     pitem->primary =0;
     pitem->primline = 0;
      usedkeys.removeAt(keyind);
keyfields.removeAt(keyind);
      QGraphicsLineItem * pline = keylines[keyind];
      keylines.removeAt(keyind);
      scene()->removeItem( pline);
delete pline;
 }


 void ctableitem::removelinksp()
 {
  for(int i=0;i<keyfields.count();i++)
 {
    ctableitem * pitem = usedkeys[i];
       QGraphicsLineItem * pline =   pitem->primline;
    pitem->primline = 0;
    pitem->primary =0;
    scene()->removeItem( pline);
delete pline;

  }

  removeprimary();

 }

 void ctableitem::removelinks()
{
     for(int i=0;i<keyfields.count();i++)removeforeign(i);
     removeprimary();

 }


void ctableitem::keyPressEvent ( QKeyEvent * event )
{

    if(event->key()==Qt::Key_Delete)
  {



   }


}
