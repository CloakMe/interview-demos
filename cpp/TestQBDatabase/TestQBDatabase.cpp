// TestQBDatabase.cpp : Defines the entry point for the console application.
//
#include <iostream>

#include "stdafx.h"
#include "Utilities.h"
#include "QBRecordCollection.h"

void Test1()
{
	int N = 1000;
    QBRecordCollection recordCollection("testdata", N);
    QBRecordCollection filteredSet = recordCollection.QBFindMatchingRecords( Column::column1, "testdata500");
    QBRecordCollection filteredSet2 = recordCollection.QBFindMatchingRecords( Column::column2, "24");
	
    if( (filteredSet.size() == 1) && filteredSet2.size() == 10)
		std::cout<< "Test case 1 Passed!\n" ;
	else
		std::cout<< "Test case 1 Failed!\n" ;
}

void Test2()
{
	int N = 10000;
    QBRecordCollection recordCollection("testdata", N);
    QBRecordCollection filteredSet = recordCollection.QBFindMatchingRecords( Column::column3, "500testdata");
    QBRecordCollection filteredSet2 = recordCollection.QBFindMatchingRecords( Column::column0, "24");
	QBRecordCollection filteredSet3 = recordCollection.QBFindMatchingRecords( Column::column2, "24");

    if( (filteredSet.size() == 10) && filteredSet2.size() == 1 && filteredSet3.size() == 100)
		std::cout<< "Test case 2 Passed!\n" ;
	else
		std::cout<< "Test case 2 Failed!\n" ;
}

void Test3()
{
	int N = 1000;
    QBRecordCollection recordCollection("testdata", N);
	QBRecordCollection filteredSet = recordCollection.QBFindMatchingRecords( Column::column3, "testdata");
    QBRecordCollection filteredSet2 = recordCollection.QBFindMatchingRecords( Column::column2, "101");
	QBRecordCollection filteredSet3 = recordCollection.QBFindMatchingRecords( Column::column1, "testdata1");

    if( (filteredSet.size() == N) && filteredSet2.size() == 0 && filteredSet3.size() == 111)
		std::cout<< "Test case 3 Passed!\n" ;
	else
		std::cout<< "Test case 3 Failed!\n" ;
}

int main()
{
	Test1();
	Test2();
	Test3();
	return 0;
}

