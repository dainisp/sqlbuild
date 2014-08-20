#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSettings>


namespace Ui {
class Dialog;
}


class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
   ~Dialog();

 QSettings * settings;

 void set_settings(QSettings * osettings);


signals:

public slots:

private slots:
    void on_tfilb_clicked();

    void on_kfilb_clicked();

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
