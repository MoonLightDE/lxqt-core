/* 
 * File:   DCoreModuleManager.h
 * Author: alexis
 *
 * Created on 1 de septiembre de 2013, 23:33
 */

#ifndef DCOREMODULEMANAGER_H
#define	DCOREMODULEMANAGER_H

#include <QPluginLoader>
#include <QString>
#include <QMap>

#include "LxqtModuleInterface.h"
#include "ModuleDescriptor.h"

class LxqtModuleInterface;

class ModuleFactory {
public:
    ModuleFactory(QString modulesPath, QString descriptorsPath);
    ModuleFactory(const ModuleFactory& orig);
    virtual ~ModuleFactory();

    QString getModulesPath() const;
    void setModulesPath(QString modulesPath);

    /* Description: Explore, validate and inport the module descriptors.
     * Returns: Map <ClassName, ModuleDescriptor> 
     *  */
    QMap<QString, ModuleDescriptor*> getDescriptors();
    
    /* Description: Loads a module from a file if wasn't loaded before. 
     * Returns:
     */
    LxqtModuleInterface* loadModuleByPath(QString modPath);
    LxqtModuleInterface* loadModule(QString modId);


    
private:
    QString m_modulesPath;
    QString m_descriptorsPath;
    QMap<QString, ModuleDescriptor*> candidates;
};

#endif	/* DCOREMODULEMANAGER_H */

