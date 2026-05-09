#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "34-bstrlib.h"

/* Simple implementations of core bstring functions for Exercise 36 */

bstring bfromcstr (const char * str) {
    bstring b;
    int len;
    if (str == NULL) return NULL;
    len = (int) strlen (str);
    b = (bstring) malloc (sizeof (struct tagbstring));
    if (b == NULL) return NULL;
    b->slen = len;
    b->mlen = len + 1;
    b->data = (unsigned char *) malloc (b->mlen);
    if (b->data == NULL) {
        free (b);
        return NULL;
    }
    memcpy (b->data, str, len + 1);
    return b;
}

int bdestroy (bstring b) {
    if (b == NULL || b->data == NULL || b->mlen <= 0) return BSTR_ERR;
    free (b->data);
    b->data = NULL;
    b->mlen = -1;
    b->slen = -1;
    free (b);
    return BSTR_OK;
}

int bstricmp (const_bstring b0, const_bstring b1) {
    int i, v, n;
    if (b0 == NULL || b1 == NULL || b0->data == NULL || b1->data == NULL) return 0;
    n = b0->slen;
    if (n > b1->slen) n = b1->slen;
    for (i = 0; i < n; i++) {
        v = tolower (b0->data[i]) - tolower (b1->data[i]);
        if (v != 0) return v;
    }
    return b0->slen - b1->slen;
}

int biseq (const_bstring b0, const_bstring b1) {
    if (b0 == NULL || b1 == NULL || b0->data == NULL || b1->data == NULL || b0->slen != b1->slen) return 0;
    if (b0->slen == 0) return 1;
    return memcmp (b0->data, b1->data, b0->slen) == 0;
}

bstring bstrcpy (const_bstring b) {
    bstring b2;
    if (b == NULL || b->data == NULL || b->slen < 0) return NULL;
    b2 = (bstring) malloc (sizeof (struct tagbstring));
    if (b2 == NULL) return NULL;
    b2->slen = b->slen;
    b2->mlen = b->slen + 1;
    b2->data = (unsigned char *) malloc (b2->mlen);
    if (b2->data == NULL) {
        free (b2);
        return NULL;
    }
    memcpy (b2->data, b->data, b->slen + 1);
    return b2;
}

int bassigncstr (bstring a, const char * str) {
    int len;
    if (a == NULL || a->data == NULL || a->mlen <= 0 || str == NULL) return BSTR_ERR;
    len = (int) strlen (str);
    if (len >= a->mlen) {
        unsigned char * tmp = (unsigned char *) realloc (a->data, len + 1);
        if (tmp == NULL) return BSTR_ERR;
        a->data = tmp;
        a->mlen = len + 1;
    }
    a->slen = len;
    memcpy (a->data, str, len + 1);
    return BSTR_OK;
}

int bconcat (bstring b0, const_bstring b1) {
    int len;
    if (b0 == NULL || b1 == NULL || b0->data == NULL || b1->data == NULL) return BSTR_ERR;
    len = b0->slen + b1->slen;
    if (len >= b0->mlen) {
        unsigned char * tmp = (unsigned char *) realloc (b0->data, len + 1);
        if (tmp == NULL) return BSTR_ERR;
        b0->data = tmp;
        b0->mlen = len + 1;
    }
    memcpy (b0->data + b0->slen, b1->data, b1->slen + 1);
    b0->slen = len;
    return BSTR_OK;
}

/* ... more functions could be added as needed ... */
