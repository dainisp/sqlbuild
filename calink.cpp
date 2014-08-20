#include "defaultdefs.h"
#include "calink.h"
#include "catable.h"

calink::calink(catable *first, catable *second,
               int colfirst, int colsecond,
               int ptype ,bool directed, QGraphicsItem *parent):QGraphicsLineItem(  parent )
{

    p1 = first;
    p2 = second;
    cols1 = colfirst;
    cols2 = colsecond;
    ltype = ptype;
    if(directed)
        directedt = first;
    else
        directedt = 0;
  setFlag (QGraphicsItem::ItemIsSelectable,  true );
}

