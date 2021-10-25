#include "main_aux.h"

int validate_args(int argc, char *argv[])
{
    int i;
    if (argc < 3)
    {
        return -1;
    }
    for (i = 0; i < argc; i++)
    {
        if (argv[i] == NULL || argv[i][0] == 0)
        {
            return -1;
        }
    }

    if (argc > 3)
    {
        if (strlen(argv[3]) > strlen("65536"))
        {
            return -1;
        }
        for (i = 0; i < strlen(argv[3]); i++)
        {
            if (!isdigit(argv[i]))
            {
                return -1;
            }
        }
    }
    return 0;
}


