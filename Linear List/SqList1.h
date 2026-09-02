#ifndef SQLIST1_H
#define SQLIST1_H

#include "Status.h"
#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

#ifndef ELEM_TYPE
#define ELEM_TYPE int
#endif
typedef ELEM_TYPE ElemType;
//ElemType 默认为 int, 源文件使用时define ELEM_TYPE

typedef struct {
    ElemType* elem;
    int length;
    int listsize;
} SqList;

inline Status InitList_Sq(SqList& L) {
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem) return OVERFLOW;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE * sizeof(ElemType);
    return OK;
}

inline Status DestroyList_Sq(SqList& L) {
    if(!L.elem) return ERROR;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}

inline Status ClearList_Sq(SqList& L) {
    if(!L.elem) return ERROR;
    L.length = 0;
    return OK;
}

inline Status ListEmpty_Sq(SqList L) {
    if(!L.elem) return INFEASIBLE;
    return (L.length == 0? TRUE : FALSE);
}

inline int ListLength_Sq(SqList L) {
    if(!L.elem) return INFEASIBLE;
    return L.length;
}

inline Status GetElem_Sq(SqList L, int i, ElemType& e) {
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length) return ERROR;
    e = *(L.elem + i - 1);
    return OK;
}

inline int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType)) {
    if(!L.elem) return INFEASIBLE;
    ElemType* p = L.elem;
    ElemType* q = L.elem + L.length - 1;
    for(; p <= q; p++) 
        if(compare(*p, e)) {
            return p - L.elem + 1;
        }
    return 0;
}

inline Status PriorElem_Sq(SqList L, ElemType cur_e, ElemType& pre_e) {
    if(!L.elem) return INFEASIBLE;
    if(L.length == 0) return ERROR;
    ElemType* p = L.elem;
    if(*p == cur_e) return INFEASIBLE;
    ElemType* q = L.elem + L.length - 1;
    for(; p <= q; p++) 
        if(cur_e == *p) {
            pre_e = *(p - 1);
            return OK;
        }
    return ERROR;
}

inline Status NextElem_Sq(SqList L, ElemType cur_e, ElemType& next_e) {
    if(!L.elem) return INFEASIBLE;
    if(L.length == 0) return ERROR;
    ElemType* q = L.elem + L.length - 1;
    if(*q == cur_e) return INFEASIBLE;
    ElemType* p = L.elem;
    for(; p < q; p++) 
        if(cur_e == *p) {
            next_e = *(p + 1);
            return OK;
        }
    return ERROR;
}

inline Status ListIncrease_Sq(SqList& L) {
    if(!L.elem) return INFEASIBLE;
    ElemType* np = (ElemType*)realloc(L.elem, L.listsize + LISTINCREMENT * sizeof(ElemType));
    if(!np) return OVERFLOW;
    L.elem = np;
    L.listsize += LISTINCREMENT * sizeof(ElemType);
    return OK;
}

inline Status ListInsert_Sq(SqList& L, int i, ElemType e) {
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length + 1) return ERROR;
    if(L.length * sizeof(ElemType) >= (size_t)L.listsize) {
        Status flag = ListIncrease(L);
        if(flag != OK) return ERROR;
    }
    ElemType* p = L.elem + L.length - 1;
    ElemType* q = L.elem + i - 1;
    for(; p >= q; p--) 
        *(p + 1) = *(p);
    *q = e;
    L.length ++;
    return OK;
}

inline Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length) return ERROR;
    ElemType* p = L.elem + i - 1;
    ElemType* q = L.elem + L.length - 1;
    e = *p;
    for(; p < q; p++)
        *(p) = *(p + 1);
    L.length --;
    return OK;
}

inline Status ListTraverse_Sq(SqList& L, void (*visit)(ElemType&)) {
    if(!L.elem) return INFEASIBLE;
    ElemType* p = L.elem;
    ElemType* q = L.elem + L.length - 1;
    for(; p <= q; p++)
        visit(*p);
    return OK;
}

#endif
