/*******************************************************************************
 *                                                                             *
 * tree.h - Search tree interface for OS's without direct SEH support.         *
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


#ifndef __LIBSEH_TREE_H__
#define __LIBSEH_TREE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long tree_key_t;
typedef void* tree_value_t;

#define RESULT_OK         0
#define RESULT_FAIL       1

struct _tree_node;
typedef struct _tree_node *tree_t;

/**
 * Create a tree.
 * 
 * @return NULL - this is a dumb placeholder function
 *         that is no longer really needed.  
 */
tree_t tree_create();

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
int tree_insert(tree_t* t, tree_key_t k, tree_value_t v);

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
int tree_search(tree_t* t, tree_key_t k, tree_value_t* v);

/**
 * Delete a node from a tree.
 * 
 * @param t      The tree to act upon.
 * @param k      The key of the node to be deleted.
 * 
 * @return RESULT_OK - the node was found and deleted.
 *         RESULT_FAIL - the node was not found.
 */
int tree_delete(tree_t* t, tree_key_t k);

/**
 * Destroy a tree node and all of it's sub nodes.
 * 
 * @param t      The tree to destroy.
 */
void tree_destroy(tree_t* t);

#ifdef __cplusplus
}
#endif


#endif


