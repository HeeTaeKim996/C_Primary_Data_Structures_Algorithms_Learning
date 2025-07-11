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
		 - CHAR_BIT : 1바이트가 몇비트인지 나타냄
		 - printf 내의 * : *가 있으면, 인자(정수?)를 추가로 입력
		 - %0*X : %X는 16진수. 0는 빈문자열을 0로 채움. * 는 인자로 받은 수만큼의 자릿수로 입력
		         -> 인자로 받은 정수 (CHAR_BIT + 3) / 4 자릿수로, 빈값은 0으로 채워, *s를 %X인 16진수로 출력
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
○ 효율 정리
 - 브루트 포스법 : txt가 짧을 때 효율적
 - KMP			: 패턴이 반복되는 구조 ( pat = ABABAB... )
 - 보이어-무어법 : 가장 무난한, 평균적으로 가장 빠른 검색법
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
□  이해 정리

○ SKIP의 용도
  - chars : A B C A B C D E F 
    라고 하자.
  - 위 BruteForceMatch로 서치할 때, pp 가 A B C A B 까지 통고했는데 그 후가 txt가 Z여서, 실패했다 하자. 
    BruteForceMatch는 다시 B C A B .. 이렇게 인덱스 ++ 부터 다시 서치한다.
  - 이부분을 보완하는 것이 KMP_Match. 위에서, A B C A B 에서, 뒤의 A B 는 처음의 A B 와 일치하기 때문에,
    pt 를 감소시키지 말고, pat의 인덱스 2 부터 다시 비교하면 된다.
  - KMP_Match는 pat의 인덱스 2부터 비교할 수 있도록, 비교 실패시, 그 때의 pp의 대응되는, 값들을 안내하는
    int skip[] 을, 검색 전에 미리 만들어 사용하는 방법


○ SKIP을 만드는 방법
CHARS
INDEX  0 1 2 3 4 5 6 7 8 
CHAR   A A A B A A A A B

SKIP
INDEX  0 1 2 3 4 5 6 7 8 9
VALUE  - 0 1 2 0 1 2 3 3 4

==> SKIP을 만들 때, SKIP의 전인덱스, VALUE를 참조하여, pat[pt] == pat[pp]를 비교하여 SKIP을 만든다 하면 이해하기 쉽다.

==> 위에서 SKIP의 인덱스 4, 8, 9 가 만들어지는 과정을 보면 이해하기 쉽다.

 1) 인덱스 4
   - pat[3] : B != pat[2] : A
    -> pp = skip[2] = 1;
	-> pat[3] : B != pat[1] : A
	-> pp = skip[1] = 0
	-> pp == 0 => pat[4] = 0;

2) 인덱스 8
   - pat[7] : A != pat[3] : B
    -> pp = skip[3] = 2;
	-> pat[7] : A == pat[2] : A
	-> pat[8] = 3;

3) 인덱스 9
   - pat[8] : B == pat[3] : B
    -> pat[9] = 4; 

	==>> 마치 클라이밍에서 피벗? 간에 줄을 연결하는 것 같다. 서치 실패시, 바닥(0)부터 검색을 다시 하는 게 아니라,
	     개별 피벗간이 줄로 연결되어, (어떤 피벗은 줄연결이 없어, 바로 0으로 떨어지지만) 실패시 연결된 피벗으로 떨어진다.
		 만약 그 피벗도 실패시, 그 피벗과 연결된 피벗으로 또 떨어진다.

		 -> Brute Force Method는 로프 없이, 클라이밍을 하는 것에 비유할 수 있고,
		    KMP 는 로프로 피벗간 연결을 해서, 좀 더 안전하게 클라이밍을 하는 것에 비유할 수 있다.

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

	/* 정리
	 ○ for(pt = 0; pt < pat_len - 1; pt++) 에서 pt <= pat_pen - 1이 아닌, pt < pat_len - 1 인 이유는?
	  - pat의 마지막항에는 pat_len 만큼 할당하면 된다. 루프중 txt[pt]가 pat[pat_len - 1]일 경우,
	    마지막요소 외에 해당 텍스트가 없다면, 해당 구간은 매칭될 가능성이 없다.
		따라서 pat에 없는 요소가 txt[pt] != pat[pp]의 txt[pt]에 잡혔을 때에, pat_len 만큼 이동하는 것과 마찬가지로,
		txt[pt] != pat[pp] 에서 txt[pt] == pat[pat_len -1] 이며, 해당 텍스트가 마지막 요소 외에 없다면,
		pat_len 만큼 이동한다.
		
	 ※ 추가로, 위 for루프 반복시, pt는 자연스럽게 서치의 시작위치인 pat_len - 1 이 할당된다.

	○ skip[txt[pt]] > pat_len - pp ? 에서 우항이 할당되는 경우는 언제인가?
	 - 우항이 할당되는 경우를 보자. 루프문에서, pt--; pp--; 를 하고 있다. 즉 루프문이 돌수록, pt는 감소한다.
	 - pp도 정비례로 감소한다. 루프가 돌수록, 우항인 pat_len - pp 는 1씩 증가한다.
	 - 즉, 우항이 할당되는 경우에, 항상 패턴 pat이 1 만큼만 이한다. 
	   [ pt (-n) += pat_len - pp == pat_len - (pat_len - 1 (-n) ) == (+n) + 1 ] 
	   ==>> pt가 n만큼 감소한 만큼, pp 가 n만큼 증가시켜, 총이동량은 고정 1
	     
	 ==>> 따라서, 우항이 채택되는 경우, 고정 1 우측 이동이다. 즉, 우항이 채택되는 상황에서, 코드가 잘못되어 좌항이 채택되는 경우는,
	      패턴 pat 이동을 안하거나, 오히려 좌측으로 이동하는 경우다.
		  이 상황을 방지하기 위해, 최소 우측 1이동을 위해, 우항이 더 클시, 우항을 할당하여 최소 1만큼 우측 이동하도록 보장한다.
	*/
}