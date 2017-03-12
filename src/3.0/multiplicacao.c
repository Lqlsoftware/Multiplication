#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define MAXNUMLEN 100000

char *normalizar(char *valor) {
	//cortando zeros a esquerda;
	int i;

	for(i=0;*(valor+i)=='0';i++);

	return (valor + i);
}


char *multiEach(char n1, char n2, char n3) {
	static char saida[2];
	int ir;

	ir = ((n1 - '0') * (n2 - '0')) + (n3 - '0');

	if(ir > 9) {
		saida[1] = (ir % 10) + '0';
		saida[0] = (ir / 10) + '0';
	}else{
		saida[1] = ir + '0';
		saida[0] = '0';
	}
	//saida é um array de dois elementos, ex: valor = 12, saida = {'1','2'}
	return saida;
}

char *somaEach(char n1, char n2, char n3) {
	static char saida[2];
	int ir;

	ir = (n1 - '0') + (n2 - '0') + (n3 - '0');

	if(ir > 9) {
		saida[1] = (ir % 10) + '0';
		saida[0] = (ir / 10) + '0';
	}else{
		saida[1] = ir + '0';
		saida[0] = '0';
	}
	//saida é um array de dois elementos, ex: valor = 12, saida = {'1','2'}
	return saida;
}

char *somai(char *num1, char *num2) {
	int tamanhoMaximo,indexSaida,indexN1,indexN2;
	int lenNum1 = strlen(num1);
	int lenNum2 = strlen(num2);
	char *soma, *somapedaco;

	if(lenNum1 > lenNum2) {
		tamanhoMaximo = lenNum1+2;
	}else{
		tamanhoMaximo = lenNum2+2;
	}
	soma  = (char *) malloc((tamanhoMaximo) * sizeof(char));
	memset(soma,'0',(tamanhoMaximo) * sizeof(char));
	*(soma+tamanhoMaximo-1) = '\0';

	indexSaida = tamanhoMaximo-2;
	indexN1 = lenNum1 -1;
	indexN2 = lenNum2 -1;

	for(;indexSaida >= 0;indexSaida--,indexN1--,indexN2--) {
		if(indexN1 >= 0 && indexN2 >= 0) {
			somapedaco = somaEach(*(num1+indexN1),*(num2+indexN2),*(soma+indexSaida));
			*(soma+indexSaida) = somapedaco[1];
			*(soma+indexSaida-1) = somapedaco[0];
		}else{
			if(indexN1 < 0 && indexN2 >=0) {
				somapedaco = somaEach('0',*(num2+indexN2),*(soma+indexSaida));
				*(soma+indexSaida) = somapedaco[1];
				*(soma+indexSaida-1) = somapedaco[0];
			}else{
				if(indexN2 < 0 && indexN1 >=0) {
					somapedaco = somaEach('0',*(num1+indexN1),*(soma+indexSaida));
					*(soma+indexSaida) = somapedaco[1];
					*(soma+indexSaida-1) = somapedaco[0];
				}
			}
		}
	}
	return soma;
}

char *multiSmart(char *num1, char *num2){
	int lenNum1 = strlen(num1);
	int lenNum2 = strlen(num2);
	int indexNum2,indexNum1,indexSaida;
	int tamanho = lenNum1 + lenNum2;
	int tamTmp = tamanho;
	char *saida, *pedaco, *tmp, *somaAnterior;

	saida = malloc((tamanho+1) * sizeof(char));
	memset(saida,'0',(tamanho+1));
	*(saida+tamanho) = '\0';

	tmp = malloc((tamanho+1) * sizeof(char));
	memset(tmp,'0',(tamanho+1));
	*(tmp+tamanho) = '\0';

	for(indexNum2=lenNum2-1;indexNum2>=0;indexNum2--) {
		for(indexNum1=lenNum1-1,indexSaida=tamanho-1;indexNum1>=0;indexNum1--,indexSaida--) {
			pedaco = multiEach(*(num1+indexNum1),*(num2+indexNum2),*(tmp+indexSaida));
			*(tmp+indexSaida) = pedaco[1];
			*(tmp+indexSaida-1) = pedaco[0];
		}
		somaAnterior = saida;
		saida = somai(tmp,saida);
		free(somaAnterior);
		memset(tmp,'0',(tamTmp+1));
		*(tmp+tamTmp) = '\0';
		tamanho--;
	}
	free(tmp);free(num1);free(num2);
	return normalizar(saida);
}

char *multi(char *num1, char *num2) {
	char *saida;
	int j,i=1,valor = 0;
	int lenNum2 = strlen(num2);

	for(lenNum2 = lenNum2 - 1; lenNum2 >= 0; lenNum2--, i = i * 10)
		valor = valor + i * (*(num2+lenNum2) - '0');

	saida = num1;
	for(j=2;j<=valor;j++)
		saida = somai(saida,num1);

	return saida;
}

void main() {
	char *result,*num1,*num2,c;
    int lenth = 0;
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
	printf("Enter Number1: ");
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
        } else {
            num1[lenth] = c;
            lenth ++;
        }
    }
    num1[lenth] = '\0';
    num1DecimalMark = num1DecimalMark==0 ? 0 : (lenth - num1DecimalMark);

	// 输入第二个数
    lenth = 0;
	printf("Enter Number2: ");
    while ((c = getchar()) != '\n') {
        if (c == '.') {
            // 输入了两个小数点
            if (num2DecimalMark != 0) {
                printf("Input Error!\n");
                system("pause");
		        exit(0);
            } else {
                num2DecimalMark = lenth;
            }
        } else {
            num2[lenth] = c;
            lenth ++;
        }
    }
    num2[lenth] = '\0';
    num2DecimalMark = num2DecimalMark==0 ? 0 : (lenth - num2DecimalMark);

    // 记录小数点位置
    DecimalMark = num1DecimalMark + num2DecimalMark;

    // 重新调整分配内存大小
	num1 = realloc(num1,(strlen(num1)+1) * sizeof(char)); 
	num2 = realloc(num2,(strlen(num2)+1) * sizeof(char));

    // 进行计算
	result = multiSmart(num1,num2);

    // 输出结果
	printf("\nResult: \n");
    lenth = 0;
    int reslen = strlen(result);
    while (result[lenth] != '\0') {
        // 输出小数点
        if (lenth == reslen - DecimalMark) {
            printf(".");
        }
        // 每行显示200位数字
        if (lenth % 120 == 0 && lenth != 0) {
            printf("\n");
        }
        // 输出数字
        printf("%c", result[lenth]);
        lenth ++;
    }
    printf("\n");

	system("pause");
}
