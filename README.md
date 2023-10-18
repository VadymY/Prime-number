# Prime-number this is solution for test task (Prime numbers)

Giraffic C++ Candidate Test
General Notes
1.	Please solve ONE of the following assignments using C++, and send us your code.
2.	Both Linux and Windows are OK - Visual Studio or Eclipse.
3.	Use any source of information you like, but write the code yourself.
4.	Extra credit will be given for using ACE framework.
5.	For further questions please contact us.

Assignment Option 1: Packet Loss Detector
You are designing an application that receives a stream of UDP datagrams from a remote peer. The peer sends the packets at a relatively constant rate of about 8 packets per second. Each datagram has a sequentially incremented serial number.
C++ class
Write a C++ class that calculates the current and overall packet loss for such a stream. It exposes three external functions:
1.	void OnPacketReceived(int packetSerialNumber);
 This function is called when we receive a packet.
2.	int GetCurrentLoss(); 
This returns the current packet loss on the stream (we define it as the loss for the past 2 seconds). The returned number is an integer representing the loss percentage (0-100).
3.	int GetAverageLoss();
This returns the percentage of overall packet loss from beginning to the current point in time (0-100). 

Please provide a short documentation of your class, and the principals that guided you in its design (e.g. performance, simplicity, or whatever principals you value in your design)
Tester
Please provide a working tester for this class.
The tester can simulate the stream, but for extra credit you can use real networking!

Assignment Option 2: Prime numbers
Please write the fastest C++ program you can think of, that detects whether a number is prime or not. The numbers it must test are 64 bit long integers.
Use any dirty trick you can think of to get more juice out of your program and the host machine(s)!
Please provide an explanation of the reasoning behind your algorithm and implementation, and why you chose it.
Note: The algorithm here is not necessarily the most significant part. Consider multithreading!

Good Luck 
