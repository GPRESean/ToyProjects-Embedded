# 1. What is this?
 This project is created to get familiar with STM32F446RE. It will contain simple drivers for STM32F446RE.

# 2. Target
Microcontroller : [STM32F446RE](https://www.st.com/en/microcontrollers/stm32f446re.html)

Board : [NUCLEO-F446RE](https://www.st.com/en/evaluation-tools/nucleo-f446re.html)

# 3. How to get build environment
Only tested on MacOS "High Sierra" and "Mojave"
- Eclipse Photon 4.8.0 / 2018-09 4.9.0
- Eclipse plugin "System Workbench for STM32" 2.6.0.201809060829
- You might need STLink driver depending on OS

1. Install Eclipse IDE for C/C++ Developers
2. Open Eclipse and open menu Help > Install New Software
3. Add Name: "System Workbench for STM32 - Bare Machine edition", URL: http://ac6-tools.com/Eclipse-updates/org.openstm32.system-workbench.update-site-v2
4. Select all of the Open STM32 tools. and click Next
5. Click Install anyway
6. Click Restart Now

[Latest Installation manual (Register required)](http://www.openstm32.org/Installing%2BSystem%2BWorkbench%2Bfor%2BSTM32)

-> Recommend manual install "Installing System Workbench for STM32 from Eclipse" to avoid debug crashes.

# 4. If you want to make a new project
Check out below links.

[Creating a new project](http://www.openstm32.org/Creating%2Ba%2Bnew%2Bproject)

[Importing a STCubeMX generated project](http://www.openstm32.org/Importing%2Ba%2BSTCubeMX%2Bgenerated%2Bproject)

[STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)

# 5. TODO List
- [ ] Implement GPIO Driver
- [ ] Implement SPI Driver
- [ ] Implement I2C Driver
- [ ] Implement UART Driver
