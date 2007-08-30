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
#include <kgenericfactory.h>
#include <util/log.h>
#include <torrent/queuemanager.h>
#include <interfaces/coreinterface.h>
#include <interfaces/torrentinterface.h>
#include "zeroconfplugin.h"
#include "torrentservice.h"
		
		
#define NAME "Zeroconf"
#define AUTHOR "Lesly Weyts, Kevin Andre and Joris Guisson"
		
K_EXPORT_COMPONENT_FACTORY(ktzeroconfplugin,KGenericFactory<kt::ZeroConfPlugin>("ktzeroconfplugin"))

using namespace bt;

namespace kt
{

	ZeroConfPlugin::ZeroConfPlugin(QObject* parent,const QStringList& args)
	: Plugin(parent,NAME,i18n("Zeroconf"),AUTHOR,QString::null,
			i18n("Finds peers running ktorrent on the local network to share torrents with"),"ktplugins")
	{
		services.setAutoDelete(true);
	}


	ZeroConfPlugin::~ZeroConfPlugin()
	{}
	
	void ZeroConfPlugin::load()
	{
		CoreInterface* core = getCore();
		connect(core,SIGNAL(torrentAdded( kt::TorrentInterface* )),
				this,SLOT(torrentAdded( kt::TorrentInterface* )));
		connect(core,SIGNAL(torrentRemoved( kt::TorrentInterface* )),
				this,SLOT(torrentRemoved( kt::TorrentInterface* )));
		
		// go over existing torrents and add them
		bt::QueueManager* qman = core->getQueueManager();
		for (QList<kt::TorrentInterface*>::iterator i = qman->begin();i != qman->end();i++)
		{
			torrentAdded(*i);
		}
	}
	
	void ZeroConfPlugin::unload()
	{
		CoreInterface* core = getCore();
		disconnect(core,SIGNAL(torrentAdded( kt::TorrentInterface* )),
				   this,SLOT(torrentAdded( kt::TorrentInterface* )));
		disconnect(core,SIGNAL(torrentRemoved( kt::TorrentInterface* )),
				   this,SLOT(torrentRemoved( kt::TorrentInterface*)));
		
		bt::PtrMap<kt::TorrentInterface*,TorrentService>::iterator i = services.begin();
		while (i != services.end())
		{
			TorrentService* av = i->second;
			kt::TorrentInterface* ti = i->first;
			ti->removePeerSource(av);
			i++;
		}
		services.clear();
	}
	
	void ZeroConfPlugin::torrentAdded(kt::TorrentInterface* tc)
	{
		if (services.contains(tc))
			return;
		
		
		TorrentService* av = new TorrentService(tc);
		services.insert(tc,av);
		tc->addPeerSource(av);
		Out(SYS_ZCO|LOG_NOTICE) << "ZeroConf service added for " << tc->getStats().torrent_name << endl;
		connect(av,SIGNAL(serviceDestroyed( TorrentService* )),
			this,SLOT(avahiServiceDestroyed( TorrentService* )));
	}

		
	void ZeroConfPlugin::torrentRemoved(kt::TorrentInterface* tc)
	{
		TorrentService* av = services.find(tc);
		if (!av)
			return;
		Out(SYS_ZCO|LOG_NOTICE) << "ZeroConf service removed for " 
				<< tc->getStats().torrent_name << endl;
		tc->removePeerSource(av);
		services.erase(tc);
	}

	void ZeroConfPlugin::avahiServiceDestroyed(TorrentService* av)
	{
		services.setAutoDelete(false);
		
		Out(SYS_ZCO|LOG_NOTICE) << "ZeroConf service destroyed " << endl;
		bt::PtrMap<kt::TorrentInterface*,TorrentService>::iterator i = services.begin();
		while (i != services.end())
		{
			if (i->second == av)
			{
				services.erase(i->first);
				break;
			}
			i++;
		}
		services.setAutoDelete(true);
	}

	bool ZeroConfPlugin::versionCheck(const QString & version) const
	{
		return version == KT_VERSION_MACRO;
	}
}
#include "zeroconfplugin.moc"
