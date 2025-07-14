#ifndef ___BinTree
#define ___BinTree

#ifdef __cplusplus
extern "C"
{
#endif

#include "Member.h"

	typedef struct __BinNode
	{
		Member data;
		struct __BinNode* left;
		struct __BinNode* right;
	} BinNode;

	BinNode* BinTree_Search(BinNode* p, const Member* x);

	BinNode* BinTree_Add(BinNode* p, const Member* x);

	int BinTree_Remove(BinNode** root, const Member* x);

	void BinTree_PrintTree(const BinNode* p);

	void BinTree_FreeTree(BinNode* p);



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___BinTree
