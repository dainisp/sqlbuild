#ifndef CSCENE_H
#define CSCENE_H

#include <QGraphicsScene>
#include <QMenu>

#include "cexpritem.h"
#include "calink.h"
#include "crtableitem.h"

class catable;

class cscene : public QGraphicsScene
{
  Q_OBJECT
public:
    cscene( QObject * parent = 0);
// QList<ctableitem *>   usedtables;
//  QList<QGraphicsLineItem *>  usedlines;
//  QList<cexpritem * > usedexprs;

 QList<ctable * > * alltables;
void  publicate_keys();
int mode;
crtableitem *  addtable(ctable * atable,QString talias=QString());
//void addforeign(crtableitem * ftable,crtableitem * idtable);
//void addcustom(ctableitem * ftable,ctableitem * stable);
//void add_argum(int argind, cexpritem * expr, ctableitem * table);
QMenu * menu;
QPointF mousepos;
crtableitem * getselectedtable();
QString make_query();
QList<catable *> load_from_stream(QDataStream * stream);
QList<catable *> save_to_stream(QDataStream * stream);
void loadl_from_stream(QDataStream * stream, QList<catable *> tlist);
void savel_to_stream(QDataStream * stream, QList<catable *> tlist);
//void  removeat(ctableitem * ritem);
//void place_tables(QList < csertable * > sertables, QList<ctable *> alltables);
void add_link(catable *first, catable *second, int firstcol, int secondcol,
              int type = TTYPE_LINK , bool directed = false);
QString export_allt_to_graphml();
void arrange_tables();
crtableitem * find_primary_table(ctable * table);
bool add_selected_link();
//void findprimary(ctableitem * pitem);

private slots:

void performselection();

protected:

void keyPressEvent ( QKeyEvent * keyEvent );

void mousePressEvent(QGraphicsSceneMouseEvent *event);



};

#endif // CSCENE_H
