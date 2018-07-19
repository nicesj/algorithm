#pragma once

#include <stdio.h>
#include <errno.h>

#include "234Tree.h"
#include "Common.h"

struct tree_node;

extern int tree_dump(struct tree_node *root);
extern struct tree_node *node_create(int key0, int key1, int key2);
extern int tree_insert(struct tree_node **root, int key);
extern int tree_remove(struct tree_node **root, int key);
extern struct tree_node *tree_search(struct tree_node *root, int key);
extern int tree_validate(struct tree_node *root);