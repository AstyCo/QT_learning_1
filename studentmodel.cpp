#include "studentModel.h"
#include "student.h"

#include "Qt"

StudentModel::StudentModel(QObject *parent)
    :QAbstractTableModel(parent)
{
    m_studentList.clear();
}

int StudentModel::rowCount(const QModelIndex &parent) const
{
    return m_studentList.size();
}

int StudentModel::columnCount(const QModelIndex &parent) const
{
    return Student::STUD_FIELD_CNT;
}

//bool StudentModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(parent,row,row+count-1);

//    for(int i=0 ; i<count ; ++i)
//        studentList.insert(row,"");

//    endInsertRows();
//    return true;
//}

bool StudentModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent,row,row+count-1);

    for(int i=0; i<count ; ++i)
        m_studentList.removeAt(row);

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
            return m_studentList.at(row).getNum();
        case 1:
            return m_studentList.at(row).getFio();
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
            m_studentList[row].setNum(value.toInt());
            break;
        case 1:
            m_studentList[row].setFio(value.toString());
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
                return tr("id");
            case 1:
                return tr("fio");
            default:
                return QVariant();
            }
        else
            return QString::number(section);
    }
    return QVariant();
}

Qt::ItemFlags StudentModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable ;
}

bool StudentModel::addStudent(const Student &studentItem)
{
    beginInsertRows(QModelIndex(),m_studentList.size(),m_studentList.size());
    m_studentList.append(studentItem);
    endInsertRows();
    return true;
}

void StudentModel::clear()
{
    if(!m_studentList.empty())
        removeRows(0,m_studentList.size());
    m_studentList.clear();
}

//bool StudentModel::insertStudent(int row, const Student &studentItem,const QModelIndex &parent)
//{
//    if(!insertRows(row,1,parent))
//        return false;
//    int num = studentItem.getNum();
//    QString fio = studentItem.getFio();\

//    QModelIndex numIndex=parent.child(row,0),
//           fioIndex=parent.child(row,1);


//    if(!setData(numIndex,num,Qt::DisplayRole))
//    {
//        removeRows(row,1,parent);
//        return false;
//    }
//    {
//        setData(fioIndex,fio,Qt::DisplayRole);

//    return true;
//    }
//}

QList<Student> StudentModel::studentList() const
{
    return m_studentList;
}

void StudentModel::setStudentList(const QList<Student> &value)
{
    m_studentList = value;
    reset();
}

