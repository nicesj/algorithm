#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct tree_node;
struct stack_item;

extern struct tree_node *node_create(int value);
extern int tree_dump(struct tree_node *root, int show_value);
extern int tree_insert(struct tree_node **root, int value);
extern int tree_remove(struct tree_node **root, int value);

#ifdef __cplusplus
}
#endif