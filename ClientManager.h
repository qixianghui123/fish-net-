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
								map<string, BaseSocket*> m_mapClient;
								Mutex m_Mutex;
								void ClearClientQueue();

				public:
								static ClientManager* GetInstance();

								BaseSocket* FindSocket(int sock);
								int GetClientQueueSize();
								int GetClients(vector<BaseSocket*> &vctClients);

								bool Insert(BaseSocket *client);
								bool Erase(BaseSocket *client);
};

#endif
