#pragma once

// std

#include <string>

// lib

#define PUGIXML_HEADER_ONLY
#include <pugixml.hpp>

#define VFILE_UNKNOWN       0x00
#define VFILE_VETA          0x01 //Equivalent to Unity .meta Files
#define VFILE_IMAGE         0x02

#define VFILE_IMAGE_PNG     0x00
#define VFILE_IMAGE_JPEG    0x01
#define VFILE_IMAGE_GIF     0x02

namespace vaxe
{
    class vFile
    {
    public:
        vFile();
    private:
        std::string m_path;
        pugi::xml_node m_xmlNode;
    };
}