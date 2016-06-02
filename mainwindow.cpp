#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "student.h"

#include <QFile>
#include <QList>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>

#include "QDir"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->loadButton,SIGNAL(clicked()),this,SLOT(loadStudents()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveStudents()));
    connect(ui->newStudentButton,SIGNAL(clicked()),this,SLOT(addRow()));
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(updateItemInfo(int,int)));
}

void MainWindow::addRow()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}


void MainWindow::loadStudents()
{
    //QDir::toNativeSeparators();
    //QDir::separator();
    //QApplication::applicationFilePath();
    //QDir::homePath();
    QString fName("students.txt");
    QFile file(fName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        studentList.clear();
        while(!in.atEnd())
        {
            Student newStudent;
            QString line = in.readLine();
            QStringList words = line.split(" ");
            newStudent.setNum(words[0].toInt());
            newStudent.setFio(words[1]);
            studentList.append(newStudent);
            if(in.status() != QTextStream::Ok)
            {
                QMessageBox::critical(this,tr("Ошибка чтения файла"),tr("Read corrupted data"));
            }
        }
        file.close();
    }
    else
        QMessageBox::critical(this,tr("Ошибка открытия файла"),tr("File \"%1\" cannot be opened").arg(fName));
    updateQTableWidget();
}

void MainWindow::updateItemInfo(int rowNum,int colNum)
{
    QTableWidgetItem * changedItem = ui->tableWidget->item(rowNum,colNum);

    switch(colNum)
    {
    case 0:
        studentList[rowNum].setNum(changedItem->text().toInt());
        break;
    case 1:
        studentList[rowNum].setFio(changedItem->text());
        break;
    default:
        break;
    }
}


bool MainWindow::saveStudents(const QString &fName)
{
    QFile file(fName);



    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,tr("Ошибка открытия файла"),tr("File \"%1\" cannot be opened").arg(fName));
        return false;
    }

    QTextStream out(&file);

    for (int i = 0; i < studentList.size(); ++i)
    {
        out << studentList[i] << endl;
    }
    file.close();
    QMessageBox::information(this,tr(""),tr("File \"%1\" saved").arg(fName));
    return true;
}

void MainWindow::updateQTableWidget()
{

    ui->tableWidget->setRowCount(studentList.size());

    for (int i = 0; i < studentList.size(); ++i)
    {
        QList<QTableWidgetItem *>items;
        (items+=(new QTableWidgetItem(studentList[i].getNums())))
                +=(new QTableWidgetItem(studentList[i].getFio()));

        for(int j = 0; j<items.size(); ++j)
            ui->tableWidget->setItem(i,j,items[j]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
