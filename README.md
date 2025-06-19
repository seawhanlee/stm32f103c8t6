# STM32F103C8T6 Code Snippets

이 저장소는 STM32F103C8T6 마이크로컨트롤러를 위한 코드 스니펫을 제공합니다. 개발 보드는 STM32F103C8T6 "Blue Pill" 보드를 사용합니다.

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

## 2. 프로젝트 기본 설정

### 2.1. Pinout & Configuration

- `SYS` - `Debug` - `Serial Wire`
- `RCC` - `High Speed Clock (HSE)` - `Crystal/Ceramic Resonator`

### 2.2. Clock Configuration

- `PLL Source Mux` - `HSE`
- `System Clock Mux` - `PLLCLK`
- `HCLK (MHz)` - `72`

## 2.3. Project Manager

- `Project` - `Toolchain/IDE` - `CMake`
- `Code Genreator` - `Generated files` - `Generate peripheral initialization as a pair of '.c/.h/' files per peripheral`

## 3. Import 절차

- VSCode의 `STM32Cube for Visual Studio Code` 확장 메뉴에서 Import Cmake project. 프로젝트 폴더를 선택하기
  - `.vscode` 경로에 VSCode `launch.json`, `tasks.json` 파일 등을 생성하는 역할을 함
- VSCode에서 프로젝트 폴더를 작업 공간으로 열기
- `CMake: Configure`에서 `Debug` 빌드 환경 선택

## 4. 추가 Peripheral 설정

### 4.1. Connectivity

- `SPII1` - `Mode` - `Full-Duplex Master`
  - `Parameter Settings` - `Clock Parameters` - `Prescaler` - `32`
- `USART2` - `Mode` - `Asynchronous`

### 4.2. Middleware and Software Packs

- `FATFS` - `User-defined`

### 4.3. System Core

- `GPIO` - `PB0` - `GPIO_OUTPUT`

## 5. Wiring Diagram

![Wiring Diagram](./diagram/wiring.drawio.svg)

## 6.. References

- [ControllersTech. "SD card using SPI in STM32". Last Modified Unknown. Accessed June 20, 2025.](https://controllerstech.com/sd-card-using-spi-in-stm32/)

> ControllersTech의 코드 중 `FR_NO_FILESYSTEM ` 해결을 위해 구버전 소스 코드를 적용함

---
