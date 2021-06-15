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

    if( (filteredSet.size() == 1) && filteredSet2.size() == 1 && filteredSet3.size() == 100)
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

    if( (filteredSet.size() == 0) && filteredSet2.size() == 0 && filteredSet3.size() == 1)
		std::cout<< "Test case 3 Passed!\n" ;
	else
		std::cout<< "Test case 3 Failed!\n" ;
}

void Test4()
{
	int N = 1000;
    QBRecordCollection recordCollection("testdata", N);
	QBRecordCollection filteredSet = recordCollection.QBFindMatchingRecords( Column::column0, "150");

	recordCollection.QBDeleteRecordByID( 150 );
	auto filteredSet3 = recordCollection.QBFindMatchingRecords( Column::column0, "150");
	auto filteredSet4 = recordCollection.QBFindMatchingRecords( Column::column1, "testdata150");

    if( filteredSet.size() == 1 && filteredSet3.size() == 0 && filteredSet4.size() == 0 )
		std::cout<< "Test case 4 Passed!\n" ;
	else
		std::cout<< "Test case 4 Failed!\n" ;
}

void Test5()
{
	int N = 10;
    QBRecordCollection recordCollection("testdata", N);

	for( int i = 0; i < N; i++ )
		recordCollection.QBDeleteRecordByID( i );
	
    if( recordCollection.size() == 0 )
		std::cout<< "Test case 5 Passed!\n" ;
	else
		std::cout<< "Test case 5 Failed!\n" ;
}

void Test6()
{
	int N = 1000;
    QBRecordCollection recordCollection("testdata", N);
	QBRecordCollection filteredSet = recordCollection.QBFindMatchingRecords( Column::column2, "15");

	recordCollection.QBDeleteRecordByID( 15 );
	for( int i = 150; i < 159; i++ )
		recordCollection.QBDeleteRecordByID( i );
	
	auto filteredSet2 = recordCollection.QBFindMatchingRecords( Column::column0, "15");

    if( filteredSet.size() == 10 && filteredSet2.size() == 0 && recordCollection.size() == N - 10 )
		std::cout<< "Test case 6 Passed!\n" ;
	else
		std::cout<< "Test case 6 Failed!\n" ;
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	return 0;
}

