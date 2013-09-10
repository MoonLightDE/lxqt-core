/* 
 * File:   Core.cpp
 * Author: alexis
 * 
 * Created on 3 de septiembre de 2013, 21:27
 */

#include <QDebug>
#include <QDir>
#include <qtxdg/xdgdirs.h>
#include <qt4/QtCore/qlist.h>

#include "Core.h"
#include "ModuleFactory.h"
#include "LxqtModuleInterface.h"
#include "lxqt-core-config.h"

Core::Core(RazorApplication* app) {
    m_app = app;
    QString basePath(INSTALL_PREFIX);
    m_moduleFactory = new ModuleFactory(basePath);

    // Load settings
    m_settings = new QSettings("lxqt", "Core");
}

Core::~Core() {
    delete m_moduleFactory;
    delete m_settings;
}

void Core::init() {
    // Load modules.
    int nmodules = m_settings->beginReadArray("STARUP_MODULES");
    for (int i = 0; i <= nmodules; i++) {
        m_settings->setArrayIndex(i);
        QString moduleName = m_settings->value("PluggingClass").toString();
        loadModule(moduleName);
    }
    m_settings->endArray();

    /*
    QDir autostart(XdgDirs::configHome() + "/autostart");
    qDebug() << "NOTICE: Loading descriptors from: " + autostart.path();

    foreach(QString entry, autostart.entryList()) {

        if (entry.endsWith(".desktop")) {
            ModuleDescriptor desc(autostart.absoluteFilePath(entry));
            if (!desc.getLibName().isNull()) {
                qDebug() << "NOTICE: Loading " + desc.getName() + " from " + desc.getLibName();
                LxqtModuleInterface* mod = loadModuleByClassName(desc.getClass());
                if (mod) {
                    qDebug() << "NOTICE: Starting: " + desc.getName();
                    mod->setObjectName(mod->getId());
                    mod->init(this);
                }
            }
        }
    } */
    if (getActiveModulesNames().isEmpty()) {
        LxqtModuleInterface* mod = loadModule("LxqtMod_CoreConfig");
        // load config module
        if (mod) {
            qDebug() << "NOTICE: Starting: LxqtMod_CoreConfig";
            mod->setObjectName("LxqtMod_CoreConfig");
            mod->init(this);
        }
    }

}

void Core::unloadModule(QString modName) {
    LxqtModuleInterface *child = this->findChild<LxqtModuleInterface*>(modName);
    if (child) {
        delete child;
        qDebug() << "Notice: " << modName << " unloaded";
    } else {
        qDebug() << "Notice: " << modName << " is not loaded";
    }

}

LxqtModuleInterface* Core::loadModule(QString className) {
    LxqtModuleInterface* mod = 0;
    QMap<QString, ModuleDescriptor*> m_aviableModules = m_moduleFactory->loadDescriptors();
    if (m_aviableModules.contains(className)) {
        mod = m_moduleFactory->loadModule(m_aviableModules[className]->getLibName());
        if (mod) {
            mod->setParent(this);
            mod->setObjectName(mod->getId());
        }
    }

    return mod;
}

LxqtModuleInterface* Core::getActiveModule(QString className) const {
    LxqtModuleInterface *child = this->findChild<LxqtModuleInterface*>(className);
    return child;
}

QStringList Core::getActiveModulesNames() const {
    QList<LxqtModuleInterface *> children = this->findChildren<LxqtModuleInterface*>(QString());
    QStringList modNames;

    foreach(LxqtModuleInterface * mod, children) {
        modNames.append(mod->getId());
    }
    return modNames;
}

QMap<QString, ModuleDescriptor*> Core::getAllDescriptors() const {
    return m_moduleFactory->loadDescriptors();
}

RazorApplication* Core::getRazorApp() const {
    return m_app;
}

void Core::setLoadOnStartUp(QString className) {
    QStringList startUpModules = getStartUpModules();
    if (startUpModules.contains(className) == QBool(false)) {
        startUpModules.append(className);
    }
    setStartUpModules(startUpModules);

}

void Core::unsetLoadOnStartUp(QString className) {
    QStringList startUpModules = getStartUpModules();
    if (startUpModules.contains(className) == QBool(true)) {
        startUpModules.removeAll(className);
    }
    setStartUpModules(startUpModules);
}

QStringList Core::getStartUpModules() {
    QStringList startUpModules;
    int nmodules = m_settings->beginReadArray("STARUP_MODULES");
    for (int i = 0; i < nmodules; i++) {
        m_settings->setArrayIndex(i);
        QString moduleName = m_settings->value("PluggingClass").toString();
        startUpModules.append(moduleName);
    }
    m_settings->endArray();

    return startUpModules;
}

void Core::setStartUpModules(QStringList startUpModules) {
    int nmodules = startUpModules.size();
    m_settings->beginWriteArray("STARUP_MODULES", startUpModules.size());

    for (int i = 0; i < nmodules; i++) {
        m_settings->setArrayIndex(i);
        m_settings->setValue("PluggingClass", startUpModules.at(i));
    }
    m_settings->endArray();
}

QSettings* Core::getGlobalSettings() const {
    return m_settings;
}