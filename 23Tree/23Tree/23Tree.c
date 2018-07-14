// References
// [1] https://www.slideshare.net/sandpoonia/23-tree
// [2] https://cathyatseneca.gitbooks.io/data-structures-and-algorithms/2-3_trees/
// [3] https://en.wikipedia.org/wiki/2%E2%80%933_tree

#include <stdio.h>
#include <stdlib.h>

#include "23Tree.h"
#include "Common.h"

struct tree_node {
	struct tree_node *left;
	struct tree_node *middle;
	struct tree_node *right;

	int key[2];
};

struct stack_item {
	struct tree_node *node;
	enum {
		LEFT = -1,
		MIDDLE = 0,
		RIGHT = 1,
	} path;
};

struct tree_node *node_create(int key1, int key2)
{
	struct tree_node *node;

	node = malloc(sizeof(*node));
	if (node == NULL) return NULL;

	node->key[0] = key1;
	node->key[1] = key2;
	node->left = NULL;
	node->right = NULL;
	node->middle = NULL;

	return node;
}

int tree_dump(struct tree_node *root)
{
	struct tree_node *queue[485] = { 0, }; // level 4
	struct tree_node *node;
	int front = 0;
	int rear = 0;
	int level = 0;
	int items = 0;
	int count_of_items = 0;
	int count;
	struct tree_node *dummy_node;
	char screen[20][400];
	int start_idx;
	int span;
	int i;
	int l;
	int k;
	int tmp;
	int cell_size;
	int val_size = 3;
	int space = 1;

	if (root == NULL) {
		printf("Empty tree\n");
		return 0;
	}

	/*
	          1         2         3         4         5         6         7         8         9         0         1         2         3         4         5         6
	01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

	                                                                              7 8                                                                               
                            5 6                                                   5 6                                                   5 6
          3 4               3 4               3 4               3 4               3 4               3 4               3 4               3 4               3 4
	1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2   1 2

	240   40     +27
	78    13      +9
	24     4      +3    start_idx' = 6 + 3 + span = 
	6      1      +1    start_idx' = start_idx + cell + span = 0 + 3 + 3
	0      0      0     start_idx' = 0   


	51    17  
	15     5   span' = span * 3 + cell * 2
	3      1
	*/

	dummy_node = node_create(-100, -100);

	queue[rear++] = root;
	count = 0x01;
	tmp = 0;
	while (front != rear) {
		node = queue[front];
		front = (front + 1) % (sizeof(queue) / sizeof(queue[0]));

		if (node->left) {
			queue[rear] = node->left;
			count_of_items++;
			tmp++;
		}
		else queue[rear] = dummy_node;
		rear = (rear + 1) % (sizeof(queue) / sizeof(queue[0]));

		if (node->middle) {
			queue[rear] = node->middle;
			count_of_items++;
			tmp++;
		}
		else queue[rear] = dummy_node;
		rear = (rear + 1) % (sizeof(queue) / sizeof(queue[0]));

		if (node->right) {
			queue[rear] = node->right;
			count_of_items++;
			tmp++;
		}
		else queue[rear] = dummy_node;
		rear = (rear + 1) % (sizeof(queue) / sizeof(queue[0]));

		items++;

		if (items == count) {
			if (tmp == 0) break;
			level++;
			items = 0;
			tmp = 0;
			count *= 3;
		}
	}

	// clear the screen buffer
	for (l = 0; l < sizeof(screen) / sizeof(screen[0]); l++) {
		for (i = 0; i < sizeof(screen[0]) / sizeof(screen[0][0]); i++) {
			screen[l][i] = ' ';
		}
	}

	cell_size = 2 * val_size + space;
	start_idx = 0;
	span = 4;
	int idx;
	for (l = level; l >= 0; l--) {
		idx = 0;
		for (k = 1, tmp = 0; tmp < l; tmp++) {
			idx += k;
			k *= 3;
		}

		for (i = 0; i < k; i++) {
			if (queue[idx + i]->key[0] == -100) {
				for (tmp = 0; tmp < val_size; tmp++) {
					screen[l][start_idx + i * (span + cell_size) + tmp] = '*';
				}
			}
			else if (queue[idx + i]->key[0] == -1) {
				for (tmp = 0; tmp < val_size; tmp++) {
					screen[l][start_idx + i * (span + cell_size) + tmp] = '-';
				}
			}
			else {
				tmp = snprintf(screen[l] + start_idx + i * (span + cell_size), val_size + 1, "%0.d", queue[idx + i]->key[0]);
				if (tmp < 0) {
					fprintf(stderr, "Failed to update the screen buffer %d\n", errno);
					break;
				}
				// Eliminate the last null character
				screen[l][start_idx + i * (span + cell_size) + tmp] = ' ';
			}

			if (queue[idx + i]->key[1] == -100) {
				for (tmp = 0; tmp < val_size; tmp++) {
					screen[l][start_idx + i * (span + cell_size) + space + val_size + tmp] = '*';
				}
			}
			else if (queue[idx + i]->key[1] == -1) {
				for (tmp = 0; tmp < val_size; tmp++) {
					screen[l][start_idx + i * (span + cell_size) + space + val_size + tmp] = '-';
				}
			}
			else {
				tmp = snprintf(screen[l] + start_idx + i * (span + cell_size) + space + val_size, val_size + 1, "%0.d", queue[idx + i]->key[1]);
				if (tmp < 0) {
					fprintf(stderr, "Failed to update the screen buffer %d\n", errno);
					break;
				}
				// Eliminate the last null character
				screen[l][start_idx + i * (span + cell_size) + space + val_size + tmp] = ' ';
			}
		}
	
		// Index of the first item of the upper level
		start_idx = start_idx + cell_size + span;
		span = span * 3 + cell_size * 2;
	}

	// Draw the buffer in the screen
	for (l = 0; l <= level; l++) {
		for (i = 0; i < sizeof(screen[0]) / sizeof(screen[0][0]); i++) {
			putchar(screen[l][i]);
		}
		putchar('\n');
	}

	free(dummy_node);
	return 0;
}

int tree_insert(struct tree_node **root, int key)
{
	struct tree_node *iterator;
	struct tree_node *new_node;
	struct stack_item stack[100];
	int top;
	int i;

	new_node = node_create(key, -1);
	if (new_node == NULL) return -1;

	if (*root == NULL) {
		*root = new_node;
		return 0;
	}

	top = 0;

	iterator = *root;
	while (iterator != NULL) {
		if (key < iterator->key[0]) {
			stack[top].node = iterator;
			stack[top].path = LEFT;
			top++;

			iterator = iterator->left;
		}
		else if (key == iterator->key[0]) {
			free(new_node);
			return -1;
		}
		else if (iterator->key[1] < 0 || key < iterator->key[1]) {
			stack[top].node = iterator;
			stack[top].path = MIDDLE;
			top++;

			iterator = iterator->middle;
		}
		else if (key == iterator->key[1]) {
			free(new_node);
			return -1;
		}
		else if (key > iterator->key[1]) {
			stack[top].node = iterator;
			stack[top].path = RIGHT;
			top++;

			iterator = iterator->right;
		}
		else {
			// Already exists
			free(new_node);
			return -1;
		}
	}

	int ret = 0;

	iterator = new_node;

	i = top;
	while (--i >= 0) {
		if (stack[i].node->key[0] >= 0 && stack[i].node->key[1] >= 0) {
			if (stack[i].path == LEFT) {
				struct tree_node *right;

				right = node_create(stack[i].node->key[1], -1);
				if (right == NULL) {
					ret = -1;
					break;
				}
				right->left = stack[i].node->middle;
				right->middle = stack[i].node->right;

				stack[i].node->key[1] = -1;
				stack[i].node->left = iterator;
				stack[i].node->middle = right;
				stack[i].node->right = NULL;

				iterator = stack[i].node;

				if (i == 0) *root = iterator;
			}
			else if (stack[i].path == MIDDLE) {
				struct tree_node *right;

				right = node_create(stack[i].node->key[1], -1);
				if (right == NULL) {
					ret = -1;
					break;
				}

				right->left = iterator->middle;
				right->middle = stack[i].node->right;

				stack[i].node->middle = iterator->left;
				stack[i].node->right = NULL;
				stack[i].node->key[1] = -1;

				iterator->left = stack[i].node;
				iterator->middle = right;

				if (i == 0) *root = iterator;
			}
			else if (stack[i].path == RIGHT) {
				struct tree_node *parent;

				parent = node_create(stack[i].node->key[1], -1);
				if (parent == NULL) {
					ret = -1;
					break;
				}

				parent->left = stack[i].node;
				parent->middle = iterator;

				stack[i].node->key[1] = -1;
				stack[i].node->right = NULL;

				if (i == 0) *root = parent;
				else iterator = parent;
			}
		}
		else if (stack[i].node->key[0] >= 0) {
			if (stack[i].path == LEFT) {
				stack[i].node->key[1] = stack[i].node->key[0];
				stack[i].node->key[0] = iterator->key[0];

				stack[i].node->right = stack[i].node->middle;
				stack[i].node->middle = iterator->middle;
				stack[i].node->left = iterator->left;
			}
			else { // stack[i].path == MIDDLE
				stack[i].node->key[1] = iterator->key[0];
				stack[i].node->middle = iterator->left;
				stack[i].node->right = iterator->middle;
			}

			free(iterator);
			break;
		}
		else {
			// An exceptional case which is not possible to happen.
			ret = -1;
			break;
		}
	}

	return ret;
}

static inline struct tree_node *find_node(struct tree_node *iterator, int key, int *idx, struct stack_item *stack, int *top)
{
	int i = *top;

	while (iterator != NULL) {
		if (key < iterator->key[0]) {
			stack[i].node = iterator;
			stack[i].path = LEFT;
			i++;

			iterator = iterator->left;
		}
		else if (key == iterator->key[0]) {
			*idx = 0;
			break;
		}
		else if (key < iterator->key[1] || iterator->key[1] < 0) {
			stack[i].node = iterator;
			stack[i].path = MIDDLE;
			i++;

			iterator = iterator->middle;
		}
		else if (key == iterator->key[1]) {
			*idx = 1;
			break;
		}
		else if (key > iterator->key[1]) {
			stack[i].node = iterator;
			stack[i].path = RIGHT;
			i++;

			iterator = iterator->right;
		}
		else {
			iterator = NULL;
			break;
		}
	}

	*top = i;
	return iterator;
}

static inline struct tree_node *find_successor(struct tree_node *iterator, int *idx, struct stack_item *stack, int *top)
{
	struct tree_node *successor = NULL;
	int i;

	i = *top;

	// Let's get the successor of the searched node.
	if (*idx == 0) {
		if (iterator->middle != NULL) {
			// Try to find the smallest value of the right child
			stack[i].node = iterator;
			stack[i].path = MIDDLE;
			i++;

			iterator = iterator->middle;

			while (iterator->left != NULL) {
				stack[i].node = iterator;
				stack[i].path = LEFT;
				i++;

				iterator = iterator->left;
			}

			// Take the key[0] for the successor
			successor = iterator;
		}
		else if (iterator->left != NULL) {
			// Try to find the largest value of the left child
			stack[i].node = iterator;
			stack[i].path = LEFT;
			i++;

			iterator = iterator->left;

			while (iterator) {
				stack[i].node = iterator;

				if (iterator->right != NULL) {
					stack[i].path = RIGHT;
					i++;

					iterator = iterator->right;
				}
				else if (iterator->key[1] < 0 && iterator->middle != NULL) {
					stack[i].path = MIDDLE;
					i++;

					iterator = iterator->middle;
				}
				else {
					break;
				}
			}

			// Take the key[1] if exists or the key[0] for the successor
			*idx = 1;
			successor = iterator;
		}
		else {
			successor = iterator;
		}
	}
	else if (*idx ==  1) {
		if (iterator->right != NULL) {
			// Try to find the smallest value of the right child
			stack[i].node = iterator;
			stack[i].path = RIGHT;
			i++;

			iterator = iterator->right;

			while (iterator->left != NULL) {
				stack[i].node = iterator;
				stack[i].path = LEFT;
				i++;

				iterator = iterator->left;
			}
			// Take the key[0] for the successor
			successor = iterator;
			*idx = 0;
		}
		else if (iterator->middle != NULL) {
			// Try to find the largest value of the left child
			stack[i].node = iterator;
			stack[i].path = MIDDLE;
			i++;

			iterator = iterator->middle;

			while (iterator) {
				stack[i].node = iterator;

				if (iterator->right != NULL) {
					stack[i].path = RIGHT;
					i++;
				}
				else if (iterator->key[1] < 0 && iterator->middle != NULL) {
					stack[i].path = MIDDLE;
					i++;
				}
				else {
					break;
				}
			}

			// Take the key[1] if exists or the key[0] for the successor.
			successor = iterator;
		}
		else {
			successor = iterator;
		}
	}

	*top = i;
	return successor;
}

static inline void shift_left(struct tree_node *node, int new_value, struct tree_node *new_right)
{
	node->left = node->middle;
	node->middle = node->right;
	node->right = new_right;

	node->key[0] = node->key[1];
	node->key[1] = new_value;
}

static inline void shift_right(struct tree_node *node, int new_value, struct tree_node *new_left)
{
	node->right = node->middle;
	node->middle = node->left;
	node->left = new_left;

	node->key[1] = node->key[0];
	node->key[0] = new_value;
}

static inline int is_empty(struct tree_node *node)
{
	return (node->key[0] < 0) && (node->key[1] < 0);
}

static inline int is_full(struct tree_node *node)
{
	return (node->key[0] >= 0) && (node->key[1] >= 0);
}

int tree_remove(struct tree_node **root, int key)
{
	struct tree_node *iterator;
	struct tree_node *successor;
	struct stack_item stack[256];
	int key_idx;
	int top = 0;
	int i;

	iterator = find_node(*root, key, &i, stack, &top);
	if (iterator == NULL) return -1;

	key_idx = i;
	successor = find_successor(iterator, &key_idx, stack, &top);
	if (successor == NULL) return -1;

	// Replace the found with successor.
	if (successor->key[key_idx] < 0) key_idx = 0;
	iterator->key[i] = successor->key[key_idx];
	successor->key[key_idx] = -1;

	if (key_idx == 1) return 0;

	// key[0] is replaced with...
	if (successor->key[1] >= 0) {
		// Just shift the key to left
		shift_left(successor, -1, NULL);
		return 0;
	}

	i = top;
	iterator = successor;
	while (--i >= 0) {
		if (stack[i].path == LEFT) {
			if (is_empty(stack[i].node->left)) {
				if (stack[i].node->middle == NULL) {
					// @note
					// If there is a left node,
					// middle node cannot be null in case of the 2-3 tree.
					// So this part is dead code.
					// However, I just leave this for the exceptional cases.
					if (is_full(stack[i].node)) {
						stack[i].node->left->key[0] = stack[i].node->key[0];
						stack[i].node->left->middle = stack[i].node->middle;

						stack[i].node->key[0] = stack[i].node->key[1];
						stack[i].node->middle = stack[i].node->right;
						stack[i].node->right = NULL;
						break;
					}
					else {
						// In this case, the depth of the tree is reduced.
						// proceed to the parent.
						free(stack[i].node->left);
						stack[i].node->left = NULL;
					}
				}
				else {
					if (is_full(stack[i].node->middle)) {
						// Borrow from the sibling.
						stack[i].node->left->key[0] = stack[i].node->key[0];
						stack[i].node->key[0] = stack[i].node->middle->key[0];
						stack[i].node->left->middle = stack[i].node->middle->left;

						stack[i].node->middle->left = stack[i].node->middle->middle;
						stack[i].node->middle->middle = stack[i].node->middle->right;
						stack[i].node->middle->right = NULL;

						stack[i].node->middle->key[0] = stack[i].node->middle->key[1];
						stack[i].node->middle->key[1] = -1;
						break;
					}
					else {
						// left node is empty,
						// and the middle node is not full but neither empty nor null.
						if (is_full(stack[i].node)) {
							stack[i].node->left->key[0] = stack[i].node->key[0];
							stack[i].node->left->key[1] = stack[i].node->middle->key[0];

							stack[i].node->key[0] = stack[i].node->key[1];
							stack[i].node->key[1] = -1;

							stack[i].node->left->middle = stack[i].node->middle->middle;
							stack[i].node->left->right = stack[i].node->middle->right;

							free(stack[i].node->middle);

							stack[i].node->middle = stack[i].node->right;
							stack[i].node->right = NULL;
							break;
						}
						else {
							struct tree_node *left;
							struct tree_node *middle;

							left = stack[i].node->left;
							middle = stack[i].node->middle;

							stack[i].node->key[1] = middle->key[0];
							stack[i].node->right = middle->middle;
							stack[i].node->middle = middle->left;
							stack[i].node->left = NULL;

							free(left);
							free(middle);

							// Depth of a tree is reduced,
							// proceed to the parent.
						}
					}
				}
			}
			else { // left node is not empty
				if (is_full(stack[i].node->middle)) {
					struct tree_node *node;

					node = node_create(stack[i].node->key[0], -1);

					node->left = stack[i].node->left;
					stack[i].node->left = node;
					node->middle = stack[i].node->middle->left;
					stack[i].node->key[0] = stack[i].node->middle->key[0];

					shift_left(stack[i].node->middle, -1, NULL);
					break;
				}
				else { // middle is not full
					if (is_full(stack[i].node)) {
						shift_right(stack[i].node->middle, stack[i].node->key[0], stack[i].node->left);
						shift_left(stack[i].node, -1, NULL);
						break;
					}
					else {
						struct tree_node *middle;
						middle = stack[i].node->middle;
						stack[i].node->key[1] = middle->key[0];
						stack[i].node->right = middle->middle;
						stack[i].node->middle = middle->left;
						free(middle);
					}
				}
			} // left node is empty or not.
		}
		else if (stack[i].path == MIDDLE) {
			if (is_empty(stack[i].node->middle)) {
				if (stack[i].node->left == NULL && stack[i].node->right == NULL) {
					// @note
					// This is not valid for the 2-3 tree.
					// I just leave this for the exceptional case.

					// There are no siblings to borrow.
					free(stack[i].node->middle);
					stack[i].node->middle = NULL;
					// Proceed to the parent,
					// The height of the tree is decreased.
				}
				else if (stack[i].node->left != NULL && is_full(stack[i].node->left)) {
					stack[i].node->middle->key[0] = stack[i].node->key[0];

					stack[i].node->key[0] = stack[i].node->left->key[1];
					stack[i].node->left->key[1] = -1;

					stack[i].node->middle->left = stack[i].node->left->right;
					stack[i].node->left->right = NULL;
					break;
				}
				else if (stack[i].node->right != NULL && is_full(stack[i].node->right)) {
					stack[i].node->middle->key[0] = stack[i].node->key[1];
					stack[i].node->key[1] = stack[i].node->right->key[0];
					stack[i].node->middle->middle = stack[i].node->right->left;

					shift_left(stack[i].node->right, -1, NULL);
					break;
				}
				else {
					if (is_full(stack[i].node)) {
						free(stack[i].node->middle);
						stack[i].node->middle = NULL;

						stack[i].node->left->key[1] = stack[i].node->key[0];
						stack[i].node->left->right = stack[i].node->middle;

						stack[i].node->middle = stack[i].node->right;
						stack[i].node->right = NULL;

						stack[i].node->key[0] = stack[i].node->key[1];
						stack[i].node->key[1] = -1;
						break;
					}
					else if (stack[i].node->left != NULL) {
						struct tree_node *left;

						free(stack[i].node->middle);
						stack[i].node->middle = NULL;

						left = stack[i].node->left;

						stack[i].node->key[1] = stack[i].node->key[0];
						stack[i].node->key[0] = left->key[0];

						stack[i].node->right = stack[i].node->middle;
						stack[i].node->middle = left->middle;
						stack[i].node->left = left->left;

						free(left);
						// height of the tree is decreased
						// proceed to the parent.
					}
					else {
						// @note
						// It is not possible that the left node is null.
						// In case of the 2-3 tree, this is not valid one.
						free(stack[i].node->middle);
						stack[i].node->middle = NULL;

						// height of the tree is decreased.
						// proceed to the parent.
					}
				}
			}
			else { // middle is not empty
				if (stack[i].node->left == NULL && stack[i].node->right == NULL) {
					// What can I do for this?
					// @note
					// This is not valid for the 2-3 tree.
					// Just leave for the exceptional case.
					break;
				}
				else if (stack[i].node->left != NULL && is_full(stack[i].node->left)) {
					struct tree_node *node;

					node = node_create(stack[i].node->key[0], -1);
					stack[i].node->key[0] = stack[i].node->left->key[1];
					node->left = stack[i].node->left->right;
					stack[i].node->left->right = NULL;
					stack[i].node->left->key[1] = -1;
					node->middle = stack[i].node->middle;
					stack[i].node->middle = node;
					break;
				}
				else if (stack[i].node->right != NULL && is_full(stack[i].node->right)) {
					struct tree_node *node;

					node = node_create(stack[i].node->key[1], -1);
					stack[i].node->key[1] = stack[i].node->right->key[0];
					node->middle = stack[i].node->right->left;
					node->left = stack[i].node->middle;
					shift_left(stack[i].node->right, -1, NULL);
					stack[i].node->middle = node;
					break;
				}
				else { // left or right has one key
					if (is_full(stack[i].node)) {
						// node has 3 children.
						if (stack[i].node->left != NULL) {
							stack[i].node->left->key[1] = stack[i].node->key[0];
							stack[i].node->left->right = stack[i].node->middle;

							stack[i].node->key[0] = stack[i].node->key[1];
							stack[i].node->key[1] = -1;

							stack[i].node->middle = stack[i].node->right;
							stack[i].node->right = NULL;

							break;
						}
						else if (stack[i].node->right != NULL) {
							// @note
							// Always the left node should have a child
							// therefore, this code cannot be executed.
							shift_right(stack[i].node->right, stack[i].node->key[1], stack[i].node->middle);
							stack[i].node->key[1] = -1;
							stack[i].node->middle = stack[i].node->right;
							stack[i].node->right = NULL;
							break;
						}
					}
					else { // node has 2 children.
						// There is no right node. because the parent is not full.
						if (stack[i].node->left == NULL) {
							// @note
							// This is not valid case for the 2-3 tree
							// What can I do for this?
							break;
						}
						struct tree_node *left;
						left = stack[i].node->left;

						shift_right(stack[i].node, -1, NULL);
						stack[i].node->key[0] = left->key[0];
						stack[i].node->left = left->left;
						stack[i].node->middle = left->middle;

						free(left);
						// Height of the tree is decreased,
						// proceed to a parent.
					}
				} // left or right has one key
			} // middle is not empty
		}
		else if (stack[i].path == RIGHT) {
			// is_full(stack[i].node) == true
			if (is_empty(stack[i].node->right)) {
				// right node is deleted. (Empty)
				if (stack[i].node->middle == NULL) {
					// @note
					// This case is not valid for the 2-3 tree.
					// I leave this for the exceptional case.
					stack[i].node->right->key[0] = stack[i].node->key[1];
					stack[i].node->key[1] = -1;
					stack[i].node->middle = stack[i].node->right;
					stack[i].node->right = NULL;
					break;
				} else if (is_full(stack[i].node->middle)) {
					stack[i].node->right->key[0] = stack[i].node->key[1];
					stack[i].node->key[1] = stack[i].node->middle->key[1];
					stack[i].node->middle->key[1] = -1;
					stack[i].node->right->left = stack[i].node->middle->right;
					stack[i].node->middle->right = NULL;
					break;
				}
				else {
					stack[i].node->middle->key[1] = stack[i].node->key[1];
					free(stack[i].node->right);
					stack[i].node->right = NULL;
					stack[i].node->key[1] = -1;
					break;
				}
			}
			else if (is_full(stack[i].node->right)) {
				// right node has two children.
				if (stack[i].node->middle == NULL) {
					struct tree_node *node;
					// @note
					// This is not possible case for the 2-3 tree.
					node = node_create(stack[i].node->key[1], -1);
					stack[i].node->key[1] = -1;
					node->middle = stack[i].node->right;
					stack[i].node->middle = node;
					stack[i].node->right = NULL;
					break;
				}
				else if (is_full(stack[i].node->middle)) {
					struct tree_node *node;
					node = node_create(stack[i].node->key[1], -1);
					stack[i].node->key[1] = stack[i].node->middle->key[1];
					stack[i].node->middle->key[1] = -1;
					node->left = stack[i].node->middle->right;
					stack[i].node->middle->right = NULL;
					node->middle = stack[i].node->right;
					stack[i].node->right = node;
					break;
				}
				else {
					// parent = full, right == full, middle == 1 child
					stack[i].node->middle->key[1] = stack[i].node->key[1];
					stack[i].node->middle->right = stack[i].node->right;
					stack[i].node->key[1] = -1;
					stack[i].node->right = NULL;
					break;
				}
			}
			else { // right node has a child.
				// @note
				// This case is not executed.
				if (stack[i].node->middle == NULL) {
					shift_right(stack[i].node->right, -1, NULL);
					stack[i].node->right->key[0] = stack[i].node->key[1];
					stack[i].node->key[1] = -1;
					stack[i].node->middle = stack[i].node->right;
					stack[i].node->right = NULL;
					break;
				}
				else if (is_full(stack[i].node->middle)) {
					struct tree_node *node;
					node = node_create(stack[i].node->key[1], -1);
					stack[i].node->key[1] = stack[i].node->middle->key[1];
					stack[i].node->middle->key[1] = -1;

					node->left = stack[i].node->middle->right;
					stack[i].node->middle->right = NULL;

					node->middle = stack[i].node->right;
					stack[i].node->right = node;
					break;
				}
				else {
					// middle has a child.
					stack[i].node->middle->key[1] = stack[i].node->key[1];
					stack[i].node->key[1] = -1;
					stack[i].node->middle->right = stack[i].node->right;
					stack[i].node->right = NULL;
					break;
				}
			} // right node has a child
		} // RIGHT
	}

	if (i < 0 && is_empty(*root)) {
		free(*root);
		*root = NULL;
	}

	return 0;
}

struct tree_node *tree_search(struct tree_node *root, int key)
{
	struct tree_node *iterator;

	iterator = root;
	while (iterator != NULL) {
		if (key < iterator->key[0]) {
			iterator = iterator->left;
		}
		else if (key == iterator->key[0]) {
			break;
		}
		else if (iterator->key[1] < 0 || key < iterator->key[1]) {
			iterator = iterator->middle;
		}
		else if (key == iterator->key[1]) {
			break;
		}
		else if (key > iterator->key[1]) {
			iterator = iterator->right;
		}
		else {
			iterator = NULL;
			break;
		}
	}

	return iterator;
}

int tree_validate(struct tree_node *node)
{
	int depth[3];
	int d;

	if (node == NULL) return 0;

	depth[0] = tree_validate(node->left) + 1;
	if (depth[0] == 0) return -1;
	depth[1] = tree_validate(node->middle) + 1;
	if (depth[1] == 0) return -1;
	depth[2] = tree_validate(node->right) + 1;
	if (depth[2] == 0) return -1;

	if (is_full(node)) {
		if (depth[0] != depth[1]) return -1;
		if (depth[1] != depth[2]) return -1;
	}
	else if (is_empty(node)) {
		return -1;
	}
	else {
		if (depth[0] != depth[1]) return -1;
	}

	d = max(depth[0], depth[1]);
	d = max(d, depth[2]);

	return d;
}