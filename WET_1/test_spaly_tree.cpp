#include "splayTree.h"
#include "gladiator.h"
#include "test_tools.h"

using namespace splayTree;


bool testConstructor(){
    SplayTree<int>* spt=new SplayTree<int>();
    ASSERT_EQUALS(spt->getSize(),0);
    delete (spt);
    return true;
}

bool testInsert(){
    SplayTree<int>* spt=new SplayTree<int>();
    ASSERT_EQUALS(spt->getSize(),0);
    int* keys=new int[6];
    for(int i=1;i<6;i++){
        keys[i]=i;
    }
    ASSERT_EQUALS(spt->insertKey(keys[3]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->getMaxKey(),keys[3]);
    ASSERT_EQUALS(spt->insertKey(keys[4]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->getMaxKey(),keys[4]);
    ASSERT_EQUALS(spt->insertKey(keys[1]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->getMaxKey(),keys[4]);
    ASSERT_EQUALS(spt->insertKey(keys[5]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->getMaxKey(),keys[5]);
    ASSERT_EQUALS(spt->insertKey(keys[2]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),5);
    ASSERT_EQUALS(spt->getMaxKey(),keys[5]);
    delete[] keys;
    delete spt;
    return true;
}

bool testFind(){
    SplayTree<int>* spt=new SplayTree<int>;
    ASSERT_EQUALS(spt->getSize(),0);
    int* keys=new int[6];
    for(int i=1;i<6;i++){
        keys[i]=i;
    }
    ASSERT_EQUALS(spt->insertKey(keys[3]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->getMaxKey(),keys[3]);
    ASSERT_EQUALS(spt->insertKey(keys[4]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->getMaxKey(),keys[4]);
    ASSERT_EQUALS(spt->insertKey(keys[1]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->getMaxKey(),keys[4]);
    ASSERT_EQUALS(spt->insertKey(keys[5]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->getMaxKey(),keys[5]);
    ASSERT_EQUALS(spt->insertKey(keys[2]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),5);
    ASSERT_EQUALS(spt->getMaxKey(),keys[5]);
    delete[] keys;
    int x=8;
    ASSERT_EQUALS(spt->find(x),TREE_FAILURE);
    ASSERT_EQUALS(spt->getRoot(),5);
    x=1;
    ASSERT_EQUALS(spt->find(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),1);
    x=2;
    ASSERT_EQUALS(spt->find(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),2);
    x=3;
    ASSERT_EQUALS(spt->find(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),3);
    x=4;
    ASSERT_EQUALS(spt->find(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),4);
    x=5;
    ASSERT_EQUALS(spt->find(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),5);
    x=0;
    ASSERT_EQUALS(spt->find(x),TREE_FAILURE);
    ASSERT_EQUALS(spt->getRoot(),1);
    delete spt;
    return true;
}

bool testDeleteKey(){
    SplayTree<int>* spt=new SplayTree<int>();
    ASSERT_EQUALS(spt->getSize(),0);
    int* keys=new int[6];
    for(int i=1;i<6;i++){
        keys[i]=i;
    }
    ASSERT_EQUALS(spt->insertKey(keys[3]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[4]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[1]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[5]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[2]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),keys[2]);
    delete[] keys;
    int x=8;
    ASSERT_EQUALS(spt->deleteKey(x),TREE_FAILURE);
    ASSERT_EQUALS(spt->getRoot(),5);
    x=3;
    ASSERT_EQUALS(spt->deleteKey(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    x=5;
    ASSERT_EQUALS(spt->deleteKey(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->getMaxKey(),4);
    x=4;
    ASSERT_EQUALS(spt->deleteKey(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->getMaxKey(),2);
    x=2;
    ASSERT_EQUALS(spt->deleteKey(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->getMaxKey(),1);
    x=1;
    ASSERT_EQUALS(spt->deleteKey(x),TREE_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),0);
    delete spt;
    return true;
}

bool testInorderToArr(){
    SplayTree<int>* spt=new SplayTree<int>();
    ASSERT_EQUALS(spt->getSize(),0);
    int* keys=new int[6];
    for(int i=0;i<6;i++){
        keys[i]=i;
    }
    ASSERT_EQUALS(spt->insertKey(keys[3]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[4]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[0]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[1]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[5]),TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[2]),TREE_SUCCESS);
    delete[](keys);
    ASSERT_EQUALS(spt->getSize(),6);
    int allkeys[6];
    spt->treeToArr(allkeys);
    ASSERT_EQUALS(allkeys[0],0);
    ASSERT_EQUALS(allkeys[1],1);
    ASSERT_EQUALS(allkeys[2],2);
    ASSERT_EQUALS(allkeys[3],3);
    ASSERT_EQUALS(allkeys[4],4);
    ASSERT_EQUALS(allkeys[5],5);
    delete(spt);
    return true;
}

bool testArrToInorder() {
    SplayTree<int> *spt = new SplayTree<int>();
    ASSERT_EQUALS(spt->getSize(), 0);
    int *keys = new int[6];
    for (int i = 0; i < 6; i++) {
        keys[i] = i;
    }
    ASSERT_EQUALS(spt->insertKey(keys[3]), TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[4]), TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[0]), TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[1]), TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[5]), TREE_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[2]), TREE_SUCCESS);
    delete[](keys);
    ASSERT_EQUALS(spt->getMaxKey(), 5);
    ASSERT_EQUALS(spt->getSize(), 6);
    int allkeys[6];
    spt->treeToArr(allkeys);
    ASSERT_EQUALS(allkeys[0], 0);
    ASSERT_EQUALS(allkeys[1], 1);
    ASSERT_EQUALS(allkeys[2], 2);
    ASSERT_EQUALS(allkeys[3], 3);
    ASSERT_EQUALS(allkeys[4], 4);
    ASSERT_EQUALS(allkeys[5], 5);
    for (int i = 0; i < 6; i++) {
        allkeys[i] *= 2;

    }
    ASSERT_EQUALS(spt->getMaxKey(), 5);
    ASSERT_EQUALS(spt->getRoot(), 2);
    spt->arrToTree(allkeys,6);
    ASSERT_EQUALS(spt->getMaxKey(), 10);
    ASSERT_EQUALS(spt->getRoot(), 4);
    delete (spt);
    return true;
}

using namespace colosseum::gladiator;

bool testInsertGladInIDTree(){
    SplayTree<GladiatorByID> *spt = new SplayTree<GladiatorByID>();
    ASSERT_EQUALS(spt->getSize(),0);
    int trainer=10;
    GladiatorByID*g1=new GladiatorByID(1,2,&trainer);
    spt->insertKey(*g1);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->getMaxKey() ,*g1);
    ASSERT_EQUALS(spt->getRoot(),*g1);
    delete (g1);
    GladiatorByID g3(3,2,&trainer);
    spt->insertKey(g3);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->getMaxKey(),g3);
    ASSERT_EQUALS(spt->getRoot(),g3);
    GladiatorByID g2(2,2,&trainer);
    spt->insertKey(g2);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->getMaxKey(),g3);
    ASSERT_EQUALS(spt->getRoot(),g2);
    GladiatorByID g5(5,2,&trainer);
    spt->insertKey(g5);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->getMaxKey(),g5);
    ASSERT_EQUALS(spt->getRoot(),g5);
    delete (spt);
    return true;
}

bool testInsertGladInLEVELTree(){
    SplayTree<GladiatorByLevel>* spt= new SplayTree<GladiatorByLevel>;
    ASSERT_EQUALS(spt->getSize(),0);
    int trainer=10;
    GladiatorByLevel*g1=new GladiatorByLevel(1,2,&trainer);
    spt->insertKey(*g1);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->getMaxKey(),*g1);
    ASSERT_EQUALS(spt->getRoot(),*g1);
    GladiatorByLevel g3(3,2,&trainer);
    spt->insertKey(g3);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->getMaxKey(),*g1);
    ASSERT_EQUALS(spt->getRoot(),g3);
    delete (g1);
    GladiatorByLevel g2(2,9,&trainer);
    spt->insertKey(g2);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->getMaxKey(),g2);
    ASSERT_EQUALS(spt->getRoot(),g2);
    GladiatorByLevel g5(5,25,&trainer);
    spt->insertKey(g5);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->getMaxKey(),g5);
    ASSERT_EQUALS(spt->getRoot(),g5);
    ASSERT_EQUALS(spt->find(g3),TREE_SUCCESS);
    ASSERT_EQUALS(spt->find(g2),TREE_SUCCESS);
    delete (spt);
    return true;
}


int main(){
    RUN_TEST(testConstructor);
    RUN_TEST(testInsert);
    RUN_TEST(testFind);
    RUN_TEST(testDeleteKey);
    RUN_TEST(testInorderToArr);
    RUN_TEST(testArrToInorder);
    RUN_TEST(testInsertGladInIDTree);
    RUN_TEST(testInsertGladInLEVELTree);
    return 0;
}