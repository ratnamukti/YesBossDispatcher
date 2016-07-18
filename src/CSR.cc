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

#include "CSR.h"
#include "Message_m.h"

Define_Module(CSR);

void CSR::initialize() {
    time = 0;
}

void CSR::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        send(msg, "conn$o");
    } else {
        Message *job = check_and_cast<Message *>(msg);
        // TODO delay type
        double time = job->getTime() + 100;
        job->setTime(time);
        job->setState(job->getState() + 1);
        scheduleAt(time, job);
    }
}

double CSR::max(double a) {
    if (a > 0) {
        return a;
    } else {
        return 0;
    }
}

/*
 * - Typing Time
 * - Research Time
 * - Payment Time
 * - Order Time
 * - Idle Time
 * - Switching Time
 */
