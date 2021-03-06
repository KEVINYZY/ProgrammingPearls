//
// Created by zjp on 18-12-20.
//

#ifndef PARALLELPROGRAM_TOOLS_H
#define PARALLELPROGRAM_TOOLS_H

#include <string>
/**
 * 创建随机数组
 * @param len 长度
 * @param max 可能达到的最大值
 * @return int*
 */
int* createRandomArray(int len,int max);

/**
 * 生成不重复的随机数列
 * 必须符合max-min+1>=len,如果不符合，最后全部用0填充
 * @param len
 * @param min
 * @param max
 * @return
 */
int* createRandomArray_noRepeat(int len,int min,int max);

/**
 * 生成随机数列，并指定不出现的数字
 * @param len 生成数列长度
 * @param min 最小值
 * @param max 最大值
 * @param unexisted_ints 不出现的数字数组
 * @param ulen unexisted_ints数组的长度
 * @return
 */
int* createRandomArray_set_unexisted(int len,int min,int max,int* unexisted_ints,int ulen);

/**
 * 创建随即数组到文件
 * @param len
 * @param min
 * @param max
 * @param output_filename
 */
void createRandomArrayToFile(int len,int min,int max,std::string output_filename);

/**
 * 创建不重复的随机数列到文件
 * @param len
 * @param min
 * @param max
 * @param output_filename
 */
void createRandomArrayToFile_noRepeat(int len,int min,int max,std::string output_filename);

/**
 * 打印数组
 * @param flag 打印标志
 * @param a 数组
 * @param len 数组长度
 */
void printArray(std::string flag,int* a,int len);
/**
 * 判断两个数组是否相同
 * @param a
 * @param b
 * @param n
 * @return
 */
bool isArrayEqual(int *a,int *b,int n);

/**
 * qsort函数调用的比较函数
 * @param a
 * @param b
 * @return
 */
int cmp(const void* a,const void* b);

/**
 * 复制数组
 * @param dest
 * @param sour
 * @param num
 */
void copyArray(int *dest,int *sour,int num);

/**
 * 以2为底的num的对数
 * @param num
 * @return
 */
int log2(int num);

/**
 * 求2的n次幂
 * @param n
 * @return
 */
int exp2(int n);

/**
 * 交换两个数
 * @param a
 * @param b
 */
void swap(int* a,int* b);

/**
 * 从文件中读取数据到数组
 * @param f 文件路径
 * @param a 数组指针
 * @param n 想要读取的数据个数
 * @return 实际读取的数据个数
 */
int readData(FILE* f,int* a,int n);

/**
 * 将数组中的数据写出到文件
 * @param f 输出文件路径
 * @param a 数据数组
 * @param n 输出数据个数
 */
void writeData(FILE* f,int* a,int n);

#endif //PARALLELPROGRAM_TOOLS_H
