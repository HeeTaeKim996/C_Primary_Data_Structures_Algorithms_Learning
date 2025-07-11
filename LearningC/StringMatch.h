#pragma once
#include <stdio.h>
#include <string.h>
#include <limits.h>

inline void str_dump(const char* s)
{
	for (; *s != '\0'; s++)
	{
		printf("%c %0*X ", *s, (CHAR_BIT + 3) / 4, *s);
		for (int i = CHAR_BIT - 1; i >= 0; i--)
		{
			putchar(((*s >> i) & 1U) ? '1' : '0');
		}
		putchar('\n');

		/*
		 - CHAR_BIT : 1����Ʈ�� ���Ʈ���� ��Ÿ��
		 - printf ���� * : *�� ������, ����(����?)�� �߰��� �Է�
		 - %0*X : %X�� 16����. 0�� ���ڿ��� 0�� ä��. * �� ���ڷ� ���� ����ŭ�� �ڸ����� �Է�
		         -> ���ڷ� ���� ���� (CHAR_BIT + 3) / 4 �ڸ�����, ���� 0���� ä��, *s�� %X�� 16������ ���
		 - 1U == 0b0001 
		*/
	}
}

inline void swap_ptr(char** x, char** y)
{
	char* tmp = *x;
	*x = *y;
	*y = tmp;
}

inline int str_len(const char* s)
{
	int len = 0;
	while (s[len])
	{
		len++;
	}
	return len;
}
inline int str_len_2(const char* s)
{
	int len = 0;
	while (*s++)
	{
		len++;
	}
	return len;

}

inline int str_len_3(const char* s)
{
	const char* p = s;
	while (*s)
	{
		s++;
	}
	return s - p;
}

inline int str_chr(const char* s, int c)
{
	int i = 0;
	c = (char)c;
	while (s[i] != c)
	{
		if (s[i] == '\0')
		{
			return -1;
		}
		i++;
	}
	return i;
}

inline int str_rchar(const char* s, int c)
{
	int i = 0;
	c = (char)c;

	while (s[i] != '\0')
	{
		i++;
	}
	i--;
	while (s[i] != c)
	{
		if (i < 0)
		{
			return -1;
		}

		i--;
	}

	return i;
}

inline int str_cmp(const char* s1, const char* s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return 0;
		}
		s1++;
		s2++;
	}

	return (unsigned char)*s1 - (unsigned char)*s2;
}

inline int str_ncmp(const char* s1, const char* s2, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (*s1 != *s2)
		{
			return (unsigned char)s1 - (unsigned char)s2;
		}
		s1++;
		s2++;
	}

	return 0;
}

/*
�� ȿ�� ����
 - ���Ʈ ������ : txt�� ª�� �� ȿ����
 - KMP			: ������ �ݺ��Ǵ� ���� ( pat = ABABAB... )
 - ���̾�-����� : ���� ������, ��������� ���� ���� �˻���
*/


inline int BruteForceMatch(const char txt[], const char pat[])
{
	int pt = 0;
	int pp = 0;

	while (txt[pt] != '\0' && pat[pp] != '\0')
	{
		if (txt[pt] == pat[pp])
		{
			pt++;
			pp++;
		}
		else
		{
			pt = pt - pp + 1;
			pp = 0;
		}
	}

	if (pat[pp] == '\0')
	{
		return pt - pp;
	}
	return -1;
}

inline int KMP_Match(const char txt[], const char pat[])
{
/*
��  ���� ����

�� SKIP�� �뵵
  - chars : A B C A B C D E F 
    ��� ����.
  - �� BruteForceMatch�� ��ġ�� ��, pp �� A B C A B ���� ����ߴµ� �� �İ� txt�� Z����, �����ߴ� ����. 
    BruteForceMatch�� �ٽ� B C A B .. �̷��� �ε��� ++ ���� �ٽ� ��ġ�Ѵ�.
  - �̺κ��� �����ϴ� ���� KMP_Match. ������, A B C A B ����, ���� A B �� ó���� A B �� ��ġ�ϱ� ������,
    pt �� ���ҽ�Ű�� ����, pat�� �ε��� 2 ���� �ٽ� ���ϸ� �ȴ�.
  - KMP_Match�� pat�� �ε��� 2���� ���� �� �ֵ���, �� ���н�, �� ���� pp�� �����Ǵ�, ������ �ȳ��ϴ�
    int skip[] ��, �˻� ���� �̸� ����� ����ϴ� ���


�� SKIP�� ����� ���
CHARS
INDEX  0 1 2 3 4 5 6 7 8 
CHAR   A A A B A A A A B

SKIP
INDEX  0 1 2 3 4 5 6 7 8 9
VALUE  - 0 1 2 0 1 2 3 3 4

==> SKIP�� ���� ��, SKIP�� ���ε���, VALUE�� �����Ͽ�, pat[pt] == pat[pp]�� ���Ͽ� SKIP�� ����� �ϸ� �����ϱ� ����.

==> ������ SKIP�� �ε��� 4, 8, 9 �� ��������� ������ ���� �����ϱ� ����.

 1) �ε��� 4
   - pat[3] : B != pat[2] : A
    -> pp = skip[2] = 1;
	-> pat[3] : B != pat[1] : A
	-> pp = skip[1] = 0
	-> pp == 0 => pat[4] = 0;

2) �ε��� 8
   - pat[7] : A != pat[3] : B
    -> pp = skip[3] = 2;
	-> pat[7] : A == pat[2] : A
	-> pat[8] = 3;

3) �ε��� 9
   - pat[8] : B == pat[3] : B
    -> pat[9] = 4; 

	==>> ��ġ Ŭ���ֿ̹��� �ǹ�? ���� ���� �����ϴ� �� ����. ��ġ ���н�, �ٴ�(0)���� �˻��� �ٽ� �ϴ� �� �ƴ϶�,
	     ���� �ǹ����� �ٷ� ����Ǿ�, (� �ǹ��� �ٿ����� ����, �ٷ� 0���� ����������) ���н� ����� �ǹ����� ��������.
		 ���� �� �ǹ��� ���н�, �� �ǹ��� ����� �ǹ����� �� ��������.

		 -> Brute Force Method�� ���� ����, Ŭ���̹��� �ϴ� �Ϳ� ������ �� �ְ�,
		    KMP �� ������ �ǹ��� ������ �ؼ�, �� �� �����ϰ� Ŭ���̹��� �ϴ� �Ϳ� ������ �� �ִ�.

*/
	int pt = 1;
	int pp = 0;

	int skip[1024];
	skip[1] = 0;

	while (pat[pt] != '\0')
	{
		if (pat[pt] == pat[pp])
		{
			skip[++pt] = ++pp;
		}
		else if (pp == 0)
		{
			skip[++pt] = 0;
		}
		else
		{
			pp = skip[pp];
		}
	}

	pt = pp = 0;

	while (txt[pt] != '\0' && pat[pp] != '\0')
	{
		if (txt[pt] == pat[pp])
		{
			pt++;
			pp++;
		}
		else if (pp == 0)
		{
			pt++;
		}
		else
		{
			pp = skip[pp];
		}
	}

	if (pat[pp] == '\0')
	{
		return pt - pp;
	}
	return -1;
}


inline int Boyer_Moore_Match(const char txt[], const char pat[])
{
	int pt = 0;
	int pp = 0;
	int txt_len = strlen(txt);
	int pat_len = strlen(pat);

	int skip[UCHAR_MAX + 1];
	for (int i = 0; i <= UCHAR_MAX; i++)
	{
		skip[i] = pat_len;
	}
	for (int i = 0; i < pat_len - 1; i++)
	{
		skip[pat[i]] = pat_len - 1 - i;
	}
	
	while (pt < txt_len )
	{
		pp = pat_len - 1;
		while (txt[pt] == pat[pp])
		{
			if (pp == 0)
			{
				return pt;
			}
			pt--;
			pp--;
		}

		pt += (skip[txt[pt]] > pat_len - pp) ? skip[txt[pt]] : pat_len - pp;
	}
	return -1;

	/* ����
	 �� for(pt = 0; pt < pat_len - 1; pt++) ���� pt <= pat_pen - 1�� �ƴ�, pt < pat_len - 1 �� ������?
	  - pat�� �������׿��� pat_len ��ŭ �Ҵ��ϸ� �ȴ�. ������ txt[pt]�� pat[pat_len - 1]�� ���,
	    ��������� �ܿ� �ش� �ؽ�Ʈ�� ���ٸ�, �ش� ������ ��Ī�� ���ɼ��� ����.
		���� pat�� ���� ��Ұ� txt[pt] != pat[pp]�� txt[pt]�� ������ ����, pat_len ��ŭ �̵��ϴ� �Ͱ� ����������,
		txt[pt] != pat[pp] ���� txt[pt] == pat[pat_len -1] �̸�, �ش� �ؽ�Ʈ�� ������ ��� �ܿ� ���ٸ�,
		pat_len ��ŭ �̵��Ѵ�.
		
	 �� �߰���, �� for���� �ݺ���, pt�� �ڿ������� ��ġ�� ������ġ�� pat_len - 1 �� �Ҵ�ȴ�.

	�� skip[txt[pt]] > pat_len - pp ? ���� ������ �Ҵ�Ǵ� ���� �����ΰ�?
	 - ������ �Ҵ�Ǵ� ��츦 ����. ����������, pt--; pp--; �� �ϰ� �ִ�. �� �������� ������, pt�� �����Ѵ�.
	 - pp�� ����ʷ� �����Ѵ�. ������ ������, ������ pat_len - pp �� 1�� �����Ѵ�.
	 - ��, ������ �Ҵ�Ǵ� ��쿡, �׻� ���� pat�� 1 ��ŭ�� ���Ѵ�. 
	   [ pt (-n) += pat_len - pp == pat_len - (pat_len - 1 (-n) ) == (+n) + 1 ] 
	   ==>> pt�� n��ŭ ������ ��ŭ, pp �� n��ŭ ��������, ���̵����� ���� 1
	     
	 ==>> ����, ������ ä�õǴ� ���, ���� 1 ���� �̵��̴�. ��, ������ ä�õǴ� ��Ȳ����, �ڵ尡 �߸��Ǿ� ������ ä�õǴ� ����,
	      ���� pat �̵��� ���ϰų�, ������ �������� �̵��ϴ� ����.
		  �� ��Ȳ�� �����ϱ� ����, �ּ� ���� 1�̵��� ����, ������ �� Ŭ��, ������ �Ҵ��Ͽ� �ּ� 1��ŭ ���� �̵��ϵ��� �����Ѵ�.
	*/
}