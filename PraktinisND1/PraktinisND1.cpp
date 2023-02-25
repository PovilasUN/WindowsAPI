#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
using namespace std;

const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void printOutMenu();
void pickFunctionFromMenu();
void formatNumbers();
void displayErrorMessages();
void displaySystemInformation();
void computeBASE64();
void findPrimes();
bool isPrime(int num);

int main()
{
    printOutMenu();
    pickFunctionFromMenu();
    return 0;
}

void printOutMenu()
{
    printf("1. Formatting the entered number with printf.\n");
    printf("2. Displaying error messages using Windows API.\n");
    printf("3. Displaying system information.\n");
    printf("4. BASE64 computation for \"Secure Programming\" text.\n");
    printf("5. Finding prime numbers.\n");
}

void pickFunctionFromMenu()
{
    int input;
    int number;
    scanf_s("%i", &input);
    switch (input)
    {
    case 1:
        formatNumbers();
        break;
    case 2:
        displayErrorMessages();
        break;
    case 3:
        displaySystemInformation();
        break;
    case 4:
        computeBASE64();
        break;
    case 5:
        findPrimes();
        break;
    default:
        printf("ERROR! Please choose a valid command.");
        break;
    }
}

void formatNumbers()
{
    float number;
    for (int i = 0; i < 3; i++)
    {
        scanf_s("%f", &number);
        if (i == 0)
        {
            printf("%.2f\n", number);
        }
        else if (i == 1)
        {
            printf("%.1f\n", floor(10.0 * number) / 10.0);
        }
        else
        {
            printf("%.2e", number);
        }
    }
}

void displayErrorMessages()
{
    int errorCode;
    LPWSTR errorMessage = NULL;
    for (int i = 0; i < 3; i++)
    {
        scanf_s("%u", &errorCode);
        if (errorCode < 1)
        {
            printf("No such error exists\n");
        }
        else
        {
            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                errorCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPWSTR)&errorMessage,
                0,
                NULL);
            wprintf(L"Message %i: %s\n", errorCode, errorMessage);
            LocalFree(errorMessage);
        }
    }
}

void displaySystemInformation()
{
    SYSTEM_INFO lpSystemInfo;
    GetNativeSystemInfo(&lpSystemInfo);
    printf("Number of Logical Processors: %lu\n", lpSystemInfo.dwNumberOfProcessors);
    printf("Page size: %lu Bytes\n", lpSystemInfo.dwPageSize);
    printf("Processor Mask: 0x%x\n", lpSystemInfo.dwActiveProcessorMask);
    printf("Minimum process address: 0x%p\n", lpSystemInfo.lpMinimumApplicationAddress);
    printf("Maximum process address: 0x%p\n", lpSystemInfo.lpMaximumApplicationAddress);
}

void computeBASE64()
{
    string text = "Secure Programming";
    string encoded_text;
    int i = 0;
    while (i < text.length()) {
        unsigned char byte1 = i < text.length() ? text[i++] : 0;
        unsigned char byte2 = i < text.length() ? text[i++] : 0;
        unsigned char byte3 = i < text.length() ? text[i++] : 0;

        unsigned char enc1 = base64_chars[byte1 >> 2];
        unsigned char enc2 = base64_chars[((byte1 & 3) << 4) | (byte2 >> 4)];
        unsigned char enc3 = i <= text.length() + 1 ? base64_chars[((byte2 & 15) << 2) | (byte3 >> 6)] : '=';
        unsigned char enc4 = i <= text.length() ? base64_chars[byte3 & 63] : '=';

        encoded_text += enc1;
        encoded_text += enc2;
        encoded_text += enc3;
        encoded_text += enc4;
    }
    printf("%s", encoded_text.c_str());
}

void findPrimes()
{
    int number;
    while (true)
    {
        scanf_s("%i", &number);
        if (number == 0)
        {
            break;
        }
        else
        {
            printf(isPrime(number) ? "TRUE\n" : "FALSE\n");
        }
    }
}

bool isPrime(int num)
{
    if (num <= 1) {
        return false;
    }
    int limit = sqrt(num);
    for (int i = 2; i <= limit; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}
