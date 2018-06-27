#include "huffman.h"
#include <stdio.h>

/**
 * huffman_codes - produce a huffman tree and print all huffman codes
 *
 * @data: array of characters
 * @freq: array of frequencies of characters
 * @size: size of the arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char *code;
	size_t depth, i;

	root = huffman_tree(data, freq, size);
	if (root == NULL)
		return (0);
	depth = get_depth(root, 0);
	code = malloc(sizeof(char) + (depth + 1));
	for (i = 0; i < depth + 1; i++)
		code[i] = '\0';
	print_huffman_tree_r(root, code, 0);
	free(code);
	free_codes(root);

	return (1);
}

/**
 * free_codes - free all nodes in the huffman tree
 *
 * @root: root of current tree to free
 */
void free_codes(binary_tree_node_t *root)
{
	if (root->left)
		free_codes(root->left);
	if (root->right)
		free_codes(root->right);
	free(root->data);
	free(root);
}

/**
 * get_depth - get the depth from the current @root
 *
 * @root: current root of the tree
 * @depth: depth in the tree
 *
 * Return: depth of the tree from @root
 */
size_t get_depth(binary_tree_node_t *root, size_t depth)
{
	int left_depth, right_depth;

	left_depth = right_depth = -1;
	if (root->left)
		left_depth = get_depth(root->left, depth + 1);
	if (root->right)
		right_depth = get_depth(root->right, depth + 1);
	else
		return (depth);
	if (left_depth > right_depth)
		return (left_depth);
	return (right_depth);
}

/**
 * print_huffman_tree_r - print a huffman tree's contents recursively from
 * a given @root
 *
 * @root: current root of huffman tree
 * @code: code to print
 * @depth: depth into huffman tree
 */
void print_huffman_tree_r(binary_tree_node_t *root, char *code, size_t depth)
{
	if (root->left)
	{
		code[depth] = '0';
		print_huffman_tree_r(root->left, code, depth + 1);
	}
	if (root->right)
	{
		code[depth] = '1';
		print_huffman_tree_r(root->right, code, depth + 1);
	}
	else
	{
		symbol_t *symbol;

		symbol = (symbol_t *)root->data;
		printf("%c: %s\n", symbol->data, code);
	}
}
