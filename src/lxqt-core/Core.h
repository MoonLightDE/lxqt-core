/* 
 * File:   Core.h
 * Author: Alexis Lopez Zubieta
 *
 * Created on 3 de septiembre de 2013, 21:27
 */

#ifndef CORE_H
#define	CORE_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QList>
#include <QMap>

// Included to increase compatibility with razorqt applications
#include <razorqt/razorapplication.h>

#include "ModuleDescriptor.h"

class LxqtModuleInterface;
class ModuleFactory;

class Core : public QObject {
public:
    Core(RazorApplication* app);
    Core(const Core& orig);
    void init();

    LxqtModuleInterface* loadModuleByLibName(QString libName);
    LxqtModuleInterface* loadModuleByClassName(QString className);
    
    LxqtModuleInterface* getModuleByClassName(QString className) const;
    
    QStringList getActiveModuleClassNames() const;
    QMap<QString, ModuleDescriptor*> getModuleList() const;
    RazorApplication* getRazorApp() const;
    
public slots:
    /* Description: Unload a module. 
     * Returns:
     */
    void unloadModule(QString className);

    virtual ~Core();
private:
    RazorApplication* m_app;
    QSettings* m_settings;
    ModuleFactory* m_moduleFactory;
    
};

#endif	/* CORE_H */

