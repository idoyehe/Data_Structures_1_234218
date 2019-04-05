#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

#include <cassert>
#include <exception>
#include <new>
#include <stdlib.h>

#define START_SIZE 0
#define EQUAL 0


namespace splayTree {

    typedef enum {
        TREE_SUCCESS = 0,
        TREE_FAILURE = -1,
        TREE_ALLOCATION_ERROR = -2
    } StatusTree;


    template <class T>
    class SplayTree {
    private:
/************************* begin of Vertex implementation**********************/
        class Vertex {
        private:
            T data;
            Vertex *leftV;
            Vertex *rightV;

            /*
             * rotating the vertex to the left
             */
            Vertex *LL_Rotate() {
                assert(this->leftV != NULL);
                Vertex *temp = this->leftV;
                this->leftV = temp->rightV;
                temp->rightV = this;
                return temp;
            }

            /*
             * rotating the vertex to the right
             */
            Vertex *RR_Rotate() {
                assert(this->rightV != NULL);
                Vertex *temp = this->rightV;
                this->rightV = temp->leftV;
                temp->leftV = this;
                return temp;
            }

        public:
            /*constructor*/
            Vertex(const T& data) : data(data), leftV(NULL), rightV(NULL) {};

            /*
            * destructor of the vertex removing all sub vertices recursively
            */
            ~Vertex() {
                delete (this->leftV);
                delete (this->rightV);
            }

            /*return const reference to the data in the vertex*/
            const T& getData() const {
                return this->data;
            }

            /*return reference to the data in the vertex*/
             T* getDataRef()  {
                return &(this->data);
            }

            /*get reference of a key and splay it's vertex to the root,
             * if not found splay the last vertex reached*/
            Vertex* find(const T& key) {
                //base case: the key is in the root or the tree is empty
                if (this->getData() == key) {
                    return this;
                }
                //case: the required key is on the left side of the root
                if (this->getData() > key) {

                    //case: left sub tree does NOT exist
                    if (this->leftV == NULL) return this;

                    //key is in the left vertex sub tree
                    if (this->leftV->getData() != key) {
                        this->leftV = this->leftV->find(key);
                    }
                    return this->LL_Rotate();

                }
                assert(this->getData() <  key);
                //case: right sub tree does NOT exist
                if (this->rightV == NULL) return this;

                //key is in the right vertex sub tree
                if (this->rightV->getData() != key) {
                    this->rightV = this->rightV->find(key);
                }
                return this->RR_Rotate();
            }

            /*find the min key vertex and splay it all the way to the root*/
            Vertex *findMin() {
                if (this->leftV == NULL) {
                    return this;
                }
                this->leftV = this->leftV->findMin();
                return this->LL_Rotate();
            }

            /*find the max key vertex and splay it all the way to the root*/
            Vertex *findMax() {
                if (this->rightV == NULL) {
                    return this;
                }
                this->rightV = this->rightV->findMax();
                return this->RR_Rotate();
            }

            /*join 2 splay trees to one big tree
             * ASSERTION: key(x)<key(y) for all x in this and all y in root
             */
            Vertex *join(Vertex *root2) {
                assert(root2 != NULL);
                Vertex *root1 = this->findMax();
                root1->rightV = root2;
                return root1;
            }

            /*split this tree to 2 trees trees by the pivot and export them into 2 pointers
             * key(x) <= pivot for all x in t1
             * key(y)> pivot for all y in t2
             */
            void split(Vertex **t1, Vertex **t2, const T& pivot) {
                assert(t1 != NULL && t2 != NULL);
                *t1 = this->find(pivot);
                if ((*t1)->getData() < pivot ||(*t1)->getData() == pivot ) {
                    *t2 = (*t1)->rightV;
                    (*t1)->rightV = NULL;
                } else {
                    *t2 = *t1;
                    *t1 = (*t2)->leftV;
                    (*t2)->leftV = NULL;
                }
                return;
            }

            /*insert new allocated vertex into the root
             * of the tree by using split*/
            Vertex *insertV(Vertex *vertexToInsert){
                Vertex *t1 = NULL;
                Vertex *t2 = NULL;
                this->split(&t1, &t2, vertexToInsert->getData());
                vertexToInsert->leftV = t1;
                vertexToInsert->rightV = t2;
                return vertexToInsert;
            }

            /*removing the root of the tree, by using join,
             * BUT does NOT deallocate it, export it by pointer*/
            Vertex *removeRoot(Vertex **oldRoot) {
                assert(oldRoot != NULL);
                *oldRoot=this;
                if(this->leftV == NULL) {//case: only right sub tree
                    Vertex* newRoot = this->rightV;
                    this->leftV = NULL;
                    this->rightV = NULL;
                    return newRoot;
                }
                if(this->rightV == NULL) {//case: only left sub tree
                    Vertex* newRoot = this->leftV;
                    this->leftV = NULL;
                    this->rightV = NULL;
                    return newRoot;
                }
                //case: two sub trees
                Vertex* newRoot = this->leftV->join(this->rightV);
                this->leftV = NULL;
                this->rightV = NULL;
                return newRoot;
            }

            /*print the tree into an array by inorder*/
            void inorderToArr(int& current_index, T* output) {
                if (this->leftV != NULL) {
                    this->leftV->inorderToArr(current_index, output);
                }
                output[current_index] = this->getData();
                (current_index)++;
                if (this->rightV != NULL) {
                    this->rightV->inorderToArr(current_index, output);
                }
                return;
            }

            /*print keys from sorted array to tree by inorder */
            void arrToTree(int& current_index, T *input) {
                if (this->leftV != NULL) {
                    this->leftV->arrToTree(current_index, input);
                }
                this->data = input[current_index];
                (current_index)++;
                if (this->rightV != NULL) {
                    this->rightV->arrToTree(current_index, input);
                }
                return;
            }

            /*run manipulation on the tree keys without changing them*/
            template <typename Manipulation>
            StatusTree inorderManipulation(const Manipulation& manipulation) const{
                if (this->leftV != NULL) {
                    this->leftV->inorderManipulation(manipulation);
                }
                if (manipulation(this->getData()) == TREE_ALLOCATION_ERROR){
                    return TREE_ALLOCATION_ERROR;
                }
                if (this->rightV != NULL) {
                    this->rightV->inorderManipulation(manipulation);
                }
                return TREE_SUCCESS;
            }


        };

/************************* end of Vertex implementation**********************/
        Vertex* root;
        int size;
        Vertex* max;
/********************begin Splay Tree implementation***************************/
    public:
        /*constructor of the splay tree gets compare function only*/
        explicit SplayTree() : root(NULL), size(START_SIZE),max(NULL){}

        /*get a reference to key and try to find it in the tree using vertex find function*/
        StatusTree find(const T& key) {
            if (this->root==NULL){
                return TREE_FAILURE;
            }
            this->root = this->root->find(key);
            if (this->getRoot() == key) {
                return TREE_SUCCESS;
            }
            return TREE_FAILURE;
        }

        /*insert a key to the tree, it does NOT check if the key already inside!! update max and size as well
        * ALLOCATION_ERROR-> when allocating new vertex fails
        * SUCCESS -> when the key inserted to the tree*/
        StatusTree insertKey(const T& key) {
            if (this->root != NULL && this->find(key)==TREE_SUCCESS){
                return TREE_FAILURE;
            }
            try {
                Vertex* vertexToInsert = new Vertex(key);
                if (this->root == NULL) {
                    this->root = vertexToInsert;
                    this->size++;
                    this->max=vertexToInsert;
                    return TREE_SUCCESS;
                }
                this->root = this->root->insertV(vertexToInsert);
                this->size++;
                if(key > this->max->getData()){
                    this->max=root;
                }
                assert(root==vertexToInsert);
                return TREE_SUCCESS;
            }catch (const std::bad_alloc&) {
                return TREE_ALLOCATION_ERROR;
            }
        }

        /*gets a reference to key and splay it to the root and remove it using vertex remove root function
         * FAILURE-> when key does NOT found
         * SUCCESS-> remove successfully from the tree*/
        StatusTree deleteKey(const T& duplicateKey) {
            if (this->root != NULL && this->find(duplicateKey) == TREE_FAILURE) {
                return TREE_FAILURE;
            }
            assert(this->root->getData() == duplicateKey);
            Vertex* oldRoot = NULL;
            this->root = this->root->removeRoot(&oldRoot);
            assert(oldRoot->getData() == duplicateKey);
            this->size--;
            if(size > 0 && this->max == oldRoot){
                this->root=this->root->findMax();
                this->max=this->root;
            }
            if(size==0){
                this->max=NULL;
            }
            delete(oldRoot);
            return TREE_SUCCESS;
        }

        /*print the splay tree into a given array using inorder, at the end the array is sorted
         * ASSERTION: the tree and the array have the same size
         * FAILURE-> when the tree is empty
         * SUCCESS-> otherwise*/
        StatusTree treeToArr(T* output) {
            if (this->root == NULL) {
                return TREE_FAILURE;
            }
            int i = 0;
            this->root->inorderToArr(i, output);
            return TREE_SUCCESS;
        }

        /*print a sorted array into the splay tree
         * ASSERTION: the tree and the array have the same size
         * FAILURE-> when the tree is empty, or the array is not sorted
         * SUCCESS-> otherwise*/
        StatusTree arrToTree(T* input, const int& array_size) {
            if (this->root == NULL || array_size != this->getSize()) {
                return TREE_FAILURE;
            }

            for (int i=0; i < array_size-1; i++){
                if(input[i] > input[i+1]){
                    return TREE_FAILURE;
                }
            }
            int index = 0;
            this->root->arrToTree(index, input);
            return TREE_SUCCESS;
        }

        template <typename Manipulation>
        /*run manipulation on the tree keys without changing them*/
        StatusTree keysManipulation(const Manipulation& manipulation) const {
            return this->root->inorderManipulation(manipulation);
        }


        /*return the size of the tree*/
        int getSize() const {
            return this->size;
        }

        /*return a const reference to the max key in the tree
         * ASSERTION: the tree is NOT empty*/
        const T& getMaxKey() const {
            assert(this->root != NULL);
            return this->max->getData();
        }

        /*return a reference to the root key in the tree
         * ASSERTION: the tree is NOT empty and the user does NOT chenge the ID of tyhe key*/
        T* getRootRef() const{
            assert(this->root != NULL);
            return this->root->getDataRef();
        }

        /*return a const reference to the root key in the tree
        * ASSERTION: the tree is NOT empty*/
        const T& getRoot() const {
            assert(this->root != NULL);
            return this->root->getData();
        }


        /*return true if the tree is empty otherwise false*/
        bool isEmpty()const {
            return this->getSize()==0;
        }

        /*recursive destructor using vertex destructor*/
        ~SplayTree() {
            delete (this->root);
        }


    };
}
#endif //WET1_SPLAYTREE_H
