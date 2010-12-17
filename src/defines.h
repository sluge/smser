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

#ifndef _DEFINES_H_
#define _DEFINES_H_

//Convert number to string
#define NUM(s) QString::number(s)
//null string
#define SNULL QString::null

#define CONN(sender, signal, slot) CONNECT(sender, signal, this, slot)


#define CONNECT(sender, signal, receiver, slot) { const bool b = QObject::connect(\
                                         sender, SIGNAL(signal), receiver, SLOT(slot));\
                                         Q_ASSERT(b); \
                                       }

#define CUR_DATE QDateTime::currentDateTime()

#endif //_DEFINES_H_
