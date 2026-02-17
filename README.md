# Bico Protocol Bridge

## Project Overview

The Bico Protocol Bridge is an embedded software project that provides protocol bridging capabilities between serial interfaces and various hardware peripherals (Analog, Digital I/O, I2C, SPI).

## 📁 Project Structure

```
Bico_Protocol_Brigde/
├── 1_requirement/              # Feature requirements
│   ├── SerialToAnalog/
│   ├── SerialToDigital/
│   ├── SerialToI2C/
│   └── SerialToSPI/
├── 2_architecture/             # Architecture documentation
│   └── fucntionView/
│       ├── layer1Driver/
│       ├── layer2Service/
│       └── layer3Application/
├── 3_swComp/                   # Software components (MAIN IMPLEMENTATION)
│   ├── layer1Driver/           # Hardware abstraction drivers
│   ├── layer2Service/          # Business logic services
│   └── layer3Application/      # Application logic
├── 4_addOn/                    # Add-on modules
├── CMakeLists.txt              # Root build configuration
├── BUILD_SUMMARY.txt           # Detailed build summary
├── COMPONENT_STRUCTURE.md      # Component documentation
└── QUICKSTART.md               # Quick start guide
```

## 🎯 Features

Based on project requirements, the system provides:

1. **Serial to Analog** - Control analog outputs via serial commands
2. **Serial to Digital** - Control digital I/O via serial commands  
3. **Serial to I2C** - Bridge serial commands to I2C bus
4. **Serial to SPI** - Bridge serial commands to SPI bus

## 🏗️ Architecture

The project follows a 3-layer architecture:

### Layer 1: Hardware Drivers (9 Components)
- ADC, GPIO, Serial, PWM, NVM drivers
- I2C Master/Slave, SPI Master/Slave drivers
- **Status**: Prototype created, vendor HAL code needed

### Layer 2: Services (4 Components)
- Configuration service
- Serialization/Deserialization services
- NVM Service
- **Status**: Prototype created, business logic needed

### Layer 3: Applications (5 Components)
- Central Application Controller
- SerialToAnalog, SerialToDigital applications
- SerialToI2C, SerialToSPI bridge applications
- **Status**: Prototype created, application logic needed

## 🚀 Quick Start

### Prerequisites
- CMake 3.21 or higher
- C/C++ compiler (GCC, Clang, MSVC)
- Google Test (for unit testing)

### Build

```bash
# Clone the repository
cd Bico_Protocol_Brigde

# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .

# Run tests
ctest
```

### Component Template

Each component follows a standardized structure:
- `1_swcReq/` - Requirements
- `2_design/` - Design documentation
- `3_inc/` - Public headers
- `4_config/` - Configuration
- `5_src/` - Implementation
- `6_test/` - Unit tests
- `7_tools/` - Tools
- `8_misc/` - Miscellaneous

## 📊 Implementation Status

### ✅ Completed (As of 2026-02-01)
- [x] 18 software components created
- [x] Build system configured (CMake)
- [x] Test infrastructure setup (GTest)
- [x] Component interfaces defined
- [x] Prototype implementations
- [x] Documentation templates

### ⚠️ TODO - Implementation Required

#### Layer 1 Drivers
All driver components have TODO markers for vendor-specific HAL code:
```c
// TODO: Add vendor-specific HAL initialization here
```

**Action Required**: Implement vendor MCU-specific peripheral access

#### Layer 2 Services  
Service logic placeholders need implementation:
- Calibration algorithms
- Configuration management
- Data conversion formulas
- Protocol serialization/deserialization

**Action Required**: Implement business logic

#### Layer 3 Applications
Application state machines need implementation:
- Serial command parsing
- Protocol handling
- State transitions
- Error recovery

**Action Required**: Implement application-specific logic

## 📝 Documentation

- **[QUICKSTART.md](QUICKSTART.md)** - Quick reference guide
- **[COMPONENT_STRUCTURE.md](COMPONENT_STRUCTURE.md)** - Detailed component docs
- **[BUILD_SUMMARY.txt](BUILD_SUMMARY.txt)** - Build output summary
- **Architecture diagrams** - In `2_architecture/fucntionView/`
- **Component diagram** - `3_swComp/ComponentArchitecture.puml`

## 🧪 Testing

Each component includes:
- Unit test suite (GTest framework)
- Test CMakeLists.txt configuration
- Mock/Fake/Stub infrastructure (in `6_test/gtest/`)

Run all tests:
```bash
cd build
ctest --verbose
```

Run specific component test:
```bash
./testAdcDriver
./testSerialDriver
# etc.
```

## 🔧 Development Workflow

1. **Choose a component** to implement (Layer 1, 2, or 3)
2. **Read requirements** in `1_swcReq/` folder
3. **Review design** in `2_design/` folder
4. **Implement logic** in `5_src/` files
5. **Write tests** in `6_test/gtest/`
6. **Build and test** using CMake
7. **Update documentation** as needed

## 📦 Component Count

- **Total Components**: 18
- **Layer 1 (Drivers)**: 9 components
- **Layer 2 (Services)**: 4 components
- **Layer 3 (Applications)**: 5 components
- **Total Files**: ~198 files

## 🎨 Coding Standards

- **Naming Convention**: 
  - Types: `ComponentName_TypeName_t`
  - Functions: `ComponentName_FunctionName()`
  - Enums: `COMPONENT_NAME_ENUM_VALUE`
  - Macros: `COMPONENT_MACRO_NAME`

- **File Organization**:
  - One component per directory
  - Public APIs in `3_inc/`
  - Implementation in `5_src/`
  - Config in `4_config/`

## 🔗 Dependencies

Components are designed with clear layer dependencies:
- Layer 3 → depends on → Layer 2
- Layer 2 → depends on → Layer 1  
- Layer 1 → depends on → Hardware HAL (vendor-specific)

Dependencies managed via CMake `target_link_libraries`.

## 🛠️ Next Steps

1. **Select target MCU** and set up vendor HAL
2. **Implement Layer 1 drivers** with vendor-specific code
3. **Implement Layer 2 services** with business logic
4. **Implement Layer 3 applications** with protocols
5. **Write comprehensive unit tests**
6. **Perform integration testing**
7. **Optimize and refine**

## 📞 Support

For detailed information:
- See component-specific documentation in each `1_swcReq/` and `2_design/` folder
- Review architecture in `2_architecture/fucntionView/`
- Check build summary in `BUILD_SUMMARY.txt`

## 📄 License

[Add your license information here]

## 👥 Contributors

[Add contributor information here]

---

**Project Status**: Component structure complete, implementation in progress

**Created**: 2026-02-01

**Last Updated**: 2026-02-01
