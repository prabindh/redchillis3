1. DIRECTORY STRUCTURE

redchillis3_src - Contains 1 header file containing the API
redchillis3_test - Contains a C++ sample application for using the REDCHILLIS3 DLL directly
redchillis3_test_dotnet - Contains a .NET sample application for using the REDCHILLIS3 DLL, wrapped in a middle layer DLL that programs the keys
redchillis3mm - Contains the middle layer DLL that programs the keys. This DLL is used by the .NET sample application

All projects are provided with Visual Studio 2005 .VCPROJ files.

2. HOW DO I START ?


a. Get a S3 account. Include the keys in the respective project you want to use. 
For C++ application, place it in the placeholder in the redchillis3.cpp file in redchillis3_test folder.
For .NET application, place it in the placeholder in the redchillis3mm_interface.cpp file in the redchillis3mm folder.

b. Build the required sample application, and run it. Depending on where you are, you might be required to set the proxy.

c. Build your own applications by securing the keys in a secure manner that would not necessarily make it impossible to hack it, 
but makes it infeasible compared to the value of data you are protecting. It is always better to keep checking your AWS account periodically to
check misuse of your keys.