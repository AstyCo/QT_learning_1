#ifndef EDITABLESQLMODEL_H
#define EDITABLESQLMODEL_H


#include <QSqlQueryModel>
#include <QSqlQuery>

class EditableSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    EditableSqlModel(QObject *parent = 0);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    bool setId(int personId, int newId);
    bool setFio(int personId, const QString &lastName);
    void refresh();
};

#endif // EDITABLESQLMODEL_H
