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

package yesbossdispatcher;

network Network
{
    @display("bgb=492,224");

    int csr_count = default(5);
    
    submodules:
        dispatcher: Dispatcher {
            @display("p=241,108");
            csr_num = csr_count;
        }
        sms: SMS {
            @display("p=64,108");
        }
        csr[csr_count]: CSR {
            @display("p=417,108");
        }

    connections:
        sms.conn <--> dispatcher.toSMS;
        for i=0..csr_count-1 {
            dispatcher.toCSR[i] <--> csr[i].conn;
        }
}