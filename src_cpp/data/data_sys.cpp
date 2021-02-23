#include <nwl_pch.hpp>
#include "data_sys.h"

#include <nwl_math.hpp>
#include <core/nwl_container.h>
#include <core/nwl_string.h>
#include <io/io_stream.h>
#include <io/io_exception.h>

#define STB_IMAGE_IMPLEMENTATION
#include <../ext/stbi/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <../ext/stbi/stb_image_write.h>

NWL::String NWL::DataSys::s_strRscDir = &std::filesystem::current_path().generic_string()[0];

namespace NWL
{
    // --setters
    // --==<core_methods>==--
    void DataSys::OnInit() {}
    void DataSys::OnQuit() {}
    // --file_dialogs
    const char* DataSys::FDialogSave(const char* strFilter, Ptr pWindow)
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
        if (GetSaveFileNameA(&ofn)) { return ofn.lpstrFile; }
        else { return ""; }
#endif  // NWL_PLATFORM
    }
    const char* DataSys::FDialogLoad(const char* strFilter, Ptr pWindow)
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
        if (GetOpenFileNameA(&ofn)) { return ofn.lpstrFile; }
        else { return ""; }
#endif  // NWL_PLATFORM
    }

    // --binary_data
    bool DataSys::SaveFData(const char* strFPath, void* pData, Size szBytes)
    {
        OutFStream fStream;
        fStream.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fStream.open(strFPath, std::ios::out | std::ios::binary);
            fStream.write(static_cast<char*>(pData), szBytes);
            fStream.close();
        }
        catch (std::ios_base::failure ex) { return false; }
        return true;
    }
    bool DataSys::LoadFData(const char* strFPath, void* pData, Size szBytes)
    {
        InFStream fStream;
        fStream.exceptions(std::ios::badbit | std::ios::failbit);
        try {
            fStream.open(strFPath, std::ios::in | std::ios::binary);
            fStream.read(static_cast<char*>(pData), szBytes);
            fStream.close();
        }
        catch (std::ios_base::failure ex)
        {
            return false;
        }
        return true;
    }
    // --strings
    bool DataSys::SaveFString(const char* strFPath, const char* strSrc, Size szBytes)
    {
        IOFStream fStream;
        fStream.exceptions(std::ios::badbit | std::ios::failbit);
        StrStream strStream;
        try {
            fStream.open(strFPath, std::ios::out, std::ios::binary);
            fStream.write(&strSrc[0], szBytes);
            fStream.close();
            return true;
        }
        catch (std::ios_base::failure ex) {
            return false;
        }
    }
    bool DataSys::LoadFString(const char* strFPath, String& strDest)
    {
        IOFStream fStream;
        fStream.exceptions(std::ios::badbit | std::ios::failbit);
        StrStream strStream;
        try {
            fStream.open(strFPath, std::ios::in, std::ios::binary);
            fStream.seekg(0, std::ios::end);
            strDest.resize(fStream.tellg());
            fStream.seekg(0, std::ios::beg);
            strStream << fStream.rdbuf();
            strcpy_s(&strDest[0], strDest.size(), &strStream.str()[0]);
            fStream.close();
            return true;
        }
        catch (std::ios_base::failure ex) { return false; }
        return true;
    }

    // --images
    bool DataSys::SaveFImage(const char* strFPath, Image& rImage)
    {
        stbi_write_png(strFPath, rImage.GetSizeW(), rImage.GetSizeH(), 0, rImage.GetData(), 0);
        return true;
    }
    bool DataSys::LoadFImage(const char* strFPath, Image& rImage)
    {
        try {
            const char* strFormat = CStrGetDelimR(&strFPath[0], '.');
            if (CStrIsEqual(strFormat, ".bmp")) { return LoadFImageBmp(strFPath, rImage); }
            else if (CStrIsEqual(strFormat, ".png")) { return LoadFImagePng(strFPath, rImage); }
            else { return false; }
        }
        catch (std::ios_base::failure ex) { return false; }

        return true;
    }
    bool DataSys::LoadFImageBmp(const char* strFPath, Image& rImage)
    {
        // a bitmap file described with some chunks of data
        // the first "file header": signature, file size, reserved1, reserved2, file offset to pixels
        // the second one "info(dib) header": size, width, height, planes, bitcount, compression,
        // image size, xpels per meter, ypels per meter, colors used, color important
        IOFStream fStream(strFPath, std::ios_base::out | std::ios_base::in | std::ios_base::binary);
        BitMapInfo bmInfo;
        ImageInfo imgInfo;
        fStream.read(reinterpret_cast<Byte*>(&bmInfo.File), sizeof(bmInfo.File));
        fStream.read(reinterpret_cast<Byte*>(&bmInfo.Desc), sizeof(bmInfo.Desc));
        fStream.read(reinterpret_cast<Byte*>(&bmInfo.Clut), sizeof(bmInfo.Clut));

        imgInfo.nWidth = bmInfo.Desc.nWidth;
        imgInfo.nHeight = bmInfo.Desc.nHeight;
        imgInfo.nChannels = bmInfo.Desc.nPxBits / 8;
        rImage.SetData(nullptr, imgInfo);

        const Int32 nStride = ((bmInfo.Desc.nWidth * bmInfo.Desc.nPxBits + (32 - 1)) & (32 - 1)) >> 3;
        const Int32 nPad = (4 - (rImage.GetSizeW() * rImage.GetChannels()) % 4) % 4;

        switch (rImage.GetChannels()) {
        case 1: {
            for (Int32 iy = 0; iy < rImage.GetSizeH(); iy++) {
                for (Int32 ix = 0; ix < rImage.GetSizeW(); ix++) {
                    rImage.SetPixel(ix, iy, fStream.get(), fStream.get(), fStream.get());
                }
                fStream.seekg(nPad, std::ios_base::cur);
            }
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            fStream.seekg(bmInfo.File.szOffset, std::ios_base::beg);
            for (Int32 iy = 0; iy < rImage.GetSizeW(); iy++) {
                for (Int32 ix = 0; ix < rImage.GetSizeH(); ix++) {
                    rImage.SetPixel(ix, iy, fStream.get(), fStream.get(), fStream.get());
                }
                fStream.seekg(nPad, std::ios_base::cur);
            }
            break;
        }
        case 4: {
            fStream.seekg(bmInfo.File.szOffset, std::ios_base::beg);
            for (Int32 iy = 0; iy < rImage.GetSizeH(); iy++) {
                for (Int32 ix = 0; ix < rImage.GetSizeW(); ix++) {
                    rImage.SetPixel(ix, iy, fStream.get(), fStream.get(), fStream.get(), fStream.get());
                }
                fStream.seekg(nPad, std::ios_base::cur);
            }
            break;
        }default: throw(Exception("unsupported format", ERC_NO_SUPPORT)); break;
        }

        return true;
    }
    bool DataSys::LoadFImagePng(const char* strFPath, Image& rImage) {
        UByte* pData = nullptr;
        ImageInfo imgInfo = rImage.GetInfo();
        pData = stbi_load(strFPath, &imgInfo.nWidth, &imgInfo.nHeight, &imgInfo.nChannels, 0);
        
        if (pData == nullptr) { return false; }
        else { rImage.SetData(pData, imgInfo); }
        stbi_image_free(pData);
        
        return true;
    }
    // --meshes
    bool DataSys::SaveFMesh(const char* strFPath, GfxMeshInfo& rMesh)
    {
        try {
        }
        catch (std::ios_base::failure ex) { return false; }
           
        return true;
    }
    bool DataSys::LoadFMesh(const char* strFPath, GfxMeshInfo& rMesh)
    {
        String strBuf;
        try {
            if (!LoadFString(strFPath, strBuf)) { return false; }
            const char* strFormat = CStrGetDelimR(&strFPath[0], '.');
            if (strcmp(strFormat, ".obj") == 0) { return LoadFMeshObj(&strBuf[0], rMesh); }
            else { return false; }
        }
        catch (std::ios_base::failure ex) { return false; }

        return true;
    }
    bool DataSys::LoadFMeshObj(const char* strFile, GfxMeshInfo& rMesh) {
        String strBuf;
        StrStream strStream(strFile);
        DArray<V3f> vtxCrd;
        DArray<V2f> texCrd;
        DArray<V3f> nrmCrd;
        DArray<UInt32> idxData;

        vtxCrd.reserve(1 << 12);
        texCrd.reserve(1 << 12);
        nrmCrd.reserve(1 << 12);
        idxData.reserve(1 << 12);

        while (strStream >> strBuf) { if (strBuf != rMesh.strName) { continue; } }
        if (strBuf != rMesh.strName) { return false; }
        while (strStream >> strBuf) {
            if (strBuf == "usemtl") { strStream >> rMesh.strMtlName; }
            if (strBuf == "v") {
                vtxCrd.push_back(V3f());
                for (UInt32 vti = 0; vti < 3; vti++) {
                    if (!(strStream >> vtxCrd.back()[vti])) { return false; }
                }
            }
            if (strBuf == "vt") {
                texCrd.push_back(V3f());
                for (UInt32 vti = 0; vti < 2; vti++) {
                    if (!(strStream >> texCrd.back()[vti])) { return false; }
                }
            }
            if (strBuf == "vn") {
                nrmCrd.push_back(V3f());
                for (UInt32 vti = 0; vti < 3; vti++) { if (!(strStream >> nrmCrd.back()[vti])) { return false; } }
            }
            if (strBuf == "f") {
                strStream >> strBuf;
                idxData.push_back(0);
                if (sscanf_s(&strBuf[0], "%d/%d/%d", &idxData.back(), &idxData.back(), &idxData.back()) != 3) { return false; }
            }
        }

        Size nMin = 0;
        nMin = nMin > vtxCrd.size() ? nMin : vtxCrd.size();
        nMin = nMin > texCrd.size() ? nMin : texCrd.size();
        nMin = nMin > nrmCrd.size() ? nMin : nrmCrd.size();
        rMesh.vtxData.resize(nMin * sizeof(Float32) * (3 + 2 + 3));
        for (UInt32 vti = 0; vti < nMin; vti++) {
            Size szOffset = 0;
            szOffset = vti * sizeof(Float32) * (3 + 2 + 3) + sizeof(Float32) * (0);
            memcpy(&rMesh.vtxData[szOffset], &vtxCrd[vti], sizeof(vtxCrd[vti]));
            szOffset = vti * sizeof(Float32) * (3 + 2 + 3) + sizeof(Float32) * (3);
            memcpy(&rMesh.vtxData[szOffset], &texCrd[vti], sizeof(texCrd[vti]));
            szOffset = vti * sizeof(Float32) * (3 + 2 + 3) + sizeof(Float32) * (3 + 2);
            memcpy(&rMesh.vtxData[szOffset], &texCrd[vti], sizeof(texCrd[vti]));
        }

        rMesh.idxData.resize(idxData.size() * sizeof(UInt32));
        memcpy(&rMesh.idxData[0], &idxData[0], rMesh.idxData.size());

        return true;
    }
    // --models
    bool DataSys::SaveFModel(const char* strFPath, GfxModelInfo& rModel)
    {
        try {
        }
        catch (std::ios_base::failure ex) { return false; }
        
        return true;
    }
    bool DataSys::LoadFModel(const char* strFPath, GfxModelInfo& rModel)
    {
        String strBuf;
        try {
            if (!LoadFString(strFPath, strBuf)) { return false; }
            const char* strFormat = CStrGetDelimR(strFPath, '.', 1);
            if (strcmp(strFormat, ".obj") == 0) { return LoadFModelObj(&strBuf[0], rModel); }
            else { return false; }
        }
        catch (std::ios_base::failure ex) { return false; }

        return true;
    }
    bool DataSys::LoadFModelObj(const char* strFile, GfxModelInfo& rModel) {
        String strBuf;
        StrStream strStream(strFile);
        DArray<V3f> vtxCrd;
        DArray<V2f> texCrd;
        DArray<V3f> nrmCrd;
        DArray<UInt32> idxData;

        auto fnUploadMesh = [&](GfxMeshInfo& rMesh)->bool {
            if (vtxCrd.size() == 0 || texCrd.size() == 0 || nrmCrd.size() == 0 || idxData.size() == 0) { return false; }
            Size nMin = 0;
            nMin = nMin > vtxCrd.size() ? nMin : vtxCrd.size();
            nMin = nMin > texCrd.size() ? nMin : texCrd.size();
            nMin = nMin > nrmCrd.size() ? nMin : nrmCrd.size();
            rMesh.vtxData.resize(nMin * sizeof(Float32) * (3 + 2 + 3));
            for (Size vti = 0; vti < nMin; vti++) {
                Size szOffset = 0;
                szOffset = vti * sizeof(Float32) * (3 + 2 + 3) + sizeof(Float32) * (0);
                memcpy(&rMesh.vtxData[szOffset], &vtxCrd[vti], sizeof(vtxCrd[vti]));
                szOffset = vti * sizeof(Float32) * (3 + 2 + 3) + sizeof(Float32) * (3);
                memcpy(&rMesh.vtxData[szOffset], &texCrd[vti], sizeof(texCrd[vti]));
                szOffset = vti * sizeof(Float32) * (3 + 2 + 3) + sizeof(Float32) * (3 + 2);
                memcpy(&rMesh.vtxData[szOffset], &texCrd[vti], sizeof(texCrd[vti]));
            }

            rMesh.idxData.resize(idxData.size() * sizeof(UInt32));
            memcpy(&rMesh.idxData[0], &idxData[0], rMesh.idxData.size());
            vtxCrd.clear();
            texCrd.clear();
            nrmCrd.clear();
            idxData.clear();
            vtxCrd.reserve(1 << 12);
            texCrd.reserve(1 << 12);
            nrmCrd.reserve(1 << 12);
            idxData.reserve(1 << 12);
            return true;
        };

        vtxCrd.reserve(1 << 12);
        texCrd.reserve(1 << 12);
        nrmCrd.reserve(1 << 12);
        idxData.reserve(1 << 12);
        while (strStream >> strBuf) {
            if (strBuf == "g") {
                rModel.Meshes.push_back(GfxMeshInfo());
                strStream >> rModel.Meshes.back().strName;
                while (strStream >> strBuf) {
                    if (strBuf == "usemtl") { strStream >> rModel.Meshes.back().strMtlName; }
                    if (strBuf == "v") {
                        vtxCrd.push_back(V3f());
                        for (UInt32 vti = 0; vti < 3; vti++) {
                            if (!(strStream >> vtxCrd.back()[vti])) { return false; }
                        }
                    }
                    if (strBuf == "vt") {
                        texCrd.push_back(V3f());
                        for (UInt32 vti = 0; vti < 2; vti++) {
                            if (!(strStream >> texCrd.back()[vti])) { return false; }
                        }
                    }
                    if (strBuf == "vn") {
                        nrmCrd.push_back(V3f());
                        for (UInt32 vti = 0; vti < 3; vti++) { if (!(strStream >> nrmCrd.back()[vti])) { return false; } }
                    }
                    if (strBuf == "f") {
                        for (UInt32 idi = 0; idi < 3; idi++) {
                            strStream >> strBuf;
                            idxData.push_back(0);
                            if (sscanf_s(&strBuf[0], "%d/%d/%d", &idxData.back(), &idxData.back(), &idxData.back()) != 3) { return false; }
                        }
                    }
                    if (strBuf == "g") { break; }
                }
                if (!fnUploadMesh(rModel.Meshes.back())) { return false; }
            }
        }
        return true;
    }
    // --==</core_methods>==--
}