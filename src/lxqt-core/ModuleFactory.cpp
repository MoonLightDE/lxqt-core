/* 
 * File:   DCoreModuleManager.cpp
 * Author: alexis
 * 
 * Created on 1 de septiembre de 2013, 23:33
 */

#include <QDebug>
#include <QDir>
#include <QPluginLoader>


#include "ModuleFactory.h"
#include "ModuleDescriptor.h"

ModuleFactory::ModuleFactory(QString basePath)  {
    m_modulesPath = basePath + "/lib/lxqt-core/modules";
    m_descriptorsPath = basePath + "/share/lxqt-core/descriptors";
}

ModuleFactory::~ModuleFactory() {
}

QMap<QString, ModuleDescriptor*> ModuleFactory::loadDescriptors() {
    QMap<QString, ModuleDescriptor*> candidates;
    if (m_descriptorsPath.isNull())
        return candidates;

    QDir descriptorsDir = QDir(m_descriptorsPath);
    qDebug() << "NOTICE: Loading descriptors from: " << descriptorsDir.absolutePath();

    foreach(QString fileName, descriptorsDir.entryList(QDir::Files)) {
        if (fileName.endsWith(".desktop")) {
            QString path = descriptorsDir.absoluteFilePath(fileName);
            ModuleDescriptor *mod = new ModuleDescriptor(path);
            if (mod && isAValidDescriptor(mod)) {
                qDebug() <<  "NOTICE: " << mod->getClass() << " loaded.";
                candidates[mod->getClass()] = mod;
            }

        }
    }
    return candidates;
}

LxqtModuleInterface * ModuleFactory::loadModuleByPath(QString modPath) {
    LxqtModuleInterface *lxqtModule = 0;
    if (QFile::exists(modPath)) {
        qDebug() << "NOTICE: Loading " << modPath;
        QPluginLoader loader(modPath);
        QObject *plugin = loader.instance();
        if (plugin) {
            qDebug() << "NOTICE: Casting " << modPath;
            lxqtModule = qobject_cast<LxqtModuleInterface*>(plugin);
            if (lxqtModule) {
                qDebug() << "NOTICE: Succeed!";
            } else {
                qDebug() << "ERROR: " << modPath << " is not a valid module.";
            }
        } else {
            qDebug() << loader.errorString();
        }
    }
    return lxqtModule;
}

LxqtModuleInterface * ModuleFactory::loadModule(QString libName) {
    LxqtModuleInterface * mod = 0;
    QString fullPath = m_modulesPath + "/" + libName;
    return loadModuleByPath(fullPath);
}

QString ModuleFactory::getDescriptorsPath() const {
    return m_descriptorsPath;
}

QString ModuleFactory::getModulesPath() const {
    return m_modulesPath;
}

void ModuleFactory::setModulesPath(QString modulesPath) {
    this->m_modulesPath = modulesPath;
}

void ModuleFactory::setDescriptorsPath(QString descriptorsPath) {
    this->m_descriptorsPath = descriptorsPath;
}

/*TODO: Do a more extensive validation. */

bool ModuleFactory::isAValidDescriptor(ModuleDescriptor *desc) {
    QDir pluginsDir = QDir(m_modulesPath);
    return pluginsDir.exists(desc->getLibName());
}