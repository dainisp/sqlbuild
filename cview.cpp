//#include <QMatrix>
#include "cview.h"

cview::cview(QWidget *parent) :
    QGraphicsView(parent)
{
sizefact=0.1;
}


void cview::wheelEvent ( QWheelEvent * event )
{
int dlt = event->delta();
QMatrix  matrix = this->matrix();
qreal ctrans =  matrix.m22();
qreal ntrans;
if(dlt < 0)ntrans =  ((qreal)((-dlt)/120) * (1-sizefact)) ;
else ntrans =   (((qreal)(dlt/120)) * (sizefact+1) );

//ctrans = ntrans*sizefact/ctrans;


scale(ntrans,ntrans);

  emit scaled(ntrans*ctrans);

}
