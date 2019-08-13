#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

std::vector<int> sortArray(const std::vector<int>&, size_t, size_t);
void sort(std::vector<int>&, size_t, size_t);
void merge(std::vector<int>&, size_t, size_t, size_t);

int main() {
	std::vector<int> unsortedData{9, 2, 6, 4, 1, 3, 2, 0};
	std::vector<int> sortedData = sortArray(unsortedData, 0, unsortedData.size() - 1);
	for (const auto &a : unsortedData)	std::cout << a << ", ";	std::cout << std::endl;
	for (const auto &b : sortedData)	std::cout << b << ", ";	std::cout << std::endl;
	return EXIT_SUCCESS;
}

std::vector<int> sortArray(const std::vector<int> &data, size_t lowerBound, size_t upperBound) {
	if (!data.data()) {
		return {};
	}
	else {
		std::vector<int> copyData(data);
		sort(copyData, lowerBound, upperBound);
		return copyData;
	}
}

// Первичная декомпозиция рекурсивным методом блока данных до размера 2,
// последующая сортировка смежных элементов каждой из отсортированных частей [lowerBound, halfBound], [halfBound + 1, upperBound]
// с передачей управления функции merge для окончательной сортировки на каждом этапе декомпозиции входного блока данных.
void sort(std::vector<int>& data, size_t lowerBound, size_t upperBound) {
	if (lowerBound < upperBound - 1) {
		size_t halfBound = (size_t)std::trunc((lowerBound + upperBound) / 2);
		sort(data, lowerBound, halfBound);
		sort(data, halfBound + 1, upperBound);
		merge(data, lowerBound, halfBound, upperBound);
	}
	else {
		for (size_t i = lowerBound; i < upperBound; i++) {
			if (data[i] > data[i + 1])
				std::swap(data[i], data[i + 1]);
		}
	}
}

void merge(std::vector<int> &data, size_t lowerBound, size_t halfdBound, size_t upperBound) {
	// Выделение дополнительного объема памяти для выполнения сортировки.
	size_t lSize = (halfdBound - lowerBound) + 1;
	size_t rSize = (upperBound - halfdBound);
	std::vector<int> lBuffer(lSize);
	std::vector<int> rBuffer(rSize);	
	std::copy(data.begin() + lowerBound, data.begin() + (halfdBound + 1), lBuffer.begin());
	std::copy(data.begin() + (halfdBound + 1), data.begin() + (upperBound + 1), rBuffer.begin());
	
	size_t i, j, k;
	for (i = 0, j = 0, k = lowerBound; i < lSize && j < rSize; k++) {
		if (lBuffer[i] < rBuffer[j]) {
			data[k] = lBuffer[i];
			i++;
		}
		else {
			data[k] = rBuffer[j];
			j++;
		}
	}

	while (i < lSize) {
		data[k] = lBuffer[i];
		i++;
		k++;
	}

	while (j < rSize) {
		data[k] = rBuffer[j];
		j++;
		k++;
	}
}
