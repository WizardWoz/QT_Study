#include <stdio.h>

int main() {
    int a,b;
    printf("Hello, World!\n");
    printf("你好，世界！\n");
    //警告：error C6031：返回值被忽略: “scanf”。
	//scanf("%d %d", &a,&b);
    if (scanf("%d %d", &a, &b) != 2) {
        printf("输入无效，请输入两个整数。\n");
        return 1;
    }
	printf("You entered: %d %d\n", a,b);
	printf("%d + %d = %d\n", a, b, a + b);
    return 0;
}