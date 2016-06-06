#ifndef LOGINSQL_H
#define LOGINSQL_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class LoginSql;
}

class LoginSql : public QDialog
{
    Q_OBJECT

public:
    explicit LoginSql(QWidget *parent = 0);
    ~LoginSql();

    QString databaseName() const;
    QString userName() const;
    QString password() const;

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::LoginSql *ui;
};

#endif // LOGINSQL_H
