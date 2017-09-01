#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <bitset>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;


int n, k;
vector<int> nums(1000000,0), tmp(1000000,0), totalNums;
ofstream outputFile;

void bubble(){
    for (int i = 0; i < n-1; ++i) {
        bool swapped = false;
        for (int j = 0 ; j < n-1-i; ++j) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void cocktail()
{
    bool swapped = true;
    int start = 0;
    int end = n-1;
    while (swapped)
    {
        swapped = false;
        for (int i = start; i < end; ++i)
        {
            if (nums[i] > nums[i + 1])
            {
                swap(nums[i], nums[i+1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i)
        {
            if (nums[i] > nums[i + 1])
            {
                swap(nums[i], nums[i+1]);
                swapped = true;
            }
        }
        ++start;
    }
}

void insertion(){
    for (int i = 1; i < n; ++i) {
        int j = i-1;
        int temp = nums[i];
        while(j >=0 && nums[j] > temp){
            nums[j+1] = nums[j];
            --j;
        }
        nums[j+1] = temp;
    }
}

void count(){
    int size = n;
    k = 1000000;
    vector<int> work(k+1,0);
    vector<int> output(size+1,0);
    for (int i = 0; i <= k; ++i) work[nums[i]] += 1;
    for (int i = 1; i <= k; ++i) work[i] += work[i-1];
    for (int i = size-1; i >= 0 ; --i) {
        --work[nums[i]];
        output[work[nums[i]]] = nums[i];
        --work[nums[i]];
    }
    copy(output.begin(), output.begin()+n, nums.begin());
}

int getMax()
{
    int mx = nums[0];
    for (int i = 1; i < n; i++)
        if (nums[i] > mx)
            mx = nums[i];
    return mx;
}

void countSortForRadix(int exp)
{
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[ (nums[i]/exp)%10 ]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (nums[i]/exp)%10 ] - 1] = nums[i];
        count[ (nums[i]/exp)%10 ]--;
    }
    for (i = 0; i < n; i++)
        nums[i] = output[i];
}

void radix()
{
    int m = getMax();
    k = 10;
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSortForRadix(exp);
}

void selection()
{
    for (int i=0;i<n-1;i++)
    {
        int minPos = i;
        for (int j=i+1;j<n;j++)
        {
            if (nums[j] < nums[minPos])
            {
                minPos = j;
            }
        }
        swap(nums[i], nums[minPos]);
    }
}

void shell()
{
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            int temp = nums[i];
            int j;
            for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) nums[j] = nums[j - gap];
            nums[j] = temp;
        }
    }
}

struct Node
{
    int key;
    struct Node *left, *right;
};
 
Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void storeSorted(Node *root, int &i)
{
    if (root != NULL)
    {
        storeSorted(root->left, i);
        nums[i++] = root->key;
        storeSorted(root->right, i);
    }
}

Node* insert(Node* node, int key)
{
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

void tree()
{
    struct Node *root = NULL;
    root = insert(root, nums[0]);
    for (int i=1; i<n; i++)
        insert(root, nums[i]);
    int i = 0;
    storeSorted(root, i);
}

void heapify(int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && nums[l] > nums[largest])
        largest = l;

    if (r < n && nums[r] > nums[largest])
        largest = r;

    if (largest != i)
    {
        swap(nums[i], nums[largest]);
        heapify(largest);
    }
}

void heap()
{
    for (int i = n / 2 - 1; i >= 0; i--) heapify(i);

    for (int i=n-1; i>=0; i--)
    {
        swap(nums[0], nums[i]);
        n=i;
        heapify(0);
    }
}

void merge(int low, int mid, int high)
{
    int h,i,j,k;
    h = low;
    i = low;
    j = mid+1;
    while (h <= mid && j <= high)
    {
        if (nums[h] <= nums[j])
        {
            tmp[i] = nums[h];
            h++;
        }
        else
        {
            tmp[i] = nums[j];
            j++;
        }
        i++;
    }
    if (h > mid)
    {
        for(k=j;k<=high;k++)
        {
            tmp[i] = nums[k];
            i++;
        }
    }
    else
    {
        for(k=h;k<=mid;k++)
        {
            tmp[i] = nums[k];
            i++;
        }
    }
    for(k=low;k<=high;k++) nums[k] = tmp[k];
}

void mergeSort(int low, int high)
{
    if (low == high) return;
    int MID = (low+high)/2;
    mergeSort(low, MID);
    mergeSort(MID+1, high);
    merge(low, MID, high);
}

int partition (int low, int high)
{
    int pivot = nums[high];
    int i = (low - 1);  

    for (int j = low; j <= high- 1; j++)
    {
        if (nums[j] <= pivot)
        {
            i++; 
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[high]);
    return (i + 1);
}

void quick(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        quick(low, pi - 1);
        quick(pi + 1, high);
    }
}

void bucket() {
    int SIZE = 1000000;
    int i, j, k, buckets[SIZE];

    for(i = 0; i < SIZE; ++i)
        buckets[i] = 0;

    for(i = 0; i < n; ++i)
        ++buckets[nums[i]];

    for(i = 0, j = 0; j < SIZE; ++j)
        for(k = buckets[j]; k > 0; --k)
            nums[i++] = j;
}

void fillSortMeasure(void (*sortF)(), int max){
    copy(totalNums.begin(), totalNums.begin()+max, nums.begin());
    n = max;
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    (*sortF)();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    outputFile << "   n = " << max << ", duration = " << duration << " μs\n";
}

void measureAllCases(void (*sortF)(), string fName){
    outputFile.open(fName+".txt");
    outputFile << fName+":\n";
    for (int i = 1; i <= 6 ; ++i) {
        fillSortMeasure(sortF, pow(10, i));
    }
//    for(int i=0; i<1000000; i++) outputFile << nums[i] << "\n";
    outputFile.close();
}

int main(){
    std::ios::sync_with_stdio(0);
    ifstream file("totalNums.txt");

    int num;
    while (file >> num) totalNums.push_back(num);
    // Example:
    measureAllCases(bubble, "bubble");
}





//Generate random vector
//
//for (int i = 1000000; i >= 0 ; --i) totalNums.push_back(i);
//random_shuffle(totalNums.begin(), totalNums.end());
//ofstream myfile;
//myfile.open ("totalNums.txt");
//for (int i = 0; i < totalNums.size() ; ++i) myfile << totalNums[i] << " ";
//myfile.close();