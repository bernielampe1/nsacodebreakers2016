/*******************************************************************************
 *                                                                             *
 * tree.c - Search tree operations,                                            *
 *                                                                             *
 * LIBSEH - Structured Exception Handling compatibility library.               *
 * Copyright (c) 2008 Tom Bramer < tjb at postpro dot net >                    *
 *                                                                             *
 * Permission is hereby granted, free of charge, to any person                 *
 * obtaining a copy of this software and associated documentation              *
 * files (the "Software"), to deal in the Software without                     *
 * restriction, including without limitation the rights to use,                *
 * copy, modify, merge, publish, distribute, sublicense, and/or sell           *
 * copies of the Software, and to permit persons to whom the                   *
 * Software is furnished to do so, subject to the following                    *
 * conditions:                                                                 *
 *                                                                             *
 * The above copyright notice and this permission notice shall be              *
 * included in all copies or substantial portions of the Software.             *
 *                                                                             *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,             *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES             *
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                    *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT                 *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,                *
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING                *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR               *
 * OTHER DEALINGS IN THE SOFTWARE.                                             *
 *                                                                             *
 *******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "tree.h"


#ifdef __cplusplus
extern "C" {
#endif

#define SPLAY_OP_INSERT   1
#define SPLAY_OP_SEARCH   2
#define SPLAY_OP_DELETE   3

  struct _tree_node
  {
    tree_key_t key;
    tree_value_t value;
    struct _tree_node* left;
    struct _tree_node* right;
    int level;
  };

  static tree_t _alloc_node(int level)
  {
    tree_t n = (tree_t)malloc(sizeof(struct _tree_node));
    memset(n, 0, sizeof(struct _tree_node));
    n->level = level;
    return n;
  }

  static void _destroy_node(tree_t* t)
  {
    free(*t);
    *t = NULL;
  }

  static void _splay_rot_right(tree_t* t)
  {
    tree_t n = *t;
    tree_t x = n->left;
    n->left = x->right;
    x->right = n;
    *t = x;
  }

  static void _splay_rot_left(tree_t* t)
  {
    tree_t n = *t;
    tree_t x = n->right;
    n->right = x->left;
    x->left = n;
    *t = x;
  }

  static void _splay_delete_node(tree_t* t)
  {
    tree_t n = *t;
    tree_t left = n->left;
    tree_t right = n->right;

    if(left == NULL && right == NULL) {
      _destroy_node(t);
    }
    else if(left == NULL) {
      _splay_rot_left(t);
      _splay_delete_node(&((*t)->left));
    }
    else {
      _splay_rot_right(t);
      _splay_delete_node(&((*t)->right));
    }
  }


  static int _splay_op(int opcode, tree_t* t, tree_key_t k, tree_value_t* v)
  {
    tree_t n;
    tree_t n2;
    tree_t* p;
    int level;
    int result = RESULT_FAIL;

    if(NULL == *t) {
      switch(opcode) {
        case SPLAY_OP_INSERT:
          n = *t = _alloc_node(1); 
          n->key = k;
          n->value = *v;
          result = RESULT_OK;
          break;
        case SPLAY_OP_SEARCH:
          break;
      }
    }
    else {
      n = *t;

      if(k < n->key) {
        p = &(n->left);
        level = n->level;
        if(NULL == *p) { 
          return _splay_op(opcode, p, k, v);
        }
        n2 = *p;
        if(k < n2->key) {
          result = _splay_op(opcode, &n2->left, k, v);
          if(n->left) { _splay_rot_right(t); n = *t; }
        }
        else if(k > n2->key) {
          result = _splay_op(opcode, &n2->right, k, v);
          if(n2->right) _splay_rot_left(p);
        }
        else
          return _splay_op(opcode, p, k, v);
        if(n->left) _splay_rot_right(t);
      } 
      else if(k > n->key) {
        p = &(n->right);
        level = n->level;
        if(NULL == *p) {
          return _splay_op(opcode, p, k, v);
        }
        n2 = *p;
        if(k > n2->key) {
          result = _splay_op(opcode, &n2->right, k, v);
          if(n->right) { _splay_rot_left(t); n = *t; }
        }
        else if(k < n2->key) {
          result = _splay_op(opcode, &n2->left, k, v);
          if(n2->left) _splay_rot_right(p);
        }
        else 
          return _splay_op(opcode, p, k, v);
        if(n->right) _splay_rot_left(t);
      }
      else {
        switch(opcode) {
          case SPLAY_OP_DELETE:
            _splay_delete_node(t);
            result = RESULT_OK;
            break;
          case SPLAY_OP_SEARCH:
            *v = n->value;
            result = RESULT_OK;
            break;
          case SPLAY_OP_INSERT:
            break;
        }
      }
    }

    return result;
  }

  /**
   * Create a tree.
   * 
   * @return NULL - this is a dumb placeholder function
   *         that is no longer really needed.  
   */
  tree_t tree_create()
  {
    return NULL;
  }

  /**
   * Insert an item into a tree.
   * 
   * @param t      The tree to act upon.
   * @param k      The key to be associated with the new value.
   * @param v      The new value associated with the key.
   * 
   * @return RESULT_OK - the key is not already used, and the insertion was
   *         successful.
   *         RESULT_FAIL - the key already exists in the tree.
   */
  int tree_insert(tree_t* t, tree_key_t k, tree_value_t v)
  {
    return _splay_op(SPLAY_OP_INSERT, t, k, &v);
  }

  /**
   * Search a tree for a node and return its value.
   * 
   * @param t      The tree to search.
   * @param k      The key of the node to find.
   * @param v      A pointer to where the value of the found node should be stored.
   * 
   * @return RESULT_OK - the requested node was found and the contents of *v
   *         contains the value of that node.
   *         RESULT_FAIL - the requested node was not found.
   */
  int tree_search(tree_t* t, tree_key_t k, tree_value_t* v)
  {
    return _splay_op(SPLAY_OP_SEARCH, t, k, v);
  }

  /**
   * Delete a node from a tree.
   * 
   * @param t      The tree to act upon.
   * @param k      The key of the node to be deleted.
   * 
   * @return RESULT_OK - the node was found and deleted.
   *         RESULT_FAIL - the node was not found.
   */
  int tree_delete(tree_t* t, tree_key_t k)
  {
    return _splay_op(SPLAY_OP_DELETE, t, k, (void**)NULL);
  }

  /**
   * Destroy a tree node and all of it's sub nodes.
   * 
   * @param t      The tree to destroy.
   */
  void tree_destroy(tree_t* t) 
  {
    if(NULL == *t) return;
    if(NULL != (*t)->left) tree_destroy(&((*t)->left));
    if(NULL != (*t)->right) tree_destroy(&((*t)->right));
    _destroy_node(t);
    *t = NULL;
  }

#ifdef __cplusplus
}
#endif
