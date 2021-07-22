#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char str[1000000], str1[500000], str2[500000], str3[500000];
int length,                    // length of s[] including \0
Sufarr[1000000],   // suffix array for s[]
ranking[1000000], // rank[i] gives the rank (subscript) of s[i] in sa[]
lcp[1000000];  // lcp[i] indicates the number of identical prefix symbols
               // for s[sa[i-1]] and s[sa[i]]



int sufcomp(const void *xvpt, const void *yvpt)
{
    // Used in qsort call to generate suffix array.
    int *xpt = (int*)xvpt, *ypt = (int*)yvpt;

    return strcmp(&str[*xpt], &str[*ypt]);
}

void rankcomp(void)
{
    // Computes rank as the inverse permutation of the suffix array
    int i;

    for (i = 0; i<length; i++)
        ranking[Sufarr[i]] = i;
}

void computeLCP(void)
{
    //Kasai et al linear-time construction
    int h, i, j, k;

    h = 0;  // Index to support result that lcp[rank[i]]>=lcp[rank[i-1]]-1
    for (i = 0; i<length; i++)
    {
        k = ranking[i];
        if (k == 0)
            lcp[k] = (-1);
        else
        {
            j = Sufarr[k - 1];
            // Attempt to extend lcp
            while (i + h<length && j + h<length && str[i + h] == str[j + h])
                h++;
            lcp[k] = h;
        }
        if (h>0)
            h--;  // Decrease according to result
    }
}

int main()
{
    int i, j, k, m, dolpos, hashpos, Lcpos = 0, Lclen = 0;


    scanf("%s", str1);
    scanf("%s", str2);
    scanf("%s", str3);

    //Concatinate all Strings
    for (i = 0; str1[i] != '\0'; i++)
        str[i] = str1[i];

    dolpos= i;
    str[i++] = '$';
    for (j = 0; str2[j] != '\0'; j++)
        str[i + j] = str2[j];

    length = i + j;
    hashpos = length;
    str[length++] = '#';
    for (m = 0; str3[m] != '\0'; m++)
        str[length + m] = str3[m];

    printf(" \n", str);
    str[length + m] = '\0';
    length = length + m + 1;


    printf("n is %d\n", length);

    // Quick-and-dirty suffix array construction
    for (i = 0; i<length; i++)
        Sufarr[i] = i;
    qsort(Sufarr, length, sizeof(int), sufcomp);

    //Find LCP for the strings
    rankcomp();
    computeLCP();

    
    if (length<20000)
    {
        printf("i     sa    %-35.35s lcp  t s rank  lcp[rank] \n","Suffix");
        for (i = 0; i<length; i++)
            printf("%-4d %-5d %-35.35s %-5d %-1d %c  %-5d  %-5d\n",
                i, Sufarr[i], &str[Sufarr[i]], lcp[i],(Sufarr[i]<dolpos)?0:(Sufarr[i]<hashpos)?1:2, str[i], ranking[i], lcp[ranking[i]]);
    }
    

    //Find the Longest Common Substring
    int count = 0;
    int sc1 = 0,sc2 = 0, sc3 = 0;
    int a1 = 0, a2 = 0 , a3 = 0 , fin_x, fin_y, fin_z;
    int min_LCP = 0, max;
    for (i = 3; i < length; i++)
    {
        if (!(sc1 == 1 && sc2 == 1 && sc3 == 1))
        {
            if (Sufarr[i] < dolpos)
            {
                if(sc1==0)
                    count++;
                sc1 = 1;
                a1 = i;
            }
            else if (Sufarr[i] > dolpos && Sufarr[i] < hashpos)
            {
                if (sc2 == 0)
                    count++;
                sc2 = 1;
                a2 = i;
            }
            else if (Sufarr[i] > hashpos)
            {
                if (sc3 == 0)
                    count++;
                sc3 = 1;
                a3 = i;
            }
        }
        if (count==3)
        {
            int min, mid;

            if (a1<a2 && a1<a3)
            {
                sc1 = 0;
                min = a1;
            }
            else if (a2<a1 && a2<a3)
            {
                sc2 = 0;
                min = a2;
            }
            else
            {
                sc3 = 0;
                min = a3;
            }

            if (a1>a2 && a1>a3)
            {
                max = a1;
            }
            else if (a2>a1 && a2>a3)
            {
                max = a2;
            }
            else
            {
                max = a3;
            }

            if (a1 != max && a1 != min)
            {
                mid = a1;
            }
            else if (a2!= max && a2 != min)
            {
                mid = a2;
            }
            else if (a3 != max && a3 != min)
            {
                    mid = a3;
            }

            // calculating number of maximum common char in found three strings
            min_LCP = lcp[min+1];

            for(int S = min + 2; S<=max ; S++)
            {
                min_LCP = (min_LCP<lcp[S])?min_LCP:lcp[S];
            }

            if (min_LCP >= Lclen)
            {
                Lcpos = min;
                Lclen = min_LCP;
                    
                fin_x = min;
                fin_y = mid;
                fin_z = max;

                if(Lclen!=0)
                {
                    printf("Length %d, ", Lclen);
                    printf("x at %d, y ends at %d, z at %d\n", fin_x, fin_y, fin_z,i);
                    for (k = 0; k<Lclen; k++)
                    {
                        printf("%c", str[Sufarr[Lcpos] + k]);
                    }
                    printf("\n");
                }
            }
            count = count - 1;
        }
    }
    return 0;
}

