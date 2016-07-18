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
#include "Message_m.h"

Define_Module(SMS);

void SMS::initialize() {
    total_message = this->par("sms_num");
    message_counter = 0;
    purchase_delay = 100;
    response_delay = 10;
    for (int ii = 0; ii < total_message; ii++) {
        Message *job = createJob();
        double time = job->getTime() + ii * 50;
        job->setTime(time);
        scheduleAt(time, job);
    }

}

Message *SMS::createJob() {
    char buf[80];
    sprintf(buf, "Message-%d", ++message_counter);
    Message *job = new Message(buf);
    return job;
}

void SMS::handleMessage(cMessage *msg) {
    if (!msg->isSelfMessage()) {
        Message *job = check_and_cast<Message *>(msg);
        if (job->getState() == 1) {
            send(msg, "conn$o");
        } else {
            int state = job->getState();
            if (state == 5) {
                double time = job->getTime() + purchase_delay;
                job->setTime(time);
                scheduleAt(time, job);
            } else if (state == 7) {

            } else {
                double time = job->getTime() + response_delay;
                job->setTime(time);
                scheduleAt(time, job);
            }
        }
    } else {
        send(msg, "conn$o");
    }
}

/*
 * - Response Time
 * - Payment Time
 */

/*
 *  1 : FR
 *  2 : AD
 *  3 : Sol
 *  4 : AD
 *  5 : P
 *  6 : F
 */
