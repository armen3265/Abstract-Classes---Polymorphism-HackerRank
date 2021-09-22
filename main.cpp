#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
class LRUCache : public Cache
{
public:
  LRUCache(int capacity)
  {
    cp = capacity;
    head = NULL;
    tail = NULL;
  }
  void set(int key, int value) override
  {
    if (mp.find(key) != mp.end())
    {
      mp[key]->value = value;
    }
    else
    {
      mp[key] = new Node(nullptr, head, key, value);
      if (head)
      {
        head->prev = mp[key];
        head = mp[key];
      }
      else
      {
        head = mp[key];
      }
      if (!tail) {
        tail = head;
      }
      if (mp.size() > cp)
      {
        mp.erase(tail->key);
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
      }
    }
  }

  int get(int key) override {
    if (mp.find(key) == mp.end())
    {
      set(key, -1);
      return mp[key]->value;
    }
    if (mp[key]->next == nullptr)
    {
      if (tail->prev) {
        tail = mp[key]->prev;
        mp[key]->next = head;
        head = mp[key];
      }
      return head->value;

    }
    if (mp[key]->prev == nullptr)
    {
      return mp[key]->value;
    }
    Node* tNext = mp[key]->next, * tPrev = mp[key]->prev;
    tNext->prev = tPrev;
    tPrev->next = tNext;
    mp[key]->next = head;
    head = mp[key];
    return head->value;
  }
};
int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
