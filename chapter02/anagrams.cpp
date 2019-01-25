//
// Created by zjp on 19-1-25.
//
/**
 * 变位词
 *
 * 问题描述：
 * 给定一个英语字典，找出其中所有的变位词集合。
 * 例如，“pots“，”stop“，”tops“，
 * 因为每一个单词都可以通过改变其它单词中字母的排序来得到
 *
 * 解决思路：
 * 基于排序的标识
 * 将每个单词中的字母按照字母表顺序排列，如“deposit”的标识就是“deiopst”
 * （标识的方法有很多种，也可用字母+出现次数，如mississippi的标识为i4m1p2s4）
 * （Soundex标识方法：                                              ）
 * 然后将所有单词按照其标识的顺序排序
 *
 * 整个程序由三部分组成：
 * sign：计算标识
 * sort：按照表示排序单词
 * squash：将具有相同表示的单词在同一行中打印出来
 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Tools.h"

#define MAX_WORD_NUM 100  //单词数量最大值
#define MAX_WORD_LENGTH 100

typedef struct{
    char word[MAX_WORD_LENGTH];  //单词
    char sign[MAX_WORD_LENGTH];  //标识
}Word_sign;

using namespace std;

int char_comp(const void* x,const void* y){
    return *((char*)x) - *((char*)y);
}
int signsort_comp(const void* x,const void* y){
    return strcmp(((Word_sign*)x)->sign,(((Word_sign*)y)->sign));
}
/**
 * 计算标识
 * @param word_signs
 * @param wordnum
 */
void sign(Word_sign* word_signs,int wordnum){
    for(int i=0;i<wordnum;i++){
        strcpy(word_signs[i].sign,word_signs[i].word);
        qsort(word_signs[i].sign,strlen(word_signs[i].sign),sizeof(char),char_comp);
        //cout << word_signs[i].sign << " " << word_signs[i].word << endl;
    }
}
/**
 * 按标识排序
 * @param word_signs
 * @param num
 */
void sort(Word_sign* word_signs,int num){
    qsort(word_signs,num, sizeof(Word_sign),signsort_comp);
}
/**
 * 同一标识按同一行打印
 * @param word_sign
 * @param num
 */
void squash(Word_sign* word_signs,int num){
    for(int i=0;i<num;i++){
        if(i>0&&strcmp(word_signs[i].sign,word_signs[i-1].sign)!=0)
            cout << endl;
        cout << word_signs[i].word << " ";
    }
}
void printWords(Word_sign* word_signs,int num){
    for(int i=0;i<num;i++){
        cout << word_signs[i].sign << " " << word_signs[i].word << endl;
    }
}
int main() {
    int num = 6;
    Word_sign *word_signs = new Word_sign[6];
    char *word[] = {"pans", "pots", "opt", "snap", "stop", "tops"};
    for (int i = 0; i < num; i++)
        strcpy(word_signs[i].word, word[i]);
    sign(word_signs, num);
    sort(word_signs, num);
    cout << "---------------" << endl;
    cout << "after sort:" << endl;
    printWords(word_signs, num);
    cout << "---------------" << endl;
    cout << "after squash:" << endl;
    squash(word_signs,num);

    return 0;
}


