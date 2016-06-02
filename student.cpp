#include "student.h"


int Student::getNum() const
{
    return num;
}

void Student::setNum(int newNum)
{
    num = newNum;
}

const QString& Student::getFio() const
{
    return fio;
}

QString Student::getNums() const
{
    return QString::number(num);
}

void Student::setFio(const QString &newFio )
{
    fio = newFio;
}

Student::Student()
{
    num = 0;
    fio = QString();
}

Student::operator QString() const
{
    return QString::number(num)+" "+fio;
}
