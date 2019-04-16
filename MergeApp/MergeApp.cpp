#include "pch.h"
#include <iostream>
#include <vector>

///<summary>
///prototypes
///</summary>
std::vector<int> sort(std::vector<int>&, size_t, size_t);
void merge(std::vector<int>&, size_t, size_t, size_t);

int main() {
	std::vector<int> unsortedData{5, 2, 6, 4, 1, 3, 2, 6};
	std::vector<int> sortedData = sort(unsortedData, 0, unsortedData.size() - 1);
	for (const auto &a : unsortedData) std::cout << a << ", "; std::cout << std::endl;
	for (const auto &b : sortedData) std::cout << b << ", ";
	return EXIT_SUCCESS;
}

std::vector<int> sort(std::vector<int> &data, size_t lowerBound, size_t upperBound) {
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
	return data;
}

void merge(std::vector<int> &data, size_t lowerBound, size_t halfdBound, size_t upperBound) {
	size_t lSize = (halfdBound - lowerBound) + 1;
	size_t rSize = (upperBound - halfdBound);
	int *lBuffer = new int[lSize];
	int *rBuffer = new int[rSize];
	
	std::copy(data.begin() + lowerBound, data.begin() + (halfdBound + 1), lBuffer);
	std::copy(data.begin() + (halfdBound + 1), data.begin() + (upperBound + 1), rBuffer);
	
	size_t i, j, k;
	for (i = 0, j = 0, k = 0; i < lSize && j < rSize; k++) {
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

	delete[] lBuffer;
	delete[] rBuffer;
}
