#include "hashmap.ih"

/*
    returns

    o  idx of key if key was found
       In this case, the index of the key that was found is returned too.
    o  FAILED, if not found.
       In this case, the index that can be used to store key is returned.

    The hashitem vector may not be completely filled up.
    `prime' must be a prime, indicating the size of the map-vector.
*/

size_t hm_find(size_t *index, register HashItem **map, size_t prime,
                                                  char const *key)
{
    size_t hashValue = hm_pjw(key) % prime;
    size_t returnValue = FAILED;
    size_t idx;

    if (!hashValue)             /* make sure no initial hashvalue is 0,     */
        hashValue++;            /* as that invalidates add the hash rehash  */

    idx = hashValue;

    while (1)
    {
        register HashItem *atIdx = map[idx];

        switch ((size_t)atIdx)
        {
            case FREE:
                *index =
                    returnValue != FAILED ?
                        returnValue         /* return returnValue if set    */
                    :                       /* otherwise return idx         */
                        idx;
            return FAILED;                  /* indicate key not found */

            case REMOVED:
                if (returnValue == FAILED)  /* returned index not yet set */
                    returnValue = idx;      /* set it to REMOVED location */
            break;

            default:
                                            /* return idx of matching keys */
                if (!strcmp(key, atIdx->d_key))
                    return *index = idx;
            break;
        }
                                            /* element in use: rehash */
        idx = (idx + hashValue) % prime;
    }
}
