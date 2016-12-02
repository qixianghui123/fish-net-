#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include "Mutex.h"
#include "BaseSocket.h"

#include <map>
#include <vector>
#include <string>
using namespace std;

class ClientManager {
				private:
								ClientManager();
								ClientManager(ClientManager &){};
								ClientManager operator=(ClientManager& manager){ ClientManager oth(manager); return oth; };

				public:
								virtual ~ClientManager();

				protected:
								map<string, BaseSocket*> m_mapWaitClient;
								map<string, BaseSocket*> m_mapReadClient;
								map<string, BaseSocket*> m_mapDestoryClient;

								Mutex m_waitMutex;
								Mutex m_readMutex;
								Mutex m_destoryMutex;

								//void ClearClientQueue();

				public:
								static ClientManager* GetInstance();

								BaseSocket* FindSocket(int sock);

								bool InsertWaitMap(BaseSocket *client);
								bool MoveToReadMap(BaseSocket *client);
								bool MoveToDestoryMap(BaseSocket *client);

								int GetClients(map<string, BaseSocket*> &vctClients);
								int GetWaitClientSize();
								int GetReadClientSize();
								int GetDestoryClientSize();
								/*
								BaseSocket* FindSocket(int sock);
								int GetClientQueueSize();
								int GetClients(map<string, BaseSocket*> &vctClients);

								bool Insert(BaseSocket *client);
								bool Erase(BaseSocket *client);
								*/
};

#endif
