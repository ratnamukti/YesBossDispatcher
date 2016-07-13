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

#include "Dispatcher.h"
#include "Message_m.h"

Define_Module(Dispatcher);

void Dispatcher::initialize() {
    csr_index = 0;
    total_csr = this->par("csr_num");
}

void Dispatcher::handleMessage(cMessage *msg) {
    if (msg->arrivedOn("toSMS$i")) {
        Message *job = check_and_cast<Message *>(msg);
        if (job->getCsr_id() == -1) {
            job->setCsr_id(csr_index);
            send(job, "toCSR$o", csr_index);
            if (++csr_index == total_csr) {
                csr_index = 0;
            }
        } else {
            send(job, "toCSR$o", job->getCsr_id());
        }
    }

    if (msg->arrivedOn("toCSR$i")) {
        send(msg, "toSMS$o");
    }
}
