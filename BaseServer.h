#ifndef BASE_SERVER_H
#define BASE_SERVER_H

#include "ev.h"

class BaseServer
{
				public:
								int Create();
								int Bind();
								int Listen();
								int InitServer();
				private:
								static void AcceptCallBack(struct ev_loop* loop, struct ev_io* watcher, int events);//accept callback function
								static void ClientCallBack(struct ev_loop* loop, struct ev_io* watcher, int evevts);//read call back function
				private:
								int m_fd;
};
#endif
