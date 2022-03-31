// C libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//The restricted number of unicode characters
#define unicode_set 1114112

/* The function for this algorithm
 * The description is below the main function
 */
void finite_automation_matcher(char text[], int **function, int pattern_size, int pattern_length);

void compute_transition_function(char pattern[], int char_set, int **function);

void improved_compute_transition_function(char pattern[], int char_set, int **function);

int utf8_size(unsigned char ch);

int utf8_strlen(char *str);

unsigned int utf8_codepoint(char *str, int i);

//The main function
int main () {

  //allocate memory for the text file
  char *text=(char *)malloc(405008);

  //read the text file character by character
  char c;

  FILE * file = fopen("/home/reseda/Public/algorithms/resources/eight-cousins.txt", "r");

  if(file){
    for(int i=0;(c=getc(file)) != EOF;i++){
      text[i]=c;
    }
    fclose(file);
  }

  /* For clearity, size means the number of elements in the char array, and
   * length means the number of unicode characters in the char array
   */

  //pattern 1: headache
  char *pattern_1 = "headache";
  int pattern_1_size = strlen(pattern_1);
  int pattern_1_length = utf8_strlen(pattern_1);
  int **function_1=(int **)malloc(sizeof(int*)*(pattern_1_length+1));
  for(int i=0;i<=pattern_1_length;i++){
    function_1[i]=(int*)malloc(sizeof(int)*unicode_set);
  }

  //pattern 2: lull
  char *pattern_2 = "lull";
  int pattern_2_size = strlen(pattern_2);
  int pattern_2_length =utf8_strlen(pattern_2);
  int **function_2=(int **)malloc(sizeof(int*)*(pattern_2_length+1));
  for(int i=0;i<=pattern_2_length;i++){
    function_2[i]=(int*)malloc(sizeof(int)*unicode_set);
  }

  //pattern 3: purple
  char *pattern_3 = "purple";
  int pattern_3_size = strlen(pattern_3);
  int pattern_3_length =utf8_strlen(pattern_3);
  int **function_3=(int **)malloc(sizeof(int*)*(pattern_3_length+1));
  for(int i=0;i<=pattern_3_length;i++){
    function_3[i]=(int*)malloc(sizeof(int)*unicode_set);
  }

  //pattern 4: violet
  char *pattern_4 = "violet";
  int pattern_4_size = strlen(pattern_4);
  int pattern_4_length = utf8_strlen(pattern_4);
  int **function_4=(int **)malloc(sizeof(int*)*(pattern_4_length+1));
  for(int i=0;i<=pattern_4_length;i++){
    function_4[i]=(int*)malloc(sizeof(int)*unicode_set);
  }

  //Additional pattern that contains a non-ASCII character
  //pattern 5: ” said Archie
  char *pattern_5 = "” said Archie";
  int pattern_5_size = strlen(pattern_5);
  int pattern_5_length = utf8_strlen(pattern_5);
  int **function_5=(int **)malloc(sizeof(int*)*(pattern_5_length+1));
  for(int i=0;i<=pattern_5_length;i++){
    function_5[i]=(int*)malloc(sizeof(int)*unicode_set);
  }
  
  //matching for each pattern
  printf("Pattern 1: %s\n",pattern_1);
  printf("Original version\n");
  compute_transition_function(pattern_1, unicode_set, function_1);
  finite_automation_matcher(text, function_1, pattern_1_size, pattern_1_length);

  printf("Improved version\n");
  improved_compute_transition_function(pattern_1, unicode_set, function_1);
  finite_automation_matcher(text, function_1, pattern_1_size, pattern_1_length);

  printf("\n");
  
  printf("Pattern 2: %s\n",pattern_2);
  printf("Original version\n");
  compute_transition_function(pattern_2, unicode_set, function_2);  
  finite_automation_matcher(text, function_2, pattern_2_size, pattern_2_length);

  printf("Improved version\n");
  improved_compute_transition_function(pattern_2, unicode_set, function_2);  
  finite_automation_matcher(text, function_2, pattern_2_size, pattern_2_length);

  printf("\n");
  
  printf("Pattern 3: %s\n",pattern_3);
  printf("Original version\n");
  compute_transition_function(pattern_3, unicode_set, function_3);  
  finite_automation_matcher(text, function_3, pattern_3_size, pattern_3_length);

  printf("Improved version\n");
  improved_compute_transition_function(pattern_3, unicode_set, function_3);  
  finite_automation_matcher(text, function_3, pattern_3_size, pattern_3_length);

  printf("\n");
  
  printf("Pattern 4: %s\n",pattern_4);
  printf("Original version\n");
  compute_transition_function(pattern_4, unicode_set, function_4);
  finite_automation_matcher(text, function_4, pattern_4_size, pattern_4_length);

  printf("Improved version\n");
  improved_compute_transition_function(pattern_4, unicode_set, function_4);
  finite_automation_matcher(text, function_4, pattern_4_size, pattern_4_length);

  printf("\n");
  
  printf("Pattern 5: %s\n",pattern_5);
  printf("Original version\n");
  compute_transition_function(pattern_5, unicode_set, function_5);
  finite_automation_matcher(text, function_5, pattern_5_size, pattern_5_length);

  printf("Improved version\n");
  improved_compute_transition_function(pattern_5, unicode_set, function_5);
  finite_automation_matcher(text, function_5, pattern_5_size, pattern_5_length);

  //free functions
  for(int i=0;i<=pattern_1_length;i++){
    free(function_1[i]);
  }
  free(function_1);
 
  for(int i=0;i<=pattern_2_length;i++){
    free(function_2[i]);
  }
  free(function_2);
  for(int i=0;i<=pattern_3_length;i++){
    free(function_3[i]);
  }
  free(function_3);
 
  for(int i=0;i<=pattern_4_length;i++){
    free(function_4[i]);
  }
  free(function_4);
  for(int i=0;i<=pattern_5_length;i++){
    free(function_5[i]);
  }
  free(function_5);

  //free the text string
  free(text);
  
  //End the program
  return 0;
  
}

/* @Name   finite_automation_matcher
 * @brief  Find a pattern in a given text
 * @param  text, a char array that contains a text
 *         function, an two-dimensional int array that is a state function
 *         pattern_size, an integer that is the number of elements in the char array of pattern
 *         pattern_length, an integer that is the number of unicode characters in the char array of pattern
 * @pre    text and pattern is non-empty array
 * @post   Print the index where the pattern occurs.
 *         the index indicates nth element in the char array of text, not nth character in the text
 */
void finite_automation_matcher(char text[], int **function, int pattern_size, int pattern_length){

  //text_length stores the number of elements in the char array of text
  int text_size=strlen(text);

  //state starts from 0
  int state=0;

  //Check all the unicode characters in the text to find the given pattern
  for(int i=0; i<text_size;){

    //state changes depending on the next character
    state=function[state][utf8_codepoint(text, i)];

    //The index is printed out when the given pattern is found
    if(state == pattern_length){
      printf("The pattern occurs at index %d\n", i-pattern_size+1);
    }
    
    //Move to the next unicode character
    i += utf8_size(text[i]);
  }
}

/* @Name   compute_transition_function
 * @brief  Compute a transition function for a pattern matching
 * @param  pattern, a char array that is a given pattern
 *         char_set, an integer that is the number of characters in the character set
 *         function, a two-dimensional int array where a transition function will be stored
 * @pre    text and pattern is non-empty array
 * @post   The result is stored in function
 */
void compute_transition_function(char pattern[], int char_set, int **function){

  /* pattern_legnth is the number of unicode characters in the pattern
   * pattern_size is the number of elements in the char array of the pattern
   */
  int pattern_length=utf8_strlen(pattern);
  int pattern_size = strlen(pattern);

  /* state is the state in the transition function
   * i and j are variables to find the longest prefix of the pattern that is a suffix of what has been read so far
   */
  int i,j,state=0;

  /* traverse each character in the pattern
   * index is the index in the char array
   */
  for(int index=0;index<=pattern_size;state++){

    //traverse each character in the character set
    for(int a=0;a<char_set;a++){      

      //if a is equal to the next character in the pattern, state+1 is stored in the function
      if(state < pattern_length && utf8_codepoint(pattern, index)==a){
        function[state][a]=state+1;
        a++;
      }

      //find the longest prefix of the pattern that is a suffix of what has been read so far
      for(i=index;i>0;i--){
        for(j=0;j<i-1;j++){
          if(pattern[j] != pattern[index-i+1+j]){
            break;
          }
        }
        if(j==i-1 && utf8_codepoint(pattern, i-1)==a){
          function[state][a]=i;
          break;
        }
      }
      if(i==0){
        function[state][a]=0;
      }
    }

    //move to the next unicode character
    index+=utf8_size(pattern[index]);
  }
}

/* According to Exercise 32.4-8, there is a faster COMPUTE-TRANSITION-FUNCTION
 * using the fact delta(q,a)=delta(pi[q],a) if q = m or P[q+1] != a
 */

/* @Name   improved_compute_transition_function
 * @brief  Compute a transition function for a pattern matching
 * @param  pattern, a char array that is a given pattern
 *         char_set, an integer that is the number of characters in the character set
 *         function, a two-dimensional int array where a transition function will be stored
 * @pre    text and pattern is non-empty array
 * @post   The result is stored in function
 */
void improved_compute_transition_function(char pattern[], int char_set, int **function){

  /* pattern_legnth is the number of unicode characters in the pattern
   * pattern_size is the number of elements in the char array of the pattern
   */
  int pattern_length=utf8_strlen(pattern);
  int pattern_size = strlen(pattern);
  
  /* state is the state in the transition function
   * prev is pi[q] where pi is the prefix function in the KMP algorithm
   */
  int state=1, prev=0;

  //fill in the first row of the transition function
  for(int a=0;a<=char_set;a++){
    if(utf8_codepoint(pattern, 0)==a){
      function[0][a]=1;
    }else{
      function[state][a]=0;
    }
  }

  //copy and paste from the prev row to the state row
  for(int index=utf8_size(pattern[0]);index<=pattern_size;state++){
    for(int a=0;a<char_set;a++){
      function[state][a]=function[prev][a];
    }

    //update the function for the matched next character
    function[state][utf8_codepoint(pattern, index)]=state+1;

    //store the index of the row for the next state
    prev = function[prev][utf8_codepoint(pattern, index)];

    //move to the next unicode character
    index += utf8_size(pattern[index]);
  }
}

/* @Name   utf8_size
 * @brief  Find a byte size of the given unicode character
 * @param  ch, a char that is the first byte of the unicode character
 * @return count, an integer that is the byte size of the unicode character
 * @pre    ch must be the first byte of the unicode character
 * @post   the byte size of the unicode character is returned
 */
int utf8_size(unsigned char ch){

  //count starts from 0
  int count=0;

  /* if the byte is smaller than or equal to 127, the charcter is in the ASCII code,
   * so it has 1 byte
   * if not, the number of 1s at the beginning indicates the byte size of characters
   */
  if(ch <=127){
    return 1;
  }else{
    ch>>=4;
    while(ch){
      count += ch & 1;
      ch >>= 1;
    }
    return count;
  }
}

/* @Name   utf8_strlen
 * @brief  Count unicode characters in the given string
 * @param  str, a char array that is the given string
 * @post   The number of unicode characters in str is returned
 */
int utf8_strlen(char *str){

  //count and i start from 0
  int count=0, i=0;

  //increment count until the procedure reaches the end of str
  if(str == NULL){
    return 0;
  }else{
    while(str[i] != '\0'){
      count++;

      //move to the next unicode character
      i += utf8_size((unsigned char)str[i]);
    }
    return count;
  }
}

/* @Name   utf8_codepoint
 * @brief  Decode the UTF-8 unicode character
 * @param  str, a char array that is the given string
 *         i, an integer that is the index where a unicode character starts
 * @post   The codepoint of the unicode character is returned
 */
unsigned int utf8_codepoint(char *str, int i){

  //temp is necessary not to modify the actural string
  unsigned char temp;

  /* codepoin is used to calculate the code point
   * temp_size is the byte size of the unicode character
   */
  unsigned int codepoint, temp_size;

  //store the first byte of the unicode character to temp
  temp=(unsigned char)str[i];

  //get rid of the bits that represent the byte size
  temp_size=utf8_size(temp);
  temp <<= temp_size;
  temp >>= temp_size;

  //store the valid bits in the first byte to codepoint
  codepoint=(unsigned int)temp;

  //find the valid bits in the next bytes and update codepoint
  for(int j=1;j<temp_size;j++){
    codepoint <<= 6;
    temp=(unsigned char)str[i+j];
    temp &= 63;
    codepoint += temp;
  }

  return codepoint;
}
