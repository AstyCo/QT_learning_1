#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "QTableView"
#include "QTranslator"
#include "QApplication"
#include <QCloseEvent>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>


#include "student.h"
#include "studentmodel.h"
#include "delegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void installLocalTranslate(QApplication *);

private:
    Ui::MainWindow *ui;
    StudentModel *studModel;
    Delegate *customDelegate;

    QSqlDatabase pdb;

#define MODE 3
#if MODE == 1
    QSqlQueryModel *model;
#elif MODE == 2
    QSqlTableModel *model;
#elif MODE == 3
    QSqlRelationalTableModel *model;
#endif




    QTranslator m_translator; // contains the translations for this application
    QTranslator m_translatorQt; // contains the translations for qt
    QString m_currLang; // contains the currently loaded language
    QString m_langPath; // Path of language files. This is always fixed to /languages.

    const QString AppName;
    const QString driver;
    const QString database;

private:
    QList<Student> loadStudents(const QString &fname="students.txt");
    void uploadStudents(const QList<Student>&);

    void initSettings();
    void saveSettings();
    void loadSettings();
    void closeEvent(QCloseEvent*event);

    void loadDatabase();
    void saveDatabase();

private:


private slots:
    void addRow();
    void loadDefault();
    void loadDB(const QString&);
    void chooseFile();
    bool saveStudents(const QString& fName = "students_save.txt");
    void on_loadSqlButton_clicked();
    void on_saveSqlButton_clicked();
};

#endif // MAINWINDOW_H
