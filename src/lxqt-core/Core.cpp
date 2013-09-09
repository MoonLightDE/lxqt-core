/* 
 * File:   Core.cpp
 * Author: alexis
 * 
 * Created on 3 de septiembre de 2013, 21:27
 */

#include <QDebug>
#include <QDir>
#include <qtxdg/xdgdirs.h>

#include "Core.h"
#include "ModuleFactory.h"
#include "LxqtModuleInterface.h"
#include "lxqt-core-config.h"

Core::Core(RazorApplication* app) {
    m_app = app;
    QString basePath(INSTALL_PREFIX);
    m_moduleFactory = new ModuleFactory( basePath + "/lib/lxqt-core/modules", basePath + "/share/lxqt-core/descriptors");

    // Load settings
    m_settings = new QSettings("lxqt", "Core");

}

Core::Core(const Core& orig) {
}

Core::~Core() {
    delete m_moduleFactory;
    delete m_settings;
}

void Core::init() {
    // Load modules.
    QDir autostart(XdgDirs::configHome() + "/lxqt/core");

    qDebug() << "NOTICE: Loading descriptors from: " + autostart.path();

    foreach(QString entry, autostart.entryList()) {

        if (entry.endsWith(".desktop")) {
            ModuleDescriptor desc(autostart.absoluteFilePath(entry));
            if (!desc.getLibName().isNull()) {
                qDebug() << "NOTICE: Loading " + desc.getName() + " from " + desc.getLibName();
                LxqtModuleInterface* mod = loadModuleByLibName(desc.getLibName());
                if (mod) {
                    qDebug() << "NOTICE: Starting: " + desc.getName();
                    mod->setObjectName(mod->getId());
                    mod->init(this);
                }
            }
        }
    }
    if (getActiveModuleClassNames().isEmpty()) {
        LxqtModuleInterface* mod = loadModuleByClassName("LxqtMod_CoreConfig");
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

LxqtModuleInterface* Core::loadModuleByLibName(QString libName) {
    LxqtModuleInterface* mod = m_moduleFactory->loadModule(libName);
    if (mod) {
        mod->setParent(this);
        mod->setObjectName(mod->getId());
    }
    return mod;
}

LxqtModuleInterface* Core::loadModuleByClassName(QString className) {
    LxqtModuleInterface* mod = 0;
    QMap<QString, ModuleDescriptor*> m_aviableModules = m_moduleFactory->getDescriptors();
    if (m_aviableModules.contains(className)) {
        mod = m_moduleFactory->loadModule(m_aviableModules[className]->getLibName());
        if (mod) {
            mod->setParent(this);
            mod->setObjectName(mod->getId());
        }
    }

    return mod;
}

LxqtModuleInterface* Core::getModuleByClassName(QString className) const {
    LxqtModuleInterface *child = this->findChild<LxqtModuleInterface*>(className);
    return child;
}

QStringList Core::getActiveModuleClassNames() const {
    QList<LxqtModuleInterface *> children = this->findChildren<LxqtModuleInterface*>(QString());
    QStringList modNames;

    foreach(LxqtModuleInterface * mod, children) {
        modNames.append(mod->getId());
    }
    return modNames;
}

QMap<QString, ModuleDescriptor*> Core::getModuleList() const {
    return m_moduleFactory->getDescriptors();
}

RazorApplication* Core::getRazorApp() const {
    return m_app;
}
