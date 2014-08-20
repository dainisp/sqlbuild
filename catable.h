#ifndef CATABLE_H
#define CATABLE_H

#include <QGraphicsItemGroup>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include "defaultdefs.h"


class calink;


class catable : public QGraphicsItemGroup
{
public:
    catable(QGraphicsItem * parent = 0);
    catable(QStringList acolnames,QString ptablestring = QString(),QGraphicsItem * parent  = 0);
    //   catable(QString tname,QStringList acolnames,QGraphicsItem * parent  = 0);
   QString tablestring;
   QStringList colnames;
   QList<int> coltypes;
   QMap<int,QColor> typecolors;
int colcount;
   int defaultwidth;
   int defaultrowhight;
   int selected_item;
   QStringList colstrings;
   QMap<int, QGraphicsRectItem * > colrects;
   QPointF dpressed;
  QPointF ppressed;
 int ttype;

  void set_column_type(int colnum,int coltype);
   void set_column_types(QList<int> coltypes);

  void moveoneline(calink *link , int firstpoint, QPointF point);
  void set_type(int type);
  int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
       return TTYPE_ABSTRACT;
    }
protected:
     void initdefault();
   void mousePressEvent ( QGraphicsSceneMouseEvent * event );
 void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
 void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
};

#endif // CATABLE_H
