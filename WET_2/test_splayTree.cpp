#include "splayTree.h"
#include "gladiators.h"
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
    for(int i=0;i<6;i++){
        keys[i]=i;
    }
    ASSERT_EQUALS(spt->insertKey(keys[3]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->insertKey(keys[4]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(keys[1]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->insertKey(keys[5]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->insertKey(keys[2]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),5);
    ASSERT_EQUALS(spt->insertKey(keys[0]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),6);
    delete[] keys;
    delete spt;
    return true;
}

bool testFind(){
    SplayTree<int>* spt=new SplayTree<int>();
    ASSERT_EQUALS(spt->getSize(),0);
    int* keys=new int[6];
    for(int i=0;i<6;i++){
        keys[i]=i;
    }
    ASSERT_EQUALS(spt->insertKey(keys[3]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->insertKey(keys[4]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(keys[1]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->insertKey(keys[5]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->insertKey(keys[2]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),5);
    ASSERT_EQUALS(spt->insertKey(keys[0]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),6);
    delete[] keys;
    int x=8;
    ASSERT_EQUALS(spt->find(x),ST_FAILURE);
    ASSERT_EQUALS(spt->getRoot(),5);
    x=1;
    ASSERT_EQUALS(spt->find(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),1);
    x=2;
    ASSERT_EQUALS(spt->find(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),2);
    x=3;
    ASSERT_EQUALS(spt->find(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),3);
    x=4;
    ASSERT_EQUALS(spt->find(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),4);
    x=5;
    ASSERT_EQUALS(spt->find(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),5);
    x=-1;
    ASSERT_EQUALS(spt->find(x),ST_FAILURE);
    ASSERT_EQUALS(spt->getRoot(),0);
    x=0;
    ASSERT_EQUALS(spt->find(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),0);
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
    ASSERT_EQUALS(spt->insertKey(keys[3]),ST_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[4]),ST_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[1]),ST_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[5]),ST_SUCCESS);
    ASSERT_EQUALS(spt->insertKey(keys[2]),ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot(),keys[2]);
    delete[] keys;
    int x=1;
    ASSERT_EQUALS(spt->deleteKey(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    x=2;
    ASSERT_EQUALS(spt->deleteKey(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    x=5;
    ASSERT_EQUALS(spt->deleteKey(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    x=4;
    ASSERT_EQUALS(spt->deleteKey(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    x=3;
    ASSERT_EQUALS(spt->deleteKey(x),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),0);
    delete spt;
    return true;
}

using namespace colosseum::gladiator;

bool testInsertGladInIDTree(){
    SplayTree<GladiatorByID>* spt=new SplayTree<GladiatorByID>();
    ASSERT_EQUALS(spt->getSize(),0);
    GladiatorByID* g5=new GladiatorByID(5,5);
    spt->insertKey(*g5);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->getRoot(),*g5);
    GladiatorByID g3(3,2);
    spt->insertKey(g3);
    ASSERT_EQUALS(spt->getSize(),2);
    delete (g5);
    ASSERT_EQUALS(spt->getRoot(),g3);
    GladiatorByID g2(2,2);
    spt->insertKey(g2);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->getRoot(),g2);
    GladiatorByID g6(6,2);
    spt->insertKey(g6);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->getRoot(),g6);
    delete (spt);
    return true;
}

bool testInsertGladInLEVELTree(){
    SplayTree<GladiatorByScore>* spt= new SplayTree<GladiatorByScore>();
    ASSERT_EQUALS(spt->getSize(),0);
    GladiatorByScore*g1=new GladiatorByScore(1,10);
    spt->insertKey(*g1);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->getRoot(),*g1);
    GladiatorByScore g3(3,30);
    spt->insertKey(g3);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->getRoot(),g3);
    delete (g1);
    GladiatorByScore g2(2,2);
    spt->insertKey(g2);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->getRoot(),g2);
    GladiatorByScore g5(5,25);
    spt->insertKey(g5);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->getRoot(),g5);
    ASSERT_EQUALS(spt->find(g3),ST_SUCCESS);
    ASSERT_EQUALS(spt->find(g2),ST_SUCCESS);
    delete (spt);
    return true;
}


int main(){
    RUN_TEST(testConstructor);
    RUN_TEST(testInsert);
    RUN_TEST(testFind);
    RUN_TEST(testDeleteKey);
    RUN_TEST(testInsertGladInIDTree);
    RUN_TEST(testInsertGladInLEVELTree);
    return 0;
}
