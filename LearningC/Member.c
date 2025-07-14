
#include "Member.h"





Member Member_ScanMember(const char* message, int sw)
{
	Member tmp;
	printf("%s하는 데이터를 입력하세요\n", message);
	if (sw & MEMBER_NO) { printf("번호 : "), scanf_s("%d", &tmp.no); }
	if (sw & MEMBER_NAME) { printf("이름 : "), scanf_s("%s", tmp.name, sizeof(tmp.name)); }
	return tmp;
}