#include "ClientManager.h"
#include "BaseSocket.h"
#include <iostream>

using namespace std;

ClientManager::ClientManager() {
				m_mapClient.clear();
}

ClientManager::~ClientManager() {
				ClearClientQueue();
}

ClientManager* ClientManager::GetInstance() {
				static ClientManager manager;
				return &manager;
}

int ClientManager::GetClientQueueSize() {
				m_Mutex.Lock();
				int iSize = m_mapClient.size();
				m_Mutex.Unlock();
				return iSize;
}

void ClientManager::ClearClientQueue() {
				m_Mutex.Lock();
				map<string, BaseSocket*>::iterator it;
				for(it=m_mapClient.begin(); it!=m_mapClient.end();) {
								delete it->second;
								m_mapClient.erase(it++);
				}
				m_Mutex.Unlock();
}

BaseSocket* ClientManager::FindSocket(int sock)
{
				m_Mutex.Lock();
				BaseSocket* client;
				map<string, BaseSocket*>::iterator it;
				for(it=m_mapClient.begin(); it!=m_mapClient.end(); it++)
				{
								if(it->second->GetSocket() == sock)
								{
												client = it->second;
												m_Mutex.Unlock();
												return client;
								}
				}
				m_Mutex.Unlock();
				return NULL;
}

int ClientManager::GetClients(vector<BaseSocket*> &vctClients) 
{
				int count=0;
				m_Mutex.Lock();

				if( m_mapClient.size() > 0 ) {
								map<string, BaseSocket*>::iterator it;
								for(it=m_mapClient.begin(); it!=m_mapClient.end();) {
												BaseSocket *client = it->second;
												if( client->GetSocketStatus() == wait_quit ) {

																delete client;
																m_mapClient.erase(it++);
												}
												else if(client->GetSocketStatus() == wait_read){
																vctClients.push_back(client);
																it++;
																if( ++count >= 1024)
																				break;
												}   
												usleep(100);
								} 
				} 
				m_Mutex.Unlock();

				return count;
}

bool ClientManager::Insert(BaseSocket *client) {
				if( NULL == client )
								return false;

				m_Mutex.Lock();
				m_mapClient.insert(pair<string, BaseSocket*>(client->GetClientKey(), client));
				m_Mutex.Unlock();
				return true;
}

bool ClientManager::Erase(BaseSocket *client) {
				if( NULL == client )
								return false;

				m_Mutex.Lock();
				map<string, BaseSocket*>::iterator it = m_mapClient.find(client->GetClientKey());
				if( it != m_mapClient.end() ) {
								delete it->second;
								m_mapClient.erase(it);
				}
				m_Mutex.Unlock();
				return true;
}

