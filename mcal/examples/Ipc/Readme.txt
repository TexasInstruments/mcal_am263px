Steps to Test IPC example apps
==============================

- SDK Binaries(.out files for each core) required for testing IPC example apps (SDK Binaries Path: mcal_sitara_mcu\mcal_test\ipc_test\SDK_Binarys_am263)

- Once available, indivisually flash each binary to its corresponding core (e.g R5_0:example_app, R5_1:r5fss0-1.out, R5_2:r5fss1-0.out & R5_3:r5fss1-1.out )

- Now run each core followed by r5_0 and proceed with the testing

  In case SDK Binaries not available, 
  
  Download & install platform specific MCU+SDK, then load new project in ccs from path 
  "C:\ti\mcu_plus_sdk_am263px_10_02_00_15\examples\drivers\ipc\ipc_notify_echo\am263px-cc\system_freertos_nortos", it will load 
  the required files, then build the binaries directly in ccs and follow the testing steps as mentioned. 

-NOTE:
 While testing IPC UTs, check the test-cases if using special contiditions(low-buffer, stress test etc.), and use the same SDK binary for that. 
