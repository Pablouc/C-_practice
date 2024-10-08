#include <iostream>
using namespace std;


struct Node{
    int key;
    int value;
    struct Node *next; // Pointer to the next node
    struct Node *prev; // Pointer to the previous node

    Node(int k, int v): key(k), value(v), next(nullptr), prev(nullptr) {}
};


class DoublyLinkedList {
private:
    Node *head; // Pointer to the head of the list
    Node *tail; // Pointer to the tail of the list
    int indexes=0;
    int size;

    public:
        DoublyLinkedList(): head(nullptr), tail(nullptr), size(0) {}

        int getSize(){
            return size;
        }
        Node* getTail(){
            return tail;
        }

        Node* getHead(){
            return head;
        }
        void addNodeToHead(Node* newNode){
            if(head == nullptr){
                head = newNode;
                tail = newNode;
            }
            else{
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            size++;
        }

        void removeTail(){
            if (tail == nullptr) return;
            
            Node* temp = tail;
    
            if (head == tail) {
                // Only one element in the list
                head = nullptr;
                tail = nullptr;
            } else {
                tail = tail->prev;
                tail->next = nullptr;
            }

            delete temp;
            size--;
        }

        void moveToHead(Node* node) {
        if (node == head) return; // Already at the head

        // Disconnect node from its current position
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;

        // If node is tail, update tail
        if (node == tail) {
            tail = node->prev;
        }

        // Move node to the head
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;

        // If tail was null (meaning list was empty), set tail as well
        if (tail == nullptr) {
            tail = head;
        }
    }


};


class LRUCache {

private:
    int capacity_;                // Maximum capacity of the cache
    unordered_map<int, Node*> cache; // Hash map for key-to-node lookup
    DoublyLinkedList linkedList;


public:
    LRUCache(int capacity) : capacity_(capacity) {}
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1; // Key not found
        }

        Node* node = cache[key];
        linkedList.moveToHead(node); // Move this node to the head as it's now most recently used
        return node->value;
    }
    
    void put(int key, int value) {
        if(get(key)!= -1){
            Node* node = cache[key];
            node->value = value;
        }
        else{
            Node* newNode = new Node(key,value);
            
            if(linkedList.getSize() == capacity_){
                int tailKey = linkedList.getTail()->key;
                linkedList.removeTail();
                cache.erase(tailKey);
            }
            
            linkedList.addNodeToHead(newNode);
            cache[key] = newNode;
            
        }
              
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
