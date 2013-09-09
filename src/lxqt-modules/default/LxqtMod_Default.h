/* 
 * File:   DefaultModule.h
 * Author: alexis
 *
 * Created on 31 de agosto de 2013, 21:09
 */

#ifndef DEFAULTMODULE_H
#define	DEFAULTMODULE_H

#include <QObject>

#include <Core.h>
#include <LxqtModuleInterface.h>


class LxqtMod_Default : public LxqtModuleInterface  {
    Q_OBJECT
    Q_INTERFACES(LxqtModuleInterface)
public:
    virtual void init(Core *core);
    virtual QString getId();
    
    LxqtMod_Default();
    LxqtMod_Default(const LxqtMod_Default& orig);
    virtual ~LxqtMod_Default();
private:
    Core* m_core;

};


#endif	/* DEFAULTMODULE_H */

