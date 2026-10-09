/**
 * @file binary_tree.c
 * @brief Binary tree module: creates, populates, flips, draws, and frees a binary tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief A node in a binary tree.
 */
typedef struct Node {
    int value; /**< The integer value stored in this node. */
    struct Node *left; /**< Pointer to the left child. */
    struct Node *right; /**< Pointer to the right child. */
} Node;

/**
 * @brief Create a binary tree of depth n, populated with random numbers between a and b.
 * @param n Remaining depth to create.
 * @param a Lower bound for random numbers.
 * @param b Upper bound for random numbers.
 * @return Pointer to the root node, or NULL if n <= 0 or allocation fails.
 */
static Node *create_tree(int n, int a, int b)
{
    if (n <= 0)
        return NULL;

    Node *node = malloc(sizeof(Node));
    if (!node)
        return NULL;

    node->value = a + rand() % (b - a + 1);
    node->left = create_tree(n - 1, a, b);
    node->right = create_tree(n - 1, a, b);

    return node;
}

/**
 * @brief Flip a binary tree recursively (swap left and right children).
 * @param node Pointer to the root of the tree to flip.
 */
static void flip_tree(Node *node)
{
    if (!node)
        return;

    Node *temp = node->left;
    node->left = node->right;
    node->right = temp;

    flip_tree(node->left);
    flip_tree(node->right);
}

/**
 * @brief Draw the binary tree to the terminal using a pre-order traversal with indentation.
 * @param node Pointer to the current node being drawn.
 * @param depth Current depth for indentation.
 * @param is_right Whether this node is a right child.
 */
static void draw_tree(Node *node, int depth, int is_right)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }

    if (depth > 0) {
        printf(is_right ? "\\-- " : "/-- ");
    }

    printf("%d\n", node->value);

    draw_tree(node->left, depth + 1, 0);
    draw_tree(node->right, depth + 1, 1);
}

/**
 * @brief Free a binary tree recursively.
 * @param node Pointer to the root of the tree to free.
 */
static void free_tree(Node *node)
{
    if (!node)
        return;

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

/**
 * @brief Generate, flip, and draw a binary tree to the terminal.
 * @return 0 on success; nonzero if allocation or printing fails.
 */
int print_binary_tree(void)
{
    srand((unsigned int)time(NULL));
    int depth = 3;
    int a = 1;
    int b = 100;

    Node *root = create_tree(depth, a, b);
    if (!root)
        return EXIT_FAILURE;

    printf("Original Tree:\n");
    draw_tree(root, 0, 0);

    flip_tree(root);

    printf("\nFlipped Tree:\n");
    draw_tree(root, 0, 0);

    free_tree(root);

    return EXIT_SUCCESS;
}
