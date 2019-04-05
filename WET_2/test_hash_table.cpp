#include "hashTable.h"
#include "test_tools.h"
#include "trainingGroup.h"

using namespace hashTable;
using namespace colosseum::trainingGroup;

bool testConstructor() {
    HashTable<TGroup> hashTable(5);
    return true;
}

bool testInsert(){
    HashTable<TGroup> hashTable(4);
    TGroup tg1(1);
    TGroup tg2(2);
    TGroup tg3(3);
    TGroup tg4(4);
    TGroup tg5(5);
    TGroup tg6(6);
    TGroup tg7(7);
    TGroup tg8(8);
    TGroup tg9(18);
    ASSERT_EQUALS(hashTable.insertData(tg1),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg1),HT_FAILURE);
    ASSERT_EQUALS(hashTable.insertData(tg2),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg3),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg4),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg5),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg6),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg7),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg8),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg9),HT_SUCCESS);
    TGroup tg10(20);
    TGroup tg20(21);
    TGroup tg30(22);
    TGroup tg40(23);
    TGroup tg50(24);
    TGroup tg60(25);
    TGroup tg70(26);
    TGroup tg80(27);
    TGroup tg90(46);
    ASSERT_EQUALS(hashTable.insertData(tg10),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg10),HT_FAILURE);
    ASSERT_EQUALS(hashTable.insertData(tg20),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg30),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg40),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg50),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg60),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg70),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg80),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg90),HT_SUCCESS);
    return true;
}

bool testFind(){
    HashTable<TGroup> hashTable(4);
    TGroup tg1(1);
    TGroup tg2(2);
    TGroup tg3(3);
    TGroup tg4(4);
    TGroup tg5(5);
    TGroup tg6(6);
    TGroup tg7(7);
    TGroup tg8(8);
    TGroup tg9(18);
    ASSERT_EQUALS(hashTable.insertData(tg1),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg1),HT_FAILURE);
    ASSERT_EQUALS(hashTable.insertData(tg2),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg3),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg4),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg5),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg6),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg7),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg8),HT_SUCCESS);
    ASSERT_EQUALS(hashTable.insertData(tg9),HT_SUCCESS);
    TGroup* pointer = NULL;
    ASSERT_EQUALS(hashTable.findData(50,&pointer),HT_FAILURE);
    ASSERT_EQUALS(hashTable.findData(1,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),1);
    ASSERT_EQUALS(hashTable.findData(2,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),2);
    ASSERT_EQUALS(hashTable.findData(3,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),3);
    ASSERT_EQUALS(hashTable.findData(4,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),4);
    ASSERT_EQUALS(hashTable.findData(5,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),5);
    ASSERT_EQUALS(hashTable.findData(6,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),6);
    ASSERT_EQUALS(hashTable.findData(7,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),7);
    ASSERT_EQUALS(hashTable.findData(8,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),8);
    ASSERT_EQUALS(hashTable.findData(18,&pointer),HT_SUCCESS);
    ASSERT_EQUALS(pointer->getGroupID(),18);

    return true;
}


int main(){
    RUN_TEST(testConstructor);
    RUN_TEST(testInsert);
    RUN_TEST(testFind);
    return 0;
}
