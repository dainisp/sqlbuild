#include <QFileDialog>
#include <QMessageBox>
#include "dialog.h"
#include "ui_settings.h"




Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
     ui->setupUi(this);
}



Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_tfilb_clicked()
{
QString defdir;
QFileInfo finfo(ui->tablee->text());
if(finfo.exists())
   defdir = finfo.dir().absolutePath();

 QString nfile = QFileDialog::getOpenFileName(this,"File for table defs",defdir,"Xml files (*.xml)");
 if(!nfile.isEmpty())
     ui->tablee->setText(nfile);


}

void Dialog::on_kfilb_clicked()
{
    QString defdir;
    QFileInfo finfo(ui->keyfile->text());
    if(finfo.exists())
       defdir = finfo.dir().absolutePath();

     QString nfile = QFileDialog::getOpenFileName(this,"File for key defs",defdir,"Xml files (*.xml)");
     if(!nfile.isEmpty())
         ui->keyfile->setText(nfile);

}


 void Dialog::set_settings(QSettings * osettings)
 {
 settings =  osettings;
 settings->beginGroup("TableList");

ui->tablee->setText( settings->value("tablepath").toString());
 ui->keyfile->setText(settings->value("keypath").toString());
 int exres = this->exec();

if( exres == 1)
   {
    settings->setValue("tablepath",QVariant(ui->tablee->text()));
      settings->setValue("keypath",QVariant(ui->keyfile->text()));

}


 }
