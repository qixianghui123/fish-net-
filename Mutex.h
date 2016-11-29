#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>
#include <malloc.h>
#include <time.h>

class Mutex
{
public:
	Mutex(void);
	virtual ~Mutex(void);

	bool Lock();
	bool Unlock();
	pthread_mutex_t* getHandle(){ return m_pLock; };

protected:
	pthread_mutex_t *m_pLock;
};

#endif
