#include "array.h"
#include <stdio.h>
int main(){
dyntab P;
dyntab_init(&P, sizeof(int));
int i;
int k;
for(i = 0 ; i < 5000 ; ++i){
	dyntab_push(&P, &i);
	dyntab_pop_get(&P, &k);
	printf("%d \n", k);
}	
	return 0;
}
