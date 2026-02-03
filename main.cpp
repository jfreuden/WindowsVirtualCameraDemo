#include <iostream>
#include <mfvirtualcamera.h>
#include <combaseapi.h>

// Source - https://stackoverflow.com/a/17387176
// Posted by Jamin Grey, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-03, License - CC BY-SA 4.0 - Tweaked by Joshua Freudenhammer to handle this one usecase

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString(DWORD errorMessageID = 0)
{
    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
}


class VirtualCamera {
public:
    VirtualCamera() {
        LPOLESTR clsid;

        if (const HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED); FAILED(hr)) {
            std::cerr << "Failed to initialize COM: " << GetLastErrorAsString(hr) << std::endl;
        }

        if (const HRESULT hr = StringFromCLSID(GetGUID(), &clsid); FAILED(hr)) {
            std::cerr << "Failed to create GUID: " << hr << std::endl;
            exit(hr);
        }


        const HRESULT hr = MFCreateVirtualCamera(
            MFVirtualCameraType_SoftwareCameraSource,
            MFVirtualCameraLifetime_Session,
            MFVirtualCameraAccess_CurrentUser,
            reinterpret_cast<LPCWSTR>("Rainybyte"),
            clsid,
            nullptr,
            0,
            &camera
        );

        if FAILED(hr) {
            std::cerr << "Failed to create Virtual Camera: ";

            std::string error_string = GetLastErrorAsString(hr);
            std::cerr << error_string << std::endl;

            exit(hr);
        }

        CoTaskMemFree(clsid);
    }

    void Dispose() {
    }

private:
    IMFVirtualCamera* camera {};

    static GUID GetGUID() {
        GUID guid;

        if (const HRESULT hr = CoCreateGuid(&guid); FAILED(hr)) {
            std::cerr << "Failed to create GUID: " << hr << std::endl;
            exit(hr);
        }

        return guid;
    }
};

int main() {
    std::cout << "Beginning virtual camera demonstration" << std::endl;
    auto bob = VirtualCamera();



    std::cout << "Hello, World!" << std::endl;
    return 0;
}

