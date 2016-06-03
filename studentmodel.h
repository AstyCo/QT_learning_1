#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include "QAbstractTableModel"

#include "student.h"


class StudentModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    StudentModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QT::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<Student> studentList;


};


#endif // STUDENTMODEL_H

