#pragma once

#include <cstddef>
#include <iostream>


namespace JintGEEn {
    namespace Windows {
        struct internalWindow;
        struct Window {
        public:
            void SetWidth(unsigned int width);
            void SetHeight(unsigned int height);
            void SetDimensions(unsigned int width, unsigned int height);
            unsigned int GetWidth();
            unsigned int GetHeight();

            void SetXPosition(unsigned int x);
            void SetYPosition(unsigned int y);
            void SetPosition(unsigned int x, unsigned int y);
            unsigned int GetXPosition();
            unsigned int GetYPosition();

            template<class T>
            void SetProperty(const char* name, T data) {
                if (this->propertyExists(name)) this->DeleteProperty(name);
                unsigned char* buffer = new unsigned char[sizeof(T)];
                *(T*)buffer = data;
                this->setProperty(name, buffer);
            }
            template<class T>
            T GetProperty(const char* name) {
                unsigned char* buffer = (unsigned char*)this->getProperty(name);
                return *(T*)buffer;
            }
            bool PropertyExists(const char* name) {return this->propertyExists(name);}
            void DeleteProperty(const char* name) {
                unsigned char* data = (unsigned char*)this->getProperty(name);
                this->deleteProperty(name);
                delete[] data;
            }

            internalWindow* pInternalWindow;
        private:
            void setProperty(const char* name, void* pData);
            void* getProperty(const char* name);
            bool propertyExists(const char* name);
            void deleteProperty(const char* name);
        };
        enum class EventType {
            Render
        };
        struct Event {
            EventType type;
            Window* pWindow;
        };

        Window* CreateWindow(const char* windowTitle, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        void DestroyWindow(Window* pWindow);
        void DestroyAllWindows();

        Event NextEvent();
    }
}