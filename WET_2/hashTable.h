#ifndef DATASRUCTURES_HASHTABLE_H
#define DATASRUCTURES_HASHTABLE_H

#include <cstdlib>
#include <new>

namespace hashTable{

    typedef enum {
        HT_SUCCESS = 0,
        HT_FAILURE = -1,
        HT_ALLOCATION_ERROR = -2
    } StatusHashTable;

    template <class T>
    class HashTable{
    private:
        class Node {
        private:
            T data;
            Node *next;

        public:
            /*
             * constructor copy data to the node and set next and prev to NULL
             */
            Node(const T &data):data(data), next(NULL) {};

            /*return pointer of the next node*/
            Node* getNext() const{
                return this->next;
            }
            /*return pointer of the data saved in the node*/
            T* getData() {
                return &(this->data);
            }

            /*set the next of the node to given pointer*/
            void setNext(Node* next){
                this->next = next;
                return;
            }

            /*destructor of all the node in the list*/
            ~Node(){
                delete(this->next);
            }
            /*get the key of the data saved in the node*/
            int getKeyData(){
                return this->data();//operator () that return the Key of the data T
            }

        };
        Node** table;
        int capacity;
        int tableSize;

        /*the hash function
         * complexity: O(1)*/
        int hashFunc(const int& key){
            return key % this->tableSize;
        }

        /*clean all the data from the table
         * complexity: O(n)*/
        void tableClean(Node** table,const int& size){
            for (int i=0; i < size;++i){
                delete(table[i]);
                table[i]=NULL;
            }
            return;
        }
        /*increase the table to bigger one and copy all the data to the new bigger table
         * complexity: O(n)*/
        void tableIncrease(){
            int oldSize = this->tableSize;
            int newSize = (2*oldSize) +1;
            Node** newTable = new Node*[newSize]();
            this->tableSize=newSize;
            for(int i = 0; i <oldSize ;++i){
                Node* currentNode=this->table[i];
                Node* handNode=currentNode;
                while(handNode !=NULL){
                    handNode = handNode->getNext();
                    int key = currentNode->getKeyData();
                    int indexToInsert = this->hashFunc(key);
                    currentNode->setNext(newTable[indexToInsert]);
                    newTable[indexToInsert] = currentNode;
                    currentNode = handNode;
                }
                this->table[i]=NULL;//disconnecting the old table from the nodes
            }
            delete[] (this->table);
            this->table = newTable;
        }

        /*get pointer to data saved in the table by key
        * average complexity: O(1)*/
        T* getDataPointer(const int& key) {
            int indexToSeek = this->hashFunc(key);
            Node *currentNode = this->table[indexToSeek];
            while (currentNode != NULL) {
                if (currentNode->getKeyData() == key) {
                    return currentNode->getData();
                }
                currentNode = currentNode->getNext();
            }
            return NULL;
        }
    public:
        /*constructor build new table with 2*(given size) + 1
         * complexity: O(n)*/
        explicit HashTable(int initSize) : table(NULL),capacity(0), tableSize((2*initSize)+1) {
            this->table = new Node* [tableSize]();
        }
        /*destructor deallocate all nodes and the table itself
         * complexity: O(n)*/
        ~HashTable() {
            this->tableClean(this->table,this->tableSize);
            delete[](this->table);
        }

        /*return HT_SUCCESS if and only if the key is exist in the table and export it
         * average complexity: O(1)*/
        StatusHashTable findData (const int& key, T** pointerEx){
            if (pointerEx == NULL){
                return  HT_FAILURE;
            }
            (*pointerEx) = this->getDataPointer(key);
            if( (*pointerEx) == NULL){
                return HT_FAILURE;
            }
            return HT_SUCCESS;
        }

        /* return true if and only if the key exist in the table
         * average complexity: O(1)*/
        bool isExist (const int& key){
            return (this->getDataPointer(key) !=NULL);
        }

        /*insert the data to table
         * estimate complexity: O(1)*/
        StatusHashTable insertData(const T& data) {
            int key = data();
            if(this->getDataPointer(key) !=NULL){
                return HT_FAILURE;
            }
            int indexToInsert = this->hashFunc(key);
            try {
                Node *newNode = new Node(data);
                newNode->setNext(this->table[indexToInsert]);
                this->table[indexToInsert] = newNode;
                this->capacity++;
                if (this->capacity == this->tableSize) {
                    this->tableIncrease();
                }
                return HT_SUCCESS;
            } catch (const std::bad_alloc &) {
                return HT_ALLOCATION_ERROR;
            }
        }
    };
}
#endif //DATASRUCTURES_HASHTABLE_H
