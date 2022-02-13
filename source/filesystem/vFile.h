#pragma once

// std

#include <string>

// lib

#define PUGIXML_HEADER_ONLY
#include <pugixml.hpp>

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