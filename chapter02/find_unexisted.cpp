//
// Created by zjp on 19-1-24.
//
/**
 * 寻找不存在整数
 *
 * 问题描述：
 * 给定一个最多包含40亿个随机排列的32位整数的顺序文件，找出一个不存在文件中的32位整数（在文件中至少缺失这样一个数---为什么？）。
 * 在具有足够内存的情况下，如何解决该问题？如果有几个外部的临时文件可用但是仅有几百字节的内存，又该如何解决该问题？
 *
 * 2^30 = 1073741824 约10亿
 * 2^32 = 4073741824 约40亿，但大于40亿
 * 因此40亿个数内至少有73741824个不存在的数
 *
 * 解决思路：
 * 从表示每个整数的32位的视角来考虑二分搜索。
 * 算法的第一趟（最多读取40亿个输入整数），并把起始位为0的整数写入一个顺序文件，把起始位为1的整数写入另外一个顺序文件。
 * 这两个文件中，有一个文件最多包含20亿个整数，接下来用这个文件用作当前输入文件并重复探测过程，但这次探测的是第二个位。
 * 如果原始文件输入包含n个元素，那么第二趟最多n/2,第三趟最多n/4，...，以此类推。
 * 总运行时间正比于n。
 */
#include <catch.h>
#include <string>

#define FOUR_BILLIONS 4000000000 //40亿

#define CREATE_DATAED
#define FIND_UNEXISTEDED
#define FIND_LOST

using namespace std;

/**
 * 生成随机数列
 * 指定了不出现的数字
 */
#ifdef CREATE_DATA

#include "Tools.h"
TEST_CASE("create data"){
    SECTION(""){
        string randomFile = "/home/zjp/Documents/ProgrammingPearls/chapter02/random_data.txt";
        int min=1,max=10;
        int len=10;
        int unexisted[] = {5};
        int ulen = 1;
        int* randomData = createRandomArray_set_unexisted(len,min,max,unexisted,ulen);
        //printArray("randomData",randomData,len);
        FILE* f = fopen(randomFile.data(),"w");
        writeData(f,randomData,len);
        fclose(f);
    }
}

#endif


/**
 * 生成40亿个整数的文件占用磁盘空间太大
 * 电脑空间不足
 * 没有进行测试
 */
#ifdef FIND_UNEXISTED

#define INTEGER_LEN 32
#define LEN 10

TEST_CASE("find unexisted"){
    SECTION(""){
        string randomFileName = "/home/zjp/Documents/ProgrammingPearls/chapter02/random_data.txt";
        string currFileName = randomFileName;
        int count0 = 0,count1 = 0;
        int n=LEN;
        int result = 0;
        string temp0 = "/home/zjp/Documents/ProgrammingPearls/chapter02/temp";  //不包含文件后缀的临时文件名
        string temp1 = "/home/zjp/Documents/ProgrammingPearls/chapter02/temp";
        for(int index=0;index<INTEGER_LEN;index++){
            count0 = 0;
            count1 = 0;

            temp0 += "0";
            temp1 += "1";

            string tempFileName0 = temp0 + ".txt";
            string tempFileName1 = temp1 + ".txt";

            FILE* currFile = fopen(currFileName.data(),"r");
            FILE* tempFile0 = fopen(tempFileName0.data(),"w");
            FILE* tempFile1 = fopen(tempFileName1.data(),"w");
            assert(currFile);
            assert(tempFile0);
            assert(tempFile1);

            int data;
            while(fscanf(currFile,"%d",&data)!=EOF){
                if((data>>(31-index))==1) {
                    fprintf(tempFile1, "%d ", data);
                    count1++;
                }else {
                    fprintf(tempFile0, "%d ", data);
                    count0++;
                }
            }
            if(count0<n/2) {
                currFileName = tempFileName0;
                temp1 = temp0;
                //缺失值的当前为为0
            }else {
                currFileName = tempFileName1;
                temp0 = temp1;
                result |= (1<<(31-index)); //缺失值的当前为为1
            }

        }
        cout << result << endl;
    }
}
#endif

/**
 * 使用内存做简单测试
 */
#ifdef FIND_LOST

/**
 * https://segmentfault.com/q/1010000000359749
 * 很精妙的算法！！！
 *
 * @param data 待查找数组
 * @param len 待查找数组data[]的长度
 * @param bit 位数
 */
int findLost(int* data,int len,int bit=32){
    int* temp0 = new int[len]; //储存第bit位为0的数
    int* temp1 = new int[len]; //储存第bit位为1的数
    int index0=0,index1=0;  //temp0和temp1数组的索引器
    int result = 0; //结果，缺失值
    while(bit--) {
        index0 = 0,index1 = 0;
        for (int i = 0; i < len; i++) {
            if (data[i] & (1 << bit)) { //若a[i]的第bit位为1
                temp1[index1++] = data[i];
            }else{ //第bit位为0
                temp0[index0++] = data[i];
            }
        }
        if(index1<=index0){ //第bit位为1的数比为0的数少，缺失值肯定在第bit位为1中
            result |= (1<<bit); //缺失值在第bit位为1中，说明确实值的第bit位为1,将该位置1
            int* temp = data; //以第bit位为1的数组作为待查找数组进行下一步查找
            data = temp1;
            temp1 = temp;
            len = index1;
        }else{
            //第bit位位0
            int* temp = data;
            data = temp0;
            temp0 = temp;
            len = index0;
        }
    }
    return result;
}

TEST_CASE("find lost integer"){
    SECTION(""){
        int data[] = {0,1,3,5,4,6,7};
        //当前测试全部数据的第4位开始都为0,设置bit=3,只需要测试前3位
        int result = findLost(data,7,3);
        cout << result << endl;
    }
}
#endif
