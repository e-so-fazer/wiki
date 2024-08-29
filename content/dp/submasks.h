/**
 * Author: Arthur Botelho
 * Description: iterating over all submasks of all masks in descending order
 * Time: O(3^n)
 * Memory: O(1)
 * Status: not tested
*/

void submaskiteration(){
	int mx = 4;
	for(int mask = 0; mask < (1<<mx); mask++){
		for(int s = mask; s ; s=(s-1)&mask){
			//s is a non zero submask of mask
			;
		}
		//now process zero submask
	}
}