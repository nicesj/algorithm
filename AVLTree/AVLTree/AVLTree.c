#include <stdio.h>
#include <stdlib.h>

#include "AVLTree.h"

struct tree_node {
	struct tree_node *left;
	struct tree_node *right;

	int value;
	int balance;
};

struct stack_item {
	struct tree_node *node;
	int balance;
	enum {
		LEFT = -1,
		RIGHT = 1
	} path;
};

struct tree_node *node_create(int value)
{
	struct tree_node *node;

	node = malloc(sizeof(*node));
	if (!node) return NULL;

	node->value = value;
	node->balance = 0;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int tree_dump(struct tree_node *root, int show_value)
{
	struct tree_node *queue[1024] = { 0, }; // level 8
	struct tree_node *node;
	int front = 0;
	int rear = 0;
	int level = 0;
	int items = 0;
	int count_of_items = 0;
	int count;
	struct tree_node *dummy_node;
	int screen[20][200];
	int start_idx;
	int span;
	int i;
	int l;
	int tmp;

	if (root == NULL) {
		printf("Empty tree\n");
		return 0;
	}

	dummy_node = node_create(-100);
	dummy_node->balance = -100;

	queue[rear++] = root;
	count = 0x01 << level;
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
			count = 0x01 << level;
		}
	}

	for (l = 0; l < sizeof(screen) / sizeof(screen[0]); l++) {
		for (i = 0; i < sizeof(screen[0]) / sizeof(screen[0][0]); i++) {
			screen[l][i] = -4;
		}
	}

	start_idx = 0;
	span = 4;
	for (l = level; l >= 0; l--) {
		for (i = 0; i < (0x01 << l); i++) {
			screen[l][start_idx + (i * span)] = (show_value == 1) ? queue[(0x01 << l) + i - 1]->value : queue[(0x01 << l) + i - 1]->balance;
		}

		// Index of the first item of the upper level
		tmp = ((start_idx + span * 3) + (start_idx + span * 2)) / 2;
		start_idx = (start_idx + start_idx + span) / 2;
		span = tmp - start_idx;
	}

	for (l = 0; l <= level; l++) {
		for (i = 0; i < sizeof(screen[0]) / sizeof(screen[0][0]); i++) {
			if (show_value == 1) {
				if (screen[l][i] == -4) putchar(' ');
				else if (screen[l][i] == -100) putchar('*');
				else if (screen[l][i] >= 0) printf("%X", screen[l][i]);
			}
			else {
				if (screen[l][i] == -4) putchar(' ');
				else if (screen[l][i] == -100) putchar('*');
				else printf("%2d", screen[l][i]);
			}
		}
		putchar('\n');
	}

	free(dummy_node);
	return 0;
}

static inline int validate_tree(struct tree_node *node, int depth, int balanced)
{
	int right_depth;
	int left_depth;

	if (node == NULL) return depth;

	right_depth = validate_tree(node->right, depth + 1, balanced);
	if (right_depth < 0) return right_depth;

	left_depth = validate_tree(node->left, depth + 1, balanced);
	if (left_depth < 0) return left_depth;

	if (node->balance != (right_depth - left_depth)) {
		printf("Balance of the node[%X] is invalid. right(%d) left(%d) node balance[%d]\n", node->value, right_depth, left_depth, node->balance);
		abort();
		return -1;
	}

	if (!!balanced && abs(right_depth - left_depth) >= 2) return -1;

	return right_depth > left_depth ? right_depth : left_depth;
}

static inline int check_tree(struct tree_node *root, int balanced)
{
	printf("Balance tree\n");
	tree_dump(root, 0);
	printf("\nValue tree\n");
	tree_dump(root, 1);

	return validate_tree(root, 0, balanced);
}

static int rotate_left(struct tree_node **root, struct tree_node *parent)
{
	struct tree_node *new_root;

	new_root = (*root)->right;
	if (new_root == NULL) return -1;

	if (parent != NULL) {
		if (parent->right == *root) parent->right = new_root;
		else parent->left = new_root;
	}

	(*root)->right = new_root->left;
	new_root->left = *root;

	if (new_root->balance < 0) {
		(*root)->balance = (*root)->balance - 1;
		new_root->balance = (*root)->balance + new_root->balance - 1 - max(0, (*root)->balance);
	}
	else if (new_root->balance >= 0) {
		(*root)->balance = (*root)->balance - new_root->balance - 1;
		new_root->balance = (*root)->balance + new_root->balance - 1 - max(0, (*root)->balance);
	}

	*root = new_root;
	return 0;
}

static int rotate_right(struct tree_node **root, struct tree_node *parent)
{
	struct tree_node *new_root;

	new_root = (*root)->left;
	if (new_root == NULL) return -1;

	if (parent != NULL) {
		if (parent->right == *root) parent->right = new_root;
		else parent->left = new_root;
	}

	(*root)->left = new_root->right;
	new_root->right = *root;

	if (new_root->balance > 0) {
		(*root)->balance = (*root)->balance + 1;
		new_root->balance = (*root)->balance + new_root->balance + 1 - min((*root)->balance, 0);
	}
	else if (new_root->balance <= 0) {
		(*root)->balance = (*root)->balance - new_root->balance + 1;
		new_root->balance = new_root->balance + 1 + max(0, (*root)->balance);
	}

	*root = new_root;
	return 0;
}

int tree_rotate_right(struct tree_node **root, struct tree_node *parent)
{
	if ((*root)->left == NULL) return -1;

	if ((*root)->left->balance > 0) {
		struct tree_node *tmp = (*root)->left;
		rotate_left(&tmp, *root);

		check_tree(*root, 0);
	}

	return rotate_right(root, parent);
}

int tree_rotate_left(struct tree_node **root, struct tree_node *parent)
{
	if ((*root)->right == NULL) return -1;

	if ((*root)->right->balance < 0) {
		struct tree_node *tmp = (*root)->right;
		rotate_right(&tmp, *root);

		check_tree(*root, 0);
	}

	return rotate_left(root, parent);
}

int tree_insert(struct tree_node **root, int value)
{
	struct tree_node *node;
	struct tree_node *iterator;
	struct stack_item stack[100];
	int top = 0;
	int i;

	node = node_create(value);

	if (*root == NULL) {
		*root = node;
		return 0;
	}

	iterator = *root;

	while (iterator != NULL) {
		if (iterator->value < value) {
			stack[top].balance = iterator->balance;
			stack[top].path = RIGHT;
			stack[top].node = iterator;
			top++;

			iterator = iterator->right;
		}
		else if (iterator->value > value) {
			stack[top].balance = iterator->balance;
			stack[top].path = LEFT;
			stack[top].node = iterator;
			top++;

			iterator = iterator->left;
		}
		else {
			// Already exists (duplicated value)
			free(node);
			return -1;
		}
	}

	// Adding a new item to the tree
	if (stack[top - 1].path == LEFT) stack[top - 1].node->left = node;
	else stack[top - 1].node->right = node;

	// Update the balance factor of all parent nodes
	i = top;
	while (--i >= 0) {
		stack[i].node->balance += stack[i].path;

		if (stack[i].node->balance == 2) {
			check_tree(stack[i].node, 0);

			tree_rotate_left(&stack[i].node, i - 1 >= 0 ? stack[i - 1].node : NULL);
			if (i == 0) *root = stack[i].node;

			check_tree(stack[i].node, 0);

			break;
		}
		else if (stack[i].node->balance == -2) {
			check_tree(stack[i].node, 0);

			tree_rotate_right(&stack[i].node, i - 1 >= 0 ? stack[i - 1].node : NULL);
			if (i == 0) *root = stack[i].node;

			check_tree(stack[i].node, 0);

			break;
		}
		else if (abs(stack[i].balance) == 1 /* && stack[i].node->balance == 0 */) {
			// Children nodes of the parent node were filled. So there are no changes of the depth.
			check_tree(stack[i].node, 0);
			break;
		}
	}

	*root = stack[0].node;
	return 0;
}

int tree_remove(struct tree_node **root, int value)
{
	struct tree_node *iterator;
	struct stack_item stack[100];
	int stack_top = 0;
	int i;

	iterator = *root;

	while (iterator != NULL) {
		if (iterator->value < value) {
			stack[stack_top].node = iterator;
			stack[stack_top].balance = iterator->balance;
			stack[stack_top].path = RIGHT;
			stack_top++;

			iterator = iterator->right;
		}
		else if (iterator->value > value) {
			stack[stack_top].node = iterator;
			stack[stack_top].balance = iterator->balance;
			stack[stack_top].path = LEFT;
			stack_top++;

			iterator = iterator->left;
		}
		else if (iterator->value == value) {
			struct tree_node *found;

			found = iterator;

			if (iterator->right != NULL) {
				stack[stack_top].node = iterator;
				stack[stack_top].balance = iterator->balance;
				stack[stack_top].path = RIGHT;
				stack_top++;
				iterator = iterator->right;

				if (iterator->left != NULL) {
					while (iterator->left != NULL) {
						stack[stack_top].node = iterator;
						stack[stack_top].balance = iterator->balance;
						stack[stack_top].path = LEFT;
						stack_top++;
						iterator = iterator->left;
					}

					found->value = iterator->value;
					stack[stack_top - 1].node->left = iterator->right;
				}
				else {
					found->value = iterator->value;
					stack[stack_top - 1].node->right = iterator->right;
				}
			}
			else if (iterator->left != NULL) {
				stack[stack_top].node = iterator;
				stack[stack_top].balance = iterator->balance;
				stack[stack_top].path = LEFT;
				stack_top++;
				iterator = iterator->left;

				found->value = iterator->value;
				stack[stack_top - 1].node->left = iterator->left;
				stack[stack_top - 1].node->right = iterator->right;
			}
			else {
				// Leaf node
				if (stack_top >= 1) {
					if (stack[stack_top - 1].path == LEFT) stack[stack_top - 1].node->left = NULL;
					else stack[stack_top - 1].node->right = NULL;
				}
				else {
					*root = NULL;
				}
			}

			free(iterator);

			i = stack_top;
			while (--i >= 0) {
				if (stack[i].node->balance == 0) {
					stack[i].node->balance = -stack[i].path;

					check_tree(stack[i].node, 0);

					break;
				}

				stack[i].node->balance -= stack[i].path;

				if (stack[i].node->balance == -2) {
					check_tree(stack[i].node, 0);

					tree_rotate_right(&stack[i].node, i - 1 >= 0 ? stack[i - 1].node : NULL);

					check_tree(stack[i].node, 0);

					if (i == 0) *root = stack[i].node;
					if (stack[i].node->balance == 1) break;
				}
				else if (stack[i].node->balance == 2) {
					// do not use (i + 1) for accessing the child node
					//       D
					//  C         F
					//          E
					// In this tree, if the node C is deleted, stack has no information of F and E
					// So we have to access them using right or left node pointer.
					check_tree(stack[i].node, 0);

					tree_rotate_left(&stack[i].node, i - 1 >= 0 ? stack[i - 1].node : NULL);

					check_tree(stack[i].node, 0);

					if (i == 0) *root = stack[i].node;
					if (stack[i].node->balance == -1) break;
				}
			}

			return 0;
		}
	}

	return -1;
}