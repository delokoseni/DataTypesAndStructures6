#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

int** getmatrixfromfile(ifstream* file, int countofnodes);	//Функция записи из файла
int countofways(int** arr, int countofnodes, int nodex, int nodey);	//Функция поиска количества путей
void matrixoutput(int **arr, int countofnodes, ostream* stream);	//Функция вывода матрицы
void matrixtofile(int** arr, int countofnodes, ostream* stream, int nodex, int nodey);	//Функция записи результатов в файл

const int N = 6;	//Размерность матрицы

int main()
{
	setlocale(LC_ALL, "russian");
	int **arr, nodex, nodey, i;
	arr = new int*[N];		//Выделение памяти под матрицу
	for (i = 0; i < N; i++)
		*(arr + i) = new int[N];
	ifstream inputfile("input.dat");
	arr = getmatrixfromfile(&inputfile, N);		//Получение значений в матрицу из файла
	inputfile.close();
	cout << "Полученная матрица смежности:" << endl;
	matrixoutput(arr, N, &cout);	//Вывод полученной матрицы
	cout << "\nВведите номер первого узла: ";
	cin >> nodex;	//Ввод узла из которого ищем пути
	cout << "Введите номер второго узла: ";
	cin >> nodey;	//Ввод узла, в который ищем пути
	cout << "Количество путей из узла " << nodex << " в узел " << nodey << ": ";
	cout << countofways(arr, N, nodex, nodey);	//Поиск количества путей из nodex в nodey
	ofstream outputfile("output.dat", ios::app); //Файл открыт на дозапись
	matrixtofile(arr, N, &outputfile, nodex, nodey);
	outputfile.close();
	for(i = 0; i < N; i++)	//Очистка памяти из под матрицы
		delete[] *(arr + i);
	delete[] arr;
	return 0;
}

//Функция записи из файла
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

//Функция вывода матрицы
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

//Функция поиска количества путей
int countofways(int **arr, int countofnodes, int nodex, int nodey) {
	int count = 0, i, j;
	i = nodex - 1;
	if (nodex > countofnodes || nodey > countofnodes)
		return -1;
	for (j = 0; j < countofnodes; j++) {
		if (arr[i][j] == 1 && i != j)
			if (j == nodey - 1)
				count++;
			else
				count += countofways(arr, countofnodes, j+1, nodey);
	}
	return count;
}

//Функция записи результатов в файл
void matrixtofile(int** arr, int countofnodes, ostream* stream, int nodex, int nodey) {
	matrixoutput(arr, countofnodes, stream);
	*stream << "\nКоличество путей из узла " << nodex << " в узел " << nodey << ": ";
	*stream << countofways(arr, N, nodex, nodey);	//Поиск количества путей из nodex в nodey
	*stream << "\n\n";
}