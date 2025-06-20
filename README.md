# STM32F103C8T6 Code Snippets: Attitude Heading Reference System

이 저장소는 STM32F103C8T6 마이크로컨트롤러를 위한 코드 스니펫을 제공합니다. 개발 보드는 STM32F103C8T6 "Blue Pill" 보드를 사용합니다.

본 브린채는 `GY-521` 가속도계 - 자이로스코프 센서를 사용하여 자세 측정을 구현한 예제 코드를 제공합니다.

## 1. 코드 생성 및 개발 Toolchain

- STM32CubeMX v6.14.1
- STM32CubeCLT v1.18.0
- STMCUFinder v 6.1.0
- Visual Studio Code(VSCode)
  - STM32Cube for Visual Studio Code
  - 확장 설치 후 `STM32CubeMX`, `STM32CubeCLT`, `STMCUFinder` 경로를 설정해야 함
- [CMake](https://cmake.org/download/)
- [Ninja](https://github.com/ninja-build/ninja/releases)
  - 시스템 환경 변수로 등록되어 있어야 함

## 2. 추가 Peripheral 설정

### 2.1. Connectivity

- `Connectivity` - `I2C2` - `I2C` - `I2C`
  - `Parameter Settings` - `I2C Speed Mode` - `Fast Mode`

### 2.2. GPIO

- `PB1` - `GPIO_INPUT`

> 본 예제에서는 `PB1` 핀을 인터럽트용으로 설정하나, 실제로 사용하지는 않음

## 3. Wiring Diagram

![Wiring Diagram](./diagram/wiring.drawio.svg)

## 4. References

- [GitHub. "leech001/MPU6050". Last Modified Jun 5, 2021. Accessed: 2025-06-20.](https://github.com/leech001/MPU6050)

---
