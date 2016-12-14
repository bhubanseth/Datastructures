#include<iostream>
#include<math.h>
using namespace std;

int getMid(int start, int end) {
  return start + (end - start)/2;
}

int createSegTree(int arr[], int *segTree, int start, int end, int segIndex) {
  if (start == end) {
    segTree[segIndex] = arr[start];
    return segTree[segIndex];
  }
  int mid = getMid(start, end);
  segTree[segIndex] = createSegTree(arr, segTree, start, mid, segIndex*2 + 1)
    + createSegTree(arr, segTree, mid + 1, end, segIndex*2 + 2);
  return segTree[segIndex];
}

int findSegSize(int n) {
  int x = (int)(ceil(log2(n))); 
  int segSize = 2*(int)pow(2, x) - 1; 
  return segSize;
}

int * createSegTree(int arr[], int n, int segSize) {
  int *segTree = new int[segSize];
  createSegTree(arr, segTree, 0, n-1, 0);
  return segTree;
}


int findSubArraySum(int *segTree,int nodeIndex, int i, int j, int start, int end) {
  if (start >=i && j>=end) {
    return segTree[nodeIndex];
  }
  if (end<i || start > j) {
    return 0;
  }
  return findSubArraySum(segTree, nodeIndex*2 + 1, i, j, start, getMid(start, end))
    + findSubArraySum(segTree, nodeIndex * 2 + 2, i, j, getMid(start, end) + 1, end);
}

void updateValue(int array[], int *segTree, int nodeIndex, int index, int newValue, int start, int end) {
  if (start > end) {
    return;
  }
  if (start <=index && index <=end) {
    cout<<"updating"<< nodeIndex<<" with index"<<start<<","<<end<<endl;
    segTree[nodeIndex] += (newValue - array[index]);
    if (start != end) {
      updateValue(array, segTree, nodeIndex * 2 + 1, index, newValue, start, getMid(start, end));
      updateValue(array, segTree, nodeIndex * 2 + 2, index, newValue, getMid(start, end) + 1, end);
    }
  }
}

int main() {
  int array[] = {1,3,5,7,9,11};
  int n = (sizeof(array))/(sizeof(array[0]));
  int segSize = findSegSize(n);
  int * segTree = createSegTree(array, n, segSize);
  for (int i =0; i < segSize; i ++) {
    cout<<"segTree["<<i<<"] = "<< segTree[i]<<endl;
  }
  cout<<findSubArraySum(segTree, 0, 2, 5, 0, n-1)<<endl;
  updateValue(array, segTree, 0, 3, 17, 0, n-1);
  cout<<findSubArraySum(segTree, 0, 2, 5, 0, n-1)<<endl;
  cout<<findSubArraySum(segTree, 0, 2, 4, 0, n-1)<<endl;
  return 0;
}

