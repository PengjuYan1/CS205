#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//将大数逆序存储为字符数组
void reverse(char *str){
  int len = strlen(str);
  for(int i = 0; i < len / 2; i++){
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
}
//将逆序字符数组转换为逆序数组
void str_to_num_array(const char *str, int *num, int *len){
  *len = strlen(str);
  char temp[*len + 1];
  strcpy(temp, str);
  reverse(temp);
  for(int i = 0; i < *len ; i++){
    num[i] = temp[i] - '0';
  }
}

void mul(const int *num1, int len1, const int *num2, int len2, int *result){
  //初始化结果数组为0
  int max_len = len1 + len2;
  for(int i = 0; i < max_len; i++){
    result[i] = 0;  
  }

  //逐位相乘并累加
  for(int i = 0; i < len1; i++){
    for(int j = 0; j < len2; j++){
      result[i + j] += num1[i] * num2[j];
      result[i + j + 1] += result[i + j] / 10; //进位
      result[i + j] %= 10;
    }
  }
}

void result_to_string(const int *result, int len, char *output){
     int start = len - 1;
    // 找到第一个非零位
    while (start >= 0 && result[start] == 0) {
        start--;
    }
    if (start == -1) { // 结果为0
        output[0] = '0';
        output[1] = '\0';
        return;
    }
    // 逆序转换为字符串
    int idx = 0;
    for (int i = start; i >= 0; i--) {
        output[idx++] = result[i] + '0';
    }
    output[idx] = '\0';
}

int main(){
  char str1[] = "987654321";
  char str2[] = "987654321";
  int num1[100], num2[100], result[200] = {0};
  int len1, len2;
  str_to_num_array(str1, num1, &len1);
  str_to_num_array(str2, num2, &len2);
  mul(num1, len1, num2, len2, result);
  char output[200];
  result_to_string(result, len1 + len2, output);
  printf("%s * %s = %s\n", str1, str2, output);

  return 0;
}
