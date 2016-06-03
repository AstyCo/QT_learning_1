#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "student.h"

#include <QFile>
#include <QList>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>
#include "QDir"
#include "QFileDialog"

#include <iostream>

#include "studentmodel.h"
#include "loadfile.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    customDelegate = new Delegate(this);
    studModel = new StudentModel(this);
    ui->tableView->setModel(studModel);
    ui->tableView->setItemDelegate(customDelegate);

    connect(ui->loadButton,SIGNAL(clicked()),this,SLOT(chooseFile()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveStudents()));
    connect(ui->newStudentButton,SIGNAL(clicked()),this,SLOT(addRow()));
}

void MainWindow::addRow()
{
    studModel->addStudent(Student());
}

void MainWindow::loadDefault()
{
    studModel->clear();

    uploadStudents(loadStudents());
}

void MainWindow::loadDB(const QString &fname)
{
    studModel->clear();

    uploadStudents(loadStudents(fname));
}

void MainWindow::chooseFile()
{
//    LoadFile dlg(this);

//    connect(&dlg,SIGNAL(s_fileChosen(QString)),this,SLOT(loadDB(QString)));

//    if(dlg.exec()==QDialog::Accepted)
//    {
//    }


    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("QFileDialog::getOpenFileName()"));
    if (!fileName.isEmpty())
        qDebug()<< fileName;
}

void MainWindow::uploadStudents(const QList<Student>& slist)
{
    for(int i=0;i<slist.size();++i)
        studModel->addStudent(slist[i]);
}


QList<Student> MainWindow::loadStudents(const QString &fName)
{
    //QDir::toNativeSeparators();
    //QDir::separator();
    //QApplication::applicationFilePath();
    //QDir::homePath();
    QList<Student> data;
    QFile file(fName);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            Student s;
            QString line = in.readLine();
            QStringList words = line.split(" ");

            s.setFio(words[1]);
            s.setNum(words[0].toInt());

            data.append(s);

            if(in.status() != QTextStream::Ok)
            {
                QMessageBox::critical(this,tr("Reading error"),tr("Read corrupted data"));
            }
        }
        file.close();
    }
    else
        QMessageBox::critical(this,tr("Open error"),tr("File \"%1\" cannot be opened").arg(fName));
    //studModel->setStudentList(data);
    return data;
}

bool MainWindow::saveStudents(const QString &fName)
{
    QFile file(fName);



    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,tr("Open error"),tr("File \"%1\" cannot be opened").arg(fName));
        return false;
    }

    QTextStream out(&file);
    QList<Student> studentList=studModel->studentList();

    for (int i = 0; i < studentList.size(); ++i)
    {
        out << studentList[i] << endl;
    }
    file.close();
    QMessageBox::information(this,tr(""),tr("File \"%1\" saved").arg(fName));
    return true;
}


MainWindow::~MainWindow()
{
    delete customDelegate;
    delete studModel;
    delete ui;
}


void MainWindow::installLocalTranslate(QApplication *app)
{
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
//    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
    m_langPath = QApplication::applicationDirPath();
    std::clog<<m_langPath.toStdString()<<std::endl;
    m_langPath.append("/languages");
    m_currLang = defaultLocale;
    std::clog<<m_currLang.toStdString()<<std::endl;
    m_currLang.truncate(defaultLocale.lastIndexOf('_'));
    std::clog<<m_currLang.toStdString()<<std::endl;
    QLocale locale=QLocale(m_currLang);
    QLocale::setDefault(locale);

    QString fname = QString("%2app_%1").arg(defaultLocale).arg(m_langPath);
    if(!m_translator.load(fname))
        std::clog<<"loaded fine"<<std::endl;
    app->installTranslator(&m_translator);
}
