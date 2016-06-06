#include "loginsql.h"
#include "ui_loginsql.h"
#include <QDialogButtonBox>

LoginSql::LoginSql(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginSql)
{
    ui->setupUi(this);

    ui->editPassword->setEchoMode(QLineEdit::Password);

}

LoginSql::~LoginSql()
{
    delete ui;
}

QString LoginSql::databaseName() const
{
    return ui->editDatabase->text();
}

QString LoginSql::userName() const
{
    return ui->editUsername->text();
}

QString LoginSql::password() const
{
    return ui->editPassword->text();
}


void LoginSql::on_buttonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stButton = ui->buttonBox->standardButton(button);
    if(stButton == QDialogButtonBox::Ok)
        accept();
    else
        reject();
}
