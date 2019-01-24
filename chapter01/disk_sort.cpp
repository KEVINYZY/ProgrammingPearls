//
// Created by zjp on 19-1-23.
//
/**
 * 磁盘文件排序
 *
 * 问题描述：
 *      一个最多包含n个正整数的文件，每个数都小于n，其中n=10^7。
 *      如果在输入文件中有任何整数重复出现就是致命错误。
 *      没有其它数据与该整数相关联。
 * 输出：
 *      按升序排列的输入整数列表
 * 约束：
 *      最多有大约1M的内存空间可用，有充足的磁盘空间可用。运行时间最多几分钟，运行时间为10秒就不需要进一步优化了。
 *
 * 时间对比(总时间)：
 * qsort     set<int>    bit      bitset    严格限制1M(两趟排序)
 * 3.98841s  28.2615s  1.97697s  2.35041s     4.26004s
 */
#include "catch.h"
#include "Tools.h"
#include <string>
#include <time.h>

#define N 10000000

#define CREATE_DATAED
#define DIST_SORT_QSORTED
#define DIST_SORT_CPP_SETED
#define DIST_SORT_BITED
#define DIST_SORT_CPP_BITSETED
#define DIST_SORT_1M

using namespace std;

/**
 * 生成数据
 */
#ifdef CREATE_DATA
TEST_CASE("create data"){
    SECTION(""){
        string unsortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/unsorted_data.txt";
        int len = 10000000; //10^7
        int min = 0,max = len;
        createRandomArrayToFile_noRepeat(len,min,max,unsortedFile);
        int* a = new int[len];
        FILE* f = fopen(unsortedFile.data(),"r");
        readData(f,a,len);
        fclose(f);
//        string sortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/sorted_data.txt";
//        FILE* fout = fopen(sortedFile.data(),"w");
//        writeData(fout,a,len);
//        fclose(fout);
    }
}

#endif


/**
 * 使用stdlib库中的qsort函数进行排序
 * 使用时间：
 * Sort time:1.91137s
 * Total ime:3.98841s
 */
#ifdef DIST_SORTED_QSORT
TEST_CASE("qsort"){
    SECTION(""){
#include <stdlib.h>
        clock_t start_time,end_time; //总时间，包括读写文件
        clock_t sort_start_time,sort_end_time;  //排序时间
        start_time = clock();
        string unsortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/unsorted_data.txt";
        string sortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/sorted_data.txt";
        int len = 10000000;
        //int min = 0,max = len;
        int* data = new int[len];
        FILE* fin = fopen(unsortedFile.data(),"r");
        FILE* fout = fopen(sortedFile.data(),"w");
        readData(fin,data,len);

        sort_start_time = clock();
        qsort(data,len,sizeof(int),cmp);
        sort_end_time = clock();

        writeData(fout,data,len);
        fclose(fin);
        fclose(fout);
        end_time = clock();
        cout << "Sort time:" << (double)(sort_end_time-sort_start_time)/CLOCKS_PER_SEC << "s" << endl;
        cout << "Total ime:" << (double)(end_time-start_time)/CLOCKS_PER_SEC << "s" << endl;
    }
}

#endif


/**
 * 使用c++的set容器
 * 使用时间：
 * Total time:28.2615s
 */
#ifdef DIST_SORT_CPP_SET

#include <set>
TEST_CASE("set int"){
        SECTION(""){
                set<int> dataSet;
                clock_t start_time,end_time; //总时间，包括读写文件
                start_time = clock();
                string unsortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/unsorted_data.txt";
                string sortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/sorted_data.txt";
                FILE* fin = fopen(unsortedFile.data(),"r");
                FILE* fout = fopen(sortedFile.data(),"w");
                assert(fin);
                assert(fout);
                int temp;
                for(int i=0;i<N&&(fscanf(fin,"%d",&temp)!=EOF);i++){
                        dataSet.insert(temp);
                }
                for(set<int>::iterator i=dataSet.begin();i!=dataSet.end();i++){
                        fprintf(fout,"%d ",*i);
                }
                fclose(fin);
                fclose(fout);
                end_time = clock();
                cout << "Total time:" << (double)(end_time-start_time)/CLOCKS_PER_SEC << "s" << endl;
        }
}
#endif

/**
 * 位图法
 * 使用时间：
 * Total time:1.97697s
 */
#ifdef DIST_SORT_BIT

#define BITS_PER_WORD 32
#define SHIFT 5
#define MASK 0x1F
int bit[1+N/BITS_PER_WORD];
void bit_set(int i){
        bit[i>>SHIFT] |= (1<<(i &MASK));
}
void bit_clr(int i){
        bit[i>>SHIFT] &= ~(1<<(i &MASK));
}
int bit_test(int i){
        return bit[i>>SHIFT] &(1<<(i &MASK));
}
TEST_CASE("bit sort"){
        SECTION(""){
                clock_t start_time,end_time; //总时间，包括读写文件
                start_time = clock();
                string unsortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/unsorted_data.txt";
                string sortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/sorted_data.txt";
                FILE* fin = fopen(unsortedFile.data(),"r");
                FILE* fout = fopen(sortedFile.data(),"w");
                assert(fin);
                assert(fout);

                for(int i=0;i<N;i++)
                        bit_clr(i);
                int temp;
                for(int i=0;i<N&&(fscanf(fin,"%d",&temp)!=EOF);i++)
                        bit_set(i);
                for(int i=0;i<N;i++) {
                        if (bit_test(i)) {
                                fprintf(fout, "%d ", i);
                        }
                }
                fclose(fin);
                fclose(fout);
                end_time = clock();
                cout << "Total time:" << (double)(end_time-start_time)/CLOCKS_PER_SEC << "s" << endl;
        }
}
#endif

/**
 * 使用c++的<bitset>库
 * 使用时间:
 * Total time:2.35041s
 */
#ifdef DIST_SORT_CPP_BITSET

#include <bitset>
TEST_CASE("bitset"){
        SECTION(""){
                bitset<N> bitMap;
                clock_t start_time,end_time; //总时间，包括读写文件
                start_time = clock();
                string unsortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/unsorted_data.txt";
                string sortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/sorted_data.txt";
                FILE* fin = fopen(unsortedFile.data(),"r");
                FILE* fout = fopen(sortedFile.data(),"w");
                assert(fin);
                assert(fout);

                int temp;
                for(int i=0;i<N&&(fscanf(fin,"%d",&temp)!=EOF);i++)
                        bitMap.set(i);
                for(int i=0;i<N;i++){
                        if(bitMap[i]==1)
                                fprintf(fout,"%d ",i);
                }
                fclose(fin);
                fclose(fout);
                end_time = clock();
                cout << "Total time:" << (double)(end_time-start_time)/CLOCKS_PER_SEC << "s" << endl;
        }
}
#endif

/**
 * 严格限制1M空间
 * 使用位图法 N=10^7 ，则需要使用1.25M空间
 * 解决方法：
 * 通过两次排序，第一次读取0～5*10^3-1之间的树，第二次读取5*10^3-1～10^7 之间的数
 *
 * 时间：
 * Total time:4.26004s
 */
#ifdef DIST_SORT_1M

#define BITS_PER_WORD 32
#define SHIFT 5
#define MASK 0x1F
int bit[1+(N/BITS_PER_WORD)/2];
void bit_set(int i){
        bit[i>>SHIFT] |= (1<<(i &MASK));
}
void bit_clr(int i){
        bit[i>>SHIFT] &= ~(1<<(i &MASK));
}
int bit_test(int i){
        return bit[i>>SHIFT] &(1<<(i &MASK));
}
TEST_CASE("bitsort 1M"){
        SECTION(""){
                clock_t start_time,end_time; //总时间，包括读写文件
                start_time = clock();
                string unsortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/unsorted_data.txt";
                string sortedFile = "/home/zjp/Documents/ProgrammingPearls/chapter01/sorted_data.txt";
                FILE* fin = fopen(unsortedFile.data(),"r");
                FILE* fout = fopen(sortedFile.data(),"w");
                assert(fin);
                assert(fout);

                //第一趟排序
                for(int i=0;i<N/2;i++) //N/2
                        bit_clr(i);
                int temp;
                for(int i=0;i<N&&(fscanf(fin,"%d",&temp)!=EOF);i++) {
                        if (i < N / 2)
                                bit_set(i);
                }
                for(int i=0;i<N/2;i++){ //N/2
                        if(bit_test(i))
                                fprintf(fout,"%d ",i);
                }

                //第二趟排序
                //文件指针重新定位到开头
                int result = fseek(fin,0,SEEK_SET);
                assert(!result);

                for(int i=0;i<N/2;i++) //N/2
                        bit_clr(i);
                for(int i=0;i<N&&(fscanf(fin,"%d",&temp)!=EOF);i++) {
                        if (i >= N / 2)
                                bit_set(i-N/2);
                }
                for(int i=0;i<N/2;i++){ //N/2
                        if(bit_test(i))
                                fprintf(fout,"%d ",i+N/2);
                }

                fclose(fin);
                fclose(fout);
                end_time = clock();
                cout << "Total time:" << (double)(end_time-start_time)/CLOCKS_PER_SEC << "s" << endl;
        }
}

#endif