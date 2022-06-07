
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include"源.h"


//ExeFile->FileBuffer  返回值为计算所得文件大小
//读取一个exe文件，然后输出为FileBuffer
DWORD ReadPEFile(IN const char* lpszFile, OUT LPVOID* pFileBuffer)
{
    //下面有个IN和OUT，大致意思就是参数的类型传入进来之后不进行宏扩展；
    //啥也不干，即使理解成干，也是扩展成空白，这个是C++语法中允许的；
    //LPSTR  ---->  typedef CHAR *LPSTR, *PSTR; 意思就是char* 指针；在WINNT.H头文件里面
    FILE* pFile = NULL;
    //定义一个FILE结构体指针，在标准的Stdio.h文件头里面
    //可参考：https://blog.csdn.net/qq_15821725/article/details/78929344
    DWORD fileSize = 0;
    // typedef unsigned long       DWORD;  DWORD是无符号4个字节的整型
    LPVOID pTempFileBuffer = NULL;
    //LPVOID ---->  typedef void far *LPVOID;在WINDEF.H头文件里面；别名的void指针类型

    //打开文件
    pFile = fopen(lpszFile, "rb"); //lpszFile是当作参数传递进来
    if (!pFile)
    {
        printf("打开文件失败!\r\n");
        return 0;
    }
    /*
    关于在指针类型中进行判断的操作，下面代码出现的情况和此一样，这里解释下：
    1.因为指针判断都要跟NULL比较，相当于0，假值，其余都是真值
    2.if(!pFile)和if(pFile == NULL), ----> 为空，就执行语句；这里是两个等于号不是一个等于号
    3.if(pFile)就是if(pFile != NULL), 不为空，就执行语句；
    */

    //读取文件内容后，获取文件的大小
    fseek(pFile, 0, SEEK_END);
    fileSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    /*
    fseek 通过使用二进制的方式打开文件，移动文件读写指针的位置,在stdio.h头文件里

    int fseek(FILE * stream, long offset, int fromwhere);

    上面是fseek的函数原型
    第一个参数stream 为文件指针
    第二个参数offset 为偏移量，整数表示正向偏移，负数表示负向偏移
    第三个参数fromwhere 为指针的起始位置,设定从文件的哪里开始偏移,可能取值为：SEEK_CUR，SEEK_END，SEEK_SET
    SEEK_SET 0 文件开头
    SEEK_CUR 1 当前读写的位置
    SEEK_END 2 文件尾部

    下面是相关用法和例子：
　　fseek(fp,100L,0);把fp指针移动到离文件开头100字节处；
　　fseek(fp,100L,1);把fp指针移动到离文件当前位置100字节处；
    fseek(fp,100L,2);把fp指针退回到离文件结尾100字节处。
    fseek(fp,0,SEEK_SET);将读写位置移动到文件开头;
    fseek(fp,0,SEEK_END);将读写位置移动到文件尾时;
    fseek(fp,100L,SEEK_SET);将读写位置移动到离文件开头100字节处；
    fseek(fp,100L,SEEK_CUR);将读写位置移动到离文件当前位置100字节处；
    fseek(fp,-100L,SEEK_END);将读写指针退回到离文件结尾100字节处；
    fseek(fp,1234L,SEEK_CUR);把读写位置从当前位置向后移动1234字节;
    fseek(fp,0L,2);把读写位置移动到文件尾;
    其中 --->  L后缀表示长整数

    ftell()用于返回文件当前指针指向的位置，与fseek配合可以算出文件元素数据总数。
    参考：http://c.biancheng.net/cpp/html/2519.html

    ftell()函数用来获取文件读写指针的当前位置，其原型为：long ftell(FILE * stream); 同样在stdio.h头文件里
    参数：stream 为已打开的文件指针。
    */

    //动态申请内存空间
    pTempFileBuffer = malloc(fileSize);

    /*
    参考：http://c.biancheng.net/cpp/html/137.html
    原型：void* malloc (size_t size);
    size_t ---> typedef unsigned int size_t; 无符号整型别名是size_t
    void*  ---> 函数的返回值类型是 void* ；void并不是说没有返回值或者返回空指针，而是返回的指针类型未知;
    所以在使用 malloc() 时通常需要进行强制类型转换，将 void 指针转换成我们希望的类型;
    例如：char *ptr = (char *)malloc(10);  //分配10个字节的内存空间，用来存放字符
    参数说明 ---> size 为需要分配的内存空间的大小，以字节（Byte）计。
    函数说明 ---> malloc()在堆区分配一块指定大小的内存空间，用来存放数据。这块内存空间在函数执行完成后不会被初始化;
    它们的值是未知的，所以分配完成内存之后需要初始化；
    返回值:分配成功返回指向该内存的地址，失败则返回 NULL。
    */

    if (!pTempFileBuffer)
    {
        printf("内存分配失败!\r\n");
        fclose(pFile);
        return 0;
    }

    //根据申请到的内存空间，读取数据

    size_t n = fread(pTempFileBuffer, fileSize, 1, pFile);
    if (!n)
    {
        printf("读取数据失败!\r\n");
        free(pTempFileBuffer);   // 释放内存空间
        fclose(pFile);           // 关闭文件流
        return 0;
    }

    //数据读取成功，关闭文件
    *pFileBuffer = pTempFileBuffer;  // 将读取成功的数据所在的内存空间的首地址放入指针类型pFileBuffer
    pTempFileBuffer = NULL;  // 初始化清空临时申请的内存空间
    fclose(pFile);           // 关闭文件
    return fileSize;         // 返回获取文件的大小
}

//CopyFileBuffer --> ImageBuffer
//将读取的FileBuffer拉伸加载到ImageBuffer，用作测试验证文件拉伸；
DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pImageBuffer)
{
    //LPVOID ---->  typedef void far *LPVOID;在WINDEF.H头文件里面；别名的void指针类型
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    LPVOID pTempImageBuffer = NULL;
    /*
    上面都是PE里面的相关结构体类型，使用其类型进行自定义变量，并初始化值为NULL
    PIMAGE_DOS_HEADER ---> 指向结构体，别名为这两个 IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER
    PIMAGE_NT_HEADERS ---> 指向结构体，typedef PIMAGE_NT_HEADERS32    PIMAGE_NT_HEADERS;
    PIMAGE_FILE_HEADER ---> 指向结构体，别名为这两个 IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
    PIMAGE_OPTIONAL_HEADER32 ---> 指向结构体，别名为这两个 IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;
    PIMAGE_SECTION_HEADER ---> 指向结构体，别名为这两个 IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;
    */

    if (pFileBuffer == NULL)
    {
        printf("FileBuffer 获取失败!\r\n");
        return 0;
    }

    //判断是否是有效的MZ标志
    if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("无效的MZ标识\r\n");
        return 0;
    }
    /*
    IMAGE_DOS_SIGNATURE 这个在头文件WINNT.H里面，对应是个无参数宏；
    #define IMAGE_DOS_SIGNATURE                 0x5A4D      // MZ
    在宏扩展的时候就会替换为0x5A4D ，然后根据架构的不同进行排序存储，分大端和小端模式；
    使用上面方式进行比对是否是有效的MZ头是非常有效；
    而且IMAGE_DOS_SIGNATURE存储的值是两个字节，刚好就是PWORD ---> typedef WORD near *PWORD;
    所以在进行比较的时候需要强制类型转换为相同的类型进行比较
    */

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    //这里的定义，就相当于已经确定了，其头肯定是MZ了，然后强制转换类型为PIMAGE_DOS_HEADER，就是Dos头

    //判断是否是有效的PE标志
    if (*((PDWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("无效的PE标记\r\n");
        return 0;
    }
    /*
    IMAGE_NT_SIGNATURE  ---> #define IMAGE_NT_SIGNATURE   0x00004550  // PE00
    上述同样是个宏扩展，在头文件WINNT.H里面；
    在进行比对的时候因为在Dos头里面有个值是 e_lfanew 对应的时候DWORD类型，所以在进行指针相加的时候
    需要先进行强制类型转换，然后相加，即移动指针位置；然后最终需要比对的结果是0x4550站两个字节
    所以又要强制转换类型为PWORD；
    */
    //定位NT头
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    //上面偏移完成之后pFileBuffer的指针偏移到了NT头---> pNTHeader
    //****************************************************************************************
    //定位PE文件头
    pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
    //根据PE头的结构体内容，PE文件头位置在NT头首地址偏移4个字节即可得到pPEHeader
    //****************************************************************************************
    //定位可选PE头
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    /*
    要得到可选PE的首地址位置，就根据上面得到的PE文件头位置里面的IMAGE_SIZEOF_FILE_HEADER来定位；
    IMAGE_SIZEOF_FILE_HEADER也是个宏扩展，里面字节描述了PE文件头的大小是20个字节；
    #define IMAGE_SIZEOF_FILE_HEADER  20，所以只要在PE文件头的首地址偏移20个字节即可移动到可选PE头；
    指针相加的时候，此处的类型依然是DWORD
    */
    //****************************************************************************************
    //第一个节表指针
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);
    /*
    这里要移动到第一个节表指针的首地址，就需要根据上面标准PE文件头中的SizeOfOptionalHeader获取具体可选PE
    头的大小，然后根据这个大小进行偏移即可；
    */
    //****************************************************************************************

    /*
    到了节表的首地址位置之后，因为需要将FileBuffer复制到ImageBuffer，这个过程中，节表之前的Dos头，NT头
    PE文件头，可选PE头，她们的大小都是不变的，所以定位出来之后，到后面的操作中直接复制即可，而节表不一样
    她在FileBuffer状态和ImageBuffer状态是不相同的，她们节表之间复制转换到ImageBuffer是需要拉长节表，所以
    在操作的时候是需要确定FileBuffer到ImageBuffer之后ImageBuffer的大小是多少，而这个大小，已经在可选PE头
    里面的某一个值中已经给出来了 ---> SizeOfImage ;
    注意：FileBuffer和ImageBuffer都是在内存中的展示，只不过FileBuffer是使用winhex等类似的形式打开查看其
    二进制的形式，而ImageBuffer则是双击打开应用程序，将其加载至内存中显示的二进制的形式；
    */
    //****************************************************************************************

    //根据SizeOfImage申请新的内存空间
    pTempImageBuffer = malloc(pOptionHeader->SizeOfImage);

    if (!pTempImageBuffer)
    {
        printf("再次在堆中申请一块内存空间失败\r\n");
        return 0;
    }

    //因为下面要开始对内存空间进行复制操作，所以需要初始化操作，将其置为0，避免垃圾数据，或者其他异常
    //初始化新的缓冲区
    memset(pTempImageBuffer, 0, pOptionHeader->SizeOfImage);
    /*
    参考：http://c.biancheng.net/cpp/html/157.html

    在头文件string.h里面

    void* memset( void* ptr,int value,size_t num );
    memset()函数用来将指定内存的前n个字节设置为特定的值;

    参数说明：
    ptr     为要操作的内存的指针;
    value   为要设置的值;既可以向value传递int类型的值,也可以传递char类型的值,int和char可以根据ASCII码相互转换;
    num     为ptr的前num个字节,size_t就是unsigned int。
    函数说明：memset()会将ptr所指的内存区域的前num个字节的值都设置为value,然后返回指向ptr的指针;
    */
    //****************************************************************************************

    //根据SizeOfHeaders大小的确定，先复制Dos头
    memcpy(pTempImageBuffer, pDosHeader, pOptionHeader->SizeOfHeaders);
    /*
    参考：http://c.biancheng.net/cpp/html/155.html

    在头文件string.h里面

    void* memcpy (void* dest,const void* src,size_t num);
    memcpy()函数功能用来复制内存的；她会复制src所指向内容的首地址，作为起始位置，然后偏移num个字节到dest所指的内存地址
    的位置；此函数有个特征就是，她并不关心被复制的数据类型，只是逐字节地进行复制，这给函数的使用带来了很大的灵活性，
    可以面向任何数据类型进行复制；

    需要注意的是：
    dest 指针要分配足够的空间，也就是要大于等于num字节的空间，如果没有分配足够的空间会出现错误；
    dest和src所指的内存空间不能重叠（如果发生了重叠，使用 memmove() 会更加安全）。

    所以上面的代码的含义如下：
    (1)pDosHeader ---> 是指向pFileBuffer的首地址，也就是内存复制的时候从这里开始；
    (2)pTempImageBuffer  ---> 这里是表示上面要复制的目的，要把内容复制到这块内存来；
    (3)pOptionHeader->SizeOfHeaders  ---> 这里表示复制多大的内容到pTempImageBuffer里面去；
    (4)从上面看来我们就知道复制到目标pOptionHeader->SizeOfHeaders所在的内存空间一定要比pTempImageBuffer大；
    */
    //****************************************************************************************

    //上面把已经确定的头都复制好了，那么下面就可以开始复制节的里面的内容，因为节不仅仅是一个，所以需要用到for循环进行操作
    //根据节表循环copy节的内容
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;
    //定义一个临时节表的指针
    for (int i = 0; i < pPEHeader->NumberOfSections; i++, pTempSectionHeader++)
    {
        memcpy((void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress),
            (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData), pTempSectionHeader->SizeOfRawData);
    }
    /*
    上面的大概操作就是根据标准PE文件头里面的值 NumberOfSections确定有几个节，然后不断的计算并增加指针偏移位置，不停的复制

    PointerToRawData   ---> 节在文件中的偏移地址；
    VirtualAddress     ---> 节在内存中的偏移地址;
    SizeOfRawData      ---> 节在文件中对齐后的尺寸;

    (void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress)   ---> Dest（目的地）
    上面我们已经知道了函数memcpy是怎么复制操作的，所以这里我们依依解释下：
    首先我们知道，上面展示的是目的地，而且我们的目的是要从FileBuffer节内容复制到ImageBuffer节的内容，
    那么要使用到的是文件被双击打开之后在内存中的偏移地址，这个地址就是VirtualAddress；这里举个例子:
    正常打开notepad.exe,然后使用winhex加载这个notepad.exe的内存数据，同时使用PE解析工具得到两个值的信息如下：
    可选PE头 ---> ImageBase   ---> 0x01000000
    第一个节表显示的VirtualAddress  ---> 00001000
    上面两个值相加就得到了文件被打开在内存中第一个节的真实数据的起始位置 ---> 0x01001000
    查看winhex对应的地址，确认是对的；

    (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData)      ---> Src（源复制的起始内存地址）
    同样是上面的例子：
    PointerToRawData是节在文件中的偏移地址，而我们知道，在文件中和在内存中是不一样的，因为在内存中有ImageBase的说法，
    但在文件中没有，所以她的起始位置就是文件存储在硬盘的时候使用winhex打开的开头位置，为这里同样使用winhex以二进制的形式
    打开notepad.exe（非双击打开），发现文件的起始位置是0x00000000，同时使用PE解析工具确认出了PointerToRawData的值
    PointerToRawData  ---> 0x00000400 ; 起始位置为0x00000000 ,她们相加就得到第一个节表的起始位置为0x00000400
    查看winhex对应的地址，确认是对的；
    所以这里总结下来的Src，就是内存复制的时候，从这个偏移地址开始拿数据开始复制；

    pTempSectionHeader->SizeOfRawData
    这里就是告诉我们上面复制要复制多大的内容到 (void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress)
    SizeOfRawData ---> 节在文件中对齐后的尺寸;
    例子还是以上面的为例：
    通过PE解析工具确认SizeOfRawData的大小为：0x00007800

    总结：
    memcpy((void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress),
    (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData),
    pTempSectionHeader->SizeOfRawData);

    上面代码就是在文件中的形式找到要复制的位置0x00000400的起始位置开始复制，要复制0x00007800个字节大小，也就是从
    0x00000400这个地址开始向后偏移7800个字节，将这些数据复制到文件双击被打开时候的内存地址0x01001000为起点向后覆盖复制
    完成即可，为这里测试算了下；0x00000400+0x00007800=0x00007C00 ; 0x00007C00这个地址刚好是第二个节的PointerToRawData
    这样就可以很好的理解for循环对第二个节的复制；
    */

    //****************************************************************************************
    //返回数据
    * pImageBuffer = pTempImageBuffer;
    //将复制好后节的首地址保存到指针pImageBuffer中
    pTempImageBuffer = NULL;
    //初始化清空临时使用的pTempImageBuffer

    return pOptionHeader->SizeOfImage;
}

//FileBuffer ---> NewImageBuffer（新增节操作）?
//通过复制FileBuffer并增加1000H到新的NewImageBuffer,用作新增节；
DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeder = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PIMAGE_SECTION_HEADER pLastSectionHeader = NULL;
    LPVOID pTempNewImageBuffer = 0;
    DWORD sizeOfFile = 0;
    DWORD numberOfSection = 0;
    DWORD okAddSections = 0;


    //判断读取pFileBuffer读取是否成功
    if (!pFileBuffer)
    {
        printf("缓冲区指针无效\r\n");
        return 0;
    }

    //判断是否为MZ标志

    if ((*(PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)// IMAGE_DOS_SIGNATURE --> MZ
    {
        printf("不是一个有效的MZ标志\r\n");
        return 0;
    }

    //判断是否为PE标志
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE) // IMAGE_NT_SIGNATURE --> PE
    {
        printf("不是有效的PE标志\r\n");
        return 0;
    }

    //*********************申请开辟内存空间*****************************************************************

    sizeOfFile = fileSize + 0x1000;
    pTempNewImageBuffer = malloc(sizeOfFile);

    //判断内存空间开辟是否成功
    if (!pTempNewImageBuffer)
    {
        printf("pTempNewImageBuffer开辟内存空间失败\r\n");
        return 0;
    }

    //初始化内存内容
    memset(pTempNewImageBuffer, 0, sizeOfFile);

    //初始化完成之后，先把为修改的内存空间全部拷贝到新的内存空间
    memcpy(pTempNewImageBuffer, pFileBuffer, fileSize);

    //定位Dos头地址
    pDosHeader = (PIMAGE_DOS_HEADER)(pTempNewImageBuffer);

    //定位NT头的地址
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pTempNewImageBuffer + pDosHeader->e_lfanew);

    //定位标志PE头地址
    pPEHeder = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 0x04);//PE SIGNATURE 站4个字节

    //定位可选PE头地址
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)(((DWORD)pPEHeder) + IMAGE_SIZEOF_FILE_HEADER);//IMAGE_SIZEOF_FILE_HEADER -> 20个字节

    //定位第一个节表地址
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeder->SizeOfOptionalHeader);

    //定位最后一个节表的地址
    pLastSectionHeader = &pSectionHeader[pPEHeder->NumberOfSections - 1];

    //判断是否有足够的空间添加一个节表
    //判断条件：
    /*
        SizeOfHeader - (DOS + 垃圾数据 + PE标记 + 标准PE头 + 可选PE头 + 已存在节表) >= 2个节表的大小
        SizeOfHeader在可选PE头里面
    */

    okAddSections = (DWORD)(pOptionHeader->SizeOfHeaders - (pDosHeader->e_lfanew + 0x04 + \
        sizeof(PIMAGE_FILE_HEADER) + pPEHeder->SizeOfOptionalHeader + sizeof(PIMAGE_SECTION_HEADER) \
        * pPEHeder->NumberOfSections));

    if (okAddSections < 2 * sizeof(PIMAGE_SECTION_HEADER))
    {
        printf("这个exe文件头不剩余空间不够\r\n");
        free(pTempNewImageBuffer);
        return 0;
    }

    //上面没问题，就开始修改内容了
//*************************修改内容*******************************************************************

    //初始化新节表信息
    PWORD pNumberOfSection = &pPEHeder->NumberOfSections;
    PDWORD pSizeOfImage = &pOptionHeader->SizeOfImage;

    numberOfSection = pPEHeder->NumberOfSections;
    PVOID pSecName = &pSectionHeader[numberOfSection].Name;
    PDWORD pSecMisc = &pSectionHeader[numberOfSection].Misc.VirtualSize;
    PDWORD pSecVirtualAddress = &pSectionHeader[numberOfSection].VirtualAddress;
    PDWORD pSecSizeOfRawData = &pSectionHeader[numberOfSection].SizeOfRawData;
    PDWORD pSecPointToRawData = &pSectionHeader[numberOfSection].PointerToRawData;
    PDWORD pSecCharacteristics = &pSectionHeader[numberOfSection].Characteristics;

    //修改PE文件头里面的节数量信息

    printf("*pNumberOfSection:%#X \r\n", pPEHeder->NumberOfSections);
    *pNumberOfSection = pPEHeder->NumberOfSections + 1;
    printf("*pNumberOfSection:%#X \r\n", pPEHeder->NumberOfSections);

    //修改PE可选头里面SizeOfImage信息
    printf("*pSizeOfImage:%#X \r\n", pOptionHeader->SizeOfImage);
    *pSizeOfImage = pOptionHeader->SizeOfImage + 0x1000;
    printf("*pSizeOfImage:%#X \r\n", pOptionHeader->SizeOfImage);

    //向节表中添加数据

    memcpy(pSecName, ".newSec", 8);
    *pSecMisc = 0x1000;
    //这里VirtualAddress的地址需要根据最后一个节表中对齐前内存中的实际大小?
    //和文件中对齐后的大小，分别使用VirtualAddress加上她们的值，哪个大，就是
    //哪个；
    //VirtualAddress+max(VirtualSize,SizeOfRawData)
    //就是上面的公式

    //判断出要添加的值
    DWORD add_size = pLastSectionHeader->Misc.VirtualSize > pLastSectionHeader->SizeOfRawData ? \
        pLastSectionHeader->Misc.VirtualSize:pLastSectionHeader->SizeOfRawData;
    //上面是个三目运算符

    printf("pLastSectionHeader: %#X \r\n", pLastSectionHeader);
    printf("add_size: %#X \r\n", add_size);
    printf("numberOfSection: %#X \r\n", pPEHeder->NumberOfSections);
    printf("pLastSectionHeader->Misc.VirtualSize: %#X \r\n", pLastSectionHeader->Misc.VirtualSize);
    printf("pLastSectionHeader->SizeOfRawData: %#X \r\n", pLastSectionHeader->SizeOfRawData);
    printf("add_size: %#X \r\n", add_size);

    *pSecVirtualAddress = pLastSectionHeader->VirtualAddress + add_size;

    //SectionAlignment对齐

    if (*pSecVirtualAddress % pOptionHeader->SectionAlignment)
    {
        *pSecVirtualAddress = *pSecVirtualAddress / pOptionHeader->SectionAlignment * \
            pOptionHeader->SectionAlignment + pOptionHeader->SectionAlignment;
    }

    *pSecSizeOfRawData = 0x1000;
    *pSecPointToRawData = pLastSectionHeader->PointerToRawData + pLastSectionHeader->SizeOfRawData;

    //FileAlignment对齐

    if (*pSecPointToRawData % pOptionHeader->FileAlignment)
    {
        *pSecPointToRawData = *pSecPointToRawData / pOptionHeader->FileAlignment * \
            pOptionHeader->FileAlignment + pOptionHeader->FileAlignment;
    }

    *pSecCharacteristics = 0xFFFFFFFF;

    *pNewImageBuffer = pTempNewImageBuffer;
    pTempNewImageBuffer = NULL;

    return sizeOfFile;
}

//求对齐后的大小
//Actuall_size  ---> 内存中对齐前实际的大小 ---> VirtualSize
//Align_size  ---> 文件中对齐后的大小 ---> SizeOfRawData
DWORD AlignLength(DWORD Actuall_size, DWORD Align_size)
{
    if (Actuall_size % Align_size == 0)
    {
        return Actuall_size;
    }
    else
    {
        DWORD n = Actuall_size / Align_size;
        return Align_size * (n + 1);
    }
}

//另一种对齐计算方式
DWORD Alignment(DWORD alignment_value, DWORD addend, DWORD address)
{
    int n = 0;
    if (addend / alignment_value)
    {
        if (addend % alignment_value)
        {
            n = addend / alignment_value + 1;
        }
        else
        {
            n = addend / alignment_value;
        }
    }
    else
    {
        if (addend)
        {
            n = 1;
        }
        else
        {
            n = 0;
        }
    }
    address += n * alignment_value;
    return address;
}

//ImageBuffer ---> NewImageBuffer
//将拉伸后加载到内存的ImageBuffer存入到NewImageBuffer，修改数据完成之后，准备存盘操作
DWORD FileBufferToModifyImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pNewImageBuffer)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PIMAGE_SECTION_HEADER pLastSectionHeader = NULL;
    LPVOID pTempNewImageBuffer = NULL;
    DWORD ImageBuffer_Size = 0;
    DWORD numberOfSection = 0;

    //判断读取pImageBuffer是否成功
    if (!pFileBuffer)
    {
        printf("缓冲区指针无效\r\n");
    }

    //判断是否是有效的MZ头
    if ((*(PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("不是有效的MZ头\r\n");
        return 0;
    }

    //判断是否是有效的PE头
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("不是有效的PE头\r\n");
        return 0;
    }

    //定位NT头
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);

    //定位标准的PE文件头
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);

    //定位可选PE头
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

    //定位第一个节表地址
    numberOfSection = pPEHeader->NumberOfSections;
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //定位最后一个节表地址
    pLastSectionHeader = &pSectionHeader[numberOfSection - 1];
    //    printf("numberOfSection --> %#X \r\n",numberOfSection);
    //    printf("*pSectionHeader --> %#X \r\n",pSectionHeader->Misc.VirtualSize);
    //    printf("*pLastSectionHeader --> %#X \r\n",&pLastSectionHeader);

        //开始操作需要修改的部分

        //最后一个节中内存中对齐前的大小；
    PDWORD pVirtualSize = &pLastSectionHeader->Misc.VirtualSize;
    //最后一个节在文件中对齐后的大小；
    PDWORD pSizeOfRawData = &pLastSectionHeader->SizeOfRawData;
    //文件中SizeOfImage的大小；
    PDWORD pSizeOfImage = &pOptionHeader->SizeOfImage;

    //扩展修改之前的数据
//    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
//    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
//
//    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
//    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
//
//    printf("&pOptionHeader->SizeOfImage --> %#X \r\n",pSizeOfImage);
//    printf("*pOptionHeader->SizeOfImage --> %#X \r\n",*pSizeOfImage);

    //扩展修改pVirtualSize
    * pVirtualSize = AlignLength(*pVirtualSize, pOptionHeader->SectionAlignment) + 0x1000;
    //    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
    //    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
    //    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
    //    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
    //
        //扩展修改pSizeOfRawData
    *pSizeOfRawData = AlignLength(*pSizeOfRawData, pOptionHeader->SectionAlignment) + 0x1000;
    //    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
    //    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
    //    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
    //    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
    //    printf("&pOptionHeader->SizeOfImage --> %#X \r\n",pSizeOfImage);
    //    printf("*pOptionHeader->SizeOfImage --> %#X \r\n",*pSizeOfImage);

        //修改SizeOfImage
    *pSizeOfImage += 0x1000;
    //    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
    //    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
    //    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
    //    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
    //    printf("&pOptionHeader->SizeOfImage --> %#X \r\n",pSizeOfImage);
    //    printf("*pOptionHeader->SizeOfImage --> %#X \r\n",*pSizeOfImage);

        //得到修改之后的大小准备申请内存空间

    ImageBuffer_Size = pOptionHeader->SizeOfImage;
    pTempNewImageBuffer = malloc(ImageBuffer_Size);

    if (!pTempNewImageBuffer)
    {
        printf("分配内存空间失败\r\n");
        return 0;
    }

    //初始化内存空间
    memset(pTempNewImageBuffer, 0, ImageBuffer_Size);

    //复制SizeOfHeaders
    memcpy(pTempNewImageBuffer, pDosHeader, pOptionHeader->SizeOfHeaders);

    //创建临时节的结构体指针，遍历数据
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;

    for (DWORD i = 0; i < pPEHeader->NumberOfSections; i++, pTempSectionHeader++)
    {
        memcpy((PVOID)((DWORD)pTempNewImageBuffer + pTempSectionHeader->VirtualAddress), \
            (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData), pTempSectionHeader->SizeOfRawData);
    }

    *pNewImageBuffer = pTempNewImageBuffer;
    pTempNewImageBuffer = NULL;
    return *pSizeOfImage;
}

//将ImageBuffer更改为一个节表和节然后压缩为NewBuffer，供存盘准备
DWORD ImageBufferMergeSections(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PIMAGE_SECTION_HEADER pLastSectionHeader = NULL;
    LPVOID pTempMergeSection = NULL;
    DWORD finalSections_Size = 0;
    DWORD numberOfSection = 0;
    DWORD lastSectionsMax_Size = 0;
    DWORD sizeOfFile = 0;
    DWORD NewSecCharacteristics = 0;
    DWORD NewSectionsBuffer = 0;

    //判断读取pImageBuffer是否成功
    if (pImageBuffer == NULL)
    {
        printf("缓冲区指针无效\r\n");
    }
    //判断是否是有效的MZ标志
    if (*((PWORD)pImageBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("不是有效的MZ头\r\n");
        free(pImageBuffer);
        return 0;
    }
    //判断是否是有效的PE标志

    pDosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
    if (*((PDWORD)((DWORD)pImageBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("不是有效的PE标志\r\n");
        free(pImageBuffer);
        return 0;
    }


    //定位NT头
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBuffer + pDosHeader->e_lfanew);

    //定位标准的PE文件头
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);

    //定位可选PE头
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

    //定位第一个节表地址
    numberOfSection = pPEHeader->NumberOfSections;
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //定位最后一个节表地址
    pLastSectionHeader = &pSectionHeader[numberOfSection - 1];

    //定义一个临时节表指针
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;

    //先计算出SizeOfHeaders
    pOptionHeader->SizeOfHeaders = Alignment(pOptionHeader->SectionAlignment, pOptionHeader->SizeOfHeaders, 0);


    //最后一个节中内存对齐前的大小；
    DWORD pVirtualSize = pLastSectionHeader->Misc.VirtualSize;
    //最后一个节在文件中对齐后的大小；
    DWORD pSizeOfRawData = pLastSectionHeader->SizeOfRawData;

    //计算最后一个节中最大值是SizeOfRawData还是VirtualSize
    lastSectionsMax_Size = (pSizeOfRawData > pVirtualSize ? pSizeOfRawData : pVirtualSize);

    //测试一把
    if (!debug)
    {
        printf("pLastSectionHeader->SizeOfRawData: %#X \r\n", pSizeOfRawData);
        printf("pLastSectionHeader->Misc.VirtualSize: %#X \r\n", pVirtualSize);
        printf("lastSectionsMax_Size: %#X \r\n", lastSectionsMax_Size);
    }

    //计算最终合并后节对应SizeOfRawData或VirtualSize的大小
    finalSections_Size = (pLastSectionHeader->VirtualAddress + lastSectionsMax_Size - pOptionHeader->SizeOfHeaders);

    //遍历到最后一个节表,具体操作就是将每个节都置为0
    for (DWORD i = 0; i < numberOfSection; i++, pTempSectionHeader++)
    {
        NewSecCharacteristics |= pTempSectionHeader->Characteristics;
        //上述 |= 按位或然后赋值，因为NewSecCharacteristics为0，所以新的节对应的值也都置为0了
        if (i > 0)
        {
            memset(&pSectionHeader[i], 0, IMAGE_SIZEOF_SECTION_HEADER);//将每个节都置为0
        }
    }

    //IMAGE_SIZEOF_SECTION_HEADER --> 40

    //修改第一个节的SizeOfRawData和VirtualSize的值，将其更改为上面计算出来的最终值
    pSectionHeader->Misc.VirtualSize = finalSections_Size;
    pSectionHeader->SizeOfRawData = finalSections_Size;

    //修改新节的Characteristics的值
    pSectionHeader->Characteristics = NewSecCharacteristics;

    //修改pPEHeader->NumberOfSections的属性为0x01
    pPEHeader->NumberOfSections = 0x01;

    //继续测试一把
    if (!debug)
    {
        printf("pSectionHeader->Characteristics: %#X \r\n", pSectionHeader->Characteristics);
        printf("pSectionHeader->SizeOfRawData: %#X \r\n", pSectionHeader->SizeOfRawData);
        printf("pSectionHeader->Misc.VirtualSize: %#X \r\n", pSectionHeader->Misc.VirtualSize);
    }

    //根据SizeOfImage申请新的空间,到此处说明上面已经更改完成了各个相关的属性值，可以申请内存空间为存盘做准备了；
    pTempMergeSection = malloc(pOptionHeader->SizeOfImage);

    //sizeOfFile = pOptionHeader->SizeOfHeaders + finalSections_Size;
    //使用winhex打开notepad.exe 是0x00000400，这是第一个节之前的所有大小
    // for(DWORD i = 0;i<numberOfSection;i++)
    // {
    //     sizeOfFile += pSectionHeader[i].SizeOfRawData;  // pSectionHeader[i]另一种加法
    // }

    //pTempNewBuffer = malloc(sizeOfFile);

    if (!pTempMergeSection)
    {
        printf("申请内存空间失败\r\n");
        return 0;
    }

    //初始化新的缓冲区
    memset(pTempMergeSection, 0, pOptionHeader->SizeOfImage);
    //根据SizeOfHeaders 先copy头
    memcpy(pTempMergeSection, pDosHeader, pOptionHeader->SizeOfHeaders);
    //开始复制节的信息，因为这里是合并节，只有一个节，所以不需要使用for循环进行遍历复制，直接复制即可；
    memcpy((PDWORD)((DWORD)pTempMergeSection + pSectionHeader->PointerToRawData), \
        (PDWORD)((DWORD)pImageBuffer + pSectionHeader->VirtualAddress), \
        pSectionHeader->SizeOfRawData);

    //返回数据
    *pNewBuffer = pTempMergeSection;
    pTempMergeSection = NULL;
    return pOptionHeader->SizeOfImage;
}

//ImageBuffer ---> NewBuffer
//将拉伸后加载到内存的ImageBuffer存入到NewBuffer里面，然后准备存盘；
DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer)
{
    //下面大部分操作都是跟上面一样的，这里就不再赘述了
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    LPVOID pTempNewBuffer = NULL;
    DWORD sizeOfFile = 0;
    DWORD numberOfSection = 0;

    if (pImageBuffer == NULL)
    {
        printf("缓冲区指针无效\r\n");
    }
    //判断是否是有效的MZ标志
    if (*((PWORD)pImageBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("不是有效的MZ头\r\n");
        return 0;
    }
    pDosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
    //判断是否是有效的PE标志
    if (*((PDWORD)((DWORD)pImageBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("不是有效的PE标志\r\n");
        return 0;
    }
    //NT头地址
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBuffer + pDosHeader->e_lfanew);
    //标准PE文件头
    pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
    //可选PE头
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    //第一个节表地址
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //计算文件需要的空间--最后一个节的文件偏移+节对齐后的长度
    /*
    numberOfSection = pPEHeader->NumberOfSections;
    pSectionHeader = pSectionHeader[numberOfSection-1];
    sizeOfFile = (pSectionHeader->PointerToRawData + pSectionHeader->Misc.VirtualSize + pOptionHeader->FileAlignment);
    printf("sizeOfFile %X \r\n",sizeOfFile);

    for (DWORD i=0;i<=numberOfSection;i++)
    {
        sizeOfFile += sizeOfFile[i];
    }
    */

    sizeOfFile = pOptionHeader->SizeOfHeaders;
    //使用winhex打开notepad.exe 是0x00000400，这是第一个节之前的所有大小
    for (DWORD i = 0; i < pPEHeader->NumberOfSections; i++)
    {
        sizeOfFile += pSectionHeader[i].SizeOfRawData;  // pSectionHeader[i]另一种加法
    }

    /*
    上面的for循环大概意思就是基于几个节的数量依次循环叠加sizeOfFile的值；因为SizeOfRawData是文件中对齐后的大小；
    所以循环计算如下：
    sizeOfFile = 0x00000400 + 0x00007800 = 0x00007C00
    sizeOfFile = 0x00007C00 + 0x00000800 = 0x00008400
    sizeOfFile = 0x00008400 + 0x00008000 = 0x00010400

    */

    //根据SizeOfImage申请新的空间
    pTempNewBuffer = malloc(sizeOfFile);

    if (!pTempNewBuffer)
    {
        printf("申请内存空间失败\r\n");
        return 0;
    }
    //初始化新的缓冲区
    memset(pTempNewBuffer, 0, sizeOfFile);
    //根据SizeOfHeaders 先copy头
    memcpy(pTempNewBuffer, pDosHeader, pOptionHeader->SizeOfHeaders);
    //根据节表循环复制节
    //PIMAGE_SECTION_HEADER pTempSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader);
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;
    for (int j = 0; j < pPEHeader->NumberOfSections; j++, pTempSectionHeader++)
    {
        /*memcpy((LPVOID)((DWORD)pTempNewBuffer + pTempSectionHeader->PointerToRawData),
        (LPVOID)((DWORD)pImageBuffer + pTempSectionHeader->VirtualAddress),
        pTempSectionHeader->SizeOfRawData);*/
        //PointerToRawData节区在文件中的偏移,VirtualAddress节区在内存中的偏移地址,SizeOfRawData节在文件中对齐后的尺寸
        memcpy((PDWORD)((DWORD)pTempNewBuffer + pTempSectionHeader->PointerToRawData),
            (PDWORD)((DWORD)pImageBuffer + pTempSectionHeader->VirtualAddress),
            pTempSectionHeader->SizeOfRawData);
        //printf("%X  --> PoniterToRadata\r\n",pTempSectionHeader->PointerToRawData);
        //printf("%X  --> VirtualAddress\r\n",pTempSectionHeader->VirtualAddress);
        //printf("%X  --> VirtualSize\r\n",pTempSectionHeader->Misc.VirtualSize);
    }

    //返回数据
    *pNewBuffer = pTempNewBuffer;
    pTempNewBuffer = NULL;
    return sizeOfFile;
}

//将上面得到的MemBuffer存盘到本地；
BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT const char* lpszFile)
{
    FILE* fp = NULL;
    fp = fopen(lpszFile, "wb+");
    if (!fp)  //  这里我刚开始写漏了一个等于号，变成复制NULL了，导致错误
//  if(fp == NULL)  可以这么写，没问题
    {
        fclose(fp);
        return FALSE;
    }
    fwrite(pMemBuffer, size, 1, fp);
    fclose(fp);
    fp = NULL;
    return TRUE;
}

//RVA格式转换FOA  --- RvaToFileOffset
DWORD RvaToFileOffset(IN LPVOID pFileBuffer, IN DWORD dwRva)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    DWORD numberOfSection = 0;
    DWORD dwFOAValue = 0;

    //判断指针是否有效
    if (!pFileBuffer)
    {
        printf("pFileBuffer 指针无效\r\n");
        return 0;
    }
    //判断是否是有效的MZ标志
    if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("pFileBuffer不是有效的MZ标志\r\n");
        return 0;
    }
    //判断是否是一个有效的PE标志
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("pFileBuffer不是一个有效的PE标志\r\n");
        return 0;
    }

    printf("当前的Rva地址: %#X \r\n", dwRva);
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //定义个临时节表指针进行下面的计算操作
    numberOfSection = pPEHeader->NumberOfSections;
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;


    //判断dwRva所处的节
    if (dwRva <= pOptionHeader->SizeOfHeaders)
    {
        return (DWORD)dwRva;
    }
    //上面是判断如果rva地址所处的节在第一个节之前那么直接返回rva的地址；
    //否则下面就是开始遍历查找节；
    else
    {
        for (DWORD n = 0; n < numberOfSection; n++, pTempSectionHeader++)
        {//下面是判断在哪个节的范围，然后根据rva所在的地址减去所在节的VirtualAddress得到的偏移值加上文件中对应节的偏移值PointerToRawData
            if ((dwRva >= pTempSectionHeader->VirtualAddress) && (dwRva < pTempSectionHeader->VirtualAddress + pTempSectionHeader->Misc.VirtualSize))
            {
                dwFOAValue = dwRva - pTempSectionHeader->VirtualAddress + pTempSectionHeader->PointerToRawData;
            }
            else
            {
                printf("RvaToFoa 转换失败！\r\n");
                return 0;
            }
        }
    }
    return dwFOAValue;
}

//FOA格式转换RVA  --- ImageOffset
DWORD FoaToImageOffset(IN LPVOID pFileBuffer, IN DWORD dwFoa)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    DWORD numberOfSection = 0;
    DWORD dwRVAValue = 0;

    //判断指针是否有效
    if (!pFileBuffer)
    {
        printf("pFileBuffer 指针无效\r\n");
        return 0;
    }
    //判断是否是有效的MZ标志
    if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("pFileBuffer不是有效的MZ标志\r\n");
        return 0;
    }
    //判断是否是一个有效的PE标志
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("pFileBuffer不是一个有效的PE标志\r\n");
        return 0;
    }

    printf("当前的Foa地址: %#X \r\n", dwFoa);
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //定义个临时节表指针进行下面的计算操作
    numberOfSection = pPEHeader->NumberOfSections;
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;

    if (dwFoa <= pOptionHeader->SizeOfHeaders)
    {
        return (DWORD)dwFoa;
    }
    else
    {
        for (DWORD n = 0; n < numberOfSection; n++, pTempSectionHeader++)
        {
            if ((dwFoa >= pTempSectionHeader->PointerToRawData) && (dwFoa < pTempSectionHeader->SizeOfRawData))
            {
                dwRVAValue = dwFoa - pTempSectionHeader->PointerToRawData + pTempSectionHeader->VirtualAddress;
            }
            else
            {
                printf("FoaToRva 转换失败！\r\n");
                return 0;
            }
        }
    }
    return dwRVAValue;
}

//在原有的exe文件中开始操作添加ShellCode代码；

VOID AddCodeInCodeSec()
{
    LPVOID pFileBuffer = NULL;
    LPVOID pImageBuffer = NULL;
    LPVOID pNewBuffer = NULL;
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_FILE_HEADER pFileHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PBYTE codeBegin = NULL;
    BOOL isOK = FALSE;
    DWORD size = 0;

    //File-->FileBuffer
    ReadPEFile((LPSTR)FilePath_In, &pFileBuffer);
    if (!pFileBuffer)
    {
        printf("文件-->缓冲区失败\r\n");
        return;
    }

    //FileBuffer-->ImageBuffer
    CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);
    if (!pImageBuffer)
    {
        printf("FileBuffer-->ImageBuffer失败\r\n");
        free(pFileBuffer);
        return;
    }

    //判断代码段空闲区域是否能够足够存储ShellCode代码
    pDosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
    pFileHeader = (PIMAGE_FILE_HEADER)(((DWORD)pImageBuffer + pDosHeader->e_lfanew) + 4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)(((DWORD)pImageBuffer + pDosHeader->e_lfanew) + 4 + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)(((DWORD)pImageBuffer + pDosHeader->e_lfanew) + 4 + IMAGE_SIZEOF_FILE_HEADER + pFileHeader->SizeOfOptionalHeader);
    if (((pSectionHeader->SizeOfRawData) - (pSectionHeader->Misc.VirtualSize)) < SHELLCODELENGTH)
    {
        printf("代码区域空闲空间不够\r\n");
        free(pFileBuffer);
        free(pImageBuffer);
    }

    //将代码复制到空闲区域
    codeBegin = (PBYTE)((DWORD)pImageBuffer + pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize);
    printf("pSectionHeader->VirtualAddress: %#010X\r\n", pSectionHeader->VirtualAddress);
    printf("pSectionHeader->Misc.VirtualSize: %#010X\r\n", pSectionHeader->Misc.VirtualSize);
    printf("codeBegin: %#010X\r\n", codeBegin);

    memcpy(codeBegin, ShellCode, SHELLCODELENGTH);

    //修正E8-->call后面的代码区域
    DWORD callAddr = (MESSAGEBOXADDR - (pOptionHeader->ImageBase + ((DWORD)(codeBegin + 0xD) - (DWORD)pImageBuffer)));
    printf("callAddr ---> %#010X \r\n", callAddr);
    *(PDWORD)(codeBegin + 0x09) = callAddr;
    printf("*(PWORD)(codeBegin + 0x09) ---> %#010X \r\n", *(PDWORD)(codeBegin + 0x09));
    /*
    关于修正E8的理解，公式：X = 要跳转的地址 - (E8当前的地址 + 5)；
    要跳转的地址，这里是毋庸置疑的，就是我们要加入代码MessageBox的地址；
    然后要减去E8当前的地址+5的位置，这里不是太好理解；
    我们的目的是要将E8后面的4个字节计算出来，然后写入到E8后面，也就是公式中X；
    上面公式E8当前地址+5 ，而在此情况要定位到这个位置就要从代码的Dos开始通过指针相加；
    进行位置偏移到E8当前地址+5的位置；
    所以定位codeBegin的位置是：pImageBuffer指针最开始的位置（Dos头位置）通过内存中偏移的宽度移动到第一个节表的位置；
    也就是上面的pSectionHeader->VirtualAddress 操作形式；
    然后再偏移第一个节表在内存中对齐前实际的宽度（尺寸）pSectionHeader->Misc.VirtualSize；
    上述一番操作之后就到了第一个节表没有对齐前的位置，这个位置就是我们可以添加ShellCode代码的起始位置；
    到了添加ShellCode代码的起始位置之后，就要想办法添加E8位置后面的4个字节，此时根据ShellCode代码的宽度；
    进行计算，确认0x6A 00 0x6A 00 0x6A 00 0x6A 00 E8 00 00 00 00 刚好向后面数13个位置，按照十六进制看；
    就是0xD，所以在codeBegin偏移0xD个位置即可到达E9的位置，这也就是我们说的(E8当前的地址 + 5);
    到了上面的位置之后，由于我们最终是需要在程序运行之后在内存中添加ShellCode代码；所以这里一定要计算出；
    其准确的偏移地址，这样不管怎么拉伸到哪个位置，都能准确找到位置；
    注意：这里需要注意一点理解，上面说的pImageBuffer这个是我们加载程序到我们申请的内存中，绝不是程序在；
    运行中的那个内存，这里一定要理解清楚，她们是不一样的，理解了这个就能理解上面代码为什么要减去Dos头的；
    首地址，(DWORD)(codeBegin + 0xD) - (DWORD)pImageBuffer)
    */

    //修正E9-->jmp后面的代码区域
    DWORD jmpAddr = ((pOptionHeader->ImageBase + pOptionHeader->AddressOfEntryPoint) - (pOptionHeader->ImageBase + ((DWORD)(codeBegin + SHELLCODELENGTH) - (DWORD)pImageBuffer)));
    printf("jmpAddr ---> %#010X \r\n", jmpAddr);
    *(PDWORD)(codeBegin + 0x0E) = jmpAddr;
    printf("*(PWORD)(codeBegin + 0x0E) ---> %#010X \r\n", *(PDWORD)(codeBegin + 0x0E));
    /*
    公式：X = 要跳转的地址 - (E9当前的地址 + 5)
    这里同样是要计算出E9后面4个字节的地址，我们的目的是在这里添加OEP的地址，让其执行完成MessageBox之后跳转；
    OEP的地址，那么这里就要先计算出OEP地址，就是pOptionHeader->ImageBase + pOptionHeader->AddressOfEntryPoint；
    再减去(E9当前的地址 + 5) 0x6A 00 0x6A 00 0x6A 00 0x6A 00 E8 00 00 00 00 E9 00 00 00 00；
    (DWORD)codeBegin + SHELLCODELENGTH 就是加上ShellCode总长度，偏移完成之后减去ImageBuffer首地址再加上ImageBase；
    */

    //修正OEP
    printf("pOptionHeader->AddressOfEntryPoint ---> %#010X \r\n", pOptionHeader->AddressOfEntryPoint);
    printf("(DWORD)codeBegin ---> %#010X \r\n", ((DWORD)codeBegin - (DWORD)pImageBuffer));
    pOptionHeader->AddressOfEntryPoint = (DWORD)codeBegin - (DWORD)pImageBuffer;
    printf("pOptionHeader->AddressOfEntryPoint ---> %#010X \r\n", pOptionHeader->AddressOfEntryPoint);
    //修正OEP好理解，就是定位到OEP地址，然后直接通过codeBegin地址减去pImageBuffer的首地址即可；

    //ImageBuffer-->NewBuffer
    size = CopyImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);
    if (size == 0 || !pNewBuffer)
    {
        printf("ImageBuffer-->NewBuffer失败\r\n");
        free(pFileBuffer);
        free(pImageBuffer);
        return;
    }

    //NewBuffer-->文件
    isOK = MemeryTOFile(pNewBuffer, size, FilePath_Out);
    if (isOK)
    {
        printf("修改代码添加SHELLCODE 存盘成功\r\n");
        return;
    }

    //释放内存
    free(pFileBuffer);
    free(pImageBuffer);
    free(pNewBuffer);
}

//调用函数新增节表和节操作，成功之后并存盘到本地；
VOID NewSectionsInCodeSec()
{
    LPVOID pFileBuffer = NULL;
    LPVOID pNewImageBuffer = NULL;
    BOOL isOK = FALSE;
    DWORD size1 = 0;
    DWORD size2 = 0;

    //File-->FileBuffer
    size1 = ReadPEFile(FilePath_In, &pFileBuffer);
    if (size1 == 0 || !pFileBuffer)
    {
        printf("文件-->缓冲区失败\r\n");
        return;
    }
    printf("fileSize - Final: %#X \r\n", size1);

    //FileBuffer-->NewImageBuffer
    size2 = CopyFileBufferToNewImageBuffer(pFileBuffer, size1, &pNewImageBuffer);
    if (size2 == 0 || !pFileBuffer)
    {
        printf("FileBuffer-->NewImageBuffer失败\r\n");
        free(pFileBuffer);
        return;
    }
    printf("sizeOfFile - Final: %#X \r\n", size2);
    //NewImageBuffer-->文件
    isOK = MemeryTOFile(pNewImageBuffer, size2, FilePath_Out);
    if (isOK)
    {
        printf("新增节表和节存盘成功\r\n");
        return;
    }

    //释放内存
    free(pFileBuffer);
    free(pNewImageBuffer);
}

//调用函数扩大一个节
VOID ExtendLastSectionsInCodeSec()
{
    //ReadPEFile CopyFileBufferToImageBuffer CopyImageBufferToNewImageBuffer

    LPVOID pFileBuffer = NULL;
    LPVOID pImageBuffer = NULL;
    LPVOID pNewImageBuffer = NULL;
    BOOL isOK = FALSE;
    DWORD FileBufferSize = 0;
    DWORD ImageBufferSize = 0;
    DWORD size = 0;

    //File-->FileBuffer
    FileBufferSize = ReadPEFile(FilePath_In, &pFileBuffer);
    if (FileBufferSize == 0 || !pFileBuffer)
    {
        printf("文件-->缓冲区失败\r\n");
        return;
    }
    printf("FileBufferSize - Final: %#X \r\n", FileBufferSize);

    //FileBuffer-->ImageBuffer
    ImageBufferSize = FileBufferToModifyImageBuffer(pFileBuffer, &pImageBuffer);
    if (ImageBufferSize == 0 || !pFileBuffer)
    {
        printf("FileBuffer-->ImageBuffer失败\r\n");
        free(pFileBuffer);
        return;
    }
    printf("ImageBufferSize - Final: %#X \r\n", ImageBufferSize);

    size = CopyImageBufferToNewBuffer(pImageBuffer, &pNewImageBuffer);
    if (size == 0 || !pImageBuffer)
    {
        printf("pImageBuffer-->pNewImageBuffer失败\r\n");
        free(pFileBuffer);
        return;
    }
    //pNewImageBuffer-->文件
    isOK = MemeryTOFile(pNewImageBuffer, size, FilePath_Out);
    if (isOK)
    {
        printf("扩大一个节成功，并存盘\r\n");
        return;
    }

    //释放内存
    free(pFileBuffer);
    free(pImageBuffer);
    free(pNewImageBuffer);
}


//调用函数扩大一个节
VOID ModifySectionsOneInCodeSec()
{
    //ReadPEFile CopyFileBufferToImageBuffer FileBufferToModifyOneImageBuffer MemeryTOFile

    LPVOID pFileBuffer = NULL;
    LPVOID pImageBuffer = NULL;
    LPVOID pNewImageBuffer = NULL;
    BOOL isOK = FALSE;
    DWORD FileBufferSize = 0;
    DWORD ImageBufferSize = 0;
    DWORD size = 0;

    //File-->FileBuffer
    FileBufferSize = ReadPEFile(FilePath_In, &pFileBuffer);
    if (FileBufferSize == 0 || !pFileBuffer)
    {
        printf("文件-->缓冲区失败\r\n");
        return;
    }
    printf("FileBufferSize ---> %#X \r\n", FileBufferSize);

    //FileBuffer-->ImageBuffer
    ImageBufferSize = CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);
    if (ImageBufferSize == 0 || !pFileBuffer)
    {
        printf("FileBuffer-->ImageBuffer失败\r\n");
        free(pFileBuffer);
        return;
    }
    printf("ImageBufferSize ---> %#X \r\n", ImageBufferSize);

    size = ImageBufferMergeSections(pImageBuffer, &pNewImageBuffer);
    if (size == 0 || !pImageBuffer)
    {
        printf("pImageBuffer-->pNewImageBuffer失败\r\n");
        free(pFileBuffer);
        return;
    }
    //pNewImageBuffer-->文件
    isOK = MemeryTOFile(pNewImageBuffer, size, FilePath_Out);
    if (isOK)
    {
        printf("合并节完成，存盘成功\r\n");
        return;
    }

    //释放内存
    free(pFileBuffer);
    free(pImageBuffer);
    free(pNewImageBuffer);
}

VOID RvaAndFoaConversion()
{
    LPVOID pFileBuffer = NULL;
    DWORD FileBufferSize = 0;
    DWORD FoaFinalVaule = 0;
    DWORD RvaFinalVaule = 0;
    size_t pRVA = 1180;
    size_t pFOA = 2279;

    //File-->FileBuffer
    FileBufferSize = ReadPEFile(FilePath_In, &pFileBuffer);
    if (FileBufferSize == 0 || !pFileBuffer)
    {
        printf("文件-->缓冲区失败\r\n");
        return;
    }
    printf("FileBufferSize: %#X \r\n", FileBufferSize);

    FoaFinalVaule = RvaToFileOffset(pFileBuffer, pRVA);
    if (FoaFinalVaule == 0 || !pFileBuffer)
    {
        printf("pFileBuffer-->读取失败\r\n");
        free(pFileBuffer);
        return;
    }
    printf("转换成功 --> FoaFinalVaule 传进来的pRVA值: : %#X %#X\r\n", FoaFinalVaule, pRVA);

    RvaFinalVaule = FoaToImageOffset(pFileBuffer, pFOA);
    if (RvaFinalVaule == 0 || !pFileBuffer)
    {
        printf("pFileBuffer-->读取失败\r\n");
        free(pFileBuffer);
        return;
    }
    printf("转换成功 --> RvaFinalVaule 传进来的pFOA值 : %#X %#X\r\n", RvaFinalVaule, pFOA);


    free(pFileBuffer);
}

// allpelx.cpp : Defines the entry point for the console application.
//


