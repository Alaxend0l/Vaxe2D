#include "filesystem/vProject.h"

#include <iostream>

// types

#include "types/vByte1.h"
#include "types/vByte2.h"

namespace vaxe
{
    vProject::vProject()
    {
        m_currentScene = std::make_shared<vScene>();
        

        if (!LoadConfigFile())
        {
            CreateNewConfigFile();
        }
    }

    vProject::~vProject()
    {

    }

    bool vProject::LoadConfigFile()
    {
        pugi::xml_parse_result result = doc.load_file((m_path + "/vconfig.xml").c_str());

        if (!result)
        {
            return 0;
        }

        m_currentDirectory = std::make_shared<vDirectory>(m_path, "", "Base", doc.child("Hierarchy"));

        IterateThroughDirectory(m_currentDirectory);
        return 1;
    }

    bool vProject::CreateNewConfigFile()
    {
        m_currentDirectory = std::make_shared<vDirectory>(m_path, "", "Base", doc.append_child("Hierarchy"));
        
        auto audioDir = CreateDirectory(m_currentDirectory, "Audio");
        CreateDirectory(m_currentDirectory, "Fonts");
        CreateDirectory(m_currentDirectory, "Scenes");
        CreateDirectory(m_currentDirectory, "Scripts");
        CreateDirectory(m_currentDirectory, "Textures");

        CreateDirectory(audioDir, "Music");
        CreateDirectory(audioDir, "SoundEffects");

        return doc.save_file((m_path + "/vconfig.xml").c_str());

    }

    std::shared_ptr<vDirectory> vProject::CreateDirectory(std::shared_ptr<vDirectory> directory, std::string name)
    {
        std::string relativePath = directory->GetRelativePath() + "/" + name;
        std::string basePath = m_path + relativePath;
        std::filesystem::create_directory(basePath);

        return directory->CreateSubDirectory(name);
    }

    std::shared_ptr<vDirectory> vProject::CreateSubDirectoryInCurrentDirectory(std::string name)
    {
        std::string relativePath = m_currentDirectory->GetRelativePath() + "/" + name;
        std::string basePath = m_path + relativePath;
        std::filesystem::create_directory(basePath);

        return m_currentDirectory->CreateSubDirectory(name);
    }

    void HandleFiles(byte_1 type, byte_1 variant, pugi::xml_node child)
    {
        switch ((int)type)
        {
            default:
                std::cout << "Unknown File Type! " << child.name() << std::endl;
                break;

            case VFILE_UNKNOWN:
                std::cout << "Deliberately Unknown File Type! " << child.name() << std::endl;
                break;

            case VFILE_VETA:
                std::cout << "Ignore this! " << child.name() << std::endl;
                break;
        }
    }


    void vProject::IterateThroughDirectory(std::shared_ptr<vDirectory> directory)
    {
        for (pugi::xml_node child = directory->GetXMLNode().first_child(); child;)
        {
            // Get next child node before possibly deleting current child
            pugi::xml_node next = child.next_sibling();

            // Check whether child node shall be deleted
            bool isFile = child.attribute("isFile").as_bool();

            if (isFile)
            {
                byte_2 fullType = child.attribute("filetype").as_uint();
                byte_1 fileType = (fullType & 0xFF00) << 8;
                byte_1 typeVariant = (fullType & 0x00FF);
                
                HandleFiles(fileType, typeVariant, child);

            }
            else
            {
                std::string relative = directory->GetRelativePath() + "/" + child.name();

                std::cout << "Adding directory: " << relative << std::endl;
                
                std::shared_ptr<vDirectory> newDirectory = directory->AddSubDirectory(child);
                IterateThroughDirectory(newDirectory);

            }
            child = next;
        }
    }

    bool vProject::SaveProject()
    {
        return doc.save_file((m_path + "/vconfig.xml").c_str());
    }
}