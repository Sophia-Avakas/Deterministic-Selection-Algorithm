#include <iostream>
#include <vector>
#include <algorithm>
#include "timer.c"
using namespace std;

static const int GROUP_SIZE = 7;

static const double SMALL = 1000;
static const double MIDDLE = 100000;
static const double LARGE = 10000000;

double dshrandom(long input) {
	/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
	/*	Random Number Generator					*/
	/*		first called with seed				*/
	/*		thereafter called with 0			*/
	/*	Based on code appearing in				*/
	/*	"Random number generators: good ones are hard to find"	*/
	/*		by Stephen Park and Keith Miller		*/
	/*		CACM 31 (Oct 1988) 1192-1201.			*/
	/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
	static long seed = 3125;
	static long a = 16807;
	static long m = 2147483647;
	static long q = 127773;      /* m div a */
	static long r = 2836;        /* m mod a */
	long lo, hi, test;

	if (input>0) seed = input;
	hi = seed / q;
	lo = seed - (hi*q);
	test = a*lo - r*hi;
	if (test>0) seed = test;
	else        seed = test + m;
	/* seed equally in range 0...2^31 -1  */
	return(((double)seed) / (double)m);
}

int partition(vector<double>& vec, int start, int end, double pivot) {
	int i = start, j = end;
	while (i < j) {
		while (vec[i] < pivot && i <= j) i++;
		while (vec[j] > pivot && j >= i) j--;
		if (i >= j) break;
		else if (vec[i] == vec[j]) { i++; continue; }
		swap(vec[i], vec[j]);
	}
	return j;
}

double quickSelection(vector<double>& vec, int start, int end, int k)
{
	if (start == end) return vec[start];
	int j = partition(vec, start, end, vec[end]);
	int length = j - start + 1;
	if (length == k) return vec[j];
	else if (k < length) return quickSelection(vec, start, j - 1, k);
	else  return quickSelection(vec, j + 1, end, k - length);
}

/*Find the medians array. */
vector<double> findMedians(vector<double>& vec, int start, int end) {
	vector<double> medians;
	for (int i = start; i <= end; i += GROUP_SIZE) {
		int group_end = min(i + GROUP_SIZE - 1, end);
		//notice here when sorting the element at group_end + 1 is not included
		sort(vec.begin() + i, vec.begin() + group_end + 1);
		int middle_index = i + (group_end - i) / 2;
		medians.push_back(vec[middle_index]);
	}
	return medians;
}

/* Returns the k-th element of this array. */
double deterministicSelect(vector<double>& vec, int start, int end, int k) {

	if (end - start < 50) {
		//notice here when sorting the element at end + 1 is not included
		sort(vec.begin() + start, vec.begin() + end + 1);
		return vec[start + k-1]; //should be k-1, as k begins with 1
	}

	vector<double> medians = findMedians(vec, start, end);

	double median = deterministicSelect(medians, 0, medians.size() - 1, (medians.size()+1) / 2); //here medians.size() should be added by 1

	int index = partition(vec, start, end, median);
	int length = index - start + 1;

	if (k < length) {
		return deterministicSelect(vec, start, index - 1, k);
	}
	else if (k > length) {
		return deterministicSelect(vec, index + 1, end, k - length);
	}
	else
		return vec[start + k-1]; //should be k-1, as k begins with 1
}


int main() {
	vector<double> vecSmall;
	vector<double> vecMiddle;
	vector<double> vecLarge;

	dshrandom(1212);
	for (int i = 0; i < SMALL; i++) {
		double temp = dshrandom(0);
		vecSmall.push_back(temp);

	}
	for (int i = 0; i < MIDDLE; i++) {
		double temp = dshrandom(0);
		vecMiddle.push_back(temp);
	}
	for (int i = 0; i < LARGE; i++) {
		double temp = dshrandom(0);
		vecLarge.push_back(temp);
	}

	cout << "-------------Array Size 100-----------------" << endl;
	start_timer();
	cout << "Median in deterministicSelect is " << deterministicSelect(vecSmall, 0, SMALL - 1, (SMALL + 1) / 2) << endl;
	cout << "Time elapse in deterministicSelect is " << elapsed_time() << endl;
	start_timer();
	cout << "Median in quickSelection is " << quickSelection(vecSmall, 0, SMALL - 1, (SMALL + 1) / 2) << endl;
	cout << "Time elapse in quickSelection is " << elapsed_time() << endl;

	cout << "-------------Array Size 10000-----------------" << endl;
	start_timer();
	cout << "Median in deterministicSelect is " << deterministicSelect(vecMiddle, 0, MIDDLE - 1, (MIDDLE + 1) / 2) << endl;
	cout << "Time elapse in deterministicSelect is " << elapsed_time() << endl;
	start_timer();
	cout << "Median in quickSelection is " << quickSelection(vecMiddle, 0, MIDDLE - 1, (MIDDLE + 1) / 2) << endl;
	cout << "Time elapse in quickSelection is " << elapsed_time() << endl;

	cout << "-------------Array Size 1000000-----------------" << endl;
	start_timer();
	cout << "Median in deterministicSelect is " << deterministicSelect(vecLarge, 0, LARGE - 1, (LARGE + 1) / 2) << endl;
	cout << "Time elapse in deterministicSelect is " << elapsed_time() << endl;
	start_timer();
	cout << "Median in quickSelection is " << quickSelection(vecLarge, 0, LARGE - 1, (LARGE + 1) / 2) << endl;
	cout << "Time elapse in quickSelection is " << elapsed_time() << endl;

	system("pause");
	return 0;
}




