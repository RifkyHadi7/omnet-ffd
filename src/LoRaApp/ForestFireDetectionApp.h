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

#ifndef __FORESTFIREDETECTIONAPP_H_
#define __FORESTFIREDETECTIONAPP_H_

#include <omnetpp.h>
#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/INETDefs.h"
#include "inet/common/packet/Packet.h"

namespace flora { // Tambahkan namespace flora
using namespace inet;

class ForestFireDetectionApp : public ApplicationBase
{
  protected:
    // Parameter sensor
    std::string sensorTypes;
    double temperatureThreshold = 50.0; // Batas suhu
    double gasThreshold = 0.2;          // Batas gas
    double smokeThreshold = 0.3;        // Batas asap

    // Event untuk pengiriman paket
    cMessage *sendPacketEvent = nullptr;

    // Implementasi metode
    virtual int numInitStages() const override { return NUM_INIT_STAGES; } // Multiple init stages
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    // Lifecycle operation
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

    // Logika aplikasi
    virtual void sendAlarmPacket();

  public:
    virtual ~ForestFireDetectionApp();
};

} // namespace inet

#endif /* LORAAPP_FORESTFIREDETECTION_H_ */
