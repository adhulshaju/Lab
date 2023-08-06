#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_WINDOW_SIZE 5
typedef struct {
int sequenceNumber;
bool isAcked;
} Packet;
int acceptPackets(Packet packets[], int totalPackets) {
int i;
for (i = 0; i < totalPackets; i++) {
packets[i].sequenceNumber = i;
packets[i].isAcked = false;
}
return totalPackets;
}
void transmitPacket(Packet packet) {
printf("Transmitting packet %d\n", packet.sequenceNumber);
usleep(1000000);
}
bool checkAcknowledgement(Packet packet) {
int acknowledgement = rand() % 2;
if (acknowledgement == 0)
return false;
else
return true;
}
int main() {
int windowSize;
printf("Enter the window size (<= %d): ", MAX_WINDOW_SIZE);
scanf("%d", &windowSize);
if (windowSize > MAX_WINDOW_SIZE) {
printf("Window size exceeds the maximum allowed size.\n");
return 1;
}
int totalPackets;
printf("Enter the total number of packets to send: ");
scanf("%d", &totalPackets);
Packet packets[totalPackets];
totalPackets = acceptPackets(packets, totalPackets);
int totalFrames = (totalPackets + windowSize - 1) / windowSize;
printf("Sending details to the client: Total Packets = %d, Total Frames =%d\n", totalPackets, totalFrames);
int base = 0;
int nextSeqNum = 0;
while (base < totalPackets) {
for (int i = base; i < base + windowSize && i < totalPackets; i++) {
if (!packets[i].isAcked) {
transmitPacket(packets[i]);
}
}
for (int i = base; i < base + windowSize && i < totalPackets; i++) {
if (!packets[i].isAcked) {
if (checkAcknowledgement(packets[i])) {
packets[i].isAcked = true;
printf("Received acknowledgement for packet %d\n",
packets[i].sequenceNumber);
if (i == base) {
while (packets[base].isAcked && base < totalPackets) {
base++;
nextSeqNum++;
}
}
}
}
}
}
return 0;
}
