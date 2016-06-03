#include "studentModel.h"
#include "student.h"

#include "Qt"

StudentModel::StudentModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

int StudentModel::rowCount(const QModelIndex &parent) const
{
    return studentList.size();
}

int StudentModel::columnCount(const QModelIndex &parent) const
{
    return Student::STUD_FIELD_CNT;
}

bool StudentModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);

    for(int i=0 ; i<count ; ++i)
        studentList.insert(row,"");

    endInsertRows();
    return true;
}

bool StudentModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent,row,row+count-1);

    for(int i=0; i<count ; ++i)
        studentList.removeAt(row);

    endRemoveRows();
    return true;
}

QVariant StudentModel::data(const QModelIndex &index, int role) const
{
    int row = index.row(),
        col = index.column();

    if(!index.isValid())
        return false;

    if(role == Qt::DisplayRole)
    {
        switch(col)
        {
        case 0:
            return studentList.at(row).getNum();
        case 1:
            return studentList.at(row).getFio();
        default:
            return QVariant();
        }
    }
    return QVariant();
}

bool StudentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row(),
        col = index.column();

    if(!index.isValid())
        return false;

    if(role == Qt::EditRole)
    {
        switch(col)
        {
        case 0:
            studentList.at(row).setNum(value.toInt());
            break;
        case 1:
            studentList.at(row).setFio(value.toString());
            break;
        default:
            return false;
        }
        emit dataChanged(index,index);
        return true;
    }
    return false;
}

QVariant StudentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
            switch(section)
            {
            case 0:
                return tr("Номер зачетки");
            case 1:
                return tr("Фамилия");
            default:
                return QVariant();
            }
        else if(section)
            return QString::number(section);
        else
            return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags StudentModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable ;
}
