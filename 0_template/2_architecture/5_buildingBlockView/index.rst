Chapter 5. Building Block View
##############################

5.0. Feature Realization
========================
Each feature from ``1_requirement`` has its own number 5.0.<n>, one puml file and one ``sw_arch`` item, id ``SWARCH_<FEATURENAME>``.
The diagram shows the feature, its functions, and for each function the components it uses directly.
The ``sw_arch`` item is linked to the requirements of the feature it realizes.

5.0.1. Feature Name 1
---------------------
..  sw_arch:: Feature Name 1
   :id: SWARCH_FEATURENAME1
   :realizes: SWREQ_FEATURENAME1_001, SWREQ_FEATURENAME1_002

   Function 1 uses the config service to set the parameters, function 2 uses the config service to get them
   and the IO service to command the peripheral.

..  uml:: feature/featureName1/featureName1.puml

5.0.2. Feature Name 2
---------------------
..  sw_arch:: Feature Name 2
   :id: SWARCH_FEATURENAME2
   :realizes: SWREQ_FEATURENAME2_001, SWREQ_FEATURENAME2_002

   Function 1 uses the crypto service to protect data, function 2 uses the diagnostic service to report events.

..  uml:: feature/featureName2/featureName2.puml

5.1. Level 1: Overall System
============================
This show the overall system architecture, what SW block available in project.
Overall system could be the ASW, BSW, HAL and 3rd-party SW blocks 
and their main dependencies or anything else as long as it could be clearly separated.
The number of blocks is not limitted, this depend on the specific project, 
uml example about show the ASW, BSW, HAL and 3rd-party SW blocks, it could be more or less.

..  uml:: level1/overallSystemArchitecture.puml

5.2. Level 2: Building Blocks
=============================
This show the packages inside each block of the overall system,
Each block has its own diagram, one puml file per block, packages could be nested.
The number of packages in each block is not limitted, this depend on the specific project, 
uml example below about packages inASW, BSW, HAL and 3rd-party SW blocks, it could be more or less packages.
The packages represented is just an example, the actual packages depend on the specific project.

ASW
---
Packages inside the ASW block.

..  uml:: level2/aswPackage.puml

BSW
---
Service and Driver packages inside the BSW block, each with its own packages.

..  uml:: level2/bswPackage.puml

HAL
---
Packages inside the HAL block, hardware-specific implementations behind the HAL API.

..  uml:: level2/halPackage.puml

3rd-party SW
------------
Packages inside the 3rd-party SW block, proprietary and open source software.

..  uml:: level2/thirdPartySwPackage.puml


5.3. Level 3: Component Block
=============================
Each component inside the packages has its own puml file, 
shown as a class with a provides and a requires section.
Interfaces follow the naming convention compName_interfaceName, 
where compName is the providing component.
The components represented is just an example, the actual components depend on the specific project.
Example, ComService provides ComService_sendMessage(id, data) and ComService_receiveCallBack,
and requires ComDriver_canSend(id, data) and ComDriver_getCanStatus.
The puml files are grouped in a folder per block and, if the block has nested packages, in a sub-folder per package,
for example `level3/aswPackage/` for ASW components and `level3/bswPackage/servicePackage/` for Service components.
The 3rd party interface is not comply this project naming convention, it has it own naming style,
so just get the interface name from the 3rd-party documentation to and show here, 
just show the interface we use, not all interface some 3rd party documentation provides.

ASW
---

Application controller
^^^^^^^^^^^^^^^^^^^^^^
..  sw_arch:: Application controller
   :id: SWARCH_APP_CTRL
   :provides: ApplicationController_start(), ApplicationController_stop(), ApplicationController_getState()
   :requires: ComService_sendMessage(id, data), ConfigService_setParameter(id, value), ConfigService_getParameter(id), IoService_setOutput(channel, level)

   Controls the application flow and calls the services.

..  uml:: level3/aswPackage/applicationControllerInterface.puml

App 1
^^^^^
..  sw_arch:: App 1
   :id: SWARCH_APP_1
   :provides: App1_execute(request), App1_getResult()
   :requires: ComService_sendMessage(id, data), ComService_receiveCallBack()

   Application that uses the communication service.

..  uml:: level3/aswPackage/app1Interface.puml

App 2
^^^^^
..  sw_arch:: App 2
   :id: SWARCH_APP_2
   :provides: App2_execute(request), App2_getResult()
   :requires: StorageService_readData(key), StorageService_writeData(key, data)

   Application that uses the storage service.

..  uml:: level3/aswPackage/app2Interface.puml

BSW - Service
-------------

Com service
^^^^^^^^^^^
..  sw_arch:: Com service
   :id: SWARCH_COM_SRV
   :provides: ComService_sendMessage(id, data), ComService_receiveCallBack()
   :requires: ComDriver_canSend(id, data), ComDriver_getCanStatus()

   Sends and receives messages through the communication driver.

..  uml:: level3/bswPackage/servicePackage/comServiceInterface.puml

Config service
^^^^^^^^^^^^^^
..  sw_arch:: Config service
   :id: SWARCH_CFG_SRV
   :provides: ConfigService_setParameter(id, value), ConfigService_getParameter(id)
   :requires: StorageService_readData(key), StorageService_writeData(key, data)

   Validates and holds the configuration parameters in RAM, stores them through the storage service.

..  uml:: level3/bswPackage/servicePackage/configServiceInterface.puml

IO service
^^^^^^^^^^
..  sw_arch:: IO service
   :id: SWARCH_IO_SRV
   :provides: IoService_setOutput(channel, level), IoService_getInput(channel)
   :requires: IoDriver_readPin(pin), IoDriver_writePin(pin, level)

   Maps logical IO channels to pins and reads or writes them through the IO driver.

..  uml:: level3/bswPackage/servicePackage/ioServiceInterface.puml

Storage service
^^^^^^^^^^^^^^^
..  sw_arch:: Storage service
   :id: SWARCH_STO_SRV
   :provides: StorageService_readData(key), StorageService_writeData(key, data)
   :requires: StorageDriver_flashRead(address, length), StorageDriver_flashWrite(address, data)

   Reads and writes data through the storage driver.

..  uml:: level3/bswPackage/servicePackage/storageServiceInterface.puml

Crypto service
^^^^^^^^^^^^^^
..  sw_arch:: Crypto service
   :id: SWARCH_CRY_SRV
   :provides: CryptoService_encrypt(data), CryptoService_decrypt(data), CryptoService_verify(data, signature)
   :requires: StorageService_readData(key)

   Encrypts, decrypts and verifies data.

..  uml:: level3/bswPackage/servicePackage/cryptoServiceInterface.puml

Diagnostic service
^^^^^^^^^^^^^^^^^^
..  sw_arch:: Diagnostic service
   :id: SWARCH_DIA_SRV
   :provides: DiagnosticService_reportEvent(id), DiagnosticService_getDiagnosticStatus()
   :requires: StorageService_readData(key), StorageService_writeData(key, data), ComService_sendMessage(id, data)

   Records diagnostic events and reports their status.

..  uml:: level3/bswPackage/servicePackage/diagnosticServiceInterface.puml

BSW - Driver
------------

Com driver
^^^^^^^^^^
..  sw_arch:: Com driver
   :id: SWARCH_COM_DRV
   :provides: ComDriver_canSend(id, data), ComDriver_getCanStatus(), ComDriver_rxIndication(id, data)
   :requires: HwImplementation1_canTransmit(id, data), HwImplementation1_getCanStatus()

   Sends and receives frames on the communication bus.

..  uml:: level3/bswPackage/driverPackage/comDriverInterface.puml

Storage driver
^^^^^^^^^^^^^^
..  sw_arch:: Storage driver
   :id: SWARCH_STO_DRV
   :provides: StorageDriver_flashRead(address, length), StorageDriver_flashWrite(address, data)
   :requires: HwImplementation1_flashRead(address, length), HwImplementation1_flashWrite(address, data)

   Reads and writes the non-volatile memory.

..  uml:: level3/bswPackage/driverPackage/storageDriverInterface.puml

IO driver
^^^^^^^^^
..  sw_arch:: IO driver
   :id: SWARCH_IO_DRV
   :provides: IoDriver_readPin(pin), IoDriver_writePin(pin, level)
   :requires: HwImplementation2_readPin(pin), HwImplementation2_writePin(pin, level)

   Reads and writes digital pins.

..  uml:: level3/bswPackage/driverPackage/ioDriverInterface.puml

HAL
---

Hardware-specific implementation 1
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
..  sw_arch:: Hardware-specific implementation 1
   :id: SWARCH_HW_IMPL_1
   :provides: HwImplementation1_canTransmit(id, data), HwImplementation1_getCanStatus(), HwImplementation1_flashRead(address, length), HwImplementation1_flashWrite(address, data)
   :requires: VendorSdk_vendorApi()

   Hardware-specific implementation of the communication and storage HAL API.

..  uml:: level3/halPackage/gpioImplementationInterface.puml

Hardware-specific implementation 2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
..  sw_arch:: Hardware-specific implementation 2
   :id: SWARCH_HW_IMPL_2
   :provides: HwImplementation2_readPin(pin), HwImplementation2_writePin(pin, level)
   :requires: VendorSdk_vendorApi()

   Hardware-specific implementation of the pin HAL API.

..  uml:: level3/halPackage/spiImplementationInterface.puml

3rd-party SW
------------

ESP-IDF GPIO driver
^^^^^^^^^^^^^^^^^^^
..  sw_arch:: ESP-IDF GPIO driver
   :id: SWARCH_VENDOR_SDK
   :provides: gpio_config(), gpio_set_level(), gpio_get_level(), gpio_set_direction()
   :requires: none

   Vendor SDK GPIO driver used by the HAL implementations.

..  uml:: level3/thirdPartySwPackage/vendorSdkInterface.puml

Licensed middleware
^^^^^^^^^^^^^^^^^^^
..  sw_arch:: Licensed middleware
   :id: SWARCH_LIC_MW
   :provides: LicensedMiddleware_middlewareApi()
   :requires: Os_osApi(), Libc_stdLibApi()

   Licensed middleware used by the system.

..  uml:: level3/thirdPartySwPackage/licensedMiddlewareInterface.puml

Customer-specific library
^^^^^^^^^^^^^^^^^^^^^^^^^
..  sw_arch:: Customer-specific library
   :id: SWARCH_CUST_LIB
   :provides: CustomerLibrary_libraryApi()
   :requires: Libc_stdLibApi()

   Customer-specific library used by the system.

..  uml:: level3/thirdPartySwPackage/customerLibraryInterface.puml

zlib
^^^^
..  sw_arch:: zlib
   :id: SWARCH_OSS_LIB
   :provides: deflateInit(), deflate(), deflateEnd(), inflateInit(), inflate(), inflateEnd()
   :requires: malloc(), free()

   Open source compression library (zlib 1.4) used by the system.

..  uml:: level3/thirdPartySwPackage/openSourceLibraryInterface.puml


