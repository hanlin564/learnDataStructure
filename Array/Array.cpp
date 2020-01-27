#include <stdio.h>
#include <malloc.h>//包含了malloc
#include <stdlib.h>//包含了exit()

/*
*定义了一个数据类型,名字叫做struct Array
*该数据类型含有三个成员
*分别是pBase,len,cnt
*/
struct Array
{
	int * pBase;//存储数组第一个元素的地址
	int len;//数组所能容纳的最大元素的个数
	int cnt;//当前数组有效元素的个数
	//int increment;//自动增长因子
};

void init_arr(struct Array *pArr, int length);
bool append_arr(struct Array *pArr, int val);
bool insert_arr(struct Array *pArr, int pos, int val);//pos的值从1开始
/*
传递结构体地址,删除元素的位置,最后传入一个int型指针
传入int型指针的目的:在不改变函数返回类型bool的前提下得到删除元素的值
在调用之前先申明一变量val,把该变量的指针传递给函数
由于函数得到了val的地址,可通过地址访问与修改val
把被删元素值赋给 *pVal就达到目的
*/
bool delete_arr(struct Array *pArr, int pos, int *pVal);
int get(struct Array *pArr, int pos);
bool is_empty(struct Array *pArr);
bool is_full(struct Array *pArr);
void sort_arr(struct Array *pArr);
void show_arr(struct Array *pArr);
void inversion_arr(struct Array *pArr);


int main() {
	struct Array arr;
	int val;
	init_arr(&arr, 6);
	append_arr(&arr, 3);
	append_arr(&arr, 2);
	append_arr(&arr, 1);
	show_arr(&arr);

	//append_arr(&arr, 4);
	//append_arr(&arr, 5);
	inversion_arr(&arr);
	show_arr(&arr);
	//inversion_arr(&arr);
	//show_arr(&arr);

	//append_arr(&arr, 6);
	//append_arr(&arr, 7);
	//append_arr(&arr, 8);
	//insert_arr(&arr, 6, 99);
	//printf("插入的数为%d\n", get(&arr, 6));
	//show_arr(&arr);
	//if (delete_arr(&arr, 1, &val))
	//{
	//	printf("删除成功\n");
	//	printf("您删除的元素是%d\n", val);
	//}
	//else
	//	printf("删除失败\n");
	//show_arr(&arr);

	return 0;
}

void init_arr(Array *pArr, int length) {
	/*
	*sizeof(int)含义:建立的数组存放int型
	*(int *)含义:把申请的内存强转换为内存首地址,存放在指针pBase中
	*pBase含义:指向数组首地址的指针
	*/
	pArr->pBase = (int *)malloc(sizeof(int) * length);
	if (pArr->pBase == NULL)
	{
		printf("动态内存分配失败\n");
		exit(-1);//终止整个程序
	}
	else
	{
		/*
		*初始化数组首先向函数传递结构体Array的首地址和所需数组的长度
		*结构体里面不存放数组元素
		*结构体中存放数组首元素的地址(pBase)、length(最大元素个数)、cnt(有效元素个数)
		*length包含申请了内存未使用的元素
		*cnt只包含赋值了的元素
		*/
		pArr->len = length;
		pArr->cnt = 0;
	}
	return;
}

bool append_arr(Array * pArr, int val)
{
	//当数组满时返回false
	if (is_full(pArr))
		return false;
	else
	{
		//数组最后一个有效元素为pBase[cnt-1],故把val赋给pBase[cnt]
		pArr->pBase[pArr->cnt] = val;
		//数组有效元素个数增加
		pArr->cnt++;
		return true;
	}
}

bool insert_arr(Array * pArr, int pos, int val)
{
	//数组满时返回false
	if (is_full(pArr))	return false;
	//当pos小于1或大于cnt+1时返回false
	//为何是cnt+1而不是cnt:数组最后元素为pBase[cnt-1],在末尾增加一元素是合理的
	//而在末元素后空一个元素添加是不合理的
	if (pos<1 || pos>pArr->cnt + 1)	return false;
	//cnt-1含义:末元素下标
	//pos-1:插入位置下标
	//顺序:从后往前
	for (int i = pArr->cnt - 1; i >= pos - 1; i--)
	{
		pArr->pBase[i + 1] = pArr->pBase[i];
	}
	pArr->pBase[pos - 1] = val;
	pArr->cnt++;
	return true;
}

bool delete_arr(Array * pArr, int pos, int * pVal)
{
	if (is_empty(pArr))	return false;
	//为何是cnt而不是cnt+1:只能删除末元素而不能删除末元素后的无效元素
	if (pos<1 || pos>pArr->cnt)	return false;
	*pVal = pArr->pBase[pos - 1];
	//pos:删除元素的位置
	//cnt:末元素的位置 i<cnt说明i最后会到达cnt-1 即末元素下标
	//顺序:从前往后
	for (int i = pos; i < pArr->cnt; i++)
	{
		pArr->pBase[i - 1] = pArr->pBase[i];
	}
	pArr->cnt--;
	return true;
}

int get(Array * pArr, int pos)
{
	//当游标i等于pos-1时,返回pBase[i]
	for (int i = 0; i < pos; i++)
	{
		if (i == pos - 1)	return pArr->pBase[i];
	}
}

bool is_empty(Array *pArr)
{
	//当有效元素为0时数组为空
	if (pArr->cnt == 0)
		return true;
	else
		return false;
}

bool is_full(Array *pArr)
{
	//当有效元素和最大元素个数相等时,数组为满
	if (pArr->cnt == pArr->len)
		return true;
	else
		return false;
}

void sort_arr(Array * pArr)
{
	int i, j, temp;
	for (i = 0; i < pArr->cnt; i++)
	{
		for (j = i + 1; j < pArr->cnt; j++)
		{
			if (pArr->pBase[i] > pArr->pBase[j])
			{
				temp = pArr->pBase[i];
				pArr->pBase[i] = pArr->pBase[j];
				pArr->pBase[j] = temp;
			}
		}
	}
}

void show_arr(Array *pArr) {
	if (is_empty(pArr))
		printf("数组为空\n");
	else
	{
		//遍历数组
		for (int i = 0; i < pArr->cnt; i++)
		{
			printf("%d ", pArr->pBase[i]);
		}
		printf("\n");
	}
}

void inversion_arr(Array * pArr)
{
	int temp;
	for (int i = 0; i < pArr->cnt / 2; i++)
	{
		temp = pArr->pBase[i];
		pArr->pBase[i] = pArr->pBase[pArr->cnt - 1 - i];
		pArr->pBase[pArr->cnt - 1 - i] = temp;
	}
}
