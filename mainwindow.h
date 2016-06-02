#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include "student.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QList<Student> studentList;

private slots:
    void addRow();
    void loadStudents();
    void updateQTableWidget();
    void updateItemInfo(int,int);
    bool saveStudents(const QString& fName = "students_save.txt");
};

#endif // MAINWINDOW_H
