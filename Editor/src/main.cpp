#include "Engine.hpp"
#include "Windows.hpp"

int main() {
    #ifdef __linux__

    JintGEEn::Initalize();

    auto window = JintGEEn::Windows::CreateWindow("Test1 window", 0,0, 800,600);

    while (true) {
        JintGEEn::Windows::EventUpdate(window);
    }

    JintGEEn::Windows::DestroyWindow(window);

    JintGEEn::Cleanup();
    #endif
}