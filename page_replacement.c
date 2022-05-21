#include <stdio.h>
#define MAX_NUMBER_OF_PAGE_REFERENCES 100000

int number_of_pages_allocated_to_process;
int number_of_page_faults = 0;
char replacement_algorithm[7];
int page_references[MAX_NUMBER_OF_PAGE_REFERENCES];
int number_of_page_references = 0;

int increment_pointer(int pointer)
{
    pointer++;
    if (pointer == number_of_pages_allocated_to_process)
        return 0;
    else
        return pointer;
}

int search(int array[number_of_pages_allocated_to_process], int target, int length)
{
    if (length == 0)
        return 0;

    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        if (array[i] == target)
            return 1;
    }

    return 0;
}

int find_index(int array[number_of_pages_allocated_to_process], int target)
{
    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        if (array[i] == target)
            return i;
    }
}

int max(int array[], int length)
{
    int max_index = 0;
    int max = array[0];

    for (int i = 1; i < length; i++)
        if (array[i] > max)
        {
            max = array[i];
            max_index = i;
        }

    return max_index;
}

int min(int array[], int length)
{
    int min_index = 0;
    int min = array[0];

    for (int i = 1; i < length; i++)
        if (array[i] < min)
        {
            min = array[i];
            min_index = i;
        }

    return min_index;
}

int find_least_optimal(int array[number_of_pages_allocated_to_process], int current_i)
{
    int index[number_of_pages_allocated_to_process];

    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        index[i] = -1;
        for (int j = current_i + 1; j < number_of_page_references; j++)
        {
            if (array[i] == page_references[j])
            {
                index[i] = j;
                break;
            }
        }
        if (index[i] == -1)
            return i;
    }

    return max(index, number_of_pages_allocated_to_process);
}

int find_lru(int array[number_of_pages_allocated_to_process], int current_i)
{
    int index[number_of_pages_allocated_to_process];

    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        for (int j = current_i - 1; j >= 0; j--)
        {
            if (array[i] == page_references[j])
            {
                index[i] = j;
                break;
            }
        }
    }

    return min(index, number_of_pages_allocated_to_process);
}

void fifo()
{
    int current_pages[number_of_pages_allocated_to_process];
    int length = 0;
    int number_of_pages_skipped = 0;
    int pointer = 0;
    int is_found;

    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        current_pages[i] = -1;
    }

    for (int i = 0; length != number_of_pages_allocated_to_process; i++)
    {
        if (page_references[i] > 9)
            printf("%d     ", page_references[i]);
        else
            printf("0%d     ", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            number_of_pages_skipped++;
            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            current_pages[pointer] = page_references[i];
            pointer = increment_pointer(pointer);
            length++;

            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }

    for (int i = number_of_pages_allocated_to_process + number_of_pages_skipped; i < number_of_page_references; i++)
    {
        if (page_references[i] > 9)
            printf("%d", page_references[i]);
        else
            printf("0%d", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            printf("     ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            number_of_page_faults++;
            current_pages[pointer] = page_references[i];
            pointer = increment_pointer(pointer);

            printf(" F   ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }
}

void optimal()
{
    int current_pages[number_of_pages_allocated_to_process];
    int length = 0;
    int number_of_pages_skipped = 0;
    int is_found;
    int least_optimal;

    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        current_pages[i] = -1;
    }

    for (int i = 0; length != number_of_pages_allocated_to_process; i++)
    {
        if (page_references[i] > 9)
            printf("%d     ", page_references[i]);
        else
            printf("0%d     ", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            number_of_pages_skipped++;
            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            current_pages[length] = page_references[i];
            length++;

            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }

    for (int i = number_of_pages_allocated_to_process + number_of_pages_skipped; i < number_of_page_references; i++)
    {
        if (page_references[i] > 9)
            printf("%d", page_references[i]);
        else
            printf("0%d", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            printf("     ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            number_of_page_faults++;
            least_optimal = find_least_optimal(current_pages, i);
            current_pages[least_optimal] = page_references[i];

            printf(" F   ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }
}

void lru()
{
    int current_pages[number_of_pages_allocated_to_process];
    int length = 0;
    int number_of_pages_skipped = 0;
    int is_found;
    int lru;

    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        current_pages[i] = -1;
    }

    for (int i = 0; length != number_of_pages_allocated_to_process; i++)
    {
        if (page_references[i] > 9)
            printf("%d     ", page_references[i]);
        else
            printf("0%d     ", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            number_of_pages_skipped++;
            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            current_pages[length] = page_references[i];
            length++;

            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }

    for (int i = number_of_pages_allocated_to_process + number_of_pages_skipped; i < number_of_page_references; i++)
    {
        if (page_references[i] > 9)
            printf("%d", page_references[i]);
        else
            printf("0%d", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            printf("     ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            number_of_page_faults++;
            lru = find_lru(current_pages, i);
            current_pages[lru] = page_references[i];

            printf(" F   ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }
}

void clk()
{
    int current_pages[number_of_pages_allocated_to_process];
    int used_bits[number_of_pages_allocated_to_process];
    int length = 0;
    int number_of_pages_skipped = 0;
    int pointer = 0;
    int is_found;

    for (int i = 0; i < number_of_pages_allocated_to_process; i++)
    {
        current_pages[i] = -1;
    }

    for (int i = 0; length != number_of_pages_allocated_to_process; i++)
    {
        if (page_references[i] > 9)
            printf("%d     ", page_references[i]);
        else
            printf("0%d     ", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            number_of_pages_skipped++;
            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            current_pages[pointer] = page_references[i];
            used_bits[pointer] = 1;
            pointer = increment_pointer(pointer);
            length++;

            for (int j = 0; j < length; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }

    for (int i = number_of_pages_allocated_to_process + number_of_pages_skipped; i < number_of_page_references; i++)
    {
        if (page_references[i] > 9)
            printf("%d", page_references[i]);
        else
            printf("0%d", page_references[i]);

        is_found = search(current_pages, page_references[i], length);

        if (is_found)
        {
            used_bits[find_index(current_pages, page_references[i])] = 1;
            printf("     ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
        else
        {
            number_of_page_faults++;

            while (used_bits[pointer] != 0)
            {
                used_bits[pointer] = 0;
                pointer = increment_pointer(pointer);
            }

            current_pages[pointer] = page_references[i];
            used_bits[pointer] = 1;
            pointer = increment_pointer(pointer);

            printf(" F   ");
            for (int j = 0; j < number_of_pages_allocated_to_process; j++)
            {
                if (current_pages[j] > 9)
                    printf("%d ", current_pages[j]);
                else
                    printf("0%d ", current_pages[j]);
            }
            printf("\n");
        }
    }
}

int main()
{
    scanf("%d", &number_of_pages_allocated_to_process);
    scanf("%s", &replacement_algorithm);

    for (int i = 0; i < MAX_NUMBER_OF_PAGE_REFERENCES; i++)
    {
        int j;
        scanf("%d", &j);
        if (j == -1)
            break;
        else
        {
            number_of_page_references++;
            page_references[i] = j;
        }
    }

    printf("Replacement Policy = %s\n", replacement_algorithm);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    if (replacement_algorithm[0] == 'F' && replacement_algorithm[1] == 'I' && replacement_algorithm[2] == 'F' && replacement_algorithm[3] == 'O')
        fifo();
    else if (replacement_algorithm[0] == 'O' && replacement_algorithm[1] == 'P' && replacement_algorithm[2] == 'T' && replacement_algorithm[3] == 'I' && replacement_algorithm[4] == 'M' && replacement_algorithm[5] == 'A' && replacement_algorithm[6] == 'L')
        optimal();
    else if (replacement_algorithm[0] == 'L' && replacement_algorithm[1] == 'R' && replacement_algorithm[2] == 'U')
        lru();
    else if (replacement_algorithm[0] == 'C' && replacement_algorithm[1] == 'L' && replacement_algorithm[2] == 'O' && replacement_algorithm[3] == 'C' && replacement_algorithm[4] == 'K')
        clk();
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", number_of_page_faults);
    return 0;
}