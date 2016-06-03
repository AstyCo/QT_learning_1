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
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<Student> studentList;


};


#endif // STUDENTMODEL_H

