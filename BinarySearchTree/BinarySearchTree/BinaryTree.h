#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern int insert(int tree[], int size, int v);
extern int delete(int tree[], int size, int v);
extern int search(int tree[], int size, int v);
extern int depth(int tree[], int size);

#ifdef __cplusplus
}
#endif