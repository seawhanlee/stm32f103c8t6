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

## 4. SWO 확인을 위한 설정

SWO 확인을 위해서는 먼저 OpenOCD를 절치해야 한다.

- [GNU Toolchains. "Download pre-built OpenOCD for Windows".](https://gnutoolchains.com/arm-eabi/openocd/)
- 해당 경로에서 다운로드받은 바이너리를 환경 변수에 추가한다.

환경 변수 추가 후 `launch.json`의 `Build & Debug Microcontroller - ST-Link`를 참고해 OpenOCD 프로파일을 추가한다.

- `stlink.cfg`와 `stm32f1x.cfg` 파일은 GitHub `openocd-org/openocd` 저장소에서 다운로드 받을 수 있다.

```json
        {
            "name": "Build & Debug Microcontroller - OpenOCD",
            "cwd": "${workspaceFolder}",
            "type": "cortex-debug",
            "executable": "${command:cmake.launchTargetPath}",
            // Let CMake extension decide executable: "${command:cmake.launchTargetPath}"
            // Or fixed file path: "${workspaceFolder}/path/to/filename.elf"
            "request": "launch",
            "servertype": "openocd",
            "configFiles": [
                "${workspaceFolder}/stlink.cfg",
                "${workspaceFolder}/stm32f1x.cfg"
            ],
            "device": "STM32F103C8Tx", //MCU used
            "interface": "swd",
            "serialNumber": "",        //Set ST-Link ID if you use multiple at the same time
            "runToEntryPoint": "main",
            "svdFile": "${config:STM32VSCodeExtension.cubeCLT.path}/STMicroelectronics_CMSIS_SVD/STM32F103.svd",
            "v1": false,               //Change it depending on ST Link version
            "serverpath": "C:\\Users\\merlin\\Documents\\Tools\\OpenOCD\\bin\\openocd.exe", // 사용자의 OpenOCD 경로
            "stm32cubeprogrammer":"${config:STM32VSCodeExtension.cubeCLT.path}/STM32CubeProgrammer/bin",
            "stlinkPath": "${config:STM32VSCodeExtension.cubeCLT.path}/STLink-gdb-server/bin/ST-LINK_gdbserver",   
            "armToolchainPath": "${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin",
            "gdbPath":"${config:STM32VSCodeExtension.cubeCLT.path}/GNU-tools-for-STM32/bin/arm-none-eabi-gdb",            
            "swoConfig": {
                "enabled":true,
                "source":"probe",
                "swoFrequency": 2000000,
                "cpuFrequency":72000000,
                "decoders": [
                    { 
                        "port": 0,
                        "type": "console",
                        "label": "SWO output",
                        "encoding":"ascii"
                    }
                ]
            }
            //"preLaunchTask": "Build + Flash"
            /* If you use external loader, add additional arguments */
            //"serverArgs": ["--extload", "path/to/ext/loader.stldr"],
        }
```

복제품 ST-Link v2의 경우 [`swo` 기능이 없어 별도 개조가 필요하다고 알려져 있다](https://mokhwasomssi.tistory.com/201?category=927528).

- 작업 방법에 대해서는 [다음 글을](https://www.eevblog.com/forum/microcontrollers/quick-hack-to-get-swo-on-st-link-clones/) 참고한다.

기타 OpenOCD 설정 관련 내용은 참고문헌들을 참고한다.

## 4. References

- [STMicroelectronics Community. "How to configure STM32 VS Code extension to use OpenOCD". Last Modified Jan 31, 2025. Accessed June 20, 2025.](https://community.st.com/t5/stm32-mcus/how-to-configure-stm32-vs-code-extension-to-use-openocd/ta-p/748562)
- [Zen`s embedded. "STM32 and VSCode: Advanced Manual Configuration Guide". Last Modified Jan 12, 2025. Accessed June 20, 2025.](https://zenembed.com/vscode-cubemx-pro-guide)
- [GitHub. "Marus/cortex-debug wiki". Last Modified Jan 17, 2025. Accessed June 20, 2025.](https://github.com/Marus/cortex-debug/wiki/SWO-Output)
- [EEVblog Electronics Community Forum. "Quick hack to get SWO on ST-Link clones". Last Modified Dec 7, 2019. Accessed June 20, 2025.](https://www.eevblog.com/forum/microcontrollers/quick-hack-to-get-swo-on-st-link-clones/)

---
