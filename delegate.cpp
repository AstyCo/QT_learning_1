#include "QSpinBox"


#include "delegate.h"


Delegate::Delegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *Delegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    int col = index.column();
    switch(col)
    {
    case 0:
    {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    case 1:
        return QItemDelegate::createEditor(parent, option, index);
    default:
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void Delegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QVariant value = index.model()->data(index, Qt::EditRole);
    int col = index.column();
    switch(col)
    {
    case 0:
    {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value.toInt());
        break;
    }
    case 1:
    default:
        QItemDelegate::setEditorData(editor, index);
        break;
    }
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    int col = index.column();
    QVariant value;
    if(col==0)
    {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void Delegate::updateEditorGeometry(QWidget *editor,
    const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    switch(col)
    {
    case 0:
        editor->setGeometry(option.rect);
        break;
    case 1:
    default:
        break;
    }
}
