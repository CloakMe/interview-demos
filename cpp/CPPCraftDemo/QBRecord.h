#pragma once
#include <string>

#ifndef uint
#define uint unsigned int
#endif

enum class Column : int
{
	column0,
	column1,
	column2,
	column3,
	size
};

struct QBRecord
{
	uint column0; // unique id column
    std::string column1;
    long column2;
    std::string column3;
};


