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

## 2. 추가 Peripheral 설정

### 2.1. Timers

- `TIM1` - `Clock Source` - `Internal Clock`
  - `Channel 1` - `PWM Generation CH1`
  - `Channel 2` - `PWM Generation CH2`
  - `Channel 3` - `PWM Generation CH3`
  - `Channel 4` - `PWM Generation CH4`
  - `Parameter Settings` - `Prescaler` - `720-1`
  - `Parameter Settings` - `Counter Period` - `1000-1`

## 3. Wiring Diagram

![Wiring Diagram](./diagram/wiring.drawio.svg)

## 4. Reference

- [서강대학교 청년광장. "06_[STM32] 타이머를 이용하여 PWM 출력하기". Last Modified Aug 30, 2019. Accessed June 20, 2025.](https://sc.sogang.ac.kr/bbs/bbsview.do?pkid=51929&bbsid=3857&wslID=mecha&searchField=&searchValue=)

---
