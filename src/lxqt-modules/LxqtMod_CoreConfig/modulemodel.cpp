/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright (C) 2012  Alec Moskvin <alecm@gmx.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QDebug>
#include <qtxdg/xdgicon.h>

#include "modulemodel.h"
#include "../../lxqt-core/LxqtModuleInterface.h"

ModuleModel::ModuleModel(Core* core, QObject* parent)
: QAbstractListModel(parent), m_core(core) {

}

ModuleModel::~ModuleModel() {

    foreach(ModuleDescriptor * mod, m_ItemMap.values()) {
        delete mod;
    }
}

void ModuleModel::reset() {
    m_KeyList.clear();
    m_StateMap.clear();

    foreach(ModuleDescriptor * mod, m_ItemMap.values()) {
        delete mod;
    }
    m_ItemMap.clear();
    
    m_ItemMap = m_core->getModuleList();
    // Hide config from list
    m_ItemMap.remove("LxqtMod_CoreConfig");

    m_KeyList = m_ItemMap.keys();

    QStringList moduleList = m_core->getActiveModuleClassNames();

    foreach(const QString& moduleName, moduleList) {
        if (m_ItemMap.contains(moduleName)) {
            m_StateMap[moduleName] = true;
            m_ItemMap[moduleName]->setEnabled(QBool(TRUE));
        }
    }
}

QVariant ModuleModel::data(const QModelIndex& index, int role) const {
    QString name = m_KeyList.at(index.row());
    if (index.column() == 0) {
        switch (role) {
            case Qt::DisplayRole:
                return m_ItemMap[name]->getName();
            case Qt::CheckStateRole:
                return m_ItemMap[name]->isEnabled() ? Qt::Checked : Qt::Unchecked;
            case Qt::ToolTipRole:
                return m_ItemMap[name]->getDescription();
        }
    } else if (index.column() == 1 && (role == Qt::DisplayRole || role == Qt::DecorationRole)) {
        if (role == Qt::DisplayRole && m_StateMap[name] == true)
            return tr("Running") + " ";
    }
    return QVariant();
}

bool ModuleModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (role == Qt::CheckStateRole) {
        QString key = m_KeyList.at(index.row());
        m_ItemMap[key]->setEnabled(QBool(value == Qt::Checked));
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags ModuleModel::flags(const QModelIndex& index) const {
    Q_UNUSED(index);
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

int ModuleModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return m_KeyList.size();
}

void ModuleModel::writeChanges() {

    foreach(const QString& key, m_KeyList) {
        m_ItemMap[key]->commit();
    }
}

void ModuleModel::updateModuleState(QString moduleName, bool state) {
    if (m_ItemMap.contains(moduleName)) {
        m_StateMap[moduleName] = state;
        QModelIndex i = index(m_KeyList.indexOf(moduleName), 1);
        emit dataChanged(i, i);
    }
}

void ModuleModel::toggleModule(const QModelIndex &index, bool status) {
    if (!index.isValid())
        return;

    QStringList activeModules = m_core->getActiveModuleClassNames();
    LxqtModuleInterface *mod = 0;
    if (activeModules.contains(m_KeyList.at(index.row())))
        m_core->unloadModule(m_KeyList.at(index.row()));
    else
        mod = m_core->loadModuleByClassName(m_KeyList.at(index.row()));

    if (mod) {
        mod->setParent(m_core);
        mod->setObjectName(mod->getId());
        mod->init(m_core);
    }

    reset();
}
