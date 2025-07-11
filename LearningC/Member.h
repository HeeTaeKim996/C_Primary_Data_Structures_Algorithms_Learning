#ifndef ___Member
#define ___Member
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "string.h"

typedef struct
{
	int no;
	char name[20];
} Member;


#define MEMBER_NO 1
#define MEMBER_NAME 2

inline int Member_NoCmp(const Member* x, const Member* y)
{
	return x->no < y->no ? -1 : x->no > y->no ? 1 : 0;
}
inline int Member_NameCmp(const Member* x, const Member* y)
{
	return strcmp(x->name, y->name);
}
inline void Member_PrintMember(const Member* x)
{
	printf("%d %s", x->no, x->name);
}
inline void Member_PrintLnMember(const Member* x)
{
	printf("%d %s\n", x->no, x->name);
}
inline Member Member_ScanMember(const char* message, int sw)
{
	Member tmp;
	printf("%s하는 데이터를 입력하세요\n", message);
	if (sw & MEMBER_NO) { printf("번호 : "), scanf("%d", &tmp.no); }
	if (sw & MEMBER_NAME) { printf("이름 : "), scanf("%s", tmp.name); }
	return tmp;
}
#endif ___Member