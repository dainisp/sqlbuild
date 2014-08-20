#ifndef EQU_DIALOG_H
#define EQU_DIALOG_H

#include <QDialog>

namespace Ui {
class equ_Dialog;
}

class equ_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit equ_Dialog(QWidget *parent = 0);
    ~equ_Dialog();
    static QString get_equation(QString equ = QString(),QWidget *parent = 0);
    QString s_get_equation();
private slots:
    void on_cancelb_clicked();

    void on_okb_clicked();

private:
    Ui::equ_Dialog *ui;
};

#endif // EQU_DIALOG_H
