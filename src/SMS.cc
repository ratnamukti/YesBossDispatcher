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
    scheduleAt(0, new cMessage("START"));
    total_message = this->par("sms_num");
}

Message *SMS::createJob() {
    char buf[80];
    sprintf(buf, "Message-%d", ++message_counter);
    Message *job = new Message(buf);
    return job;
}

void SMS::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        delete msg;
        for (int i = 0; i < total_message; i++) {
            Message *job = createJob();
            send(job, "conn$o");
        }
    } else {
        Message *job = check_and_cast<Message *>(msg);
        if(job->getState() != 8){
            send(msg, "conn$o");
        } else{
            delete msg;
        }
    }
}
