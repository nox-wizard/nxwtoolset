/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Dec 25 15:37:44 CET 2002
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


 
#include "nxwtoolset.h"

int main(int argc, char **argv)
{
        QApplication a(argc, argv);
        NXWToolset *nxwtoolset = new NXWToolset(&a, "nxwtoolset");
        a.setMainWidget(nxwtoolset);
        nxwtoolset->show();
        return a.exec();
}
