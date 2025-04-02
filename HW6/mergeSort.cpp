#include<iostream>

using namespace std;

int * merge(int * left, int * right, int arrSize)
{
    int * leftPointer = left;
    int * rightPointer = right;
    int currentIndex = 0;
    int * outArr = new int[arrSize * 2];
    while(currentIndex < arrSize * 2)
    {
        // cout << "left " << *leftPointer << endl << "right " << *rightPointer << endl;
        if(leftPointer == left + arrSize && rightPointer != right + arrSize)
        {
            outArr[currentIndex] = *rightPointer;
            rightPointer++;
        }else if(rightPointer == right + arrSize && leftPointer != left + arrSize)
        {
            outArr[currentIndex] = *leftPointer;
            leftPointer++;
        }else if(*rightPointer >= *leftPointer)
        {
            outArr[currentIndex] = *rightPointer;
            rightPointer++;
        }else if(*leftPointer > *rightPointer)
        {
            outArr[currentIndex] = *leftPointer;
            leftPointer++;
        }
        currentIndex += 1;
    }
    return outArr;
}

int* mergeSort(int* sortArr, int arrSize)
{
    // cout << arrSize << endl;
    if(arrSize == 1)
    {
        return sortArr;
    }
    int * left = mergeSort(sortArr, arrSize / 2);
    int * right = mergeSort(&sortArr[(arrSize / 2)], arrSize / 2);
    return merge(left, right, arrSize / 2);  
}


int main()
{
    int sortArr[8] = {999,15,16,3,0,8,90,69};
    int * sortedArr = mergeSort(sortArr, 8);
    for(int i = 0; i < 8; i++)
    {
        cout << sortedArr[i] << endl;
    }
    return 0;
}