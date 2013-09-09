/* 
 * File:   DCoreModuleManager.cpp
 * Author: alexis
 * 
 * Created on 1 de septiembre de 2013, 23:33
 */

#include <QDebug>
#include <QDir>
#include <qt4/QtCore/qplugin.h>


#include "ModuleFactory.h"
#include "ModuleDescriptor.h"

ModuleFactory::ModuleFactory(QString modulesPath, QString descriptorsPath) : m_modulesPath(modulesPath), m_descriptorsPath(descriptorsPath) {
}

ModuleFactory::ModuleFactory(const ModuleFactory& orig) {
}

ModuleFactory::~ModuleFactory() {
}

QString ModuleFactory::getModulesPath() const {
    return m_modulesPath;
}

void ModuleFactory::setModulesPath(QString modulesPath) {
    this->m_modulesPath = modulesPath;
}

QMap<QString, ModuleDescriptor*> ModuleFactory::getDescriptors() {
    QMap<QString, ModuleDescriptor*> candidates;
    if (m_descriptorsPath.isNull())
        return candidates;

    QDir pluginsDir = QDir(m_descriptorsPath);
    qDebug() << "Notice: Loading candidates from " << pluginsDir.absolutePath();

    foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
        if (fileName.endsWith(".desktop")) {
            QString path = pluginsDir.absoluteFilePath(fileName);
            ModuleDescriptor *mod = new ModuleDescriptor(path);
            if (mod) {
                candidates[mod->getClass()] = mod;
            }

        }
    }
    return candidates;
}

LxqtModuleInterface * ModuleFactory::loadModuleByPath(QString modPath) {
    LxqtModuleInterface *dCoreModule = 0;
    qDebug() << "NOTICE: Loading " << modPath;
    QPluginLoader loader(modPath);
    QObject *plugin = loader.instance();
    if (plugin) {
        qDebug() << "NOTICE: Casting " << modPath;
        dCoreModule = qobject_cast<LxqtModuleInterface*>(plugin);
        if (dCoreModule) {
            qDebug() << "NOTICE: Succeed!";
        } else {
            qDebug() << "ERROR: " << modPath << " is not a valid module.";
        }
    } else {
        qDebug() << loader.errorString();
    }

    return dCoreModule;
}

LxqtModuleInterface * ModuleFactory::loadModule(QString libName) {
    LxqtModuleInterface * mod = 0;
    QString fullPath = m_modulesPath + "/" + libName;
    if (QFile::exists(fullPath)) {

        qDebug() << "NOTICE: Loading " << libName;
        QPluginLoader loader(fullPath);
        QObject *plugin = loader.instance();
        if (plugin) {
            qDebug() << "NOTICE: Casting " << libName;
            mod = qobject_cast<LxqtModuleInterface*>(plugin);
            if (mod) {
                qDebug() << "NOTICE: Succeed on load";
            } else {
                qDebug() << "NOTICE: " << libName << " is not a valid DCoreModule. Load Failed.";
            }
        } else {
            qDebug() << loader.errorString();
        }
    } else {
        qDebug() << "ERROR: File not found: " + fullPath;
    }



    return mod;
}
