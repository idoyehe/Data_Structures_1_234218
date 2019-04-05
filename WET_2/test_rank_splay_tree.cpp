#include "rankSplayTree.h"
#include "test_tools.h"

using namespace splayTree;


bool testConstructor(){
    RankSplayTree* spt=new RankSplayTree();
    ASSERT_EQUALS(spt->getSize(),0);
    delete (spt);
    return true;
}

bool testInsert(){
    RankSplayTree* spt=new RankSplayTree();
    ASSERT_EQUALS(spt->getSize(),0);
    GladiatorByScore g1(1,10);
    GladiatorByScore g2(2,20);
    GladiatorByScore g3(3,30);
    GladiatorByScore g4(4,40);
    GladiatorByScore g5(5,10);
    ASSERT_EQUALS(spt->insertKey(g1),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->insertKey(g5),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(g1),ST_FAILURE);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(g4),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->insertKey(g3),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->insertKey(g2),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),5);
    delete spt;
    return true;
}

bool testFindKPivoT(){
    RankSplayTree* spt=new RankSplayTree();
    ASSERT_EQUALS(spt->getSize(),0);
    GladiatorByScore g1(1,10);
    GladiatorByScore g2(2,20);
    GladiatorByScore g3(3,30);
    GladiatorByScore g4(4,40);
    GladiatorByScore g5(5,10);
    ASSERT_EQUALS(spt->insertKey(g1),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->insertKey(g5),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(g1),ST_FAILURE);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(g4),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->insertKey(g3),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->insertKey(g2),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),5);

    ASSERT_EQUALS(spt->findKpivot(6), ST_FAILURE);
    ASSERT_EQUALS(spt->findKpivot(2), ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot().getGladiatorID(),3);
    ASSERT_EQUALS(spt->findKpivot(5), ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot().getGladiatorID(),5);
    ASSERT_EQUALS(spt->findKpivot(1), ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot().getGladiatorID(),4);
    ASSERT_EQUALS(spt->findKpivot(4), ST_SUCCESS);
    ASSERT_EQUALS(spt->getRoot().getGladiatorID(),1);
    delete spt;
    return true;
}

bool testDeleteKey(){
    RankSplayTree* spt=new RankSplayTree();
    ASSERT_EQUALS(spt->getSize(),0);
    GladiatorByScore g1(1,10);
    GladiatorByScore g2(2,20);
    GladiatorByScore g3(3,30);
    GladiatorByScore g4(4,40);
    GladiatorByScore g5(5,10);
    ASSERT_EQUALS(spt->insertKey(g1),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),1);
    ASSERT_EQUALS(spt->insertKey(g5),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(g1),ST_FAILURE);
    ASSERT_EQUALS(spt->getSize(),2);
    ASSERT_EQUALS(spt->insertKey(g4),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),3);
    ASSERT_EQUALS(spt->insertKey(g3),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),4);
    ASSERT_EQUALS(spt->insertKey(g2),ST_SUCCESS);
    ASSERT_EQUALS(spt->getSize(),5);
    ASSERT_EQUALS(spt->deleteKey(g1),ST_SUCCESS);
    ASSERT_EQUALS(spt->deleteKey(g1),ST_FAILURE);
    ASSERT_EQUALS(spt->deleteKey(g2),ST_SUCCESS);
    ASSERT_EQUALS(spt->deleteKey(g3),ST_SUCCESS);
    ASSERT_EQUALS(spt->deleteKey(g4),ST_SUCCESS);
    ASSERT_EQUALS(spt->deleteKey(g5),ST_SUCCESS);
    delete spt;
    return true;
}


int main(){
    RUN_TEST(testConstructor);
    RUN_TEST(testInsert);
    RUN_TEST(testFindKPivoT);
    RUN_TEST(testDeleteKey);
    return 0;
}
