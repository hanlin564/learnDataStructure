#include <stdio.h>
#include <malloc.h>//������malloc
#include <stdlib.h>//������exit()

/*
*������һ����������,���ֽ���struct Array
*���������ͺ���������Ա
*�ֱ���pBase,len,cnt
*/
struct Array
{
	int * pBase;//�洢�����һ��Ԫ�صĵ�ַ
	int len;//�����������ɵ����Ԫ�صĸ���
	int cnt;//��ǰ������ЧԪ�صĸ���
	//int increment;//�Զ���������
};

void init_arr(struct Array *pArr, int length);
bool append_arr(struct Array *pArr, int val);
bool insert_arr(struct Array *pArr, int pos, int val);//pos��ֵ��1��ʼ
/*
���ݽṹ���ַ,ɾ��Ԫ�ص�λ��,�����һ��int��ָ��
����int��ָ���Ŀ��:�ڲ��ı亯����������bool��ǰ���µõ�ɾ��Ԫ�ص�ֵ
�ڵ���֮ǰ������һ����val,�Ѹñ�����ָ�봫�ݸ�����
���ں����õ���val�ĵ�ַ,��ͨ����ַ�������޸�val
�ѱ�ɾԪ��ֵ���� *pVal�ʹﵽĿ��
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
	//printf("�������Ϊ%d\n", get(&arr, 6));
	//show_arr(&arr);
	//if (delete_arr(&arr, 1, &val))
	//{
	//	printf("ɾ���ɹ�\n");
	//	printf("��ɾ����Ԫ����%d\n", val);
	//}
	//else
	//	printf("ɾ��ʧ��\n");
	//show_arr(&arr);

	return 0;
}

void init_arr(Array *pArr, int length) {
	/*
	*sizeof(int)����:������������int��
	*(int *)����:��������ڴ�ǿת��Ϊ�ڴ��׵�ַ,�����ָ��pBase��
	*pBase����:ָ�������׵�ַ��ָ��
	*/
	pArr->pBase = (int *)malloc(sizeof(int) * length);
	if (pArr->pBase == NULL)
	{
		printf("��̬�ڴ����ʧ��\n");
		exit(-1);//��ֹ��������
	}
	else
	{
		/*
		*��ʼ�����������������ݽṹ��Array���׵�ַ����������ĳ���
		*�ṹ�����治�������Ԫ��
		*�ṹ���д��������Ԫ�صĵ�ַ(pBase)��length(���Ԫ�ظ���)��cnt(��ЧԪ�ظ���)
		*length�����������ڴ�δʹ�õ�Ԫ��
		*cntֻ������ֵ�˵�Ԫ��
		*/
		pArr->len = length;
		pArr->cnt = 0;
	}
	return;
}

bool append_arr(Array * pArr, int val)
{
	//��������ʱ����false
	if (is_full(pArr))
		return false;
	else
	{
		//�������һ����ЧԪ��ΪpBase[cnt-1],�ʰ�val����pBase[cnt]
		pArr->pBase[pArr->cnt] = val;
		//������ЧԪ�ظ�������
		pArr->cnt++;
		return true;
	}
}

bool insert_arr(Array * pArr, int pos, int val)
{
	//������ʱ����false
	if (is_full(pArr))	return false;
	//��posС��1�����cnt+1ʱ����false
	//Ϊ����cnt+1������cnt:�������Ԫ��ΪpBase[cnt-1],��ĩβ����һԪ���Ǻ����
	//����ĩԪ�غ��һ��Ԫ������ǲ������
	if (pos<1 || pos>pArr->cnt + 1)	return false;
	//cnt-1����:ĩԪ���±�
	//pos-1:����λ���±�
	//˳��:�Ӻ���ǰ
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
	//Ϊ����cnt������cnt+1:ֻ��ɾ��ĩԪ�ض�����ɾ��ĩԪ�غ����ЧԪ��
	if (pos<1 || pos>pArr->cnt)	return false;
	*pVal = pArr->pBase[pos - 1];
	//pos:ɾ��Ԫ�ص�λ��
	//cnt:ĩԪ�ص�λ�� i<cnt˵��i���ᵽ��cnt-1 ��ĩԪ���±�
	//˳��:��ǰ����
	for (int i = pos; i < pArr->cnt; i++)
	{
		pArr->pBase[i - 1] = pArr->pBase[i];
	}
	pArr->cnt--;
	return true;
}

int get(Array * pArr, int pos)
{
	//���α�i����pos-1ʱ,����pBase[i]
	for (int i = 0; i < pos; i++)
	{
		if (i == pos - 1)	return pArr->pBase[i];
	}
}

bool is_empty(Array *pArr)
{
	//����ЧԪ��Ϊ0ʱ����Ϊ��
	if (pArr->cnt == 0)
		return true;
	else
		return false;
}

bool is_full(Array *pArr)
{
	//����ЧԪ�غ����Ԫ�ظ������ʱ,����Ϊ��
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
		printf("����Ϊ��\n");
	else
	{
		//��������
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
