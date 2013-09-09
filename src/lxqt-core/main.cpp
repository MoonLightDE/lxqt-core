/*
 * File:   main.cpp
 * Author: Alexis López Zubieta
 *
 * Created on 11 de junio de 2013, 13:19
 */

#include <QtGui/QApplication>
#include <QPluginLoader>
#include <QDir>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QAction>
#include <QVBoxLayout>

#include <iostream>
#include <string>

#include <razorqt/razorapplication.h>
#include "LxqtModuleInterface.h"
#include "ModuleFactory.h"


int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    RazorApplication app(argc, argv);

    Core core(&app);
    core.init();
    
    return app.exec();
}
