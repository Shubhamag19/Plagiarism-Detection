#include<stdio.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdlib.h>

int b=11,k;
int columns;

char** kgrams(char s[]){
  int i=0, n=0;
  while(s[n] != '\0'){
    n++;
  }
  columns=(n-5)+1;

  char **grams;
  grams = calloc(columns, sizeof(char*));
  for(i=0; i<columns; i++){
    grams[i]=calloc(5, sizeof(char*));
  }

  for(i=0;i<columns;i++){
    for(int j=0;j<5;j++){
      *(*(grams+i)+j)=s[i+j];
    }
  }
  return grams;
}
int* hashing(char** grams){
  int *hash;
  hash = calloc(columns, sizeof(int*));
  int h=0;
  for(int i=0;i<columns;i++){
    for(int j=0;j<k;j++){
      hash[i]+=grams[i][j]*pow(b,(k-(j+1)));
    }
  }
  return hash;
}
int** windowformation(int* hash){
  int wlength=4;
  int len=columns-4;
  int** window_index;
  window_index = calloc(len+1, sizeof(int*));
  for(int i=0; i<columns; i++){
    window_index[i]=calloc(wlength, sizeof(int*));
  }
  int** window;
  window = calloc(len+1,sizeof(int*));
  for(int i=0;i<len+1;i++){
    window[i] = calloc(wlength, sizeof(int*));
  }

  for(int i=0;i<len+1;i++){
    for(int j=0;j<wlength;j++){
      window[i][j]=hash[i+j];
      window_index[i][j]=j;
    }
  }
  return window;
}
int calcfv(int** window){
  int len=columns-4;
  int *minvalue;
  minvalue = calloc(len+1, sizeof(int*));
  int fvi = 1;
  for(int i=1;i<len+1;i++){
     int localmin=INT_MAX;
     for(int j=0;j<4;j++){
       if(window[i][j]<localmin){
         minvalue[i]=window[i][j];
         localmin=minvalue[i];
       }
     }
      if(minvalue[i]!=window[i-1][0] && minvalue[i]!=window[i-1][1] && minvalue[i]!=window[i-1][2] && minvalue[i]!=window[i-1][3]){
        fvi++;
      }
      else if(minvalue[i]!=minvalue[i-1]){
        fvi++;
      }
    }
    return fvi;
}
int* valuefromwindow(int** window){
  int len=columns-4;
  int *minvalue;
  minvalue = calloc(len+1, sizeof(int*));
  int *fingerprint_values;
  int fvival = calcfv(window);
  fingerprint_values = calloc(fvival, sizeof(int*));
  int fvi=0;


  int i=0;
  int localmin=INT_MAX;
  for(int j=0;j<4;j++){
    if(window[i][j]<localmin){
      minvalue[i]=window[i][j];
      localmin=minvalue[i];
    }
  }
  fingerprint_values[fvi]=minvalue[i];
  fvi++;

  for(i=1;i<len+1;i++){
     localmin=INT_MAX;
     for(int j=0;j<4;j++){
       if(window[i][j]<localmin){
         minvalue[i]=window[i][j];
         localmin=minvalue[i];
       }
     }

      if(minvalue[i]!=window[i-1][0] && minvalue[i]!=window[i-1][1] && minvalue[i]!=window[i-1][2] && minvalue[i]!=window[i-1][3]){
        fingerprint_values[fvi]=minvalue[i];
        fvi++;
      }
      else if(minvalue[i]!=minvalue[i-1]){
        fingerprint_values[fvi]=minvalue[i];
        fvi++;
      }
    }
    return fingerprint_values;
}

void filter(char s[]){
  int i=0;
  while(s[i] != '\0'){
    if(s[i]<'a' || s[i]>'z'){
      int j=i;
      while(s[j] != '\0'){
        s[j]=s[j+1];
        j++;
      }
      i--;
    }
    i++;
  }
}
void compare(int* fval1, int* fval2){
  float c1=0.0, c2=0.0;
  int i=0;
  int match=0;
  while(fval1[i]!='\0'){
    i++;
    c1++;
  }
  i=0;
  while(fval2[i]!='\0'){
    i++;
    c2++;
  }
    for(i=0;i<c1;i++){
      for(int j=0;j<c2;j++){
        if(fval1[i]==fval2[j]){
          match++;
          break;
        }
      }
    }
    float total=c1+c2;
    float result = (match/c1)*100;
    printf("Percentage from Winnowing Algorithm: %f%\n\n", k, result);
}
void preprocess(char *s, int count, int kk){
  k=kk;
  filter(s);
  char** kg=kgrams(s);
  int* hvalue=hashing(kg);
  int** wf = windowformation(hvalue);

  int* fval1;
  int* fval2;
  if(count==0){
    fval1 = valuefromwindow(wf);
  }
  if(count==1){
    fval2 = valuefromwindow(wf);
    compare(fval1, fval2);
  }
}

