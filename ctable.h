#ifndef CTABLE_H
#define CTABLE_H
#include <QStringList>


struct ctable {

QStringList fields;
QString name;
QString alias;
int primary;
QList<int> fkeys;
QList<ctable * > fkeytables;
void setkeyfield(QString fname);
 static  int  findtablebyname(QString  tname,QList<ctable * > * alltables );
void setrkeyfield(QString fname, ctable *rtable);
QList<ctable * > findftables( QList<ctable *> *alltables);
int get_foreign_by_prim_table(ctable * prim_table);
};


#endif // CTABLE_H
