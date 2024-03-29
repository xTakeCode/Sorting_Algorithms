#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <cstring>  // memcpy
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <stdio.h>

using namespace std;

class Table {
	int size;
	int* tab;
	vector<int>v;

public:
	Table(int size, const int* t)
		: size(size), tab((int*)memcpy(new int[size], t, size*sizeof(int))) {
	}

	Table(const Table& t) : size(t.size),
		tab((int*)memcpy(new int[size], t.tab, size*sizeof(int))) {
	}

	~Table() {
		delete[]tab;
	}

	Table& operator++();
	Table operator++(int);
	int* getTab();
	AnsiString Table::TableToString();
	void ArrayToVector();
	inline void Sort();
	inline void BubbleSort();
	inline void InsertionSort();
	inline void MergeSort();
	inline void CountingSort();
	inline void BucketSort();
	inline void RadixSort();
	inline void SelectionSort();
	inline void ShellSort();
	inline void QuickSort();
	inline void HeapSort();
	inline void ExchangeSort();

private:
	void merge_sort(int arr1[], int ll, int ul);
	void merge(int arr1[], int ll1, int ul1, int ll2, int ul2);
	void countSort(int arr[], int n, int exp);
	int getMax(int arr[], int n);
	int pivot(int a[], int first, int last);
	void swap(int& a, int& b);
	void swapNoTemp(int& a, int& b);
	void quickSort(int a[], int first, int last);
	void siftDown(int *a, int k, int N);
	void heapsort(int a[], int N);
	void sort(int* arr, int len);
	void findMinMax(int* arr, int len, int& mi, int& mx);
};

Table& Table:: operator++() {
	for (int i = 0; i < size; ++i)
		++tab[i];
	return *this;
}

Table Table:: operator++(int) {
	Table t(*this);
	++*this;
	return t;
}

int* Table::getTab() {
	return tab;
}

inline AnsiString Table::TableToString() {
	AnsiString sorted = "";
	for (int i = 0; i < size; i++) {
		sorted += IntToStr(tab[i]);
		if (i != size - 1) {
			sorted += ",";
		}
	}
	return sorted;
}

void Table::ArrayToVector() {
	vector<int>v(tab, tab +sizeof tab / sizeof tab[0]);
}

inline void Table::Sort() {
	std::sort(tab, tab + size);
}

inline void Table::BubbleSort() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (tab[j] > tab[j + 1])
				swap(tab[j], tab[j + 1]);
		}
	}
}

inline void Table::InsertionSort() {
	int temp, j;

	for (int i = 1; i < size; i++) {
		temp = tab[i];

		for (j = i - 1; j >= 0 && tab[j] > temp; j--)
			tab[j + 1] = tab[j];

		tab[j + 1] = temp;
	}
}

inline void Table::SelectionSort() {
	int pos_min, temp;

	for (int i = 0; i < size - 1; i++) {
		pos_min = i; // set pos_min to the current index of array

		for (int j = i + 1; j < size; j++) {

			if (tab[j] < tab[pos_min])
				pos_min = j;
			// pos_min will keep track of the index that min is in, this is needed when a swap happens
		}

		// if pos_min no longer equals i than a smaller value must have been found, so a swap must occur
		if (pos_min != i) {
			temp = tab[i];
			tab[i] = tab[pos_min];
			tab[pos_min] = temp;
		}
	}
}

inline void Table::ShellSort() {
	int gap, i, j, temp;

	for (gap = size / 2; gap > 0; gap /= 2)

		for (i = gap; i < size; i++)

			for (j = i - gap; j >= 0 && tab[j] > tab[j + gap]; j -= gap) {

				temp = tab[j];

				tab[j] = tab[j + gap];

				tab[j + gap] = temp;

			}
}

void Table::merge(int arr1[], int ll1, int ul1, int ll2, int ul2) {
	int i = 0, k, ll = ll1;
	int arr3[100];
	while (ll1 <= ul1 && ll2 <= ul2) {
		if (arr1[ll1] < arr1[ll2])
			arr3[i++] = arr1[ll1++];
		else
			arr3[i++] = arr1[ll2++];
	}
	while (ll1 <= ul1)
		arr3[i++] = arr1[ll1++];
	while (ll2 <= ul2)
		arr3[i++] = arr1[ll2++];
	for (k = 0; k < i; k++)
		arr1[ll++] = arr3[k];
}

void Table::merge_sort(int arr1[], int ll, int ul) {
	int mid;
	if (ll < ul) {
		mid = (ul + ll) / 2;
		merge_sort(arr1, ll, mid);
		merge_sort(arr1, mid + 1, ul);
		merge(arr1, ll, mid, mid + 1, ul);
	}
}

inline void Table::MergeSort() {
	merge_sort(tab, 0, size - 1);
}

void Table::findMinMax(int* arr, int len, int& mi, int& mx) {
	mi = INT_MAX;
	mx = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] > mx)
			mx = arr[i];
		if (arr[i] < mi)
			mi = arr[i];
	}
}

void Table::sort(int* arr, int len) {
	int mi, mx, z = 0;
	findMinMax(arr, len, mi, mx);
	int nlen = (mx - mi) + 1;
	int* temp = new int[nlen];
	memset(temp, 0, nlen * sizeof(int));

	for (int i = 0; i < len; i++)
		temp[arr[i] - mi]++;

	for (int i = mi; i <= mx; i++) {
		while (temp[i - mi]) {
			arr[z++] = i;
			temp[i - mi]--;
		}
	}

	delete[]temp;
}

inline void Table::CountingSort() {
	sort(tab, size);
}

int Table::getMax(int arr[], int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

void Table::countSort(int arr[], int n, int exp) {
	int* output = new int[n];
	int i, count[10] = {0};
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = output[i];

	delete[]output;
}

inline void Table::RadixSort() {
	int m = getMax(tab, size);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(tab, size, exp);
}

inline void Table::BucketSort() {

}

inline void Table::QuickSort() {
	quickSort(tab, 0, size - 1);
}

void Table::quickSort(int a[], int first, int last) {
	int pivotElement;

	if (first < last) {
		pivotElement = pivot(a, first, last);
		quickSort(a, first, pivotElement - 1);
		quickSort(a, pivotElement + 1, last);
	}
}

int Table::pivot(int a[], int first, int last) {
	int p = first;
	int pivotElement = a[first];

	for (int i = first + 1; i <= last; i++) {
		/* If you want to sort the list in the other order, change "<=" to ">" */
		if (a[i] <= pivotElement) {
			p++;
			swap(a[i], a[p]);
		}
	}

	swap(a[p], a[first]);

	return p;
}

void Table::swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void Table::swapNoTemp(int& a, int& b) {
	a -= b;
	b += a; // b gets the original value of a
	a = (b - a); // a gets the original value of b
}

void Table::heapsort(int a[], int N) {
	/* heapify */
	for (int k = N / 2; k >= 0; k--) {
		siftDown(a, k, N);
	}

	while (N - 1 > 0) {
		swap(a[N - 1], a[0]);
		/* put the heap back in max-heap order */
		siftDown(a, 0, N - 1);
		N--;
	}
}

void Table::siftDown(int *a, int k, int N) {
	while (k * 2 + 1 < N) {
		/* For zero-based arrays, the children are 2*i+1 and 2*i+2 */
		int child = 2 * k + 1;

		/* get bigger child if there are two children */
		if ((child + 1 < N) && (a[child] < a[child + 1]))
			child++;

		if (a[k] < a[child]) { /* out of max-heap order */
			swap(a[child], a[k]);
			/* repeat to continue sifting down the child now */
			k = child;
		}
		else
			return;
	}
}

inline void Table::HeapSort() {
	heapsort(tab, size);
}

inline void Table::ExchangeSort() {
	int i, j;
	int temp; // holding variable
	int numLength = size;
	for (i = 0; i < (numLength - 1); i++) { // element to be compared
		for (j = (i + 1); j < numLength; j++) { // rest of the elements
			if (tab[i] > tab[j]) { // ascending order
				temp = tab[i]; // swap
				tab[i] = tab[j];
				tab[j] = temp;
			}
		}
	}
}

#endif
