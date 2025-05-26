#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>

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
      int a1, a2;
      a1 = strtol(str[1], &endptr, 10);
      a2 = strtol(str[3], &endptr, 10);
      Mul_Int(a1, a2);
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


void interactive_mode(){

}

int main(int argc, char* argv[]){
  bool flag = detect_error(argc, argv);
  if(!flag) return 0;

  if(argc > 1){
  // 参数模式  
  process_input(argv);
  }else{
  // 交互模式
    interactive_mode();
  }

  return 0;
}
