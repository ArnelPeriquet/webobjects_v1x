/*
 * (C) Copyright 2015  Arnel I Periquet.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 */

#include <stdafx.h>
#include <ctype.h>
#include "JsonStr.h"


JsonStr::JsonStr(std::string iInputStr) {
    std::ostringstream oss;
    char lastChar = ' ';

    for (std::size_t i=0; i<iInputStr.length(); i++) {
        while (isspace(iInputStr[i])) {
            i++;

            if (i >= iInputStr.length())
                goto outer;
        }

        if (iInputStr[i] == ':')
            oss << '"';    

        if ((lastChar != '}' && lastChar != ']' && lastChar != ':') && (iInputStr[i] == '}' || iInputStr[i] == ']' || iInputStr[i] == ','))
            oss << '"';

        if ((lastChar == ':' || lastChar == ',') && iInputStr[i] != '{' && iInputStr[i] != '[')
            oss << '"';

        oss << iInputStr[i];

        if (iInputStr[i] == '{')
            oss << '"';

        lastChar = iInputStr[i];
    }
    outer:

    mJsonStr = oss.str();
}



std::string JsonStr::operator()() {
    return mJsonStr;
}
