#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAXNUMLEN 100000

char *sub0(char *valor) {
	//去除开头多余的0;
	int i;

	for(i=0;*(valor+i)=='0';i++);

	return (valor + i);
}

char *multiEach(char n1, char n2, char n3) {
	static char res[2];
	int ir;
	// 一位相乘并与之前的进位求和
	ir = ((n1 - '0') * (n2 - '0')) + (n3 - '0');
	// 进位
	if(ir > 9) {
		res[1] = (ir % 10) + '0';
		res[0] = (ir / 10) + '0';
	}else{
		res[1] = ir + '0';
		res[0] = '0';
	}
	return res;
}

char *addEach(char n1, char n2, char n3) {
	static char res[2];
	int ir;
	// 一位相加与之前的进位求和
	ir = (n1 - '0') + (n2 - '0') + (n3 - '0');
	// 进位
	if(ir > 9) {
		res[1] = (ir % 10) + '0';
		res[0] = (ir / 10) + '0';
	}else{
		res[1] = ir + '0';
		res[0] = '0';
	}
	return res;
}

char *add(char *num1, char *num2) {
	int totalLenMax,indexres,indexN1,indexN2;
	int lenNum1 = strlen(num1);
	int lenNum2 = strlen(num2);
	char *add, *addtmp;
	// 申请存储运算结果的空间
	if(lenNum1 > lenNum2)
		totalLenMax = lenNum1+2;
	else
		totalLenMax = lenNum2+2;
	add = (char *) malloc((totalLenMax) * sizeof(char));
	memset(add,'0',(totalLenMax) * sizeof(char));
	*(add+totalLenMax-1) = '\0';
	indexres = totalLenMax-2;
	indexN1 = lenNum1 -1;
	indexN2 = lenNum2 -1;
	// 进位相加
	for(;indexres >= 0;indexres--,indexN1--,indexN2--) {
		if(indexN1 >= 0 && indexN2 >= 0) {
			addtmp = addEach(*(num1+indexN1),*(num2+indexN2),*(add+indexres));
			*(add+indexres) = addtmp[1];
			*(add+indexres-1) = addtmp[0];
		}else{
			if(indexN1 < 0 && indexN2 >=0) {
				addtmp = addEach('0',*(num2+indexN2),*(add+indexres));
				*(add+indexres) = addtmp[1];
				*(add+indexres-1) = addtmp[0];
			}else{
				if(indexN2 < 0 && indexN1 >=0) {
					addtmp = addEach('0',*(num1+indexN1),*(add+indexres));
					*(add+indexres) = addtmp[1];
					*(add+indexres-1) = addtmp[0];
				}
			}
		}
	}
	return add;
}

int multiplication(int lenNum1,int lenNum2,char *num1,char *num2,int num1DecimalMark,int num2DecimalMark,char **result){
	int indexNum2,indexNum1,indexres;
	int totalLen = lenNum1 + lenNum2;
	int length = totalLen;
    int DecimalMark = (num1DecimalMark==0 ? 0 : (lenNum1 - num1DecimalMark)) + (num2DecimalMark==0 ? 0 : (lenNum2 - num2DecimalMark));
	char *res, *doubleNum, *tmp, *p;

    // 为结果申请存储空间
	res = malloc((totalLen+1) * sizeof(char));
	memset(res,'0',(totalLen+1));
	*(res+totalLen) = '\0';

    // 为临时空间申请存储空间
	tmp = malloc((totalLen+1) * sizeof(char));
	memset(tmp,'0',(totalLen+1));
	*(tmp+totalLen) = '\0';

    // 遍历两个数使num1的每一位与num2的每一位相乘
	for(indexNum2=lenNum2-1;indexNum2>=0;indexNum2--) {
		for(indexNum1=lenNum1-1,indexres=totalLen-1;indexNum1>=0;indexNum1--,indexres--) {
			doubleNum = multiEach(*(num1+indexNum1),*(num2+indexNum2),*(tmp+indexres));
			*(tmp+indexres) = doubleNum[1];
			*(tmp+indexres-1) = doubleNum[0];
		}
		p = res;
        // 将tmp加到结果上
		res = add(tmp,res);
        // free掉之前的res
		free(p);
        // 将tmp置零并计算下一位
		memset(tmp,'0',(length+1));
		*(tmp+length) = '\0';
		totalLen--;
	}
	// free掉申请的空间
	free(tmp);
    free(num1);
    free(num2);
    *result = sub0(res);
    return DecimalMark;
}

void main() {
	char *result,*num1,*num2;
    char c;
    int lenth = 0,lenNum1,lenNum2;
    // 小数点位置
    int num1DecimalMark = 0;
    int num2DecimalMark = 0;
    int DecimalMark = 0;

    // 申请存储输入数字的内存
	num1 = malloc(MAXNUMLEN * sizeof(char));
	num2 = malloc(MAXNUMLEN * sizeof(char));

	if(num1 == NULL || num2 == NULL) {
		printf("Memory Insuficiente\n");
        system("pause");
		exit(0);
	}

    // 输入第一个数
	printf("\nEnter Number1: ");
    while ((c = getchar()) != '\n') {
        if (c == '.') {
            // 输入了两个小数点
            if (num1DecimalMark != 0) {
                printf("Input Error!\n");
                system("pause");
		        exit(0);
            } else {
                num1DecimalMark = lenth;
            }
        } 
        else if (c-'0'<0 || c-'0'>10) {
			printf("Input Error!\n");
            system("pause");
		    exit(0);
		}
        else {
            num1[lenth] = c;
            lenth ++;
        }
    }
    num1[lenth] = '\0';
    lenNum1 = lenth;

	// 输入第二个数
    lenth = 0;
	printf("\nEnter Number2: ");
    while ((c = getchar()) != '\n') {
        if (c == '.') {
            // 输入了两个小数点
            if (num2DecimalMark != 0 || lenth == 0) {
                printf("Input Error!\n");
                system("pause");
		        exit(0);
            } else {
                num2DecimalMark = lenth;
            }
        } 
		else if (c-'0'<0 || c-'0'>10) {
			printf("Input Error!\n");
            system("pause");
		    exit(0);
		}
		else {
            num2[lenth] = c;
            lenth ++;
        }
    }
    num2[lenth] = '\0';
    lenNum2 = lenth;

    // 重新调整分配内存大小
	num1 = realloc(num1,(strlen(num1)+1) * sizeof(char)); 
	num2 = realloc(num2,(strlen(num2)+1) * sizeof(char));

    // 进行计算
	DecimalMark = multiplication(lenNum1,lenNum2,num1,num2,num1DecimalMark,num2DecimalMark,&result);

    // 输出结果
	printf("\nResult:        ");
    lenth = 0;
    int reslen = strlen(result);
    while (result[lenth] != '\0') {
        // 输出小数点
        if (lenth == reslen - DecimalMark) {
            printf(".");
        }
        // 每行显示200位数字
        if (lenth % 80 == 0 && lenth != 0) {
            printf("\n               ");
        }
        // 输出数字
        printf("%c", result[lenth]);
        lenth ++;
    }
    printf("\n\n");
	system("pause");
}
