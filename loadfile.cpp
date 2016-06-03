#include "loadfile.h"
#include "ui_loadfile.h"

#include <iostream>

LoadFile::LoadFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFile),
    highlightedFile(QModelIndex())
{
    ui->setupUi(this);

    dirModel = new QFileSystemModel(this);
    QString rootPath = QApplication::applicationDirPath();

    dirModel->setRootPath(rootPath);


    dirModel->setFilter(QDir::NoDotAndDotDot |
                            QDir::AllDirs | QDir::Files);

    ui->treeView->setModel(dirModel);
    ui->treeView->setRootIndex(dirModel->index(QDir::currentPath()));

    connect(ui->treeView,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(fileChosen(const QModelIndex&)));
    connect(ui->treeView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(fileHighlighted(const QModelIndex&)));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(fileChosen()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
}

LoadFile::~LoadFile()
{
    delete ui;
}

void LoadFile::fileChosen()
{
    if(!highlightedFile.isValid())
    {

        done(1);//  If return needs?
        return;
    }
    fileChosen(highlightedFile);
}

void LoadFile::fileChosen(const QModelIndex &index)
{
    QString fname= dirModel->fileName(index);
    emit s_fileChosen(fname);
}

void LoadFile::fileHighlighted(const QModelIndex &index)
{
    highlightedFile = index;
    std::cout<<dirModel->fileName(index).toStdString()<<std::endl;
}
