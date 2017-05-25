#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

unsigned int C, M;

struct stc {
double f;
unsigned int time;} *str = NULL;

struct stc* Test (int size)
{
    int i;
    struct stc* str;
    str = (struct stc*) malloc (sizeof(struct stc)*size);
    for (i = 0; i < size; i++)
    {
        printf("\nEnter %d, value:", i);
        scanf("%lf", &str[i].f);
        printf("\nEnter %d, time:", i);
        scanf("%u", &str[i].time);
    }
    return str;
}

struct stc* ArrayCopy (struct stc* str, int size )
{
    struct stc* str2;
    str2 = (struct stc*) malloc (sizeof(struct stc)* size);
    int i = 0;
    for (i = 0; i < size; i++)
        str2 [i] = str [i];
    return str2;
}

void swap(struct stc *a, struct stc *b)
{
    struct stc t;
    t = *a;
    *a = *b;
     *b = t;
}

void bubbleSort(struct stc* a, int size)
{
    int i;
    char flag;
    do {
        flag = 0;
        for (i = 1; i < size; i++) {
            if (a[i].time < a[i-1].time) {
                swap(&a[i], &a[i-1]);
                flag = 1;
                M++;
            }
            C++;
        }
    } while (flag);
}

void qs(struct stc* s_arr, int first, int last)
{
    int i = first, j = last, x = s_arr[(first + last) / 2].time;

    do {
        while (s_arr[i].time < x)
        {
            i++;
            C++;
        }
        while (s_arr[j].time > x)
        {
            j--;
            C++;
        }

        if(i <= j) {
            if (s_arr[i].time > s_arr[j].time) {
                    swap(&s_arr[i], &s_arr[j]);
                    C++;
                    M++;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        qs(s_arr, i, last);
    if (first < j)
        qs(s_arr, first, j);
}

void InsertionSort(struct stc* mass, int size)
{
    struct stc newElement;
    int location,i;

    for ( i = 1; i < size; i++)
    {
        newElement = mass[i];
        location = i - 1;
        while(location >= 0 && mass[location].time > newElement.time)
        {
            C++;
            mass[location+1] = mass[location];
            M++;
            location = location - 1;
        }
        mass[location+1] = newElement;
        C++;
        M++;
    }
}

typedef struct _node
{
    struct stc key;
    struct _node *left, *right; } node;

node* createnode(struct stc val)
{
    node* nnode = (node*) malloc (sizeof(node));
    nnode->key = val;
    nnode->left = NULL;
    nnode->right = NULL;
    return nnode;
}

node* add_tree(node *root, struct stc val)
{
    C++;
    if (NULL == root)
    {
        root = createnode(val);
        M++;
    }
    if (val.time < root->key.time )
    {
        if (NULL == root->left)
            root->left = createnode(val);
        else
            add_tree(root->left, val);
    }
    if (val.time > root->key.time)
    {
        if (NULL == root->right)
            root->right = createnode(val);
        else
            add_tree(root->right, val);
    }
    return root;
}

unsigned int find_tree(node *root, unsigned int search)
{
    C++;
    if (NULL == root)
    {
        return -1;
        printf("%d is not present in array.\n", search);
    }
    if (search == root->key.time)
    {
        printf("%d found\n", root->key.time);
        return root->key.time;
    }
    if (search < root->key.time)
        return find_tree(root->left, search);
    if (search > root->key.time)
        return find_tree(root->right, search);
}

void print_tree(node *root)
{
    if (root != NULL) {
        print_tree(root->left);
        printf("%0.9lf\t %u \t\n", root->key.f, root->key.time);
        print_tree(root->right);
    }
}

node* BinSort (struct stc* a, int size)
{
    int i = 0;
    node *mnode = NULL;
    while (i < size)
    {
        mnode = add_tree(mnode, a[i]);
        M++;
        i++;
    }
    //print_tree(mnode);
    return mnode;
}

FILE* OpenFile (FILE* file)
{
    char fname [50];
    while (file == NULL)
    {
        printf("Enter filename or file path (Example: file.dat or C:\\\\Users\\\\Desktop\\\\file.dat):");
        scanf("%s", fname);
        file=fopen(fname, "rb");
    }
    return file;
}

void printarray (struct stc* str, int size)
{
    int j;
    printf(" In ascending order:\t\t   In descending order: \n");
    for(j = 0; j < size; j++){
        printf("%0.9lf\t %u \t |\t%0.9lf\t %u\n",(str[j].f), (str[j].time), (str[size-j-1].f), (str[size-j-1].time));
    }
}

unsigned int LinSearch (struct stc* str, int size, unsigned int search )
{
    int i;
       for (i = 0; i < size; i++)
   {
      if (str[i].time == search)     /* if required element found */
      {
         printf("%d is present at location %d.\n", str[i].time , i);
         break;
      }
      C++;
   }
   if (i == size)
      printf("%d is not present in array.\n", search);

   return i;
}

int InterpolationS (unsigned int search, struct stc* str, int lo, int hi) {
   int mid = -1;
   int comparisons = 1;
   int index = -1;

   while((str[hi].time != str[lo].time) && (search >= str[lo].time) && (search <= str[hi].time)) {
      /*printf("\nComparison %d  \n" , comparisons ) ;
      printf("lo : %d, str[%d].time = %d\n", lo, lo, str[lo].time);
      printf("hi : %d, str[%d].time = %d\n", hi, hi, str[hi].time);*/

      comparisons++;

      // probe the mid point
      //mid = lo + (((double)(hi - lo) / (str[hi].time - str[lo].time)) * (search - str[lo].time));
      mid = lo + ((search - str[lo].time) * (hi - lo) / (str[hi].time - str[lo].time));
      //printf("mid = %d\n",mid);

      // data found
      if(str[mid].time == search) {
         index = mid;
         break;
      } else {
         if(str[mid].time < search) {
            // if data is larger, data is in upper half
            lo = mid + 1;
         } else {
            // if data is smaller, data is in lower half
            hi = mid - 1;
         }
      }
   }

   printf("\nTotal comparisons made: %d", --comparisons);
   return index;
}

int binarysearch(int a, struct stc* str, int n)
{
    int low, high, middle;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (a < str[middle].time)
        {
            C++;
            high = middle - 1;
        }
        else if (a > str[middle].time)
        {
            low = middle + 1;
            C++;
        }
        else
        {
            printf("%d is present at location %d.\n", str[middle].time , middle);
            return middle;
        }
        M++;
    }
    return -1;
}

int main (void)
{
    int i = 0, size;
    unsigned int search;
   // double min;
    FILE *file;
    int meth;

    printf("\nChoose method:\n1)Read from file\n2)Enter from the keyboard\n");
    scanf("%d", &meth);
    switch (meth)
    {
        case 1:
            file = fopen("aba1_1.csv", "rb");
            if (file == NULL)  file = OpenFile(file);

            str=(struct stc*) malloc (sizeof(struct stc));
            while (fscanf (file, "%lf%*c%u", &(str[i].f), &(str[i].time))!=EOF)
            {
                i++;
                str=(struct stc*) realloc (str,(i+1)*sizeof(struct stc));
            }
            i--;
            size = i;
            fclose(file);
        break;

        case 2:
            printf("\nNumber of values:");
            scanf("%d", &size);
            str = Test(size);
        break;

        default:
            printf( "Error.\n" );
            exit(-1);
    }

    struct stc* tmpstr = NULL;
    clock_t begin;
    clock_t end;

    M = 0;
    C = 0;
    printf("\n\tBubble sort\n");
    tmpstr = ArrayCopy(str, size);
    begin = clock();
    bubbleSort(tmpstr, size);
    end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Spent for Sorting: %lf s\n", time_spent);
    printf("Comparisons=%u\nMove operations=%u\n", C, M);

    M = 0;
    C = 0;
    printf("\n\tInsertion sort");
    tmpstr = ArrayCopy(str, size);
    begin = clock();
    InsertionSort(tmpstr, size);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime Spent for Sorting: %lf s\n", time_spent);
    printf("Comparisons=%u\nMove operations=%u\n", C, M);

    M = 0;
    C = 0;
    printf("\n\tBinary sort\n");
    node* mnode;
    tmpstr = ArrayCopy(str, size);
    begin = clock();
    mnode = BinSort(tmpstr, size);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Spent for Sorting: %lf s\n", time_spent);
    printf("Comparisons=%u\nMove operations=%u\n", C, M);

    M = 0;
    C = 0;
    printf("\n\tQuick sort\n");
    tmpstr = ArrayCopy(str, size);
    begin = clock();
    qs(tmpstr, 0, size-1);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Spent for Sorting: %lf s\n", time_spent);
    printf("Comparisons=%u\nMove operations=%u\n", C, M);

    printf("\nChoose method of enter search value:\n1)Random\n2)Enter from the keyboard\n");
    scanf("%d", &meth);
    switch (meth)
    {
        case 1:
            srand(time(NULL));
            i = rand()%size;
            search = str[i].time;
        break;

        case 2:
            printf("\nSearch value:");
            scanf("%d", &search);
        break;

        default:
            printf( "Error.\n" );
            exit(-1);
    }


    printf("\n\tLinear search\n");
    qs(str, 0, size-1);
    C = 0;
    begin = clock();
    LinSearch(str, size, search);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Spent for Searching: %lf s\n", time_spent);
    printf("Comparisons=%u\n ", C);


    C = 0;
    printf("\n\tTree search\n");
    tmpstr = ArrayCopy(str, size);
    begin = clock();
    find_tree(mnode, search);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Spent for Searching: %lf s\n", time_spent);
    printf("Comparisons=%u\n", C);

    M = 0;
    C = 0;
    printf("\n\tInterpolation search");
    //tmpstr = ArrayCopy(str, size);
    begin = clock();
    i = InterpolationS(search, str, 0, size-1);
     printf("\nElement found at location: %d\n" ,i);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Spent for Searching: %lf s\n", time_spent);

    M = 0;
    C = 0;
    printf("\n\tBinary search\n");
    tmpstr = ArrayCopy(str, size);
    begin = clock();
    binarysearch(search, str, size);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Spent for Searching: %lf s\n", time_spent);
    printf("Comparisons=%u\n ", C);

    printf("\nPrint array?\n1)y\n2)n\n");
    scanf("%d", &meth);
    if (meth == 1)
        printarray(str, size);

    free(str);
    return 0;
}



