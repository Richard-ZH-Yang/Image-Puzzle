#include "chain.h"
#include <cmath>
#include <iostream>
// PA1 functions


/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  /* your code here */
if(!other.head_){
    clear();
  }else{
    length_ = 0;
    Node * curr = other.head_;
    head_ = new Node(curr -> data);
    Node * temp = head_;
    length_ ++;
    while (curr ->next){

      curr = curr->next;
      Node *temp2 = new Node(curr -> data);
      temp -> next = temp2;
      temp2 -> prev = temp;
      temp = temp -> next;
      temp -> next = NULL;
      length_ ++;
    }
    
  }

}


/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
if(p == NULL){
    p = new Node(ndata);
    length_ ++;
    head_ = p;
    return p;
  }else {
    Node * newNode = new Node(ndata);
    Node* temp = head_;
  while(temp != p){
    temp = temp -> next;
  }
  temp -> next = newNode;
  newNode -> prev = temp;
  newNode -> next = NULL;
  length_ ++;
  return newNode;
  }

}


/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  clear();

}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  if (!head_) {
    length_ = 0;
    return;
  }

  Node *temp = head_->next;

  while (temp){
    Node *toDelete = temp;
    temp = temp->next;
    delete toDelete;
  }
  
  delete head_;
  head_ = NULL;

  length_ = 0;
}


/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  if (!p || !q || p == q) {
    return;
  }


  Node *p_prev = p->prev;  
  Node *p_next = p->next;
  Node *q_prev = q->prev;
  Node *q_next = q->next;

  if (p_prev != q && p_next != q) {

    if (p_prev) {
      p_prev->next = q;
    }

    if (q_prev) {
      q_prev->next = p;
    }

    if (p_next) {
      p_next->prev = q;
    }

    if (q_next) {
      q_next->prev = p;
    }

    p->next = q_next;
    p->prev = q_prev;
    q->next = p_next;
    q->prev = p_prev;

    if (head_ == p){
      head_ = q;
    } else if (head_ == q){
      head_ = p;
    }

  } else {
    if (length_ == 2) {
      if (p == head_) {
        p->next = NULL;
        p->prev = q;
        q->next = p;
        q->prev = NULL;
        head_ = q;
      } else {
        q->next = NULL;
        q->prev = p;
        p->next = q;
        p->prev = NULL;
        head_ = p;
      }
    } else if (p == head_ || q == head_) {
      if (p == head_) {
        p->next = p->next->next;
        q->prev = NULL;
        p->prev = q;
        q->next->prev = p;
        q->next = p;
        head_ = q;
      } else {
        q->next = q->next->next;
        p->prev = NULL;
        q->prev = p;
        p->next->prev = q;
        p->next = q;
        head_ = p;
      }
    } else if (!p->next || !q->next) {
      if (!p->next) {
        p->prev = p->prev->prev;
        p->next = q;
        q->prev->next = p;
        q->prev = p;
        q->next = NULL;
      } else {
        q->prev = q->prev->prev;
        q->next = p;
        p->prev->next = q;
        p->prev = q;
        p->next = NULL;
      }

    } else {
      if(p -> next == q){
          p -> prev -> next = q;
          q -> prev = p -> prev;
          p -> next = q -> next;
          q -> next -> prev = p;
          q -> next = p;
          p -> prev = q;
      }else{
          q -> prev -> next = p;
          q -> prev = q -> prev;
          q -> next = p -> next;
          p -> next -> prev = q;
          p -> next = q;
          q -> prev = p;
      }
    }
  }

}


/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *  This block is the one whose closest match (to the left) is the
 *  largest.  That is, the distance (using distanceTo) to this block 
 *  is big for all other blocks.
 *  For each block B, find the distanceTo B from every other block
 *  and take the minimum of these distances as B's "value".
 *  Choose the block B with the maximum value over all blocks and
 *  swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  Node *curr = head_;
  double maxValue = 0;
  double value = 0;
  Node *max = head_;
  Node *min;
  Node *temp = head_;
  double minValue = 0;
  double total = 0;
  
  while(curr) {
    temp = head_;
    total = 0;
    while(temp) {
      value = temp->data.distanceTo(curr->data);
      total += value;
      temp = temp->next;
    }

    if (total > maxValue) {
      maxValue = total;
      max = curr;
    }
    curr = curr->next;
  }

  swap(max, head_);
  head_ = max;
  curr = head_;
  min = curr->next;

  while(curr->next) {
    temp = curr->next;
    minValue = curr->data.distanceTo(temp->data);
    min = temp;
    while(temp) {
      value = curr->data.distanceTo(temp->data);
      if (value < minValue) {
        minValue = value;
        min = temp;
      }
      temp = temp->next;
    }

    swap (min, curr->next);
    curr = curr->next;
  }
  
}

