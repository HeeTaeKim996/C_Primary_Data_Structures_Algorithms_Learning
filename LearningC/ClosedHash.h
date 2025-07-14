#ifndef ___ClosedHash
#define ___ClosedHash

#ifdef __cplusplus
extern "C"
{
#endif

#include "Member.h"

	typedef enum
	{
		ClosedHash_Occupied, ClosedHash_Empty, ClosedHash_Deleted
	} ClosedHash_Status;

	typedef struct
	{
		Member data;
		ClosedHash_Status stat;
	} ClosedHash_Bucket;

	typedef struct
	{
		int size;
		ClosedHash_Bucket* table;
	} ClosedHash;

	int ClosedHash_Initialize(ClosedHash* h, int size);

	ClosedHash_Bucket* ClosedHash_Search(const ClosedHash* h, const Member* x);

	int ClosedHash_Add(ClosedHash* h, const Member* x);

	int ClosedHash_Remove(ClosedHash* h, const Member* x);

	void ClosedHash_Dump(const ClosedHash* h);

	void ClosedHash_Clear(ClosedHash* h);

	void ClosedHash_Terminate(ClosedHash* h);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___ClosedHash


/* �� ClosedHash ����
    - ����� �ѷ�
	- ���� : size�̻� ���� �Ұ�. empty�� ��ü�ɼ���, search ���ɵ� ����Ͽ� ����. empty ������ 0.3 ���Ϸ� ��������,
	        ���� �ް�
	- ���� : ĳ�� ģȭ��. empty�� ���� �ʱ⿡ ���� ���
*/