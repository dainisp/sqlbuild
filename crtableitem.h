#ifndef CRTABLEITEM_H
#define CRTABLEITEM_H
#include "catable.h"
#include "ctable.h"
class crtableitem : public catable
{
public:
    crtableitem(ctable *itable,QString alias ,QGraphicsItem *parent = 0);
ctable * table;
 // csertable gensertable(QList<ctableitem *> usedtables, QList<ctable *> alltables);

int type() const
  {
      // Enable the use of qgraphicsitem_cast with this item.
     return TTYPE_TABLE;
  }

//static crtableitem * construct_table(ctable * itable,QGraphicsItem *parent = 0);
};

#endif // CRTABLEITEM_H
