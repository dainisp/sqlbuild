#ifndef CCONDITIONITEM_H
#define CCONDITIONITEM_H

#include <QGraphicsItemGroup>
#include <ctableitem.h>
class cconditionitem : public QGraphicsItemGroup
{
public:
    cconditionitem(QGraphicsItem * parent = 0);
QString condition;
  ctableitem *  condtable;
  int condfield;

};

#endif // CCONDITIONITEM_H
