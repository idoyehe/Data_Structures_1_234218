#include "rankSplayTree.h"

#define START_SIZE 0

/************************* begin of Vertex implementation**********************/

splayTree::RankSplayTree::Vertex *splayTree::RankSplayTree::Vertex::LL_Rotate() {
    assert(this->leftV != nullptr);
    Vertex *temp = this->leftV;
    this->leftV = temp->rightV;
    this->leftTreeScore = temp->rightTreeScore;
    this->leftTreeSize = temp->rightTreeSize;
    temp->rightV = this;
    temp->rightTreeScore = this->rightTreeScore
                           + this->leftTreeScore
                           + this->vertex_score;
    temp->rightTreeSize = this->rightTreeSize
                          + this->leftTreeSize + 1;
    return temp;
}

splayTree::RankSplayTree::Vertex *splayTree::RankSplayTree::Vertex::RR_Rotate() {
    assert(this->rightV != nullptr);
    Vertex *temp = this->rightV;
    this->rightV = temp->leftV;
    this->rightTreeScore = temp->leftTreeScore;
    this->rightTreeSize = temp->leftTreeSize;
    temp->leftV = this;
    temp->leftTreeScore = this->rightTreeScore
                          + this->leftTreeScore
                          + this->vertex_score;
    temp->leftTreeSize = this->rightTreeSize
                         + this->leftTreeSize + 1;
    return temp;
}

splayTree::RankSplayTree::Vertex::Vertex(const GladiatorByScore &data) :
                    data(data), leftV(nullptr), rightV(nullptr),
                    vertex_score(data.getGladiatorScore()),leftTreeScore(0),
                    leftTreeSize(0),rightTreeScore(0),rightTreeSize(0) {}

splayTree::RankSplayTree::Vertex::~Vertex() {
    delete (this->leftV);
    delete (this->rightV);
}

const GladiatorByScore &splayTree::RankSplayTree::Vertex::getData() const {
    return this->data;
}

splayTree::RankSplayTree::Vertex *
splayTree::RankSplayTree::Vertex::find(const GladiatorByScore &key) {
    //base case: the key is in the root or the tree is empty
    if (this->getData() == key) {
        return this;
    }
    //case: the required key is on the left side of the root
    if (this->getData() > key) {

        //case: left sub tree does NOT exist
        if (this->leftV == nullptr) return this;

        //key is in the left vertex sub tree
        if (this->leftV->getData() != key) {
            this->leftV = this->leftV->find(key);
        }
        return this->LL_Rotate();

    }
    assert(this->getData() < key);
    //case: right sub tree does NOT exist
    if (this->rightV == nullptr) return this;

    //key is in the right vertex sub tree
    if (this->rightV->getData() != key) {
        this->rightV = this->rightV->find(key);
    }
    return this->RR_Rotate();
}

splayTree::RankSplayTree::Vertex *
splayTree::RankSplayTree::Vertex::findKPivot(const int &k, int &refLocation) {//    //base case: the key is in the root or the tree is empty
    if (this->rightTreeSize + refLocation + 1 == k) {
        return this;
    }
    //case: the required key is on the left side of the root
    if (this->rightTreeSize + refLocation + 1 > k) {
        assert(this->rightV != nullptr);
        return this->rightV->findKPivot(k, refLocation);

    }
    assert(this->rightTreeSize + refLocation + 1 < k);
    assert(this->leftV != nullptr);
    refLocation += (1 + this->rightTreeSize);
    return this->leftV->findKPivot(k, refLocation);
}

splayTree::RankSplayTree::Vertex *splayTree::RankSplayTree::Vertex::findMin() {
    if (this->leftV == nullptr) {
        return this;
    }
    this->leftV = this->leftV->findMin();
    return this->LL_Rotate();
}

splayTree::RankSplayTree::Vertex *splayTree::RankSplayTree::Vertex::findMax() {
    if (this->rightV == nullptr) {
        return this;
    }
    this->rightV = this->rightV->findMax();
    return this->RR_Rotate();
}

splayTree::RankSplayTree::Vertex *
splayTree::RankSplayTree::Vertex::join(splayTree::RankSplayTree::Vertex *root2) {
    assert(root2 != nullptr);
    Vertex *root1 = this->findMax();
    root1->rightV = root2;
    root1->rightTreeScore = root2->rightTreeScore
                 + root2->leftTreeScore
                 + root2->vertex_score;
    root1->rightTreeSize = root2->rightTreeSize
                + root2->leftTreeSize + 1;
    return root1;
}

void splayTree::RankSplayTree::Vertex::split(splayTree::RankSplayTree::Vertex **t1,
                                             splayTree::RankSplayTree::Vertex **t2,
                                             const GladiatorByScore &pivot) {
    assert(t1 != nullptr && t2 != nullptr);
    *t1 = this->find(pivot);
    if ((*t1)->getData() < pivot || (*t1)->getData() == pivot) {
        *t2 = (*t1)->rightV;
        (*t1)->rightV = nullptr;
        (*t1)->rightTreeScore = 0;
        (*t1)->rightTreeSize = 0;
    } else {
        *t2 = *t1;
        *t1 = (*t2)->leftV;
        (*t2)->leftV = nullptr;
        (*t2)->leftTreeScore = 0;
        (*t2)->leftTreeSize = 0;

    }
}

splayTree::RankSplayTree::Vertex *splayTree::RankSplayTree::Vertex::insertV(
        splayTree::RankSplayTree::Vertex *vertexToInsert) {
    Vertex *t1 = nullptr;
    Vertex *t2 = nullptr;
    this->split(&t1, &t2, vertexToInsert->getData());
    vertexToInsert->leftV = t1;
    vertexToInsert->rightV = t2;
    if (t1 != nullptr) {
        vertexToInsert->leftTreeScore = t1->rightTreeScore
                                        + t1->leftTreeScore
                                        + t1->vertex_score;
        vertexToInsert->leftTreeSize = t1->rightTreeSize
                                       + t1->leftTreeSize + 1;
    }
    if (t2 != nullptr) {
        vertexToInsert->rightTreeScore = t2->rightTreeScore
                                         + t2->leftTreeScore
                                         + t2->vertex_score;
        vertexToInsert->rightTreeSize = t2->rightTreeSize
                                        + t2->leftTreeSize + 1;
    }
    return vertexToInsert;
}

splayTree::RankSplayTree::Vertex *
splayTree::RankSplayTree::Vertex::removeRoot(splayTree::RankSplayTree::Vertex **oldRoot) {
    assert(oldRoot != nullptr);
    *oldRoot = this;
    if (this->leftV == nullptr) {//case: only right sub tree
        Vertex *newRoot = this->rightV;
        this->leftV = nullptr;
        this->rightV = nullptr;
        (*oldRoot)->leftTreeScore = 0;
        (*oldRoot)->rightTreeScore = 0;
        (*oldRoot)->leftTreeSize = 0;
        (*oldRoot)->rightTreeSize = 0;
        return newRoot;
    }
    if (this->rightV == nullptr) {//case: only left sub tree
        Vertex *newRoot = this->leftV;
        this->leftV = nullptr;
        this->rightV = nullptr;
        (*oldRoot)->leftTreeScore = 0;
        (*oldRoot)->rightTreeScore = 0;
        (*oldRoot)->leftTreeSize = 0;
        (*oldRoot)->rightTreeSize = 0;
        return newRoot;
    }
    //case: two sub trees
    Vertex *newRoot = this->leftV->join(this->rightV);
    this->leftV = nullptr;
    this->rightV = nullptr;
    (*oldRoot)->leftTreeScore = 0;
    (*oldRoot)->rightTreeScore = 0;
    (*oldRoot)->leftTreeSize = 0;
    (*oldRoot)->rightTreeSize = 0;
    return newRoot;
}
int splayTree::RankSplayTree::Vertex::getScore() {
    return this->vertex_score + this->rightTreeScore;
}

/********************begin Splay Tree implementation***************************/
splayTree::RankSplayTree::RankSplayTree() : root(nullptr), size(START_SIZE) {}

splayTree::StatusTree splayTree::RankSplayTree::find(const GladiatorByScore &key) {
    if (this->root == nullptr) {
        return ST_FAILURE;
    }
    this->root = this->root->find(key);
    if (this->getRoot() == key) {
        return ST_SUCCESS;
    }
    return ST_FAILURE;
}

splayTree::StatusTree splayTree::RankSplayTree::findKpivot(const int &k) {
    assert(k > 0);
    if (k > this->size) {
        return ST_FAILURE;
    }
    int ref = 0;
    Vertex *kPivot = this->root->findKPivot(k, ref);
#ifndef  NDEBUG
    StatusTree res =
#endif
            this->find(kPivot->getData());
    assert(res == ST_SUCCESS);
    return ST_SUCCESS;
}

splayTree::StatusTree splayTree::RankSplayTree::insertKey(const GladiatorByScore &key) {
    if (this->root != nullptr && this->find(key) == ST_SUCCESS) {
        return ST_FAILURE;
    }
    try {
        Vertex *vertexToInsert = new Vertex(key);
        if (this->root == nullptr) {
            this->root = vertexToInsert;
            this->size++;
            return ST_SUCCESS;
        }
        this->root = this->root->insertV(vertexToInsert);
        this->size++;
        assert(root == vertexToInsert);
        return ST_SUCCESS;
    }
    catch (const std::bad_alloc &) {
        return ST_ALLOCATION_ERROR;
    }
}

splayTree::StatusTree
splayTree::RankSplayTree::deleteKey(const GladiatorByScore &duplicateKey) {
    if(this->root != nullptr && this->find(duplicateKey) == ST_FAILURE) {
        return ST_FAILURE;
    }
    assert(this->getRoot() == duplicateKey);
    Vertex *oldRoot = nullptr;
    this->root = this->root->removeRoot(&oldRoot);
    assert(oldRoot->getData() == duplicateKey);
    this->size--;
    delete (oldRoot);
    return ST_SUCCESS;
}

int splayTree::RankSplayTree::getSize() const {
    return this->size;
}

int splayTree::RankSplayTree::getRootScore() const {
    return this->root->getScore();
}

const GladiatorByScore &splayTree::RankSplayTree::getRoot() const {
    assert(this->root != nullptr);
    return this->root->getData();
}

bool splayTree::RankSplayTree::isEmpty() const {
    return this->getSize() == 0;
}

splayTree::RankSplayTree::~RankSplayTree() {

    delete (this->root);
}
