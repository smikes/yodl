#include "chartab.ih"

void ct_destroy(void  *table)
{
    register char **cpp = (char **)table;
    register unsigned idx;

    for (idx = 0; idx < 256; idx++)             /* free elements            */
        free(*cpp++);

    free(table);                                /* free the table itself    */
}
