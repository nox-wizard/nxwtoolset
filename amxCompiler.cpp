/***************************************************************************
                          amxCompiler.cpp  -  description
                             -------------------
    begin                : Wed Dec 25 2002
    copyright            : (C) 2002 by Fabrizio Montesi
    email                : luxor@e-vinco.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#pragma warning (disable: 4244,4018,4761,4100,4125,4115)

void sc_printToGUI(char* buffer);

int sc_printf(const char *txt, ...)
{
        static char buffy[2*1024];

	va_list argptr;

	va_start( argptr, txt );
	vsprintf( buffy, txt, argptr );
	va_end( argptr );

        sc_printToGUI(buffy);
        
	return 0;
}


int sc_error(int number,char *message,char *filename,int firstline,int lastline,va_list argptr)
{
        static char *prefix[3]={ "Error", "Fatal", "Warning" };
        static char buffy[2048];

        if (number!=0) {
                char *pre;
                pre=prefix[number/100];
                if (firstline>=0)
                        sc_printf("\n%s:%d -- %d: %s [%03d]",filename,firstline,lastline,pre,number);
                else
                        sc_printf("\n%s:%d: %s [%03d]",filename,lastline,pre,number);
        }
        vsprintf(buffy,message,argptr);

        sc_printf(buffy);
        
        return 0;
}

#ifdef LINUX
#include "compiler/sclinux.h"
#endif
#include "compiler/sclib.c"


int compiler_main(int argc, char **argv)
{
        int ret;
	ret = sc_compile(argc, argv);
	return ret;
}
