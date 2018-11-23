// C Program to illustrate how to convert e-nfa to DFA 

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAX_LEN 100 

char NFA_FILE[MAX_LEN]; 
char buffer[MAX_LEN]; 
int zz = 0; 

// Structure to store DFA states and their 
// status ( i.e new entry or already present) 
struct DFA { 
char *n; 
int count; 
} dfa; 

int last_index = 0; 
FILE *fp; 
int sym; 

/* reset the hash map*/
void reset(int ar[], int size) { 
int i; 

// reset all the values of 
// the mapping array to zero 
for (i = 0; i < size; i++) { 
	ar[i] = 0; 
} 
} 

// Check which States are present in the e-closure 

/* map the states of NFA to a hash set*/
void check(int ar[], char S[]) { 
int i, j; 

// To parse the individual states of NFA 
int len = strlen(S); 
for (i = 0; i < len; i++) { 

	// Set hash map for the position 
	// of the states which is found 
	j = ((int)(S[i]) - 65); 
	ar[j]++; 
} 
} 

// To find new Closure States 
void state(int ar[], int size, char S[]) { 
int j, k = 0; 

// Combine multiple states of NFA 
// to create new states of DFA 
for (j = 0; j < size; j++) { 
	if (ar[j] != 0) 
	S[k++] = (char)(65 + j); 
} 

// mark the end of the state 
S[k] = '\0'; 
} 

// To pick the next closure from closure set 
int closure(int ar[], int size) { 
int i; 

// check new closure is present or not 
for (i = 0; i < size; i++) { 
	if (ar[i] == 1) 
	return i; 
} 
return (100); 
} 

// Check new DFA states can be 
// entered in DFA table or not 
int indexing(struct DFA *dfa) { 
int i; 

for (i = 0; i < last_index; i++) { 
	if (dfa[i].count == 0) 
	return 1; 
} 
return -1; 
} 

/* To Display epsilon closure*/
void Display_closure(int n, int closure_ar[], 
					char *closure_table[], 
					char *NFA_TABLE[][sym + 1], 
					char *DFA_TABLE[][sym]) { 
int i; 
for (i = 0; i < n; i++) { 
	reset(closure_ar, n); 
	closure_ar[i] = 2; 

	// to neglect blank entry 
	if (strcmp(&NFA_TABLE[i][sym], "-") != 0) { 

	// copy the NFA transition state to buffer 
	strcpy(buffer, &NFA_TABLE[i][sym]); 
	check(closure_ar, buffer); 
	int z = closure(closure_ar, n); 

	// till closure get completely saturated 
	while (z != 100) 
	{ 
		if (strcmp(&NFA_TABLE[z][sym], "-") != 0) { 
		strcpy(buffer, &NFA_TABLE[z][sym]); 

		// call the check function 
		check(closure_ar, buffer); 
		} 
		closure_ar[z]++; 
		z = closure(closure_ar, n); 
	} 
	} 

	// print the e closure for every states of NFA 
	printf("\n e-Closure (%c) :\t", (char)(65 + i)); 

	bzero((void *)buffer, MAX_LEN); 
	state(closure_ar, n, buffer); 
	strcpy(&closure_table[i], buffer); 
	printf("%s\n", &closure_table[i]); 
} 
} 

/* To check New States in DFA */
int new_states(struct DFA *dfa, char S[]) { 

int i; 

// To check the current state is already 
// being used as a DFA state or not in 
// DFA transition table 
for (i = 0; i < last_index; i++) { 
	if (strcmp(&dfa[i].n, S) == 0) 
	return 0; 
} 

// push the new 
strcpy(&dfa[last_index++].n, S); 

// set the count for new states entered 
// to zero 
dfa[last_index - 1].count = 0; 
return 1; 
} 

// Transition function from NFA to DFA 
// (generally union of closure operation ) 
void trans(char S[], int M, char *clsr_t[], int st, 
			char *NFT[][sym + 1], char TB[]) { 
int len = strlen(S); 
int i, j, k, g; 
int arr[st]; 
int sz; 
reset(arr, st); 
char temp[MAX_LEN], temp2[MAX_LEN]; 
char *buff; 

// Transition function from NFA to DFA 
for (i = 0; i < len; i++) { 

	j = ((int)(S[i] - 65)); 
	strcpy(temp, &NFT[j][M]); 

	if (strcmp(temp, "-") != 0) { 
	sz = strlen(temp); 
	g = 0; 

	while (g < sz) { 
		k = ((int)(temp[g] - 65)); 
		strcpy(temp2, &clsr_t[k]); 
		check(arr, temp2); 
		g++; 
	} 
	} 
} 

bzero((void *)temp, MAX_LEN); 
state(arr, st, temp); 
if (temp[0] != '\0') { 
	strcpy(TB, temp); 
} else
	strcpy(TB, "-"); 
} 

/* Display DFA transition state table*/
void Display_DFA(int last_index, struct DFA *dfa_states, 
				char *DFA_TABLE[][sym]) { 
int i, j; 
printf("\n\n********************************************************\n\n"); 
printf("\t\t DFA TRANSITION STATE TABLE \t\t \n\n"); 
printf("\n STATES OF DFA :\t\t"); 

for (i = 1; i < last_index; i++) 
	printf("%s, ", &dfa_states[i].n); 
printf("\n"); 
printf("\n GIVEN sym FOR DFA: \t"); 

for (i = 0; i < sym; i++) 
	printf("%d, ", i); 
printf("\n\n"); 
printf("STATES\t"); 

for (i = 0; i < sym; i++) 
	printf("|%d\t", i); 
printf("\n"); 

// display the DFA transition state table 
printf("--------+-----------------------\n"); 
for (i = 0; i < zz; i++) { 
	printf("%s\t", &dfa_states[i + 1].n); 
	for (j = 0; j < sym; j++) { 
	printf("|%s \t", &DFA_TABLE[i][j]); 
	} 
	printf("\n"); 
} 
} 

// Driver Code 
int main() { 
int i, j, n; 
char T_buf[MAX_LEN]; 

// creating an array dfa structures 
struct DFA *dfa_states = malloc(MAX_LEN * (sizeof(dfa))); 

printf("Enter the number of states:");
scanf("%d",&n);
printf("Enter the number of symbols:");
scanf("%d",&sym);
printf("\n STATES OF NFA :\t\t"); 
for (i = 0; i < n; i++) 

	printf("%c, ", (char)(65 + i)); 
printf("\n"); 
printf("\n GIVEN sym FOR NFA: \t"); 

for (i = 0; i < sym; i++) 

	printf("%d, ", i); 
printf("eps");
printf("\n\n"); 
printf("Hint:Here %d implies the symbol eps and place '-' where there is no transition\n",sym);
char *NFA_TABLE[n][sym + 1]; 

// Hard coded input for NFA table 
char *DFA_TABLE[MAX_LEN][sym]; 
char transition[3];
 for (int i=0;i<n;i++)
	{
		for(int j=0;j<=sym;j++)
		{
			printf("Enter the transition of %c if %d is given:",(char)(65+i),j);
			scanf("%s",&NFA_TABLE[i][j]);

		}
	}

printf("\n\n\tNFA Transition Table\n\nSTATES\t");

for (i = 0; i < sym; i++) 
	printf("|%d\t", i); 
printf("|eps\n"); 

// Displaying the matrix of NFA transition table 
printf("--------+------------------------------------\n"); 
for (i = 0; i < n; i++) { 
	printf("%c\t", (char)(65 + i)); 

	for (j = 0; j <=sym; j++) { 
	printf("|%s \t", &NFA_TABLE[i][j]); 
	} 
	printf("\n"); 
} 
int closure_ar[n]; 
char *closure_table[n]; 

Display_closure(n, closure_ar, closure_table, NFA_TABLE, DFA_TABLE); 
strcpy(&dfa_states[last_index++].n, "-"); 

dfa_states[last_index - 1].count = 1; 
bzero((void *)buffer, MAX_LEN); 

strcpy(buffer, &closure_table[0]); 
strcpy(&dfa_states[last_index++].n, buffer); 

int Sm = 1, ind = 1; 
int start_index = 1; 

// Filling up the DFA table with transition values 
// Till new states can be entered in DFA table 
while (ind != -1) { 
	dfa_states[start_index].count = 1; 
	Sm = 0; 
	for (i = 0; i <=sym; i++) { 

	trans(buffer, i, closure_table, n, NFA_TABLE, T_buf); 

	// storing the new DFA state in buffer 
	strcpy(&DFA_TABLE[zz][i], T_buf); 

	// parameter to control new states 
	Sm = Sm + new_states(dfa_states, T_buf); 
	} 
	ind = indexing(dfa_states); 
	if (ind != -1) 
	strcpy(buffer, &dfa_states[++start_index].n); 
	zz++; 
} 
// display the DFA TABLE 
Display_DFA(last_index, dfa_states, DFA_TABLE); 

return 0; 
} 

