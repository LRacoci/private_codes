#include <stdio.h>

int main() {
	int i,k;
	int v[7] = {0,0,0,3,0,2,2};
	int n = 7;

	for (i=0,k=0;i<7;i++) {
		if (v[i]) {
			v[k] = v[i];
			k++;
		} else {
			n--;
		}
	}

	for (i=0;i<n;i++) {
		printf("%d\n", v[i]);
	}
	printf("%d\n", n);

	return 0;
}