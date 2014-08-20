#include "ctable.h"




int ctable::get_foreign_by_prim_table(ctable * prim_table)
{
 int prim_table_ind = fkeytables.indexOf(prim_table);
 if(prim_table_ind < 0)
     return prim_table_ind;
 return fkeys[prim_table_ind];

}


void  ctable::setkeyfield(QString fname)
{
    int kindex = fields.indexOf(fname );
    if(kindex >=0)primary =  kindex;

}


void ctable::setrkeyfield(QString fname,ctable * rtable )
{

    int kindex = fields.indexOf(fname );
    if(kindex >=0)
    {
        fkeys.append( kindex);
        fkeytables.append(rtable);

    }
}


  int  ctable::findtablebyname(QString  tname,QList<ctable * > * alltables )
{
    //   QList<ctable * > alltables;
    int i=0;
    for(i=0;i<alltables->count();i++)
    {
        if((*alltables)[i]->name == tname)break;
    }
    if(i==alltables->count())i=-1;
return i;
}

QList<ctable * > ctable::findftables(QList<ctable * > * alltables )


{
QList<ctable * > ftables;

for(int i=0;i<alltables->count();i++)
{
    ctable *  ftable = (*alltables)[i];
    if(ftable != this  )
  {
    int j;

   j = ftable->fkeytables.indexOf(this);

    if(j>=0)ftables.append(ftable);
}

}

return ftables;
}
