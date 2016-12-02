#include "ClientManager.h"
#include "BaseSocket.h"
#include <iostream>

using namespace std;

ClientManager::ClientManager() {
				m_mapWaitClient.clear();
				m_mapReadClient.clear();
				m_mapDestoryClient.clear();
}

ClientManager::~ClientManager() {
				//ClearClientQueue();
}

ClientManager* ClientManager::GetInstance() {
				static ClientManager manager;
				return &manager;
}

BaseSocket* ClientManager::FindSocket(int sock)
{
				m_waitMutex.Lock();
				BaseSocket* client;
				map<string, BaseSocket*>::iterator it;
				for(it=m_mapWaitClient.begin(); it!=m_mapWaitClient.end(); it++)
				{
								if(it->second->GetSocket() == sock)
								{
												client = it->second;
												m_waitMutex.Unlock();
												return client;
								}
				}
				m_waitMutex.Unlock();
				return NULL;
}

bool ClientManager::InsertWaitMap(BaseSocket *client)
{
				if(client == NULL)
				{
								return false;
				}
				m_waitMutex.Lock();
				m_mapWaitClient.insert(pair<string, BaseSocket*>(client->GetClientKey(), client));
				m_waitMutex.Unlock();
				return true;
}

bool ClientManager::MoveToReadMap(BaseSocket *client)
{
				if(client == NULL)
				{
								return false;
				}
				m_waitMutex.Lock();
				map<string, BaseSocket*>::iterator it = m_mapWaitClient.find(client->GetClientKey());
				if(it == m_mapWaitClient.end())
				{
								m_waitMutex.Unlock();
								return false;
				}
				else
				{
								m_mapWaitClient.erase(it);
								m_waitMutex.Unlock();
				}
				m_readMutex.Lock();
				m_mapReadClient.insert(pair<string, BaseSocket*>(client->GetClientKey(), client));
				m_readMutex.Unlock();
				cout << "move to read map success" << endl;
				return true;
}


bool ClientManager::MoveToDestoryMap(BaseSocket *client)
{
				if(client == NULL)
				{
								return false;
				}
				m_readMutex.Lock();
				map<string, BaseSocket*>::iterator it = m_mapReadClient.find(client->GetClientKey());
				if(it == m_mapReadClient.end())
				{
								m_readMutex.Unlock();
								return false;
				}
				else
				{
								delete it->second;
								m_mapReadClient.erase(it);
								m_readMutex.Unlock();
				}
				m_destoryMutex.Lock();
				//delete client;
				//m_mapDestoryClient.insert(pair<string, BaseSocket*>(client->GetClientKey(), client));
				m_destoryMutex.Unlock();
				return true;

}


int ClientManager::GetClients(map<string, BaseSocket*> &vctClients)
{
				vctClients = m_mapReadClient;
}

int ClientManager::GetWaitClientSize()
{
				return m_mapWaitClient.size();
}

int ClientManager::GetReadClientSize()
{
				return m_mapReadClient.size();
}

int ClientManager::GetDestoryClientSize()
{
				return m_mapDestoryClient.size();
}

