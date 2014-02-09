/**
 * Copyright (C) 2014 Giovanni Capuano <webmaster@giovannicapuano.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef REGINALDO_CONFIG
#define REGINALDO_CONFIG

#ifndef INTERVAL
 #define  INTERVAL 500       // how often it has to refresh di history
#endif

/*
  Virtual-Key Codes - MSDN
    http://msdn.microsoft.com/en-us/library/ms927178.aspx
*/

#ifndef BASE_KEY
  #define BASE_KEY VK_LSHIFT // the first button to keep pressed
#endif

#ifndef SHIFTED
  #define SHIFTED  0x8000
#endif

#ifndef F1
  #define F1       112       // the button which identifies the first paste in the history
#endif

#ifndef F12
  #define F12      123       // the button which identifies the last paste in the history
#endif

#ifndef F_DIFF
  #define F_DIFF   111       // the number to subtract from F1 to obtain the wanted paste id
#endif

#endif