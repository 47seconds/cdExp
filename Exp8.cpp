#include <stdio.h>
#include <string.h>
#include <ctype.h>
int detectDataType(const char *input) {
    int len = strlen(input);
    int is_integer = 1;
    if (input[0] == '-' || input[0] == '+') {
        for (int i = 1; i < len; i++) {
            if (!isdigit(input[i])) {
                is_integer = 0;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < len; i++) {
            if (!isdigit(input[i])) {
                is_integer = 0;
                break;
            }
        }
    }
    if (is_integer) return 1;
    int dot_count = 0;
    int is_float = 1;
    if (input[0] == '-' || input[0] == '+') {
        for (int i = 1; i < len; i++) {
            if (input[i] == '.') {
                if (++dot_count > 1) {
                    is_float = 0;
                    break;
                }
            }
            else if (!isdigit(input[i])) {
                is_float = 0;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < len; i++) {
            if (input[i] == '.') {
                if (++dot_count > 1) {
                    is_float = 0;
                    break;
                }
            }
            else if (!isdigit(input[i])) {
                is_float = 0;
                break;
            }
        }
    }
    if (is_float && dot_count == 1) return 2;
    if (len == 3 && input[0] == '\'' && input[2] == '\'') return 3;
    if (len >= 2 && input[0] == '\"' && input[len - 1] == '\"') return 4;
    return 0;
}
int main()
{
    char val[100], name[100];
    int utype;
    printf("Enter the name of the variable: ");
    scanf("%s", name);
    printf("Enter the value for the variable: ");
    scanf("%s", val);
    printf("\nPlease select the data type you expect for the variable '%s':\n", name);
    printf("1\t\t2\t\t3\t\t4\t\t0\n");
    printf("Int\t\tFloat\tchar\tstring\tnone\n");
    scanf("%d", &utype);
    if (detectDataType(val) == utype) printf("Valid Data-type\n");
    else printf("Invalid data-type\n");
    return 0;
}