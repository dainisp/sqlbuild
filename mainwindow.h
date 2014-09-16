#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QListWidgetItem>
#include <QSettings>
#include <QFileDialog>
#include <cscene.h>

//#include "ctableitem.h"

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
QFileDialog * dialog;
   QSettings * settings;
   void save_settings();

   void save_field(QString filename);
   void load_field(QString filename);
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

   void on_settb_clicked();

   void on_exprb_clicked();

   void on_toolButton_3_clicked();

   void on_toolButton_2_clicked();

   void on_wh_expr_c_currentIndexChanged(const QString &arg1);

   void on_textrb_toggled(bool checked);

   void on_intrb_toggled(bool checked);

   void on_datrb_toggled(bool checked);

   void on_printb_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
