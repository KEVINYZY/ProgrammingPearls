//
// Created by zjp on 19-1-25.
//
/**
 * 旋转向量
 *
 * 问题描述：
 * 将一个n元一维向量向左旋转i个位置。
 * 例如，当n=8，i=3时，向量abcdefgh旋转为defghabc。
 * 简单的代码使用一个n元的向量在n步内完成该工作。
 * 你能否使用数十个额外字节的储存空间，在正比于n的时间内完成向量的旋转？
 *
 * 三种方法：
 * 杂技算法
 * 交换算法
 * 反转算法
 */


#include <iostream>
#include "Tools.h"
#include "catch.h"

#define ACROBATICED   //杂技算法
#define EXCHANGEED   //交换算法
#define REVERSE   //反转算法

using namespace std;

/**
 * 求a和b的最大共约数
 * 辗转相除法
 * gcd(a,b) = gcd(b,a mod b)。
 * @param a
 * @param b
 * @return
 */
int gcd(int a,int b){
    int temp;
    while(b>0){
        temp = a%b;
        a = b;
        b = temp;
    }
    return a;
}
/**
 * 方法一：杂技算法
 * 思路：
 * 移动x[0]到t，然后移动x[i]到x[0],x[2i]到x[i]......直到返回取原x[0]中的值
 * 下一次从x[1]开始移动，直到所有元素都已经移动为止.
 * 设g为i和N的最大公约数，则总共需要循环移动g次
 *
 * @param data
 * @param len
 */
template <typename T>
void rotate_acrobatic(T* data,int len,int i){
    int step = gcd(len,i);
    for(int j=0;j<step;j++){
        T temp = data[j];
        int current = j;
        while(1){
            int next = (current+i)%len;
            if(next==j)
                break;
            data[current] = data[next];
            current = next;
        }
        data[current] = temp;
    }
}

/**
 * 杂技算法
 */
#ifdef ACROBATIC
TEST_CASE("rotate_acrobatic"){
    //i和n不互质
    SECTION("1") {
        int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        int len = 9, i = 3;
        printArray("before rotate", data, len);
        rotate_acrobatic(data, len, i);
        printArray("after rotate", data, len);
    }
    //i和n互质
    SECTION("2") {
        int data[] = {0, 1, 2, 3, 4, 5, 6, 7};
        int len = 8, i = 3;
        printArray("before rotate", data, len);
        rotate_acrobatic(data, len, i);
        printArray("after rotate", data, len);
    }
}

#endif


/**
 * 方法二：交换算法
 * 思路：
 * 旋转向量x其实就是交换向量ab的两段，得到向量ba
 * a代表前i个元素
 * 假设a比b短，将b分为bl和br两段，使得br和a具有相同的长度。
 * 交换a和br，得到brbla，问题转化成交换b的两部分，与原来问题具有相同的形式，可以递归解决。
 */

//swap a[i...i+m-1]  a[j...j+m-1]
 template <typename T>
 void swap(T* a,int i,int j,int m){
     for(int k=0;k<m;k++){
         int temp = a[i+k];
         a[i+k] = a[j+k];
         a[j+k] = temp;
     }
 }
/**
 * 交换算法
 * @tparam T
 * @param a
 * @param len
 * @param pos
 */
 template <typename T>
 void rotate_exchange(T* a,int len,int pos){
     if(pos==0||pos==len)
         return;
     int i,j;
     i=pos;
     j=len-pos;
     while(i!=j){
         if(i<j){
             swap(a,pos-i,pos+j-i,i);
             j-=i;
         }else{
             swap(a,pos-i,pos,j);
             i-=j;
         }
     }
     swap(a,pos-i,pos,i);  ///??????
 }

#ifdef EXCHANGE
TEST_CASE("rotate exchange"){
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int len = 8, i = 3;
    printArray("before rotate", data, len);
    rotate_exchange(data, len, i);
    printArray("after rotate", data, len);
 }
#endif


/**
 * 方法三：反转算法
 * 通过3步将ab转化成ba
 * 1、将a反转得到a`
 * 2、将b反转得到b`
 * 3、将a`b`反转得到ba
 */

/**
 * 将a[l...r]反转成a[r...l]
 * @tparam T
 * @param a
 * @param l
 * @param r
 */
template <typename T>
void reverse(T* a,int l,int r){
    int mid = (l+r)/2;
    while(l<=mid){
        int temp = a[l];
        a[l] = a[r];
        a[r] = temp;
        l++;
        r--;
    }
}
/**
 * 反转算法
 * @tparam T
 * @param a
 * @param len
 * @param pos
 */
template <typename T>
void rotate_reverse(T* a,int len,int pos){
    reverse(a,0,pos-1);
    reverse(a,pos,len-1);
    reverse(a,0,len-1);
}

/**
 * 反转算法
 */
#ifdef REVERSE
TEST_CASE("rotate reverse"){
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int len = 8, i = 3;
    printArray("before rotate", data, len);
    rotate_reverse(data, len, i);
    printArray("after rotate", data, len);
}
#endif