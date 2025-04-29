#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode {
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new() {
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn) {
  if (!pn) {
    return;
  }

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn) {
  if (!pn) {
    return;
  }

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn) {
  int depth_l, depth_r;

  if (!pn) {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l) {
    return depth_r + 1;
  } else {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  if(pn->left!=NULL)
    count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  if(pn->right!=NULL)
    count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);

  return count;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  BSTree *tree;

  if (!print_ele || !cmp_ele) {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree) {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree) {
  if (!tree) {
    return;
  }

  _bst_node_free_rec(tree->root);
  free(tree);

  return;
}

Bool tree_isEmpty(const BSTree *tree) {
  if (!tree || !tree->root) {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

/**** TODO: find_min, find_max, insert, contains, remove ****/

BSTNode *_bst_find_min_rec(BSTNode *pn) {
  if (!pn->left)
    return pn;
  else
    return _bst_find_min_rec(pn->left);
}

void *tree_find_min(BSTree *tree) {
  if (!tree || !tree->root)
    return NULL;
  return _bst_find_min_rec(tree->root)->info;
}

BSTNode *_bst_find_max_rec(BSTNode *pn) {
  if (!pn->right)
    return pn;
  else
    return _bst_find_max_rec(pn->right);
}

void *tree_find_max(BSTree *tree) {
  if (!tree || !tree->root)
    return NULL;
  return _bst_find_max_rec(tree->root)->info;
}

Bool tree_contains(BSTree *tree, const void *elem) {
  BSTNode *pn;
  int cmp;
  if (!tree || !elem)
    return FALSE;

  pn = tree->root;

  if (!pn)
    return FALSE;
  do {
    cmp = tree->cmp_ele(pn->info, elem);
    if (cmp == 0)
      return TRUE;
    else if (cmp < 0) {
      pn = pn->right;
    } else
      pn = pn->left;
  } while (pn != NULL);

  return FALSE;
}

BSTNode *_bst_insert_rec(BSTree *tree, BSTNode *node, const void *elem) {
  int cmp;

  if (!elem || !tree)
    return NULL;

  if (node == NULL) {
    if (!(node = _bst_node_new()))
      return NULL;
    node->info = (void *)elem;
    return node;
  }

  cmp = tree->cmp_ele(elem, node->info);
  if (cmp == 0) {
    return node;
  }
  if (cmp < 0)
    node->left = _bst_insert_rec(tree, node->left, elem);
  if (cmp > 0)
    node->right = _bst_insert_rec(tree, node->right, elem);
  return node;
}

Status tree_insert(BSTree *tree, const void *elem) {
  BSTNode *ret;
  if (!tree || !elem)
    return ERROR;

  ret = _bst_insert_rec(tree, tree->root, elem);

  if (ret == NULL)
    return ERROR;

  tree->root = ret;

  return OK;
}

BSTNode *_bst_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp elem_cmp) {
  int cmp;
  BSTNode *ret, *aux;
  if (!pn || !elem )
    return NULL;

  cmp = elem_cmp(elem, pn->info);

  if (cmp < 0)
    pn->left = _bst_remove_rec(pn->left, elem, elem_cmp);

  else if (cmp > 0)
    pn->right = _bst_remove_rec(pn->right, elem, elem_cmp);

  else if (cmp == 0) {
    if (!pn->right && !pn->left) {
      _bst_node_free(pn);
      return NULL;
    }

    else if (pn->right && !pn->left) {
      ret = pn->right;
      _bst_node_free(pn);
      return ret;
    }

    else if (!pn->right && pn->left) {
      ret = pn->left;
      _bst_node_free(pn);
      return ret;
    }

    else if (pn->right && pn->left) {
      aux = _bst_find_min_rec(pn->right);
      pn->info = aux->info;
      pn->right = _bst_remove_rec(pn->right, aux->info, elem_cmp);
      return pn;
    }
  }
  return pn;
}

Status tree_remove(BSTree *tree, const void *elem) {
  BSTNode *ret;

  if (!tree || !elem)
    return ERROR;

  ret = _bst_remove_rec(tree->root, elem, tree->cmp_ele);

  tree->root = ret;

  return OK;
}
