/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * http://razor-qt.org
 *
 * Copyright: 2010-2012 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
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


#include "basicsettings.h"
#include "ui_basicsettings.h"


BasicSettings::BasicSettings(RazorSettings *settings,Core *core, QWidget *parent) :
    QWidget(parent),
    m_settings(settings),
    m_moduleModel(new ModuleModel(core)),
    m_ui(new Ui::BasicSettings),
        m_core(core)
{
    m_ui->setupUi(this);
    connect(m_ui->startButton, SIGNAL(clicked()), this, SLOT(startButton_clicked()));
    connect(m_ui->stopButton, SIGNAL(clicked()), this, SLOT(stopButton_clicked()));
    connect(m_ui->saveButton, SIGNAL(clicked()), this, SLOT(save()));
    restoreSettings();

    m_ui->moduleView->setModel(m_moduleModel);
    m_ui->moduleView->header()->setResizeMode(0, QHeaderView::Stretch);
    m_ui->moduleView->header()->setResizeMode(1, QHeaderView::ResizeToContents);
}

BasicSettings::~BasicSettings()
{
    delete m_ui;
}

void BasicSettings::restoreSettings()
{
    m_moduleModel->reset();
}

void BasicSettings::save()
{
    m_moduleModel->writeChanges();
}


void BasicSettings::startButton_clicked()
{
    m_moduleModel->toggleModule(m_ui->moduleView->selectionModel()->currentIndex(), true);
}

void BasicSettings::stopButton_clicked()
{
    m_moduleModel->toggleModule(m_ui->moduleView->selectionModel()->currentIndex(), false);
}
void BasicSettings::closeEvent(QCloseEvent * event) {
    m_core->unloadModule("LxqtMod_CoreConfig");
}