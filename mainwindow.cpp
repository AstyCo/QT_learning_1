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
#include <QSettings>
#include <QCloseEvent>
#include <QtSql>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>

#include "studentmodel.h"
#include "loadfile.h"
#include "loginsql.h"
#include "QDebug"
#include "editablesqlmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    AppName("Students Demo"),
    driver("QPSQL"),
    database("mydb")
{

    ui->setupUi(this);


    customDelegate = new Delegate(this);
    studModel = new StudentModel(this);
    ui->tableView->setModel(studModel);
    ui->tableView->setItemDelegate(customDelegate);

    //loadDatabase();

    connect(ui->loadButton,SIGNAL(clicked()),this,SLOT(chooseFile()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(saveStudents()));
    connect(ui->newStudentButton,SIGNAL(clicked()),this,SLOT(addRow()));
    //connect(ui->loadSqlButton,SIGNAL(clicked()),this,SLOT(on_loadSqlButton_clicked()));
    //connect(ui->saveSqlButton,SIGNAL(clicked()),this,SLOT(on_saveSqlButton_clicked()));


    //initSettings();
    loadSettings();

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

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::List);

    if(dialog.exec())
    {
        QStringList fileNames = dialog.selectedFiles();
        if(!fileNames.isEmpty())
        {
            qDebug()<<fileNames;
            loadDB(fileNames[0]);
        }
    }

//    QString fileName = QFileDialog::getOpenFileName(this,
//                                tr("QFileDialog::getOpenFileName()"));
//    if (!fileName.isEmpty())
//        qDebug()<< fileName;
}

void MainWindow::uploadStudents(const QList<Student>& slist)
{
    for(int i=0;i<slist.size();++i)
        studModel->addStudent(slist[i]);
}

void MainWindow::initSettings()
{
    QCoreApplication::setOrganizationName("MyOrg");
    //QCoreApplication::setOrganizationDomain("myDomain.com");
    QCoreApplication::setApplicationName("MyStudents");

    qDebug()<<"Settings initiation completed";
}

void MainWindow::saveSettings()
{
    QSettings mwSettings("GEOMIR","MyStudents");

    mwSettings.beginGroup("MainWindow");

    mwSettings.setValue("size", size());
    mwSettings.setValue("pos", pos());

    mwSettings.endGroup();

}

void MainWindow::loadSettings()
{
    QSettings mwSettings("GEOMIR","MyStudents");

    mwSettings.beginGroup("MainWindow");


    resize(mwSettings.value("size", QSize(400,400)).toSize());
    move(mwSettings.value("pos",QPoint(700,300)).toPoint());

    mwSettings.endGroup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, AppName,
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            saveSettings();
            event->accept();
        }
}

void MainWindow::loadDatabase()
{
    pdb = QSqlDatabase::addDatabase(driver);
    pdb.setDatabaseName(database);

    LoginSql dlg(this);

    if(dlg.exec() != QDialog::Accepted)
    {
        //QSqlDatabase::removeDatabase(pdb.connectionName());
        return;
    }

    if (pdb.open(dlg.userName(),dlg.password())) {
        qDebug() << "DataBase Opened!";
#define MODE 3
#if MODE == 1
        model = new EditableSqlModel(this);
        model->setQuery("select * from Students1");
        if (model->lastError().isValid())
            qDebug() << model->lastError();
#elif MODE == 2
        model = new QSqlTableModel(this);
//        model->setTable("Students1");
//        model->setTable("studentsandlessons");
        model->setTable("studentlections");
        if (model->lastError().isValid())
            qDebug() << model->lastError();
        model->select();
#elif MODE == 3
        model = new QSqlRelationalTableModel(this);
        model->setTable("StudentLections");
        if (model->lastError().isValid())
            qDebug() << model->lastError();

        model->setRelation(0,QSqlRelation("Students1","id","fio"));
        model->setRelation(1,QSqlRelation("Lections","LectionId","LectionName"));

        if (model->lastError().isValid())
            qDebug() << model->lastError();



        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Lesson"));

        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

        model->select();

#endif

        ui->tableView->setModel(model);
        ui->tableView->show();

        //pdb.close();
    }
    else
    {
        qDebug() << pdb.lastError().text();
    }
}

void MainWindow::saveDatabase()
{
#if DEBUG != 1
    model->submitAll();
#endif
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
            ui->tableView->setModel(studModel);
            ui->tableView->setItemDelegate(customDelegate);
        }
        file.close();
    }
    else
        QMessageBox::critical(this,tr("Open error"),tr("File %1 cannot be opened").arg(fName));
    //studModel->setStudentList(data);
    return data;
}

bool MainWindow::saveStudents(const QString &fName)
{
    QFile file(fName);



    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,tr("Open error"),tr("File %1 cannot be opened").arg(fName));
        return false;
    }

    QTextStream out(&file);
    QList<Student> studentList=studModel->studentList();

    for (int i = 0; i < studentList.size(); ++i)
    {
        out << studentList[i] << endl;
    }
    file.close();
    QMessageBox::information(this,tr(""),tr("File %1 saved").arg(fName));
    return true;
}


MainWindow::~MainWindow()
{

    saveSettings();

    delete customDelegate;
    delete studModel;
    delete ui;
}


void MainWindow::installLocalTranslate(QApplication *app)
{
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
//    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
    m_langPath = QApplication::applicationDirPath();

    m_langPath.append("/languages");
    m_currLang = defaultLocale;

    m_currLang.truncate(defaultLocale.lastIndexOf('_'));

    QLocale locale=QLocale(m_currLang);
    QLocale::setDefault(locale);
    QString fname = QString("%2app_%1").arg(defaultLocale).arg(m_langPath);
    app->installTranslator(&m_translator);
}

void MainWindow::on_loadSqlButton_clicked()
{
    loadDatabase();
}

void MainWindow::on_saveSqlButton_clicked()
{
    saveDatabase();
}
