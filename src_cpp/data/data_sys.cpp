#include <nwl_pch.hpp>
#include "data_sys.h"
#if (defined NW_OS)
#include <nwl_math.hpp>
#include <core/nwl_container.h>
#include <core/nwl_string.h>
#include <io/io_stream.h>
#include <io/io_error.h>
using namespace std::filesystem;
NW::dstring NW::data_sys::s_root_path = "default";
NW::dstring NW::data_sys::s_temp_path = "default";
#if (NW_OS & NW_OS_WIN)
namespace NW
{
    // --getters
    cstring data_sys::get_path() {
        return &current_path().string()[0];
    }
    cstring data_sys::get_path(cstring file_path) {
        s_temp_path = (current_path() / file_path).string();
        return &s_temp_path[0];
    }
    // --setters
    void data_sys::set_dir_root(cstring root_directory) {
        if (!::SetCurrentDirectoryA(root_directory)) { throw error("failed to set new directory"); }
    }
    // --==<core_methods>==--
    void data_sys::on_init()
    {
        s_root_path.resize(256);
        set_dir_root(&current_path().parent_path().string()[0]);
        std::cout << "data_system has been initialized;" << std::endl;
        std::cout << "new root directory: " << get_path() << ";" << std::endl;
    }
    void data_sys::on_quit()
    {
        std::cout << "data_system has been quitted;" << std::endl;
        s_root_path = "default";
    }
    // --loading
    cstring data_sys::dialog_load(cstring filter, const window_handle& wnd)
    {
        constexpr si32 max_chars = 256;
        char str_res[max_chars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = max_chars;
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&ofn)) { return &(s_temp_path = ofn.lpstrFile)[0]; }
        else { return ""; }
    }
    bit data_sys::load_file(cstring file_path, ptr data, size nof_bytes)
    {
        in_stream_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios::in | std::ios::binary);
            fstm.read(static_cast<sbyte*>(data), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("loading fail"); return false; }
        return true;
    }
    bit data_sys::load_file(cstring file_path, dstring& data)
    {
        in_stream_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::in | std::ios_base::binary);
            fstm.seekg(0, fstm.end);
            data.resize(fstm.tellg());
            fstm.seekg(0, fstm.beg);
            fstm.read(&data[0], data.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("loading fail"); return false; }
        return true;
    }
    bit data_sys::load_file(cstring file_path, a_data_rsc& data) {
        in_stream_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::in | std::ios_base::binary);
            fstm >> data;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("loading fail"); return false; }
        return true;
    }
    // --saving
    cstring data_sys::dialog_save(cstring filter, const window_handle& wnd)
    {
        constexpr si32 max_chars = 256;
        char str_res[max_chars]{ 0 };
        OPENFILENAMEA ofn{ 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = wnd;
        ofn.lpstrFile = &str_res[0];
        ofn.nMaxFile = sizeof(str_res);
        ofn.lpstrFilter = filter;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetSaveFileNameA(&ofn)) { return &(s_temp_path = ofn.lpstrFile)[0]; }
        else { return ""; }
    }
    bit data_sys::save_file(cstring file_path, ptr data, size nof_bytes)
    {
        out_stream_file fstm;
        fstm.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios::out | std::ios::binary);
            fstm.write(static_cast<sbyte*>(data), nof_bytes);
            fstm.close();
        }
        catch (std::ios_base::failure ex) { throw error("saving fail"); return false; }
        return true;
    }
    bit data_sys::save_file(cstring file_path, dstring& data)
    {
        out_stream_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::out | std::ios_base::binary);
            fstm.write(&data[0], data.size());
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("saving fail"); return false; }
        return true;
    }
    bit data_sys::save_file(cstring file_path, a_data_rsc& data)
    {
        out_stream_file fstm;
        fstm.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        try {
            fstm.open(&get_path(file_path)[0], std::ios_base::out | std::ios_base::binary);
            fstm << data;
            fstm.close();
        }
        catch (std::ios_base::failure exc) { throw error("saving fail"); return false; }
        return true;
    }
    // --==</core_methods>==--
}
#endif
#endif  // NW_OS