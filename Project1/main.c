#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
//#include <ctype.h>
#include <stdbool.h>


#define MAX_INPUT 1024

typedef enum{
  NUM_INTEGER,  //整数
  NUM_FLOAT     //浮点数
} NumberType;

bool is_numeric(const char *str){
  
  if(str == NULL || *str == '\0') return 0;
  //禁止'.1'这种形式的语法
  if(str[0] == '.') return 0;

  char *endptr;
  errno = 0; //清除错误标准
  strtod(str, &endptr); //转化为浮点数
  //检查：
  //1. 是否转到到字符串末尾
  //2. 是否发生了溢出
  //3. 是否至少有一个数字字符(避免""或者"."通过检查)
  return (*endptr == '\0' && errno != ERANGE && endptr != str);
}

NumberType check_numtype(const char *str){
  bool has_dot = false;
  const char *p = str;
  if(*p == '+' || *p == '-') p++; //跳过正负号
  while(*p != '\0'){
    if(*p == '.') has_dot = true;
    p++;
  }
  return has_dot ? NUM_FLOAT : NUM_INTEGER;

}

bool detect_error(int count, char **str){
    if(count != 4){
      printf("参数数量错误\n");
      return 0;
    }
    if(is_numeric(str[1]) == 0 || is_numeric(str[3]) == 0){
      printf("输出不是数值\n");
      return 0;
    }
    if(str[3][0] == '0'){
      printf("不能除以0\n");
      return 0;
  }
    return 1;
    
}
void Add_Int(int a1, int a2){
  printf("%d + %d = %d\n", a1, a2, a1 + a2);
}
void Add_Float(double a1, double a2){
  printf("%.1f + %.2f = %.1f\n", a1, a2, a1 + a2);
}
void Sub_Int(int a1, int a2){
  printf("%d - %d = %d\n", a1, a2, a1 - a2);
}
void Sub_Float(double a1, double a2){
  printf("%.1f - %.1f = %.1f\n", a1, a2, a1 - a2);
}
void Mul_Int(int a1, int a2){
  printf("%d x %d = %d\n", a1, a2, a1 * a2); 
}
void Mul_Float(double a1, double a2){
  printf("%.1f x %.1f = %.1f\n", a1, a2, a1 * a2);
}
void Div_Int(int a1, int a2){
  printf("%d / %d = %.1f\n", a1, a2, a1 / (double)a2);
}
void Div_Float(double a1, double a2){ 
  printf("%.1f / %.1f = %.1f\n", a1, a2, a1 / a2);
}
void reverse(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void str_to_num_array(const char *str, int *num, int *len) {
    *len = strlen(str);
    char temp[*len + 1];
    strcpy(temp, str);
    reverse(temp);
    for (int i = 0; i < *len; i++) {
        num[i] = temp[i] - '0';
    }
}

void multiply(const int *num1, int len1, const int *num2, int len2, int *result) {
    int max_len = len1 + len2;
    for (int i = 0; i < max_len; i++) result[i] = 0;

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            result[i + j] += num1[i] * num2[j];
            result[i + j + 1] += result[i + j] / 10;
            result[i + j] %= 10;
        }
    }
}

void result_to_string(const int *result, int len, char *output) {
    int start = len - 1;
    while (start >= 0 && result[start] == 0) start--;
    if (start == -1) {
        output[0] = '0';
        output[1] = '\0';
        return;
    }
    int idx = 0;
    for (int i = start; i >= 0; i--) {
        output[idx++] = result[i] + '0';
    }
    output[idx] = '\0';
}
void process_input(char **str){
  char *endptr;
  NumberType t1 = check_numtype(str[1]);
  NumberType t2 = check_numtype(str[3]);

  if(str[2][0] == '+'){
    if(t1 == NUM_FLOAT) {
      double a1, a2;
      a1 = strtod(str[1], &endptr);
      a2 = strtod(str[3], &endptr);
      Add_Float(a1, a2);
    }
    if(t2 == NUM_INTEGER) {
      int a1, a2;
      a1 = strtol(str[1], &endptr, 10);
      a2 = strtol(str[3], &endptr, 10);
      Add_Int(a1, a2);
    }
  } else if(str[2][0] == '-'){
    if(t1 == NUM_FLOAT) {
      double a1, a2;
      a1 = strtod(str[1], &endptr);
      a2 = strtod(str[3], &endptr);
      Sub_Float(a1, a2);
    }
    if(t2 == NUM_INTEGER) {
      int a1, a2;
      a1 = strtol(str[1], &endptr, 10);
      a2 = strtol(str[3], &endptr, 10);
      Sub_Int(a1, a2);
    }
  } else if(str[2][0] == 'x'){
    if(t1 == NUM_FLOAT) {
      double a1, a2;
      a1 = strtod(str[1], &endptr);
      a2 = strtod(str[3], &endptr);
      Mul_Float(a1, a2);
    }
    if(t2 == NUM_INTEGER) {
      // int a1, a2;
      // a1 = strtol(str[1], &endptr, 10);
      // a2 = strtol(str[3], &endptr, 10);
      // Mul_Int(a1, a2);
      int num1[100], num2[100], result[200] = {0};
      int len1, len2;
      str_to_num_array(str[1], num1, &len1);
      str_to_num_array(str[3], num2, &len2);

      // 计算乘积
      multiply(num1, len1, num2, len2, result);

      // 转换为字符串并输出
      char output[200];
      result_to_string(result, len1 + len2, output);
      printf("%s x %s = %s\n", str[1], str[3], output);
    }
  } else if(str[2][0] == '/'){
    if(t1 == NUM_FLOAT) {
      double a1, a2;
      a1 = strtod(str[1], &endptr);
      a2 = strtod(str[3], &endptr);
      Div_Float(a1, a2);
    }
    if(t2 == NUM_INTEGER) {
      int a1, a2;
      a1 = strtol(str[1], &endptr, 10);
      a2 = strtol(str[3], &endptr, 10);
      Div_Int(a1, a2);
    }
  }
  
}
void process_input_interactive(char *str){
  char *input[100] = {};
  char *token = strtok(str, " ");//按空格分割
  
  //for(int i = 0; i < 3; i++){
  //  input[i] = token;
  //  printf("token:%s\n", input[i]);
  //  token = strtok(NULL, " ");
  //}
  int i = 1;  
  //这里i从1开始是因为要兼容process_input处理argv的元素，否则会非法内存访问
  while(token != NULL){
    input[i] = token;
    //printf("token:%s\n", input[i]);
    token = strtok(NULL, " ");
    i++;
  }
  process_input(input);

}
void interactive_mode() {
  char input[MAX_INPUT];
  printf("=== 交互模式 === (输入quit退出)\n");

  while(true){
    if(fgets(input, MAX_INPUT, stdin) == NULL){
      printf("读取失败或遇到EOF!\n");
      break;
    }
    //退出
    if(strcmp(input, "quit\n") == 0) break;
    //去除换行符
    input[strcspn(input, "\n")] = '\0';
    //处理输入
    process_input_interactive(input);
  }
}

int main(int argc, char* argv[]){

  if(argc > 1){
  // 参数模式  
  bool flag = detect_error(argc, argv);
  if(!flag) return 0;
  process_input(argv);
  }else{
  // 交互模式
    interactive_mode();
  }

  return 0;
}
