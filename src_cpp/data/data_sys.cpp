#include <nwl_pch.hpp>
#include "data_sys.h"

#include <nwl_math.hpp>
#include <data/data_image.h>
#include <data/data_mesh.h>
#include <core/nwl_container.h>
#include <core/nwl_string.h>
#include <io/io_stream.h>
#include <io/io_exception.h>

NWL::String NWL::DataSys::s_strDir = &std::filesystem::current_path().generic_string()[0];

namespace NWL
{
    // --setters
    // --==<core_methods>==--
    void DataSys::OnInit()
    {
    }
    void DataSys::OnQuit() {}
    // --file_dialogs
    String DataSys::DialogSave(const char* strFilter, Ptr pWindow)
    {
#if (defined NWL_PLATFORM_WINDOWS)
        constexpr Int32 nMaxChars = 256;
        char strRes[nMaxChars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = reinterpret_cast<HWND>(pWindow);
        ofn.lpstrFile = &strRes[0];
        ofn.nMaxFile = sizeof(strRes);
        ofn.lpstrFilter = strFilter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn)) { return String(ofn.lpstrFile); }
        else { return ""; }
#endif  // NWL_PLATFORM
    }
    String DataSys::DialogLoad(const char* strFilter, Ptr pWindow)
    {
#if (defined NWL_PLATFORM_WINDOWS)
        constexpr Int32 nMaxChars = 256;
        char strRes[nMaxChars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = reinterpret_cast<HWND>(pWindow);
        ofn.lpstrFile = &strRes[0];
        ofn.nMaxFile = nMaxChars;
        ofn.lpstrFilter = strFilter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn)) { return String(ofn.lpstrFile); }
        else { return ""; }
#endif  // NWL_PLATFORM
    }
    // --binary_data
    bool DataSys::SaveFile(const char* strFPath, Ptr pData, Size szBytes)
    {
        OutFStream fStream;
        fStream.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fStream.open(strFPath, std::ios::out | std::ios::binary);
            fStream.write(static_cast<Byte*>(pData), szBytes);
            fStream.close();
        }
        catch (std::ios_base::failure ex) { throw Exception("saving fail"); return false; }
        return true;
    }
    bool DataSys::LoadFile(const char* strFPath, Ptr pData, Size szBytes)
    {
        InFStream fStream;
        fStream.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fStream.open(strFPath, std::ios::in | std::ios::binary);
            fStream.read(static_cast<Byte*>(pData), szBytes);
            fStream.close();
        }
        catch (std::ios_base::failure exc) { throw Exception("loading fail"); return false; }
        return true;
    }
    // --strings
    bool DataSys::SaveFile(const char* strFPath, String& rData)
    {
        OutFStream fStream;
        fStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fStream.open(strFPath, std::ios_base::out | std::ios_base::binary);
            fStream.write(&rData[0], rData.size());
            fStream.close();
        }
        catch (std::ios_base::failure exc) { throw Exception("saving fail"); return false; }
        return true;
    }
    bool DataSys::LoadFile(const char* strFPath, String& rData)
    {
        InFStream fStream;
        fStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fStream.open(strFPath, std::ios_base::in | std::ios_base::binary);
            fStream.seekg(0, fStream.end);
            rData.resize(fStream.tellg());
            fStream.seekg(0, fStream.beg);
            fStream.read(&rData[0], rData.size());
            fStream.close();
        }
        catch (std::ios_base::failure exc) { throw Exception("loading fail"); return false; }
        return true;
    }
    // --images
    bool DataSys::SaveFile(const char* strFPath, AInfo& rData)
    {
        OutFStream fStream;
        fStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fStream.open(strFPath, std::ios_base::out | std::ios_base::binary);
            fStream << rData;
            fStream.close();
        }
        catch (std::ios_base::failure exc) { throw Exception("saving fail"); return false; }
        return true;
    }
    bool DataSys::LoadFile(const char* strFPath, AInfo& rData) {
        InFStream fStream;
        fStream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fStream.open(strFPath, std::ios_base::in | std::ios_base::binary);
            fStream >> rData;
            fStream.close();
        }
        catch (std::ios_base::failure exc) { throw Exception("saving fail"); return false; }
        return true;
    }
    // --==</core_methods>==--
}