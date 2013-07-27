#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QListWidgetItem>
 #include <cscene.h>

#include "ctableitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   cscene scene;
   QList<ctable * > alltables;
   bool mustsave;
   QString tpath;
     QString kpath;
   void save_settings();

   void save_field(QString filename);
   QList < csertable * >  load_field(QString filename);
   void import_tables(QString afname = QString(),bool interactive = false);
    void import_keys(QString afname = QString());
     int  findtablebyname(QString  tname);

     void addlinkedtables(int tind);
     void addlinkedtablesp(  ctable * curtab );
      // void addtable(ctable * atable);

private slots:
   void on_pushButton_clicked();
   void onviewscaled(qreal cursize);

   void on_pushButton_2_clicked();
   void on_list_doubleClicked ( const QModelIndex & index );

   void on_pushButton_3_clicked();

   void on_lineEdit_textChanged(const QString &arg1);

   void on_parseb_clicked();

   void on_appendfb_clicked();

   void on_flistb_clicked();

   void on_foreignl_itemDoubleClicked(QListWidgetItem *item);



   void on_savefb_clicked();

   void on_loadfb_clicked();

   void on_copyb_clicked();

   void on_addprimb_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
