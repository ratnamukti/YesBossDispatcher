//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "SMS.h"

Define_Module(SMS);


void SMS::initialize()
{
    if (strcmp("sms", getName()) == 0) {
        cMessage *msg = new cMessage("Hello World!");
        send(msg, "conn$o");
    }
}

void SMS::handleMessage(cMessage *msg)
{
    send(msg, "conn$o");
}