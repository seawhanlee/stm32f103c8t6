# STM32F103C8T6 Code Snippets: Bluetooth

이 저장소는 STM32F103C8T6 마이크로컨트롤러를 위한 코드 스니펫을 제공합니다. 개발 보드는 STM32F103C8T6 "Blue Pill" 보드를 사용합니다.

본 브랜치는 `HC-06` 블루투스 모듈을 사용하여 블루투스 통신을 구현한 예제 코드를 제공합니다.

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

- `Connectivity` - `USART2` - `Mode` - `Asynchronous`
  - `NVIC Settings` - `USART2 global interrupt` - `Enabled`

## 3. AT Command 설정

> 본 작업에는 USB to TTL 컨버터가 필요함

`HC-06` 블루투스 모듈의 설정 값을 바꾸기 위해서는 `HC-06`을 시리얼-USB 컨버터를 통해 PC에 직접 연결하여 다음 명령어를 입력해야 함

- `AT`: 연결 상태 확인
- 블루투스 모듈의 이름을 `AEP00`으로 변경
- 블루투스 모듈의 비밀번호를 `4242`로 변경
- 블루투스 모듈의 시리얼 통신 속도를 `115200bps`로 변경

```none
AT
AT+NAMEAEP00
AT+PIN4242
AT+BAUD8
```

> 블루투스 데이터 확인 시에는 `Serial Bluetooth Terminal` 앱을 사용

## 4. Wiring Diagram

![Wiring Diagram](./diagram/wiring.drawio.svg)

## 5. References

- [DeepBlue Embedded. "STM32-HC-05 Bluetooth Module Examples". Last modified unknown. Accessed: 2025-06-20.](https://deepbluembedded.com/stm32-hc-05-bluetooth-module-examples/)
- [NewBongman. "Bluetooth(HC-06) AT  명령어 사용하기". Last modified 2019-10-30. Accessed: 2025-06-20.](https://blog.naver.com/newbongman/221692871583)

---
