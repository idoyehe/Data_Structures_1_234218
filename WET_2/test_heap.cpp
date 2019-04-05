#include "heap.h"
#include "test_tools.h"

using namespace heap;


bool testConstructor() {
    Heap<int> heap;
    ASSERT_EQUALS(heap.getSize(),0);
    return true;
}

bool testMakeHeap(){
    Heap<int> heap;
    ASSERT_EQUALS(heap.getSize(),0);
    int arr[20];
    for(int i=0;i<20;++i){
        arr[i]=20-i;
    }
    void* addressing[20];
    ASSERT_EQUALS(heap.makeHeap(arr,addressing,20),HP_SUCCESS);
    return true;
}

bool testInsertData(){
    Heap<int> heap;
    ASSERT_EQUALS(heap.getSize(),0);
    int arr[5];
    for(int i=0;i<5;++i){
        arr[i]=10-i*2;
    }
    void* addressing[5];
    ASSERT_EQUALS(heap.makeHeap(arr,addressing,5),HP_SUCCESS);
    void * newDataAddress=NULL;
    ASSERT_EQUALS(heap.insert(5,&newDataAddress),HP_SUCCESS);
    ASSERT_EQUALS(heap.insert(100,&newDataAddress),HP_SUCCESS);
    ASSERT_EQUALS(1,1);
    return true;
}

bool testDeckP() {
    Heap<int> heap;
    ASSERT_EQUALS(heap.getSize(),0);
    int arr[5];
    for(int i=0;i<5;++i){
        arr[i]=10-i*2;
    }
    void* addressing[5];
    ASSERT_EQUALS(heap.makeHeap(arr,addressing,5),HP_SUCCESS);
    ASSERT_EQUALS(heap.decK(addressing[3],20),HP_FAILURE);
    ASSERT_EQUALS(heap.decK(addressing[3],-1),HP_SUCCESS);
    ASSERT_EQUALS(1,1);
    return true;
}

bool testDeleteMin() {
    Heap<int> heap;
    ASSERT_EQUALS(heap.getSize(),0);
    int arr[10];
    for(int i=0;i<10;++i){
        arr[i]=20-i*2;
    }
    void* addressing[10];
    ASSERT_EQUALS(heap.makeHeap(arr,addressing,10),HP_SUCCESS);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),4);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),6);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),8);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),10);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),12);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),14);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),16);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),18);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getMin(),20);
    ASSERT_EQUALS(heap.deleteMin(),HP_SUCCESS);
    ASSERT_EQUALS(heap.getSize(),0);
    ASSERT_EQUALS(heap.deleteMin(),HP_FAILURE);
    ASSERT_EQUALS(heap.getSize(),0);
    void* newAddressing=NULL;
    ASSERT_EQUALS(heap.insert(20,&newAddressing),HP_SUCCESS);
    ASSERT_EQUALS(heap.insert(30,&newAddressing),HP_SUCCESS);
    ASSERT_EQUALS(heap.insert(40,&newAddressing),HP_SUCCESS);
    ASSERT_EQUALS(1,1);
    return true;
}



int main(){
    RUN_TEST(testConstructor);
    RUN_TEST(testMakeHeap);
    RUN_TEST(testInsertData);
    RUN_TEST(testDeckP);
    RUN_TEST(testDeleteMin);
    return 0;
}
