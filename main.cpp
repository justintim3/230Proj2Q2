#include <iostream>
#include <fstream>
#include <string>
#include <chrono>	//time
//#include "ReplacementSelection.cpp"
#include "heap.h"
#include "Comp.cpp"
#include "heap.h"
#include "qsortop.cpp"
//#pragma once

int THRESHOLD2 = 8;

void genRandFile();
void genRandFile2(int lines);
template<typename E> void fillArrAsc(E a[], int size);
template<typename E> void shuffleArr(E a[], int size);
std::streamoff readData(std::string *inBuff, std::streamoff start, int size);
template<typename E> void printArr(E a[], int size);
template<typename E> void printHeap(heap<E, Comp<E>>* heap, int size);
template<typename E> void repSel(heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize);
void clearData();
void writeData(std::string *outBuff, int size);
template<typename E> void multiMrg(int buffSize);

int main()
{
	srand((unsigned)time(0));
	int bufferSize = 7, heapSize = 7;
	std::streamoff start;

	std::string *heapArr = new std::string[heapSize];
	clearData();	//clear output file
	genRandFile2(heapSize + (bufferSize * 1));	//generate input file
	start = readData(heapArr, 0, heapSize);	//read data into heap array
	heap<std::string, Comp<std::string>>* minHeap = new heap<std::string, Comp<std::string>>(heapArr, heapSize, heapSize);
		std::cout << "heap___________________________________" << std::endl;
		printArr(heapArr, heapSize);
	repSel<std::string>(minHeap, start, bufferSize);
	qsortO(heapArr, heapSize);
		std::cout << "heap___________________________________" << std::endl;
		printArr(heapArr, heapSize);
	writeData(heapArr, heapSize);
	//multiMrg<std::string>(heapSize + (bufferSize * 2));

	std::string wait;
	std::cin >> wait;	//Pause console after program finishes
	return 0;
}

void genRandFile()
{
	std::ofstream ofs;
	ofs.open("Random Data.txt");

	int randLines = 85;//(rand() % 100) + 60;
	int randLength, maxLength = 20;
	char randChar;
	for (int i = 0; i < randLines; i++)
	{
		randLength = (rand() % maxLength) + 1;
		for (int j = 0; j < randLength; j++)
		{
			randChar = (rand() % 26) + 'A';
			ofs << randChar;
		}
		ofs << std::endl;
	}
	ofs.close();
}

void genRandFile2(int lines)
{
	std::ofstream ofs;
	ofs.open("Random Data.txt");

	std::string *stringArr = new std::string[lines];
	fillArrAsc(stringArr, lines);
	shuffleArr(stringArr, lines);

	for (int i = 0; i < lines; i++)
	{
		ofs << stringArr[i] << std::endl;
	}
	ofs.close();
	delete[] stringArr;
}

template<typename E>
void fillArrAsc(E a[], int size) {	//Fills array with values 0-n in ascending order
	for (int i = 0; i < size; i++) {
		a[i] = i + 65;
	}
}

template<typename E>
void shuffleArr(E a[], int size) {	//Randomly shuffles an array
	int num;
	for (int i = 0; i < size; i++) {
		num = rand() % size;
		swap(a[i], a[num]);
	}
}

std::streamoff readData(std::string *inBuff, std::streamoff start, int size)
{
	std::streamoff getPos;
	std::ifstream ifs("Random Data.txt");

	if (ifs.is_open())
	{
		ifs.seekg(start);
		//while(!stream.eof())
		for (int i = 0; i < size; i++)
		{
			//while (getline(ifs, buffer[i]))
			getline(ifs, inBuff[i]);
		}
	}
	getPos = ifs.tellg();
	//printArr(inBuff, size);
	ifs.close();

	return getPos;
	//delete buffer;
}

void clearData()
{
	std::ofstream ofs("Sorted Data.txt", std::ios::out | std::ios::trunc);
	ofs.close();
}

void writeData(std::string *outBuff, int size)
{
	std::ofstream ofs("Sorted Data.txt", std::ios::out | std::ios::app);

	if (ofs.is_open())
	{
		//ofs.seekp(start);
		//while(!stream.eof())
		for (int i = 0; i < size; i++)
		{
			//while (getline(ifs, buffer[i]))
			ofs << outBuff[i] << std::endl;
		}
	}
	//printArr(outBuff, size);
	ofs.close();
}

template<typename E>
void printArr(E a[], int size) {	//Prints an array
	for (int i = 0; i < size; i++) {
		std::cout << a[i] << std::endl;
	}
}

template<typename E>
void printHeap(heap<E, Comp<E>>* heap, int size) {	//Prints a heap
	for (int i = 0; i < size; i++) {
		std::cout << heap->getVal(i) << std::endl;
	}
}

template<typename E>
void repSel(heap<E, Comp<E>>* minHeap, std::streamoff start, int buffSize)
{
	E *inBuff = new E[buffSize];
	E *outBuff = new E[buffSize];
	int heapSize = minHeap->size();

	for (int i = 0; i < 1; i++)
	{
		std::cout << "start" << start << std::endl;
		start = readData(inBuff, start, buffSize);
		std::cout << "start" << start << std::endl;
		//std::cout << "inBuff_______________________" << std::endl;
		//printArr(inBuff, buffSize);
		//std::cout << "inBuff_______________________" << std::endl;
		for (int j = 0; j < buffSize; j++)
		{

			if (minHeap->size() == 0)	//if heap size is 0, rebuild heap
			{
				minHeap->setHeapSize(heapSize);
				minHeap->buildHeap();
				//std::cout << "buildHeap_______________________" << std::endl;
			}

			outBuff[j] = minHeap->getVal(0);	//send root to heap buffer
			//std::cout << "outBuff_______________________" << outBuff[j] << std::endl;
			if (inBuff[j] > outBuff[j])
			{
				minHeap->setVal(0, inBuff[j]);
				minHeap->siftdown(0);	//siftdown root
				//std::cout << "heap_______________________" << std::endl;
				//printHeap(minHeap, buffSize);
				//std::cout << "heap_______________________" << std::endl;
				//std::cout << minHeap->size() << "size_______________________" << std::endl;

			}
			else
			{
				minHeap->removefirst();
				//std::cout << "heap_______________________" << std::endl;
				//printHeap(minHeap, buffSize);
				//std::cout << "heap_______________________" << std::endl;
				//std::cout << minHeap->size() << "size_______________________" << std::endl;
			}
		}
		writeData(outBuff, buffSize);

		std::cout << "in___________________________________" << std::endl;
		printArr(inBuff, buffSize);
		std::cout << "out___________________________________" << std::endl;
		printArr(outBuff, buffSize);
	}
	delete[] inBuff;
	delete[] outBuff;
}

template<typename E>
void multiMrg(int buffSize)	//Temporarily using quicksort for testing
{
	E *inBuff = new E[buffSize];
	readData(inBuff, 0, buffSize);

	qsortO(inBuff, buffSize);

	writeData(inBuff, 0, buffSize);

	delete[] inBuff;
}