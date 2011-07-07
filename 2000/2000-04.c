#include <contest.h>

#define D if (0)

int n_columns;
int n_rows;
int *col_widths;
char *col_justify;
char *col_sep;
char ***rows;  

char  *justify(char *string, char mode, int length, int last) {
  char *newstr;

  if (strlen(string) > length+1) {
    printf("strlen(\"%s\") == %d > %d\n",string,strlen(string),length);
    return strdup("string too long");
  }

  newstr = malloc(sizeof(char) * (length+10));

  strcpy(newstr," ");
  strcat(string, " ");
  
  switch (mode) {
  case 'r':
    while ( (strlen(newstr) + strlen(string)) < length)
      strcat(newstr," ");
    strcat(newstr,string);
    return newstr;
    break;
  case 'l':
    strcat(newstr, string);
    while (strlen(newstr) < (length))
      strcat(newstr," ");
    return newstr;
  case 'c':
    
    while ((strlen(newstr) + (strlen(string)-1)/2) < (length/2 + length%2))
	   strcat(newstr," ");
    strcat(newstr,string);
    while (strlen(newstr) < length)
      strcat(newstr," ");
    return newstr; 
  }
  return strdup("error");
}

int main(int argc, char **argv) {

  int row = 0;
  int column = 0;
  char *str,
    *string;

  string = malloc(255);
  str = string;

  n_rows = 0;
  n_columns = 0;
  rows = NULL;

  while (1 == scanf("%s",string)) {
    D printf("got word \"%s\"\n",string);
    switch (string[0]) {
    case '\\':
      D printf("got escape sequence\n");
      if (0 == strcmp(string,"\\\\")) {
	D printf("row %u column %u has length %u and is \"%s\"\n",
		 row, column, strlen(rows[row][column]), rows[row][column]);
	column  = 0;
	row ++;
	n_rows ++;
	rows = realloc(rows, sizeof(char **) * n_rows);
	rows[row] = calloc(sizeof(char *) , n_columns);

	D printf("moving on to row %u\n",  row);
      } else 
	if (0 == strcmp("\\end{tabular}",string)) {
	}
	else {
	  /* assume \begin{tabular}{....} */
	  
	  D printf("parsing begin tag\n");
	  str = string + 15;
	  rows = NULL;
	  n_rows = 0;
	  col_sep = NULL;

	  while (str[0] != '}') {
	    D printf("got char '%c'\n",str[0]);
	    if ((str[0] == 'l') || (str[0] == 'c') || (str[0] == 'r')) {
	      n_columns ++;
	      col_widths = realloc(col_widths, n_columns * sizeof(int));
	      col_justify = realloc(col_justify, n_columns * sizeof(int));
	      col_sep = realloc(col_sep, n_columns * sizeof(char));
	      col_widths[n_columns - 1] = 0;
	      col_justify[n_columns - 1] = str[0];
	      col_sep[n_columns - 1] = ' ';
	      D printf("Creating column number %u, justification '%c'\n",
		       n_columns - 1, col_justify[n_columns - 1]);
	      
	    } else {
	      if ((str[0] == '|')) {
		D printf("setting col_sep[%u] = '%c'\n",n_columns - 1,str[0]);
		col_sep[n_columns - 1] = str[0];
	      }
	    }
	    str ++;
	  } 
	  D printf("done parsing begin tag\n");
	 
	  column  = 0;
	  n_rows ++;
	  rows = (char ***)realloc(rows, sizeof(char **) * n_rows);
	  rows[row] = (char **)calloc(sizeof(char *) , n_columns);
	  D printf("done creating data structures \n");
	  /* done creating data structures */
	}
      break;
    case '&':
      D printf("row %u column %u has length %u and is \"%s\"\n",
	       row, column, strlen(rows[row][column]), rows[row][column]);
      column ++;
      D printf("moving on to column %d\n",column);
      break;
    default:
      D printf("this is column contents\n");
      if (rows[row][column] != NULL) {
	D printf("this is NOT the first word in the cell\n");
	strcat(rows[row][column]," ");
	strcat(rows[row][column],string);
      } else {
	D printf("this IS the first word in the cell\n");
	rows[row][column] = strdup(string);
      }
      {
	int column_length;
	column_length = strlen(rows[row][column]);
	if (column_length > col_widths[column])
	  col_widths[column] = column_length;
      }
      break;
    }
    
  }

  {
    int i, j;
    D printf("\nOUTPUT\n");
    for (j = 0; j < n_columns; j++) {
 
      D printf(" %u ",col_widths[j]);
    }
    D printf("\n");

    for (i = 0; i < n_rows-1; i++) {
      for (j = 0; j < n_columns; j++) {
	char *foo;
	int k;
	if (j && (col_sep[j-1] != ' ')) printf("%c",col_sep[j-1]);

	for (k = 0; k<strlen(rows[i][j]); k++)
	  if (rows[i][j][k] < 32) {
	    rows[i][j][k] =0;
	    break;
	  }

	foo = justify(rows[i][j],col_justify[j],col_widths[j]+2,j == (n_columns - 1));
	
	printf("%s",foo);
				     
      }
      printf("\n");
    }
    
  }
   
  return 0;
}
