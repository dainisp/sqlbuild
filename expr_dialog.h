#ifndef EXPR_DIALOG_H
#define EXPR_DIALOG_H

#include <QDialog>

namespace Ui {
class expr_dialog;
}

class expr_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit expr_dialog(QWidget *parent = 0);
    static int get_expr_params(QString * name,int * argcount,QString * expression  );
    ~expr_dialog();

private slots:
    void on_okb_clicked();

    void on_cancelb_clicked();

private:
    Ui::expr_dialog *ui;
};

#endif // EXPR_DIALOG_H
