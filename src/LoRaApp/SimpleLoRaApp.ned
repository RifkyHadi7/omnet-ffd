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

package flora.LoRaApp;

import inet.applications.contract.IApp;

//
// A Simple LoRa Application with Forest Fire Detection
//
simple SimpleLoRaApp like IApp
{
    parameters:
        @signal[LoRa_AppPacketSent](type=long); // Signal for sent packets
        @statistic[LoRa_AppPacketSent](source=LoRa_AppPacketSent; record=count);
        int numberOfPacketsToSend = default(1); // Number of packets to send
        volatile double timeToFirstPacket @unit(s) = default(10s); // Time to first packet
        volatile double timeToNextPacket @unit(s) = default(10s); // Time between packets
        double initialLoRaTP @unit(dBm) = default(14dBm); // Initial transmission power
        double initialLoRaCF @unit(Hz) = default(868MHz); // Initial carrier frequency
        int initialLoRaSF = default(12); // Initial spreading factor
        double initialLoRaBW @unit(Hz) = default(125kHz); // Initial bandwidth
        int initialLoRaCR = default(4); // Initial coding rate
        bool initialUseHeader = default(true); // Use LoRa header
        bool evaluateADRinNode = default(false); // Evaluate ADR in node
        int dataSize @unit(B) = default(10B); // Data size for payload

        // Forest fire detection parameters
        bool enableFireDetection = default(false); // Enable/disable fire detection
        double criticalTemperature @unit(C) = default(45C); // Critical temperature threshold
        double criticalHumidity = default(0.2); // Critical humidity threshold

    gates:
        input socketIn @labels(LoRaAppPacket/up); // Input gate for packets from lower layer
        output socketOut @labels(LoRaAppPacket/down); // Output gate for packets to lower layer
}
