#include <stdlib.h>
#include <stdio.h>
#include "bstree.h"


#define MAX_BUFFER 64 // Maximum file line size

/* START [_BSTNode] */
typedef struct _BSTNode {
    void * info;
    struct _BSTNode * left;
    struct _BSTNode * right;
    struct _BSTNode * parent;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
    BSTNode * root;
    P_tree_ele_print print_ele;
    P_tree_ele_cmp cmp_ele;
};
/* END [_BSTree] */


/*** BSTNode TAD private functions ***/
BSTNode * _bst_node_new(){
    BSTNode * pn = NULL;

    pn = malloc(sizeof(BSTNode));
    if (!pn) {
        return NULL;
    }
 
    pn->left = pn->right = NULL;
    pn->parent =NULL;
    pn->info = NULL;
    return pn;
}

void _bst_node_free (BSTNode * pn){
    if (!pn) return;
    if(pn->info)
        free(pn->info);
    free(pn);
}

void _bst_node_free_rec (BSTNode * pn){
    if (!pn) return;

    _bst_node_free_rec(pn->left);
    _bst_node_free_rec(pn->right);
    _bst_node_free(pn);

    return;
}

int _bst_depth_rec (BSTNode * pn) {
    int depthR, depthL;
    if (!pn) return 0;

    depthL = _bst_depth_rec(pn->left);
    depthR = _bst_depth_rec(pn->right);

    if (depthR > depthL) {
        return depthR + 1;
    } else {
        return depthL + 1;
    }
}

int _bst_size_rec(BSTNode * pn) {
    int count = 0;
    if (!pn) return count;

    count += _bst_size_rec(pn->left);
    count += _bst_size_rec(pn->right);

    return count + 1;
}

int _bst_preOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += print_ele(pf, pn->info);
    count += _bst_preOrder_rec(pn->left, pf, print_ele);
    count += _bst_preOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_inOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_inOrder_rec(pn->left, pf, print_ele);
    count += print_ele(pf, pn->info);
    count += _bst_inOrder_rec(pn->right, pf, print_ele);

    return count;
}

int _bst_postOrder_rec (BSTNode * pn, FILE * pf, P_tree_ele_print print_ele) {
    int count = 0;
    if (!pn) return count;

    count += _bst_postOrder_rec(pn->left, pf, print_ele);
    count += _bst_postOrder_rec(pn->right, pf, print_ele);
    count += print_ele(pf, pn->info);

    return count;
}

/*** BSTree TAD functions ***/
BSTree * tree_init(P_tree_ele_print print_ele, P_tree_ele_cmp cmp_ele){
    if (!print_ele || !cmp_ele) return NULL;

    BSTree * tree = malloc (sizeof(BSTree));
    if (!tree) {
        return NULL;
    }

    tree->root = NULL;
    tree->print_ele = print_ele;
    tree->cmp_ele = cmp_ele;

    return tree;
}

void tree_destroy (BSTree * tree) {
    if (!tree) return;

    _bst_node_free_rec(tree->root);

    free(tree);
    return;
}

Bool tree_isEmpty( const BSTree * tree){
    if (!tree || !tree->root) return TRUE;
    return FALSE;
}

int tree_depth (const BSTree * tree){
    if (!tree) return -1;

    return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree * tree) {
    if (!tree) return -1;

    return _bst_size_rec(tree->root);
}

int tree_preOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder (FILE *f, const BSTree * tree){
    if (!f || !tree) return -1;

    return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}



/**** TODO: find_min, find_max, insert, contains, remove ****/


BSTNode *bst_insertRec(BSTNode *pn, const void *pe, P_tree_ele_cmp cmp_ele) {
    int cmp;

    if (pn == NULL) {
        pn = _bst_node_new();
        if (pn == NULL) return NULL;
        pn->info =  (void *) pe;
        return pn;
    }

    cmp = cmp_ele (pe, pn->info);

    if (cmp < 0)
        pn->left = bst_insertRec(pn->left, pe, cmp_ele);

    else if (cmp > 0)
        pn->right = bst_insertRec(pn->right, pe, cmp_ele);

    return pn; 
}

Status tree_insert (BSTree *tree, const void *elem) {
    BSTNode *n;
    if (!tree || !elem) return ERROR;

    n = bst_insertRec(tree->root, elem, tree->cmp_ele);

    if (n == NULL) return ERROR;
    
    tree->root = n;

    return OK;
}

BOOL bst_containsRec(BSTNode* pn, void * pe, P_tree_ele_cmp cmp_ele){
    int cmp = 0;
    BOOL bool = FALSE;
    
    if(!pn)
        return NULL;
    
    cmp = cmp_ele(pe, pn->info);
    if(cmp == 0)
        bool = TRUE;
    else if(cmp<0)
        return bst_containsRec(pn->left, pe, cmp_ele);
    else if(cmp > 0)
        return bst_containsRec(pn->right, pe, cmp_ele);
    
    return bool;
}
Bool tree_contains(BSTree * tree, const void * elem){
    BOOL found = FALSE;
   
    if(!tree || !elem)
        return FALSE;
    
    found = bst_containsRec(tree->root, pe, tree->cmp_ele);
    
    return found;
}

Status tree_remove(BSTree * tree, const void * elem){
    BSTNode *n = NULL;
    BTSNode *aux_node = NULL;
    
    if (!tree)
        return NULL;
    
    n = tree->root;
            
    if(n->info > elem)
        n = bst_remove_rec(tree->root->left, elem, tree->cmp_ele);
    
    else if(n->right < elem)
        n = bst_remove_rec(tree->root->right, elem, tree->cmp_ele);
    
    else if(n->info = elem){
        
        if (n->right == NULL && n->left == NULL){
            _bst_node_free(n);
            return NULL;
        }
        else if(n->right != NULL && n->left == NULL){
            ret_node = n->left;
            _bts_node_free(n);
            return ret_node;        
        }
        else if(n->right == NULL && n->left != NULL){
            ret_node = n->right;
            _bts_node_free(n);
            return ret_node; 
        }
        else if(n->right == NULL && n->left == NULL){
            aux_node = _bts_find_min_rec(n->right);
            n->info = aux_node->info;
            n->right = _bts_remove_rec(n->right, aux_node, tree->cmp_ele);
            return n;
        }
    }
    return n;    
}