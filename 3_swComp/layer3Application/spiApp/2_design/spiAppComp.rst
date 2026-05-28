#################################
What is this component about?
#################################

The Serial-to-SPI Application provides typed SPI write and transceive operations. It is
called by the Central Application Controller via RID 0x0500 (SPI Write) and
RID 0x0501 (SPI Transceive). This module has no UDS awareness - it receives typed
parameters and returns typed results.


#################################
Static structure
#################################

..  uml:: SPIAPPStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: SPIAPPStateMachine.puml

* Sequence diagram
..  uml:: SPIAPPSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide hardware-abstracted SPI write and full-duplex transceive for the CAC dispatcher.

Assumptions and influencing factors:
************************************
* SPI master driver is initialized and available.
* Device selection is handled via device index (chip select managed by driver).
* No UDS framing knowledge required in this module.

Solutions list:
***************
Solution 1 - Write + Transceive functions
Expose Write(dev, pData, len) and Transceive(dev, pTx, txLen, pRx, rxLen).

Solution 2 - Single transfer function with mode parameter
Combined function handling both write-only and full-duplex.

Solution evaluation:
********************
Separate functions match the RID mapping and provide clearer API semantics.

Final solution:
****************
Solution 1 selected for clarity and RID alignment.