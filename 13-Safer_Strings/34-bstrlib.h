/*
 * This source file is part of the bstring string library.  This code was
 * written by Paul Hsieh in 2002-2015, and is covered by the BSD open source
 * license and the GPL. Refer to the accompanying documentation for details
 * on usage and license.
 */

#ifndef BSTRLIB_INCLUDE
#define BSTRLIB_INCLUDE

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#if !defined (BSTRLIB_CAN_USE_STL)
#define BSTRLIB_CAN_USE_STL (0)
#endif

#define BSTR_OK (0)
#define BSTR_ERR (-1)

typedef struct tagbstring * bstring;
typedef const struct tagbstring * const_bstring;

/* Version */
#define BSTR_VER_UPDATE 0

/* Copy functions */
#define cstr2bstr bfromcstr
extern bstring bfromcstr (const char * str);
extern bstring bfromcstralloc (int mlen, const char * str);
extern bstring bfromcstrrangealloc (int minl, int maxl, const char* str);
extern bstring blk2bstr (const void * blk, int len);
extern char * bstr2cstr (const_bstring s, char z);
extern int bcstrfree (char * s);
extern bstring bstrcpy (const_bstring b1);
extern int bassign (bstring a, const_bstring b);
extern int bassignmidstr (bstring a, const_bstring b, int left, int len);
extern int bassigncstr (bstring a, const char * str);
extern int bassignblk (bstring a, const void * s, int len);

/* Destroy function */
extern int bdestroy (bstring b);

/* Space allocation hinting functions */
extern int balloc (bstring s, int len);
extern int ballocmin (bstring b, int len);

/* Substring extraction */
extern bstring bmidstr (const_bstring b, int left, int len);

/* Various standard manipulations */
extern int bconcat (bstring b0, const_bstring b1);
extern int bconchar (bstring b0, char c);
extern int bcatcstr (bstring b, const char * s);
extern int bcatblk (bstring b, const void * s, int len);
extern int binsert (bstring s1, int pos, const_bstring s2, unsigned char fill);
extern int binsertblk (bstring s1, int pos, const void * s2, int len, unsigned char fill);
extern int binsertch (bstring s1, int pos, int len, unsigned char fill);
extern int breplace (bstring b1, int pos, int len, const_bstring b2, unsigned char fill);
extern int bdelete (bstring s1, int pos, int len);
extern int bsetstr (bstring b0, int pos, const_bstring b1, unsigned char fill);
extern int btrunc (bstring b, int n);

/* Scan/search functions */
extern int bstricmp (const_bstring b0, const_bstring b1);
extern int bstrnicmp (const_bstring b0, const_bstring b1, int n);
extern int biseqcaseless (const_bstring b0, const_bstring b1);
extern int biseqcaselessblk (const_bstring b, const void * blk, int len);
extern int bisstemeqcaselessblk (const_bstring b0, const void * blk, int len);
extern int biseq (const_bstring b0, const_bstring b1);
extern int biseqblk (const_bstring b, const void * blk, int len);
extern int bisstemeqblk (const_bstring b0, const void * blk, int len);
extern int biseqcstr (const_bstring b, const char * s);
extern int biseqcstrcaseless (const_bstring b, const char * s);
extern int bstrcmp (const_bstring b0, const_bstring b1);
extern int bstrncmp (const_bstring b0, const_bstring b1, int n);
extern int binstr (const_bstring s1, int pos, const_bstring s2);
extern int binstrr (const_bstring s1, int pos, const_bstring s2);
extern int binstrcaseless (const_bstring s1, int pos, const_bstring s2);
extern int binstrrcaseless (const_bstring s1, int pos, const_bstring s2);
extern int bstrchrp (const_bstring b, int c, int pos);
extern int bstrrchrp (const_bstring b, int c, int pos);

#define bstrrchr(b,c) bstrrchrp ((b), (c), blength(b)-1)
extern int binchr (const_bstring b0, int pos, const_bstring b1);
extern int binchrr (const_bstring b0, int pos, const_bstring b1);
extern int bninchr (const_bstring b0, int pos, const_bstring b1);
extern int bninchrr (const_bstring b0, int pos, const_bstring b1);
extern int bfindreplace (bstring b, const_bstring find, const_bstring repl, int pos);
extern int bfindreplacecaseless (bstring b, const_bstring find, const_bstring repl, int pos);

/* List of string container functions */
struct bstrList {
    int qty, mlen;
    bstring * entry;
};
extern struct bstrList * bstrListCreate (void);
extern int bstrListDestroy (struct bstrList * sl);
extern int bstrListAlloc (struct bstrList * sl, int msz);
extern int bstrListAllocMin (struct bstrList * sl, int msz);

/* String split and join functions */
extern struct bstrList * bsplit (const_bstring str, unsigned char splitChar);
extern struct bstrList * bsplits (const_bstring str, const_bstring splitStr);
extern struct bstrList * bsplitstr (const_bstring str, const_bstring splitStr);
extern bstring bjoin (const struct bstrList * bl, const_bstring sep);
extern bstring bjoinblk (const struct bstrList * bl, const void * s, int len);
extern int bsplitcb (const_bstring str, unsigned char splitChar, int pos,
	int (* cb) (void * parm, int ofs, int len), void * parm);
extern int bsplitscb (const_bstring str, const_bstring splitStr, int pos,
	int (* cb) (void * parm, int ofs, int len), void * parm);
extern int bsplitstrcb (const_bstring str, const_bstring splitStr, int pos,
	int (* cb) (void * parm, int ofs, int len), void * parm);

/* Miscellaneous functions */
extern int bpattern (bstring b, int len);
extern int btoupper (bstring b);
extern int btolower (bstring b);
extern int bltrimws (bstring b);
extern int brtrimws (bstring b);
extern int btrimws (bstring b);

#if !defined (BSTRLIB_NOVSNP)
extern bstring bformat (const char * fmt, ...);
extern int bformata (bstring b, const char * fmt, ...);
extern int bassignformat (bstring b, const char * fmt, ...);
extern int bvcformata (bstring b, int count, const char * fmt, va_list arglist);

#define bvformata(ret, b, fmt, lastarg) { \
bstring bstrtmp_b = (b); \
const char * bstrtmp_fmt = (fmt); \
int bstrtmp_r = BSTR_ERR, bstrtmp_sz = 16; \
	for (;;) { \
		va_list bstrtmp_arglist; \
		va_start (bstrtmp_arglist, lastarg); \
		bstrtmp_r = bvcformata (bstrtmp_b, bstrtmp_sz, bstrtmp_fmt, bstrtmp_arglist); \
		va_end (bstrtmp_arglist); \
		if (bstrtmp_r >= 0) { /* Everything went ok */ \
			bstrtmp_r = BSTR_OK; \
			break; \
		} else if (-bstrtmp_r <= bstrtmp_sz) { /* A real error? */ \
			bstrtmp_r = BSTR_ERR; \
			break; \
		} \
		bstrtmp_sz = -bstrtmp_r; /* Doubled or target size */ \
	} \
	ret = bstrtmp_r; \
}

#endif

typedef int (*bNgetc) (void *parm);
typedef size_t (* bNread) (void *buff, size_t elsize, size_t nelem, void *parm);

/* Input functions */
extern bstring bgets (bNgetc getcPtr, void * parm, char terminator);
extern bstring bread (bNread readPtr, void * parm);
extern int bgetsa (bstring b, bNgetc getcPtr, void * parm, char terminator);
extern int bassigngets (bstring b, bNgetc getcPtr, void * parm, char terminator);
extern int breada (bstring b, bNread readPtr, void * parm);

/* Stream functions */
extern struct bStream * bsopen (bNread readPtr, void * parm);
extern void * bsclose (struct bStream * s);
extern int bsbufflength (struct bStream * s, int sz);
extern int bsreadln (bstring b, struct bStream * s, char terminator);
extern int bsreadlns (bstring r, struct bStream * s, const_bstring term);
extern int bsread (bstring b, struct bStream * s, int n);
extern int bsreadlna (bstring b, struct bStream * s, char terminator);
extern int bsreadlnsa (bstring r, struct bStream * s, const_bstring term);
extern int bsreada (bstring b, struct bStream * s, int n);
extern int bsunread (struct bStream * s, const_bstring b);
extern int bspeek (bstring r, const struct bStream * s);
extern int bssplitscb (struct bStream * s, const_bstring splitStr, 
	int (* cb) (void * parm, int ofs, const_bstring entry), void * parm);
extern int bssplitstrcb (struct bStream * s, const_bstring splitStr, 
	int (* cb) (void * parm, int ofs, const_bstring entry), void * parm);
extern int bseof (const struct bStream * s);

struct tagbstring {
	int mlen;
	int slen;
	unsigned char * data;
};

/* Accessor macros */
#define blength(b) ((b) ? (b)->slen : -1)
#define bdata(b) ((char *)((b) ? (b)->data : NULL))
#define bchar(b, p) ((((unsigned)(p)) < (unsigned)blength(b)) ? (char)((b)->data[(p)]) : (char)0)

#ifdef __cplusplus
}
#endif

#endif
