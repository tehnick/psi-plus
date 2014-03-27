/*
 * contactlistmodelupdater.h - class to group model update operations together
 * Copyright (C) 2008-2010  Yandex LLC (Michail Pishchagin)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#ifndef CONTACTLISTMODELUPDATER_H
#define CONTACTLISTMODELUPDATER_H

#include <QObject>
#include <QHash>
#include <QDateTime>

class QTimer;

class PsiContact;
class PsiContactList;

class ContactListModelUpdater : public QObject
{
	Q_OBJECT
public:
	ContactListModelUpdater(PsiContactList* contactList, QObject *parent);
	~ContactListModelUpdater();

	bool updatesEnabled() const;
	void setUpdatesEnabled(bool updatesEnabled);

public slots:
	void commit();
	void clear();

signals:
	void addedContact(PsiContact*);
	void removedContact(PsiContact*);
	void contactAlert(PsiContact*);
	void contactAnim(PsiContact*);
	void contactUpdated(PsiContact*);
	void contactGroupsChanged(PsiContact*);
	void groupsDelimiterChanged();

	void beginBulkContactUpdate();
	void endBulkContactUpdate();

public slots:
	void addContact(PsiContact*);

private slots:
	void removeContact(PsiContact*);

	void contactAlert();
	void contactAnim();
	void contactUpdated();
	void contactGroupsChanged();

	void beginBulkUpdate();
	void endBulkUpdate();

private:
	bool updatesEnabled_;
	PsiContactList* contactList_;
	QTimer* commitTimer_;
	QDateTime commitTimerStartTime_;
	QHash<PsiContact*, bool> monitoredContacts_;

	enum Operation {
		AddContact           = 1 << 0,
		RemoveContact        = 1 << 1,
		UpdateContact        = 1 << 2,
		ContactGroupsChanged = 1 << 3,
		AnimateContact	     = 1 << 4
	};
	QHash<PsiContact*, int> operationQueue_;

	void addOperation(PsiContact* contact, Operation operation);
	int simplifiedOperationList(int operations) const;
};

#endif
