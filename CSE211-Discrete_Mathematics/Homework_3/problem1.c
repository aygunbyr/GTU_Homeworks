#include <stdio.h>
#include <stdlib.h> // standard lib
#include <string.h> // for string operations, such as comparison

int split_elements(char c[], char elements[][4]);
int check_relations(FILE *of, char elements[][4], char relation_left[][4], char relation_right[][4], int element_count, int relation_count);
int check_reflexivity(FILE *of, char elements[][4], char relation_left[][4], char relation_right[][4], int element_count, int relation_count);
int check_symmetry(FILE *of, char relation_left[][4], char relation_right[][4], int relation_count);
int check_antisymmetry(FILE *of, char relation_left[][4], char relation_right[][4], int relation_count);
int check_transitivity(FILE *of, char relation_left[][4], char relation_right[][4], int relation_count);
int sirali_mi(char relation_left[][4], char relation_right[][4], int n);
int sirala(char relation_left[][4], char relation_right[][4], int n);
int remove_reflexive_transitive_pairs(char relation_left[][4], char relation_right[][4], int * relation_count);
void make_reflexive(char elements[][4], char relation_left[][4], char relation_right[][4], int * relation_count, int element_count);
void make_antisym(char relation_left[][4], char relation_right[][4], int * relation_count);
void make_transitive(char relation_left[][4], char relation_right[][4], int * relation_count);


int main() {
    char c[1000], temp[10];
    FILE *fp;
    FILE *of;
    int element_count, relation_count, i, j, k, is_reflexive, is_symmetric, is_antisymmetric, is_transitive, is_valid, siralimi;
    char elements[20][4]; // partially filled array
    char relation_left[20][4], relation_right[20][4]; // partially filled array
    fp = fopen("input.txt", "r");
    of = fopen("output.txt", "w");

    while (!feof(fp))
    {
        // Get relation count from first line of file
        relation_count = atoi(fgets(c, 1000, fp));
        // To avoid from empty lines
        if(strlen(c) == 1)
            break;

        // Get elements from next line
        fgets(c,1000,fp);
        
        element_count = split_elements(c, elements);

        fprintf(of,"n\n");

        // Get relations line by line
        for(i=0; i<relation_count; i++)
        {
            fgets(c, 1000, fp);
            for(j=0; c[j] != ','; j++)
            {
                relation_left[i][j] = c[j];
            }
            relation_left[i][j] = '\0';
            j++; // skip comma
            for(k=0; c[j+k] != '\n' && c[j+k] != '\0'; k++)
            {
                relation_right[i][k] = c[j+k];
            }
            relation_right[i][k] = '\0';
            //fprintf(of,"(%s,%s)", relation_left[i], relation_right[i]);
        }

        is_valid = check_relations(of, elements, relation_left, relation_right,  element_count,  relation_count);

        if( is_valid == 1)
        {
            //fprintf(of,"\nReflexive:");
            is_reflexive = check_reflexivity(of,elements, relation_left, relation_right,  element_count, relation_count);
            /*
            if(is_reflexive)
                fprintf(of,"Yes, all elements are present.");
                */
          
            //fprintf(of,"\nSymmetric:");
            is_symmetric = check_symmetry(of,relation_left, relation_right, relation_count);
            /*
            if(is_symmetric)
                fprintf(of,"Yes, all elements are present.");
            */
              
            //fprintf(of,"\nAntisymmetric:");
            is_antisymmetric = check_antisymmetry(of,relation_left, relation_right, relation_count);
            /*
            if(is_antisymmetric==0)
                fprintf(of,"No, all elements are NOT present.");
            */
            //fprintf(of,"\nTransitive:"); 
            is_transitive = check_transitivity(of,relation_left, relation_right, relation_count);


            siralimi = sirali_mi(relation_left, relation_right, relation_count);
            if(siralimi==0)
            {
                // If relation set is unsorted, sort
                sirala(relation_left,  relation_right,  relation_count);
            }

            // If not reflexive, make reflexive
            if(is_reflexive == 0)
            {
                make_reflexive(elements, relation_left, relation_right, &relation_count,  element_count);
                sirala(relation_left, relation_right, relation_count);
            }

            // Make antisymetric for ex. there are a,b and b,a remove one of them
            make_antisym(relation_left, relation_right, &relation_count);
            sirala(relation_left, relation_right, relation_count);

            // If not transitive, add pairs and make transitive
            make_transitive(relation_left, relation_right, &relation_count);
            sirala(relation_left, relation_right, relation_count);
           
            fprintf(of, "POSET: ");
            for(i=0; i<relation_count; i++)
            {
                fprintf(of, "(%s, %s)", relation_left[i], relation_right[i]);
                if(i!=relation_count-1)
                    fprintf(of, ",");
                fprintf(of, " ");
            }
            fprintf(of, "\n");

            // Remove reflexive and transitive pairs
            remove_reflexive_transitive_pairs(relation_left, relation_right, &relation_count);

            // Print the set for hasse diagram
            for(i=0; i<relation_count; i++)
            {
                fprintf(of, "%s,%s\n", relation_left[i], relation_right[i]);
            }
        }
        else if( is_valid == 0)
        {
            fprintf(of, "Relations are invalid.\n");
        }
    }

    fclose(fp);
    fclose(of);

    return 0;
}

int split_elements(char c[], char elements[][4]) {
    int element=0,i,j;
    for(i=0; c[i]!='\n' && c[i]!='\0'; i++)
    {
        for(j=0; c[i+j]!=',' && c[i+j]!='\n' && c[i+j]!='\0'; j++)
        {
            elements[element][j] = c[i+j]; 
        }
        elements[element][j] = '\0';
        i += j;
        element++;
    }
    elements[element][0] = '\0';
    return element;
}

int check_relations(FILE *of, char elements[][4], char relation_left[][4], char relation_right[][4], int element_count, int relation_count)
{
    int i, j, number_of_valid_elements=0;
    for(i=0; i<relation_count; i++) {
        for(j=0; j<element_count; j++)
        {
            if( strcmp(relation_left[i], elements[j]) == 0)
                number_of_valid_elements++;
            if( strcmp(relation_right[i], elements[j]) == 0)
                number_of_valid_elements++;
        }
    }

    // If every element in relations are from set elements, relations are valid
    if(number_of_valid_elements == relation_count * 2)
        return 1;
    else // If some are not, relations are invalid
        return 0; 
}

int check_reflexivity(FILE *of, char elements[][4], char relation_left[][4], char relation_right[][4], int element_count, int relation_count)
{
    int i, j, found;
    for(i=0; i<element_count; i++)
    {
        found=0;
        for(j=0; j<relation_count; j++)
        {
            if( strcmp(relation_left[j], elements[i]) == 0 && strcmp(relation_right[j], elements[i]) == 0)
                found=1;
        }
        if(found==0)
        {
            // Not printing on HW3
            //fprintf(of,"No, since (%s,%s) is not found.", elements[i], elements[i]);
            return 0;
        }
    }
    return 1; // so this relation is reflexive
}

int check_symmetry(FILE *of, char relation_left[][4], char relation_right[][4], int relation_count) 
{
    int i, j, symmetric, flag=1;

    for(i=0; i<relation_count; i++)
    {
        symmetric=0;
        for(j=0; j<relation_count; j++)
        {
            if(strcmp(relation_left[i], relation_right[j]) == 0 && strcmp(relation_left[j], relation_right[i]) == 0)
            {
                symmetric=1;
            }
        }
        if(symmetric==0)
        {
            // Not printing on HW3
            //fprintf(of,"No, (%s,%s) is found whereas (%s,%s) is not found.", relation_left[i], relation_right[i], relation_right[i], relation_left[i]);
            return 0;
        }
    }
    return flag;
}


int check_antisymmetry(FILE *of, char relation_left[][4], char relation_right[][4], int relation_count) 
{
    int i, j, antisymmetric, flag=1, count_of_reflexives=0;

    for(i=0; i<relation_count; i++)
    {
        antisymmetric=1;
        // Check if not a reflexive relation
        if(strcmp(relation_left[i], relation_right[i]) != 0)
        {
            for(j=0; j<relation_count; j++)
            {
                if(strcmp(relation_left[i], relation_right[j]) == 0 && strcmp(relation_left[j], relation_right[i]) == 0)
                {
                    antisymmetric=0;
                }
            }
            if(antisymmetric==1)
            {
                // Not printing on HW3
                //fprintf(of,"Yes, (%s,%s) is found whereas (%s,%s) is not found.", relation_left[i], relation_right[i], relation_right[i], relation_left[i]);
                return 1;
            }
        }
        else
            count_of_reflexives++;
    }
    if(count_of_reflexives==relation_count) // All relations are reflexive
    {
        // Reflexive elements does not break antisymmetry
        // Not printing on HW3
        // fprintf(of,"Yes, all elements are present.");
        return 1;
    }
    else // All elements not reflexive and antisymmetric not found, so it is not antisymmetric
        return 0;

}

int check_transitivity(FILE *of, char relation_left[][4], char relation_right[][4], int relation_count) 
{
    int i, j, k, is_found, transitive_count=0, transitive_relations[3], not_transitive_relations[2];
    int any_starts_with_b, b_transitive, third_found, is_transitive;

    for(i=0; i<relation_count; i++)
    {
        is_transitive=0;
        
        if( strcmp(relation_left[i], relation_right[i]) == 0)
        {
            // If a,a it is reflexive so transitive also
            is_transitive=1;
        }
        else
        {
            any_starts_with_b=0;
            b_transitive=0;
            for(j=0; j<relation_count; j++)
            {
                if( strcmp(relation_right[i], relation_left[j]) == 0 )
                {
                    any_starts_with_b=1;
                    if( strcmp(relation_left[j], relation_right[j]) == 0)
                    {
                        // It is reflexive and also transitive
                        b_transitive = 1;
                    }
                    else
                    {
                        // There is a second relation and it is not reflexive
                        third_found=0;
                        for(k=0; k<relation_count; k++)
                        {
                            if( strcmp(relation_right[j], relation_right[k]) == 0 && strcmp(relation_left[k], relation_left[i]) == 0 && i != k)
                            {
                                third_found=1;
                                transitive_relations[0]=i;
                                transitive_relations[1]=j;
                                transitive_relations[2]=k;
                            }
                        }
                        if(third_found==1)
                        {
                            // a,b b,c and a,c found
                            is_transitive=1;
                        }
                        else if(third_found==0)
                        {
                            is_transitive=0;
                            not_transitive_relations[0]=i;
                            not_transitive_relations[1]=j;
                        }
                    }
                }

            }
            if(any_starts_with_b==0 || b_transitive == 1)
            {
                is_transitive=1;
            }

        }
        if(is_transitive)
            transitive_count++;
    }
             
    // Finish
    /* Not printing on HW3
    if(transitive_count == relation_count && third_found == 1)
    fprintf(of,"Yes, (%s,%s) is found since (%s,%s) and (%s,%s) are found.", relation_left[transitive_relations[2]], relation_right[transitive_relations[2]], relation_left[transitive_relations[0]], relation_right[transitive_relations[0]], relation_left[transitive_relations[1]], relation_right[transitive_relations[1]]);
    else if(transitive_count == relation_count) {
        fprintf(of,"Yes, all elements are present.");
    }
    else
        fprintf(of,"No, (%s,%s) is NOT found whereas (%s,%s) and (%s,%s) are found.", relation_left[not_transitive_relations[0]], relation_right[not_transitive_relations[1]], relation_left[not_transitive_relations[0]], relation_right[not_transitive_relations[0]], relation_left[not_transitive_relations[1]], relation_right[not_transitive_relations[1]]);
    */

    return is_transitive;

}

int sirali_mi(char relation_left[][4], char relation_right[][4], int n) {
    int i;

    for(i=0; i<n; i++)
    {
        if( strcmp(relation_left[i], relation_left[i+1]) > 0 ||
        (strcmp(relation_left[i], relation_left[i+1]) == 0 && strcmp(relation_right[i], relation_right[i+1]) > 0
        ))
            return 0;
    }
    return 1;
}

int sirala(char relation_left[][4], char relation_right[][4], int n) {
    int i, j;
    char temp[4];
    // bubble sort
    for (i = 0; i < n-1; i++)  
    {
        for (j = 0; j < n-i-1; j++) 
        {
            if( (strcmp(relation_left[j], relation_left[j+1]) > 0) || 
                (strcmp(relation_left[j], relation_left[j+1]) == 0 && strcmp(relation_right[j], relation_right[j+1]) > 0)
            )
            {
                // swap pairs
                strcpy(temp, relation_left[j]);
                strcpy(relation_left[j], relation_left[j+1]);
                strcpy(relation_left[j+1], temp);
                strcpy(temp, relation_right[j]);
                strcpy(relation_right[j], relation_right[j+1]);
                strcpy(relation_right[j+1], temp);
            }
        }
    }

    return 0;          
}


int remove_reflexive_transitive_pairs(char relation_left[][4], char relation_right[][4], int * relation_count) {
    int i, j, k, relation_count_then;

    relation_count_then = *relation_count;

    // Remove reflexive pairs at first
    for(i=0; i<*relation_count; i++)
    {
        if(strcmp(relation_left[i], relation_right[i]) == 0)
        {
            strcpy(relation_left[i], "|");
            strcpy(relation_right[i], "|");
            relation_count_then--;
        }
    }

    // Update array after removal
    sirala(relation_left,  relation_right, *relation_count);
    *relation_count = relation_count_then;

    // Remove transitive pairs
    for(i=0; i<*relation_count; i++)
    {
        for(j=0; j<*relation_count; j++)
        {
            for(k=0; k<*relation_count; k++)
            {
                if(i!=k && i!=j && j!=k)
                {
                    if(
                        strcmp(relation_left[i], relation_left[k]) == 0 &&
                        strcmp(relation_left[j], relation_right[i]) == 0 &&
                        strcmp(relation_right[k], relation_right[j]) == 0 &&
                        strcmp(relation_left[i], "|") != 0 &&
                        strcmp(relation_left[j], "|") != 0 &&
                        strcmp(relation_left[k], "|") != 0
                        // Transitive and not marked before
                    )
                    {
                        // Mark transitive pairs to be removed then
                        strcpy(relation_left[i], "|");
                        strcpy(relation_right[i], "|");
                        strcpy(relation_left[j], "|");
                        strcpy(relation_right[j], "|");
                        strcpy(relation_left[k], "|");
                        strcpy(relation_right[k], "|");
                        relation_count_then = relation_count_then - 3;
                    }
                }
            }
        }
    }
    
    // Update array after removal again
    sirala(relation_left,  relation_right, *relation_count);
    *relation_count = relation_count_then;

    return 0;

}


void make_reflexive(char elements[][4], char relation_left[][4], char relation_right[][4], int * relation_count, int element_count)
{
    int i, j, is_pair_found, new_pair_index;
    for(i=0; i<element_count; i++)
    {
        is_pair_found = 0;
        for(j=0; j<*relation_count; j++)
        {
            if( strcmp(relation_left[j], elements[i]) == 0 && strcmp(relation_right[j], elements[i]) == 0 )
                is_pair_found = 1;
        }
        if(is_pair_found == 0)
        {
            new_pair_index = *relation_count;
            strcpy(relation_left[new_pair_index], elements[i]);
            strcpy(relation_right[new_pair_index], elements[i]);
            (*relation_count)++;
        }
    }
}

void make_antisym(char relation_left[][4], char relation_right[][4], int * relation_count) {
    int i, j;
    for(i=0; i<*relation_count; i++)
    {
        // Check reflexivity and do not remove reflexive pairs
        if( strcmp(relation_left[i], relation_right[i]) != 0 )
        {
            for(j=0; j<*relation_count; j++)
            {
                if( strcmp(relation_left[i], relation_right[j]) == 0 && strcmp(relation_left[j], relation_right[i]) == 0 )
                {
                    // Mark with '|' character to be removed later.
                    strcpy(relation_left[j], "|");
                    strcpy(relation_right[j], "|");
                    sirala(relation_left, relation_right, *relation_count);
                    (*relation_count)--;
                }
            }
        }
    }
}

void make_transitive(char relation_left[][4], char relation_right[][4], int * relation_count) 
{
    int i, j, k, is_third_pair_found, new_pair_index;

    for(i=0; i<*relation_count; i++)
    {
        // Check reflexivity
        if( strcmp(relation_left[i], relation_right[i]) != 0 )
        {
            for(j=0; j<*relation_count; j++)
            {
                // Check reflexivity
                if( strcmp(relation_left[j], relation_right[j]) != 0 )
                {
                    if( strcmp(relation_right[i], relation_left[j]) == 0  )
                    {
                        is_third_pair_found=0;
                        for(k=0; k<*relation_count; k++)
                        {
                            // If third pair found, it is transitive
                            if( strcmp(relation_left[i], relation_left[k]) == 0 && strcmp(relation_right[j], relation_right[k]) == 0 )
                                is_third_pair_found=1;
                        }
                        if(is_third_pair_found==0)
                        {
                            // If third not found, add third one to make relation transitive.
                            new_pair_index = *relation_count;
                            strcpy(relation_left[new_pair_index], relation_left[i]);
                            strcpy(relation_right[new_pair_index], relation_right[j]);
                            (*relation_count)++;
                        }
                    }
                }
            }
        }
    }
}