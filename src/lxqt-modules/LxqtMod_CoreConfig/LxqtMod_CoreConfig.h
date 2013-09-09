/* 
 * File:   LxqtMod_CoreConfig.h
 * Author: alexis
 *
 * Created on 6 de septiembre de 2013, 16:15
 */

#ifndef LXQTMOD_CORECONFIG_H
#define	LXQTMOD_CORECONFIG_H
#include "../lxqt-core/Core.h"
#include "../lxqt-core/LxqtModuleInterface.h"

#include "basicsettings.h"

class LxqtMod_CoreConfig : public LxqtModuleInterface {
    Q_OBJECT
    Q_INTERFACES(LxqtModuleInterface)
public:
    virtual void init(Core* core);
    virtual QString getId();


    LxqtMod_CoreConfig();
    LxqtMod_CoreConfig(const LxqtMod_CoreConfig& orig);
    virtual ~LxqtMod_CoreConfig();
private:
    Core* m_core;
    BasicSettings* m_ui;

};

#endif	/* LXQTMOD_CORECONFIG_H */

