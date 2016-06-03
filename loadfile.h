#ifndef LOADFILE_H
#define LOADFILE_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class LoadFile;
}

class LoadFile : public QDialog
{
    Q_OBJECT

public:
    explicit LoadFile(QWidget *parent = 0);
    ~LoadFile();

private:
    Ui::LoadFile *ui;
    QFileSystemModel *dirModel;
    QModelIndex highlightedFile;

signals:
    void s_fileChosen(const QString&);

private slots:
    void fileChosen();
    void fileChosen(const QModelIndex&);
    void fileHighlighted(const QModelIndex& index);
};

#endif // LOADFILE_H
