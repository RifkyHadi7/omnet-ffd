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
 
simple ForestFireDetectionApp like IApp
{
    parameters:
        string sensorTypes; // Jenis sensor: "temperature,gas,smoke"
        double temperatureThreshold = default(45); // Ambang batas suhu
        double gasThreshold = default(80);        // Ambang batas gas CO
        double smokeThreshold = default(0.8);     // Ambang batas partikel asap
        @display("i=block/app");
    gates:
        input socketIn @labels(LoRaAppPacket/up);
        output socketOut @labels(LoRaAppPacket/down);  
}