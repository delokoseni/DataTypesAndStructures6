#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

int* getmatrixfromfile(ifstream* file, int countofnodes);
void matrixoutput(int* arr, int countofnodes, ostream* stream);
int countofways(int *arr, int countofnodes, int nodex, int nodey);

const int N = 6;

int main()
{
	setlocale(LC_ALL, "russian");
	int *arr, nodex, nodey;
	arr = new int[N * N];
	ifstream inputfile("input.dat");
	arr = getmatrixfromfile(&inputfile, N);
	inputfile.close();
	cout << "Полученная матрица смежности:" << endl;
	matrixoutput(arr, N, &cout);
	cout << "\nВведите номер первого узла: ";
	cin >> nodex;
	cout << "Введите номер второго узла: ";
	cin >> nodey;
	ofstream outputfile("output.dat");
	matrixoutput(arr, N, &outputfile);
	outputfile.close();
	return 0;
}

int* getmatrixfromfile(ifstream* file, int countofnodes) {
	if (!file->is_open())
		return NULL;
	int i = 0, *arr;
	arr = new int[countofnodes * countofnodes];
	while (i < countofnodes * countofnodes && !file->eof()) {
		*file >> *(arr+i);
		i++;
	}
	cout << endl;
	return arr;
}

void matrixoutput(int* arr, int countofnodes, ostream* file) {
	int i, j = 0, flag = 0, k = 1;
	*file << " ";
	for (i = 0; i < countofnodes; i++)
		*file << " " << i + 1;
	*file << endl;
	for (i = 0; i < countofnodes * countofnodes; i++) {
		if (!flag) {
			*file << k << " ";
			k++;
			flag = 1;
		}
		*file << *(arr + i) << " ";
		j++;
		if (j == countofnodes) {
			*file << endl;
			j = 0;
			flag = 0;
		}
	}
}

int countofways(int* arr, int countofnodes, int nodex, int nodey) {
	int count = 0, *ways, i = nodex - 1, j;
	ways = new int[countofnodes];
	return count;
}