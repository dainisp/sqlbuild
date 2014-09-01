#include <QFileDialog>
#include <QDomDocument>
#include <QMessageBox>
#include <QSettings>
#include "dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "catable.h"
#include "crtableitem.h"
//#include "sqlparser.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mustsave = false;
    ui->splitter->setStretchFactor(0,0);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter_2->setStretchFactor(0,0);
    ui->splitter_2->setStretchFactor(1,1);
    scene.alltables = &alltables;
ui->laukums->setScene(&scene);
  ui->laukums->scale(0.8,0.8);

  //connect(ui->laukums,SIGNAL(scaled(qreal)),this,SLOT(onviewscaled(qreal)));
  ui->laukums->setAcceptDrops(true);

 QSettings settings("Dainis Soft", "SQLBuild");
  settings.beginGroup("TableList");
 tpath = settings.value("tablepath").toString();
   kpath = settings.value("keypath").toString();
     settings.endGroup();
    if(!tpath.isEmpty() && !kpath.isEmpty() )
  {
   import_tables(tpath);
   import_keys(kpath);

    }

if(QApplication::arguments().count()>1)
{
load_field(QApplication::arguments()[1]);



}

}



  void  MainWindow::load_field(QString filename)
  {



    QFile infile(filename);
    if(  infile.open(QIODevice::ReadOnly ))
   {
    QDataStream instream(&infile);
QList<catable *> tlist =  scene.load_from_stream(&instream);
scene.loadl_from_stream(&instream,tlist);


   infile.close();

    }

  }






void MainWindow::save_field(QString filename)
{
    QFile outfile(filename);

    if(  outfile.open(QIODevice::WriteOnly  ))
   {
    QDataStream outstream(&outfile);

    QList<  catable * > tlist = scene.save_to_stream(&outstream);
    scene.savel_to_stream(&outstream,tlist);
    outfile.close();
        }
}









void MainWindow::save_settings()
{

    if(mustsave)
   {
        QSettings settings("Dainis Soft", "SQLBuild");
         settings.beginGroup("TableList");
         settings.setValue("tablepath", tpath);
         settings.setValue("keypath", kpath );
        settings.endGroup();

    }

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    import_tables(QString(),true);
    import_keys();


}



void MainWindow::onviewscaled(qreal cursize)
{

    this->statusBar()->showMessage(QString("Resized %1").arg(cursize),4000);


}


void MainWindow::import_tables(QString afname, bool interactive)
{
QString fname;
    if(afname.isEmpty())
    {
    fname = QFileDialog::getOpenFileName ( this, "Import tables" );
//"/home/dainis/csourc/sqlbuild-build-Desktop-Debug/tables.xml"
}
 else  fname =  afname;

    if(!fname.isEmpty())
    {
        QFile indoc(fname);
      QDomDocument doc;
      if(  doc.setContent(&indoc,false))
      {
QDomNodeList  tlist = doc.elementsByTagName("table");

QString tname;
ctable * table;

ui->tlistv->clear();
if(alltables.count())
  {
    foreach(ctable * table,alltables)
        delete table;
alltables.clear();
}
for(int i=0;i<tlist.count();i++)
{

  QDomElement tableelem = tlist.item(i).toElement().elementsByTagName("name").item(0).toElement();
    QDomElement aliaselem = tlist.item(i).toElement().elementsByTagName("alias").item(0).toElement();
       QDomElement fieldelem = tlist.item(i).toElement().elementsByTagName("field").item(0).toElement();

    if(tname != tableelem.text() )
 {

  tname = tableelem.text();
 table = new ctable;
  alltables.append(table);
table->name = tname;
if(!aliaselem.isNull())table->alias = aliaselem.text();
ui->tlistv->addItem(tname);

    }
   table->fields.append( fieldelem.text());

   // table->fields.append(tlist.item(i).toElement().elementsByTagName("field").text() );

}

if(tpath.isEmpty()   )
{
mustsave = true;
tpath = fname;

}
else
   {
    if( interactive && QMessageBox::question ( this, "Choose variant" , "Save path to config?", QMessageBox::Yes | QMessageBox::No ) == QMessageBox::Yes )
    {
        mustsave = true;
        tpath = fname;

    }
}
      }

    }

}


 void MainWindow::import_keys(QString afname )
 {

     QString fname;
         if(afname.isEmpty())
         {
         fname = QFileDialog::getOpenFileName ( this, "Import tables" );
     //"/home/dainis/csourc/sqlbuild-build-Desktop-Debug/tables.xml"
     }
      else  fname =  afname;

         if(!fname.isEmpty())
         {
             QFile indoc(fname);
           QDomDocument doc;
           if(  doc.setContent(&indoc,false))
           {
     QDomNodeList  tlist = doc.elementsByTagName("key");

     QString tname;
     ctable * table;
int tind = -1;

     for(int i=0;i<tlist.count();i++)
     {

         QDomElement tableelem = tlist.item(i).toElement().elementsByTagName("table").item(0).toElement();
             QDomElement rtableelem = tlist.item(i).toElement().elementsByTagName("remote_table").item(0).toElement();
          //     QDomElement rfieldeelem = tlist.item(i).toElement().elementsByTagName("remote_field").item(0).toElement();
                QDomElement kfieldeelem = tlist.item(i).toElement().elementsByTagName("keyfield").item(0).toElement();

         if(tname != tableelem.text() )
      {

       tname = tableelem.text();

      tind = findtablebyname(tname);


         }
       if(tind>=0)
        {

           table = alltables[tind];
         //  table->fields.append( tlist.item(i).nextSibling().toElement().text());
           if(rtableelem.isNull())
           {
               table->setkeyfield(kfieldeelem.text());

           }

         else

       {
         int rtind = findtablebyname(rtableelem.text());
         if(rtind>=0)
         {
             ctable * rtable = alltables[rtind];
       table->setrkeyfield(kfieldeelem.text(),rtable);
         }

           }

       }


       }

     if(kpath.isEmpty() || mustsave  )
     {
     mustsave = true;
     kpath = fname;

     }


     }


           }

         }





     int  MainWindow::findtablebyname(QString  tname)
     {
         //   QList<ctable * > alltables;
         int i=0;
         for(i=0;i<alltables.count();i++)
         {
             if(alltables[i]->name == tname)break;
         }
         if(i==alltables.count())i=-1;
return i;
     }


void MainWindow::on_pushButton_2_clicked()
{


 scene.publicate_keys();


}



void MainWindow::addlinkedtablesp(  ctable * curtab )
{

    for(int i = 0;i<curtab->fkeys.count();i++)
{
        scene.addtable(curtab->fkeytables[i]);


    }
QList<ctable * >  flist = curtab->findftables(&alltables);

for(int i=0;i<flist.count();i++)scene.addtable(flist[i]);


}





 void MainWindow::addlinkedtables(int tind)
 {
  ctable * curtab =   alltables[tind];

     for(int i = 0;i<curtab->fkeys.count();i++)
 {
         scene.addtable(curtab->fkeytables[i]);


     }
QList<ctable * >  flist = curtab->findftables(&alltables);

for(int i=0;i<flist.count();i++)scene.addtable(flist[i]);


 }


/*
 void MainWindow::addtable(ctable * atable)
 {

     ctableitem * titem =  new ctableitem(atable);
     QString alias = titem->table->alias;
     if(alias.isEmpty())alias=titem->table->name;
    int aliascount=0;
     for(int i=0;i<scene.usedtables.count();i++)
         if(scene.usedtables[i]->alias.startsWith(alias))aliascount++;
     if(aliascount>0)alias+=QString::number(aliascount );
       titem->alias = alias;
     scene.usedtables.append( titem );
     scene.addItem( titem);




 }
*/




  void MainWindow::on_list_doubleClicked ( const QModelIndex & index )
  {
      /*
  Qt::KeyboardModifiers modifiers  =   QApplication::queryKeyboardModifiers ();
  if(modifiers & Qt::ShiftModifier)
  {

      crtableitem * table = new crtableitem(alltables[index.row()]);
      scene.addItem(table);
  }
  else
      */
 scene.addtable(alltables[index.row()]);

  }


void MainWindow::on_pushButton_3_clicked()
{

    ui->queryt->setPlainText(scene.make_query());

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
QList<QListWidgetItem *> itlst = ui->tlistv->findItems(arg1, Qt::MatchStartsWith);
if(itlst.count())
 {
ui->tlistv->scrollToItem(itlst[0]);

}


}

int do_parse(QString inputstr, cscene * scene,   QList<ctable * > * tables );

void MainWindow::on_parseb_clicked()
{
QString query = ui->queryt->toPlainText().trimmed();
if(query.left(1) != ";")
    query.append(';');
query = "EXEC SQL\n" + query;

int pres = do_parse(query, &scene,&alltables);
if(pres==1)QMessageBox::warning ( this, "SQLbuild", "Query parse error!");
if(pres==2)QMessageBox::warning ( this, "SQLbuild", "Query parsed, but selected table not in list");

}

void MainWindow::on_appendfb_clicked()
{
// usedtables
crtableitem *  seltable = scene.getselectedtable();
        if(seltable)
         addlinkedtablesp(  seltable->table );

}

void MainWindow::on_flistb_clicked()
{

crtableitem *  seltable = scene.getselectedtable();
if (seltable)
{
ui->foreignl->clear();
 QList<ctable * >  flist = seltable->table->findftables(&alltables);
 foreach(ctable * ftable,flist )
 ui->foreignl->addItem(ftable->name);


}
}

void MainWindow::on_foreignl_itemDoubleClicked(QListWidgetItem *item)
{
    ctable * ftable = alltables[ ctable::findtablebyname(item->text(),&alltables)];
    scene.addtable(ftable);
}


void MainWindow::on_savefb_clicked()
{
    QString fname = QFileDialog::getSaveFileName ( this, QString("Save query"),QString(),QString("Sqlbuild (*.sqb)"));
    if(!fname.isEmpty())
     {
save_field(fname);




    }

}

void MainWindow::on_loadfb_clicked()
{
    QString fname = QFileDialog::getOpenFileName ( this, "Open query" ,QString(),QString("Sqlbuild (*.sqb)"));
    if(!fname.isEmpty())
     {

      load_field(fname) ;
    //scene.place_tables(sertable,alltables);



    }



}

void MainWindow::on_copyb_clicked()
{

    crtableitem *  seltable = scene.getselectedtable();
    scene.addtable(seltable->table);
}

void MainWindow::on_addprimb_clicked()
{
    crtableitem *  seltable = scene.getselectedtable();
    if (seltable)
    {
    ui->foreignl->clear();

     foreach( ctable *  ftable,seltable->table->fkeytables )
     ui->foreignl->addItem(ftable->name);


    }

}

void MainWindow::on_settb_clicked()
{
  Dialog dialog;
    QSettings settings("Dainis Soft", "SQLBuild");

    dialog.set_settings(&settings);

}



void MainWindow::on_exprb_clicked()
{


    if(scene.mode)
    scene.mode = 0;
  else
      scene.mode = 1;

/*

    QFile outf("graph.xml");
    if(outf.open(QIODevice::WriteOnly))
  {
   outf.write(scene.export_allt_to_graphml().toUtf8());
    outf.close();

    }

*/
}


void MainWindow::on_toolButton_3_clicked()
{
    QStringList colnames;
    colnames << "HEADER" << "COL1"  << "COL2" << "COL3";

    catable * tbl = new catable(colnames) ;
    int ttp = tbl->type();

    scene.addItem(new catable(colnames) );
}

void MainWindow::on_toolButton_2_clicked()
{
scene.add_selected_link();
}
