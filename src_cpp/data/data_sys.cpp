#include <nwl_pch.hpp>
#include "data_sys.h"

#include <nwl_math.hpp>
#include <data/data_image.h>
#include <data/data_mesh.h>
#include <core/nwl_container.h>
#include <core/nwl_string.h>
#include <io/io_stream.h>
#include <io/io_error.h>

NWL::dstring NWL::data_sys::s_strDir = &std::filesystem::current_path().generic_string()[0];

namespace NWL
{
    // --setters
    // --==<core_methods>==--
    void data_sys::on_init() { }
    void data_sys::on_quit() { }
    // --loading
    dstring data_sys::dialog_load(cstring filter, ptr user_data)
    {
#if (defined NWL_PLATFORM_WINDOWS)
        constexpr si32 nMaxChars = 256;
        char strRes[nMaxChars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = reinterpret_cast<HWND>(user_data);
        ofn.lpstrFile = &strRes[0];
        ofn.nMaxFile = nMaxChars;
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn)) { return dstring(ofn.lpstrFile); }
        else { return ""; }
#endif  // NWL_PLATFORM
    }
    bit data_sys::load_file(cstring file_path, ptr data, size nof_bytes)
    {
        in_file_stream fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(file_path, std::ios::in | std::ios::binary);
            fstm.read(static_cast<sbyte*>(data), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("loading fail"); return false; }
        return true;
    }
    bit data_sys::load_file(cstring file_path, dstring& data)
    {
        in_file_stream fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(file_path, std::ios_base::in | std::ios_base::binary);
            fstm.seekg(0, fstm.end);
            data.resize(fstm.tellg());
            fstm.seekg(0, fstm.beg);
            fstm.read(&data[0], data.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("loading fail"); return false; }
        return true;
    }
    bit data_sys::load_file(cstring file_path, a_info& data) {
        in_file_stream fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(file_path, std::ios_base::in | std::ios_base::binary);
            fstm >> data;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("saving fail"); return false; }
        return true;
    }
    // --saving
    dstring data_sys::dialog_save(cstring filter, ptr user_data)
    {
#if (defined NWL_PLATFORM_WINDOWS)
        constexpr si32 nMaxChars = 256;
        char strRes[nMaxChars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = reinterpret_cast<HWND>(user_data);
        ofn.lpstrFile = &strRes[0];
        ofn.nMaxFile = sizeof(strRes);
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn)) { return dstring(ofn.lpstrFile); }
        else { return ""; }
#endif  // NWL_PLATFORM
    }
    bit data_sys::save_file(cstring file_path, ptr data, size nof_bytes)
    {
        out_file_stream fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(file_path, std::ios::out | std::ios::binary);
            fstm.write(static_cast<sbyte*>(data), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure ex) { throw error("saving fail"); return false; }
        return true;
    }
    bit data_sys::save_file(cstring file_path, dstring& data)
    {
        out_file_stream fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(file_path, std::ios_base::out | std::ios_base::binary);
            fstm.write(&data[0], data.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("saving fail"); return false; }
        return true;
    }
    bit data_sys::save_file(cstring file_path, a_info& data)
    {
        out_file_stream fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(file_path, std::ios_base::out | std::ios_base::binary);
            fstm << data;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("saving fail"); return false; }
        return true;
    }
    // --==</core_methods>==--
}