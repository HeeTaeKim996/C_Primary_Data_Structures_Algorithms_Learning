
#include "Member.h"





Member Member_ScanMember(const char* message, int sw)
{
	Member tmp;
	printf("%s�ϴ� �����͸� �Է��ϼ���\n", message);
	if (sw & MEMBER_NO) { printf("��ȣ : "), scanf_s("%d", &tmp.no); }
	if (sw & MEMBER_NAME) { printf("�̸� : "), scanf_s("%s", tmp.name, sizeof(tmp.name)); }
	return tmp;
}