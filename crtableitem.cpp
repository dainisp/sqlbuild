#include "crtableitem.h"

crtableitem::crtableitem(ctable * itable, QString alias, QGraphicsItem * parent)
:catable( QStringList(itable->name) + itable->fields,alias  ,parent)
{
table = itable;
tablestring = alias;
}





/*
crtableitem * crtableitem::construct_table(ctable * itable,QGraphicsItem *parent = 0)
{
QStringList colnames;
//for(int i=0;i<itable->)


}
*/
