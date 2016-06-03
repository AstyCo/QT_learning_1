#include "mainwindow.h"
#include <QApplication>
#include "QTextCodec"
#include "QTranslator"
#include "QLibraryInfo"

#include <iostream>


void installLocalTranslate(QTranslator *translator,QApplication *app)
{
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
    QString langPath = QApplication::applicationDirPath();
    std::clog<<langPath.toStdString()<<std::endl;
    langPath.append("/");
    QString currLang = defaultLocale;
    std::clog<<currLang.toStdString()<<std::endl;
    currLang.truncate(defaultLocale.lastIndexOf('_'));
    std::clog<<currLang.toStdString()<<std::endl;
    QLocale locale=QLocale(currLang);
    QLocale::setDefault(locale);

    QString fname = QString("%2app_%1").arg(defaultLocale).arg(langPath);
    std::clog<<fname.toStdString()<<std::endl;
    if(translator->load(fname))
        std::clog<<"loaded fine"<<std::endl;
    app->installTranslator(translator);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    installLocalTranslate(&translator,&app);

    MainWindow w;

    w.show();

    //QObject::tr("f")

    return app.exec();
}
