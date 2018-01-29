#include <iostream>
#include <string>

using namespace std;

int main()
{
	char S[10] = "ABCDE";
	char *cptr;

	for (cptr = S; *cptr != '\0'; cptr++)
	{
		while (cptr != S)
			cout << *(--cptr);
	}

	return 0;
}