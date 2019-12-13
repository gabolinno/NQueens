#include<stdlib.h>
#include<time.h>
#include<chrono>
#include "Board.h";

void generateAnswer(Board& b) {
	int i = 0;
	while (i <= 3 * b.getN()) {
		i++;

		int newCol = b.getColWithMaxConf();
		if (newCol == -1) {
			break;
		}
		int newRow = b.getRowWithMinConf(newCol);
		int oldRow = b.getRow(newCol);
		b.changeRow(newCol, newRow);
		b.recalculateConflicts(oldRow, newRow, newCol);

		if (!b.hasConflicts()) {
			return;
		}
	}
	if (b.hasConflicts()) {
		int n = b.getN();
		b.resetValues();
		b.initialize();

		generateAnswer(b);
	}
}

int main() {
	srand(time(NULL));
	int n;
	std::cin >> n;
	if (n > 3) {
		auto start_time = std::chrono::high_resolution_clock::now();
		
		Board b(n);
		generateAnswer(b);
		auto current_time = std::chrono::high_resolution_clock::now();

		//b.print();

		std::cout << "Program has been running for " << std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time).count() << " microsec" << std::endl;
	}
	else {
		std::cout << "Invalid input!" << std::endl;
	}

	system("pause");

	return 0;
}
