#ifndef DATASRUCTURES_HEAP_H
#define DATASRUCTURES_HEAP_H

#include "cassert"
#include <new>

#define RIGHT 1
#define LEFT 0
#define HEAP_LOG_SIZE 100


namespace heap {
    typedef enum {
        HP_SUCCESS = 0,
        HP_FAILURE = -1,
        HP_ALLOCATION_ERROR = -2
    } StatusHeap;

    template<class T>
    class Heap {
    private:
        class Vertex {
        private:
            T data;
            int index;
            Vertex *leftV;
            Vertex *rightV;
            friend class Heap<T>;
        public:
            Vertex *siftDown() {
                if (this->rightV == NULL && this->leftV == NULL) {
                    return this;
                }
                if (this->getData() < this->leftV->getData()) {
                    if (this->rightV == NULL || this->getData() < this->rightV->getData())
                        return this;
                }
                if (this->rightV == NULL ||
                    this->leftV->getData() < this->rightV->getData()) {
                    Vertex *temp = this->rightV;
                    Vertex *min = this->leftV;
                    this->rightV = min->rightV;
                    this->leftV = min->leftV;
                    min->leftV = this;
                    min->rightV = temp;
                    int tempIndex = min->index;
                    min->index = this->index;
                    this->index = tempIndex;
                    min->leftV = this->siftDown();
                    return min;
                }
                if (this->rightV != NULL) {
                    Vertex *temp = this->leftV;
                    Vertex *min = this->rightV;
                    this->rightV = min->rightV;
                    this->leftV = min->leftV;
                    min->rightV = this;
                    min->leftV = temp;
                    int tempIndex = min->index;
                    min->index = this->index;
                    this->index = tempIndex;
                    min->rightV = this->siftDown();
                    return min;
                }
                return this;
            }

            /*constructor*/
            Vertex(const T &data, const int &index) : data(data), index(index),
                                                      leftV(NULL),
                                                      rightV(NULL) {}

            /*
            * destructor of the vertex removing all sub vertices recursively
            */
            ~Vertex() {
                delete (this->leftV);
                delete (this->rightV);
            }

            /*return const reference to the data in the vertex*/
            const T &getData() const {
                return this->data;
            }

            /*set the data in the vertex to the new one*/
            void setData(const T &newData) {
                this->data = newData;
                return;
            }

            /*set the index in the vertex to the new one*/
            void setIndex(const int &newIndex) {
                this->index = newIndex;
                return;
            }

            /*return const reference to the index in the vertex*/
            const T &getIndex() const {
                return this->index;
            }


            Vertex *siftUp(const int &index, int *binDigit, int currentTurn) {
                //base case: the index is in the root or the tree is the requested index
                if (this->getIndex() == index) {
                    assert(currentTurn == -1);
                    return this;
                }
                if (binDigit[currentTurn] == RIGHT && this->rightV != NULL) {
                    this->rightV = this->rightV->siftUp(index, binDigit, currentTurn - 1);
                    if (this->getData() > this->rightV->getData()) {
                        Vertex *temp = this->leftV;
                        Vertex *min = this->rightV;
                        this->rightV = min->rightV;
                        this->leftV = min->leftV;
                        min->rightV = this;
                        min->leftV = temp;
                        int tempIndex = min->index;
                        min->index = this->index;
                        this->index = tempIndex;
                        return min;
                    }
                } else {
                    if (this->leftV != NULL) {
                        this->leftV = this->leftV->siftUp(index, binDigit,
                                                          currentTurn - 1);
                        if (this->getData() > this->leftV->getData()) {
                            Vertex *temp = this->rightV;
                            Vertex *min = this->leftV;
                            this->rightV = min->rightV;
                            this->leftV = min->leftV;
                            min->leftV = this;
                            min->rightV = temp;
                            int tempIndex = min->index;
                            min->index = this->index;
                            this->index = tempIndex;
                            return min;
                        }
                    }
                }
                return this;
            }

            Vertex *
            makeTree(T *arr, void **addressing, const int &currentIndex, const int &
            arrSize) {
                if (currentIndex > arrSize)
                    return NULL;
                Vertex *new_vertex = new Vertex(arr[currentIndex - 1], currentIndex);
                addressing[currentIndex - 1] = (void *) new_vertex;
                new_vertex->leftV = makeTree(arr, addressing, currentIndex * 2, arrSize);
                new_vertex->rightV = makeTree(arr, addressing, (currentIndex * 2) + 1,
                                              arrSize);
                return new_vertex;
            }


            /*get reference of a key and splay it's vertex to the root,
             * if not found splay the last vertex reached*/
            Vertex *find(const int &index, int *binDigit, int currentTurn) {
                //base case: the index is in the root or the tree is the requested index
                if (this->getIndex() == index) {
                    return this;
                }
                if (currentTurn < 0) {
                    return NULL;
                }
                if (binDigit[currentTurn] == RIGHT) {
                    return this->rightV->find(index, binDigit, currentTurn - 1);
                }
                assert(binDigit[currentTurn] == LEFT);
                return this->leftV->find(index, binDigit, currentTurn - 1);
            }
        };

/************************* end of Vertex implementation**********************/
        int size;
        Vertex *root;

        int binaryBase(int num, int *binDigits) {
            int currentTurn = 0;
            while (num > 0) {
                binDigits[currentTurn] = num % 2;
                currentTurn++;
                num = num / 2;
            }
            return currentTurn - 1;
        }

        Vertex *find(const int &index) {
            if (index > size || index <= 0) {
                return NULL;
            }
            int binDigits[HEAP_LOG_SIZE]; //maximum heap size of 2^100
            int currentTurn = this->binaryBase(index, binDigits);
            return this->root->find(index, binDigits, currentTurn - 1);
        }

    public:
        /*constructor new heap with size of n
         * complexity: O(1)*/
        Heap() : size(0), root(NULL) {};

        /*destructor the heap of size n
        * complexity: O(n)*/
        ~Heap() {
            delete (root);
        }

        /*add the data from the array to the tree and arrange it by minimum heap
         * conventions and exporting the addressing of each data in the heap
         * complexity: O(n)*/
        StatusHeap makeHeap(T *arr, void **addressing, const int &size) {
            assert(root == NULL);
            if (arr == NULL || size <= 0) {
                return HP_FAILURE;
            }
            try {
                this->size = size;
                this->root = this->root->makeTree(arr, addressing, 1, size);
                for (int i = size / 2; i > 0; i--) {
                    if (i != 1) {
                        Vertex *father = this->find(i / 2);


                        if (i % 2 == 0) {
                            father->leftV = father->leftV->siftDown();
                        } else
                            father->rightV = father->rightV->siftDown();
                    } else
                        this->root = this->root->siftDown();
                }
                return HP_SUCCESS;
            } catch (const std::bad_alloc &) {
                return HP_ALLOCATION_ERROR;
            }
        }

        int getSize() const {
            return this->size;
        }

        /*insert new data to the heap
         * complexity: O(log(n))*/
        StatusHeap insert(const T &data, void **address) {
            assert(address != NULL);
            try {
                Vertex *newVertex = new Vertex(data, size + 1);
                (*address) = newVertex;
                if(this->root == NULL){
                    this->root=newVertex;
                }
                else {
                    Vertex *father = this->find((size + 1) / 2);
                    if ((size + 1) % 2 == LEFT) {
                        assert(father->leftV == NULL);
                        father->leftV = newVertex;
                    } else {
                        assert(father->rightV == NULL);
                        father->rightV = newVertex;
                    }
                }
                this->size++;

                int binDigits[HEAP_LOG_SIZE]; //maximum heap size of 2^100
                int currentTurn = this->binaryBase(newVertex->getIndex(), binDigits);
                this->root = this->root->siftUp(newVertex->getIndex(), binDigits,
                                                currentTurn - 1);
                return HP_SUCCESS;
            } catch (const std::bad_alloc &) {
                return HP_ALLOCATION_ERROR;
            }
        }

        /*insert new id to the heap, if the heap is full reallocate new heap with size
         *twice
         * complexity: O(log(n))*/
        StatusHeap decK(void *pointerV, const T &newData) {
            assert(pointerV != NULL);
            Vertex *vertexP = (Vertex *) pointerV;
            if (vertexP->getData() <= newData) {
                return HP_FAILURE;
            }
            assert(vertexP->getData() > newData);
            vertexP->setData(newData);
            int binDigits[HEAP_LOG_SIZE]; //maximum heap size of 2^100
            int currentTurn = this->binaryBase(vertexP->getIndex(), binDigits);
            this->root = this->root->siftUp(vertexP->getIndex(), binDigits,
                                            currentTurn - 1);
            return HP_SUCCESS;
        }

        /*delete the root of the heap
         * complexity: O(log(n))*/
        StatusHeap deleteMin() {
            if (this->size == 0) {
                assert(this->root == NULL);
                return HP_FAILURE;
            }
            if (this->size == 1) {
                delete (this->root);
                this->root = NULL;
                this->size--;
                return HP_SUCCESS;
            }
            Vertex *max_index_vertex = this->find(this->size);
            Vertex *max_index_vertex_father = this->find(
                    max_index_vertex->getIndex() / 2);
            if (max_index_vertex->getIndex() % 2 == LEFT) {
                max_index_vertex_father->leftV = NULL;
                assert(max_index_vertex_father->rightV == NULL);
            } else {
                assert(max_index_vertex->getIndex() % 2 == RIGHT);
                max_index_vertex_father->rightV = NULL;
            }
            max_index_vertex->rightV = this->root->rightV;
            max_index_vertex->leftV = this->root->leftV;
            max_index_vertex->setIndex(1);
            this->root->leftV = NULL;
            this->root->rightV = NULL;
            delete (this->root);
            this->size--;
            this->root = max_index_vertex;
            this->root = this->root->siftDown();
            return HP_SUCCESS;
        }

        /*return refernce to the root of the heap
        * complexity: O(1)*/
        const T& getMin(){
            assert(this->root !=NULL);
            return this->root->getData();
        }
    };
}
#endif //DATASRUCTURES_HEAP_H
