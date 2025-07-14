#include <stdio.h>
#include <stdlib.h>
#include "Member.h"
#include "BinTree.h"

static BinNode* AllocBinNode()
{
	return calloc(1, sizeof(BinNode));
}

static void SetBinNode(BinNode* n, const Member* x, const BinNode* left, const BinNode* right)
{
	n->data = *x;
	n->left = left;
	n->right = right;
}

BinNode* BinTree_Search(BinNode* p, const Member* x)
{
	int cond;
	if (p == NULL)
	{
		return NULL;
	}
	else if ((cond = Member_NoCmp(x, &p->data)) == 0)
	{
		return p;
	}
	else if (cond < 0)
	{
		return BinTree_Search(p->left, x);
	}
	else
	{
		return BinTree_Search(p->right, x);
	}
}

BinNode* BinTree_Add(BinNode* p, const Member* x)
{
	int cond;
	if (p == NULL)
	{
		p = AllocBinNode();
		SetBinNode(p, x, NULL, NULL);
	}
	else if ((cond = Member_NoCmp(x, &p->data)) == 0)
	{
		printf("오류 : %d 는 이미 등록되어 있습니다\n", x->no);
	}
	else if (cond < 0)
	{
		p->left = BinTree_Add(p->left, x);
	}
	else
	{
		p->right = BinTree_Add(p->right, x);
	}
	return p;
}

int BinTree_Remove(BinNode** root, const Member* x)
{
	BinNode* next, *temp;
	BinNode** left;

	BinNode** p = root;

	while (1)
	{
		int cond;
		if (*p == NULL)
		{
			printf("오류 : 존재하지 않는 %d 를 삭제 요청\n", x->no);
			return -1;
		}
		else if ((cond = Member_NoCmp(x, &(*p)->data)) == 0)
		{
			break;
		}
		else if (cond < 0)
		{
			p = &((*p)->left);
		}
		else
		{
			p = &((*p)->right);
		}
	}


	if ((*p)->left == NULL)
	{
		next = (*p)->right;
	}
	else
	{
		left = &((*p)->left);

		if ((*left)->right == NULL)
		{
			next = *left;
			next->right = (*p)->right;
		}
		else
		{
			while ((*left)->right != NULL)
			{
				left = &(*left)->right;
			}
			next = *left;
			*left = (*left)->left;
			next->left = (*p)->left;
			next->right = (*p)->right;
		}
	}

	temp = *p;
	*p = next;
	free(temp);

	return 0;
}

void BinTree_PrintTree(const BinNode* p)
{
	if (p != NULL)
	{
		BinTree_PrintTree(p->left);
		
		Member_PrintLnMember(&p->data);

		BinTree_PrintTree(p->right);
	}
}

void BinTree_FreeTree(BinNode* p)
{
	if (p != NULL)
	{
		BinTree_FreeTree(p->left);
		BinTree_FreeTree(p->right);
		free(p);
	}
}
