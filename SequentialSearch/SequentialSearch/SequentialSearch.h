#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern int search(int data[], int size, int v);
extern int insert(int data[], int *size, int v);
extern int delete(int data[], int *size, int v);

#ifdef __cplusplus
}
#endif