#include "yodlpost.h"

void handle_xml_tocentry(long offset, HashItem *item)
{
    file_copy2offset(global.d_out, postqueue_istream(), offset);
    fprintf(global.d_out, "<a id=\"l%u\"></a>\n",
                                        (unsigned)hashitem_value(item));
}
