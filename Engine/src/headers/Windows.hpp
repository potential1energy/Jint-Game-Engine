#pragma once

namespace JintGEEn {
    namespace Windows {
        struct Window {
        public:
            unsigned int GetWidth();
            unsigned int GetHeight();

            bool IsGraphicsReady();

            void SetWidth(unsigned int width);
            void SetHeight(unsigned int height);

            void ResetGraphics();

            void* internalWindow;
        };

        Window* CreateWindow(const char* windowTitle, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        void DestroyWindow(Window* pWindow);

        void EventUpdate(Window* pWindow);
    }
}