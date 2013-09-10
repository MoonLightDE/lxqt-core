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
    void init();

    /*Description: Returns a Module if it's loaded.   */
    LxqtModuleInterface* getActiveModule(QString className) const;

    QStringList getActiveModulesNames() const;

    /* Description: Finds the descriptors of the installed modules.
     * Returns: Mpdule descriptors maped by its className.
     */
    QMap<QString, ModuleDescriptor*> getAllDescriptors() const;
    ModuleDescriptor* getDescriptor(QString className) const;
    RazorApplication* getRazorApp() const;

    /* Description: Find the classNames of the modules that are
     *          loaded on startup.
     * Returns: List of startup modules classNames.
     */
    QStringList getStartUpModules();

    QSettings* getGlobalSettings() const;
    virtual ~Core();

public slots:
    void setStartUpModules(QStringList startUpModules);

    // TODO: Implement reference count
    LxqtModuleInterface* loadModule(QString className);
    void unloadModule(QString className);

    void setLoadOnStartUp(QString className);
    void unsetLoadOnStartUp(QString className);
private:
    RazorApplication* m_app;
    QSettings* m_settings;
    ModuleFactory* m_moduleFactory;

};

#endif	/* CORE_H */

