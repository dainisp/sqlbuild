#ifndef CVIEW_H
#define CVIEW_H

#include <QGraphicsView>
 #include <QWheelEvent>


class cview : public QGraphicsView
{
    Q_OBJECT
public:
    explicit cview(QWidget *parent = 0);
qreal sizefact;

protected:
void wheelEvent ( QWheelEvent * event );
    
signals:
void scaled(qreal curscale);
public slots:

    
};

#endif // CVIEW_H
