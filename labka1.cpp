#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <iostream>
#include <string>

using namespace std;


string generate_random_string(int length)
{
	const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	random_device random_device;
	mt19937 generator(random_device());
	uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	string random_string;

	for (int i = 0; i < length; i++)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}

vector<vector<double> > generate_random_matrix(int height, int width) {
	vector<vector<double> > matrix(height);
	for (int i = 0; i < height; i++) {
		matrix[i].resize(width);
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			matrix[i][j] = (double)rand() / 200;
		}
	}
	return matrix;
}

void sort_matrix_lines(vector<vector<double>> &matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		sort(matrix[i].begin(), matrix[i].end());
	}
}

void firstcode() {
	string S = generate_random_string(100);
	cout << "Result1: " << count(S.begin(), S.end(), 'A');
}

void secondcode() {

	int height = 5, width = 5;
	vector<vector<double> > matrix = generate_random_matrix(height, width);
	sort_matrix_lines(matrix);
	cout << "Result2: " << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv); int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	srand(time(0));
	if (rank == 0) {
		firstcode();
	}
	else if (rank == 1) {
		secondcode();
	}
	MPI_Finalize();
	return 0;
}