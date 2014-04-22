#pragma once

#define USE_SYNCHRONIZE

class CNullLock
{
public:
	BOOL Unlock()
	{
		return TRUE;
	}

	BOOL Lock()
	{
		return TRUE;
	}

	BOOL Lock(DWORD dwTimeout)
	{
		return TRUE;
	}
};

template<class T, class SYNCH_STRATEGY>
class SyncObject : public T, public SYNCH_STRATEGY
{
public:
	typedef T Super;
	typedef SYNCH_STRATEGY Synch;
	SyncObject()
	{

	}

	~SyncObject()
	{

	}
};
