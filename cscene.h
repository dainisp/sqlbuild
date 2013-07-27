#ifndef CSCENE_H
#define CSCENE_H

#include <QGraphicsScene>
#include "ctableitem.h"
class cscene : public QGraphicsScene
{
  Q_OBJECT
public:
    cscene( QObject * parent = 0);
 QList<ctableitem *>   usedtables;
  QList<QGraphicsLineItem *>  usedlines;
void  publicate_keys();
void addtable(ctable * atable,QString talias=QString());
void addforeign(ctableitem * ftable,ctableitem * idtable);
ctableitem * getselectedtable();
QString make_query();
void  removeat(ctableitem * ritem);
void place_tables(QList < csertable * > sertables, QList<ctable *> alltables);

//void findprimary(ctableitem * pitem);

private slots:

void performselection();

protected:

void keyPressEvent ( QKeyEvent * keyEvent );
};

#endif // CSCENE_H
