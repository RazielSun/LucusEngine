//
//  LucusUtils.h
//  LucusGame
//
//  Created by Alexander Kardakov on 23/02/2020.
//

#ifndef _LUCUS_ENGINE_UTILS_H
#define _LUCUS_ENGINE_UTILS_H

#include "LucusTypes.h"
#include <cctype>

namespace LucusEngine
{
    struct Utils
    {
        // from MOAI Hash function
        static u32 HashName( cc8* name )
        {
            u32 hash = 0;
            int shift = 0;
            
            for (int i = 0; i < 6; i++)
            {
                char c = name[ i ];
                if ( c && isalnum(c) )
                {
                    if (isalpha(c))
                    {
                        c = (char)toupper(c);
                        c = (c - 'A') + 10;
                    }
                    else
                    {
                        c = c - '0';
                    }
                    hash += (( c & 0x1f ) << shift );
                    shift += 5;
                }
                else
                {
                    break;
                }
            }
            return hash;
        }

        // from Internet
        static u32 HashString( cc8* str )
        {
            u32 hash = 0x811c9dc5;
            u32 prime = 0x1000193;

            for(size_t i = 0; i < strlen(str); ++i)
            {
                u8 value = str[i];
                hash = hash ^ value;
                hash *= prime;
            }

            return hash;
        }
    };
}

#endif /* _LUCUS_ENGINE_UTILS_H */
