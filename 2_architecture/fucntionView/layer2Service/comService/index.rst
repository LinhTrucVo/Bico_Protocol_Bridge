ComService
##########

Layer 2: Service Layer

This function provides a communication abstraction over the Serial Driver using ring-buffer
management for both receive (Rx) and transmit (Tx) directions.

Description
***********
The ComService manages incoming and outgoing serial data through ring-buffer arrays.
It registers RX/TX callbacks with the Serial Driver to receive data asynchronously from ISR context,
storing it into the internal Rx ring-buffer. The periodic Run() function flushes the Tx ring-buffer
by calling SerialDriverUnit_Send(). Upper layers use a simple API to check data availability,
read frames, and write responses without direct dependency on the Serial Driver.

Key responsibilities:

- **Rx buffering**: Receive data via registered RxCallback (ISR context) and store into Rx ring-buffer
- **Tx buffering**: Queue outgoing frames into a Tx ring-buffer for transmission
- **Data availability check**: Report whether a complete frame is available for reading
- **Read API**: Provide buffered frame data to the caller
- **Write API**: Accept response frames and forward them to Serial Driver
- **Run function**: Periodic execution to flush Tx ring-buffer via SerialDriverUnit_Send()
- **Callback management**: Register and handle RX/TX complete callbacks from Serial Driver

Static view
***********
..  uml:: staticView.puml

Information flow
****************
..  uml:: informationFlow.puml

Dynamic behaviour
*****************
..  uml:: dynamicBehaviour.puml

Timing behaviour
****************
- Run cycle: called periodically (typ. 1 ms)
- Buffering latency: < 1 ms per frame
- Supports throughput matching Serial Driver baud rate

Resource consumption
********************
- RAM: ~1 KB (Rx ring-buffer + Tx ring-buffer)
- ROM: ~1.5 KB for buffer management code
- CPU: Minimal, memory copy operations
