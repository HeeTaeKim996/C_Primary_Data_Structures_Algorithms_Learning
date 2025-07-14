#ifndef ___ChainHash
#define ___ChainHash

#ifdef __cplusplus
extern "C"
{
#endif

#include "Member.h"

	typedef struct __ChainHashNode
	{
		Member data;
		struct __ChainHashNode* next;
	} ChainHashNode;

	typedef struct
	{
		int size;
		ChainHashNode** table;
	} ChainHash;

	int ChainHash_Initialize(ChainHash* h, int size);

	ChainHashNode* ChainHash_Search(const ChainHash* h, const Member* x);

	int ChainHash_Add(ChainHash* h, const Member* x);

	int ChainHash_Remove(ChainHash* h, const Member* x);

	void ChainHash_Dump(const ChainHash* h);

	void ChainHash_Clear(ChainHash* h);

	void ChainHash_Terminate(ChainHash* h);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___ChainHash