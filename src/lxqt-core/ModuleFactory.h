/* 
 * File:   ModuleFactory.h
 * Author: Alexis Lopez Zubieta
 *
 * Created on 1 de septiembre de 2013, 23:33
 */

#ifndef LXQTMODULEINTERFACE_H
#define	LXQTMODULEINTERFACE_H

#include <QString>
#include <QMap>

#include "LxqtModuleInterface.h"
#include "ModuleDescriptor.h"

class LxqtModuleInterface;

class ModuleFactory {
public:
    ModuleFactory(QString basePath);
    virtual ~ModuleFactory();

    QString getModulesPath() const;
    QString getDescriptorsPath() const;
    
    void setModulesPath(QString modulesPath);
    void setDescriptorsPath(QString descriptorsPath);
    
    /* Description: Explore, validate and inport the module descriptors.
     * Returns: Map <ClassName, ModuleDescriptor> 
     *  */
    QMap<QString, ModuleDescriptor*> loadDescriptors();

    /* Description: Loads a module from a file if wasn't loaded before. 
     * Returns:
     */
    LxqtModuleInterface* loadModuleByPath(QString modPath);
    LxqtModuleInterface* loadModule(QString libName);



private:
    bool isAValidDescriptor(ModuleDescriptor *desc);
    
    QString m_modulesPath;
    QString m_descriptorsPath;
};

#endif	/* LXQTMODULEINTERFACE_H */

