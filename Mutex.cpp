#include "Mutex.h"


Mutex::Mutex(void) {
	m_pLock =(pthread_mutex_t*)malloc(sizeof (pthread_mutex_t));
	pthread_mutexattr_t attr;
	pthread_mutexattr_init (&attr);
	pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init (m_pLock, &attr);
	pthread_mutexattr_destroy (&attr);
}

Mutex::~Mutex(void) {
	pthread_mutex_destroy (m_pLock);
	free (m_pLock);
	m_pLock = NULL;
}

bool Mutex::Lock() {
	if( !pthread_mutex_lock(m_pLock) )
		return true;
	else
		return false;
}

bool Mutex::Unlock() {
	if( !pthread_mutex_unlock(m_pLock) )
		return true;
	else
		return false;
}
