#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <string.h>


int main(void)
{
	WIN32_FIND_DATA dataFind;
	HANDLE dataHandle;
	
	dataHandle = FindFirstFile("*.*", &dataFind);
	printf("%s\n", dataFind.cFileName);
	
	
	LPCTSTR lpFileName;
	DWORD dwFileAttributes;
	int file_found;
	
	while( 1 )
	{
		file_found = FindNextFile (dataHandle, &dataFind);
		if(file_found == 0) break; // no more files
		printf("%s\n", dataFind.cFileName);
		GetFileAttributes(dataFind.cFileName);
	}
	return 0;
}
