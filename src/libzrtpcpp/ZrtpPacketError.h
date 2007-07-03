/*
  Copyright (C) 2006 Werner Dittmann

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Boston, MA 02111.
*/

#ifndef _ZRTPPACKETERROR_H_
#define _ZRTPPACKETERROR_H_

#include <libzrtpcpp/ZrtpPacketBase.h>

/**
 * Implement the Error packet.
 *
 * The ZRTP simple message Error. The implementation sends this
 * after detecting an error.
 *
 * @author Werner Dittmann <Werner.Dittmann@t-online.de>
 */

class ZrtpPacketError : public ZrtpPacketBase {

 protected:
    Error_t* errorHeader;

 public:
    ZrtpPacketError();		/* Creates a Error packet with default data */
    ZrtpPacketError(char* data);	/* Creates a Error packet from received data */
    virtual ~ZrtpPacketError();

    uint32_t getErrorCode() { return ntohl(errorHeader->errorCode); };

    void setErrorCode(uint32_t code) {errorHeader->errorCode = htonl(code); };

 private:
     ErrorPacket_t data;
};

#endif // ZRTPPACKETERROR

