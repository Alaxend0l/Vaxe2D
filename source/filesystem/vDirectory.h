#pragma once

// filesystem

#include "filesystem/vFile.h"

// std

#include <vector>
#include <memory>

namespace vaxe
{
    class vDirectory;

    class vDirectory : public std::enable_shared_from_this<vDirectory>
    {
    public:
        vDirectory(std::string base, std::string relative, std::string name, pugi::xml_node node) : m_basePath(base), m_relativePath(relative), m_name(name), m_xmlNode(node) {}

        std::shared_ptr<vDirectory> CreateSubDirectory(std::string base, std::string relative, std::string name)
        { 
            auto node = m_xmlNode.append_child(name.c_str());
            node.append_attribute("isFile") = false;
            m_folders.push_back(std::make_shared<vDirectory>(base, relative, name, node));
            m_folders.at(m_folders.size()-1)->SetParentDirectory(shared_from_this());
            return m_folders.at(m_folders.size()-1);
        }

        std::shared_ptr<vDirectory> AddSubDirectory(std::string base, std::string relative, pugi::xml_node node)
        { 
            m_folders.push_back(std::make_shared<vDirectory>(base, relative, node.name(), node));
            m_folders.at(m_folders.size()-1)->SetParentDirectory(shared_from_this());
            return m_folders.at(m_folders.size()-1);
        }

        void SetParentDirectory(std::shared_ptr<vDirectory> parent) { m_parent = parent; }

        std::shared_ptr<vDirectory> GetParentDirectory() { return m_parent; }

        int GetContentAmount() { return m_folders.size() + m_files.size(); }
        int GetFolderAmount() { return m_folders.size(); }
        int GetFileAmount() { return m_files.size(); }

        std::shared_ptr<vDirectory> GetDirectoryAtIndex(int index) { return m_folders[index]; }
        std::shared_ptr<vFile> GetFileAtIndex(int index) { return m_files[index]; }

        std::string GetBasePath() { return m_basePath; }
        std::string GetRelativePath() { return m_relativePath; }
        std::string GetName() { return m_name; }
        pugi::xml_node GetXMLNode() { return m_xmlNode; }
    private:
        std::vector<std::shared_ptr<vDirectory>> m_folders;
        std::vector<std::shared_ptr<vFile>> m_files;
        std::shared_ptr<vDirectory> m_parent;
        std::string m_basePath;
        std::string m_relativePath;
        std::string m_name;
        pugi::xml_node m_xmlNode;
        
    };
}