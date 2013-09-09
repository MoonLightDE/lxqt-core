/* 
 * File:   DefaultModule.cpp
 * Author: alexis
 * 
 * Created on 31 de agosto de 2013, 21:09
 */

#include "LxqtMod_Default.h"

#include <iostream>

LxqtMod_Default::LxqtMod_Default() {
}

LxqtMod_Default::LxqtMod_Default(const LxqtMod_Default& orig) {
}

LxqtMod_Default::~LxqtMod_Default() {
}

void LxqtMod_Default::init(Core *core) {
    m_core = core;
    using namespace std;
    cout << "The module is up and running!!!" << endl;
}

QString LxqtMod_Default::getId() {
    return QString("DefaultModule");
}

QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(LxqtMod_Default, LxqtMod_Default)
QT_END_NAMESPACE