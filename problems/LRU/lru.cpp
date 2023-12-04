#include <bits/stdc++.h>

class LruCache{
  public:
  class Node{
    public:
    int key;
    int val;

    Node* next;
    Node* prev;
    Node(int key, int val){
      this->key = key;
      this->val = val;
    }
 };
  Node* head = new Node(-1, -1);
  Node* tail = new Node(-1, -1);
  int cap;
  unordered_map<int, Node* >m;
  LruCache(int capacity){
    head->next = tail;
    tail->prev = head;
  }

  void addNode(Node* newNode){
    Node* tempNode = head->next;
    newNode->next = tempNode;
    newNode->prev = head;
    tempNode->prev = newNode;
    head->next = newNode;
  }

  void delNode(Node* delNode){
    // 1 2 3 4 5 0
    Node* delPrev = delNode->prev;
    Node* delNext = delNode->next;
    delPrev->next = delNext;
    delNext->prev = delPrev;
  }

  int get(int key_){
    if(m.find(key_)!=m.end()){
      Node* resnode = m[key_];
      int res = resnode->val;
      addNode(resnode);
      delNode(resnode);
      m[key_] = head->next;
      m.erase(res);
      return res;
    }

    return -1;
  }

  void put(int key_, int value){
    if(m.find(key_)!=m.end()){
      Node* resnode = m[key_];
      m.erase(key_);
      delNode(key_);
    }

    if(m.size() == cap){
      m.erase(tail->prev);
      delNode(tail->prev);
    }

    addNode(new Node(key_, value));
    m[key_] = head->next;
  }

};
