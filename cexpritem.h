#ifndef CEXPRITEM_H
#define CEXPRITEM_H

#include <QGraphicsItemGroup>

#include "catable.h"

class cexpritem : public catable
{
public:

      cexpritem(QString aexpression, QStringList acolnames,  QGraphicsItem * parent = 0);


QString expression;

int type() const
  {
      // Enable the use of qgraphicsitem_cast with this item.
     return TTYPE_EXPRESSION;
  }



};

#endif // CEXPRITEM_H
