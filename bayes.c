#include<stdio.h>
#include <string.h>
#include <math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

float count_col(int train[][192], int label[], int class, int feature, int value, float class_prob[]){
	int i,j;
	float count=0.0,count1=0.0;
	i=0;
	while(i<6670){
		if(label[i]==class){ 
			if(train[i][feature] == value){
				count++;
			}
			count1++;
		}
		i++;
	}
	class_prob[class]=count1/6670.0;
	return count/count1;
	float max = -9999.0;
	float sum;
	int i,j,ind=-1;
	for(i=0;i<10;i++){
		sum=0.0;
		for(j=0;j<192;j++){
			sum = sum + log(pro[i][j][test[j]]);
		}
		sum = sum + log(class_prob[i]);
		if(sum > max){
			max = sum;
			ind = i;
		}
	}
    return ind;
}
int main(){
	FILE *f1 = fopen("pp_tra.dat", "r"); 
	int train[6670][192];
	int label[6670];
	float class_prob[10];
	int i,j,k,c;
	for(i=0;i<6670;i++){
		for(j=0;j<192;j++){
			fscanf(f1,"%d",&train[i][j]);
		}
        fscanf(f1,"%d",&label[i]);
	}
	float pro[10][192][5];

	for(i=0;i<10;i++){
		for(j=0;j<192;j++){
			for(k=0;k<5;k++){
				pro[i][j][k]=count_col(train,label,i,j,k,class_prob);
			}
		}
	}

/*	for(i=0;i<10;i++){
		printf("%d\n\n ",i);
		for(j=0;j<192;j++){
			printf("%d ",j);
			for(k=0;k<5;k++){
				printf("%f ",pro[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}*/

	FILE *f2 = fopen("pp_tes.dat", "r"); 
	int test[3333][192];
	int pred_label[3333];
	int test_label[3333];
	for(i=0;i<3333;i++){
		j=0;
		while(j<192){
			fscanf(f2,"%d",&test[i][j]);
			j++;
		}
        fscanf(f2,"%d",&test_label[i]);
	}
	i=0;
	while(i<3333){
		pred_label[i] = count_test(test[i],pro,class_prob);
	i++;
	}
    int count=0;
	for(i=0;i<3333;i++){
		if(test_label[i]==pred_label[i]){
			count++;
		}
	}
	i=0;
	while(i<3333){
		printf("%d %d %d\n",i,pred_label[i],test_label[i]);
		i++;
	}

	printf("%lf\n",(count/3333.0)*100);

	
	return 0;
}