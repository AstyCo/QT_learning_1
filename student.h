#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
private:
    int num;
    QString fio;
public:
    Student();
    int getNum() const;
    QString getNums() const;
    void setNum(int num);
    const QString& getFio() const;
    void setFio(const QString &fio);
    operator QString () const;
};

#endif // STUDENT_H
