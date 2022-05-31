#include"04PE加载过程.h"

#define FILEPATH_IN  "D:/ipmsg.exe"
#define FILEPATH_OUT "D:/ipmsg_s.exe"

VOID Test()
{
	DWORD	Size = 0;
	BOOL	isok = FALSE;
	LPVOID	pFileBuffer = NULL;
	LPVOID	pImageBuffer = NULL;
	LPVOID	pNewBuffer = NULL;

	//File-> FileBuffer
	Size = ReadPEFile((LPSTR)FILEPATH_IN, &pFileBuffer);
	if (!pFileBuffer)
	{
		printf("File-> FileBuffer失败");
		return;
	}


	//FileBuffer->ImageBuffer
	CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);

	if (!pImageBuffer)
	{
		printf("FileBuffer->ImageBuffer失败");
		free(pFileBuffer);
		return;
	}

	//ImageBuffer->NewBuffer
	Size = CopyImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);
	if (!Size || !pNewBuffer)
	{
		printf("ImageBuffer->NewBuffer失败");
		free(pFileBuffer);
		free(pImageBuffer);
		return;
	}

	//NewBuffer->文件
	isok = MemeryTOFile(pNewBuffer, Size, (LPSTR)FILEPATH_OUT);
	if (isok)
	{
		printf("存盘成功");
		return;
	}

	//释放内存
	free(pFileBuffer);
	free(pImageBuffer);
	free(pNewBuffer);
}


int main()
{
	Test();

	return 0;
}