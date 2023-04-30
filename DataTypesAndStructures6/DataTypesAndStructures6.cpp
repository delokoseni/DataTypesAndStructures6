#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

int** getmatrixfromfile(ifstream* file, int countofnodes);
void matrixoutput(int **arr, int countofnodes, ostream* stream);
int countofways(int **arr, int countofnodes, int nodex, int nodey);

const int N = 6;

int main()
{
	setlocale(LC_ALL, "russian");
	int **arr, nodex, nodey, i;
	arr = new int*[N];
	for (i = 0; i < N; i++)
		*(arr + i) = new int[N];
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
	cout << "Количество путей из узла " << nodex << " в узел " << nodey << ": ";
	cout << countofways(arr, N, nodex, nodey);
	outputfile.close();
	for(i = 0; i < N; i++)
		delete[] *(arr + i);
	delete[] arr;
	return 0;
}

int** getmatrixfromfile(ifstream* file, int countofnodes) {
	if (!file->is_open())
		return NULL;
	int i, j, **arr;
	arr = new int*[countofnodes];
	for(i = 0; i < countofnodes; i++)
		*(arr + i) = new int[countofnodes];
	for (i = 0; i < countofnodes && !file->eof(); i++)
		for (j = 0; j < countofnodes && !file->eof(); j++)
			*file >> arr[i][j];
	return arr;
}

void matrixoutput(int** arr, int countofnodes, ostream* file) {
	int i, j;
	*file << " ";
	for (i = 0; i < countofnodes; i++)
		*file << " " << i + 1;
	*file << endl;
	for (i = 0; i < countofnodes; i++) {
		*file << i + 1 << " ";
		for (j = 0; j < countofnodes; j++) {
			*file << arr[i][j] << " ";
		}
		*file << endl;
	}
}

int countofways(int **arr, int countofnodes, int nodex, int nodey) {
	int count = 0, *ways, i, j;
	ways = new int[countofnodes];
	i = nodex - 1;
	for (j = 0; j < countofnodes; j++) {
		if (arr[i][j] == 1)
			if (j == nodey - 1)
				count++;
			else
				count += countofways(arr, countofnodes, j+1, nodey);
	}
	return count;
}