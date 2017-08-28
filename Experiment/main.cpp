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
using namespace std;
using namespace std::chrono;


int n;
vector<int> nums;

void bubbleSort() {
    for (int i = n; i > 0; --i) {
        for (int j = 0 ; j < i; ++j) {
            if (nums[j] > nums[j + 1]) swap(nums[j], nums[j + 1]);
        }
    }
}

void cocktailSort()
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

void fillSortMeasure(void (*sortF)(), int max){
    nums.clear();
    n = max;
    for (int i = n; i >= 0 ; --i) nums.push_back(i);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    (*sortF)();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
//    for(auto num: nums) cout << num << "\n";
//    cout << "\n";
    cout << "n = " << max << ", duration = " << duration << " ms\n";
}

void measureAllCases(void (*sortF)()){
    for (int i = 1; i <= 3 ; ++i) {
        fillSortMeasure(sortF, 10*i);
    }
}

int main(){
    std::ios::sync_with_stdio(0);
    measureAllCases(cocktailSort);
}