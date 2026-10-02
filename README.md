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
git clone https://github.com/LinhTrucVo/Bico_Protocol_Bridge.git
cd Bico_Protocol_Bridge
git submodule update --init --recursive --depth 1
cd "7_1_esp32_workspace/esp32_bico_protocol_bridge"
<esp-idf_path>\export.ps1
idf.py build

git clone --branch develop_on_esp32 --depth 1 --recurse-submodules --shallow-submodules https://github.com/LinhTrucVo/Bico_Protocol_Bridge.git

## Component Template

Each component follows a standardized structure:
- `1_swcReq/` - Requirements
- `2_design/` - Design documentation
- `3_inc/` - Public headers
- `4_config/` - Configuration
- `5_src/` - Implementation
- `6_test/` - Unit tests
- `7_tools/` - Tools
- `8_misc/` - Miscellaneous

## 📝 Documentation

- **Architecture diagrams** - In `2_architecture/fucntionView/`
- **Component diagram** - `3_swComp/ComponentArchitecture.puml`

## 🧪 Testing

Each component includes:
- Unit test suite (GTest framework)
- Test CMakeLists.txt configuration
- Mock/Fake/Stub infrastructure (in `6_test/gtest/`)


## 🔧 Development Workflow

1. **Choose a component** to implement (Layer 1, 2, or 3)
2. **Read requirements** in `1_swcReq/` folder
3. **Review design** in `2_design/` folder
4. **Implement logic** in `5_src/` files
5. **Write tests** in `6_test/gtest/`
6. **Build and test** (dependent on mcu build support)
7. **Update documentation** as needed


## 🎨 Coding Standards

- **Naming Convention**: 
  - Types: `ComponentName_TypeName_t`
  - Functions: `ComponentName_FunctionName()`
  - Enums: `COMPONENT_NAME_ENUM_VALUE`
  - Macros: `COMPONENT_MACRO_NAME`

- **File Organization**:
  - One component per directory
  - Public APIs in `3_inc/`
  - Private APIs, Implementation for Component's Units (.c, .h files) in `5_src/`
  - Config in `4_config/`

## 🔗 Dependencies

Components are designed with clear layer dependencies:
- Layer 3 → depends on → Layer 2
- Layer 2 → depends on → Layer 1  
- Layer 1 → depends on → Hardware HAL (vendor-specific)


## 📞 Support

For detailed information:
- See component-specific documentation in each `1_swcReq/` and `2_design/` folder
- Review architecture in `2_architecture/fucntionView/`

## 📄 License

[Add your license information here]

## 👥 Contributors

[Add contributor information here]

---

**Project Status**: 

**Created**: 

**Last Updated**: 
