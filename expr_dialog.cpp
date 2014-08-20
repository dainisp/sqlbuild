#include "expr_dialog.h"
#include "ui_expr_dialog.h"

expr_dialog::expr_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::expr_dialog)
{
    ui->setupUi(this);
}

expr_dialog::~expr_dialog()
{
    delete ui;
}

 int  expr_dialog::get_expr_params(QString * name,int * argcount,QString * expression  )
 {
expr_dialog  dialog;



if(name->isEmpty())
dialog.ui->nose->setText("Expr1");
else
    dialog.ui->nose->setText(* name);
dialog.ui->countb->setValue(*  argcount);

if(expression->isEmpty())
    dialog.ui->plainTextEdit->setPlainText("%1 + %2");
else
    dialog.ui->plainTextEdit->setPlainText(* expression);

int retval =  dialog.exec();

* name = dialog.ui->nose->text();
* argcount = dialog.ui->countb->value();
* expression = dialog.ui->plainTextEdit->toPlainText();

return retval;

  }

void expr_dialog::on_okb_clicked()
{
    setResult(QDialog::Accepted);
   accept();
}

void expr_dialog::on_cancelb_clicked()
{
    setResult(QDialog::Rejected);
    reject();
}
