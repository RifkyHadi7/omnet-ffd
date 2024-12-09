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

#include "ForestFireDetectionApp.h"

namespace flora {
Define_Module(ForestFireDetectionApp);

ForestFireDetectionApp::~ForestFireDetectionApp()
{
    cancelAndDelete(sendPacketEvent);
}

void ForestFireDetectionApp::initialize(int stage)
{
    ApplicationBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        // Ambil parameter dari file .ned
        sensorTypes = par("sensorTypes").stdstringValue();
        temperatureThreshold = par("temperatureThreshold").doubleValue();
        gasThreshold = par("gasThreshold").doubleValue();
        smokeThreshold = par("smokeThreshold").doubleValue();

        // Inisialisasi event pengiriman paket
        sendPacketEvent = new cMessage("sendPacketEvent");
        scheduleAt(simTime() + uniform(1, 10), sendPacketEvent); // Jadwal pertama
    }
}

void ForestFireDetectionApp::handleStartOperation(LifecycleOperation *operation)
{
    EV_INFO << "Starting ForestFireDetectionApp..." << endl;

        // Jika event sebelumnya dibatalkan, buat ulang event
        if (!sendPacketEvent) {
            sendPacketEvent = new cMessage("sendPacketEvent");
        }

        // Jadwalkan event pertama (jika belum dijadwalkan)
        if (!sendPacketEvent->isScheduled()) {
            scheduleAt(simTime() + uniform(1, 10), sendPacketEvent);
        }

        // Reset warna ikon menjadi hijau (default)
        getDisplayString().setTagArg("i", 1, "green");
}

void ForestFireDetectionApp::handleStopOperation(LifecycleOperation *operation)
{
    EV_INFO << "Stopping ForestFireDetectionApp..." << endl;

        // Batalkan semua event yang masih aktif
        if (sendPacketEvent) {
            cancelEvent(sendPacketEvent);
        }

        // Ubah ikon node menjadi abu-abu untuk menunjukkan status tidak aktif
        getDisplayString().setTagArg("i", 1, "gray");
}

void ForestFireDetectionApp::handleCrashOperation(LifecycleOperation *operation)
{
    EV_ERROR << "ForestFireDetectionApp has crashed!" << endl;

        // Batalkan event untuk mencegah memory leak
        if (sendPacketEvent) {
            cancelEvent(sendPacketEvent);
        }

        // Ubah ikon node menjadi merah gelap untuk menunjukkan status crash
        getDisplayString().setTagArg("i", 1, "darkred");
}

void ForestFireDetectionApp::handleMessageWhenUp(cMessage *msg)
{
    if (msg == sendPacketEvent) {
        // Simulasikan pembacaan sensor
        double temperature = uniform(20.0, 60.0); // Suhu dalam derajat Celsius
        double gasLevel = uniform(0.0, 100.0);    // Gas CO dalam ppm
        double smokeLevel = uniform(0.0, 1.0);    // Partikel asap

        EV_INFO << "Sensor Readings: Temperature=" << temperature
                << ", Gas=" << gasLevel
                << ", Smoke=" << smokeLevel << endl;

        // Periksa apakah ada anomali
        if (temperature > temperatureThreshold || gasLevel > gasThreshold || smokeLevel > smokeThreshold) {
            EV_WARN << "Anomaly Detected! Sending alarm packet..." << endl;
            sendAlarmPacket();
        }

        // Jadwalkan pengiriman berikutnya
        scheduleAt(simTime() + uniform(10, 20), sendPacketEvent);
    }
}

void ForestFireDetectionApp::sendAlarmPacket()
{
    // Buat paket alarm
    auto packet = new Packet("AlarmPacket");
    // Tambahkan konten ke paket jika diperlukan
    send(packet, "socketOut");
}
}
