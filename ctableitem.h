#ifndef CTABLEITEM_H
#define CTABLEITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
 #include <QGraphicsRectItem>
 #include <QKeyEvent>


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

};


struct csertable
{
    QString alias;
    int primary;
  QPointF position;
int tindex;
int iindex;
 QList<int> outputfields;
 QList<int> keyfields;
     QList<int > usedkeys;
};





class ctableitem : public QGraphicsItemGroup
{
public:
    ctableitem(QGraphicsItem * parent = 0);
    ctableitem(ctable * itable,QGraphicsItem * parent = 0);
    ctable * table;
    QString alias;
    ctableitem *  primary;
    QGraphicsRectItem * namerect;
    QList<ctableitem *  > usedkeys;
    QList<int> keyfields;
 QList<int> outputfields;
QList<QGraphicsRectItem * > outputrects;
 QGraphicsLineItem * primline;
 QList<QGraphicsLineItem *> keylines;
 //QStringList outputaliases;
    QColor hcolor;
   QColor scolor;
    QColor outcolor;
    qreal defaultwidth;
    qreal defaultrowhight;
    int findforeign(ctableitem * ftable);
    void initdefault();
    csertable gensertable( QList<ctableitem *>   usedtables, QList<ctable * > alltables);
     int findforeignl( QGraphicsItem * fline);
    int findforeignind(int index);
void removeprimary();
void removeforeign(int keyind);

    void removelinks();
     void removelinksp();
protected:
   QPointF dpressed;
    QPointF ppressed;
void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
void mousePressEvent ( QGraphicsSceneMouseEvent * event );
void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * event );
void keyPressEvent ( QKeyEvent * event );

};

#endif // CTABLEITEM_H
