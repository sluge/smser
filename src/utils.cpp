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

#include "config.h"
#include "defines.h"
#include "utils.h"

using namespace config;

///////////
//Globals//
///////////

void srand()
{
    srand(QDateTime::currentDateTime().toTime_t());
}

uint smsRand()
{
    return static_cast<uint>(static_cast<double>(rand()) / RAND_MAX * randomFactor);
}

QString bytesToText(cuint& n)
{
    if(n < 1000)
        return NUM(n) + " b";
    if(n < 1000000)
        return QString::number(static_cast<double>(n) / 1024, 'f', 1) + " kb";
    else
        return QString::number(static_cast<double>(n) / (1024 * 1024), 'f', 1) + " mb";
}

QStringList combo2StringList(QComboBox* cb)
{
    QStringList s;
    if(!cb)
        return s;

    cuint c = cb->count();
    for(uint i = 0; i < c; ++i)
        s << cb->itemText(i);

    return s;
}

void fillCombo(QComboBox* cb, CQStringList& s)
{
    if(!cb)
        return;

    cuint c = s.size();

    for(uint i = 0; i < c; ++i)
        cb->addItem(s[i]);
}

CQStringList clearList(CQStringList& s)
{
    QStringList res;
    cuint c = s.size();
    for(uint i = 0; i < c; ++i)
        if(!s[i].isEmpty())
            res << s[i];

    res.removeDuplicates();
    return res;
}
