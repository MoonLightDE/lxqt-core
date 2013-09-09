/* 
 * File:   LxqtMod_CoreConfig.cpp
 * Author: alexis
 * 
 * Created on 6 de septiembre de 2013, 16:15
 */

#include "LxqtMod_CoreConfig.h"


LxqtMod_CoreConfig::LxqtMod_CoreConfig() {
    this->setObjectName(getId());
}

LxqtMod_CoreConfig::LxqtMod_CoreConfig(const LxqtMod_CoreConfig& orig) {
}

LxqtMod_CoreConfig::~LxqtMod_CoreConfig() {
    delete m_ui;
}

QString LxqtMod_CoreConfig::getId() {
    return QString(this->metaObject()->className());
    //return "LxqtMod_CoreConfig";
}

void LxqtMod_CoreConfig::init(Core* core) {
    m_core = core;

    RazorSettings * settings = new RazorSettings("lxqt-core");
    m_ui = new BasicSettings(settings, core);
    m_ui->show();
    
}


QT_BEGIN_NAMESPACE
Q_EXPORT_PLUGIN2(LxqtMod_CoreConfig, LxqtMod_CoreConfig)
QT_END_NAMESPACE
