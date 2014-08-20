#include "equ_dialog.h"
#include "ui_equ_dialog.h"

equ_Dialog::equ_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::equ_Dialog)
{
    ui->setupUi(this);
}

equ_Dialog::~equ_Dialog()
{
    delete ui;
}


QString equ_Dialog::s_get_equation()
{
return ui->eque->text();
}

QString equ_Dialog::get_equation(QString equ, QWidget *parent)
 {
QString retstr;
  equ_Dialog * dlg = new equ_Dialog(parent);
  dlg->ui->eque->setText(equ);
//  dlg->setModal(true);
  dlg->exec();

  retstr = dlg->s_get_equation();
  delete dlg;
 return retstr;


 }

void equ_Dialog::on_cancelb_clicked()
{
    ui->eque->setText("");
     close();
}

void equ_Dialog::on_okb_clicked()
{
   close();
}
