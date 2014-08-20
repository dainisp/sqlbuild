#include <QGraphicsScene>
#include "catable.h"
#include "calink.h"
#include "equ_dialog.h"

catable::catable(QGraphicsItem *parent):QGraphicsItemGroup(  parent )
{
    initdefault();
}

/*
  catable::catable(QString tname,QStringList acolnames,QGraphicsItem * parent  = 0)
  :QGraphicsItemGroup(  parent )
  {
    acolnames.


  }
*/
catable::catable(QStringList acolnames, QString ptablestring, QGraphicsItem * parent ):QGraphicsItemGroup(  parent )
{
 initdefault();
tablestring = ptablestring;
for(int i=0;i<acolnames.count();i++)
{
    if(i)
coltypes.append(0);
else
coltypes.append(1);
colnames.append(acolnames[i]);
colstrings.append(QString());

}

colcount = colnames.count();

       int maxwidth = 0;


            for (int i=0;i< colcount;i++ )
            {
       int relativhig = i  * defaultrowhight;
       QGraphicsTextItem *  tline = new QGraphicsTextItem(colnames[i],this);
               tline->setPos(0, relativhig);
              this->addToGroup(tline);
               if(maxwidth < tline->boundingRect().width())maxwidth = tline->boundingRect().width();

            }
            if(maxwidth > defaultwidth ) defaultwidth = maxwidth;

            this->addToGroup(new QGraphicsRectItem(QRectF(0,0,defaultwidth, defaultrowhight * colnames.count()),this));

            for(int i=0;i<colcount;i++)
                if(typecolors[ coltypes[i]].isValid())
                 {
            QGraphicsRectItem *    namerect = new QGraphicsRectItem(QRectF(0,i*defaultrowhight,defaultwidth,defaultrowhight),this) ;
         namerect->setFlag( QGraphicsItem::ItemStacksBehindParent,  true );
         namerect->setBrush(QBrush(typecolors[coltypes[i]]));
                this->addToGroup(namerect);
         colrects.insert(i,namerect);
}


            for(int i=1;i<colcount;i++)
            {
       int relativhig = i  * defaultrowhight;
            //  QGraphicsTextItem *  tline = new QGraphicsTextItem(fname,this);
             //  tline->setPos(0, relativhig);
                this->addToGroup(new QGraphicsLineItem(0,relativhig,defaultwidth,relativhig ,this));
            //  this->addToGroup(tline);
            }




}
/*
int catable::type()
{
 return TTYPE_ABSTRACT;
}
*/
  void catable::set_column_type(int colnum,int coltype)
  {
      if(coltypes[colnum])
      {
        if(coltype)
            colrects[colnum]->setBrush(QBrush(typecolors[coltype]));
        else
      {
            QGraphicsRectItem *  crect = colrects[colnum];
            colrects.remove(colnum);
            removeFromGroup(crect);
            delete crect;
      }
      coltypes[colnum] = coltype;
      }
      else
       {
          if(coltype)
            {
          QGraphicsRectItem *    namerect = new QGraphicsRectItem(QRectF(0,colnum*defaultrowhight,defaultwidth,defaultrowhight),this) ;
       namerect->setFlag( QGraphicsItem::ItemStacksBehindParent,  true );
       namerect->setBrush(QBrush(typecolors[coltype]));
           colrects.insert( colnum, namerect);
           coltypes[colnum] = coltype;
          this->addToGroup(namerect);
          }

      }

  }

void catable::set_column_types(QList<int> coltypes)
{
 for(int i=0;i< coltypes.count();i++)
     set_column_type(i,coltypes[i]);


}

void catable::initdefault()
{

        defaultwidth = 50;
        defaultrowhight = 20;
        typecolors.insert(1,Qt::green);
        typecolors.insert(2,Qt::red);
        typecolors.insert(4,Qt::cyan);
        typecolors.insert(8,Qt::yellow);
        typecolors.insert(16,Qt::magenta);
        selected_item = 0;
ttype = TTYPE_ABSTRACT;
     //   primline = 0;
     //   primary =0;
     //   customrect = 0;
        setFlag (QGraphicsItem::ItemIsSelectable,  true );

}


void catable::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    QPointF point =  event->pos()+dpressed;
 //   this->translate(point.x(),point.y());
//     setPos(point.x(),point.y());
     setTransform(QTransform::fromTranslate(point.x(), point.y()), true);

 //moveline_array(usedarguments,point);
     foreach(QGraphicsItem * item,scene()->items())
     {
         if((item->type() & TTYPE_LINK) == TTYPE_LINK )
         {

             calink * link = static_cast<calink *>(item);
             {
                 if(link->p1 == this)
                    moveoneline( link , 1 , point);
                 if(link->p2 == this)
                    moveoneline( link , 0 , point);

             }



         }

     }



}

void catable::set_type(int type)
{
 ttype = type;

}



void catable::moveoneline(calink * link , int firstpoint ,QPointF point)
{

catable * remote_table = link->p1;
    if(firstpoint)
        remote_table = link->p2;

    qreal pbefore = remote_table->scenePos().x()-ppressed.x();
    qreal pnow =  remote_table->scenePos().x()-this->scenePos().x();
qreal xdiff = 0;
qreal xdifo =0;

    if(pbefore > 0 && pnow < 0 )
    {
        xdiff = -defaultwidth;
    xdifo = remote_table->defaultwidth;

    }

        if(pbefore < 0 && pnow > 0 )
        {
        xdiff = defaultwidth;
xdifo = -remote_table->defaultwidth;
        }

  QLineF line =  link->line();

  QPointF p1;



  if(firstpoint)
       p1 = line.p1();
  else
   p1 = line.p2();



  if(xdiff!=0 )
{

      if(firstpoint)
      line.setP2(line.p2()+QPointF( xdifo,0));
      else
        line.setP1(line.p1()+QPointF( xdifo,0));

      p1.setX(p1.x()+xdiff);

  ppressed = this->scenePos();

  }

  p1 += point;
 if(firstpoint)
  line.setP1(p1);
else
   line.setP2(p1);

 link->setLine(line);



}




 void catable::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
 {
     qreal rfieldpos =  event->pos().y()/this->defaultrowhight ;
   int fieldpos = (int)rfieldpos;
   if(fieldpos >0 && fieldpos < colcount && ( (coltypes[fieldpos] |  CTYPE_OUTPUTFIELD ) == CTYPE_OUTPUTFIELD ) )
      {
  if(coltypes[fieldpos]  == CTYPE_NORMAL)
       set_column_type(fieldpos,CTYPE_OUTPUTFIELD);
   else
      set_column_type(fieldpos,CTYPE_NORMAL);
   }


 }



void catable::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{


//-----------
if (event->buttons() == Qt::RightButton)
{

    qreal rfieldpos =  event->pos().y()/this->defaultrowhight ;
  int fieldpos = (int)rfieldpos;
  if(fieldpos >0 && fieldpos < colcount   )
     {

if(event->modifiers() & Qt::ShiftModifier )
{
    QString exstr =  equ_Dialog::get_equation(colstrings[fieldpos]);
if(exstr.isEmpty() && coltypes[fieldpos] != CTYPE_NORMAL  )
{
    set_column_type(fieldpos,CTYPE_NORMAL);
 colstrings[fieldpos] ="";
}   else{
    colstrings[fieldpos] = exstr;
      set_column_type(fieldpos,CTYPE_OUTPUTFIELD);
}
return;
}

if(event->modifiers() & Qt::ControlModifier )
{
    QString exstr =  equ_Dialog::get_equation();
if(exstr.isEmpty() && coltypes[fieldpos] != CTYPE_NORMAL  )
{
    set_column_type(fieldpos,CTYPE_NORMAL);
 colstrings[fieldpos] ="";
}   else{
    colstrings[fieldpos] = exstr;
      set_column_type(fieldpos,CTYPE_WHERE_FIELD);
}
return;
}


if( (coltypes[fieldpos] | CTYPE_CUSTOM_SELECTED ) == CTYPE_CUSTOM_SELECTED )
  {
if(coltypes[fieldpos] ==CTYPE_CUSTOM_SELECTED )
     set_column_type(fieldpos,CTYPE_NORMAL);
else
    set_column_type(fieldpos,CTYPE_CUSTOM_SELECTED);


}



      /*
  if(selected_item != fieldpos )
   {
    //  QGraphicsRectItem  * outrect = new QGraphicsRectItem(QRectF(0,(fieldpos+1)*defaultrowhight,defaultwidth,(fieldpos+2)*defaultrowhight),this);
      if(selected_item)
      {
      QGraphicsRectItem  * oldrect = colrects.value(selected_item,0);
            if(oldrect)
            {
               removeFromGroup(oldrect);
               delete oldrect;
            }

       }
      QGraphicsRectItem  * outrect = new QGraphicsRectItem(QRectF(0,fieldpos*defaultrowhight,defaultwidth,defaultrowhight),this);
 //outrect->stackBefore (this);
 outrect->setFlag( QGraphicsItem::ItemStacksBehindParent,  true );
    outrect->setBrush(typecolors[CTYPE_CUSTOM_SELECTED]);

colrects.insert(fieldpos,outrect);
  //  argumentrects.append(outrect);
     this->addToGroup(outrect);
 //QList<QGraphicsRectItem * > outputrects;
 //this->stackBefore(outrect);
   //  outrect->stackBefore (this);
    selected_item = fieldpos;
  }
  else
  {
      QGraphicsRectItem  * oldrect = colrects.value(selected_item,0);
      if(oldrect)
      {
         removeFromGroup(oldrect);
         delete oldrect;
      }
      selected_item =0;
  }
*/
  }


}
else
  {
   event->accept();
 dpressed = this->pos() - event->pos();
 ppressed = this->scenePos();

QGraphicsItem::mousePressEvent(event );
}
}

/*
void cexpritem::moveline_array( QList<ctableitem *> remote_tables, QPointF point)
{

    for(int i=0;i<remote_tables.count();i++)
       {
 int remote_index = remote_tables[i]->customlink_self.indexOf(argumentfields[i]);
 if(remote_index >=0)
        moveoneline(remote_tables[i]->customlines[remote_index]  ,remote_tables.at(i),point);
}

}

*/