/***************************************************************************
 *   Copyright (C) 2010 by Igor Sobinov   *
 *   sluge@mail.ru *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

//////////////////////////////////////////////////////////////////////////
//    Author :       Igor Sobinov
//    File:          $Source:  $
//    Revision:      $Revision: $
//    Last modified: $Date:  $
//    Description:   
//////////////////////////////////////////////////////////////////////////


#include "mainwidget.h"
#include "logger.h"
#include "config.h"

using namespace config;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(2 == argc)
        LOGGER.setLevel(argv[1]);

    LOGGER<<eDebug<<"*********************************************"<<NL;
    LOGGERD<<programmName
           <<"Programm running, found argument "<<argv[1]<<NL;

    MainWidget mw;
    mw.show();

    return a.exec();
}
