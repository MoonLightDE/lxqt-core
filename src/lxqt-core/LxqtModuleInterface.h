/* 
 * File:   DCoreModuleInterface.h
 * Author: Alexis López Zubieta
 *
 * Created on 31 de agosto de 2013, 19:14
 */

#ifndef DCOREMODULE_H
#define	DCOREMODULE_H

#include <QtPlugin>

#include "Core.h"

QT_BEGIN_NAMESPACE
class QObject;
QT_END_NAMESPACE

class LxqtModuleInterface : public QObject {
public:
    // Start the module
    virtual void init(Core *core) = 0;
    
    // Returns the module Id (className)
    virtual QString getId() = 0;
    
    virtual ~LxqtModuleInterface() {}
private:
    
};

QT_BEGIN_NAMESPACE

        Q_DECLARE_INTERFACE( LxqtModuleInterface, "com.lxqt.moduleInterface/0.1" )

QT_END_NAMESPACE

#endif	/* DCOREMODULE_H */

