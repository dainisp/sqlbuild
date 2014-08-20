#ifndef CALINK_H
#define CALINK_H

#include <QGraphicsLineItem>
#include "catable.h"



class calink : public QGraphicsLineItem
{
public:
    calink(catable * first, catable * second, int colfirst, int colsecond, int ptype = TTYPE_LINK, bool directed = false ,  QGraphicsItem * parent = 0);
   catable * p1;
    catable * p2;
    int cols1;
   int cols2;
   catable * directedt;
   int ltype;

   int type() const
     {
         // Enable the use of qgraphicsitem_cast with this item.
        return ltype;
     }
};

#endif // CALINK_H
