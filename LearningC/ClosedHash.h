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


/* ○ ClosedHash 개요
    - 장단이 뚜렷
	- 단점 : size이상 저장 불가. empty가 대체될수록, search 성능도 비례하여 저하. empty 비율이 0.3 이하로 내려갈시,
	        성능 급감
	- 장점 : 캐시 친화적. empty가 많은 초기에 성능 우수
*/