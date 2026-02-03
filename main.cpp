#include <iostream>
#include <mfvirtualcamera.h>
#include <combaseapi.h>

class VirtualCamera {
public:
    VirtualCamera() {

        LPOLESTR clsid;

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

            switch(hr) {
                case E_INVALIDARG: std::cerr << "Invalid Argument"; break;
                case E_OUTOFMEMORY: std::cerr << "Out of memory"; break;
                case E_POINTER: std::cerr << "Invalid pointer"; break;
                case E_ACCESSDENIED: std::cerr << "Access Denied"; break;
                default: std::cerr << hr;
            }

            std::cerr << std::endl;
            exit(hr);
        }

        CoTaskMemFree(clsid);
    }

    void Dispose() {
    }

private:
    IMFVirtualCamera* camera;

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

