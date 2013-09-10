/* 
 * File:   ModuleDescriptor.cpp
 * Author: alexis
 * 
 * Created on 4 de septiembre de 2013, 12:36
 */

#include "ModuleDescriptor.h"
#include <QSettings>
#include <QVariant>
#include <QFile>
#include <QBool>
#include <qtxdg/xdgdirs.h>
#include <QDebug>

ModuleDescriptor::ModuleDescriptor() {
}

ModuleDescriptor::ModuleDescriptor(QString path)  {
    if (QFile::exists(path)) {
        QSettings settings(path, QSettings::IniFormat);

        settings.beginGroup("LXQT-CORE MODULE Entry");

        m_class = settings.value("Class").toString();
        m_libName = settings.value("Lib").toString();

        m_name = settings.value("Name").toString();
        m_iconPath = settings.value("Icon").toString();
        m_description = settings.value("Comment").toString();

        settings.endGroup();
    }
}

ModuleDescriptor::~ModuleDescriptor() {
}

QString ModuleDescriptor::getDescription() const {
    return m_description;
}

QString ModuleDescriptor::getIconPath() const {
    return m_iconPath;
}

QString ModuleDescriptor::getClass() const {
    return m_class;
}

QString ModuleDescriptor::getName() const {
    return m_name;
}

QString ModuleDescriptor::getLibName() const {
    return m_libName;
}

void ModuleDescriptor::setDescription(QString description) {
    this->m_description = description;
}

void ModuleDescriptor::setIconPath(QString iconPath) {
    this->m_iconPath = iconPath;
}

void ModuleDescriptor::setClass(QString className) {
    this->m_class = className;
}

void ModuleDescriptor::setName(QString name) {
    this->m_name = name;
}

void ModuleDescriptor::setLibName(QString path) {
    this->m_libName = path;
}


