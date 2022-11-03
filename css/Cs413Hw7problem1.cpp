#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iomanip>
using namespace std;

unsigned long long int counter; // to count item comparisons

void print(int nums[], int length) {
    cout << "[ ";
    for (int i = 0; i < length; i++)
        cout << nums[i] << " ";
    cout << "]" << endl;
}

 

// helper for mergeSort1
int* merge(int  p1[], int length1, int  p2[], int length2, int  buff[]) {
    //  cout << "In merge, length1, length2 = " << length1 << ", " << length2 << endl;
    //  cout << p1[0] << " " << p2[0] << endl;
    for (int i = 0, j = 0, k = 0; k < length1 + length2;) {
        if (i < length1 && (j >= length2 || p1[i] <  p2[j] )){
            buff[k++] = p1[i++];
            counter++;
        }
        if (j < length2 && (i >= length1 || p2[j] <= p1[i] )){
            buff[k++] = p2[j++];
        //      cout << "k = " << k << endl;
        //      cin.get();
        counter++;
        
        }
    return buff;
}

// helper for sort6 (mergesort)
void mergeSort1(int* first, int* last, int buff[]) {
    if (first >= last) return;
    int length = last - first + 1, len1 = length / 2;
    //  cout << "In mergesort1 length, len1 = " << length << "," << len1 << endl;
    mergeSort1(first, first + len1 - 1, buff);
    mergeSort1(first + len1, last, buff);
    merge(first, len1, first + len1, length - len1, buff);

    while (first <= last) {
        //   cout << ".";
        *first++ = *buff++;  // copy back to original array
    }
}


// mergesort
void mergesort(int a[], int length) {
    //  cout << "In mergesort" << endl;
    int* buff = new int[length];  // O(n) extra memory 
    mergeSort1(a, a + length - 1, buff);
    delete[] buff;
}


int partition(int a[], int low, int high)
{
    int x = a[low];
    bool highTurn = true;

    while (low < high)
    {
        if (highTurn) {
           
            if (a[high] < x) {
                a[low++] = a[high];
                highTurn = !highTurn;
            }
            else    high--;
        }
        else {
            
            if (a[low] > x) {
                a[high--] = a[low];
                highTurn = !highTurn;
            }
            else    low++;
        }
        counter++;
    }
    a[low] = x;
    return low;
    
    
}

void quickSort1(int nums[], int start, int end) {
    if (start >= end) return;

    int mid = partition(nums, start, end);

    quickSort1(nums, start, mid - 1);
    quickSort1(nums, mid + 1, end);
}

// quicksort
void quicksort(int  nums[], int len) {
    quickSort1(nums, 0, len - 1);
}

void copy(int dest[], int source[], int length) {
    for (int i = 0; i < length; i++)
        dest[i] = source[i];
}
unsigned int random10(int powOf10) {
    if (powOf10 > 9) {
        cout << "Limit is 10^9" << endl;
        powOf10 = 9;
    }
    unsigned int num = 0;
    while (powOf10-- > 0)
        num = num * 10 + rand() % 10;
    return num;
}

void fillArray(int a[], int length) {
    for (int i = 0; i < length; i++) {
        a[i] = random10(9);
    }
}

 

int main() {
    srand(time(0));
    const int STARTING_SIZE = 2, MAX_SIZE = 135000000;
    static int toSort[MAX_SIZE], original[MAX_SIZE];
    fillArray(original, MAX_SIZE);
    cout << "Quicksort" << endl;
    cout << setw(14) << "n" << setw(14) << "comps" << setw(14) << "nlogn" << setw(14) << "comps/nlogn" << endl;
    for (int n = STARTING_SIZE; n <= MAX_SIZE; n *= 2) {
        counter = 0;
        copy(toSort, original, n);
        quicksort(toSort, n);
        double nlogn = n * (log(n) / log(2)); // n * (log base 2 of n)
        cout << setw(14) << n << setw(14) << counter << setw(14) << (unsigned long long int)(nlogn) << setw(14) << (counter / nlogn) << endl;
    }
    cout << endl << "Mergesort" << endl;
    for (int n = STARTING_SIZE; n <= MAX_SIZE; n *= 2) {
        counter = 0;
        copy(toSort, original, n);
        mergesort(toSort, n);
        double nlogn = n * (log(n) / log(2)); // n * (log base 2 of n)
        cout << setw(14) << n << setw(14) << counter << setw(14) << (unsigned long long int)(nlogn) << setw(14) << (counter / nlogn) << endl;
    }

    return 0;
}