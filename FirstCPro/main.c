#include <stdio.h>

int main() {
    int a,b;
    printf("Hello, World!\n");
    printf("��ã����磡\n");
    //���棺error C6031������ֵ������: ��scanf����
	//scanf("%d %d", &a,&b);
    if (scanf("%d %d", &a, &b) != 2) {
        printf("������Ч������������������\n");
        return 1;
    }
	printf("You entered: %d %d\n", a,b);
	printf("%d + %d = %d\n", a, b, a + b);
    return 0;
}