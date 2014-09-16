#include <QBrush>
#include <QGraphicsScene>
#include "cexpritem.h"


  cexpritem::cexpritem(QString aexpression, QStringList acolnames,  QGraphicsItem * parent )
:catable(acolnames,aexpression , parent )
  {
      if(!aexpression.isNull())
   set_table_tooltip(aexpression);
  }



