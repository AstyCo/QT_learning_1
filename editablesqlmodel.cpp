#include "editablesqlmodel.h"

EditableSqlModel::EditableSqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{

}

Qt::ItemFlags EditableSqlModel::flags(
        const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 0 || index.column() == 1)
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool EditableSqlModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.column() < 0 || index.column() > 1)
        return false;

    if(role == Qt::EditRole)
    {
        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
        int id = data(primaryKeyIndex).toInt();

        clear();

        bool ok;
        if (index.column() == 1) {
            ok = setFio(id, value.toString());
        } else {
            ok = setId(id, value.toInt());
        }
        refresh();
        return ok;
    }
    return false;
}

void EditableSqlModel::refresh()
{
    setQuery("select * from \"Students1\"");
}


bool EditableSqlModel::setFio(int personId, const QString &fio)
{
    QSqlQuery query;
    query.prepare("update \"Students1\" set fio = ? where id = ?");
    query.addBindValue(fio);
    query.addBindValue(personId);
    return query.exec();
}


bool EditableSqlModel::setId(int personId, int newId)
{
    QSqlQuery query;
    query.prepare("update \"Students1\" set id = ? where id = ?");
    query.addBindValue(newId);
    query.addBindValue(personId);
    return query.exec();
}
