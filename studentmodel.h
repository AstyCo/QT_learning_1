#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include "QAbstractTableModel"

#include "student.h"


class StudentModel: public QAbstractTableModel
{
    Q_OBJECT

public:
    StudentModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent=QModelIndex()) const;
   // bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

public:
    // bool insertStudent(int row,const Student& studentItem,const QModelIndex& parent = QModelIndex());
    bool addStudent(const Student& studentItem);
    void clear();
    // Student readStudent(int row);

    QList<Student> studentList() const;
    void setStudentList(const QList<Student> &value);

private:
    QList<Student> m_studentList;


};


#endif // STUDENTMODEL_H

