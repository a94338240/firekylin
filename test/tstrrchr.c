#include <string.h>
#include <stdio.h>

int main()
{
	printf("%s\n",strrchr("dfsf/dsfsdfds/fdsfdsf",'/'));
	printf("%s\n",strrchr("dfsf/dsfsdfds///1fdsfdsf",'/'));
	printf("%s\n",strrchr("dfsf/dsfsdfds//fdsfdsf",'/'));
	printf("%s\n",strrchr("dfsf/dsfsdfds//fdsfdsf/",'/'));
}
