/***************************************************************************
 *   Copyright (C) 2005-2007 by Joris Guisson                              *
 *   joris.guisson@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 ***************************************************************************/
#ifndef KT_TORRENTSERVICE_HH
#define KT_TORRENTSERVICE_HH

#include <dnssd/publicservice.h>
#include <dnssd/servicebrowser.h>
#include <interfaces/peersource.h>
#include <k3resolver.h>

namespace kt
{
	class TorrentInterface;
	
	/**
	 * Zeroconf service which publishes a torrent
	 * */
	class TorrentService : public PeerSource
	{
		Q_OBJECT
	public:
		TorrentService(TorrentInterface* tc);
		virtual ~TorrentService();
		
		virtual void stop(bt::WaitJob* wjob = 0);
		virtual void start();
		virtual void aboutToBeDestroyed();
		
	signals:
		void serviceDestroyed(TorrentService* av);
		
	public slots:
		void onPublished(bool ok);
		void onServiceAdded(DNSSD::RemoteService::Ptr ptr);
		void hostResolved(KNetwork::KResolverResults res);
		
	private:
		TorrentInterface* tc;
		DNSSD::PublicService* srv;
		DNSSD::ServiceBrowser* browser;
	};
}

#endif
