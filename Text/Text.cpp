// Text.cpp : Defines the entry point for the console application.
//

#include "text.h"


int main()
{
	text<string> t("Text.txt");
	t.print(80);
    return 0;
}

