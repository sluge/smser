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

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "types.h"

namespace config
{
CQString programmName = "SMSER";

CQString programmAuthor = QObject::trUtf8("Игорь Собинов");

CQString programmAuthorEn = "Igor Sobinov";

CQString programmWebSite = "<A href=http://smser-ru.narod.ru>smser-ru.narod.ru</A>";

CQString programmVersion = "0.1 beta";

CQString messageSite = "smste.ru";

CQString http = "http://";

CQString mimeJpg = "image/jpeg";

CQString mimeXml = "application/xml";

CQString mimeHtml = "text/html";

CQString code = "codemod";

CQString code2 = "value=\"code";

CQString code3 = "\"";

CQString sent1 = "\"sentok\">";

CQString sent2 = "</";

CQString contentType = "Content-Type";

CQString setCookie = "Set-Cookie";

CQString formUrl = "application/x-www-form-urlencoded";

CQString extra1 = "ёЁжЖчЧшШюЮяЯєЄ";

CQString extra2 = "щЩ";

cint phoneMinLen = 9;

cuint numderDefLen = 11;

cuint maxDefMsgLen = 160;

cuint intermedSmsLen = 61;

cuint randomFactor = 100000;

CQString xmlDefEncoding = "utf-8";

CQString xmlRoot = "file";

CQString xmlNumber = "number";

CQString xmlDigits = "digits";

CQString xmlOperator = "name";

CQString xmlRegion = "region";

CQString xmlOperLink = "href";

CQString xmlOperSupp = "support";

CQString xmlCaptcha = "image";

CQString xmlEvent = "event";

CQString xmlMaxLen = "maxlen";

CQString xmlEncoding = "encoding=";

CQString confNumbers = "numbers";

CQString confLastNumber = "lastnum";

CQString confSignatures = "signatures";

CQString confLastSign = "lastsign";

}

#endif //_CONFIG_H_
