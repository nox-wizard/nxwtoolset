/***************************************************************************
                          settings.h  -  description
                             -------------------
    begin                : Wed Dec 25 15:37:44 CET 2002
    copyright            : (C) 2002 by Fabrizio Montesi
    email                : luxor@eos-software.it
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

class NXWSettingsDialog : public QDialog
{
public:
	NXWSettingsDialog(NXWToolset* parent, const char* name);
};
