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
    last_time = 0;
    delay = 0;
}

void CSR::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        send(msg, "conn$o");
    } else {
        Message *job = check_and_cast<Message *>(msg);
        int state = job->getState();
        double time = job->getTime();
        if (state == 0 || state == 1 || state == 3) {
//typing time
            delay = 1;
        } else if (state == 2) {
//research time
            delay = 2;
        } else if (state == 4) {
//payment time
            delay = 3;
        } else if (state == 5) {
// Order Time
            delay = 4;
        }
        time = delay + max(time - last_time) + last_time;
        last_time = time;
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
